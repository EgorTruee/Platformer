#include "Controllable.h"

#include <functional>

#include "Collision.h"
#include "VectorMath.h"

Controllable::Controllable(const Collision& collision) : 
	GameObject(collision)
{
	using namespace std::placeholders;

	getCollision()->onCollisionBegin.attach(makeListener<std::shared_ptr<Collision>, std::shared_ptr<const Collision>>(
		std::function<void(std::shared_ptr<Collision>, std::shared_ptr<const Collision>)>(
			std::bind(&Controllable::onCollisionBegin, this, _1, _2))));

	getCollision()->onCollisionEnd.attach(makeListener<std::shared_ptr<Collision>, std::shared_ptr<const Collision>>(
		std::function<void(std::shared_ptr<Collision>, std::shared_ptr<const Collision>)>(
			std::bind(&Controllable::onCollisionEnd, this, _1, _2))));
}

float Controllable::getWalkVelocity() const
{
	return walkV;
}

void Controllable::setWalkVelocity(float v)
{
	walkV = v;
}

void Controllable::onCollisionBegin(std::shared_ptr<Collision> one, std::shared_ptr<const Collision> two)
{
	CollisionInfo info = one->getCollisionInfo(*two);

	if (info.normal * two->getVelocity() <= 0 && sf::Vector2f(0, 1) * info.normal > 0)
	{
		floor = two;
	}
}

void Controllable::onCollisionEnd(std::shared_ptr<Collision> one, std::shared_ptr<const Collision> two)
{
	if (!floor.expired() && floor.lock() == two)
	{
		floor.reset();
	}
}

void Controllable::update(float dt)
{
}
