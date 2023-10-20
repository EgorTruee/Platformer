#pragma once

#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <vector>

#include "Delegate.h"

class Collision : public sf::Transformable
{
public:

	explicit Collision(const std::vector<sf::Vector2f> vertex);
	explicit Collision(sf::Vector2f position = { 0, 0 }, 
		sf::Vector2f velocity = { 0, 0 },
		sf::Vector2f acceleration = { 0, 0 }, 
		float angularSpeed = 0,
		float angularAcceleration = 0,
		const std::vector<sf::Vector2f> vertex = {});
	Collision(const Collision& other) = default;
	Collision(Collision&& other) = default;

	bool isInside(const sf::Vector2f& pos) const;
	bool isColiding(const Collision& other) const;

	sf::FloatRect getBigRect() const;
	std::vector<sf::Vector2f> getPoints() const;
	float getAngularSpeed() const;
	float getAngularAcceleration() const;
	sf::Vector2f getNormalToEdge(int number) const;

	void setAngularSpeed(float omega);
	void setAngularAcceleration(float epsilon);
	void setPoints(const std::vector<sf::Vector2f>& points);
	void setVelocity(sf::Vector2f Velocity);
	void setAcceleration(sf::Vector2f Acceleration);

	void addAngularSpeed(float omega);
	void addAngularAcceleration(float epsilon);
	void addVelocity(sf::Vector2f velocity);
	void addAcceleration(sf::Vector2f acceleration);

	void collide(std::shared_ptr<Collision> other);
	void update(float dt);

	Delegate<Collision&, Collision&> onCollision, onCollisionBegin, onCollisionEnd;

private:

	void collisionUpdate(float dt);

	std::vector<sf::Vector2f> points;
	std::vector<std::shared_ptr<Collision>> colliding;
	sf::Vector2f v = { 0, 0 };
	sf::Vector2f a = { 0, 0 };
	float angularSpeed = 10;
	float angularAcceleration = 0;
};

