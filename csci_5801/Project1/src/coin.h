#ifndef COIN_H
#define COIN_H

#include <iostream>
#include <string>
#include <ctime>

/**
 * @brief A class that uses a coin flip to determine the winner of a tie
 */
class Coin {
  public:

    /**
     * @brief constructor instantiates random number generation using srand((unsigned)time(NULL))
     */
    Coin(); 

    /**
     * @brief a coin is randomly flipped to determine the winner of a tie breaker
     * 
     * @return 0 for heads and 1 for tails
     */
    int flip();
};

#endif
