#include "PhysicsComp.h"

#include <algorithm>

#include "GameObject.h"

PhysicsComp::PhysicsComp(std::shared_ptr<GameObject> parent, Collider col) :
	Component(parent),
	collider(col)
{
}

bool PhysicsComp::checkCollision(std::shared_ptr<const PhysicsComp> other) const
{
	sf::Transform toLocalCoordinats = getInverseTransform() * getParent()->getInverseTransform() *
		other->getParent()->getTransform() * other->getTransform();

	return collider.isColliding(other->collider, toLocalCoordinats);
}

void PhysicsComp::onCollision(std::shared_ptr<PhysicsComp> other)
{
#ifdef _DEBUG

	if (!checkCollision(other))
	{
		//TODO throw exception
	}
 #endif //_DEBUG

	auto pradicate = [&other](const std::weak_ptr<PhysicsComp> i)
	{
		return i.lock() == other;
	};
		
	if (std::find_if(colliding.begin(), colliding.end(), pradicate) == colliding.end())
	{
		onCollisionBegin.invoke(std::static_pointer_cast<PhysicsComp>(shared_from_this()), other);

		colliding.push_back(std::weak_ptr<PhysicsComp>(other));
	}
}

void PhysicsComp::update(float dt)
{
	for (auto i = colliding.begin(); i != colliding.end(); ++i)
	{
		if (i->expired())
		{
			colliding.erase(i);

			continue;
		}
		std::shared_ptr<const PhysicsComp> other = i->lock();

		if (!checkCollision(other))
		{
			onCollisionEnd.invoke(std::static_pointer_cast<PhysicsComp>(shared_from_this()), other);

			colliding.erase(i);
		}
	}
}

void PhysicsComp::draw(sf::RenderTarget & target, sf::RenderStates state) const
{
}
