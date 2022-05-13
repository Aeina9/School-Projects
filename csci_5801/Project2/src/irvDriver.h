/**
 * @file irvDriver.h
 * @brief A class for running the IRV Election
 * @author William Henning
 */

#ifndef IRVDRIVER_H
#define IRVDRIVER_H

#include <ctime>
#include <iomanip>
#include <vector>

#include "ballotQueue.h"
#include "electionDriver.h"
#include "textResult.h"

/**
 * @brief A class for running the IRV Election
 * @author William Henning
 */
class IRVDriver : public ElectionDriver {
 public:
  /**
   * @brief Default constructor
   */
  IRVDriver() {}

  /**
   * @brief Destructor
   */
  ~IRVDriver() {}

  /**
   * @brief The option to turn on and off shuffle for testing purposes
   *
   * @return true for shuffle is on and false for shuffle is off. Default off.
   */
  bool shuffleOn = false;

  /**
   * @brief The run function is used to run the Election.
   *
   * @param filename the csv file the function will run
   */
  void run(std::string filename);

 private:
  BallotQueue ballots;
  BallotQueue invalid;
  std::vector<BallotQueue*> candidates;

  std::ofstream invalidfile;
  std::stringstream invalidBallots;
};

#endif
