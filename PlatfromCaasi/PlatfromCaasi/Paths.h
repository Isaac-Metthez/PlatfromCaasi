#pragma once

namespace platfrom
{
	constexpr auto PLATFROM_DATA = "C:\\ProgramData\\PlatfromCaasi";
	namespace hmi
	{
		constexpr auto CONFIG_DIR = "C:\\ProgramData\\PlatfromCaasi\\Config";
		constexpr auto CONFIG_FILE = "Config.txt";

		constexpr auto MAPS_PATH = "..\\Map";

		constexpr auto TEXTURE_DIR = "..\\Texture";
		constexpr auto TEXTURE_ENEMY_BLUE = "Enemy blue.png";
		constexpr auto TEXTURE_ENEMY_RED = "Enemy red.png";
		constexpr auto TEXTURE_ENEMY_GREEN = "Enemy green.png";
		constexpr auto TEXTURE_FIREBALL = "Fireball.png";
		constexpr auto TEXTURE_CHARACTER_IDLE = "Character idle.png";
		constexpr auto TEXTURE_CHARACTER_JUMP = "Character jump.png";
		constexpr auto TEXTURE_CHARACTER_RUN = "Character run.png";
		constexpr auto TEXTURE_DIRT = "Dirt.png";
		constexpr auto TEXTURE_ICE = "Ice.png";
		constexpr auto TEXTURE_STONE = "Stone.png";
		constexpr auto TEXTURE_WEB = "Web.png";
		constexpr auto TEXTURE_NONE = "None.png";
		constexpr auto TEXTURE_STONE_UP = "Stone Up.png";
		constexpr auto TEXTURE_GRASS = "Grass.png";
		constexpr auto TEXTURE_ICE_UP = "Ice Up.png";
		constexpr auto TEXTURE_LADER = "Lader.png";
	}
	namespace logic
	{
		constexpr auto ACHIEVED_DIR = "C:\\ProgramData\\PlatfromCaasi\\Achieved";
		constexpr auto LEVEL_FILE = "Levels.txt";
	}
}

namespace utils
{
	constexpr auto LOG_DIR = "C:\\ProgramData\\PlatfromCaasi\\Logger";
}