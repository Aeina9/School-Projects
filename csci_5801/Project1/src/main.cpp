// main.cc
#include <iostream>
#include <string>

#include "oplDriver.h"
//#include "oplDriver.cc"

//#include "party.cc"

#include "irvDriver.h"

#include "candidate.h"
//#include "candidate.cc"

// #include "party.h"
// #include "ballot.h"


int main(int argc, char *argv[]){

  if (argc < 2) {
    std::cout << "Less number of arguments.\n";
    std::cout << "./build/final_program ../testing/<Name of the file>\n";
    fflush(stdout);
    exit(EXIT_FAILURE);
  }

  std::string filename = argv[1];
  
  std::ifstream filein(filename);
  std::string line;
  std::getline(filein, line);

  std::cout<<filename<<std::endl;
  //std::cout<<line.compare("OPL")<<std::endl;


  if(line.compare("OPL")==0 || line.compare("OPL")==1){
    std::cout<<"Running OPL"<<std::endl;
    OPLDriver opl;
    opl.run(filename);
  }
  else if(line.compare("IRV")==0 || line.compare("IRV")==1){
    std::cout<<"Running IRV"<<std::endl;
    IRVDriver irv;

    if (argc == 3 && std::string(argv[2]) == "-sh"){
      std::cout << "Shuffle is on" << std::endl;
      irv.shuffleOn = true;
    }

    irv.run(filename);
  }



  return 0;
}