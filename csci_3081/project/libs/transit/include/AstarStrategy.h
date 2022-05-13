#ifndef ASTAR_STRATEGY_H_
#define ASTAR_STRATEGY_H_

/**
 * include
 */
#include "math/vector3.h"
#include <vector>
#include "IStrategy.h"
#include "entity.h"
/**
 * @brief this class inhertis from the IStrategy class and is responsible for generating the beeline that the drone will take.
 */
class AstarStrategy : public IStrategy {
public:
    AstarStrategy(Vector3 pos_, Vector3 des_, const IGraph* graph_);
    ~AstarStrategy();
    void Move(IEntity* entity, double dt);
    bool IsCompleted();

protected:
    Vector3 des;
    Vector3 lastPos;
    std::vector<std::vector<float>> path;
    int currentIndex;
    int maxIndex;
}; //end class
#endif // ASTAR_STRATEGY_H_