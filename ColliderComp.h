#pragma once

#include <SFML\Graphics\Transformable.hpp>

#include <vector>
#include <optional>

#include "Component.h"
#include "Delegate.h"

struct CollisionInfo
{
	sf::Vector2f normal = { 0, 0 };
};
class ColliderComp : public Component, public sf::Transformable
{
public:

	virtual std::optional<CollisionInfo> isIntersects(std::shared_ptr<const ColliderComp> other) const = 0;
	virtual std::optional<float> isIntersects(sf::Vector2f begin, sf::Vector2f end) const = 0;
	virtual bool isInside(sf::Vector2f point) const = 0;
	void onCollision(std::shared_ptr<ColliderComp> other, const CollisionInfo& info);
	virtual void update(float dt) override;
	
	Delegate<std::shared_ptr<ColliderComp>, std::shared_ptr<ColliderComp>, const CollisionInfo&> onCollisionBegin;
	Delegate<std::shared_ptr<ColliderComp>, std::shared_ptr<ColliderComp>> onCollisionEnd;

protected:

	virtual void draw(sf::RenderTarget& target, sf::RenderStates state) const override {}
private:

	std::vector<std::weak_ptr<ColliderComp>> colliding;
};