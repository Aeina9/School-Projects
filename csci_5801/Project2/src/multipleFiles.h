/**
 * @file multipleFiles.h
 * @brief A class that combines multiple election files for an election
 * @author Amy Nguyen
 */

#ifndef MULTIPLE_FILES_H
#define MULTIPLE_FILES_H

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

/**
 * @brief A class that combines multiple election files for an election
 */
class MultipleFiles {
 public:
  /**
   * @brief data from multiple files will being combined into one file where the
   * will run
   */
  std::ofstream combinedFile;

  /**
   * @brief keeps a stream of all ballots in case of multiple files
   */
  std::stringstream ballotstream;

  /**
   * @brief keeps total number of ballots for the election, initialized to 0
   */
  int ballotCount = 0;

  /**
   * @brief function that goes through multiple files and combines data into
   * "combinedFile.csv" for IRV and OPL
   *
   * @param filename name of current file as a string
   * @param filenum current file number out of all files as an int
   * @param electionType election type indicator
   */
  void combineFiles(std::string filename, int filenum, std::string electionType);
};

#endif
