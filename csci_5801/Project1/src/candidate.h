#ifndef CANDIDATE_H
#define CANDIDATE_H

#include <iostream>
#include <string>

/**
 * @brief A class that gets the relevant information of the candidates 
 */
class Candidate {
  public:

    /**
     * @brief Default constructor with 0 votes and name "None"
     */
    Candidate();

    /**
     * @brief Gets the name of the candidate 
     * 
     * @return the name of a candidate
     */
    std::string getName();  

    /**
     * @brief Gets the number of votes that are for the given candidate
     * 
     * @return the number of votes for the candidate 
     */
    int getNumVotes();

    /**
     * @brief Sets the Name of the candidate
     * 
     * @param name name of the candidate
     */
    void setName(std::string name);

    /**
     * @brief adds a vote to the candidate
     * 
     */
    void addVote();

  private:
    std::string name;
    int numVotes;
};

#endif