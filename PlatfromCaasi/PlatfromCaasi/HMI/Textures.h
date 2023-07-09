#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
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
		 * Class Texture
		 *
		 * Texture load at construction the textures for the entities.
		 */
		class Texture
		{
		public:
			Texture();
			~Texture() = default;
			sf::Texture* BlueEnemy();
			sf::Texture* RedEnemy();
			sf::Texture* GreenEnemy();
			sf::Texture* Fireball();
			sf::Texture* CharacterIdle();
			sf::Texture* CharacterJump();
			sf::Texture* CharacterRun();
			sf::Texture* Dirt();
			sf::Texture* Ice();
			sf::Texture* Stone();
			sf::Texture* Web();
			sf::Texture* None();
			sf::Texture* StoneUp();
			sf::Texture* Grass();
			sf::Texture* IceUp();
			sf::Texture* Lader();
		protected:
			std::string getPath(std::string str);
			std::vector<sf::Texture> _textures;
		};
	}
}

