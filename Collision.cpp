#include "Collision.h"

Collision::Collision(const std::vector<sf::Vector2f> vertex) :
	points(vertex)
{
}

Collision::Collision(sf::Vector2f position, sf::Vector2f Velocity, sf::Vector2f Acceleration, const std::vector<sf::Vector2f> vertex) :
	points(vertex),
	v(Velocity),
	a(Acceleration)
{
	setPosition(position);
}

sf::FloatRect Collision::getBigRect() const
{
	float left = 0, top = 0, right = 0, bottom = 0;

	for (auto i : points)
	{
		left = fminf(left, i.x);
		top = fmax(top, i.y);
		right = fmax(right, i.x);
		bottom = fmin(bottom, i.y);
	}
	return sf::FloatRect(left + getPosition().x, top + getPosition().y, right - left, top - bottom);
}

bool Collision::isInside(const sf::Vector2f& pos) const 
{
	sf::Vector2f b = getInverseTransform() * pos;
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

bool Collision::isColiding(const Collision& other) const
{
	for (const auto& i : other.points)
	{
		if (isInside(other.getTransform() * i))
		{
			return true;
		}
	}
	return false;
}

std::vector<sf::Vector2f> Collision::getPoints() const
{
	return points;
}

void Collision::setPoints(const std::vector<sf::Vector2f>& p)
{
	points = p;
}

void Collision::setVelocity(sf::Vector2f Velocity)
{
	v = Velocity;
}

void Collision::setAcceleration(sf::Vector2f Acceleration)
{
	a = Acceleration;
}

void Collision::update(float dt)
{
	move(v * dt + a * (dt * dt / 2));
	v += a * dt;
}
