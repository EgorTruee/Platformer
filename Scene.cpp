#include "Scene.h"

#include <SFML\Graphics\RenderTarget.hpp>

#include "GameObject.h"
#include "ColliderComp.h"

Scene::Scene(bool p) :
	paused(p)
{
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

std::weak_ptr<ColliderComp> Scene::rayCast(sf::Vector2f b1, sf::Vector2f e1)
{
	//TODO solve liniar system of eqasions and check its intersection for all collision components

	sf::Vector2f a1 = e1 - b1;
	std::pair<float, std::weak_ptr<ColliderComp>> res = { 2.f, std::weak_ptr<ColliderComp>() };

	for (auto i : colliderComponents)
	{
		if (i.expired())
		{
			continue;
		}
		std::shared_ptr<ColliderComp> ptr = i.lock();
		
		sf::Transform toGlobal = ptr->getParent()->getTransform() * ptr->getTransform();
		const std::vector<sf::Vector2f> points = ptr->getVertexes();

		for (int j = 0; j < points.size(); j++)
		{
			sf::Vector2f b2 = toGlobal * points[j % points.size()];
			sf::Vector2f a2 = toGlobal * points[(j + 1) % points.size()] - b2;

			float det1 = (b2.x - b1.x) * a2.y - (b2.y - b1.y) * a2.x;
			float det2 = a1.x * (b2.y - b1.y) - a1.y * (b2.x - b1.x);
			float detG = a1.x * a2.y - a1.y * a2.x;
			float t1 = det1 / detG;
			float t2 = det2 / detG;

			if (0 <= t1 && t1 <= 1 && 0 <= t2 && t2 <= 1)
			{
				if (t1 < res.first)
				{
					res.first = t1;
					res.second = i;
				}
			}
		}
	}
	return res.second;
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

			if (col1->checkCollision(col2))
			{
				col1->onCollision(col2);
				col2->onCollision(col1);
			}
		}
	}
}
