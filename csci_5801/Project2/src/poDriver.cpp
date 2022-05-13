/**
 * @file poDriver.cpp
 * @brief Runs a PO election
 * @author William Henning
 */

#include "poDriver.h"

/**
 * @brief struct containing info of PO candidates
 */
struct POCandidate {
  std::string name;
  std::string party;
  int votes;
  bool won;
};

void PODriver::run(std::string filename) {
  int numSeats = 1;
  std::vector<POCandidate> candidates;

  std::cout << "Running PO" << std::endl;
  // start parsing file
  std::ifstream filein(filename);

  // store header lines
  std::string line;
  std::getline(filein, line);
  // gets election type from first line in file
  std::string electionType = line;
  textResults.auditStream << "-------FILE HEADER INFORMATION-------" << std::endl;
  textResults.auditStream << electionType << std::endl;
  textResults.mediaStream << "Election type: " << electionType << std::endl;

  // gets number of candidates
  std::getline(filein, line);
  int numCandidates = std::stoi(line);
  textResults.auditStream << numCandidates << std::endl;
  textResults.mediaStream << "Number of candidates: " << numCandidates << std::endl;

  // removes the brackets that seperate the cadidates
  std::getline(filein, line);
  textResults.auditStream << "Candidates and their party: " << line << std::endl;
  textResults.mediaStream << "Candidates and their party: " << line << std::endl;
  textResults.auditStream << "-------CANDIDATE ITERATION-------" << std::endl;

  line.erase(std::remove(line.begin(), line.end(), '['), line.end());
  line.erase(std::remove(line.begin(), line.end(), ']'), line.end());
  std::stringstream partyStream(line);

  // Initialize parties
  while (partyStream.good()) {
    POCandidate tempcandidate;
    std::string tempName, tempParty;
    getline(partyStream, tempName, ',');
    getline(partyStream, tempParty, ',');
    tempName.erase(std::remove(tempName.begin(),tempName.end(),' '),tempName.end());

    // adding candidate to their associated party if their party already exists
    tempcandidate.name = tempName;
    tempcandidate.party = tempParty;
    tempcandidate.votes = 0;
    tempcandidate.won = false;
    candidates.push_back(tempcandidate);
    textResults.auditStream << "Candidate " << tempName << " pushed to candidates." << std::endl;
  }

  // gets number of ballots from the file
  std::getline(filein, line);
  int numBallots = std::stoi(line);

  textResults.auditStream << numBallots << std::endl;
  textResults.mediaStream << "Number of ballots: " << numBallots << std::endl;

  // Step through ballots
  int ballotNumber = 0;
  while (std::getline(filein, line)) {
    std::string tempCandidateVote;

    textResults.auditStream << "---NEW BALLOT---" << std::endl;
    textResults.auditStream << "Ballot " << ballotNumber << ": " << line << std::endl;

    std::stringstream ballotStream(line);

    // step through ballot
    int candidateIndex = 0;
    while (ballotStream.good()) {
      getline(ballotStream, tempCandidateVote, ',');
      tempCandidateVote.erase(std::remove(tempCandidateVote.begin(), tempCandidateVote.end(), '\r'), tempCandidateVote.end());
      tempCandidateVote.erase(std::remove(tempCandidateVote.begin(), tempCandidateVote.end(), '\n'), tempCandidateVote.end());
      tempCandidateVote.erase(std::remove(tempCandidateVote.begin(), tempCandidateVote.end(), ' '), tempCandidateVote.end());
      if (tempCandidateVote.compare("1") == 0) {
        candidates.at(candidateIndex).votes++;
        textResults.auditStream << "Ballot " << ballotNumber
                                << " attributed to candidate at index "
                                << candidateIndex << std::endl;
        break;
      }
      candidateIndex++;
    }
    ballotNumber++;
  }

  // find winners
  std::vector<POCandidate> winners;
  for (int seat = 0; seat < numSeats; seat++) {
    int maximumVote = -1;
    int maximumVoteIndex = 0;
    for (int candidateindex = 0; candidateindex < numCandidates; candidateindex++) {
      if (!candidates.at(candidateindex).won) {
        if (candidates.at(candidateindex).votes > maximumVote) {
          maximumVote = candidates.at(candidateindex).votes;
          maximumVoteIndex = candidateindex;
        } else if (candidates.at(candidateindex).votes == maximumVote) {
          // if candidates tie then coin flip
          textResults.auditStream << "Coin flip:" << std::endl;
          textResults.auditStream
              << "Current candidate " << candidates.at(candidateindex).name << ": HEADS(0)\nChallenging candidate "
              << candidates.at(maximumVoteIndex).name << ": " << "TAILS(1)" << std::endl;
          if (c.flip() == 1) {  // coin flip determines winner
            maximumVote = candidates.at(candidateindex).votes;
            maximumVoteIndex = candidateindex;
          }
          textResults.auditStream << candidates.at(maximumVoteIndex).name << " won the flip" << std::endl;
        }
      }
    }
    winners.push_back(candidates.at(maximumVoteIndex));
  }

  // display
  const int nameWidth = 20;
  const int votesWidth = 7;
  const int percentageWidth = 11;

  // displays candidates results
  std::cout << "------- CANDIDATE RESULTS -------" << std::endl;
  std::cout << std::left << std::setw(nameWidth) << std::setfill(' ') << "Candidate";
  std::cout << std::left << std::setw(votesWidth) << std::setfill(' ') << "Votes";
  std::cout << std::left << std::setw(percentageWidth) << std::setfill(' ') << "Percentage";
  std::cout << std::endl;

  for (int i = 0; i < candidates.size(); i++) {
    double percentage = ((double)candidates.at(i).votes) / ((double)numBallots) * 100.0;
    // divide by 0 "error"
    if (numBallots == 0) { percentage = 0; }
    std::string candidateString = candidates.at(i).name + ", " + candidates.at(i).party;
    std::cout << std::left << std::setw(nameWidth) << std::setfill(' ') << candidateString;
    std::cout << std::left << std::setw(votesWidth) << std::setfill(' ') << candidates.at(i).votes;
    std::cout << std::left << std::setw(percentageWidth) << std::setfill(' ') << std::setprecision(4) << percentage;
    std::cout << std::endl;
  }

  // displays final winners
  std::cout << "-------!!! FINAL WINNER(S) !!!-------" << std::endl;
  std::cout << std::left << std::setw(nameWidth) << std::setfill(' ') << "Candidate";
  std::cout << std::left << std::setw(votesWidth) << std::setfill(' ') << "Votes";
  std::cout << std::left << std::setw(percentageWidth) << std::setfill(' ') << "Percentage";
  std::cout << std::endl;

  for (int i = 0; i < winners.size(); i++) {
    double percentage = ((double)winners.at(i).votes) / ((double)numBallots) * 100.0;
    std::string candidateString = winners.at(i).name + ", " + winners.at(i).party;
    std::cout << std::left << std::setw(nameWidth) << std::setfill(' ') << candidateString;
    std::cout << std::left << std::setw(votesWidth) << std::setfill(' ') << winners.at(i).votes;
    std::cout << std::left << std::setw(percentageWidth) << std::setfill(' ') << std::setprecision(4) << percentage;
    std::cout << std::endl;
  }

  textResults.auditStream << "-------!!! FINAL WINNER(S) !!!-------" << std::endl;
  for (int i = 0; i < winners.size(); i++) {
    textResults.auditStream << winners.at(i).name << ", " << winners.at(i).party << std::endl;
    textResults.mediaStream << "WINNERS: " << winners.at(i).name << ", " << winners.at(i).party << std::endl;
  }

  textResults.print();
  textResults.printAudit();
}