#include "Collider.h"

#include <SFML/Graphics/Transform.hpp>

bool Collider::isColliding(Collider other, sf::Transform toLocalCoordinats) const
{
	for (int i = 0; i < points.size(); i++)
	{
		sf::Vector2f a = points[(i + 1) % points.size()] - points[i];
		sf::Vector2f r1 = points[i];

		for (int j = 0; j < other.points.size(); j++)
		{
			sf::Vector2f b = (toLocalCoordinats * other.points[(j + 1) % other.points.size()] - toLocalCoordinats * other.points[j]);
			sf::Vector2f deltaR = toLocalCoordinats * other.points[i] - r1;
			float t1 = (deltaR.y * b.x - deltaR.x * b.y) / (a.y * b.x - a.x * b.y);
			float t2 = (deltaR.y * a.x - deltaR.x * a.y) / (a.y * b.x - a.x * b.y);

			if (0 <= t1 && t1 < 1 && 0 <= t2 && t2 < 1)
			{
				return true;
			}
		}
	}
	return false;
}

bool Collider::isInside(sf::Vector2f point, sf::Transform toLocalCoordinats) const
{
	sf::Vector2f b = toLocalCoordinats * point;
	int t = 0;

	for (int i = 1; i <= points.size(); i++)
	{
		sf::Vector2f p = points[(i - 1) % points.size()];
		sf::Vector2f a = points[i % points.size()] - points[(i - 1) % points.size()];
		float t2 = (p.y * a.x - p.x * a.y) / (b.y * a.x - b.x * a.y);
		float t1 = (b.x * p.y - b.y * p.x) / (b.y * a.x - b.x * a.y);
		
		if (0 <= t1 && t1 < 1 && 0 <= t2 && t2 < 1)
		{
			t++;
		}
	}
	return (t % 2) == 0;

}
