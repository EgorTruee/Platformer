#pragma once

#include <SFML\Graphics\Drawable.hpp>
#include <SFML\System\Clock.hpp>
#include <SFML\System\Time.hpp>

#include <vector>
#include <memory>
#include <optional>

class GameObject;
class ColliderComp;

class Scene final : public sf::Drawable 
{
public:

	explicit Scene(bool paused = true);
	Scene(const Scene& other) = default;
	Scene(Scene&& other) = default;

	Scene& operator=(const Scene& other) = default;
	Scene& operator=(Scene&& other) = default;

	void update();
	void start();
	void stop();
	std::optional<float> rayCast(sf::Vector2f begin, sf::Vector2f end);

	void addObject(std::shared_ptr<GameObject> object);

	sf::Time getTime();
	
	void removeObject(std::shared_ptr<GameObject> object);

protected:

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:

	void collisionUpdate();

	std::vector<std::shared_ptr<GameObject>> objects;
	std::vector<std::weak_ptr<ColliderComp>> colliderComponents;
	sf::Clock clock;
	sf::Time gameTime;
	bool paused;
};

inline void Scene::start()
{
	clock.restart();

	paused = false;
}

inline void Scene::stop()
{
	paused = true;
}

inline sf::Time Scene::getTime()
{
	return gameTime;
}
