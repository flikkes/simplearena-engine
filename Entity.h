#ifndef ENTITY_H
#define ENTITY_H

#include "Direction.h"

class Entity {
    private:
        float x;
        float y;
        float z;

        float plannedDistanceXF;
        float plannedDistanceYF;
        float plannedDistanceZF;
        float plannedDistanceXB;
        float plannedDistanceYB;
        float plannedDistanceZB;
        
        float dimX;
        float dimY;
        float dimZ;

        float mass;
        float fallTime;
        bool falling;

    public:
        Entity();
        Entity(float x, float y, float z, float mass, float dimX, float dimY, float dimZ);
        Entity(float x, float y, float z, float mass) : Entity(x, y, z, mass, 1, 1, 1) {};

        float getX();
        void setX(float x);
        float getY();
        void setY(float y);
        float getZ();
        void setZ(float z);

        float getPlannedDistanceX(Direction direction);
        void setPlannedDistanceX(Direction direction, float plannedDistanceX);
        float getPlannedDistanceY(Direction direction);
        void setPlannedDistanceY(Direction direction, float plannedDistanceY);
        float getPlannedDistanceZ(Direction direction);
        void setPlannedDistanceZ(Direction direction, float plannedDistanceZ);

        void resetPlannedDistances();


        void move(Direction direction, float distance);

        float getDimX();
        void setDimX(float dimX);
        float getDimY();
        void setDimY(float dimY);
        float getDimZ();
        void setDimZ(float dimZ);

        bool isColliding(Entity *questioner);
        bool isCollidingXZ(Entity *questioner);
        bool isOnPosition(float x, float y, float z);
        void placeOn(Entity *destination);

        float getMass();
        void setMass(float mass);
        
        float getFallTime();
        bool isFalling();
        void setFalling(bool falling);
        void fall(float fallTime, float fallDistance);
        float wouldFall(float fallDistance);
        void fly(float y);
        void stopFalling();
};
#endif