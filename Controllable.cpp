#include "Controllable.h"

#include <functional>

#include "Collision.h"

Controllable::Controllable(const Collision& collision) : 
	GameObject(collision)
{
	using namespace std::placeholders;

	getCollision()->onCollisionBegin.attach(makeListener<Collision&, const Collision&>(std::function<void(Collision&, const Collision&)>(std::bind(&Controllable::onCollisionBegin, this, _1, _2))));
}

sf::Vector2f Controllable::getWalkVelocity() const
{
	return sf::Vector2f();
}

void Controllable::setWalkVelocity(sf::Vector2f v)
{
}

void Controllable::onCollisionBegin(Collision& one, const Collision& two)
{
}

void Controllable::onCollisionEnd(Collision& one, const Collision& two)
{
}

void Controllable::update(float dt)
{
}
