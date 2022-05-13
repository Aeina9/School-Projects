#include "CelebrationDecorator.h"

bool CelebrationDecorator::IsCompleted(){
    return strategy->IsCompleted();
}

void CelebrationDecorator::Move(IEntity* entity, double dt){
    strategy->Move(entity, dt);
}
