#include "Scene.h"

#include <SFML\Graphics\RenderTarget.hpp>

#include "GameObject.h"
#include "ColliderComp.h"
#include "TestObject.h"

Scene::Scene(bool p) :
	paused(p)
{
	addObject(createGameObject<TestObject>(sf::Vector2f(0, 0), sf::Vector2f(10, 10)));
	addObject(createGameObject<TestObject>(sf::Vector2f(100, 100), sf::Vector2f(0, 0)));
}

void Scene::update()
{
	if (paused)
	{
		return;
	}
	sf::Time dt = clock.getElapsedTime();

	clock.restart();

	gameTime += dt;

	collisionUpdate();

	for (auto i : objects)
	{
		i->update(dt.asSeconds());
	}
}

void Scene::addObject(std::shared_ptr<GameObject> object)
{
	objects.push_back(object);

	for (auto i : object->getComponents())
	{
		std::shared_ptr<ColliderComp> collider = std::dynamic_pointer_cast<ColliderComp>(i);

		if (collider)
		{
			colliderComponents.push_back(std::weak_ptr(collider));
		}
	}
}

void Scene::removeObject(std::shared_ptr<GameObject> object)
{
	auto iter = std::find(objects.begin(), objects.end(), object);

	if (iter != objects.end())
	{
		objects.erase(iter);
	}
}

void Scene::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	for (auto i : objects)
	{
		target.draw(*i, states);
	}
}

void Scene::collisionUpdate()
{
	for (int i = 0; i < colliderComponents.size() - 1; i++)
	{
		if (colliderComponents[i].expired())
		{
			continue;
		}
		std::shared_ptr<ColliderComp> col1 = colliderComponents[i].lock();

		for (int j = i + 1; j < colliderComponents.size(); j++)
		{
			if (colliderComponents[j].expired())
			{
				continue;
			}
			std::shared_ptr<ColliderComp> col2 = colliderComponents[j].lock();

			if (col1->isIntersects(col2))
			{
				col1->onCollision(col2);
				col2->onCollision(col1);
			}
		}
	}
}
