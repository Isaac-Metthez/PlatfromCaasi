#pragma once
#include <SFML/Graphics.hpp>
#include "Logic/Blocks.h"
#include "Logic/Character.h"
#include "Logic/HitBox.h"
#include "HMI/Sequencer.h"
#include "Utils/EventLogger.h"
#include "HMI/Textures.h"
#include <vector>

namespace platfrom
{
	constexpr double NANOS_IN_SEC = 1000000000;

	/**
	 * Class Platfrom
	 *
	 * Platfrom is the main class to launch the game
	 */
	class Platfrom
	{
	public:
		Platfrom();
		virtual ~Platfrom();
		void launch();

		static hmi::Inputs& getInputs() { return _inputs; };
		static hmi::Sequencer::Page& getPage() { return *_page; };
		static hmi::Config& getConfig() { return _config; };
		static hmi::Texture& getTexture() { return *_texture; };
		static utils::EventLogger& getEventLogger() { return _eventLogger; };
		static double& getFPS() { return _fps; };
	protected:
		sf::View _view;
		sf::RenderWindow _window;
		hmi::Sequencer _sequencer;

		static hmi::Inputs _inputs;
		static hmi::Sequencer::Page* _page;
		static hmi::Config _config;
		static hmi::Texture *_texture;
		static utils::EventLogger _eventLogger;
		static double _fps;
	};
} 
