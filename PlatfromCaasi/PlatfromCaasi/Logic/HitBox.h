#pragma once
#include <SFML/Graphics.hpp>
#include "Physics.h"
#include <vector>

namespace platfrom
{
	namespace logic
	{
		namespace hitBoxes
		{
			/**
			 * Class HitBox
			 *
			 * Hitbox defines shape of the entity (used for calculate collision). 
			 */
			class HitBox
			{
			public:
				HitBox();
				virtual ~HitBox();
				virtual void draw(sf::RenderWindow& window,const sf::Vector2f& pos) = 0;
				virtual bool isOnview(const sf::View& view, const sf::Vector2f& pos) = 0;
			protected:
			};

			/**
			 * Class SphericalHitBox
			 *
			 * SphericalHitBox is the default hitbox for portable and personnified entity (It's faster to calculate collision for this hitbox).
			 */
			class SphericalHitBox : public HitBox
			{
			public:
				SphericalHitBox(const std::vector<sf::Vector3f> &circles);
				~SphericalHitBox() override;

				void draw(sf::RenderWindow& window,const sf::Vector2f& pos) override;
				bool isOnview(const sf::View& view, const sf::Vector2f& pos) override;

				int getNumber() const { return static_cast<int>(_relCircles.size()); }
				float getRelPosX(int index) const { return _relCircles[index].x; }
				float getRelPosY(int index) const { return _relCircles[index].y; }
				float getRadius(int index) const { return _relCircles[index].z; }
				sf::Vector2f getRelPos(int index) const { return sf::Vector2f(_relCircles[index].x, _relCircles[index].y); }

			protected:
				std::vector<sf::Vector3f> _relCircles;
				sf::Vector2f _minCoordinate, _maxCoordinate;
				std::vector<sf::CircleShape*> _shapeHitbox ;

			};

			/**
			 * Class ConvexPolygonHitBox
			 *
			 * ConvexPolygonHitBox is the default hitbox for blocks.
			 */
			class ConvexPolygonHitBox : public HitBox
			{
			public:
				ConvexPolygonHitBox(std::vector<sf::Vector2f> points);
				~ConvexPolygonHitBox() override;

				void draw(sf::RenderWindow& window,const sf::Vector2f& pos) override;
				void drawAsBlock(sf::RenderWindow& window, const sf::Vector2f& pos,const sf::Texture* texture, const sf::Texture* textureUp);
				bool isOnview(const sf::View& view, const sf::Vector2f& pos) override;

				unsigned int const getNumber() { return static_cast<unsigned int>(_relPoint.size()); };
				float const getRelPointPosX(int index) { return _relPoint[index].x; };
				float const getRelPointPosY(int index) { return _relPoint[index].y; };
				sf::Vector2f const getRelPointPos(int index) { return _relPoint[index]; };
			protected:
				std::vector<sf::Vector2f> _relPoint;
				sf::Vector2f _minCoordinate, _maxCoordinate;
				sf::ConvexShape* _shapeHitbox = nullptr;
				sf::ConvexShape* _drawAsBlock = nullptr;
				sf::ConvexShape* _drawAsBlockUp = nullptr;
			};
		}
	}
}
