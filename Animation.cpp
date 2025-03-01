#include "Entity.h"
#include "Animation.h"
#include "math.h"

Animation::Animation(float startX, float startY, float endX, float endY, float speed) {
	this->startX = startX;
	this->startY = startY;
	this->endX = endX;
	this->endY = endY;
	this->speed = speed;
	this->finished = false;
}

float Animation::getX(Entity *e) {
	float oldX = e->getX();
	float newX;
	if (!this->attemptFinish(e) && this->startX != this->endX) {
		if (this->startX<this->endX) {
			newX = oldX + this->speed;
			return newX < this->endX ? newX : this->endX;
		} else if (this->startX>this->endX) {
			newX = oldX - this->speed;
			return newX > this->endX ? newX : this->endX;
		}
	}
	return this->endX;
}

float Animation::getY(Entity *e) {
	float oldY = e->getY();
	float newY;
	if (!this->attemptFinish(e) && this->startY != this->endY) {
		if (this->startY<this->endY) {
			newY = oldY + this->speed;
			return newY < this->endY ? newY : this->endY;
		} else if (this->startY>this->endY) {
			newY = oldY - this->speed;
			return newY > this->endY ? newY : this->endY;
		}
	}
	return this->endY;
}

bool Animation::attemptFinish(Entity *e) {
	if (	(abs(e->getX() - this->endX) <= 1 && abs(e->getY() - this->endY) <= 1) ||
		(this->startX == this->endX && this->startY == this->endY) ||
		(this->startX == this->endX && abs(e->getY() - this->endY) <= 1) ||
		(abs(e->getX() - this->endX) <= 1 && this->startY == this->endY)
	) {
		this->finished = true;
	}	
	return this->finished;
}

bool Animation::isFinished() {
	return this->finished;
}

