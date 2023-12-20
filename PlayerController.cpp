#include "PlayerController.h"

std::shared_ptr<PlayerController> getPlayerController()
{
    static std::shared_ptr<PlayerController> instance(nullptr);

    if (!instance)
    {
        instance = std::shared_ptr<PlayerController>(new PlayerController());
    }
    return instance;
}

void PlayerController::update()
{
    for (auto& i : buttonBindings)
    {
        buttons[i.second].setValue(sf::Keyboard::isKeyPressed(i.first));
    }
    for (auto& i : axisBindings)
    {
        axises[get<std::string>(i)].setValue((sf::Keyboard::isKeyPressed(get<sf::Keyboard::Key>(i)) ? get<float>(i) : axises[get<std::string>(i)].getValue()));
    }
}

PlayerController::PlayerController()
{}
