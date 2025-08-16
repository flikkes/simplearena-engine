#include "GravitySimulation.h"

GravitySimulation::GravitySimulation(float gravityVelocity)
{
  this->gravityVelocity = gravityVelocity;
  this->airDrag = 0.3;
}
GravitySimulation::GravitySimulation(float gravityVelocity, float airDrag)
{
  this->gravityVelocity = gravityVelocity;
  this->airDrag = airDrag;
}
float GravitySimulation::getDistance(float seconds)
{
  return gravityVelocity * (seconds * airDrag);
}
float GravitySimulation::getDistance(float seconds, float mass)
{
  return gravityVelocity * (seconds * airDrag);
}
