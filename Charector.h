#pragma once

#include <memory>

#include "GameObject.h"

class Controller;
class ColliderComp;

class Charector : public GameObject
{
public:
	
	explicit Charector(std::shared_ptr<Controller> charControl);

	virtual void update(float dt) override;
	static void onCollisionBegin(std::shared_ptr<ColliderComp> thisCollider, std::shared_ptr<ColliderComp> otherCollider);

	virtual ~Charector() = default;

private:

	std::shared_ptr<Controller> contorller;
	std::shared_ptr<ColliderComp> collider;
};

