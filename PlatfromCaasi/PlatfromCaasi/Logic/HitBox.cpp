#include "HitBox.h"
#include "Physics.h"
#include <SFML/Graphics.hpp>

namespace platfrom
{
	namespace logic
	{
		namespace hitBoxes
		{
#pragma region HitBox 
#pragma region Operators overload
#pragma endregion
#pragma region Constructors
			HitBox::HitBox()
			{
			}

			HitBox::~HitBox()
			{
			}
#pragma endregion
#pragma region Public Methods
#pragma endregion
#pragma region Protected Methods
#pragma endregion
#pragma endregion
#pragma region SphericalHitBox 
#pragma region Operators overload
#pragma endregion
#pragma region Constructors
			SphericalHitBox::SphericalHitBox(const std::vector<sf::Vector3f>& circles)
			{
				_minCoordinate = _maxCoordinate = { circles.front().x, circles.front().y };

				for (sf::Vector3f circle : circles)
				{
					_relCircles.push_back(circle);

					if (circle.x + circle.z > _maxCoordinate.x)
						_maxCoordinate.x = circle.x + circle.z;
					if (circle.y + circle.y > _maxCoordinate.y)
						_maxCoordinate.y = circle.y + circle.y;

					if (circle.x - circle.z < _minCoordinate.x)
						_minCoordinate.x = circle.x - circle.z;
					if (circle.y - circle.z < _minCoordinate.y)
						_minCoordinate.y = circle.y - circle.z;
				}
			}
			SphericalHitBox::~SphericalHitBox()
			{
				for (sf::CircleShape* const &circle : _shapeHitbox)
				{
					delete(circle);
				}
				_shapeHitbox.clear();
			}
#pragma endregion
#pragma region Public Methods
			void SphericalHitBox::draw(sf::RenderWindow& window,const sf::Vector2f& pos)
			{
				if (_shapeHitbox.empty())
				{
					for (int i = 0; i < _relCircles.size(); i++)
					{
						_shapeHitbox.push_back(new sf::CircleShape);
						_shapeHitbox[i]->setRadius(_relCircles[i].z);
						_shapeHitbox[i]->setFillColor(sf::Color(0, 0, 0, 0));
						_shapeHitbox[i]->setOutlineColor(sf::Color::Red);
						_shapeHitbox[i]->setOutlineThickness(2);
					}
				}
				for (int i = 0; i < _shapeHitbox.size(); i++)
				{
					_shapeHitbox[i]->setPosition(pos + getRelPos(i) - sf::Vector2f(_relCircles[i].z, _relCircles[i].z));
					window.draw(*_shapeHitbox[i]);
				}

			}
			bool SphericalHitBox::isOnview(const sf::View& view, const sf::Vector2f& pos)
			{
				// true if is on the view or on the borders
				sf::Vector2f halfview = (view.getSize() / 2.f) + sf::Vector2f(100.f, 1000.f);
				return ((pos.x + _maxCoordinate.x > view.getCenter().x - (halfview.x ))
					&& (pos.x + _minCoordinate.x < view.getCenter().x + (halfview.x ))
					&& (pos.y + _maxCoordinate.y > view.getCenter().y - (halfview.y ))
					&& (pos.y + _minCoordinate.y < view.getCenter().y + (halfview.y )));
			}
#pragma endregion
#pragma region Protected Methods
#pragma endregion
#pragma endregion
#pragma region Entity 
#pragma region Operators overload
#pragma endregion
#pragma region Constructors
			ConvexPolygonHitBox::ConvexPolygonHitBox(std::vector<sf::Vector2f> points)
			{
				_minCoordinate = _maxCoordinate = points.front();

				for (sf::Vector2f point : points)
				{
					_relPoint.push_back(point);

					if (point.x > _maxCoordinate.x)
						_maxCoordinate.x = point.x;
					if (point.y > _maxCoordinate.y)
						_maxCoordinate.y = point.y ;

					if (point.x < _minCoordinate.x)
						_minCoordinate.x = point.x ;
					if (point.y < _minCoordinate.y)
						_minCoordinate.y = point.y;
				}
			}
			ConvexPolygonHitBox::~ConvexPolygonHitBox()
			{
				if (_shapeHitbox)
					delete(_shapeHitbox);
				if (_drawAsBlock)
					delete(_drawAsBlock);
			}
#pragma endregion
#pragma region Public Methods
			void ConvexPolygonHitBox::draw(sf::RenderWindow& window,const sf::Vector2f& pos)
			{
				if (!_shapeHitbox)
				{
					_shapeHitbox = new sf::ConvexShape;
					_shapeHitbox->setPointCount(_relPoint.size());
					_shapeHitbox->setFillColor(sf::Color(0, 0, 0, 0));
					_shapeHitbox->setOutlineColor(sf::Color::White);
					_shapeHitbox->setOutlineThickness(2);
					for (int i = 0; i < _relPoint.size(); i++)
					{
						_shapeHitbox->setPoint(i, _relPoint[i]);
					}
				}
				_shapeHitbox->setPosition(pos);
				window.draw(*_shapeHitbox);
			}
			void ConvexPolygonHitBox::drawAsBlock(sf::RenderWindow& window, const sf::Vector2f& pos,const sf::Texture* texture, const sf::Texture* textureUp)
			{
				if (!_drawAsBlock || !_drawAsBlockUp)
				{
					_drawAsBlock = new sf::ConvexShape;
					_drawAsBlock->setPointCount(_relPoint.size());
					for (int i = 0; i < _relPoint.size(); i++)
					{
						_drawAsBlock->setPoint(i, _relPoint[i]);
					}
					_drawAsBlock->setTextureRect(sf::IntRect(_drawAsBlock->getGlobalBounds()));
					_drawAsBlock->setTexture(texture);

					std::vector<sf::Vector2f> sortedPoint(_relPoint);
					std::sort(sortedPoint.begin(), sortedPoint.end(), 
						[](sf::Vector2f &v1, sf::Vector2f &v2)
						{
							return v1.y < v2.y;
						});
					
					_drawAsBlockUp = new sf::ConvexShape;
					_drawAsBlockUp->setPointCount(4);
					_drawAsBlockUp->setPoint(0, sortedPoint[0]);
					_drawAsBlockUp->setPoint(1, sortedPoint[1]);
					_drawAsBlockUp->setPoint(2, sortedPoint[1] + sf::Vector2f( 0, 10));
					_drawAsBlockUp->setPoint(3, sortedPoint[0] + sf::Vector2f( 0, 10));

					_drawAsBlockUp->setTextureRect(sf::IntRect(_drawAsBlockUp->getGlobalBounds()));
					_drawAsBlockUp->setTexture(textureUp);

				}
				_drawAsBlock->setPosition(pos);
				_drawAsBlockUp->setPosition(pos);
				window.draw(*_drawAsBlock);
				window.draw(*_drawAsBlockUp);

				
			}
			bool ConvexPolygonHitBox::isOnview(const sf::View& view, const sf::Vector2f& pos)
			{
				// true if is on the view or on the borders
				sf::Vector2f halfview = (view.getSize() / 2.f) + sf::Vector2f(200.f, 1100.f);
				return ((pos.x + _maxCoordinate.x > view.getCenter().x - (halfview.x))
					&& (pos.x + _minCoordinate.x < view.getCenter().x + (halfview.x))
					&& (pos.y + _maxCoordinate.y > view.getCenter().y - (halfview.y))
					&& (pos.y + _minCoordinate.y < view.getCenter().y + (halfview.y)));
			}
#pragma endregion
#pragma region Protected Methods
#pragma endregion
#pragma endregion
		}
	}

}