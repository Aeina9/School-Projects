/**
 * @file oplDriver.cpp
 * @brief Runs an OPL election
 * @author Amy Nguyen
 * @author William Henning
 */

#include "oplDriver.h"

void OPLDriver::run(std::string filename) {
  // start parsing file
  std::ifstream filein(filename);

  // store header lines
  std::string line;
  std::getline(filein, line);
  std::string electionType = line;
  textResults.auditStream << "-------FILE HEADER INFORMATION-------" << std::endl;
  textResults.auditStream << electionType << std::endl;
  textResults.mediaStream << "Election type: " << electionType << std::endl;

  std::getline(filein, line);
  int numCandidates = std::stoi(line);
  textResults.auditStream << numCandidates << std::endl;
  textResults.mediaStream << "Number of candidates: " << numCandidates << std::endl;

  // gets number of seats from the file
  std::getline(filein, line);
  int numSeats = std::stoi(line);
  textResults.auditStream << numSeats << std::endl;
  textResults.mediaStream << "Number of seats: " << numSeats << std::endl;

  // gets number of ballots from the file
  std::getline(filein, line);
  int numBallots = std::stoi(line);

  textResults.auditStream << numBallots << std::endl;
  textResults.mediaStream << "Number of ballots: " << numBallots << std::endl;

  // if candidate count > seats, everyone should get a seat
  if (numCandidates < numSeats) {
    numSeats = numCandidates;
  }

  // removes the brackets that seperate the cadidates
  std::getline(filein, line);
  textResults.auditStream << "Candidates and their party: " << line << std::endl;
  textResults.mediaStream << "Candidates and their party: " << line << std::endl;
  textResults.auditStream << "-------CANDIDATE ITERATION-------" << std::endl;

  line.erase(std::remove(line.begin(), line.end(), '['), line.end());
  line.erase(std::remove(line.begin(), line.end(), ']'), line.end());
  std::stringstream partyStream(line);

  // Initialize parties
  // this variable stores the most recent party: if the stream reads a
  // new party, we create a new  party
  std::string lastParty = " ";
  while (partyStream.good()) {
    std::string tempName, tempParty;
    getline(partyStream, tempName, ',');
    getline(partyStream, tempParty, ',');
    tempParty.erase(std::remove(tempParty.begin(), tempParty.end(), '\r'), tempParty.end());

    Candidate* newCandidate = new Candidate();
    newCandidate->setName(tempName);

    // is it a new party? if yes, add it to the list then add the candidate
    // creating a new party if the current candidates party does not yet exist
    if (tempParty.compare(lastParty) != 0) {
      textResults.auditStream << "Created Party: " << tempParty << std::endl;

      Party newParty = Party();
      newParty.setName(tempParty);
      parties.push_back(newParty);
      lastParty = tempParty;
    }

    // adding candidate to their associated party if their party already exists
    if (parties.size() > 0) {
      textResults.auditStream << "Candidate " << newCandidate->getName()
                              << " added to party " << parties.back().getName() << std::endl;
      parties.back().addCandidate(newCandidate);
    }
    candidates.push_back(newCandidate);
  }

  textResults.auditStream << "-------BALLOT ITERATION-------" << std::endl;
  textResults.auditStream << "-------FIRST ALLOCATION-------" << std::endl;

  // Step through ballots
  while (std::getline(filein, line)) {
    std::stringstream ballotStream(line);
    std::string tempCandidateVote;
    // step through candidates in the ballots
    int candidateIndex = 0;
    while (ballotStream.good()) {
      getline(ballotStream, tempCandidateVote, ',');
      if (tempCandidateVote.compare("1") == 0) {
        candidates.at(candidateIndex)->addVote();
        textResults.auditStream << candidates.at(candidateIndex)->getName()
                                << " has recieved a vote and has "
                                << candidates.at(candidateIndex)->getNumVotes()
                                << " votes" << std::endl;
        break;
      }
      candidateIndex++;
    }
  }

  // getWinners();
  std::vector<Candidate*> winners;  // winners vector
  int quota = ceil((double)numBallots / (double)numSeats);
  textResults.auditStream << "Quota calculation: (ceil(Ballots/Seats))\nQuota: "
                          << quota << std::endl;

  // case of no ballots. Election is just all coin tosses
  if (quota == 0) {
    quota = 1;
  }
  int seatsFilled = 0;

  // iterate through parties
  for (int i = 0; i < parties.size(); i++) {
    // calculate votes
    parties.at(i).calculateTotalVotes();
    int partyVotes = parties.at(i).getTotalVotes();
    textResults.auditStream << "Party " << parties.at(i).getName() << 
                            " has " << partyVotes << std::endl;

    // calculate seats initially allocated
    int partySeats = partyVotes / quota;
    textResults.auditStream << "First seat allocation calculation: floor(partyVotes/quota)" << quota << std::endl;
    textResults.auditStream << "Number of first allocation seats for party "
                            << parties.at(i).getName() + ": " << partySeats << std::endl;
    // for each seat
    for (int j = 0; j < partySeats; j++) {
      if (parties.at(i).getNumCandidates() > 0) {
        // pop most popular candidate
        Candidate* winner = parties.at(i).getPopularCandidate();
        // push candidate to winners vector
        winners.push_back(winner);
        seatsFilled++;
      }
    }
  }

  for (int i = 0; i < winners.size(); i++) {
    textResults.auditStream << "If there is more than one most popular candidate, a coin was flipped" << std::endl;
    textResults.auditStream << "First seat allocation winner: " << winners.at(i)->getName() << std::endl;
  }

  textResults.auditStream << "-------SECOND ALLOCATION-------" << std::endl;
  // iterate through parties - second pass
  textResults.auditStream << "Remainder votes calculation: totalPartyVotes" << " % " << "quota" << std::endl;
  for (int i = 0; i < (numSeats - seatsFilled); i++) {
    int max = -1;
    int maxPartyIndex = 0;
    for (int j = 0; j < parties.size(); j++) {
      if (parties.at(j).getNumCandidates() > 0) {
        int remainingVotes = parties.at(j).getTotalVotes() % quota;
        textResults.auditStream << parties.at(j).getName() << " has "
                                << remainingVotes << " remaining votes and "
                                << parties.at(j).getNumCandidates()
                                << " remaining candidates" << std::endl;

        if (remainingVotes > max) {
          max = remainingVotes;
          maxPartyIndex = j;
          textResults.auditStream << "Current party set to take a second pass seat: " << parties.at(j).getName() << std::endl;
        } else if (remainingVotes == max) {  // coin flip
          textResults.auditStream << "Coin flip:" << std::endl;
          textResults.auditStream
              << "Current party " << parties.at(maxPartyIndex).getName()
              << ": HEADS(0)\nChallenging party " << parties.at(j).getName()
              << ": TAILS(1)" << std::endl;

          for (int k = 0; k < 100; ++k) {
            c.flip();
          }
          if (c.flip() == 1) {
            maxPartyIndex = j;
          }
          textResults.auditStream
              << parties.at(maxPartyIndex).getName()
              << " won, set to take a second allocation seat" << std::endl;
        }
      }
    }

    Candidate* winner = parties.at(maxPartyIndex).getPopularCandidate();
    textResults.auditStream << "If there is more than one most popular "
                               "candidate, a coin was flipped" << std::endl;
    // push candidate to winners
    winners.push_back(winner);
    textResults.auditStream << winner->getName() << " won a second allocation seat" << std::endl;
  }

  textResults.auditStream << "-------!!! FINAL WINNERS !!!-------" << std::endl;

  std::cout << "Seat quota: " << quota << std::endl;

  std::cout << "Winning Candidates: " << std::endl;
  for (int i = 0; i < winners.size(); i++) {
    textResults.auditStream << winners.at(i)->getName() << std::endl;
    textResults.mediaStream << "WINNERS: " << winners.at(i)->getName() << " " << std::endl;
    std::cout << winners.at(i)->getName() << std::endl;
  }
  std::cout << std::endl;

  // display
  const int nameWidth = 20;
  const int votesWidth = 16;
  const int percentageWidth = 11;
  const int seatsWidth = 27;
  std::cout << std::left << std::setw(nameWidth) << std::setfill(' ') << "Party";
  std::cout << std::left << std::setw(votesWidth) << std::setfill(' ') << "Votes";
  std::cout << std::left << std::setw(seatsWidth) << std::setfill(' ') << "First Allocation of Seats";
  std::cout << std::left << std::setw(votesWidth) << std::setfill(' ') << "Remaining Votes";
  std::cout << std::left << std::setw(seatsWidth) << std::setfill(' ') << "Second Allocation of Seats";
  std::cout << std::left << std::setw(seatsWidth) << std::setfill(' ') << "Final Seat Total";
  std::cout << std::left << std::setw(percentageWidth) << std::setfill(' ') << "(%) of Votes/(%) of Seats";
  std::cout << std::endl;

  for (int i = 0; i < parties.size(); i++) {
    double percentageOfVote = ((double)parties.at(i).getTotalVotes()) / ((double)numBallots) * 100.0;
    double percentageOfSeats = ((double)parties.at(i).finalSeats) / ((double)numSeats) * 100.0;
    // divide by 0 "error"
    if (numBallots == 0) { percentageOfVote = 0; }
    std::cout << std::left << std::setw(nameWidth) << std::setfill(' ') << parties.at(i).getName();
    std::cout << std::left << std::setw(votesWidth) << std::setfill(' ') << parties.at(i).getTotalVotes();
    std::cout << std::left << std::setw(seatsWidth) << std::setfill(' ') << parties.at(i).getTotalVotes() / quota;
    std::cout << std::left << std::setw(votesWidth) << std::setfill(' ') << parties.at(i).getTotalVotes() % quota;

    std::cout << std::left << std::setw(seatsWidth) << std::setfill(' ') 
              << parties.at(i).finalSeats - parties.at(i).getTotalVotes() / quota;

    std::cout << std::left << std::setw(seatsWidth) << std::setfill(' ') << parties.at(i).finalSeats;

    std::cout << std::left << std::setw(percentageWidth) << std::setfill(' ') 
              << std::setprecision(4) << percentageOfVote << " / " << percentageOfSeats;
              
    std::cout << std::endl;
  }

  textResults.print();
  textResults.printAudit();

  while (!candidates.empty()) {
    Candidate* tempcandidate = candidates.back();
    candidates.pop_back();
    delete tempcandidate;
  }
}