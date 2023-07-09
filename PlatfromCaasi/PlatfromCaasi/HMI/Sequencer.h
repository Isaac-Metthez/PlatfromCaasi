#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <filesystem>
#include <chrono>
#include <queue>
#include <fstream>
#include <thread>
#include <string>
#include <exception>
#include "../Logic/AchievedLevels.h"
#include "../Logic/Physics.h"
#include "../Logic/Entity.h"
#include "../Logic/Character.h"
#include "../Logic/FireBall.h"
#include "../Logic/Mobs.h"
#include "../Logic/Portable.h"
#include "../Paths.h"

namespace platfrom
{
	namespace hmi
	{
		/**
		 * Class Sequencer
		 *
		 * Sequencer manage display page. 
		 * The sub classes page is called to display and return the page to call in the next cycle. 
		 */
		class Sequencer
		{
		public:
			Sequencer(sf::RenderWindow& window, sf::View& view);
			~Sequencer() = default;
			bool loadFont(const std::string& filePath);
			class Page
			{
			public:
				Page(Sequencer& super);
				virtual ~Page() = default ;
				virtual Page& foreground(sf::RenderWindow& window) = 0;
				virtual void removeEntity(logic::Entity* removed);
				virtual std::string getDebugInfo();
				virtual Page* operator()();
			protected:
				Sequencer& _super;
			};
			Page* getFirstPage() { return &_startPage; }
		protected:
			sf::Font _font;
			sf::RenderWindow& _window;
			sf::View& _view;
			logic::AchievedLevels _achievedLevels;
			

			class Start : public Page
			{
			public:
				Start(Sequencer& super);
				Page& foreground(sf::RenderWindow& window);
			protected:
				sf::Text _start;
				sf::Text _options;
				sf::Text _debug;
				sf::Text _quit;
				std::vector<sf::Text*> _textCollection;
				int _selected = -1;
			} _startPage;

			class SelectMap : public Page
			{
			public:
				SelectMap(Sequencer& super);
				~SelectMap() override;
				Page& foreground(sf::RenderWindow& window);
			protected:
				bool _getChildItemDone = false;
				typedef struct sMap{ sf::Text text; std::filesystem::path path; bool authorized = true; } map;
				std::vector<map> _maps;
				map* _selected = nullptr;
				float _centerSelection = 0;
				std::chrono::steady_clock::time_point _delay = std::chrono::steady_clock::now();
				
				
			} _selectMapPage;

			class Game : public Page
			{
			public:
				Game(Sequencer& super);
				~Game() override;
				Page& foreground(sf::RenderWindow& window);
				void removeEntity(logic::Entity* removed) override;
				std::string getDebugInfo();
				bool loadMap(std::filesystem::path path);
			protected:
				void deleteCollection();
				std::filesystem::path _levelPath;
				std::string _levelName;
				std::chrono::steady_clock::time_point _physicClock = std::chrono::steady_clock::now();
				logic::Character _caasi;
				std::list<logic::Entity*> _onViewCollection;
				std::list<logic::Entity*> _entityCollection;
				std::list<logic::Entity*> _removedCollection;
			} _gamePage;

			class Option : public Page
			{
			public:
				Option(Sequencer& super);
				Page& foreground(sf::RenderWindow& window);
			protected:
				sf::Text _logEvent;
				sf::Text _hitBox;
				sf::Text _creative;
				sf::Text _quit;
				std::vector<sf::Text*> _textCollection;
				int _selected = -1;
			} _optionPage;

			class LevelFinished : public Page
			{
			public:
				LevelFinished(Sequencer& super);
				Page& foreground(sf::RenderWindow& window);
			protected:
				std::vector<sf::Text> _textCollection;
				bool _selected = false;
			} _levelFinishedPage;

			class Debug : public Page
			{
			public:
				Debug(Sequencer& super);
				Page& foreground(sf::RenderWindow& window);
				void debugsecondWindow(sf::RenderWindow& window);
			protected:
				bool _secondWindow = false;

			} _debugPage;

			class Quit : public Page
			{
			public:
				Quit(Sequencer& super);
				Page& foreground(sf::RenderWindow& window);
			protected:
			} _quitPage;

			friend class Page;
			friend class Start;
			friend class Game;
			friend class Option;
			friend class Debug;
			friend class Credits;
			friend class Quit;
		};
	}
}

