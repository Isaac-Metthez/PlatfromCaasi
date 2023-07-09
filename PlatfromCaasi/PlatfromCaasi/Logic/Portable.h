#pragma once
#include <SFML/Graphics.hpp>

namespace platfrom
{
	namespace logic
	{
		/**
		 * Class Portable
		 *
		 * Can be carried and thrown by Character.
		 */
		class Portable
		{
		public:
			virtual ~Portable() = default;
			virtual void fling(sf::Vector2f thrownVec)= 0;
			virtual void carry(sf::Vector2f newPosition) = 0;
		};
	}
}