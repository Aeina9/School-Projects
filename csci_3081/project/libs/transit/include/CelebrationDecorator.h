#ifndef CELEBRATION_DECORATOR_H_
#define CELEBRATION_DECORATOR_H_

#include <vector>
#include "IStrategy.h"

class CelebrationDecorator: public IStrategy {
    public:
        CelebrationDecorator(IStrategy *strategy_) {strategy = strategy_; spinTime = 0;}
        void Move(IEntity* entity, double dt);
        bool IsCompleted();
    protected:
        IStrategy *strategy;
        float spinTime;
}; //close class 

#endif // CELEBRATION_DECORATOR_H_