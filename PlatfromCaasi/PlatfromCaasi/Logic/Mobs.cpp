#include "Mobs.h"
#include "Character.h"
#include "../Platfrom.h"
#include "../hmi/Inputs.h"

namespace platfrom
{
	namespace logic
	{
		namespace mobs
		{
#pragma region BaseMob 
			SimpleMob::SimpleMob(const sf::Vector2f pos, const std::vector<sf::Vector3f>& circles, bool goRightFirst)
			{
				_goRight = goRightFirst;
				_hitBox = new hitBoxes::SphericalHitBox(circles);
				_acc = sf::Vector2f(0, simplePhysics::GRAVITY);
				_skin.setSize({ circles.front().z, circles.front().z });
				_skin.setOrigin(_skin.getSize() / 2.f);
				_skinScale = { _skin.getSize().x / 4.f,  _skin.getSize().y / 4.f };
				_skin.setScale(_skinScale);
				_usualMaxVel = 15;
				setPos(pos);
			}
			SimpleMob::SimpleMob(const sf::Vector2f pos, bool goRightFirst): SimpleMob(pos, { {0,0,15.f} }, goRightFirst)
			{
			}
			SimpleMob::SimpleMob(std::ifstream& is, const std::vector<sf::Vector3f>& circles)
			{
				_hitBox = new hitBoxes::SphericalHitBox(circles);
				_acc = sf::Vector2f(0, simplePhysics::GRAVITY);
				_skin.setSize({ circles.front().z, circles.front().z });
				_skin.setOrigin({ _skin.getSize() / 2.f });
				_skinScale = { _skin.getSize().x / 4.f,  _skin.getSize().y / 4.f };
				_skin.setScale(_skinScale);
				_usualMaxVel = 15;
				is >> _goRight >> _pos;
			}
			SimpleMob::SimpleMob(std::ifstream& is) :SimpleMob(is, { {0,0,15.f} })
			{
			}
			std::ostream& SimpleMob::serialize(std::ostream& os) const
			{
				return os 
					<< typeid(*this).name() << " "
					<< _goRight << " "
					<< _pos
					<< std::endl;
			}
			Entity& SimpleMob::feature()
			{
				if (_alive)
				{
					if (_goRight)
					{
						if (_vel.x < _maxVel)
							_acc.x = _maxAcc;
						else
						{
							_vel.x = _maxVel;
							_acc.x = 0;
						}
					}
					else
					{
						if (_vel.x > -_maxVel)
							_acc.x = -_maxAcc;
						else
						{
							_vel.x = -_maxVel;
							_acc.x = 0;
						}
					}
				}
				else
				{
					// to do wait then desapear 
				}
				return *this;
			}
			Entity& SimpleMob::drawEntity(sf::RenderWindow& window, const sf::Vector2f refPos)
			{
				if (Platfrom::getConfig().getShowHitboxes())
					_hitBox->draw(window, _pos - refPos);
				_skin.setPosition(_pos - refPos);
				if (_goRight)
					_skin.setScale(_skinScale);
				else
					_skin.setScale({-_skinScale.x,  _skinScale.y});
				_skin.setTexture(Platfrom::getTexture().BlueEnemy());
				window.draw(_skin);
				return *this;

			}
			bool SimpleMob::hit(Entity& hitting, sf::Vector2f collision)
			{

				if (_alive || !dynamic_cast<PersonifiedEntity*>(&hitting))
				{
					bool isHard = Entity::hit(hitting, collision);
					if (isHard && (collision.x > -collision.y || collision.x < collision.y))
					{
						if (collision.x > 0)
							_goRight = true;
						else if (collision.x < 0)
							_goRight = false;
					}
					return isHard;
				}
				return false;

			}
			bool SimpleMob::getReaction(Entity& hitting, sf::Vector2f collision)
			{
				if (_alive )
				{
					hitting.setNextPos(hitting.getNextPos() + (collision * 0.5f));
					_nextPos -= (collision * 0.5f);

					auto* player = dynamic_cast<Character*>(&hitting);
					if (player
						&& -collision.x >= collision.y
						&& collision.x >= collision.y)
					{
						_alive = false;
						_skinScale = { _skinScale.x,_skinScale.y/2.f };
						_skin.setOrigin({ _skin.getSize().x / 2.f, 0 });
						_acc.x = 0;
						_vel = { 0,0 };

						if (Platfrom::getInputs().jump())
							player->setNextVel({ player->getNextVel().x , -player->getNextVel().y });
						else
							player->setNextVel({ player->getNextVel().x , -20.f });
					}
					else if (player)
						player->kill();

					hitting.setNextVel({
					0 <= collision.x * hitting.getNextVel().x ?
						hitting.getNextVel().x :
						_vel.x / 2  ,
					0 <= collision.y * hitting.getNextVel().y ?
						hitting.getNextVel().y :
						_vel.y / 2 });
				}
				return _alive;
			}
#pragma endregion
#pragma region PortableMob
			PortableMob::PortableMob(sf::Vector2f pos, bool goRightFirst) : SimpleMob(pos, { {0.f ,0.f, 12.f} }, goRightFirst)
			{
			}
			PortableMob::PortableMob(std::ifstream& is) :SimpleMob(is, { {0,0,12.f} })
			{
			}
			Entity& PortableMob::drawEntity(sf::RenderWindow& window, const sf::Vector2f refPos)
			{
				if (Platfrom::getConfig().getShowHitboxes())
					_hitBox->draw(window, _pos - refPos);
				_skin.setPosition(_pos - refPos);
				if (_goRight)
					_skin.setScale(_skinScale);
				else
					_skin.setScale({ -_skinScale.x,  _skinScale.y });
				if (Platfrom::getConfig().getShowHitboxes())
					_hitBox->draw(window, _pos - refPos);
				_skin.setPosition(_pos - refPos);
				if (_alive)
					_skin.setTexture(Platfrom::getTexture().RedEnemy());
				else
					_skin.setTexture(Platfrom::getTexture().GreenEnemy());
				window.draw(_skin);
				return *this;
			}
			bool PortableMob::hit(Entity& hitting, sf::Vector2f collision)
			{
				bool isHard = false;
				if  ( _alive 
					|| !_carried
					|| !dynamic_cast<Character*>(&hitting))
				{
					isHard = Entity::hit(hitting, collision);
					if (isHard && (collision.x > -collision.y || collision.x < collision.y))
					{
						if (collision.x > 0)
							_goRight = true;
						else if (collision.x < 0)
							_goRight = false;
					}
				}
				return isHard;
			}
			bool PortableMob::getReaction(Entity& hitting, sf::Vector2f collision)
			{
				auto* player = dynamic_cast<Character*>(&hitting);
				if (!_alive
					&& !_carried
					&& Platfrom::getInputs().secondAction()
					&& player)
					{
						player->addToCarriedCollection(this);
						_carried = true;
					}
				else if (!_carried)
				{
					hitting.setNextPos(hitting.getNextPos() + (collision * 0.5f));
					_nextPos -= (collision * 0.5f);
					if (_alive 
						&& player
						&& -collision.x >= collision.y
						&& collision.x >= collision.y)
					{
						_alive = false;
						_acc.x = 0;
						_vel = { 0,0 };

						if (Platfrom::getInputs().jump())
							player->setNextVel({ player->getNextVel().x , -player->getNextVel().y });
						else
							player->setNextVel({ player->getNextVel().x , -20.f });
					}
					else if (_alive && player)
						player->kill();

					if (0 >= collision.x* (hitting.getNextVel().x - _vel.x))
					{
						sf::Vector2f memVel = { _vel.x * 0.5f,hitting.getNextVel().y };
						_vel.x = hitting.getVel().x * 0.5f;
						hitting.setNextVel(memVel);
					}
					if (0 >= collision.y * (hitting.getNextVel().y - _vel.y))
					{
						sf::Vector2f memVel = { hitting.getNextVel().x,_vel.y * 0.5f };
						_vel.y = hitting.getVel().y * 0.5f;
						hitting.setNextVel(memVel);
					}
				}
				return true;
			}
			void PortableMob::carry(sf::Vector2f newPosition)
			{
				_pos = newPosition;
				_vel = { 0,0 };
			}
			void PortableMob::fling(sf::Vector2f thrownVec)
			{
				_vel = thrownVec;
				_carried = false;
			}
#pragma endregion
		}
	}
}