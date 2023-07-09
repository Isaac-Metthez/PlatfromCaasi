#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <windows.h>
#include <iostream>
#include <fstream>  
#include "../PlatfromCaasi/PlatfromCaasi/Platfrom.h"
#include "../PlatfromCaasi/PlatfromCaasi/Hmi/Inputs.h"
#include "../PlatfromCaasi/PlatfromCaasi/Hmi/Config.h"
#include "../PlatfromCaasi/PlatfromCaasi/Hmi/Sequencer.h"
#include "../PlatfromCaasi/PlatfromCaasi/Logic/Entity.h"
#include "../PlatfromCaasi/PlatfromCaasi/Logic/Blocks.h"
#include "../PlatfromCaasi/PlatfromCaasi/Logic/BlockDecorators.h"
#include "../PlatfromCaasi/PlatfromCaasi/Logic/FireBall.h"
#include "../PlatfromCaasi/PlatfromCaasi/Logic/HitBox.h"
#include "../PlatfromCaasi/PlatfromCaasi/Logic/Mobs.h"
#include "../PlatfromCaasi/PlatfromCaasi/Logic/PersonifiedEntity.h"

namespace platfrom
{
	namespace map
	{
		class POC
		{
		public:
			POC();
			void walk();
			void web();
			void air();
			void pole();
		protected:
		};

	}
}
