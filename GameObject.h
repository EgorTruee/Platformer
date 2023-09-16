#pragma once

#include <SFML/Graphics/Drawable.hpp>

#include <vector>

class GameObject
{
public:

	GameObject();
	GameObject(const GameObject&) = default;
	GameObject(GameObject&&) = default;

	virtual void update(float delta) = 0;
	virtual std::vector<sf::Drawable*> getDrawable() = 0;

	void setPosition(sf::Vector2f position);
	void setAngle(float angle);

	sf::Vector2f getPosition();
	float getAngel();

	virtual ~GameObject() {}

protected:

	sf::Vector2f pos;
	float angle;

private:
};

