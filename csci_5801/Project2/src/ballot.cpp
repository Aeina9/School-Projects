/**
 * @file ballot.cpp
 * @brief Implementation of ballot functions
 * @author William Henning
 */

#include "ballot.h"

void Ballot::push(int candidateVote) {
  candidateVotes.push_back(candidateVote);
}

int Ballot::pop() {
  int candidateIndex = candidateVotes.back();
  candidateVotes.pop_back();
  return candidateIndex;
}

bool Ballot::isEmpty() {
  return candidateVotes.empty();
}

int Ballot::size() {
  return candidateVotes.size();
}
