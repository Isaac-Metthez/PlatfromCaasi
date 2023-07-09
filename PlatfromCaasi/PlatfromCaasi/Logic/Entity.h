#pragma once
#include "HitBox.h"
#include "../Serialize/Serializable.h"
#include "../Serialize/Vector.h"
#include <math.h>
#include <SFML/Graphics.hpp>
#include <string>
#include <list>
#include <iostream>
#include <fstream>  

namespace platfrom
{
	namespace logic
	{
		/**
		 * Class Entity
		 *
		 * Almost all logic class herit from entity. Indeed entity makes possible to calculate collision, draw, call kinetics etc...
		 */
		class Entity : public serialize::Serializable
		{
		public:
			hitBoxes::HitBox* _hitBox = nullptr;

			Entity();
			virtual ~Entity();

			virtual Entity& feature();
			virtual Entity& callKinetics();
			virtual Entity& calculateCollision(Entity& object);
			virtual Entity& calculateCollision(std::list<Entity*> &collection);
			virtual Entity& setAcctualisedKinetics();
			virtual Entity& drawEntity(sf::RenderWindow& window, const sf::Vector2f refPos = { 0,0 }) = 0;
			virtual bool isOnView(const sf::View& view);
			virtual bool hit(Entity& object, sf::Vector2f collision);
			virtual bool getReaction(Entity& hitting, sf::Vector2f collision);

			sf::Vector2f getPos() const { return _pos; };
			sf::Vector2f getVel() const { return _vel; };
			sf::Vector2f getAcc() const { return _acc; };
			void setPos(const sf::Vector2f& pos) { _pos = pos; };
			void setVel(const sf::Vector2f& vel) { _vel = vel; };
			void setAcc(const sf::Vector2f& acc) { _acc = acc; };

			sf::Vector2f getNextPos() const { return _nextPos; };
			sf::Vector2f getNextVel() const { return _nextVel; };
			sf::Vector2f getNextAcc() const { return _nextAcc; };
			void setNextPos(const sf::Vector2f& pos) { _nextPos = pos; };
			void setNextVel(const sf::Vector2f& vel) { _nextVel = vel; };
			void setNextAcc(const sf::Vector2f& acc) { _nextAcc = acc; };
		protected:
			sf::Vector2f _pos, _vel, _acc;
			sf::Vector2f _nextPos, _nextVel, _nextAcc;
		};
	}
}

