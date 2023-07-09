#include "Blocks.h"
#include "BlockDecorators.h"
#include "Entity.h"
#include "HitBox.h"
#include "Physics.h"
#include "../Platfrom.h"
#include <SFML/Graphics.hpp>

namespace platfrom
{
	namespace logic
	{
		namespace blocks
		{
#pragma region Block
#pragma region Constructors
			Block::Block(sf::Vector2f pos, std::vector<sf::Vector2f> points, int matter ,const std::vector<decorators::Decoration*> &decoratorsCollection) : Entity()
			{
				_pos = pos; 
				_matter = matter;
				_hitBox = _castedHitbox = new hitBoxes::ConvexPolygonHitBox(points);
				_decoratorsCollection = decoratorsCollection;
			}
			Block::Block(std::ifstream& is)
			{
				is >> _pos
					>> _matter;

				int nb;
				is >> nb; 
				std::vector<sf::Vector2f> points;
				for (int i = 0; i < nb; i++)
				{
					sf::Vector2f newPoint(0, 0);
					is >> newPoint.x >> newPoint.y;
					points.push_back(newPoint);
				}
				_hitBox = _castedHitbox = new hitBoxes::ConvexPolygonHitBox(points);

				is >> nb;
				for (int i = 0; i < nb; i++)
				{
					std::string type;
					std::string name;
					std::string fullname;
					is >> type >> name;
					fullname = type + " " + name;
					if (fullname == typeid(decorators::Simple).name())
						_decoratorsCollection.push_back(new decorators::Simple);
					else if (fullname == typeid(decorators::OneWay).name())
						_decoratorsCollection.push_back(new decorators::OneWay);
					else if (fullname == typeid(decorators::Ice).name())
						_decoratorsCollection.push_back(new decorators::Ice);
					else if (fullname == typeid(decorators::Bouncing).name())
						_decoratorsCollection.push_back(new decorators::Bouncing);
					else if (fullname == typeid(decorators::Lader).name())
						_decoratorsCollection.push_back(new decorators::Lader);
					else if (fullname == typeid(decorators::Moving).name())
						_decoratorsCollection.push_back(new decorators::Moving(is));
					else if (fullname == typeid(decorators::Web).name())
						_decoratorsCollection.push_back(new decorators::Web);
					else if (fullname == typeid(decorators::Hurting).name())
						_decoratorsCollection.push_back(new decorators::Hurting);
					else if (fullname == typeid(decorators::Finish).name())
						_decoratorsCollection.push_back(new decorators::Finish);
					else
						int error = 0;
				}

			}
			Block::~Block()
			{
				for (const decorators::Decoration* deco : _decoratorsCollection)
				{
					delete(deco);
				}
				_decoratorsCollection.clear();
			}
#pragma endregion
#pragma region Public Methods
			bool Block::getReaction(Entity& hitting, sf::Vector2f collision)
			{
				for (decorators::Decoration* decoration : _decoratorsCollection)
				{
					decoration->posReaction(hitting, *this, collision);
					decoration->velReaction(hitting, *this, collision);
					decoration->otherReaction(hitting, *this, collision);
				}
				return true;
			}
			Entity& Block::feature()
			{
				for (decorators::Decoration* decoration : _decoratorsCollection)
				{
					decoration->decoFeature(*this);
				}
				return *this;
			}
			std::ostream& Block::serialize(std::ostream& os) const
			{
				os << typeid(*this).name() << " "
					<< _pos 
					<< _matter << " ";

				hitBoxes::ConvexPolygonHitBox* polygon = dynamic_cast<hitBoxes::ConvexPolygonHitBox*>(_hitBox);
				os << std::endl << polygon->getNumber() << std::endl;
				for (unsigned int i = 0; i < polygon->getNumber(); i++)
				{
					os <<  polygon->getRelPointPos(i);
				}
				os << std::endl << _decoratorsCollection.size() << std::endl;
				for (int i = 0; i < _decoratorsCollection.size(); i++)
				{
					os << *_decoratorsCollection[i];
				}

				return os;
			}
			Entity& Block::drawEntity(sf::RenderWindow& window, const sf::Vector2f refPos)
			{	
				bool notExistingMatter = false;
				switch (_matter)
				{
				case matter::Dirt:
					_castedHitbox->drawAsBlock(
						window,
						_pos - refPos,
						Platfrom::getTexture().Dirt(),
						Platfrom::getTexture().Grass()
					);
					break;
				case matter::Ice:
					_castedHitbox->drawAsBlock(
						window, 
						_pos - refPos, 
						Platfrom::getTexture().Ice(),
						Platfrom::getTexture().IceUp());
					break;
				case matter::Lader:
					_castedHitbox->drawAsBlock(
						window, 
						_pos - refPos, 
						Platfrom::getTexture().Lader(),
						Platfrom::getTexture().None()
					);
					break;
				case matter::Stone:
					_castedHitbox->drawAsBlock(
						window, 
						_pos - refPos, 
						Platfrom::getTexture().Stone(),
						Platfrom::getTexture().StoneUp());
					break;
				case matter::Web:
					_castedHitbox->drawAsBlock(
						window, 
						_pos - refPos, 
						Platfrom::getTexture().Web(),
						Platfrom::getTexture().None());
					break;
				case matter::Finish:
					_castedHitbox->drawAsBlock(
						window, 
						_pos - refPos, 
						nullptr,
						nullptr);
					break;
				case matter::None:
					_castedHitbox->drawAsBlock(
						window, 
						_pos - refPos, 
						Platfrom::getTexture().None(),
						Platfrom::getTexture().None());
					break;
				default:
					notExistingMatter = true;
				}
				if (notExistingMatter 
					|| Platfrom::getConfig().getShowHitboxes())
					_hitBox->draw(window, _pos - refPos);
				return *this;
			}
#pragma endregion
#pragma endregion
		}
	}
}