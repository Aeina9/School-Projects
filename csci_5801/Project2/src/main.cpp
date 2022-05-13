/**
 * @file main.cpp
 *
 * @brief
 * Main function in that takes in command line inputs
 * and runs the according election with the files given
 *
 * @author Amy Nguyen
 */

#include <iostream>
#include <string>

#include "irvDriver.h"
#include "multipleFiles.h"
#include "oplDriver.h"
#include "poDriver.h"

int main(int argc, char *argv[]) {
  if (argc < 2) {
    std::cout << "Less number of arguments.\n";
    std::cout << "./build/final_program ../testing/<Name of the file>\n";
    fflush(stdout);
    exit(EXIT_FAILURE);
  }

  // 1 file created for multiple files
  std::string allFileName = "../testing/combinedFile.csv";
  std::string currentElectionType;

  OPLDriver opl;
  IRVDriver irv;
  PODriver po;
  MultipleFiles mfiles;

  for (int i = 0; i < argc - 1; ++i) {
    std::string filename = argv[i + 1];

    std::ifstream filein(filename);
    std::string line;
    std::getline(filein, line);

    std::cout << filename << std::endl;

    // if multiple files, run multiple
    if (line.compare("OPL") == 0) {
      currentElectionType = "OPL";
      mfiles.combineFiles(filename, i, currentElectionType);
    } else if (line.compare("IRV") == 0) {
      currentElectionType = "IRV";

      // irv shuffle
      if (std::string(argv[argc - 1]) == "-sh") {
        std::cout << "Shuffle is on" << std::endl;
        irv.shuffleOn = true;
      }

      mfiles.combineFiles(filename, i, currentElectionType);
    } else if (line.compare("PO") == 0 || line.compare("PO\r") == 0) {
      currentElectionType = "PO";
      mfiles.combineFiles(filename, i, currentElectionType);
    }
  }

  // run the generated file
  std::cout << "Running " << currentElectionType << std::endl;
  if (currentElectionType == "OPL") {
    opl.run(allFileName);
  } else if (currentElectionType == "IRV") {
    irv.run(allFileName);
  } else if (currentElectionType == "PO") {
    po.run(allFileName);
  }

  return 0;
}
