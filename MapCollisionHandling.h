#ifndef MAPCOLLISIONHANDLING_H
#define MAPCOLLISIONHANDLING_H
#include "Direction.h"
#include "Entity.h"
#include "LegalDistances.h"

class MapCollisionHandling {
private:
  float mapDimX;
  float mapDimY;
  float mapDimZ;

public:
  MapCollisionHandling(float mapDimX, float mapDimY, float mapDimZ);
  LegalDistances getLegalMovement(Entity *player, Entity *entities[], int count);
  bool colliding(Entity *questioner, Entity *entities[], int count);
  bool collidingSingle(Entity *questioner, Entity *answerer);
  float getMaxFallDistance(Entity *questioner, Entity *entities[], int count);
  float getMaxFlyDistance(Entity *questioner, Entity *entities[], int count);
  bool isInLevelX(Entity *questioner, Entity *answerer);
  bool isInLevelY(Entity *questioner, Entity *answerer);
  bool isInLevelZ(Entity *questioner, Entity *answerer);
  bool isInRange(float q, float qDim, float a, float aDim);
};
#endif