/**
 * @file multipleFiles.cpp
 *
 * @brief
 * Goes through all given files and combines them into "combinedFile.csv"
 * with update ballot count and ballots. The appropriate election will then
 * run with "combinedFile.csv"
 *
 * @author Amy Nguyen
 */

#include "multipleFiles.h"

void MultipleFiles::combineFiles(std::string filename, int filenum, std::string electionType) {
  // allstrings will continuously update the header info
  std::stringstream allstrings;
  std::ifstream filein(filename);
  std::string line;
  int headerLines;

  // Account for OPL/IRV or PO headerLines
  if ((electionType == "OPL") || (electionType == "IRV")) {
    headerLines = 5;
  } else if (electionType == "PO") {
    headerLines = 4;
  }

  // store header lines
  // take initial file's header info, will run if only 1 input file
  if (filenum == 0) {
    for (int i = 0; i < headerLines; ++i) {
      if (i != 3) {
        std::getline(filein, line);
        allstrings << line << std::endl;
      // ballot count
      } else {
        std::getline(filein, line);
        ballotCount = stoi(line);
        allstrings << ballotCount << std::endl;
      }
    }
  } else {
    // check rest of file header info excluding ballot count.
    // ../testing/combinedFile.csv should exist at this point
    std::ifstream currFile("../testing/combinedFile.csv");
    std::string line2;

    // go through header info
    for (int i = 0; i < headerLines; ++i) {
      if (i != 3) {
        std::getline(filein, line);
        std::getline(currFile, line2);
        if (line2 == line) {
          allstrings << line << std::endl;
        } else {
          std::cerr << "Invalid. Please check header information for each file." << std::endl;
          exit(EXIT_FAILURE);
        }

      } else {
        // ballot count
        std::getline(filein, line);
        std::getline(currFile, line2);
        ballotCount += std::stoi(line);
        allstrings << ballotCount << std::endl;
      }
    }
  }

  // store all ballots
  while (std::getline(filein, line)) {
    ballotstream << line << std::endl;
  }

  combinedFile.open("../testing/combinedFile.csv");
  if (combinedFile.good()) {
    combinedFile << allstrings.str();
    combinedFile << ballotstream.str();
  }
  combinedFile.close();
}
