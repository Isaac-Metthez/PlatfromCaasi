#pragma once
#include <SFML/Graphics.hpp>
#include "Entity.h"
#include "HitBox.h"
#include "BlockDecorators.h"
#include <vector>
#include <fstream>
#include "../Serialize/Vector.h"
#include "../HMI/Inputs.h"
#include "../HMI/Config.h"
namespace platfrom
{
	namespace logic
	{
		namespace blocks
		{
			namespace matter 
			{
				enum matter { None, Dirt, Ice, Stone, Lader, Web, Finish };
			}
			/**
			 * Class Block
			 *
			 * Blocks are used to construct a map
			 */
			class Block: public Entity
			{
			public:
				Block(sf::Vector2f pos, std::vector<sf::Vector2f> points, int matter ,const std::vector<decorators::Decoration*> &decoratorsCollection = {});
				Block(std::ifstream& is);
				~Block();
				virtual Entity& drawEntity(sf::RenderWindow& window, const sf::Vector2f refPos = { 0,0 }) override;
				virtual Entity& feature() override;
				virtual bool getReaction(Entity& hitting, sf::Vector2f collision) override;
				std::ostream& serialize(std::ostream& os) const override;
			protected: 
				int _matter = matter::None;
				std::vector<decorators::Decoration*> _decoratorsCollection;
				logic::hitBoxes::ConvexPolygonHitBox* _castedHitbox;
			};
		}
	}
}