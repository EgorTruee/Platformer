#include "ColliderBox.h"
#include "GameObject.h"

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/VertexArray.hpp>

ColliderBox::ColliderBox(const std::string& name, sf::Vector2f sizeVector) :
	ColliderComp(name),
	size(sizeVector)
{
}

ColliderBox::ColliderBox(const std::string& name, float height, float width) : 
	ColliderComp(name),
	size(width, height)
{
}

std::optional<CollisionInfo> ColliderBox::isIntersects(std::shared_ptr<const ColliderComp> other) const
{
	sf::Transform toGlobal = getParent()->getTransform() * getTransform();
	std::optional<CollisionInfo> res = (isInside(other->getParent()->getTransform() * other->getPosition()) ? CollisionInfo() : std::optional<CollisionInfo>());
	const int sgnx[4] = { -1, 1, 1, -1 };
	const int sgny[4] = { -1, -1, 1, 1 };
	const sf::Vector2f normals[4] = { {0, -1}, {1, 0}, {0, 1}, {-1, 0} };

	for (int i = 0; i < 4; i++)
	{
		sf::Vector2f b = { sgnx[i] * size.x / 2, sgny[i] * size.y / 2 };
		sf::Vector2f e = { sgnx[(i + 1) % 4] * size.x / 2, sgny[(i + 1) % 4] * size.y / 2 };
		std::optional<float> t = other->isIntersects(toGlobal * b, toGlobal * e);

		if (t.has_value())
		{
			res = CollisionInfo(normals[i]);
		}
	}
	return res;
}

std::optional<float> ColliderBox::isIntersects(sf::Vector2f begin, sf::Vector2f end) const
{
	std::optional<float> res;
	sf::Transform toLocal = getInverseTransform() * getParent()->getInverseTransform();
	sf::Vector2f b1 = toLocal * begin;
	sf::Vector2f a1 = toLocal * end - b1;
	const int sgnx[4] = { -1, 1, 1, -1 };
	const int sgny[4] = { -1, -1, 1, 1 };

	for (int i = 0; i < 4; i++)
	{
		sf::Vector2f b2 = { sgnx[i] * size.x / 2, sgny[i] * size.y / 2 };
		sf::Vector2f a2 = sf::Vector2f(sgnx[(i + 1) % 4] * size.x / 2, sgny[(i + 1) % 4] * size.y / 2) - b2;
		float det1 = -((b2.x - b1.x) * a2.y - (b2.y - b1.y) * a2.x);
		float det2 = a1.x * (b2.y - b1.y) - a1.y * (b2.x - b1.x);
		float detG = -(a1.x * a2.y - a1.y * a2.x);

		if (detG == 0)
		{
			continue;
		}
		float t1 = det1 / detG;
		float t2 = det2 / detG;

		if (0 <= t1 && t1 <= 1 && 0 <= t2 && t2 <= 1)
		{
			if (res.has_value())
			{
				*res = fminf(*res, t1);
			}
			else
			{
				res.emplace(t1);
			}
		}
	}
	return res;
}

bool ColliderBox::isInside(sf::Vector2f point) const
{
	sf::Vector2f p = getInverseTransform() * getParent()->getInverseTransform() * point;

	return fabsf(p.x) <= size.x / 2 && fabsf(p.y) <= size.y;
}

void ColliderBox::draw(sf::RenderTarget& target, sf::RenderStates state) const
{
#ifdef _DEBUG

	state.transform *= getTransform();

	sf::VertexArray arr(sf::LinesStrip, 5);
	const int sgnx[5] = { -1, 1, 1, -1, -1 };
	const int sgny[5] = { -1, -1, 1, 1, -1 };

	for (int i = 0; i < 5; i++)
	{
		arr[i].position = { sgnx[i] * size.x / 2, sgny[i] * size.y / 2 };
	}
	target.draw(arr, state);

#endif //_DEBUG
}
