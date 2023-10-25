#pragma once

#include <memory>

#include "GameObject.h"

class Collision;

class Controllable : public GameObject
{
public:

	explicit Controllable(const Collision& collision);
	Controllable(const Controllable& other) = default;
	Controllable(Controllable&& other) = default;

	float getWalkVelocity() const;

	void setWalkVelocity(float v);

	void onCollisionBegin(std::shared_ptr<Collision> one, std::shared_ptr<const Collision> two);
	void onCollisionEnd(std::shared_ptr<Collision> one, std::shared_ptr<const Collision> two);

	virtual void update(float dt) override;

private:

	float walkV = 0;
	std::weak_ptr<const Collision> floor;
};

