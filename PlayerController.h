#pragma once

#include "Controller.h"

#include <unordered_map>

class PlayerController;
enum Key;

std::shared_ptr<PlayerController> getPlayerController();

class PlayerController : public Controller
{
public:

	friend std::shared_ptr<PlayerController> getPlayerController();

	std::unordered_map<Key, std::string> getButtonBindings() const;
	std::unordered_map<Key, std::pair<std::string, float>> getAxisBindings() const;

	void changeButtonBindings(Key key, std::string buttonName);
	void changeAxisBindings(Key key, std::string axisName, float value);

	void update();

private:

	PlayerController() {}
	PlayerController(const PlayerController& other) = delete;
	PlayerController(PlayerController&& other) = delete;
	
	std::unordered_map<Key, std::string> buttonBindings;
	std::unordered_map<Key, std::pair<std::string, float>> axisBindings;
};
