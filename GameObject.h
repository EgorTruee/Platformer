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

	std::vector<std::shared_ptr<Component>> getComponents() const;

	void addComponent(std::shared_ptr<Component> component);

	virtual void update(float delta);

	virtual ~GameObject() = default;

protected:

	virtual void draw(sf::RenderTarget& target, sf::RenderStates state) const override;

private:

	std::vector<std::shared_ptr<Component>> components;
};
 
inline std::vector<std::shared_ptr<Component>> GameObject::getComponents() const
{
	return components;
}

inline void GameObject::addComponent(std::shared_ptr<Component> component)
{
	components.push_back(component);
}
