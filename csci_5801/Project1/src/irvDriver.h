#ifndef IRVDRIVER_H
#define IRVDRIVER_H

#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <iomanip>

// #include "electionDriver.h"
#include "ballotQueue.h"
#include "coin.h"
#include "textResult.h"

/**
 * @brief A class for running the IRV Election.
 */
class IRVDriver{
  public:
  
    /**
     * @brief Default constructor
     */
    IRVDriver(){}

    /**
     * @brief Destructor
     */
    ~IRVDriver(){}

    /**
     * @brief The option to turn on and off shuffle for testing purposes
     * 
     * @return true for shuffle is on and false for suffle is off
     */
    bool shuffleOn;

    /**
     * @brief The run function is used to run the Election.
     * 
     * @param filename the csv file the function will run
     */
     void run(std::string filename);

  private:
    Coin c;
    BallotQueue ballots;
    BallotQueue invalid;
    std::vector<BallotQueue*> candidates;
    TextResult auditor;
    //IRVParser parser; //IRVDriver?
};

#endif