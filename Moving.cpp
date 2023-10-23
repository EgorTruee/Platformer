#include "Moving.h"
#include "Collision.h"

Moving::Moving(const Collision& collision) :
	GameObject(collision)
{
	getCollision()->onCollisionBegin.attach(std::make_shared<std::function<void(Collision&, const Collision&)>>([](Collision& one, const Collision& two)
		{
			one.setVelocity({ 0, 0 });
		}));
}

void Moving::update(float dt)
{
}
