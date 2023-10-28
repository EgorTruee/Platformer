#pragma once

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>

#include <vector>
#include <memory>

class Component;

class GameObject : public sf::Drawable, public sf::Transformable
{
public:

	GameObject();
	GameObject(const GameObject&) = default;
	GameObject(GameObject&&) = default;

	virtual void update(float delta);

	std::vector<std::shared_ptr<Component>> getComponents() const;
	sf::Vector2f getVelocity() const;
	sf::Vector2f getAcceleration() const;

	void addComponent(std::shared_ptr<Component> component);
	void addVelocity(sf::Vector2f vel);
	void addAcceleration(sf::Vector2f acc);

	void setVelocity(sf::Vector2f vel);
	void setAcceleration(sf::Vector2f acc);

	virtual ~GameObject() = default;

protected:

	virtual void draw(sf::RenderTarget& target, sf::RenderStates state) const override;

private:

	std::vector<std::shared_ptr<Component>> components;
	sf::Vector2f v;
	sf::Vector2f a;
};
 
inline std::vector<std::shared_ptr<Component>> GameObject::getComponents() const
{
	return components;
}

inline sf::Vector2f GameObject::getVelocity() const
{
	return v;
}

inline sf::Vector2f GameObject::getAcceleration() const
{
	return a;
}

inline void GameObject::addComponent(std::shared_ptr<Component> component)
{
	components.push_back(component);
}

inline void GameObject::addVelocity(sf::Vector2f vel)
{
	v += vel;
}

inline void GameObject::addAcceleration(sf::Vector2f acc)
{
	a += acc;
}

inline void GameObject::setVelocity(sf::Vector2f vel)
{
	v = vel;
}

inline void GameObject::setAcceleration(sf::Vector2f acc)
{
	a = acc;
}
