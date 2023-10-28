#pragma once

#include <SFML\Graphics\Transformable.hpp>

#include <vector>

#include "Component.h"
#include "Collider.h"
#include "Delegate.h"

class PhysicsComp : public Component, public sf::Transformable
{
public:

	explicit PhysicsComp(std::shared_ptr<GameObject> parent, Collider col);
	PhysicsComp(const PhysicsComp& other) = default;
	PhysicsComp(PhysicsComp&& ohter) = default;

	PhysicsComp& operator=(const PhysicsComp& other) = default;
	PhysicsComp& operator=(PhysicsComp&& other) = default;

	bool checkCollision(std::shared_ptr<const PhysicsComp> other) const;
	void onCollision(std::shared_ptr<PhysicsComp> other);
	virtual void update(float dt) override;
	
	Collider getCollider() const;
	std::vector<std::weak_ptr<PhysicsComp>> getCollidingComponents() const;

	void setCollider(const Collider& col);

	Delegate<std::shared_ptr<PhysicsComp>, std::shared_ptr<PhysicsComp>> onCollisionBegin, onCollisionEnd;

protected:

	virtual void draw(sf::RenderTarget& target, sf::RenderStates state) const override;
private:

	Collider collider;
	std::vector<std::weak_ptr<PhysicsComp>> colliding;
};

inline Collider PhysicsComp::getCollider() const
{
	return collider;
}

inline std::vector<std::weak_ptr<PhysicsComp>> PhysicsComp::getCollidingComponents() const
{
	return colliding;
}

inline void PhysicsComp::setCollider(const Collider& col)
{
	collider = col;
}
