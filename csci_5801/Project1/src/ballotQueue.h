#ifndef Ballot_Queue_H
#define Ballot_Queue_H

#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <ctime>
#include "ballot.h"

/**
 * @brief A class that holds all of the ballots
 */
class BallotQueue{
    
  public:
    /**
     * @brief Default constructor
     */
    BallotQueue(){}

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

    ~BallotQueue();

    std::string name;
    bool hasWon;
    bool hasLost;
    
  private:
    std::vector<Ballot*> ballots;
    int ballotCount;
    
};

#endif
