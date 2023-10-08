#include "GameObject.h"
#include "Collision.h"

#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

GameObject::GameObject() :
	collision(std::make_shared<Collision>())
{
}

GameObject::GameObject(const Collision& collider) :
	collision(std::make_shared<Collision>(collider))
{
}

void GameObject::setPosition(sf::Vector2f position)
{
	collision->setPosition(position);
}

void GameObject::setRotation(float phi)
{
	collision->setRotation(phi);
}

sf::Vector2f GameObject::getPosition() const
{
	return collision->getPosition();
}

float GameObject::getRotation() const
{
	return collision->getRotation();
}

std::shared_ptr<Collision> GameObject::getCollision() const
{
	return collision;
}

void GameObject::draw(sf::RenderTarget& target, sf::RenderStates state) const
{
	state.transform *= collision->getTransform();

#ifdef _DEBUG

	std::vector<sf::Vector2f> points = collision->getPoints();
	sf::VertexArray arr(sf::LineStrip, points.size() + 1);

	for (int i = 0; i < points.size() + 1; i++)
	{
		arr[i].position = points[i % points.size()];
	}
	target.draw(arr, state);

#endif //_DEBUG
}
