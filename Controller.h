#pragma once

#include <string>
#include <unordered_map>

#include "Delegate.h"

class Controller
{
public:

	void subscribeOnAxisChange(const std::string& axisName, Listener<float> listener);
	void subscribeOnButtonChange(const std::string& buttonName, Listener<bool> listener);

	float getAxisValue(const std::string& axisName) const;
	bool getButtonValue(const std::string& buttonName) const;

protected:

	class Axis
	{
	public:

		Axis();
		Axis(const Axis& other) = delete;
		Axis(Axis&& other) = default;

		float getValue() const;
		std::string getName() const;

		void setValue(float value);

		Delegate<float> onChange;

	private:

		float value = 0;
	};
	class Button
	{
	public:

		Button();
		Button(const Button& other) = delete;
		Button(Button&& other) = default;

		bool getValue() const;

		void setValue(bool value);

		Delegate<bool> onChange;

	private:

		bool value = false;
	};
	std::unordered_map<std::string, Axis> axises;
	std::unordered_map<std::string, Button> buttons;
};

inline void Controller::subscribeOnAxisChange(const std::string& axisName, Listener<float> listener)
{
	axises.at(axisName).onChange.attach(listener);
}

inline void Controller::subscribeOnButtonChange(const std::string& buttonName, Listener<bool> listener)
{
	buttons.at(buttonName).onChange.attach(listener);
}

inline float Controller::getAxisValue(const std::string& axisName) const
{
	return axises.at(axisName).getValue();
}

inline bool Controller::getButtonValue(const std::string& buttonName) const
{
	return buttons.at(buttonName).getValue();
}

inline Controller::Axis::Axis() 
{}

inline float Controller::Axis::getValue() const
{
	return value;
}

inline void Controller::Axis::setValue(float newValue)
{
	onChange.invoke(newValue);

	value = newValue;
}

inline Controller::Button::Button()
{}

inline bool Controller::Button::getValue() const
{
	return value;
}

inline void Controller::Button::setValue(bool newValue)
{
	onChange.invoke(newValue);

	value = newValue;
}
