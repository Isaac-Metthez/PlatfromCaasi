#pragma once
#include "Blocks.h"
#include <SFML/Graphics.hpp>
#include "Entity.h"
#include "HitBox.h"
#include "PersonifiedEntity.h"
#include <vector>
#include <fstream>
#include "../HMI/Inputs.h"

namespace platfrom
{
	namespace logic
	{
		namespace blocks
		{
			namespace decorators
			{
				/**
				 * Class Decorations
				 *
				 * Use to decorate the differents blocks. 
				 * Every decorations react differently to blocks collisions and give another effect.
				 */
				class Decoration : public serialize::Serializable
				{
				public:
					virtual ~Decoration() = default;
					virtual void posReaction(Entity& hitting, Entity& super, sf::Vector2f collision);
					virtual void velReaction(Entity& hitting, Entity& super, sf::Vector2f collision);
					virtual void otherReaction(Entity& hitting, Entity& super, sf::Vector2f collision);
					virtual void decoFeature(Entity& super);
					std::ostream& serialize(std::ostream& os) const override;
				protected:
				};

				/**
				 * Class Simple
				 *
				 * Basic effect, just normal block.
				 */
				class Simple : public Decoration
				{
				public:
					void posReaction(Entity& hitting, Entity& super, sf::Vector2f collision) override;
					void velReaction(Entity& hitting, Entity& super, sf::Vector2f collision) override;
				protected:
				};

				/**
				 * Class Oneway
				 *
				 * Almost as simple but the collision is just from above.
				 */
				class OneWay : public Decoration
				{
				public:
					void posReaction(Entity& hitting, Entity& super, sf::Vector2f collision) override;
					void velReaction(Entity& hitting, Entity& super, sf::Vector2f collision) override;
				protected:
				};

				/**
				 * Class Bouncing
				 *
				 * Give upward speed to personnied entities.
				 */
				class Bouncing : public Decoration
				{
				public:
					void velReaction(Entity& hitting, Entity& super, sf::Vector2f collision) override;
				protected:
				};

				/**
				 * Class Moving
				 *
				 * Move block.
				 */
				class Moving : public Decoration
				{
				public:
					Moving(sf::Vector2f endRelPos);
					Moving(std::ifstream &filein);
					Moving(sf::Vector2f endRelPos, float velocity);
					void decoFeature(Entity& super) override;
					void posReaction(Entity& hitting, Entity& super, sf::Vector2f collision) override;
					std::ostream& serialize(std::ostream& os) const override;
				protected:
					sf::Vector2f _maxPos;
					sf::Vector2f _minPos;
					sf::Vector2f _velocity;
					bool _changeDirection = false;
					bool _posSet = false;
				};

				/**
				 * Class Ice
				 *
				 * Block become sliding.
				 */
				class Ice : public Decoration
				{
				public:
					void otherReaction(Entity& hitting, Entity& super, sf::Vector2f collision) override;
				};

				/**
				 * Class Web
				 *
				 * Slow down the entities in contact of this block.
				 */
				class Web : public Decoration
				{
				public:
					void velReaction(Entity& hitting, Entity& super, sf::Vector2f collision) override;
				protected:
				};

				/**
				 * Class Lader
				 *
				 * Character is able to climb this block.
				 */
				class Lader : public Decoration
				{
				public:
					Lader();
					void posReaction(Entity& hitting, Entity& super, sf::Vector2f collision) override;
					void velReaction(Entity& hitting, Entity& super, sf::Vector2f collision) override;
				protected:
					sf::Vector2f _onLaderVelocity;
				};

				/**
				 * Class Hurting
				 *
				 * Personnified entities die by contact of this block.
				 */
				class Hurting : public Decoration
				{
				public:
					void otherReaction(Entity& hitting, Entity& super, sf::Vector2f collision) override;
				protected:
				};

				/**
				 * Class Finish
				 *
				 * If character touch this block the map is won.
				 */
				class Finish : public Decoration
				{
				public:
					void otherReaction(Entity& hitting, Entity& super, sf::Vector2f collision) override;
				protected:
				};
			}
		}
	}
}