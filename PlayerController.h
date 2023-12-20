#pragma once

#include "Controller.h"

#include <unordered_map>
#include <tuple>
#include <SFML/Window/Keyboard.hpp>

class PlayerController;

std::shared_ptr<PlayerController> getPlayerController();

class PlayerController : public Controller
{
public:

	friend std::shared_ptr<PlayerController> getPlayerController();

	std::vector<std::pair<sf::Keyboard::Key, std::string>> getButtonBindings() const;
	std::vector<std::tuple<sf::Keyboard::Key, std::string, float>> getAxisBindings() const;

	void addButtonBinding(sf::Keyboard::Key key, const std::string& buttonName);
	void addAxisBinding(sf::Keyboard::Key key, const std::string& axisName, float value);
	void removeButtonBinding(const std::string& buttonName);
	void removeAxisBinding(const std::string& axisName);
	void changeButtonBinding(sf::Keyboard::Key key, const std::string& buttonName);
	void changeAxisBinding(sf::Keyboard::Key key, const std::string& axisName, float value);

	void update();

private:

	PlayerController();
	PlayerController(const PlayerController& other) = delete;
	PlayerController(PlayerController&& other) = delete;
	
	std::vector<std::pair<sf::Keyboard::Key, std::string>> buttonBindings;
	std::vector<std::tuple<sf::Keyboard::Key, std::string, float>> axisBindings;
};

inline std::vector<std::pair<sf::Keyboard::Key,std::string>> PlayerController::getButtonBindings() const
{
	return buttonBindings;
}

inline std::vector<std::tuple<sf::Keyboard::Key, std::string, float>> PlayerController::getAxisBindings() const
{
	return axisBindings;
}

inline void PlayerController::addButtonBinding(sf::Keyboard::Key key, const std::string& buttonName)
{
	buttonBindings.emplace_back(key, buttonName);
}

inline void PlayerController::addAxisBinding(sf::Keyboard::Key key, const std::string& axisName, float value)
{
	axisBindings.emplace_back(key, axisName, value);
}

inline void PlayerController::removeButtonBinding(const std::string& buttonName)
{
	buttonBindings.erase(std::remove_if(
		buttonBindings.begin(),
		buttonBindings.end(),
		[&buttonName](const std::pair<sf::Keyboard::Key, std::string> p)
		{return p.second == buttonName; }),
		buttonBindings.end());
}

inline void PlayerController::removeAxisBinding(const std::string& axisName)
{
	axisBindings.erase(std::remove_if(
		axisBindings.begin(),
		axisBindings.end(),
		[&axisName](std::tuple<sf::Keyboard::Key, std::string, float> t)
		{return std::get<std::string>(t) == axisName; }),
		axisBindings.end());
}

inline void PlayerController::changeButtonBinding(sf::Keyboard::Key key, const std::string& buttonName)
{
	auto i = std::find_if(buttonBindings.begin(), buttonBindings.end(), [&buttonName](std::pair<sf::Keyboard::Key, std::string> p) {return p.second == buttonName; });

	if (i == buttonBindings.end())
	{
		//TODO error

		return;
	}
	i->first = key;
}

inline void PlayerController::changeAxisBinding(sf::Keyboard::Key key, const std::string& axisName, float value)
{
	auto i = std::find_if(axisBindings.begin(), axisBindings.end(), [&axisName](std::tuple<sf::Keyboard::Key, std::string, float> t) {return std::get<std::string>(t) == axisName; });

	if (i == axisBindings.end())
	{
		//TODO error

		return;
	}
	std::get<sf::Keyboard::Key>(*i) = key;
	std::get<float>(*i) = value;
}

