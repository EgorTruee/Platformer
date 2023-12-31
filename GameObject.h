#pragma once

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>

#include <vector>
#include <memory>
#include <type_traits>

class Component;

class GameObject : public sf::Drawable, public sf::Transformable, public std::enable_shared_from_this<GameObject>
{
public:

	explicit GameObject(sf::Vector2f v = { 0, 0 }, sf::Vector2f a = { 0, 0 });
	GameObject(const GameObject&) = default; 
	GameObject(GameObject&&) = default;

	virtual void update(float delta);
	void initComponents();

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
 
template<typename Object, typename ...Args>
std::shared_ptr<Object> createGameObject(Args&&... args)
{
	static_assert(std::is_base_of_v<GameObject, Object>, "Munst be inhereted from GameObject");

	std::shared_ptr<Object> res = std::make_shared<Object>(std::forward<Args>(args)...);

	res->initComponents();

	return res;
}
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
