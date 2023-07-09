#include "Entity.h"
#include "HitBox.h"
#include "Blocks.h"
#include "Character.h"
#include "../Platfrom.h"
#include <math.h>
#include <vector>
#include <typeinfo>
#include <SFML/Graphics.hpp>

namespace platfrom
{
	namespace logic
	{
	#pragma region Entity 
		#pragma region Operators overload
		#pragma endregion
		#pragma region Constructors
		Entity::Entity():
			_pos(0,0),
			_vel(0,0),
			_acc(0,0),
			_nextPos(0,0),
			_nextVel(0,0),
			_nextAcc(0,0)
		{
		}
		Entity::~Entity()
		{
			if (_hitBox)
				delete(_hitBox);
		}
		#pragma endregion
		#pragma region Public Methods
		Entity& Entity::feature()
		{
			return *this;
		}
		Entity& Entity::callKinetics()
		{
			_nextPos = simplePhysics::Simplekinematics::position(_pos, _vel);
			_nextVel = simplePhysics::Simplekinematics::velocity(_vel, _acc);
			return *this;
		}
		Entity& Entity::calculateCollision(Entity &object)
		{
			/*	Calcul collision are only do by spherical hit-box to another spherical hit-box
				or do by a spherical hit-box to an rectangular hit-box
				because polygonal hit-boxes are only for the blocks */
			hitBoxes::HitBox& obstacle = *object._hitBox;
			if (typeid(obstacle) == typeid(hitBoxes::SphericalHitBox) 
				&& typeid(*_hitBox) == typeid(hitBoxes::SphericalHitBox))
			{
				auto &refObstacleHitbox = dynamic_cast<hitBoxes::SphericalHitBox&>(obstacle);
				auto &refThisHitbox = dynamic_cast<hitBoxes::SphericalHitBox&>(*_hitBox);
				std::vector <sf::Vector2f> memCorrection(0);
				sf::Vector2f memSumCorrection(0, 0);

				for (int j = 0 ; j < refObstacleHitbox.getNumber(); j++)
				{
					for (int i = 0; i < refThisHitbox.getNumber(); i++)
					{
						sf::Vector2f rel(_nextPos.x + refThisHitbox.getRelPosX(i) -
							object._nextPos.x - refObstacleHitbox.getRelPosX(j),
							_nextPos.y + refThisHitbox.getRelPosY(i) -
							object._nextPos.y - refObstacleHitbox.getRelPosY(j));
						if (pow(rel.x,2) +
							pow(rel.y,2)
							<= pow(refThisHitbox.getRadius(i) + refObstacleHitbox.getRadius(j), 2))
						{
							float normOfRel = static_cast<float>(sqrt(pow(rel.x, 2) + pow(rel.y, 2)));
							hit(object, (0.9f * rel) / normOfRel);

							memSumCorrection += rel/ normOfRel;
							memCorrection.push_back(rel / normOfRel) ;
						}     
					}
				}
				if (!memCorrection.empty())
				{
					sf::Vector2f vecCollision(memSumCorrection.x / memCorrection.size(), memSumCorrection.y / memCorrection.size());
					hit(object, 0.9f * vecCollision);
				}
			}
			else if (typeid(obstacle) == typeid(hitBoxes::ConvexPolygonHitBox)
				&& typeid(*_hitBox) == typeid(hitBoxes::SphericalHitBox))
			{
				auto & refObstacleHitbox = dynamic_cast<hitBoxes::ConvexPolygonHitBox&>(obstacle);
				auto & refThisHitbox = dynamic_cast<hitBoxes::SphericalHitBox&>(*_hitBox);


				std::vector <bool> collision(refThisHitbox.getNumber(), true);
				std::vector <float> smallestSunk(refThisHitbox.getNumber(), std::numeric_limits<float>::max());
				std::vector <sf::Vector2f> memLimitPosition(refThisHitbox.getNumber());
				std::vector <sf::Vector2f> memUnitNormal(refThisHitbox.getNumber());
				std::vector <sf::Vector2f> memCorrection(0);
				sf::Vector2f memSumCorrection(0, 0);

				for (unsigned int j = 0; j < refObstacleHitbox.getNumber(); j++)
				{
					sf::Vector2f posNextPoint(
						j + 1 < refObstacleHitbox.getNumber() ?
						refObstacleHitbox.getRelPointPosX(j + 1) +
						object._nextPos.x :
						refObstacleHitbox.getRelPointPosX(0) +
						object._nextPos.x,
						j + 1 < refObstacleHitbox.getNumber() ?
						refObstacleHitbox.getRelPointPosY(j + 1) +
						object._nextPos.y :
						refObstacleHitbox.getRelPointPosY(0) +
						object._nextPos.y);

					sf::Vector2f relNormal(
						j == 0 ?
						-(refObstacleHitbox.getRelPointPosY(refObstacleHitbox.getNumber() - 1) -
							refObstacleHitbox.getRelPointPosY(j)) :
						-(refObstacleHitbox.getRelPointPosY(j - 1) -
							refObstacleHitbox.getRelPointPosY(j)),
						j == 0 ?
						(refObstacleHitbox.getRelPointPosX(refObstacleHitbox.getNumber() - 1) -
							refObstacleHitbox.getRelPointPosX(j)) :
						(refObstacleHitbox.getRelPointPosX(j - 1) -
							refObstacleHitbox.getRelPointPosX(j)));
					
					if (((object._nextPos.x + refObstacleHitbox.getRelPointPosX(j) - posNextPoint.x) * relNormal.x + 
						(object._nextPos.y + refObstacleHitbox.getRelPointPosY(j) - posNextPoint.y) * relNormal.y) 
						< 0)
					{
						relNormal = -relNormal;
					}

					float normOfRelNormal = static_cast<float>(sqrt(pow(relNormal.x, 2) + pow(relNormal.y, 2)));

					sf::Vector2f unitNormal(relNormal.x / normOfRelNormal, relNormal.y / normOfRelNormal);
					
					for (int i = 0; i < refThisHitbox.getNumber(); i++)
					{
						if (!collision[i])
						{
							continue;
						}
						sf::Vector2f limitPos(
							refObstacleHitbox.getRelPointPosX(j) +
							object._nextPos.x +
							(refThisHitbox.getRadius(i) *
								relNormal.x)
							/ normOfRelNormal,
							refObstacleHitbox.getRelPointPosY(j) +
							object._nextPos.y +
							(refThisHitbox.getRadius(i) *
								relNormal.y)
							/ normOfRelNormal);

						sf::Vector2f veclimitThisToPos(_nextPos + refThisHitbox.getRelPos(i) - limitPos);

						if (relNormal.x * veclimitThisToPos.x + relNormal.y * veclimitThisToPos.y > 0.f)
						{
							collision[i] = false;
						}
						else
						{
							float sinkingInThisSide = -(veclimitThisToPos.x * unitNormal.x + veclimitThisToPos.y * unitNormal.y);
							if (smallestSunk[i] > sinkingInThisSide)
							{
								smallestSunk[i] = sinkingInThisSide;
								memUnitNormal[i] = unitNormal;
								memLimitPosition[i] = limitPos;
							}
						}
					}
				}
				for (int i = 0; i < refThisHitbox.getNumber(); i++)
					{
					bool notOnCorner = true;

					if (collision[i])
					{
						for (unsigned int j = 0; j < refObstacleHitbox.getNumber(); j++)
						{
							sf::Vector2f posCorner(refObstacleHitbox.getRelPointPos(j) + object._nextPos);
							sf::Vector2f rel(_nextPos + refThisHitbox.getRelPos(i) - posCorner);

							sf::Vector2f relCornerToNextCorner(j + 1 < refObstacleHitbox.getNumber() ?
								refObstacleHitbox.getRelPointPos(j + 1) - refObstacleHitbox.getRelPointPos(j) :
								refObstacleHitbox.getRelPointPos(0) - refObstacleHitbox.getRelPointPos(j));

							sf::Vector2f relCornerToPreviousCorner(j > 0 ?
								refObstacleHitbox.getRelPointPos(j - 1) - refObstacleHitbox.getRelPointPos(j) :
								refObstacleHitbox.getRelPointPos(refObstacleHitbox.getNumber() - 1) - refObstacleHitbox.getRelPointPos(j));

							bool posNextScalarPorduct = rel.x * relCornerToNextCorner.x + rel.y * relCornerToNextCorner.y < 0;
							bool posPreviousScalarPorduct = rel.x * relCornerToPreviousCorner.x + rel.y * relCornerToPreviousCorner.y < 0;

							if (posNextScalarPorduct && posPreviousScalarPorduct)
							{
								float normOfRel = static_cast<float>(sqrt(pow(rel.x, 2) + pow(rel.y, 2)));

								if (normOfRel <= refThisHitbox.getRadius(i))
								{
									sf::Vector2f tempCorrection(
										sf::Vector2f(
											((refThisHitbox.getRadius(i)) * rel.x /
												normOfRel),
											((refThisHitbox.getRadius(i)) * rel.y /
												normOfRel)) 
										+posCorner
										- refThisHitbox.getRelPos(i) 
										- _nextPos);

									memSumCorrection += tempCorrection;
									memCorrection.push_back(tempCorrection);

								}
								notOnCorner = false;
								break;
							}

						}
						if (notOnCorner)
						{
							sf::Vector2f tempCorrection(memUnitNormal[i].x* smallestSunk[i], memUnitNormal[i].y* smallestSunk[i]);

							memSumCorrection += tempCorrection;
							memCorrection.push_back(tempCorrection);
						}
					}
				}
				if (!memCorrection.empty())
				{
					sf::Vector2f vecCollision(memSumCorrection.x / memCorrection.size(), memSumCorrection.y / memCorrection.size());
					hit(object, 0.9f * vecCollision);
				}

			}
			return *this;
		}
		Entity& Entity::calculateCollision(std::list<Entity*> &collection)
		{
			for (Entity* entity : collection)
				if (entity != this)
					calculateCollision(*entity);
			return *this;
		}
		Entity& Entity::setAcctualisedKinetics()
		{
			_pos = _nextPos;
			_vel = _nextVel;
			return *this;
		}
		Entity& Entity::drawEntity(sf::RenderWindow &window, const sf::Vector2f refPos)
		{
			_hitBox->draw(window, _pos - refPos);
			return *this;
		}
		bool Entity::isOnView(const sf::View& view)
		{
			return _hitBox->isOnview(view, _pos);
		}
		bool Entity::hit(Entity& object, sf::Vector2f collision)
		{
			return object.getReaction(*this, collision);
		}

		bool Entity::getReaction(Entity& hitting, sf::Vector2f collision)
		{
			return false;
		}
#pragma endregion
#pragma endregion
	}
}
