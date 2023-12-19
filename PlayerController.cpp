#include "PlayerController.h"

#include <SFML/Window/Keyboard.hpp>

std::shared_ptr<PlayerController> getPlayerController()
{
    static std::shared_ptr<PlayerController> instance(nullptr);

    if (!instance)
    {
        instance = std::make_shared<PlayerController>();
    }
    return instance;
}

void PlayerController::update()
{
}
