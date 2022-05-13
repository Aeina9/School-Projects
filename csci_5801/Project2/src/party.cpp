/**
 * @file party.cpp
 * @brief Implementation of party functions
 * @author Amy Nguyen
 */

#include "party.h"

// default contructor
Party::Party() {
  name = "None";
  totalVotes = 0;
}

int Party::getTotalVotes() { return totalVotes; }

std::string Party::getName() { return name; }

int Party::getNumCandidates() { return candidates.size(); }

void Party::setName(std::string name) { this->name = name; }

// calculating total votes for a party
void Party::calculateTotalVotes() {
  for (int i = 0; i < candidates.size(); ++i) {
    totalVotes = totalVotes + candidates[i]->getNumVotes();
  }
}

// add candidate to their associated party
void Party::addCandidate(Candidate* candidate) {
  candidates.push_back(candidate);
}

Candidate* Party::getPopularCandidate() {
  int max = -1;
  int index;
  Candidate* popularCandidate;
  if (!candidates.empty()) {
    // printing each the number of each candidates votes
    for (int i = 0; i < candidates.size(); ++i) {
      // updating the popular candidate if it has changed
      if (candidates[i]->getNumVotes() > max) {
        max = candidates[i]->getNumVotes();
        popularCandidate = candidates[i];
        index = i;
        // updating the popular candidate if it has changed
      } else if (candidates[i]->getNumVotes() == max) {
        // flip multiple times before deciding coin
        for (int j = 0; j < 100; ++j) {
          c.flip();
        }
        // 0 is heads and the existing popular candidate, tails in the next
        // candidate with same vote count
        if (c.flip() == 1) {
          popularCandidate = candidates[i];
          index = i;
        }
      }
    }
    candidates.erase(candidates.begin() + index);
    finalSeats++;
    return popularCandidate;
  } else {
    std::cout << "No candidates in party" << std::endl;
    return nullptr;
  }
}
