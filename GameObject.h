#pragma once

#include <SFML/Graphics/Drawable.hpp>

#include <vector>
#include <memory>

class Collision;

class GameObject : public sf::Drawable
{
public:

	GameObject();
	explicit GameObject(const Collision& collider);
	GameObject(const GameObject&) = default;
	GameObject(GameObject&&) = default;

	virtual void update(float delta) = 0;

	void setPosition(sf::Vector2f position);
	void setRotation(float angle);

	sf::Vector2f getPosition() const;
	float getRotation() const;
	std::shared_ptr<Collision> getCollision() const;

	virtual ~GameObject() {}

protected:

	virtual void draw(sf::RenderTarget& target, sf::RenderStates state) const override;

private:

	std::shared_ptr<Collision> collision;
};

