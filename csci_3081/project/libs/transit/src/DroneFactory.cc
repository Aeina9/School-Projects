#include "DroneFactory.h"

IEntity* DroneFactory::CreateEntity(JsonObject& entity){
  std::string type = entity["type"];
  if(type.compare("drone") == 0){
    Drone* droneTemp = new Drone(entity);
    std::cout << "Drone Created" << std::endl;
    return droneTemp;
  }
  return nullptr;
}
