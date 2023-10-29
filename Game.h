#pragma once

#include <vector>
#include <memory>

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/System/Clock.hpp>

class GameObject;

class Game : public sf::Drawable
{
public:

	Game();

	void start();
	void stop();
	void update();

	bool isPaused() { return paused; }

	~Game();

	template<class Object, typename ...Args>
	std::shared_ptr<Object> createGameObject(Args&&...);

protected:

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:

	void updateObjects(float dt);

	std::vector<std::shared_ptr<GameObject>> objects;
	sf::Time t1, t2;
	sf::Clock clock;
	bool paused;
};

template<class Object, typename ...Args>
inline std::shared_ptr<Object> Game::createGameObject(Args&&... args)
{
	std::shared_ptr<Object> t = std::make_shared<Object>(std::forward<Args>(args)...);

	t->initComponents();
	objects.push_back(t);

	return t;
}
