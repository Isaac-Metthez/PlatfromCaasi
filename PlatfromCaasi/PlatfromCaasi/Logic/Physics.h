#pragma once
#include <SFML/Graphics.hpp>

namespace platfrom
{
	namespace	logic
	{
	namespace simplePhysics
	{
	#pragma region Constants
		constexpr double GRAVITY = 10;
		constexpr double MAXTIME = 10000000;
		constexpr double TIMEDIVIDOR = 100000000;
	#pragma endregion	
	#pragma region Class
		/**
		 * Class Simplekinematics
		 *
		 * Simplekinematics part of the physics related to speed, accelaration etc...
		 */
		class Simplekinematics
		{
		protected:
			static double _dtime;
		public:
			static double getdtime() { return _dtime;};
			static void setdtime(double dtime) { _dtime = dtime; };
			static sf::Vector2f position(const sf::Vector2f &p0 , const sf::Vector2f &v);
			static sf::Vector2f velocity(const sf::Vector2f &v0 , const sf::Vector2f &a);
		};
	#pragma endregion	
	}

	}

}

