#include "GameObject.h"

GameObject::GameObject() :
	pos(0, 0),
	angle(0)
{
}

void GameObject::setPosition(sf::Vector2f position)
{
	pos = position;
}

void GameObject::setAngle(float phi)
{
	angle = phi;
}

sf::Vector2f GameObject::getPosition()
{
	return pos;
}

float GameObject::getAngel()
{
	return angle;
}
