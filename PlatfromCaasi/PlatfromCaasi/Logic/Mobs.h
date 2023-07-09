#pragma once
#include "PersonifiedEntity.h"
#include "Portable.h"
#include "../Serialize/Vector.h"
#include <fstream>

namespace platfrom
{
	namespace logic
	{
		namespace mobs
		{
			/**
			 * Class SimpleMob
			 *
			 * SimpleMob is a personnified entity who can be crushed by character (if fall on it),
			 * But hurt the character too, it depends on the direction of the collision.
			 */
			class SimpleMob: public PersonifiedEntity
			{
			public:
				SimpleMob(const sf::Vector2f pos, bool goRightFirst = false);
				SimpleMob(std::ifstream& is);
				Entity& feature() override;
				Entity& drawEntity(sf::RenderWindow& window, const sf::Vector2f refPos = { 0,0 }) override;
				virtual bool hit(Entity& hitting, sf::Vector2f collision) override;
				virtual bool getReaction (Entity& hitting, sf::Vector2f collision) override;
				std::ostream& serialize(std::ostream& os) const override;
			protected:
				SimpleMob(const sf::Vector2f pos, const std::vector<sf::Vector3f>& circles = { {0,0,15.f} }, bool goRightFirst = false);
				SimpleMob(std::ifstream& is, const std::vector<sf::Vector3f>& circles);
				bool _goRight = true;
				bool _alive = true;
				sf::RectangleShape _skin;
				sf::Vector2f _skinScale;
			};

			/**
			 * Class PortableMob
			 *
			 * PortableMob do almost the same as SimpleMob.
			 * But when knocked out you character can carry them. 
			 */
			class PortableMob : public Portable, public SimpleMob
			{
			public:
				PortableMob(sf::Vector2f pos, bool goRightFirst = false);
				PortableMob(std::ifstream& is);
				Entity& drawEntity(sf::RenderWindow& window, const sf::Vector2f refPos = { 0,0 }) override;
				bool hit(Entity& hitting, sf::Vector2f collision) override;
				bool getReaction(Entity& hitting, sf::Vector2f collision) override;
				void carry(sf::Vector2f newPosition) override;
				void fling(sf::Vector2f thrownVec) override;
			protected:
				bool _carried = false;
			};
		}
	}
}