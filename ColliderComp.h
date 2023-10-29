#pragma once

#include <SFML\Graphics\Transformable.hpp>

#include <vector>

#include "Component.h"
#include "Collider.h"
#include "Delegate.h"

class ColliderComp : public Component, public sf::Transformable
{
public:

	explicit ColliderComp(Collider col);
	ColliderComp(const ColliderComp& other) = default;
	ColliderComp(ColliderComp&& ohter) = default;

	ColliderComp& operator=(const ColliderComp& other) = default;
	ColliderComp& operator=(ColliderComp&& other) = default;

	bool checkCollision(std::shared_ptr<const ColliderComp> other) const;
	void onCollision(std::shared_ptr<ColliderComp> other);
	virtual void update(float dt) override;
	
	Collider getCollider() const;
	std::vector<std::weak_ptr<ColliderComp>> getCollidingComponents() const;

	void setCollider(const Collider& col);

	Delegate<std::shared_ptr<ColliderComp>, std::shared_ptr<ColliderComp>> onCollisionBegin, onCollisionEnd;

protected:

	virtual void draw(sf::RenderTarget& target, sf::RenderStates state) const override;
private:

	Collider collider;
	std::vector<std::weak_ptr<ColliderComp>> colliding;
};

inline Collider ColliderComp::getCollider() const
{
	return collider;
}

inline std::vector<std::weak_ptr<ColliderComp>> ColliderComp::getCollidingComponents() const
{
	return colliding;
}

inline void ColliderComp::setCollider(const Collider& col)
{
	collider = col;
}
