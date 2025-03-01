#include "MapCollisionHandling.h"
#include "Direction.h"
#include "Entity.h"
#include "LegalDistances.h"
#include <math.h>
#include <iostream>
#include <vector>

using namespace std;

MapCollisionHandling::MapCollisionHandling(float mapDimX, float mapDimY,
                                           float mapDimZ)
{
  this->mapDimX = mapDimX;
  this->mapDimY = mapDimY;
  this->mapDimZ = mapDimZ;
}

LegalDistances MapCollisionHandling::getLegalMovement(Entity *player,
                                                      vector<Entity> entities,
                                                      int count)
{
  float pX = player->getX();
  float pY = player->getY();
  float pZ = player->getZ();
  float pDimX = player->getDimX();
  float pDimY = player->getDimY();
  float pDimZ = player->getDimZ();

  LegalDistances legalDistances;

  legalDistances.xF = this->mapDimX - pX - pDimX;
  legalDistances.xB = pX - pDimX < 0 ? 0 : pX - pDimX;
  legalDistances.yF = this->mapDimY - pY - pDimY;
  legalDistances.yB = pY - pDimY;
  if (legalDistances.yB < 0)
  {
    legalDistances.yB = 0;
  }
  legalDistances.zF = this->mapDimZ - pZ - pDimZ;
  legalDistances.zB = pZ - pDimZ < 0 ? 0 : pZ - pDimZ;

  for (int i = 0; i < count; i++)
  {
    Entity e = entities.at(i);

    float eX = e.getX();
    float eY = e.getY();
    float eZ = e.getZ();
    float eDimX = e.getDimX();
    float eDimY = e.getDimY();
    float eDimZ = e.getDimZ();
    float legalDistance;
    if (!this->isInLevelX(player, &e) && this->isInLevelY(player, &e) &&
        this->isInLevelZ(player, &e))
    {
      if (eX > pX)
      {
        legalDistance = eX - eDimX - pX + pDimX;
        if (legalDistance >= 0)
        {
          legalDistances.xF = legalDistances.xF > legalDistance
                                  ? legalDistance
                                  : legalDistances.xF;
        }
      }
      else if (eX < pX)
      {
        legalDistance = pX - pDimX - eX + eDimX;
        if (legalDistance >= 0)
        {
          legalDistances.xB = legalDistances.xB > legalDistance
                                  ? legalDistance
                                  : legalDistances.xB;
        }
      }
    }

    if (!this->isInLevelY(player, &e) && this->isInLevelX(player, &e) &&
        this->isInLevelZ(player, &e))
    {
      if (eY > pY)
      {
        legalDistance = eY - eDimY - pY + pDimY;
        if (legalDistance >= 0)
        {
          legalDistances.yF = legalDistances.yF > legalDistance
                                  ? legalDistance
                                  : legalDistances.yF;
        }
        else
        {
          legalDistances.yF = 0;
        }
      }
      else if (eY < pY)
      {
        legalDistance = pY - pDimY - eY + eDimY;
        if (legalDistance > 0)
        {
          legalDistances.yB = legalDistances.yB > legalDistance
                                  ? legalDistance
                                  : legalDistances.yB;
        }
        else
        {
          legalDistances.yB = 0;
        }
      }
    }

    if (!this->isInLevelZ(player, &e) && this->isInLevelX(player, &e) &&
        this->isInLevelY(player, &e))
    {
      if (eZ > pZ)
      {
        legalDistance = eZ - eDimZ - pZ + pDimZ;
        if (legalDistance >= 0)
        {
          legalDistances.zF = legalDistances.zF > legalDistance
                                  ? legalDistance
                                  : legalDistances.zF;
        }
      }
      else if (eZ < pZ)
      {
        legalDistance = pZ - pDimZ - eZ + eDimZ;
        if (legalDistance >= 0)
        {
          legalDistances.zB = legalDistances.zB > legalDistance
                                  ? legalDistance
                                  : legalDistances.zB;
        }
      }
    }
  }
  return legalDistances;
}

bool MapCollisionHandling::colliding(Entity *questioner, vector<Entity> entities, int count)
{
  bool colliding = false;
  if (questioner->getX() + questioner->getDimX() >= this->mapDimX || questioner->getX() - questioner->getDimX() <= 0)
  {
    return true;
  }
  for (int i = 0; i < count; i++)
  {
    Entity e = entities.at(i);
    if (this->isInLevelX(questioner, &e) && this->isInLevelY(questioner, &e) && this->isInLevelZ(questioner, &e))
    {
      return true;
    }
  }
  return colliding;
}

bool MapCollisionHandling::collidingSingle(Entity *questioner, Entity *answerer)
{
  return this->isInLevelX(questioner, answerer) &&
         this->isInLevelY(questioner, answerer) &&
         this->isInLevelZ(questioner, answerer);
}

float MapCollisionHandling::getMaxFallDistance(Entity *questioner, vector<Entity> entities, int count)
{
  float pY = questioner->getY();
  float pDimY = questioner->getDimY();

  float distance = pY - pDimY;

  for (int i = 0; i < count; i++)
  {
    Entity e = entities.at(i);
    float eY = e.getY();
    float eDimY = e.getDimY();
    if (this->isInLevelX(questioner, &e) && this->isInLevelZ(questioner, &e) && eY - eDimY - 1 <= pY - pDimY)
    {
      float newDistance = pY - pDimY - eY - eDimY - 1;
      distance = newDistance < distance ? newDistance : distance;
    }
  }
  return distance < 0 ? 0 : distance;
}

float MapCollisionHandling::getMaxFlyDistance(Entity *questioner, vector<Entity> entities, int count)
{
  float pY = questioner->getY();
  float pDimY = questioner->getDimY();

  float distance = this->mapDimY - pY - pDimY;

  for (int i = 0; i < count; i++)
  {
    Entity e = entities.at(i);
    float eY = e.getY();
    float eDimY = e.getDimY();
    if (this->isInLevelX(questioner, &e) && this->isInLevelZ(questioner, &e) && eY - eDimY >= pY - pDimY - 1)
    {
      float newDistance = eY - eDimY - pY - pDimY - 1;
      distance = newDistance < distance ? newDistance : distance;
    }
  }
  return distance;
}

bool MapCollisionHandling::isInLevelX(Entity *questioner, Entity *answerer)
{
  float q = questioner->getX();
  float qDim = questioner->getDimX();
  float a = answerer->getX();
  float aDim = answerer->getDimX();
  bool inRange = this->isInRange(q, qDim, a, aDim);
  // cout << "is in level x" << inRange << endl;
  return inRange;
}

bool MapCollisionHandling::isInLevelY(Entity *questioner, Entity *answerer)
{

  float q = questioner->getY();
  float qDim = questioner->getDimY();
  float a = answerer->getY();
  float aDim = answerer->getDimY();
  bool inRange = this->isInRange(q, qDim, a, aDim);
  // cout << "is in level y" << inRange << endl;
  return inRange;
}

bool MapCollisionHandling::isInLevelZ(Entity *questioner, Entity *answerer)
{
  float q = questioner->getZ();
  float qDim = questioner->getDimZ();
  float a = answerer->getZ();
  float aDim = answerer->getDimZ();
  bool inRange = this->isInRange(q, qDim, a, aDim);
  // cout << "is in level z" << inRange << endl;
  return inRange;
}

bool MapCollisionHandling::isInRange(float q, float qDim, float a, float aDim)
{
  return (q - qDim <= a + aDim) && (q + qDim >= a - aDim);
}
