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

	sf::Vector2f getWalkVelocity() const;

	void setWalkVelocity(sf::Vector2f v);

	void onCollisionBegin(Collision& one, const Collision& two);
	void onCollisionEnd(Collision& one, const Collision& two);

	virtual void update(float dt) override;

private:

	sf::Vector2f walkV;
	std::shared_ptr<const Collision> floor;
};

