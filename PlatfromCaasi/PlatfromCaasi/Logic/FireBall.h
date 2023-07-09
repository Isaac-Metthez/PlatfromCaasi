#pragma once
#include "Entity.h"
#include "Portable.h"
#include "HitBox.h"
#include "Character.h"
#include "../Platfrom.h"
#include "../HMI/Inputs.h"
#include <fstream>

namespace platfrom
{
	namespace logic
	{
		/**
		 * Class Fireball
		 *
		 * Fireball are portable also character can carry and throw them.
		 */
		class FireBall : public Entity, public Portable
		{
		public:
			FireBall(sf::Vector2f pos);
			FireBall(std::ifstream& is);
			Entity& drawEntity(sf::RenderWindow& window, const sf::Vector2f refPos = { 0,0 }) override;
			bool isOnView(const sf::View& view) override;
			bool hit(Entity& hitting, sf::Vector2f collision);
			bool getReaction(Entity& hitting, sf::Vector2f collision) override;
			void fling(sf::Vector2f thrownVec) override;
			void carry(sf::Vector2f newPosition) override;
			std::ostream& serialize(std::ostream& os) const override;
		protected:
			bool _thrown = false;
			Character* _owner = nullptr;
			sf::RectangleShape _skin;
		};
	}

}