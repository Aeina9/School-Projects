#ifndef BEELINE_H_
#define BEELINE_H_

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
class Beeline : public IStrategy {
public:
    Beeline(Vector3 pos_, Vector3 des_);
    ~Beeline();
    void Move(IEntity* entity, double dt);
    bool IsCompleted();

protected:
    Vector3 des;
    Vector3 pos;
    Vector3 lastPos;
}; //end class
#endif // BEELINE_H_