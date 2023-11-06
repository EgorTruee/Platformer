#include "Charector.h"

#include "ColliderComp.h"
#include "Controller.h"
#include "VectorMath.h"

Charector::Charector(std::shared_ptr<Controller> charControl) : 
	controller(charControl)
{
	collider = std::make_shared<ColliderComp>(std::vector<sf::Vector2f>({ {10, 10}, {10, -10}, {-10, -10}, {-10, 10} }));

	addComponent(collider);
}

void Charector::update(float dt)
{
	sf::Vector2f moveDirection = { controller->getAxisValue("moveX"), controller->getAxisValue("moveY") };

	moveDirection /= length<float>(moveDirection);

	setVelocity(moveDirection * 100.f);
}

void Charector::onCollisionBegin(std::shared_ptr<ColliderComp> thisCollider, std::shared_ptr<ColliderComp> otherCollider)
{
}
