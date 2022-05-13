#include "coin.h"

Coin::Coin(){
  srand((unsigned)time(NULL)); //pseudo-random number is generated
  for(int i=0; i<10000; i++){
    rand();
  }
}

int Coin::flip(){
  int flip = rand()%2;
  return flip; // coin will be come out 0 or 1
}
