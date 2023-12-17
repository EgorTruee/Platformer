#pragma once

#include <string>

#include "Delegate.h"

class Controller
{
public:

	virtual void subscribeOnAxisChange(const std::string& axisName, Listener<float> listener) = 0;
	virtual void subscribeOnButtonChange(const std::string& buttonName, Listener<bool> listrner) = 0;

	virtual float getAxisValue(const std::string& axisName) const = 0;
	virtual bool getButtonValue(const std::string& buttonName) const = 0;
};

