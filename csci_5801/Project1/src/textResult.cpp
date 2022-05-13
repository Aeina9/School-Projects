#include "textResult.h"


// things to print:
// 0 - Type of election
// 1 - number of candidates
// 2 - number of seats
// 3 - Number of Ballots
// 4 - Candidates and their party
// 5 - Winners and their number of votes

void TextResult::print(){
  fileout.open ("./media.txt");
  if(mediaStream.good()){
    fileout << mediaStream.str();
  }
  fileout.close();
}

void TextResult::printAudit(){
  fileout.open ("./audit.txt");
  if(auditStream.good()){
    fileout << auditStream.str();
  }
  fileout.close();
}
