#ifndef DRONE_H_
#define DRONE_H_

#include "entity.h"
#include "IStrategy.h"
#include "math/vector3.h"

#include <vector>

// Represents a drone in a physical system.
// Drones move using euler integration based on a specified
// velocity and direction.
class Drone : public IEntity {
public:
    // Drones are created with a name
    Drone(JsonObject obj);
    // Destructor
    ~Drone();
    
    float GetSpeed() const {return speed;}

    // Gets the drone position
    Vector3 GetPosition() const { return position; }

    Vector3 GetDirection() const { return direction; }
    
    Vector3 GetDestination() const { return destination; }

    JsonObject GetDetails() const { return details; }

    bool GetAvailability() const {return available;}

    std::string GetStrategyName() const {return strategyName;}

    void GetNearestEntity(std::vector<IEntity*> scheduler);

    // Updates the drone's position
    void Update(double dt, std::vector<IEntity*> scheduler);

    void SetPosition(Vector3 pos_) { position = pos_; }

    // Sets the drone's direction
    void SetDirection(Vector3 dir_) { direction = dir_; }

    void SetDestination(Vector3 des_) { destination = des_;}

    void SetStrategyName(std::string strategyName_) { strategyName = strategyName_;}

    // Rotates a drone
    void Rotate(double angle);

    // Removing the copy constructor and assignment operator
    // so that drones cannot be coppied.
    Drone(const Drone& drone) = delete;
    Drone& operator=(const Drone& drone) = delete;

private:
    JsonObject details;
    Vector3 position;
    Vector3 direction;
    Vector3 destination;
    float speed;
    bool available;
    std::string strategyName;

    IEntity* nearestEntity = NULL;
    IStrategy* toTargetPosStrategy = NULL;
    IStrategy* toTargetDesStrategy = NULL;
    
};

#endif
