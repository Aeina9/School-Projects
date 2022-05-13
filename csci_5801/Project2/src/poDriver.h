/**
 * @file poDriver.h
 * @brief A class for running the PO Election
 * @author William Henning
 */

#ifndef PO_DRIVER_H
#define PO_DRIVER_H

#include <iomanip>
#include <map>
#include <string>

#include "candidate.h"
#include "electionDriver.h"
#include "party.h"
#include "textResult.h"

/**
 * @brief A class for running the PO Election
 */
class PODriver : public ElectionDriver {
 public:
  /**
   * @brief Default constructor
   */
  PODriver() {}

  /**
   * @brief Default destructor
   */
  ~PODriver() {}

  /**
   * @brief The run function is used to run the Election.
   *
   * @param filename the csv file the function will run
   */
  void run(std::string filename);
};

#endif
