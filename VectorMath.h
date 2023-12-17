#pragma once

#include <type_traits>
#include <math.h>

#include <SFML/System/Vector2.hpp>

template<typename T>
T operator*(const sf::Vector2<T>& lhs, const sf::Vector2<T>& rhs)
{
	return lhs.x * rhs.x + lhs.y * rhs.y;
}

template<typename T>
T squredLength(const sf::Vector2<T> a)
{
	return a.x * a.x + a.y * a.y;
}

template<typename T, std::enable_if_t<std::is_floating_point_v<T>, bool> = true>
T length(sf::Vector2<T> a)
{
	return sqrt(squredLength(a));
}
