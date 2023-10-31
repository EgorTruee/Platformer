#pragma once

#include <SFML\Graphics\Drawable.hpp>

#include <memory>
#include <type_traits>

class GameObject;

class Component : public sf::Drawable, public std::enable_shared_from_this<Component>
{
public:

	explicit Component() {}

	virtual void update(float dt) = 0;

	std::shared_ptr<GameObject> getParent() const;

	void setParent(std::weak_ptr<GameObject> p);

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

inline void Component::setParent(std::weak_ptr<GameObject> p)
{
	parent = p;
}

Component selector(...);

template<typename T, typename Base, typename ...Args>
std::shared_ptr<T> createComponentImpl(Args&&... args)
{
	std::shared_ptr<T> res = std::make_shared<T>(std::forward<Args>(args)...);

	return res;
}

template<typename T, typename ...Args>
std::shared_ptr<T> createComponent(Args&&... args)
{
	static_assert(std::is_base_of_v<Component, T>, "Must be inhereted from component");

	return createComponentImpl<T, decltype(selector(reinterpret_cast<T*>(nullptr)))>(std::forward<Args>(args)...);
}
