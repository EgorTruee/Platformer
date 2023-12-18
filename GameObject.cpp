#include "GameObject.h"
#include "Component.h"

#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

GameObject::GameObject(const std::string& objectName, sf::Vector2f vel, sf::Vector2f acc) : 
	name(objectName),
	components(),
	v(vel),
	a(acc)
{
}

inline void GameObject::update(float delta)
{
	for (auto i : components)
	{
		i->update(delta);
	}
	move(v * delta + a * (delta * delta / 2));

	v += a * delta;
}

void GameObject::initComponents()
{
	for (auto i : components)
	{
		i->setParent(weak_from_this());
	}
}

void GameObject::draw(sf::RenderTarget& target, sf::RenderStates state) const
{
	state.transform *= getTransform();
	
	for (auto i : components)
	{
		target.draw(*i, state);
	}
}
