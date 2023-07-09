#pragma once
#include <SFML/Graphics.hpp>
#include <windows.h>
#include <iostream>
#include <fstream>
#include <string>
#include "../Paths.h"
namespace platfrom
{
	namespace hmi
	{
		/**
		 * Class Config
		 *
		 * Manage the value that are permanent such as LogEvent, CrativeMode and ShowHitBoxes.
		 */
		class Config
		{
		public:
			Config();
			~Config();
			bool getShowHitboxes() { return  _showHitBox; };
			bool getLogEvent() { return  _logEvents; };
			bool getCreative() { return  _creative; };
			void setShowHitbox(bool val) { _showHitBox = val; };
			void setLogEvent(bool val) { _logEvents = val; };
			void setCreative(bool val) { _creative = val; };
			void save();
		protected:
			std::string getPath();

			bool _showHitBox = false;
			bool _logEvents = false;
			bool _creative = false;
		};
	}
}

