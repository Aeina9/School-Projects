#ifndef OPLDRIVER_H
#define OPLDRIVER_H


#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <string>
#include <algorithm>
#include <cmath>
#include<iomanip>

// #include "electionDriver.h"
#include "ballot.h"
#include "party.h"
#include "coin.h"
#include "textResult.h"

/**
 * @brief A class for running the OPL Election.
 */
class OPLDriver{
  public:

    /**
     * @brief OPLDriver has a coin object
     */
    Coin c;


    /**
     * @brief OPLDriver has a TextResults object
     */
    TextResult textResults;

    /**
     * @brief Default constructor
     */
    OPLDriver(){}

    /**
     * @brief Default destructor
     */
    ~OPLDriver(){}

    /**
     * @brief The run function is used to run the Election.
     * 
     * @param filename the csv file the function will run
     */
    void run(std::string filename);
    
  private:
    std::vector<Party> parties;
    std::vector<Candidate*> candidates;
    //parser possible
};

#endif