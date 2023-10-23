#include "Collision.h"

#include <algorithm>

Collision::Collision(const std::vector<sf::Vector2f> vertex) :
	Collision({ 0, 0 }, { 0, 0 }, { 0, 0 }, 0.f, 0.f, vertex)
{
}

Collision::Collision(sf::Vector2f position, sf::Vector2f Velocity, sf::Vector2f Acceleration, float omega, float epsilon, const std::vector<sf::Vector2f> vertex) :
	points(vertex),
	v(Velocity),
	a(Acceleration),
	angularSpeed(omega),
	angularAcceleration(epsilon)
{
	setPosition(position);
}

sf::FloatRect Collision::getBigRect() const
{
	float left = 0, top = 0, right = 0, bottom = 0;

	for (auto i : points)
	{
		i = getTransform() * i;

		left = fminf(left, i.x);
		top = fmaxf(top, i.y);
		right = fmaxf(right, i.x);
		bottom = fminf(bottom, i.y);
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
	for (int i = 0; i < points.size(); i++)
	{
		sf::Vector2f a = points[(i + 1) % points.size()] - points[i];
		sf::Vector2f r1 = points[i];

		for (int j = 0; j < other.points.size(); j++)
		{
			sf::Vector2f b = (getInverseTransform() * other.getTransform() * other.points[(j + 1) % other.points.size()] - getInverseTransform() * other.getTransform() * other.points[j]);
			sf::Vector2f deltaR = getInverseTransform() * (other.getTransform() * other.points[i]) - r1;
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

std::vector<sf::Vector2f> Collision::getPoints() const
{
	return points;
}

float Collision::getAngularSpeed() const
{
	return angularSpeed;
}

float Collision::getAngularAcceleration() const
{
	return angularAcceleration;
}

sf::Vector2f Collision::getNormalToEdge(int n) const
{
	sf::Vector2f a = points[(n + 1) % points.size()] - points[n % points.size()];

	return sf::Vector2f(a.y, -a.x);
}

int Collision::getCotegory() const
{
	return cotegory;
}

int Collision::getOverlapWith() const
{
	return overlapWith;
}

int Collision::getCollideWith() const
{
	return collideWith;
}

void Collision::setAngularSpeed(float omega)
{
	angularSpeed = omega;
}

void Collision::setAngularAcceleration(float epsilon)
{
	angularAcceleration = epsilon;
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

void Collision::setCotegory(int mask)
{
	cotegory = mask;
}

void Collision::setOverlapWith(int mask)
{
	overlapWith = mask;
}

void Collision::setCollideWith(int mask)
{
	collideWith = mask;
}

void Collision::addAngularSpeed(float omega)
{
	angularSpeed += omega;
}

void Collision::addAngularAcceleration(float epsilon)
{
	angularAcceleration += epsilon;
}

void Collision::addVelocity(sf::Vector2f velocity)
{
	v += velocity;
}

void Collision::addAcceleration(sf::Vector2f acceleration)
{
	a += acceleration;
}

void Collision::addCollideWith(int mask)
{
	collideWith |= mask;
}

void Collision::addOverlapWith(int mask)
{
	overlapWith |= mask;
}

void Collision::collide(std::shared_ptr<Collision> other)
{
	if (std::find(colliding.begin(), colliding.end(), other) != colliding.end())
	{
		return;
	}
	if (collideWith & other->cotegory)
	{
		onCollisionBegin.invoke(*this, *other);
	}
	if (overlapWith & other->cotegory)
	{
		onOverlapBegin.invoke(*this, *other);
	}
	colliding.push_back(other);
}

void Collision::update(float dt)
{
	collisionUpdate(dt);

	move(v * dt + a * (dt * dt / 2));
	rotate(angularSpeed * dt + angularAcceleration * (dt * dt / 2));
	angularSpeed += angularAcceleration * dt;
	v += a * dt;
}

void Collision::collisionUpdate(float dt)
{
	for (int i = 0; i < colliding.size(); i++)
	{
		if (isColiding(*colliding[i]))
		{
			if (collideWith & colliding[i]->cotegory)
			{
				onCollision.invoke(*this, *colliding[i]);
			}
			if (overlapWith & colliding[i]->cotegory)
			{
				onOverlap.invoke(*this, *colliding[i]);
			}
		}
		else
		{
			if (collideWith & colliding[i]->cotegory)
			{
				onCollisionEnd.invoke(*this, *colliding[i]);
			}
			if (overlapWith & colliding[i]->cotegory)
			{
				onOverlapEnd.invoke(*this, *colliding[i]);
			}

			colliding.erase(colliding.begin() + i);
			i--;
		}
	}
}

