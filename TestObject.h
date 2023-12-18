#pragma once

#include <memory>
#include <iostream>

#include "GameObject.h"
#include "ColliderBox.h"

class TestObject : public GameObject
{
private:

	std::shared_ptr<ColliderComp> comp;

public:

	TestObject(sf::Vector2f pos, sf::Vector2f vel) :
		GameObject(vel)
	{ 
		setPosition(pos);

		comp = std::make_shared<ColliderBox>(20, 20);
		comp->onCollisionBegin.attach(makeListener<std::shared_ptr<ColliderComp>, std::shared_ptr<ColliderComp>, const CollisionInfo&>(
			std::function<void(std::shared_ptr<ColliderComp>, std::shared_ptr<ColliderComp>, const CollisionInfo&)>
			([](std::shared_ptr<ColliderComp>, std::shared_ptr<ColliderComp>, const CollisionInfo& info) 
				{ std::cout << "Normal {" << info.normal.x << ", " << info.normal.y << "}" << std::endl; })));

		comp->onCollisionEnd.attach(makeListener<std::shared_ptr<ColliderComp>, std::shared_ptr<ColliderComp>>(
			std::function<void(std::shared_ptr<ColliderComp>, std::shared_ptr<ColliderComp>)>
			([](std::shared_ptr<ColliderComp>, std::shared_ptr<ColliderComp>)
				{
					std::cout << "Collision end" << std::endl;
				})));
		addComponent(comp);
	}
};

