#ifndef ANIMATION_H
#define ANIMATION_H 
#include "Entity.h"
class Animation {

	private:
		float startX;
		float startY;
		float endX;
		float endY;
		float speed;
		bool finished;
	public:
		Animation(float startX, float startY, float endX, float endY, float speed);
		float getX(Entity *e);
		float getY(Entity *e);
		/*
		 * Attempt to set the finished flag to true. Animation can be finished if 
		 * either 
                 *  - endX and/or endY coordinates were reached
		 *  - startX and endX and/or startY and endY are equal 
		 */
		bool attemptFinish(Entity *e);
		bool isFinished();
};
#endif
