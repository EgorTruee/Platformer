#include "ColliderComp.h"

#include <algorithm>

#include <SFML\Graphics\VertexArray.hpp>
#include <SFML\Graphics\RenderTarget.hpp>

#include "GameObject.h"

ColliderComp::ColliderComp(Collider col) :
	collider(col)
{
}

bool ColliderComp::checkCollision(std::shared_ptr<const ColliderComp> other) const
{
	sf::Transform toLocalCoordinats = getInverseTransform() * getParent()->getInverseTransform() *
		other->getParent()->getTransform() * other->getTransform();

	return collider.isColliding(other->collider, toLocalCoordinats);
}

void ColliderComp::onCollision(std::shared_ptr<ColliderComp> other)
{
#ifdef _DEBUG

	if (!checkCollision(other))
	{
		//TODO throw exception
	}
 #endif //_DEBUG

	auto pradicate = [&other](const std::weak_ptr<ColliderComp> i)
	{
		return i.lock() == other;
	};
		
	if (std::find_if(colliding.begin(), colliding.end(), pradicate) == colliding.end())
	{
		onCollisionBegin.invoke(std::static_pointer_cast<ColliderComp>(shared_from_this()), other);

		colliding.push_back(std::weak_ptr<ColliderComp>(other));
	}
}

void ColliderComp::update(float dt)
{
	for (auto i = colliding.begin(); i != colliding.end(); ++i)
	{
		if (i->expired())
		{
			colliding.erase(i);

			continue;
		}
		std::shared_ptr<ColliderComp> other = i->lock();

		if (!checkCollision(other))
		{
			onCollisionEnd.invoke(std::static_pointer_cast<ColliderComp>(shared_from_this()), other);

			colliding.erase(i);
		}
	}
}

void ColliderComp::draw(sf::RenderTarget & target, sf::RenderStates state) const
{
#ifdef _DEBUG

	state.transform *= getTransform();

	std::vector<sf::Vector2f> points = collider.getVertexes();
	sf::VertexArray Arr(sf::LineStrip, points.size() + 1);

	for (int i = 0; i <= points.size(); i++)
	{
		Arr[i].position = points[i % points.size()];
	}
	target.draw(Arr, state);

#endif //_DEBUG
}
