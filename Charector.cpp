#include "Charector.h"

#include "ColliderComp.h"

Charector::Charector(std::shared_ptr<Controller> charControl) : 
	contorller(charControl)
{
	collider = std::make_shared<ColliderComp>(std::vector<sf::Vector2f>({ {10, 10}, {10, -10}, {-10, -10}, {-10, 10} }));
	collider->onCollisionBegin.attach(makeListener < std::shared_ptr<ColliderComp>, std::shared_ptr<ColliderComp>>(
		std::function<void(std::shared_ptr<ColliderComp>, std::shared_ptr<ColliderComp>)>(&Charector::onCollisionBegin)));

	addComponent(collider);
}

void Charector::update(float dt)
{
}

void Charector::onCollisionBegin(std::shared_ptr<ColliderComp> thisCollider, std::shared_ptr<ColliderComp> otherCollider)
{
}
