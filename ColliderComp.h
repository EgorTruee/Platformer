#pragma once

#include <SFML\Graphics\Transformable.hpp>

#include <vector>
#include <optional>

#include "Component.h"
#include "Delegate.h"

class ColliderComp : public Component, public sf::Transformable
{
public:

	virtual bool isIntersects(std::shared_ptr<const ColliderComp> other) const = 0;
	virtual std::optional<float> isIntersects(sf::Vector2f begin, sf::Vector2f end) const = 0;
	virtual bool isInside(sf::Vector2f point) const = 0;
	void onCollision(std::shared_ptr<ColliderComp> other);
	virtual void update(float dt) override;
	
	Delegate<std::shared_ptr<ColliderComp>, std::shared_ptr<ColliderComp>> onCollisionBegin, onCollisionEnd;

protected:

	virtual void draw(sf::RenderTarget& target, sf::RenderStates state) const override {}
private:

	std::vector<std::weak_ptr<ColliderComp>> colliding;
};