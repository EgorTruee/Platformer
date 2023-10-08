#include "Moving.h"
#include "Collision.h"

Moving::Moving(const Collision& collision) :
	GameObject(collision)
{
}

void Moving::update(float dt)
{
}
