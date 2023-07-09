#include <chrono>
#include <thread>
#include <iostream>
#include <filesystem>
#include "../Platfrom.h"
#include "Sequencer.h"

namespace platfrom
{
    namespace hmi
    {
#pragma region View 
        Sequencer::Sequencer(sf::RenderWindow& window, sf::View& view):
    		_window(window),
            _view(view),
            _startPage(*this),
            _gamePage(*this),
            _optionPage(*this),
            _debugPage(*this),
            _selectMapPage(*this),
            _levelFinishedPage(*this),
            _quitPage(*this)
        {
            std::string path = "C:\\Windows\\Fonts\\calibri.ttf";
            while (!loadFont(path))
            {
                ShowWindow(GetConsoleWindow(), SW_SHOW);
                std::cout << "Can't load font with this current path : " << path << std::endl << "Please enter the path of calibri font" << std::endl << "=> ";
                std::cin >> path;
                ShowWindow(GetConsoleWindow(), SW_HIDE);
            }
        }
        bool Sequencer::loadFont(const std::string &filePath)
        {
            return _font.loadFromFile(filePath);
        }

        Sequencer::Page::Page(Sequencer& super) :_super(super)
        {
        }
        void Sequencer::Page::removeEntity(logic::Entity* removed)
        {
        }
        std::string Sequencer::Page::getDebugInfo()
        {
            return std::string();
        }
        Sequencer::Page* Sequencer::Page::operator()()
        {
            return &foreground(_super._window);
        }

        Sequencer::Start::Start(Sequencer& super): Page(super)
        {
            _textCollection.push_back(&_start);
            _textCollection.push_back(&_options);
            _textCollection.push_back(&_debug);
            _textCollection.push_back(&_quit);

            _start.setString("Start game");
            _options.setString("Options");
            _debug.setString("Debug");
            _quit.setString("Quit");

            float y = 300;
            for (sf::Text* text : _textCollection)
            {
                text->setFillColor(sf::Color(128, 128, 128));
                text->setOrigin(0,0);
                text->setFont(super._font);
                text->setCharacterSize(40);
                text->setStyle(sf::Text::Bold);
                text->setPosition(sf::Vector2f(100 , y));
                y += 100;
            }
        }
        Sequencer::Page& Sequencer::Start::foreground(sf::RenderWindow& window)
        {
            int newSelected = -1;

            const sf::Vector2i mousePos(sf::Mouse::getPosition() - window.getPosition());
            for (int i = 0; i < _textCollection.size(); i++)
            {
                if (_textCollection[i]->getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y - 25)))
                {
                    newSelected = i;
                }
                window.draw(*_textCollection[i]);
            }
            if (Platfrom::getInputs().reMenuUp() || Platfrom::getInputs().reMenuLeft())
                newSelected = _selected > 0  ? _selected - 1 : static_cast<int>(_textCollection.size() - 1);
            if (Platfrom::getInputs().reMenuDown() || Platfrom::getInputs().reMenuRight())
                newSelected = _selected >= 0 && _selected < static_cast<int>(_textCollection.size()) - 1 ? _selected + 1 : 0 ;

            if (newSelected >= 0)
            {
                if (_selected >= 0)
                    _textCollection[_selected]->setFillColor(sf::Color(128, 128, 128));

                _textCollection[newSelected]->setFillColor(sf::Color(255, 255, 255));
                _selected = newSelected;
            }
            if (Platfrom::getInputs().reEscape())
                return _super._quitPage;

            if (newSelected != -1 && Platfrom::getInputs().reMainMouse()
             || _selected != -1 && Platfrom::getInputs().reSelect())
            {
                switch (_selected)
                {
                case 0:
                    return _super._selectMapPage;
                case 1:
                    return _super._optionPage;
                case 2:
                    return _super._debugPage;
                case 3:
                    return _super._quitPage;
                }
            }
            return *this;
        }

        Sequencer::Game::Game(Sequencer& super) : Page(super), _caasi(_super._window)
        {}
        Sequencer::Game::~Game()
        {
            for (const logic::Entity* entity : _entityCollection)
            {
                delete(entity);
            }
            _entityCollection.clear();
        }
        bool Sequencer::Game::loadMap(std::filesystem::path path)
        {
            std::ifstream is(path);
            is >> _levelName;

            while (!is.eof())
            {
                std::string type, name, fullname;
                is >> type >> name;
                fullname = type + " " + name;

                if (fullname == typeid(logic::mobs::SimpleMob).name())
                    _entityCollection.push_back(new logic::mobs::SimpleMob(is));
                else if (fullname == typeid(logic::mobs::PortableMob).name())
                    _entityCollection.push_back(new logic::mobs::PortableMob(is));
                else if (fullname == typeid(logic::blocks::Block).name())
                    _entityCollection.push_back(new logic::blocks::Block(is));
                else if (fullname == typeid(logic::FireBall).name())
                    _entityCollection.push_back(new logic::FireBall(is));
                else if (!is.eof())
                {
                    is.close();
                    for (const logic::Entity* entity : _entityCollection)
                    {
                        delete(entity);
                    }
                    _entityCollection.clear();

                    _caasi.reset();
                    Platfrom::getEventLogger().addLogEvent("Map " + _levelName + " has been corrupted");
                    return false;
                }
            }
            is.close();

            for (logic::Entity* entity : _entityCollection)
            {
                entity->
                    callKinetics().
                    setAcctualisedKinetics();
            }
            Platfrom::getEventLogger().addLogEvent("Map " + _levelName + " loaded");
            _levelPath = path;
            return true;
        }
        void Sequencer::Game::deleteCollection()
        {
            for (const logic::Entity* entity : _entityCollection)
            {
                delete(entity);
            }
            _entityCollection.clear();
        }
        Sequencer::Page& Sequencer::Game::foreground(sf::RenderWindow& window)
        {
            // Cycle time
            const double deltatime = static_cast<double>(std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::steady_clock::now() - _physicClock).count());
            logic::simplePhysics::Simplekinematics::setdtime(
                deltatime > logic::simplePhysics::MAXTIME ?
                logic::simplePhysics::MAXTIME / logic::simplePhysics::TIMEDIVIDOR :
                deltatime / logic::simplePhysics::TIMEDIVIDOR);
            _physicClock = std::chrono::steady_clock::now();

            // select entity who are on view
            for (logic::Entity* entity : _entityCollection)
            {
                if (entity->isOnView(_super._view)
                    && !_caasi.isInCarriedCollection(dynamic_cast<logic::Portable*>(entity))
                        || _caasi.isBackOfTheCarried(dynamic_cast<logic::Portable*>(entity)))
                    _onViewCollection.push_back(entity);
            }

            _caasi.feature().
                callKinetics().
                calculateCollision(_onViewCollection).
                setAcctualisedKinetics();
            _caasi.carry();


            // Reference position
            _super._view.setCenter(_caasi.getNextPos());
            _super._window.setView(_super._view);

            for (logic::Entity* entity : _onViewCollection)
            {
                entity->feature().
                    callKinetics().
                    calculateCollision(_onViewCollection).
                    calculateCollision(_caasi).
                    setAcctualisedKinetics().
                    drawEntity(window);
            }

           _caasi.
                drawEntity(window);

           _onViewCollection.clear();

            _removedCollection.sort();
            while (!_removedCollection.empty())
            {
                _removedCollection.unique();
                if (_removedCollection.front() != &_caasi)
                {
                    _entityCollection.remove(_removedCollection.front());
                    Platfrom::getEventLogger().addLogEvent(std::string("Remove ") + typeid(*_removedCollection.front()).name() + " from entity collection");
                    delete _removedCollection.front();
                }
                _removedCollection.pop_front();
            }

            if (Platfrom::getInputs().reEscape())
            {
                deleteCollection();
                _caasi.reset();
                _super._view.setCenter(_super._view.getSize() / 2.f);
                _super._window.setView(_super._view);
                Platfrom::getEventLogger().addLogEvent("Quit game");
                return _super._selectMapPage;
            }

            if (!_caasi.isAlive())
            {
                deleteCollection();
                _caasi.reset();
                Platfrom::getEventLogger().addLogEvent("Restart after dead of caasi");
                loadMap(_levelPath);
            }

            if (_caasi.getFinish())
            {
                deleteCollection();
                _caasi.reset();
                _super._achievedLevels.addAchievedLevel(_levelName);
                Platfrom::getEventLogger().addLogEvent("Cassi as finished level :" + _levelName);
                _super._achievedLevels.save();
                _super._view.setCenter(_super._view.getSize()/2.f);
                _super._window.setView(_super._view);
                return _super._levelFinishedPage;
            }
            return *this;
        }
        void Sequencer::Game::removeEntity(logic::Entity* removed)
        {
            _removedCollection.push_back(removed);
        }
        std::string Sequencer::Game::getDebugInfo()
        {
            std::string result;
            result += "Character info :";
            result += "\n\tPosition :\n";
            result += "\t\tx :";
            result += std::to_string(_caasi.getPos().x);
            result += " y :";
            result += std::to_string(_caasi.getPos().y);
            result += "\n\tVelocity :\n";
            result += "\t\tx :";
            result += std::to_string(_caasi.getVel().x);
            result += " y :";
            result += std::to_string(_caasi.getVel().y);
            result += "\n\tAcceleration :\n";
            result += "\t\tx :";
            result += std::to_string(_caasi.getAcc().x);
            result += " y :";
            result += std::to_string(_caasi.getAcc().y);
            return result;
        }

        Sequencer::Debug::Debug(Sequencer& super) : Page(super)
        {
        }
        Sequencer::Page& Sequencer::Debug::foreground(sf::RenderWindow& window)
        {
            if (!_secondWindow)
            {
                std::thread(&Debug::debugsecondWindow, this, std::ref(window)).detach();
                _secondWindow = true;
            }
            return _super._startPage;
        }
        void Sequencer::Debug::debugsecondWindow(sf::RenderWindow& window)
        {
            sf::RenderWindow secondWindow(sf::VideoMode(600, 400), "PlatfromCaasi debug");
            auto icon = Platfrom::getTexture().CharacterIdle()->copyToImage();
            secondWindow.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
            sf::Text text("", _super._font, 24);
            // try if principal window are not destructed
            try
            {
                while (secondWindow.isOpen() && window.isOpen())
                {
                    sf::Event event{};
                    while (secondWindow.pollEvent(event))
                    {
                        if (event.type == sf::Event::Resized)
                            secondWindow.setView(sf::View(sf::FloatRect(0, 0, static_cast<float>(event.size.width), static_cast<float>(event.size.height))));
                        if (event.type == sf::Event::Closed)
                            secondWindow.close();
                    }

                    // set text
                    text.setString(
                        "FPS : " + std::to_string(Platfrom::getFPS()).substr(0, 6) +
                        "\nLast log : " + Platfrom::getEventLogger().getLastLog() +
                        "\n" + Platfrom::getPage().getDebugInfo());

                    // Window
                    secondWindow.clear();
                    secondWindow.draw(text);
                    secondWindow.display();
                }
            }
            catch (std::bad_exception &e)
            {
                // It's worth to be notified 
                std::cout << "Second window: " << e.what();
                secondWindow.close();
            }
            catch (...)
            {
                std::cout << "Second window:unexpected exception with ";
                secondWindow.close();
            }
            _secondWindow = false;
        }

        Sequencer::Quit::Quit(Sequencer& super) : Page(super)
        {
        }
        Sequencer::Page& Sequencer::Quit::foreground(sf::RenderWindow& window)
        {
            window.close();
            return *this;
        }

        Sequencer::Option::Option(Sequencer& super) : Page(super)
        {
            _textCollection.push_back(&_hitBox);
            _textCollection.push_back(&_logEvent);
            _textCollection.push_back(&_creative);
            _textCollection.push_back(&_quit);

            _hitBox.setString("Show hitboxes : " + std::string(Platfrom::getConfig().getShowHitboxes() ? "Enabled" : "Disabled"));
            _logEvent.setString("Log event : " + std::string(Platfrom::getConfig().getLogEvent() ? "Enabled" : "Disabled"));
            _creative.setString("Creative : " + std::string(Platfrom::getConfig().getCreative() ? "Enabled" : "Disabled"));
            _quit.setString("Save and quit");

            float y = 300;
            for (sf::Text* text : _textCollection)
            {
                text->setFillColor(sf::Color(128, 128, 128));
                text->setOrigin(0, 0);
                text->setFont(super._font);
                text->setCharacterSize(40);
                text->setStyle(sf::Text::Bold);
                text->setPosition(sf::Vector2f(100, y));
                y += 100;
            }
        }
        Sequencer::Page& Sequencer::Option::foreground(sf::RenderWindow& window)
        {
            int newSelected = -1;
            bool quit = false;
            const sf::Vector2i mousePos(sf::Mouse::getPosition() - window.getPosition());
            for (int i = 0; i < _textCollection.size(); i++)
            {
                if (_textCollection[i]->getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y - 25)))
                {
                    newSelected = i;
                }
                window.draw(*_textCollection[i]);
            }
            if (Platfrom::getInputs().reMenuUp() || Platfrom::getInputs().reMenuLeft())
                newSelected = _selected > 0 ? _selected - 1 : static_cast<int>(_textCollection.size() - 1);
            if (Platfrom::getInputs().reMenuDown() || Platfrom::getInputs().reMenuRight())
                newSelected = _selected >= 0 && _selected < static_cast<int>(_textCollection.size()) - 1 ? _selected + 1 : 0;

            if (newSelected >= 0)
            {
                if (_selected >= 0)
                    _textCollection[_selected]->setFillColor(sf::Color(128, 128, 128));

                _textCollection[newSelected]->setFillColor(sf::Color(255, 255, 255));
                _selected = newSelected;
            }

            if (newSelected != -1 && Platfrom::getInputs().reMainMouse()
                || _selected != -1 && Platfrom::getInputs().reSelect())
            {
                switch (_selected)
                {
                case 0:
                    Platfrom::getConfig().setShowHitbox(!Platfrom::getConfig().getShowHitboxes());
                    Platfrom::getEventLogger().addLogEvent("Active/Disabled Show hitboxes option");
                    break;
                case 1:
                    Platfrom::getConfig().setLogEvent(!Platfrom::getConfig().getLogEvent());
                    Platfrom::getEventLogger().addLogEvent("Active/Disabled LogEvent option");
                    break;
                case 2:
                    Platfrom::getConfig().setCreative(!Platfrom::getConfig().getCreative());
                    Platfrom::getEventLogger().addLogEvent("Active/Disabled Creative");
                    break;
                default:
                    quit = true;
                    break;
                }
                _hitBox.setString("Show hitboxes : " + std::string(Platfrom::getConfig().getShowHitboxes() ? "Enabled" : "Disabled"));
                _logEvent.setString("Log event : " + std::string(Platfrom::getConfig().getLogEvent() ? "Enabled" : "Disabled"));
                _creative.setString("Creative : " + std::string(Platfrom::getConfig().getCreative() ? "Enabled" : "Disabled"));
            }
            if (quit || Platfrom::getInputs().reEscape())
            {
                Platfrom::getConfig().save();
                Platfrom::getEventLogger().addLogEvent("Save options");
                return _super._startPage;
            }
            return *this;
        }

        Sequencer::SelectMap::SelectMap(Sequencer& super) : Page(super)
        {
        }
        Sequencer::SelectMap::~SelectMap()
        {
        }
        Sequencer::Page& Sequencer::SelectMap::foreground(sf::RenderWindow& window)
        {
            if (!_getChildItemDone)
            {
                _super._achievedLevels.reload();

                _maps.clear();
                bool authorised = true;
                std::string path(MAPS_PATH);
                std::ifstream is;
                for (const auto& entry : std::filesystem::directory_iterator(path))
                    if (!entry.is_directory())
                    {
                        _maps.emplace_back();
                        _maps.back().path = entry.path();
                        if (authorised)
                        {
                            _maps.back().text.setFillColor(sf::Color(128, 128, 128));
                            _maps.back().authorized = true;
                        }
                        else
                        {
                            _maps.back().text.setFillColor(sf::Color(64, 64, 64));
                            _maps.back().authorized = false;
                        }
                        _maps.back().text.setOrigin(0, 0);
                        _maps.back().text.setFont(_super._font);
                        _maps.back().text.setCharacterSize(40);
                        _maps.back().text.setStyle(sf::Text::Bold);
                        is.open(entry.path());
                        std::string name;
                        is >> name;
                        _maps.back().text.setString(name);
                        is.close();

                        authorised = _super._achievedLevels.isAchieved(name);
                    }
                _getChildItemDone = true;
            }
            const sf::Vector2i mousePos(sf::Mouse::getPosition() - window.getPosition());
            bool selectNext = Platfrom::getInputs().reMenuDown() || Platfrom::getInputs().reMenuRight();
            bool selectPrevious = Platfrom::getInputs().reMenuUp() || Platfrom::getInputs().reMenuLeft();
            bool confirm = false;
            float y = _centerSelection;

            for (auto map = _maps.begin(); map < _maps.end(); ++map)
            {
                y += 100;
                if (selectNext && (_selected == &(*map) || !_selected))
                {
                    if (_selected)
                    {
                        auto nextSelection = map == --_maps.end() ? &_maps.front() : &(*(map + 1));
                        if (nextSelection->authorized)
                        {
                            _selected->text.setFillColor(sf::Color(128, 128, 128));
                            _selected = nextSelection;
                            _selected->text.setFillColor(sf::Color(255, 255, 255));
                        }
                    }
                    else
                    {
                        _selected = &_maps.front();
                        _selected->text.setFillColor(sf::Color(255, 255, 255));
                    }
                    if (_selected != &_maps.back() && _selected->text.getPosition().y > 800)
                        _centerSelection += 800 - _selected->text.getPosition().y;
                    if (_selected == &_maps.front() && _selected->text.getPosition().y < 200)
                        _centerSelection += 100 - _selected->text.getPosition().y;
                    selectNext = false;
                }
                else if (selectPrevious && (_selected == &(*map) || !_selected))
                {
                    if (_selected)
                    {
                        auto nextSelection = map == _maps.begin() ? &_maps.back() : &(*(map - 1));
                        if (nextSelection->authorized)
                        {
                            _selected->text.setFillColor(sf::Color(128, 128, 128));
                            _selected = nextSelection;
                            _selected->text.setFillColor(sf::Color(255, 255, 255));
                        }
                    }
                    else
                    {
                        auto nextSelection = &_maps.back();
                        if (nextSelection->authorized)
                        {
                            _selected = nextSelection;
                            _selected->text.setFillColor(sf::Color(255, 255, 255));
                        }
                    }
                    if (_selected)
                    {
                        if (_selected != &_maps.front() && _selected->text.getPosition().y < 200)
                            _centerSelection += 200 - _selected->text.getPosition().y;
                        if (_selected == &_maps.back() && _selected->text.getPosition().y > 800)
                            _centerSelection += 900 - _selected->text.getPosition().y;
                    }
                    selectPrevious = false;
                }
                else if (map->text.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y - 25)))
                {
                    if (Platfrom::getInputs().reMainMouse())
                    {
                        confirm = true;
                    }
                    if (map->authorized && _selected != &(*map))
                    {
                        if (_selected)
                            _selected->text.setFillColor(sf::Color(128, 128, 128));
                        _selected = &(*map);
                        map->text.setFillColor(sf::Color(255, 255, 255));
                    }
                    if (map->authorized && 300 < std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - _delay).count())
                    {
                        if (_selected != &_maps.back() && _selected->text.getPosition().y > 800)
                            _centerSelection += 800 - _selected->text.getPosition().y;
                        else if (_selected == &_maps.front() && _selected->text.getPosition().y < 200)
                            _centerSelection += 100 - _selected->text.getPosition().y;
                        else if (_selected != &_maps.front() && _selected->text.getPosition().y < 200)
                            _centerSelection += 200 - _selected->text.getPosition().y;
                        else if (_selected == &_maps.back() && _selected->text.getPosition().y > 800)
                            _centerSelection += 900 - _selected->text.getPosition().y;
                        _delay = std::chrono::steady_clock::now();
                    }
                }
                map->text.setPosition(sf::Vector2f(100, y));
            }
            for (auto& map : _maps)
                window.draw(map.text);
            if (_selected &&
                (Platfrom::getInputs().reSelect()
                || confirm))
            {
                _getChildItemDone = false;
                if (_super._gamePage.loadMap(_selected->path))
                {
                    _selected = nullptr;
                    return _super._gamePage;
                }
            }
            if (Platfrom::getInputs().reEscape())
            {
                _selected = nullptr;
                _getChildItemDone = false;
                return _super._startPage;
            }
            return *this;
        }

        Sequencer::LevelFinished::LevelFinished(Sequencer& super) : Page(super)
        {
            _textCollection.emplace_back("Congratulations you finished level! \nNext level is unlocked", super._font, 40);
            _textCollection.emplace_back("Ok", super._font, 40);

            float y = 300;
            for (auto& text : _textCollection)
            {
                text.setFillColor(sf::Color(128, 128, 128));
                text.setOrigin(0, 0);
                text.setStyle(sf::Text::Bold);
                text.setPosition(sf::Vector2f(600, y));
                y += 100;
            }
        }
        Sequencer::Page& Sequencer::LevelFinished::foreground(sf::RenderWindow& window)
        {
            const sf::Vector2i mousePos(sf::Mouse::getPosition() - window.getPosition());
            bool isOnOK = false;

            if (Platfrom::getInputs().reMenuDown() || Platfrom::getInputs().reMenuRight()
                || Platfrom::getInputs().reMenuUp() || Platfrom::getInputs().reMenuLeft())
            {
                _textCollection[1].setFillColor(sf::Color(255, 255, 255));
                _selected = true;
            }
            if (_textCollection[1].getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y - 25)))
            {
                _textCollection[1].setFillColor(sf::Color(255, 255, 255));
                _selected = true;
                isOnOK = true;
            }

            if (_selected
                && (Platfrom::getInputs().reSelect()
                || (isOnOK && Platfrom::getInputs().reMainMouse())))
                return _super._selectMapPage;

            for (auto& text : _textCollection)
                window.draw(text);

            return *this;
        }
#pragma endregion
}
}
