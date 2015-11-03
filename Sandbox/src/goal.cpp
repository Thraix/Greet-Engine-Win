#include "goal.h"

Goal::Goal(greet::graphics::Animation* animation, float x, float y, float width, float height)
	: Entity(animation,x,y,width,height)
{

}

bool Goal::update(float timeElapsed)
{

	return false;
}