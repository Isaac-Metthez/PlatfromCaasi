#include "PersonifiedEntity.h"
#include "Physics.h"
#include "HitBox.h"
#include "../HMI/Inputs.h"
#include "../Platfrom.h"
#include <SFML/Graphics.hpp>

namespace platfrom
{
	namespace logic
	{
#pragma region PersonifiedEntity 
#pragma region Constructors
		Entity& PersonifiedEntity::callKinetics()
		{
			_maxVel = _usualMaxVel;
			_maxAcc = _usualMaxAcc;
			return Entity::callKinetics();
		}
		void PersonifiedEntity::kill()
		{
			Platfrom::getPage().removeEntity(this);
		}
#pragma endregion
#pragma region Public Methods
#pragma endregion
#pragma region Protected Methods
#pragma endregion
#pragma endregion
	}
}