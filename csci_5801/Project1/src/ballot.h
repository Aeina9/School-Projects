#ifndef _BALLOT_H
#define _BALLOT_H

#include <iostream>
#include <vector>

/**
 * @brief A class that holds each vote
 * 
 */
class Ballot {

  public:
  /**
   * @brief Default constructor
   */
  Ballot(){}

  /**
   * @brief key ballot
   */
  int key;
  
  /**
   * @brief Adds a new vote onto the stack
   * 
   * @param candidateVote index of the candidate that is represented in the CSV
   */
  void push(int candidateVote);

  /**
   * @brief Returns the first vote off the stack
   * 
   * @return the first vote on the stack 
   */
  int pop();

  /**
   * @brief Returns if there are or are not any more votes to process in the stack to determine if the IRV Driver can delete the ballot
   * 
   * @return true if there are no more votes to process in the stack
   * @return false if there are more votes to process in the stack
   */
  bool isEmpty();


  /**
   * @brief Returns the number of candidates remaining in the ballot
   * 
   * @return the number of candidates remaining in the ballot
   */
  int size();

  private:
    int current;
    std::vector<int> candidateVotes;
};

#endif