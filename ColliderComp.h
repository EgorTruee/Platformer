#pragma once

#include <SFML\Graphics\Transformable.hpp>

#include <vector>

#include "Component.h"
#include "Delegate.h"

class ColliderComp : public Component, public sf::Transformable
{
public:

	explicit ColliderComp(const std::vector<sf::Vector2f>& vertexes);
	ColliderComp(const ColliderComp& other) = default;
	ColliderComp(ColliderComp&& ohter) = default;

	ColliderComp& operator=(const ColliderComp& other) = default;
	ColliderComp& operator=(ColliderComp&& other) = default;

	bool checkCollision(std::shared_ptr<const ColliderComp> other) const;

	void onCollision(std::shared_ptr<ColliderComp> other);
	virtual void update(float dt) override;
	
	std::vector<sf::Vector2f> getVertexes() const;
	std::vector<std::weak_ptr<ColliderComp>> getCollidingComponents() const;

	void setVertexes(const std::vector<sf::Vector2f>& vertexes);

	Delegate<std::shared_ptr<ColliderComp>, std::shared_ptr<ColliderComp>> onCollisionBegin, onCollisionEnd;

protected:

	virtual void draw(sf::RenderTarget& target, sf::RenderStates state) const override;
private:

	std::vector<sf::Vector2f> points;
	std::vector<std::weak_ptr<ColliderComp>> colliding;
};

inline std::vector<sf::Vector2f> ColliderComp::getVertexes() const
{
	return points;
}

inline std::vector<std::weak_ptr<ColliderComp>> ColliderComp::getCollidingComponents() const
{
	return colliding;
}

inline void ColliderComp::setVertexes(const std::vector<sf::Vector2f>& vertexes)
{
	points = vertexes;
}
