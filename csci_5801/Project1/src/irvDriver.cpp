#include "irvDriver.h"
#define INVALID_CUTOFF 3

void IRVDriver::run(std::string filename){

  bool invalidChecking = true;

  //start parsing file
  std::ifstream filein(filename);

  auditor.auditStream << "-------FILE HEADER INFORMATION-------" <<std::endl;

  //store header lines
  std::string line;
  std::getline(filein, line);
  auditor.auditStream<<line<<std::endl;
  auditor.mediaStream << "Election type: " << line << std::endl;
  
  std::getline(filein, line);
  auditor.auditStream<<line<<std::endl;
  auditor.mediaStream << "Number of candidates: " << line << std::endl;
  int numCandidates = std::stoi(line);

  //gets number of seats from the file
  std::getline(filein, line);
  auditor.auditStream<<line<<std::endl;
  auditor.mediaStream << "Number of seats: " << line << std::endl;
  int numSeats = std::stoi(line);

  //gets number of ballots from the file
  std::getline(filein, line);
  auditor.auditStream<<line<<std::endl;
  auditor.mediaStream << "Number of ballots: " << line << std::endl;
  int numBallots = std::stoi(line);

  //seperate the cadidates
  std::getline(filein, line);
  auditor.auditStream<<line<<std::endl;
  auditor.mediaStream << "Candidates and their party: " << line << std::endl;
  std::stringstream candidateStream(line);

  auditor.auditStream << "-------CANDIDATE ITERATION-------" <<std::endl;

  //For each candidate in the string
  int candidateNumber = 0;
  while(candidateStream.good()){
    std::string tempName;
    getline(candidateStream, tempName, ',');
    tempName.erase(std::remove(tempName.begin(), tempName.end(), '\r'), tempName.end());

    //create a ballot queue, store it in a global array
    BallotQueue* newCandidate = new BallotQueue();
    newCandidate->name = tempName;
    newCandidate->hasLost = false;
    newCandidate->hasWon = false;
    candidates.push_back(newCandidate);
    
    auditor.auditStream<<"Added candidate " << newCandidate->name << " with key " << candidateNumber <<std::endl;
    candidateNumber++;
  }

  auditor.auditStream << "-------BALLOT ITERATION-------" <<std::endl;

  //Step through ballots
  int ballotNumber = 0;
  while(std::getline(filein, line)){
    std::string tempCandidateVote;
    
    Ballot* ballot = new Ballot();

    auditor.auditStream << "---NEW BALLOT---" <<std::endl;
    auditor.auditStream << "Ballot: " << line << std::endl;
    
    //search for  i-th choice candidate
    for(int i=numCandidates; i>0; i--){
      std::stringstream ballotStream(line);
      int candidateIndex = 0;

      //step through ballot
      while(ballotStream.good()){
        getline(ballotStream, tempCandidateVote, ',');
        
        if(tempCandidateVote.length()!=0 && isdigit(tempCandidateVote[0]) && std::stoi(tempCandidateVote)==i){
          ballot->push(candidateIndex);
          auditor.auditStream << "Pushed candidate with index " << candidateIndex << " as " << i <<"th choice to ballot" << std::endl;
          break;
        }  
        candidateIndex++;
      }
    }

    ballot->key=ballotNumber;
    auditor.auditStream << "Pushed ballot to the ballot queue with key " << ballotNumber << std::endl;
    ballots.push(ballot);

    ballotNumber++;
  }

  
  if(shuffleOn){
      auditor.auditStream << "-------SHUFFLING-------" << std::endl;
      ballots.shuffle();
  }

  //now we're ready to get the winners!
  std::vector<BallotQueue*> winners;
  
  //calculate droop
  int droop = ((double)numBallots/(double)(numSeats+1))+1;

  auditor.auditStream << "-------INITIAL BALLOT ALLOCATION-------" << std::endl;
  auditor.auditStream << "The droop is " << droop << std::endl;


  //iterate through the ballots initially, allocating each of them.
  while(!ballots.isEmpty()){
    Ballot* tempBallot = ballots.pop();
    int votedCandidate;
    bool beenAllocated = false;
    auditor.auditStream << "---BALLOT POPPED---" <<std::endl;
    auditor.auditStream << "Popped ballot with key "<< tempBallot->key <<std::endl;
    //if the ballot has voted for less candidates than the invalid cutoff for candidates, remove it from the pool
    if(tempBallot->size()<=INVALID_CUTOFF){
      invalid.push(tempBallot);
      auditor.auditStream << "Ballot with key "<< tempBallot->key <<" is considered invalid, containing only " << tempBallot->size() << " votes." << std::endl;
      numBallots--;
      continue;
    }
    //if the ballot's first choice is a winner, go back to the top
    while(!tempBallot->isEmpty()){
      votedCandidate = tempBallot->pop();
      auditor.auditStream << "Checking voted candidate " << votedCandidate << std::endl;
      if(candidates.at(votedCandidate)->hasWon || candidates.at(votedCandidate)->getCount() >= droop){
        if(!candidates.at(votedCandidate)->hasWon){
          winners.push_back(candidates.at(votedCandidate));
          candidates.at(votedCandidate)->hasWon=true;
          auditor.auditStream << "!!!!!!! Candidate " << votedCandidate << " won!" << std::endl;
        }
        else{
          auditor.auditStream << "Candidate " << votedCandidate << " already won." <<std::endl;
        }
      }
      else{
        candidates.at(votedCandidate)->push(tempBallot);
        beenAllocated = true;
        auditor.auditStream << "Allocated ballot " << tempBallot->key << " to candidate " << votedCandidate << std::endl;
        break;
      }
    }
    if(!beenAllocated){
      delete tempBallot;
    }
  }

  //now we handle losers with a few special cases.
  auditor.auditStream << "-------WINNERS BEFORE RUNOFF BALLOT ALLOCATION-------" <<std::endl;
  for(int i=0; i<winners.size(); i++){
    auditor.auditStream << winners.at(i)->name <<std::endl;
  }

  auditor.auditStream << "-------RUNOFF BALLOT ALLOCATION-------" << std::endl;

  //while not all seat are filled
  while(winners.size()<numSeats){
    //if the number of candidates left is equal to the number of seats, give them all seats
    int remaining = 0;
    for(int i=0; i<candidates.size(); i++){
      if(!candidates.at(i)->hasLost && !candidates.at(i)->hasWon){
        remaining++;
      }
    }

    auditor.auditStream<<"Remaining candidates: "<<remaining <<", remaining seats: " << numSeats-winners.size() << std::endl;

    if(remaining<=numSeats-winners.size()){
      for(int i=0; i<candidates.size(); i++){
        if(!candidates.at(i)->hasLost && !candidates.at(i)->hasWon){
          winners.push_back(candidates.at(i));
        }
      }
      break;
    }

    //find loser
    int minVotes = 200000000;
    int minVotesIndex = 0;
    //std::cout << "Looking for loser" << std::endl;
    for(int i=0; i<candidates.size(); i++){
      //std::cout << "Candidate " << i << " has " << candidates.at(i)->getCount() << " votes." << std::endl;
      if((!candidates.at(i)->hasLost) && (!candidates.at(i)->hasWon) && candidates.at(i)->getCount()<minVotes){
        minVotesIndex = i;
        minVotes = candidates.at(i)->getCount();
      }
      else if(candidates.at(i)->getCount()==minVotes){
        if(c.flip()){
          minVotesIndex = i;
          minVotes = candidates.at(i)->getCount();
        }
      }
    }

    auditor.auditStream << "!!!!!!! Candidate " << minVotesIndex << " with " << minVotes << " votes has lost!" << std::endl;
    //break;

    candidates.at(minVotesIndex)->hasLost = true;

    while(!candidates.at(minVotesIndex)->isEmpty()){
      Ballot* tempBallot = candidates.at(minVotesIndex)->pop();
      int votedCandidate;
      bool beenAllocated = false;
      auditor.auditStream << "---BALLOT POPPED---" <<std::endl;
      auditor.auditStream << "Popped ballot with key "<< tempBallot->key <<std::endl;
      //if the ballot's first choice is a winner, go back to the top
      while(!tempBallot->isEmpty()){
        votedCandidate = tempBallot->pop();
        auditor.auditStream << "Checking voted candidate " << votedCandidate << std::endl;

        if(candidates.at(votedCandidate)->hasWon || candidates.at(votedCandidate)->hasLost || candidates.at(votedCandidate)->getCount() >= droop){
          if(!candidates.at(votedCandidate)->hasWon && !candidates.at(votedCandidate)->hasLost){
            winners.push_back(candidates.at(votedCandidate));
            candidates.at(votedCandidate)->hasWon=true;
            auditor.auditStream << "!!!!!!! Candidate " << votedCandidate << " won!" << std::endl;
          }
          else if(candidates.at(votedCandidate)->hasWon){
            auditor.auditStream << "Candidate " << votedCandidate << " already won." <<std::endl;
          }
          else if(candidates.at(votedCandidate)->hasLost){
            auditor.auditStream << "Candidate " << votedCandidate << " already lost." <<std::endl;
          }
        }
        else{
          candidates.at(votedCandidate)->push(tempBallot);
          beenAllocated = true;
          auditor.auditStream << "Allocated ballot " << tempBallot->key << " to candidate " << votedCandidate << std::endl;
          break;
        }
      }
      if(!beenAllocated){
        delete tempBallot;
      }
    }
  }

  auditor.auditStream << "-------!!! FINAL WINNERS !!!-------" <<std::endl;
  for(int i=0; i<winners.size(); i++){
    auditor.auditStream << winners.at(i)->name <<std::endl;
    auditor.mediaStream << "WINNERS: " << winners.at(i)->name <<std::endl;
  }
  
  //display
  const int nameWidth = 20;
  const int votesWidth = 7;
  const int percentageWidth = 11;

  std::cout << "-------!!! FINAL WINNERS !!!-------" <<std::endl;
  std::cout << std::left << std::setw(nameWidth) << std::setfill(' ') << "Candidate";
  std::cout << std::left << std::setw(votesWidth) << std::setfill(' ') << "Votes";
  std::cout << std::left << std::setw(percentageWidth) << std::setfill(' ') << "Percentage";
  std::cout<<std::endl;

  for(int i=0; i<winners.size(); i++){
    double percentage = ((double)winners.at(i)->getCount())/((double) numBallots)*100.0;
    std::cout << std::left << std::setw(nameWidth) << std::setfill(' ') << winners.at(i)->name;
    std::cout << std::left << std::setw(votesWidth) << std::setfill(' ') << winners.at(i)->getCount();
    std::cout << std::left << std::setw(percentageWidth) << std::setfill(' ') << std::setprecision(4) << percentage;
    std::cout<<std::endl;
  }

  auditor.print();
  auditor.printAudit();

  while(!candidates.empty()){
    delete candidates.back();
    candidates.pop_back();
  }
}