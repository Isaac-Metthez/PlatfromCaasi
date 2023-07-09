#include "Physics.h"
#include <SFML/Graphics.hpp>

namespace platfrom
{
	namespace	logic
	{
		namespace simplePhysics
		{
#pragma region Simplekinematics 
#pragma region Public Methods

#pragma endregion
#pragma region Public Methods
			double Simplekinematics::_dtime = 0;
			sf::Vector2f Simplekinematics::position(const sf::Vector2f& p0, const sf::Vector2f& v)
			{
				// p1 = p0 + v*t
				return p0 + sf::Vector2f(v.x * (float)_dtime, v.y * (float)_dtime);
			}
			sf::Vector2f Simplekinematics::velocity(const sf::Vector2f& v0, const sf::Vector2f& a)
			{
				// v1 = v0 + a*t
				return v0 + sf::Vector2f(a.x * (float)_dtime, a.y * (float)_dtime);
			}
#pragma endregion
#pragma endregion
		}
	}
}