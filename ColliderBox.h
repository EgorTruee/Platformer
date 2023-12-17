#pragma once
#include "ColliderComp.h"
class ColliderBox : public ColliderComp
{
public:

	explicit ColliderBox(sf::Vector2f sizeVector);
	ColliderBox(float height, float width);
	ColliderBox(const ColliderBox& other) = default;
	ColliderBox(ColliderBox&& other) = default;

	ColliderBox& operator=(const ColliderBox& other) = default;
	ColliderBox& operator=(ColliderBox&& other) = default;

	virtual bool isIntersects(std::shared_ptr<const ColliderComp> other) const override;
	virtual std::optional<float> isIntersects(sf::Vector2f begin, sf::Vector2f end) const override;
	virtual bool isInside(sf::Vector2f point) const override;

protected:

	virtual void draw(sf::RenderTarget& target, sf::RenderStates state) const override;

private:

	sf::Vector2f size;
};

