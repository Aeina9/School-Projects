#include "candidate.h"

Candidate::Candidate(){
  name = "None";
  numVotes = 0;
};

std::string Candidate::getName(){return name;}

int Candidate::getNumVotes(){return numVotes;}

void Candidate::setName(std::string name){
  this->name = name;
}

void Candidate::addVote(){
  ++numVotes;
}