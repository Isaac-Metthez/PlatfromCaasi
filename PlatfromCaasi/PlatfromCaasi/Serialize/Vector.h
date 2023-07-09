#pragma once
#include <string>
#include <ostream>
#include "SFML/Graphics.hpp"
#include "Serializable.h"

/**
 * Add to sf::vector2 the property to be load from istream
 */
template <typename T>
std::istream& operator>>(std::istream& is, sf::Vector2<T>& vec)
{
	return is >> vec.x >> vec.y;
};
/**
 * Add to sf::vector3 the property to be load from istream
 */
template <typename T>
std::istream& operator>>(std::istream& is, sf::Vector3<T>& vec)
{
	return is >> vec.x >> vec.y >> vec.z;
};

/**
 * Add to sf::vector2 the property to be serialisable
 */
template <typename T>
std::ostream& operator<<(std::ostream& os,const sf::Vector2<T>& vec)
{
	return os
		<< vec.x << " "
		<< vec.y << " ";
};

/**
 * Add to sf::vector3 the property to be serialisable
 */
template <typename T>
std::ostream& operator<<(std::ostream& os,const sf::Vector3<T>& vec)
{
	return os 
		<< vec.x << " "
		<< vec.y << " "
		<< vec.z << " ";
};
