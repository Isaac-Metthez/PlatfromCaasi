#include "Blocks.h"
#include "BlockDecorators.h"
#include "Entity.h"
#include "PersonifiedEntity.h"
#include "HitBox.h"
#include "Physics.h"
#include "../Platfrom.h"
#include "Physics.h"
#include <SFML/Graphics.hpp>

namespace platfrom
{
	namespace logic
	{
		namespace blocks
		{
			namespace decorators
			{
#pragma region Decoration
				void Decoration::posReaction(Entity& hitting, Entity& super, sf::Vector2f collision)
				{
				}
				void Decoration::velReaction(Entity& hitting, Entity& super, sf::Vector2f collision)
				{
				}
				void Decoration::otherReaction(Entity& hitting, Entity& super, sf::Vector2f collision)
				{
				}
				void Decoration::decoFeature(Entity& super)
				{
				}
				std::ostream& Decoration::serialize(std::ostream& os) const
				{
					return os << typeid(*this).name() << " ";
				}
#pragma endregion
#pragma region Simple
				void Simple::posReaction(Entity& hitting, Entity& super, sf::Vector2f collision)
				{
					hitting.setNextPos(hitting.getNextPos() + collision);
				}
				void Simple::velReaction(Entity& hitting, Entity& super, sf::Vector2f collision)
				{
					sf::Vector2f projection = collision * static_cast<float>((collision.x * hitting.getNextVel().x + collision.y * hitting.getNextVel().y)/(pow(collision.x, 2) + pow(collision.y, 2)));

					sf::Vector2f velCorrection = simplePhysics::Simplekinematics::velocity(hitting.getNextVel(), -10.f*projection);
    					hitting.setNextVel({
						0 <= collision.x * hitting.getNextVel().x ? 
							hitting.getNextVel().x : 
							velCorrection.x + super.getVel().x ,
						0 <= collision.y * hitting.getNextVel().y ?
							hitting.getNextVel().y : 
							velCorrection.y + super.getVel().y });
				}
#pragma endregion
#pragma region OneWay
				void OneWay::posReaction(Entity& hitting, Entity& super, sf::Vector2f collision)
				{
					if ((collision.y < 0 && hitting.getNextVel().y > 0)
						|| (collision.y < 0 && super.getNextVel().y < 0))
						hitting.setNextPos({ hitting.getNextPos().x, hitting.getNextPos().y + collision.y });
				}
				void OneWay::velReaction(Entity& hitting, Entity& super, sf::Vector2f collision)
				{
					if ((collision.y < 0 && hitting.getNextVel().y > 0)
						|| (collision.y < 0 && super.getNextVel().y < 0))
					{
						sf::Vector2f projection = collision * static_cast<float>((collision.x * hitting.getNextVel().x + collision.y * hitting.getNextVel().y) / (pow(collision.x, 2) + pow(collision.y, 2)));

						sf::Vector2f velCorrection = simplePhysics::Simplekinematics::velocity(hitting.getNextVel(), -10.f * projection);
						hitting.setNextVel({
						0 <= collision.x * hitting.getNextVel().x ?
							hitting.getNextVel().x :
							velCorrection.x + super.getVel().x ,
						0 <= collision.y * hitting.getNextVel().y ?
							hitting.getNextVel().y :
							velCorrection.y + super.getVel().y });
					}
				}
#pragma endregion
#pragma region Bouncing
				void Bouncing::velReaction(Entity& hitting, Entity& super, sf::Vector2f collision)
				{
					if (collision.y < 0 && collision.x > collision.y && -collision.x > collision.y)
					{
						if (Platfrom::getInputs().jump())
							hitting.setNextVel(sf::Vector2f( 0.f, -100.f ));
						else
							hitting.setNextVel(sf::Vector2f( 0.f,-75.f ));
					}
				}
#pragma endregion
#pragma region Moving
				Moving::Moving( sf::Vector2f endRelPos): Moving(endRelPos, 20.f)
				{
				}
				Moving::Moving(std::ifstream& filein)
				{
					filein >> _maxPos >> _velocity;
				}
				Moving::Moving(sf::Vector2f endRelPos, float velocity)
				{
					_maxPos = endRelPos;

					float normVel = static_cast<float>(sqrt(pow(endRelPos.x, 2) + pow(endRelPos.y, 2)));
					_velocity = (endRelPos / normVel) * velocity;
				}
				void Moving::decoFeature(Entity& super)
				{
					if (!_posSet)
					{
						_posSet = true;
						_minPos = super.getPos();
						if (_maxPos.x < 0)
						{
							_minPos.x += _maxPos.x;
							_maxPos.x = -_maxPos.x;
						}
						if (_maxPos.y < 0)
						{
							_minPos.y += _maxPos.y;
							_maxPos.y = -_maxPos.y;
						}
					}

					sf::Vector2f relPos = super.getPos() - _minPos;
					if ((relPos.x > _maxPos.x || relPos.x < 0) 
						|| (relPos.y > _maxPos.y || relPos.y < 0))
					{
						if (!_changeDirection)
						{
							_velocity = -_velocity;
						}
						_changeDirection = true;
					}
					else
						_changeDirection = false;
					super.setVel(_velocity);
				}
				void Moving::posReaction(Entity& hitting, Entity& super, sf::Vector2f collision)
				{
					hitting.setNextPos(
						simplePhysics::Simplekinematics::position(
							hitting.getNextPos(), sf::Vector2f(super.getVel().x, 0)));
				}

				std::ostream& Moving::serialize(std::ostream& os) const
				{
					return os << typeid(*this).name() << " "
						<< _maxPos
						<< _velocity;
				}

#pragma endregion
#pragma region Ice
				void Ice::otherReaction(Entity& hitting, Entity& super, sf::Vector2f collision)
				{
					PersonifiedEntity* personifiedEntity = dynamic_cast<PersonifiedEntity*>(&hitting);
					if (personifiedEntity)
					{
						personifiedEntity->setMaxAcc(3);
					}
				}
#pragma endregion
#pragma region Sticky
				void Web::velReaction(Entity& hitting, Entity& super, sf::Vector2f collision)
				{
					PersonifiedEntity* personifiedEntity = dynamic_cast<PersonifiedEntity*>(&hitting);
					if (personifiedEntity)
					{
						hitting.setNextVel({ 
							hitting.getNextVel().x > 3 || hitting.getNextVel().x < -3 ? hitting.getNextVel().x * 0.9f : hitting.getNextVel().x ,
							hitting.getNextVel().y > 3 || hitting.getNextVel().y < -3 ? hitting.getNextVel().y * 0.9f : hitting.getNextVel().y });
					}
				}
#pragma endregion
#pragma region Lader
				Lader::Lader() : _onLaderVelocity({0.f,20.f})
				{}
				void Lader::posReaction(Entity& hitting, Entity& super, sf::Vector2f collision)
				{
					if (dynamic_cast<Character*>(& hitting))
					{
						if (Platfrom::getInputs().up())
							hitting.setNextPos(simplePhysics::Simplekinematics::position(hitting.getNextPos(), -_onLaderVelocity));
						if (Platfrom::getInputs().down())
							hitting.setNextPos(simplePhysics::Simplekinematics::position(hitting.getNextPos(), _onLaderVelocity));
					}
				}
				void Lader::velReaction(Entity& hitting, Entity& super, sf::Vector2f collision)
				{
					if (dynamic_cast<Character*>(&hitting))
					{
						if (Platfrom::getInputs().up() || Platfrom::getInputs().down())
							hitting.setNextVel({ hitting.getNextVel().x + super.getVel().x, super.getVel().y });
					}
				}
#pragma endregion
#pragma region Hurting
				void Hurting::otherReaction(Entity& hitting, Entity& super, sf::Vector2f collision)
				{
					PersonifiedEntity* personified = dynamic_cast<PersonifiedEntity*>(&hitting);
					if (personified)
						personified->kill();
				}
#pragma endregion
#pragma region Finish
				void Finish::otherReaction(Entity& hitting, Entity& super, sf::Vector2f collision)
				{
					Character* character = dynamic_cast<Character*>(&hitting);
					if (character)
						character->setFinish(true);
				}
#pragma endregion
			}
		}
	}
}