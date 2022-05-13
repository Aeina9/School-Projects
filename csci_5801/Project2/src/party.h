/**
 * @file party.h
 * @brief A class which organizes the candidates into their associated party.
 * @author Amy Nguyen
 */

#ifndef PARTY_H
#define PARTY_H

#include <iostream>
#include <string>
#include <vector>

#include "candidate.h"
#include "coin.h"

/**
 * @brief A class which organizes the candidates into their associated party.
 */
class Party {
 public:
  /**
   * @brief Default constructor with 0 votes and name "None"
   */
  Party();

  /**
   * @brief Party has a coin object
   */
  Coin c;

  /**
   * @brief Gets the Total Votes for the party
   *
   * @return the total number of votes
   */
  int getTotalVotes();

  /**
   * @brief Gets the name of the party
   *
   * @return name of the party
   */
  std::string getName();

  /**
   * @brief Gets the candidate with the most votes
   *
   * @return the candidate with the most votes
   */
  Candidate* getPopularCandidate();

  /**
   * @brief Gets the number of candidates associated with each party
   *
   * @return the number of candiates in each party
   */
  int getNumCandidates();

  /**
   * @brief Sets the name of a party
   *
   * @param name party's name
   */
  void setName(std::string name);

  /**
   * @brief calculate the total votes for the party
   */
  void calculateTotalVotes();

  /**
   * @brief Adding a candidate to the party
   *
   * @param candidate the candidate that will be added to the party
   */
  void addCandidate(Candidate* candidate);

  /**
   * @brief final seats or display
   */
  int finalSeats = 0;

 private:
  std::string name;
  int totalVotes;
  std::vector<Candidate*> candidates;
};

#endif
