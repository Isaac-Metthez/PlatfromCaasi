#pragma once
#include "Entity.h"
#include "HitBox.h"
#include "../HMI/Inputs.h"
namespace platfrom
{
	namespace logic
	{
		/**
		 * Class PersonifiedEntity
		 *
		 * PersonifiedEntity is a Entity who can die
		 */
		class PersonifiedEntity : public Entity 
		{
		public:
			PersonifiedEntity() = default; 

			virtual Entity& callKinetics()override;
			virtual void kill();

			void setMaxVel(const float maxVel) { _maxVel = maxVel; };
			void setMaxAcc(const float maxAcc) { _maxAcc = maxAcc; };
		protected:
			float _usualMaxVel = 30;
			float _maxVel = 30;
			float _usualMaxAcc = 50;
			float _maxAcc = 50; 
		};
	}

}