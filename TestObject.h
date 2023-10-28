#pragma once

#include <memory>

#include "GameObject.h"
#include "PhysicsComp.h"
#include "Collider.h"

class TestObject : public GameObject
{
private:

	std::shared_ptr<PhysicsComp> comp;

public:

	TestObject(sf::Vector2f pos, sf::Vector2f vel) :
		GameObject(vel)
	{
		setPosition(pos);

		comp = std::make_shared<PhysicsComp>(weak_from_this(), Collider({ {10, 10}, {10, -10}, {-10, -10}, {-10, 10} }));
		addComponent(comp);
	}
};

