#ifndef ELECTIONDRIVER_H
#define ELECTIONDRIVER_H

#include <vector>

#include "candidate.h"

/**
* @brief Abstract class handling all election types
*/
class ElectionDriver {
  public:

    /**
    * @brief Pure virtual, all elections must have a "run" function.
    */
    virtual void run(std::string filename) = 0;

    /**
    * @brief Default destructor
    */
    virtual ~ElectionDriver(){}
    // virtual std::vector<Candidate> getWinners();
};

#endif