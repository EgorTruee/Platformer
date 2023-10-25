#pragma once

#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <vector>

#include "Delegate.h"

struct CollisionInfo
{
	sf::Vector2f point;
	sf::Vector2f normal;
};
class Collision : public sf::Transformable , public std::enable_shared_from_this<Collision>
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

	CollisionInfo getCollisionInfo(const Collision& other) const;
	sf::FloatRect getBigRect() const;
	std::vector<sf::Vector2f> getPoints() const;
	float getAngularSpeed() const;
	float getAngularAcceleration() const;
	sf::Vector2f getNormalToEdge(int number) const;
	int getCotegory() const;
	int getOverlapWith() const;
	int getCollideWith() const;
	sf::Vector2f getVelocity() const;
	sf::Vector2f getAcceleration() const;

	void setAngularSpeed(float omega);
	void setAngularAcceleration(float epsilon);
	void setPoints(const std::vector<sf::Vector2f>& points);
	void setVelocity(sf::Vector2f Velocity);
	void setAcceleration(sf::Vector2f Acceleration);
	void setCotegory(int mask);
	void setOverlapWith(int mask);
	void setCollideWith(int mask);

	void addAngularSpeed(float omega);
	void addAngularAcceleration(float epsilon);
	void addVelocity(sf::Vector2f velocity);
	void addAcceleration(sf::Vector2f acceleration);
	void addCollideWith(int mask);
	void addOverlapWith(int mask);

	void collide(std::shared_ptr<Collision> other);
	void update(float dt);

	Delegate<std::shared_ptr<Collision>, std::shared_ptr<const Collision>> onCollision, onCollisionBegin, onCollisionEnd;
	Delegate<std::shared_ptr<Collision>, std::shared_ptr<const Collision>> onOverlap, onOverlapBegin, onOverlapEnd;

private:

	void collisionUpdate(float dt);

	std::vector<sf::Vector2f> points;
	std::vector<std::shared_ptr<Collision>> colliding;
	sf::Vector2f v = { 0, 0 };
	sf::Vector2f a = { 0, 0 };
	float angularSpeed = 10;
	float angularAcceleration = 0;
	int cotegory = 0;
	int collideWith = 0;
	int overlapWith = 0;
};

