/**
 * @file electionDriver.h
 * @brief An abstract class handling all election types
 * @author Amy Nguyen
 */

#ifndef ELECTIONDRIVER_H
#define ELECTIONDRIVER_H

#include <algorithm>
#include <cmath>
#include <fstream>
#include <iostream>
#include <sstream>

#include "coin.h"
#include "textResult.h"

/**
 * @brief An abstract class handling all election types
 */
class ElectionDriver {
 public:
  /**
   * @brief Every election has a coin object for ties
   */
  Coin c;

  /**
   * @brief Every election has a TextResult object to audit
   */
  TextResult textResults;

  /**
   * @brief Pure virtual, all elections must have a "run" function.
   * @param filename name and path of .csv election file
   */
  virtual void run(std::string filename) = 0;

  /**
   * @brief Destructor
   */
  virtual ~ElectionDriver() {}
};

#endif
