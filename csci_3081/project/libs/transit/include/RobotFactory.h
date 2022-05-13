#ifndef ROBOT_FACTORY_H_
#define ROBOT_FACTORY_H_

#include "entity.h"
#include "IEntityFactory.h"
#include "robot.h"

#include <vector>

class RobotFactory : public IEntityFactory {
  public:
    IEntity* CreateEntity(JsonObject& entity);
};

#endif
