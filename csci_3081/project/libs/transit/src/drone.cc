#define _USE_MATH_DEFINES
#include "drone.h"
#include "Beeline.h"
#include "AstarStrategy.h"
#include "DijkstraStrategy.h"
#include "DfsStrategy.h"
#include "SpinDecorator.h"
#include <cmath>
#include <limits>

Drone::Drone(JsonObject obj) : details(obj) { 
    JsonArray pos(obj["position"]);
    position = {pos[0], pos[1], pos[2]};

    JsonArray dir(obj["direction"]);
    direction = {dir[0], dir[1], dir[2]};

    speed = obj["speed"];

    available = true;
}

Drone::~Drone() {
    // Delete dynamically allocated variables
}

void Drone::GetNearestEntity(std::vector<IEntity*> scheduler) {
    // IEntity* nearestEntity_ = nullptr;
    float minDis = std::numeric_limits<float>::max();
    for(auto entity : scheduler){
        if(entity->GetAvailability()){
            float disToEntity = this->position.Distance(entity->GetPosition());
            if(disToEntity <= minDis){
                minDis = disToEntity;
                nearestEntity = entity;
            }
        }
    }
    if(nearestEntity){               // Set strategy for the nearest entity
        nearestEntity->SetAvailability(false);  // set availability to the entity that the drone is picking up
        available = false;                      // set this drone availability as false
        SetDestination(nearestEntity->GetPosition());
        toTargetPosStrategy = new Beeline(this->GetPosition(), nearestEntity->GetPosition());
        std::string targetStrategyName = nearestEntity->GetStrategyName();
        if(targetStrategyName.compare("beeline") == 0){
            toTargetDesStrategy = new Beeline(nearestEntity->GetPosition(), nearestEntity->GetDestination());
        } else if (targetStrategyName.compare("astar") == 0){
            toTargetDesStrategy = new AstarStrategy(nearestEntity->GetPosition(), nearestEntity->GetDestination(), graph);
            toTargetDesStrategy = new SpinDecorator(toTargetDesStrategy); // add decorator
        } else if (targetStrategyName.compare("dfs") == 0){
            toTargetDesStrategy = new DfsStrategy(nearestEntity->GetPosition(), nearestEntity->GetDestination(), graph);
            toTargetDesStrategy = new SpinDecorator(toTargetDesStrategy); // add decorator
        } else if (targetStrategyName.compare("dijkstra") == 0){
            toTargetDesStrategy = new DijkstraStrategy(nearestEntity->GetPosition(), nearestEntity->GetDestination(), graph);
            toTargetDesStrategy = new SpinDecorator(toTargetDesStrategy); // add decorator
        } else {
            // If none of the strategy name matched, use beeline as default.
            toTargetDesStrategy = new Beeline(nearestEntity->GetPosition(), nearestEntity->GetDestination());
        }
    }
}

void Drone::Update(double dt, std::vector<IEntity*> scheduler) {
    if(available) {
        GetNearestEntity(scheduler);
    }
    if (toTargetPosStrategy) {  // Move drone toward the entity's position
        toTargetPosStrategy->Move(this, dt);
        if(toTargetPosStrategy->IsCompleted()){
            delete toTargetPosStrategy;
            toTargetPosStrategy = NULL;
        }
    } else if (toTargetDesStrategy) { // Move drone and entity toward the entity's destination
        toTargetDesStrategy->Move(this, dt);
        nearestEntity->SetPosition(this->GetPosition());
        nearestEntity->SetDirection(this->GetDirection());
        if(toTargetDesStrategy->IsCompleted()){
            delete toTargetDesStrategy;
            toTargetDesStrategy = NULL;
            available = true;
            nearestEntity = NULL;
        }
    }
}

void Drone::Rotate(double angle){
    direction.x = direction.x*std::cos(angle) - direction.z*std::sin(angle);
    direction.z = direction.x*std::sin(angle) + direction.z*std::cos(angle);
}
