#include "DijkstraStrategy.h"
#include "routing/dijkstra.h"
#include "routing_api.h"
#include "graph.h"
using namespace routing;

DijkstraStrategy::DijkstraStrategy(Vector3 pos_, Vector3 des_, const IGraph* graph_) {
    des = des_;
    currentIndex = 0;
    graph = graph_;
    std::vector<float> posTemp;
    std::vector<float> desTemp;
    posTemp.push_back(pos_.x);
    posTemp.push_back(pos_.y);
    posTemp.push_back(pos_.z);
    desTemp.push_back(des_.x);
    desTemp.push_back(des_.y);
    desTemp.push_back(des_.z);
    std::vector<float> start = graph->NearestNode(posTemp, EuclideanDistance())->GetPosition();
    std::vector<float> end = graph->NearestNode(desTemp, EuclideanDistance())->GetPosition();
    path = graph->GetPath(start, end, Dijkstra::Default());
    currentIndex = 0;
    maxIndex = path.size()-1;
}

bool DijkstraStrategy::IsCompleted(){
    return currentIndex == maxIndex;
}

void DijkstraStrategy::Move(IEntity* entity, double dt){
    Vector3 currentPos = entity->GetPosition();
    Vector3 desVec = Vector3(path[currentIndex].at(0), path[currentIndex].at(1), path[currentIndex].at(2));
    Vector3 dir = (desVec - currentPos).Unit();
    float speed = entity->GetSpeed(); 
    currentPos = currentPos + dir * speed * dt;
    lastPos = currentPos;
    entity->SetPosition(currentPos);
    entity->SetDirection(dir);
    
    if((desVec - lastPos).Magnitude()<1.0){
        currentIndex++;
    }
}