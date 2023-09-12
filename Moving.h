#pragma once
#include "GameObject.h"

class Moving : public GameObject
{
public:

	virtual void start() override;
	virtual void update(float delta) override;
	virtual std::vector<const sf::Drawable*> getDrawable() override;
private:
};

