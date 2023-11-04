#include "ColliderComp.h"

#include <algorithm>

#include <SFML\Graphics\VertexArray.hpp>
#include <SFML\Graphics\RenderTarget.hpp>

#include "GameObject.h"

ColliderComp::ColliderComp(const std::vector<sf::Vector2f>& vertexes) :
	points(vertexes)
{
}

bool ColliderComp::checkCollision(std::shared_ptr<const ColliderComp> other) const
{
	sf::Transform toLocalCoordinats = getInverseTransform() * getParent()->getInverseTransform() *
		other->getParent()->getTransform() * other->getTransform();

	for (int i = 0; i < points.size(); i++)
	{
		sf::Vector2f a = points[(i + 1) % points.size()] - points[i];
		sf::Vector2f r1 = points[i];

		for (int j = 0; j < other->points.size(); j++)
		{
			sf::Vector2f b = (toLocalCoordinats * other->points[(j + 1) % other->points.size()] - toLocalCoordinats * other->points[j]);
			sf::Vector2f deltaR = toLocalCoordinats * other->points[i] - r1;
			float t1 = (deltaR.y * b.x - deltaR.x * b.y) / (a.y * b.x - a.x * b.y);
			float t2 = (deltaR.y * a.x - deltaR.x * a.y) / (a.y * b.x - a.x * b.y);

			if (0 <= t1 && t1 < 1 && 0 <= t2 && t2 < 1)
			{
				return true;
			}
		}
	}
	return false;
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
	std::remove_if(colliding.begin(), colliding.end(), [](std::weak_ptr<ColliderComp> other) {return other.expired(); });

	for (auto i : colliding)
	{
		std::shared_ptr<ColliderComp> other = i.lock();

		if (!checkCollision(other))
		{
			onCollisionEnd.invoke(std::static_pointer_cast<ColliderComp>(shared_from_this()), other);

			std::remove_if(colliding.begin(), colliding.end(), [other](std::weak_ptr<ColliderComp> comp) {return comp.lock() == other; });
		}
	}
}

void ColliderComp::draw(sf::RenderTarget & target, sf::RenderStates state) const
{
#ifdef _DEBUG

	state.transform *= getTransform();

	sf::VertexArray Arr(sf::LineStrip, points.size() + 1);

	for (int i = 0; i <= points.size(); i++)
	{
		Arr[i].position = points[i % points.size()];
	}
	target.draw(Arr, state);

#endif //_DEBUG
}
