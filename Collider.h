#pragma once

#include <SFML/System/Vector2.hpp>

#include <vector>

namespace sf
{
	class Transform;
}

class Collider
{
public:
	
	explicit Collider(std::vector<sf::Vector2f> vertexes);
	Collider(const Collider& other) = default;
	Collider(Collider&& other) = default;

	Collider& operator=(const Collider& other) = default;
	Collider& operator=(Collider&& other) = default;

	bool isColliding(Collider other, sf::Transform toLocalCoordinats) const;
	bool isInside(sf::Vector2f point, sf::Transform toLocalCoordinats) const;
	
	std::vector<sf::Vector2f> getVertexes() const;

	void setVertexes(std::vector<sf::Vector2f> vertexes);

private:

	std::vector<sf::Vector2f> points;
};

inline Collider::Collider(std::vector<sf::Vector2f> vertexes) :
	points(vertexes)
{
}

inline std::vector<sf::Vector2f> Collider::getVertexes() const
{
	return points;
}

inline void Collider::setVertexes(std::vector<sf::Vector2f> vertexes)
{
	points = vertexes;
}

