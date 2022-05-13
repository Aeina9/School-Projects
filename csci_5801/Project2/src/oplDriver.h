/**
 * @file oplDriver.h
 * @brief A class for running the OPL Election
 * @author Amy Nguyen
 * @author William Henning
 */

#ifndef OPLDRIVER_H
#define OPLDRIVER_H

#include <iomanip>
#include <map>
#include <string>

#include "ballot.h"
#include "electionDriver.h"
#include "party.h"
#include "textResult.h"

/**
 * @brief A class for running the OPL Election
 */
class OPLDriver : public ElectionDriver {
 public:
  /**
   * @brief Default constructor
   */
  OPLDriver() {}

  /**
   * @brief Default destructor
   */
  ~OPLDriver() {}

  /**
   * @brief The run function is used to run the Election.
   *
   * @param filename the csv file the function will run
   */
  void run(std::string filename);

 private:
  std::vector<Party> parties;
  std::vector<Candidate*> candidates;
};

#endif
