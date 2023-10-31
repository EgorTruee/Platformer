#include "Charector.h"

#include "ColliderComp.h"

Charector::Charector(std::shared_ptr<Controller> charControl) : 
	contorller(charControl)
{
	collider = std::make_shared<ColliderComp>(Collider({ {10, 10}, {10, -10}, {-10, -10}, {-10, 10} }));

	addComponent(collider);
}

void Charector::update(float dt)
{
}

void Charector::onCollisionBegin(std::shared_ptr<ColliderComp> thisCollider, std::shared_ptr<ColliderComp> otherCollider)
{
}
