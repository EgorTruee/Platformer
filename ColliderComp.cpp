#include "ColliderComp.h"

#include <algorithm>

#include <SFML\Graphics\VertexArray.hpp>
#include <SFML\Graphics\RenderTarget.hpp>

#include "GameObject.h"

void ColliderComp::onCollision(std::shared_ptr<ColliderComp> other)
{
#ifdef _DEBUG

	if (!isIntersects(other))
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
	colliding.erase(std::remove_if(colliding.begin(), colliding.end(), [](std::weak_ptr<ColliderComp> other) {return other.expired(); }), colliding.end());

	for (auto i : colliding)
	{
		std::shared_ptr<ColliderComp> other = i.lock();

		if (!isIntersects(other))
		{
			onCollisionEnd.invoke(std::static_pointer_cast<ColliderComp>(shared_from_this()), other);

			colliding.erase(std::remove_if(colliding.begin(), colliding.end(), [other](std::weak_ptr<ColliderComp> comp) {return comp.lock() == other; }), colliding.end());
		}
	}
}
