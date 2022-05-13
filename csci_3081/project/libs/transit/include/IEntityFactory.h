#ifndef I_ENTITY_FACTORY_H_
#define I_ENTITY_FACTORY_H_

#include "util/json.h"

#include "entity.h"
#include "IEntityFactory.h"
#include "drone.h"
#include "graph.h"

class IEntityFactory {
  public:
    virtual ~IEntityFactory() {}
    virtual IEntity* CreateEntity(JsonObject& entity) = 0;
};

#endif
