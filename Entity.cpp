#include <iostream>

#include "Entity.h"
#include "Direction.h"
#include "Validation.h"

Entity::Entity(float x, float y, float z, float mass, float dimX, float dimY, float dimZ)
{
    this->setX(x);
    this->setY(y);
    this->setZ(z);
    this->setMass(mass);
    this->setDimX(dimX);
    this->setDimY(dimY);
    this->setDimZ(dimZ);
    this->falling = false;
    this->fallTime = 0;
    this->plannedDistanceXF = 0;
    this->plannedDistanceYF = 0;
    this->plannedDistanceZF = 0;
    this->plannedDistanceXB = 0;
    this->plannedDistanceYB = 0;
    this->plannedDistanceZB = 0;
}

void Entity::setX(float x) {
    if(Validation::isValidCoordinate(x)) {
        this->x = x;
    }
}

void Entity::setY(float y) {
    if(Validation::isValidCoordinate(y)) {
        this->y = y;
    }
}

void Entity::setZ(float z) {
    if(Validation::isValidCoordinate(z)) {
        this->z = z;
    }
}

float Entity::getPlannedDistanceX(Direction direction) {
    try {
        switch (direction) {
        case Direction::XFORW:
            return this->plannedDistanceXF;
        case Direction::XBACKW:
            return this->plannedDistanceXB;
        default: 
            throw direction;
        }
    } catch (Direction ex) {
        std::cout << "Unexpected get x direction" << std::endl;
    }
    return 0;
}
void Entity::setPlannedDistanceX(Direction direction, float plannedDistanceX) {
    try {
        switch (direction) {
        case Direction::XFORW:
            this->plannedDistanceXF = plannedDistanceX;
            break;
        case Direction::XBACKW:
            this->plannedDistanceXB = plannedDistanceX;
            break;
        default: 
            throw direction;
        }
    } catch (Direction ex) {
        std::cout << "Unexpected set x direction" << std::endl;
    }
}
float Entity::getPlannedDistanceY(Direction direction) {
    try {
        switch (direction) {
        case Direction::YFORW:
            return this->plannedDistanceYF;
        case Direction::YBACKW:
            return this->plannedDistanceYB;
        default: 
            throw direction;
        }
    } catch (Direction ex) {
        std::cout << "Unexpected get y direction" << std::endl;
    }
    return 0;
}
void Entity::setPlannedDistanceY(Direction direction, float plannedDistanceY) {
    try {
        switch (direction) {
        case Direction::YFORW:
            this->plannedDistanceYF = plannedDistanceY;
            break;
        case Direction::YBACKW:
            this->plannedDistanceYB = plannedDistanceY;
            break;
        default: 
            throw direction;
        }
    } catch (Direction ex) {
        std::cout << "Unexpected set y direction" << std::endl;
    }
}
float Entity::getPlannedDistanceZ(Direction direction) {
    try {
        switch (direction) {
        case Direction::ZFORW:
            return this->plannedDistanceZF;
        case Direction::ZBACKW:
            return this->plannedDistanceZB;
        default: 
            throw direction;
        }
    } catch (Direction ex) {
        std::cout << "Unexpected get z direction" << std::endl;
    }
    return 0;
}
void Entity::setPlannedDistanceZ(Direction direction, float plannedDistanceZ) {
    try {
        switch (direction) {
        case Direction::ZFORW:
            this->plannedDistanceZF = plannedDistanceZ;
            break;
        case Direction::ZBACKW:
            this->plannedDistanceZB = plannedDistanceZ;
            break;
        default: 
            throw direction;
        }
    } catch (Direction ex) {
        std::cout << "Unexpected set z direction" << std::endl;
    }
}

void Entity::resetPlannedDistances() {
    this->plannedDistanceXB = 0;
    this->plannedDistanceXF = 0;
    this->plannedDistanceYB = 0;
    this->plannedDistanceYF = 0;
    this->plannedDistanceZB = 0;
    this->plannedDistanceZF = 0;
}

void Entity::setMass(float mass) {
    if(Validation::isValidMass(mass)) {
        this->mass = mass;
    }
}

void Entity::setDimX(float dimX) {
    if(Validation::isValidDimension(dimX)) {
        this->dimX = dimX;
    }
}

void Entity::setDimY(float dimY) {
    if(Validation::isValidDimension(dimY)) {
        this->dimY = dimY;
    }
}

void Entity::setDimZ(float dimZ) {
    if(Validation::isValidDimension(dimZ)) {
        this->dimZ = dimZ;
    }
}

float Entity::getX() {return this->x;}
float Entity::getY() {return this->y;}
float Entity::getZ() {return this->z;}
float Entity::getMass() {return this->mass;}
float Entity::getDimX() {return this->dimX;}
float Entity::getDimY() {return this->dimY;}
float Entity::getDimZ() {return this->dimZ;}

void Entity::move(Direction direction, float distance) {
    switch (direction) {
        case Direction::XFORW:
            this->setX(this->getX() + distance);
            break;
        case Direction::XBACKW:
            this->setX(this->getX() - distance);
            break;
        case Direction::YFORW:
            this->setY(this->getY() + distance);
            break;
        case Direction::YBACKW:
            this->setY(this->getY() - distance);
            break;
        case Direction::ZFORW:
            this->setZ(this->getZ() + distance);
            break;
        case Direction::ZBACKW:
            this->setZ(this->getZ() - distance);
            break;
        default:
            break;
    }
}

void Entity::setFalling(bool falling) {
    this->falling = falling;
}

void Entity::fall(float fallTime, float fallDistance) {
    this->falling = true;
    this->fallTime = fallTime;
    this->move(Direction::YBACKW, fallDistance);
}
void Entity::fly(float y) {
    if (y > 0) {
        this->falling = true;
        this->fallTime = 0;
        this->move(Direction::YFORW, y);
    }
}
void Entity::stopFalling() {
    this->falling = false;
    this->fallTime = 0;
}

bool Entity::isFalling() {return this->falling;}
float Entity::getFallTime() {return this->fallTime;}

void Entity::placeOn(Entity *destination) {
    this->setY(destination->getY() + destination->getDimY()  + this->getDimY() );
}

bool Entity::isColliding(Entity *questioner) {
    bool colliding = 
    questioner->x - questioner->dimX  <= (this->x + this->dimX ) && 
    questioner->x + questioner->dimX  >= (this->x - this->dimX ) && 
    questioner->y - questioner->dimY  <= (this->y + this->dimY ) && 
    questioner->y + questioner->dimY  >= (this->y - this->dimY ) && 
    questioner->z - questioner->dimZ  <= (this->z + this->dimZ ) && 
    questioner->z + questioner->dimZ  >= (this->z - this->dimZ );
    return colliding;
}

bool Entity::isCollidingXZ(Entity *questioner) {
    bool colliding = 
    questioner->x - questioner->dimX  <= (this->x + this->dimX ) && 
    questioner->x + questioner->dimX  >= (this->x - this->dimX ) &&
    questioner->z - questioner->dimZ  <= (this->z + this->dimZ ) && 
    questioner->z + questioner->dimZ  >= (this->z - this->dimZ );
    return colliding;
}

bool Entity::isOnPosition(float x, float y, float z) {
    return this->x == x && this->y == y && this->z == z;
}