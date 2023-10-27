#include "GameObject.h"
#include "Component.h"

#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

GameObject::GameObject()
{
}

inline void GameObject::update(float delta)
{
	for (auto i : components)
	{
		i->update(delta);
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
