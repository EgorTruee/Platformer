#include "Charector.h"

#include "ColliderBox.h"
#include "Controller.h"
#include "VectorMath.h"

Charector::Charector(const std::string& name, std::shared_ptr<Controller> charControl) :
	GameObject(name),
	controller(charControl)
{
	collider = std::make_shared<ColliderBox>("Box", 20, 20);

	addComponent(collider);
}

void Charector::update(float dt)
{
	
}

void Charector::onCollisionBegin(std::shared_ptr<ColliderComp> thisCollider, std::shared_ptr<ColliderComp> otherCollider)
{
}
