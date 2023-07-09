#pragma once
#include "Entity.h"
#include "PersonifiedEntity.h"
#include "Portable.h"
#include <list>
#include <algorithm>
#include "HitBox.h"
#include "../HMI/Inputs.h"
namespace platfrom
{
	namespace logic
	{
		/**
		 * Class Character
		 *
		 * Character is the played entity.
		 */
		class Character : public PersonifiedEntity 
		{
		public:
			Character(sf::Window& window);
			~Character();
			void reset();
			Entity& drawEntity(sf::RenderWindow& window, const sf::Vector2f refPos = {0,0}) override;
			Entity& feature() override;
			bool isOnView(const sf::View& view) override;
			bool hit(Entity& hitting, sf::Vector2f collision) override;
			bool getReaction(Entity& hitting, sf::Vector2f collision) override;
			Entity& carry();
			void addToCarriedCollection(Portable* carried);
			bool isInCarriedCollection(Portable* tested);
			bool isBackOfTheCarried(Portable* tested);
			bool isAlive() { return _alive; };
			void setFinish(bool finish) { _finish = finish; };
			bool getFinish() { return _finish; };
			void kill() override { _alive = false; };
		protected:
			bool _alive = true;
			bool _touchTheGround = false;
			bool _finish = false;
			sf::Window& _window;
			std::list<Portable*> _carriedCollection;
			sf::RectangleShape _skin;
			sf::Vector2f _skinScale;
			std::vector<sf::IntRect> _skinIntRec;
			int _posMoved = 0;
			double _moved = 0;
		};
	}

}