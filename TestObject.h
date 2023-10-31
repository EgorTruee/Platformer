#pragma once

#include <memory>
#include <iostream>

#include "GameObject.h"
#include "ColliderComp.h"
#include "Collider.h"

class TestObject : public GameObject
{
private:

	std::shared_ptr<ColliderComp> comp;

public:

	TestObject(sf::Vector2f pos, sf::Vector2f vel) :
		GameObject(vel)
	{ 
		setPosition(pos);

		comp = createComponent<ColliderComp>(Collider({ {10, 10}, {10, -10}, {-10, -10}, {-10, 10} }));
		comp->onCollisionBegin.attach(makeListener<std::shared_ptr<ColliderComp>, std::shared_ptr<ColliderComp>>(
			std::function<void(std::shared_ptr<ColliderComp>, std::shared_ptr<ColliderComp>)>([](std::shared_ptr<ColliderComp>, std::shared_ptr<ColliderComp>) 
				{ std::cout << "Collision" << std::endl; })));
		addComponent(comp);
	}
};

