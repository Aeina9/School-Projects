#ifndef DRONE_FACTORY_H_
#define DRONE_FACTORY_H_

#include "entity.h"
#include "IEntityFactory.h"
#include "drone.h"

#include <vector>

class DroneFactory : public IEntityFactory {
  public:
    virtual ~DroneFactory() {}
    IEntity* CreateEntity(JsonObject& entity);
};

#endif
