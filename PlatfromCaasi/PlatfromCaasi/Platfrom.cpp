#include "Platfrom.h"
#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>
#include <string>
#include <windows.h>
#include <iostream>
#include "Logic/Blocks.h"
#include "Logic/Character.h"
#include "Logic/HitBox.h"
#include "Logic/Physics.h"
#include "Logic/BlockDecorators.h"
#include "HMI/Sequencer.h"

namespace platfrom
{
#pragma region Platfrom 
#pragma region Static
	hmi::Inputs Platfrom::_inputs;
	hmi::Sequencer::Page* Platfrom::_page = nullptr;
	hmi::Config Platfrom::_config;
	hmi::Texture* Platfrom::_texture = nullptr;
	utils::EventLogger Platfrom::_eventLogger(PLATFROM_DATA);
	double Platfrom::_fps = 60;
#pragma endregion
#pragma region Constructors
	Platfrom::Platfrom() :
		_window(sf::VideoMode(1920, 1080), "PlatfromCaasi", 7U, sf::ContextSettings(0,0,10)),
		_sequencer(_window, _view)
	{
		_eventLogger.setLogCondition([]() -> bool { return _config.getLogEvent(); });
		_view.reset(sf::FloatRect(0, 0, 1920, 1080)),
		_window.setView(_view); 
		if (!_texture)
			_texture = new hmi::Texture;
		auto icon = _texture->CharacterIdle()->copyToImage();
		_window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
	}
	Platfrom::~Platfrom()
	{
		delete _texture;
	}
#pragma endregion
#pragma region Public
	void Platfrom::launch()
	{
		_page = _sequencer.getFirstPage();
		std::chrono::steady_clock::time_point cycleClock = std::chrono::steady_clock::now();
		int fpsCount = 0;
		while (_window.isOpen())
		{
			sf::Event event{};
			while (_window.pollEvent(event))
			{
				if (event.type == sf::Event::Resized)
				{
					_view = sf::View(sf::FloatRect(0, 0, static_cast<float>(event.size.width), static_cast<float>(event.size.height)));
					_window.setView(_view);
				}
				if (event.type == sf::Event::Closed)
					_window.close();
			}
			if (200 < static_cast<double>(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - cycleClock).count()))
			{
				_fps = fpsCount * NANOS_IN_SEC / static_cast<double>(std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::steady_clock::now() - cycleClock).count());
				cycleClock = std::chrono::steady_clock::now();
				fpsCount = 0;
			}
			if (_window.hasFocus())
			{
				++fpsCount;
				_page = (*_page)();
				_window.display();
				_window.clear();
			}
		}

		
	}
#pragma endregion
#pragma endregion
}

