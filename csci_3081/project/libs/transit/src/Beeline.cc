#include "Beeline.h"

Beeline::Beeline(Vector3 pos_, Vector3 des_) {
    pos = pos_;
    des = des_;
}

bool Beeline::IsCompleted(){
    return (des - lastPos).Magnitude()<1.0;
}

void Beeline::Move(IEntity* entity, double dt){
    Vector3 currentPos = entity->GetPosition();
    Vector3 dir = (des - currentPos).Unit();
    float speed = entity->GetSpeed(); 
    currentPos = currentPos + dir * speed * dt;
    lastPos = currentPos;
    entity->SetPosition(currentPos);
    entity->SetDirection(dir);
}