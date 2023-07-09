#pragma once
#include <SFML/Graphics.hpp>
#include <windows.h>
#include <iostream>
#include <fstream>
#include <string>
#include "../Paths.h"

namespace platfrom
{
	namespace logic
	{
		/**
		 * Class AchievedLevels
		 *
		 * Use to remain which levels are already done and also which level is unlocked. 
		 */
		class AchievedLevels
		{
		public:
			AchievedLevels();
			void addAchievedLevel(std::string name);
			const std::vector<std::string>& getAchievedLevels() { return _achievedLevels; };
			bool isAchieved(std::string& name);
			void reload();
			void save();
		protected:
			std::string getPath();
			std::vector<std::string>  _achievedLevels;
		};
	}
}

