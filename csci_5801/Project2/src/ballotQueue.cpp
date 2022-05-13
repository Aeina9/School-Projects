/**
 * @file ballotQueue.cpp
 * @brief Implementation of ballotQueue functions
 * @author William Henning
 */

#include "ballotQueue.h"

int BallotQueue::getCount() { return ballots.size(); }

bool BallotQueue::isEmpty() { return ballots.empty(); }

Ballot* BallotQueue::pop() {
  Ballot* tempBallot = ballots.back();
  ballots.pop_back();

  return tempBallot;
}

Ballot* BallotQueue::at(int i) { return ballots.at(i); }

void BallotQueue::push(Ballot* ballotToPush) {
  ballots.push_back(ballotToPush);
  ballotCount++;
}

void BallotQueue::shuffle() {
  srand((unsigned)time(NULL));
  std::default_random_engine e(rand());
  std::shuffle(std::begin(ballots), std::end(ballots), e);
}

BallotQueue::~BallotQueue() {
  while (!ballots.empty()) {
    Ballot* tempBallot = ballots.back();
    ballots.pop_back();
    delete tempBallot;
  }
}
