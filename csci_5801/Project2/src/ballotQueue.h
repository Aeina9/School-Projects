/**
 * @file ballotQueue.h
 * @brief A class that holds all of the ballots
 * @author William Henning
 */

#ifndef Ballot_Queue_H
#define Ballot_Queue_H

#include <algorithm>
#include <ctime>
#include <iostream>
#include <random>
#include <vector>

#include "ballot.h"

/**
 * @brief A class that holds all of the ballots
 */
class BallotQueue {
 public:
  /**
   * @brief Default constructor
   */
  BallotQueue() {}

  /**
   * @brief Destructor
   */
  ~BallotQueue();

  /**
   * @brief Gets the number of ballots that have been counted
   *
   * @return number of ballots counted
   */
  int getCount();

  /**
   * @brief Adds the ballot onto the ballot vector
   *
   * @param ballotToPush the ballot that is being pushed onto the ballot vector
   */
  void push(Ballot* ballotToPush);

  /**
   * @brief Removes the ballot off the ballot vector
   *
   * @return the ballot that was removed from the ballot vector
   */
  Ballot* pop();

  /**
   * @brief Shuffles the ballot vector
   *
   */
  void shuffle();

  /**
   * @brief A function for determining if the queue is empty
   *
   * @return true if empty, false if ballots remain in vector queue
   *
   */
  bool isEmpty();

  /**
   * @brief Get the ballot at i
   * @param i position of ballot
   * @return a pointer to the ballot at position i
   *
   */
  Ballot* at(int i);

  /**
   * @brief name of ballot
   */
  std::string name;

  /**
   * @brief determine if candidate has won
   */
  bool hasWon;

  /**
   * @brief determine if candidate has lost
   */
  bool hasLost;

 private:
  std::vector<Ballot*> ballots;
  int ballotCount;
};

#endif
