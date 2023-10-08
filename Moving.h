#pragma once
#include "GameObject.h"

class Moving : public GameObject
{
public:

	Moving(const Collision& collision);

	virtual void update(float dt) override;
};

