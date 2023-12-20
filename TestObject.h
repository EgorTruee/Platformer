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

	TestObject(const std::string& name, sf::Vector2f pos, sf::Vector2f vel) :
		GameObject(name, vel)
	{ 
		setPosition(pos);

		comp = std::make_shared<ColliderBox>("Box", 20, 20);
		comp->onCollisionBegin.attach(makeListener<std::shared_ptr<ColliderComp>, std::shared_ptr<ColliderComp>, const CollisionInfo&>(
			std::function<void(std::shared_ptr<ColliderComp>, std::shared_ptr<ColliderComp>, const CollisionInfo&)>
			([this](std::shared_ptr<ColliderComp>, std::shared_ptr<ColliderComp>, const CollisionInfo& info) 
				{
					std::cout << this->getName() << " Normal {" << info.normal.x << ", " << info.normal.y << "}" << std::endl; 
				})));
		comp->onCollisionEnd.attach(makeListener<std::shared_ptr<ColliderComp>, std::shared_ptr<ColliderComp>>(
			std::function<void(std::shared_ptr<ColliderComp>, std::shared_ptr<ColliderComp>)>
			([](std::shared_ptr<ColliderComp>, std::shared_ptr<ColliderComp>)
				{
					std::cout << "Collision end" << std::endl;
				})));
		addComponent(comp);
	}
};

