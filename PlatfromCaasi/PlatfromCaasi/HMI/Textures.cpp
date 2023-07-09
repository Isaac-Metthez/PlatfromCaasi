#include "Textures.h"
#include "../Platfrom.h"

namespace platfrom
{
    namespace hmi
    {
#pragma region Texture 

#pragma endregion
        Texture::Texture()
        {
			try
			{
				_textures.emplace_back();
				if (!_textures.back().loadFromFile(getPath(TEXTURE_ENEMY_BLUE), sf::IntRect(0, 0, 32, 32)))
					Platfrom::getEventLogger().addLogEvent("Texture hasn't been correctly charged :" + std::string(TEXTURE_ENEMY_BLUE));

				_textures.emplace_back();
				if (!_textures.back().loadFromFile(getPath(TEXTURE_ENEMY_RED), sf::IntRect(0, 0, 32, 32)))
					Platfrom::getEventLogger().addLogEvent("Texture hasn't been correctly charged :" + std::string(TEXTURE_ENEMY_RED));

				_textures.emplace_back();
				if (!_textures.back().loadFromFile(getPath(TEXTURE_ENEMY_GREEN), sf::IntRect(0, 0, 32, 32)))
					Platfrom::getEventLogger().addLogEvent("Texture hasn't been correctly charged :" + std::string(TEXTURE_ENEMY_GREEN));

				_textures.emplace_back();
				if (!_textures.back().loadFromFile(getPath(TEXTURE_FIREBALL), sf::IntRect(0, 0, 32, 32)))
					Platfrom::getEventLogger().addLogEvent("Texture hasn't been correctly charged :" + std::string(TEXTURE_FIREBALL));

				_textures.emplace_back();
				if (!_textures.back().loadFromFile(getPath(TEXTURE_CHARACTER_IDLE), sf::IntRect(0, 0, 32, 32)))
					Platfrom::getEventLogger().addLogEvent("Texture hasn't been correctly charged :" + std::string(TEXTURE_CHARACTER_IDLE));

				_textures.emplace_back();
				if (!_textures.back().loadFromFile(getPath(TEXTURE_CHARACTER_JUMP), sf::IntRect(0, 0, 32, 64)))
					Platfrom::getEventLogger().addLogEvent("Texture hasn't been correctly charged :" + std::string(TEXTURE_CHARACTER_JUMP));

				_textures.emplace_back();
				if (!_textures.back().loadFromFile(getPath(TEXTURE_CHARACTER_RUN), sf::IntRect(0, 0, 64, 64)))
					Platfrom::getEventLogger().addLogEvent("Texture hasn't been correctly charged :" + std::string(TEXTURE_CHARACTER_RUN));

				_textures.emplace_back();
				if (!_textures.back().loadFromFile(getPath(TEXTURE_DIRT), sf::IntRect(0, 0, 32, 32)))
					Platfrom::getEventLogger().addLogEvent("Texture hasn't been correctly charged :" + std::string(TEXTURE_DIRT));
				else
				{
					_textures.back().setSmooth(true);
					_textures.back().setRepeated(true);
				}

				_textures.emplace_back();
				if (!_textures.back().loadFromFile(getPath(TEXTURE_ICE), sf::IntRect(0, 0, 32, 64)))
					Platfrom::getEventLogger().addLogEvent("Texture hasn't been correctly charged :" + std::string(TEXTURE_ICE));
				else
				{
					_textures.back().setSmooth(true);
					_textures.back().setRepeated(true);
				}

				_textures.emplace_back();
				if (!_textures.back().loadFromFile(getPath(TEXTURE_STONE), sf::IntRect(0, 0, 32, 64)))
					Platfrom::getEventLogger().addLogEvent("Texture hasn't been correctly charged :" + std::string(TEXTURE_STONE));
				else
				{
					_textures.back().setSmooth(true);
					_textures.back().setRepeated(true);
				}

				_textures.emplace_back();
				if (!_textures.back().loadFromFile(getPath(TEXTURE_WEB), sf::IntRect(0, 0, 32, 32)))
					Platfrom::getEventLogger().addLogEvent("Texture hasn't been correctly charged :" + std::string(TEXTURE_WEB));
				else
				{
					_textures.back().setSmooth(true);
					_textures.back().setRepeated(true);
				}

				_textures.emplace_back();
				if (!_textures.back().loadFromFile(getPath(TEXTURE_NONE), sf::IntRect(0, 0, 32, 32)))
					Platfrom::getEventLogger().addLogEvent("Texture hasn't been correctly charged :" + std::string(TEXTURE_NONE));
				else
				{
					_textures.back().setSmooth(true);
					_textures.back().setRepeated(true);
				}

				_textures.emplace_back();
				if (!_textures.back().loadFromFile(getPath(TEXTURE_STONE_UP), sf::IntRect(0, 0, 32, 32)))
					Platfrom::getEventLogger().addLogEvent("Texture hasn't been correctly charged :" + std::string(TEXTURE_STONE_UP));
				else
				{
					_textures.back().setSmooth(true);
					_textures.back().setRepeated(true);
				}

				_textures.emplace_back();
				if (!_textures.back().loadFromFile(getPath(TEXTURE_GRASS), sf::IntRect(0, 0, 32, 32)))
					Platfrom::getEventLogger().addLogEvent("Texture hasn't been correctly charged :" + std::string(TEXTURE_GRASS));
				else
				{
					_textures.back().setSmooth(true);
					_textures.back().setRepeated(true);
				}

				_textures.emplace_back();
				if (!_textures.back().loadFromFile(getPath(TEXTURE_ICE_UP), sf::IntRect(0, 0, 32, 32)))
					Platfrom::getEventLogger().addLogEvent("Texture hasn't been correctly charged :" + std::string(TEXTURE_ICE_UP));
				else
				{
					_textures.back().setSmooth(true);
					_textures.back().setRepeated(true);
				}

				_textures.emplace_back();
				if (!_textures.back().loadFromFile(getPath(TEXTURE_LADER), sf::IntRect(0, 0, 32, 32)))
					Platfrom::getEventLogger().addLogEvent("Texture hasn't been correctly charged :" + std::string(TEXTURE_LADER));
				else
				{
					_textures.back().setSmooth(true);
					_textures.back().setRepeated(true);
				}
			}
			catch (...)
			{
				Platfrom::getEventLogger().addLogEvent("Error while loadin textures" );
				exit(1);
			}

        }
		sf::Texture* Texture::BlueEnemy()
		{
			return &_textures[0];
		}
		sf::Texture* Texture::RedEnemy()
		{
			return  &_textures[1];
		}
		sf::Texture* Texture::GreenEnemy()
		{
			return &_textures[2];
		}

		sf::Texture* Texture::Fireball()
		{
			return &_textures[3];
		}

		sf::Texture* Texture::CharacterIdle()
		{
			return &_textures[4];
		}

		sf::Texture* Texture::CharacterJump()
		{
			return &_textures[5];
		}

		sf::Texture* Texture::CharacterRun()
		{
			return &_textures[6];
		}

		sf::Texture* Texture::Dirt()
		{
			return &_textures[7];
		}

		sf::Texture* Texture::Ice()
		{
			return &_textures[8];
		}

		sf::Texture* Texture::Stone()
		{
			return &_textures[9];
		}

		sf::Texture* Texture::Web()
		{
			return &_textures[10];
		}

		sf::Texture* Texture::None()
		{
			return &_textures[11];
		}

		sf::Texture* Texture::StoneUp()
		{
			return &_textures[12];
		}

		sf::Texture* Texture::Grass()
		{
			return &_textures[13];
		}

		sf::Texture* Texture::IceUp()
		{
			return &_textures[14];
		}

		sf::Texture* Texture::Lader()
		{
			return &_textures[15];
		}

		std::string Texture::getPath(std::string str)
		{
			return TEXTURE_DIR + std::string("\\") + str;
		}
    }
}
