#pragma once

#include <SFML\Graphics\Drawable.hpp>

#include <memory>

class GameObject;

class Component : public sf::Drawable, public std::enable_shared_from_this<Component>
{
public:

	explicit Component(std::weak_ptr<GameObject> p) : parent(p) {}

	virtual void update(float dt) = 0;

	std::shared_ptr<GameObject> getParent() const;

	virtual ~Component() = default;
protected:

	virtual void draw(sf::RenderTarget& target, sf::RenderStates state) const override {}

private:

	std::weak_ptr<GameObject> parent;
};

inline std::shared_ptr<GameObject> Component::getParent() const
{
	if (parent.expired())
	{
		//TODO throw exception
	}
	return parent.lock();
}
