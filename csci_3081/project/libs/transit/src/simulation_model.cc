#include "simulation_model.h"
#include "DroneFactory.h"
#include "RobotFactory.h"
#include "Beeline.h"
#include "AstarStrategy.h"

SimulationModel::SimulationModel(IController& controller) : controller(controller){
  compFactory = new CompositeFactory();
  compFactory->AddFactory(new DroneFactory());
  compFactory->AddFactory(new RobotFactory());
}

/// Creates an simulation entity
void SimulationModel::CreateEntity(JsonObject& entity) {
    // int id = entity["entityId"];
    std::string type = entity["type"];
    std::string name = entity["name"];
    JsonArray position = entity["position"];
    std::cout << name << ": " << position << std::endl;

    IEntity* myNewEntity = compFactory->CreateEntity(entity);
    myNewEntity->SetGraph(graph);
    // Add to the drone dictionary
    Drone* drone = dynamic_cast<Drone*>(myNewEntity);
    if(drone) {
      drones.push_back(drone);
    }
    // Add to the robot dictionary
    Robot* robot = dynamic_cast<Robot*>(myNewEntity);
    if(robot) {
      robots.push_back(robot);
    }
    // Call AddEntity to add it to the view 
    controller.AddEntity(*myNewEntity);
    entities.push_back(myNewEntity);
}

/// Schedules a trip for an object in the scene
void SimulationModel::ScheduleTrip(JsonObject& details) {
    std::string name = details["name"];
    JsonArray start = details["start"];
    JsonArray end = details["end"];
    std::cout << name << ": " << start << " --> " << end << std::endl;
    
    for(auto entity : entities){  // Add the entity to the scheduler
      JsonObject detailsTemp = entity->GetDetails();
      std::string nameTemp = detailsTemp["name"];
      std::string typeTemp = detailsTemp["type"];
      if(name.compare(nameTemp) == 0 && typeTemp.compare("robot") == 0 && entity->GetAvailability()){
        std::string strategyName = details["search"];
        entity->SetStrategyName(strategyName);
        entity->SetDestination(Vector3(end[0], end[1], end[2]));
        scheduler.push_back(entity);
        break;
      }
    }
    controller.SendEventToView("TripScheduled", details);

    // Add a route to visualize the path
    // controller.AddPath(pathId, path);
}

/// Updates the simulation
void SimulationModel::Update(double dt) {
    //std::cout << "Update: " << dt << std::endl;
    
    // Call controller to update changed entities
    for (int i = 0; i < entities.size(); i++) {
      entities[i]->Update(dt, scheduler);
      controller.UpdateEntity(*entities[i]);
    }

    // Remove entites you no longer need
    // controller.RemoveEntity(myDeletedEntityId);

    // Remove paths you no longer want to see:
    // controller.RemovePath(myDeletedPathId);
}

void SimulationModel::AddFactory(IEntityFactory* factory) {
  compFactory->AddFactory(factory);
}
