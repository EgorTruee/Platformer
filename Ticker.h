#pragma once

#include <SFML\System\Clock.hpp>
#include <SFML\System\Time.hpp>

class Ticker
{
public:

	void zero();
	void tick();

	sf::Time getTimePerTick() const;
	float getTicksPerSecond() const;

private:

	sf::Clock clock;
	float tps = 0;
	unsigned int ticks = 0;
};

inline void Ticker::zero()
{
	clock.restart();

	ticks = 0;
}

inline void Ticker::tick()
{
	ticks++;

	if (clock.getElapsedTime().asSeconds() >= 1.0)
	{
		tps = static_cast<float>(ticks) / clock.getElapsedTime().asSeconds();
		ticks = 0;
		clock.restart();	
	}
}
inline sf::Time Ticker::getTimePerTick() const
{
	return sf::seconds(1.f / tps);
}

inline float Ticker::getTicksPerSecond() const
{
	return tps;
}

