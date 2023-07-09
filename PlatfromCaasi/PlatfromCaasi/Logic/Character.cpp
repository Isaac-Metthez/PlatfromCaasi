#include "Character.h"
#include "Physics.h"
#include "HitBox.h"
#include "PersonifiedEntity.h"
#include "../HMI/Inputs.h"
#include "../Platfrom.h"
#include <SFML/Graphics.hpp>
#include <algorithm>

namespace platfrom
{
	namespace logic
	{
#pragma region Entity 
#pragma region Operators overload
#pragma endregion
#pragma region Constructors
		Character::Character(sf::Window& window) : PersonifiedEntity(), _window(window)
		{
			_hitBox = new hitBoxes::SphericalHitBox({{0,10,10},{0,0,10},{-0,-10,10}});
			_acc = sf::Vector2f(0, simplePhysics::GRAVITY);
			_skin.setSize({ 15,15 });
			_skin.setOrigin(_skin.getSize() / 2.f);
			_skinScale = { _skin.getSize().x / 4.f,  _skin.getSize().y / 4.f }; 
			_skin.setScale(_skinScale);

			_skinIntRec.emplace_back(0, 0, 32, 32);
			_skinIntRec.emplace_back(32, 0, 32, 32);
			_skinIntRec.emplace_back(0, 32, 32, 32);
			_skinIntRec.emplace_back(32, 32, 32, 32);
			_skin.setTextureRect(_skinIntRec[0]);
		}
		Character::~Character()
		{
		}
#pragma endregion
#pragma region Public Methods
		Entity& Character::drawEntity(sf::RenderWindow& window, const sf::Vector2f refPos)
		{
			_skin.setPosition(_pos - refPos);
			if (_vel.x > 5)
				_skin.setScale(_skinScale);
			else if (_vel.x < -5)
				_skin.setScale({ -_skinScale.x,  _skinScale.y });

			if (_touchTheGround && (_vel.x > 1 || _vel.x < -1))
			{
				_moved += logic::simplePhysics::Simplekinematics::getdtime() * std::abs(_vel.x);
				if (_moved > 30)
				{
					++_posMoved;
					_moved -= 30;
					if (_posMoved > 3)
						_posMoved = 0;
				}
				_skin.setTextureRect(_skinIntRec[_posMoved]);
				_skin.setTexture(Platfrom::getTexture().CharacterRun());
			}
			else
			{
				_posMoved = 0;
				if (!_touchTheGround && (_vel.y > 0))
				{
					_skin.setTextureRect(_skinIntRec[0]);
					_skin.setTexture(Platfrom::getTexture().CharacterJump());
				}
				else if (!_touchTheGround && (_vel.y < 0))
				{
					_skin.setTextureRect(_skinIntRec[2]);
					_skin.setTexture(Platfrom::getTexture().CharacterJump());
				}
				else
				{
					_skin.setTextureRect(_skinIntRec[0]);
					_skin.setTexture(Platfrom::getTexture().CharacterIdle());
				}
			}

			window.draw(_skin);
			if (Platfrom::getConfig().getShowHitboxes())
				_hitBox->draw(window, _pos - refPos);
			return *this;
		}
		Entity& Character::feature()
		{
			float maxVel = _maxVel;
			if (Platfrom::getInputs().secondAction())
				maxVel *= 1.1f;
			if (_touchTheGround && Platfrom::getInputs().jump())
				_vel.y = -maxVel * 2 < _vel.y ? -maxVel * 2 : _vel.y ;
			
			_touchTheGround = false;
			if (Platfrom::getInputs().left())
			{
				if (_vel.x > -maxVel)
					_acc.x = -_maxAcc;
				else
				{
					_vel.x = -maxVel;
					_acc.x = 0;
				}
			}
			else if (Platfrom::getInputs().right())
			{
				if (_vel.x < maxVel)
					_acc.x = _maxAcc;
				else
				{
					_vel.x = maxVel;
					_acc.x = 0;
				}
			}
			else
			{
				if (_vel.x < 0)
				{
					_acc.x = _maxAcc /4;
				}
				else if (_vel.x > 0)
				{
					_acc.x = -_maxAcc /4;
				}
			}
			if (Platfrom::getConfig().getCreative())
			{
				if (Platfrom::getInputs().up())
				{
					if (_vel.y > -maxVel)
						_acc.y = -_maxAcc;
					else
					{
						_vel.y = -maxVel;
						_acc.y = 0;
					}
				}
				else if (Platfrom::getInputs().down())
				{
					if (_vel.y < maxVel)
						_acc.y = _maxAcc;
					else
					{
						_vel.y = maxVel;
						_acc.y = 0;
					}
				}
				else
				{
					if (_vel.y < 0)
					{
						_acc.y = _maxAcc / 4;
					}
					else if (_vel.y > 0)
					{
						_acc.y = -_maxAcc / 4;
					}
				}
			}
			return *this;
		}
		bool Character::isOnView(const sf::View& view)
		{
			return true;
		}
		Entity& Character::carry()
		{
			// Carry objects
			auto characterToMouse = sf::Mouse::getPosition()
				- _window.getPosition() + sf::Vector2i(0, -25)
				- sf::Vector2i(_window.getSize()) / 2;

			sf::Vector2f carryPosition(_nextPos + sf::Vector2f(characterToMouse.x > 0 ? 20.f : -20.f, -20.f));

			for (auto carried : _carriedCollection)
			{
				carried->carry(carryPosition);
			}
			// Throw objects
			if (Platfrom::getInputs().reAction() && !_carriedCollection.empty())
			{
				auto carriedToMouse = characterToMouse - sf::Vector2i(characterToMouse.x > 0 ? 20 : -20, -20);

				if (carriedToMouse == sf::Vector2i(0, 0))
					carriedToMouse = { 0,-1 };

				sf::Vector2f throwVec(carriedToMouse);
				throwVec *= 100.f / static_cast<float>(sqrt(pow(carriedToMouse.x, 2) + pow(carriedToMouse.y, 2)));

				_carriedCollection.back()->fling(throwVec);
				_carriedCollection.pop_back();
			}
			return *this;
		}
		void Character::reset()
		{
			_alive = true;
			_finish = false;
			_pos = _vel = _nextPos = _nextVel = { 0,0 };
			_acc = _nextAcc = { 0, simplePhysics::GRAVITY };
			_carriedCollection.clear();
		}
		bool Character::hit(Entity& hitting, sf::Vector2f collision)
		{
			bool ground = false;
			if (-collision.x >= collision.y && collision.x >= collision.y)
				ground = true;
			bool solid = Entity::hit(hitting, collision);
			if (ground && solid)
				_touchTheGround = true;
			return solid;
		}
		bool Character::getReaction(Entity& hitting, sf::Vector2f collision)
		{
			hitting.setNextPos(hitting.getNextPos() + (collision * 0.2f));
			_nextPos -= (collision * 0.2f);
			return true;
		}
		void Character::addToCarriedCollection(Portable* carried)
		{
			_carriedCollection.push_back(carried);
		}
		bool Character::isInCarriedCollection(Portable* tested)
		{
			if (tested)
				return std::find(_carriedCollection.begin(), _carriedCollection.end(), tested) != _carriedCollection.end();
			else
				return false;
		}
		bool Character::isBackOfTheCarried(Portable* tested)
		{
			return tested && tested == _carriedCollection.back();
		}
#pragma endregion
#pragma endregion
	}
}