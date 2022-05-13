/**
 * @file textResult.cpp
 * @brief Prints a media and audit file for an election
 * @author Amy Nguyen
 */

#include "textResult.h"

void TextResult::print() {
  fileout.open("./media.txt");
  if (mediaStream.good()) {
    fileout << mediaStream.str();
  }
  fileout.close();
}

void TextResult::printAudit() {
  fileout.open("./audit.txt");
  if (auditStream.good()) {
    fileout << auditStream.str();
  }
  fileout.close();
}
