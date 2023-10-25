#include "Moving.h"
#include "Collision.h"

Moving::Moving(const Collision& collision) :
	GameObject(collision)
{
	getCollision()->onCollisionBegin.attach(std::make_shared<
		std::function<void(std::shared_ptr<Collision>, std::shared_ptr<const Collision>)>>(
			[](std::shared_ptr<Collision> one, std::shared_ptr<const Collision> two)
		{
			one->setVelocity({ 0, 0 });
		}));
}

void Moving::update(float dt)
{
}
