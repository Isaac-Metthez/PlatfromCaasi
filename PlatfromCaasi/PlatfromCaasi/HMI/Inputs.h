#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

namespace platfrom
{
	namespace hmi
	{
		/**
		 * Class Inputs
		 *
		 * Get if inputs from keyboard or mouse are pressed. 
		 * Get if inputs has a rising edge.
		 */
		class Inputs
		{
		public:
			Inputs();
			bool pressedKey(sf::Keyboard::Key & pressed);
			bool right();
			bool left();
			bool jump();
			bool up();
			bool down();
			bool action();
			bool secondAction();
			bool select();
			bool escape();
			bool mainMouse();
			bool secondMouse();
			bool menuRight();
			bool menuLeft();
			bool menuUp();
			bool menuDown();

			bool reRight();
			bool reLeft();
			bool reJump();
			bool reUp();
			bool reDown();
			bool reAction();
			bool reSecondAction();
			bool reSelect();
			bool reEscape();
			bool reMainMouse();
			bool reSecondMouse();
			bool reMenuRight();
			bool reMenuLeft();
			bool reMenuUp();
			bool reMenuDown();
		protected:
			sf::Keyboard::Key _right = sf::Keyboard::D;
			sf::Keyboard::Key _left = sf::Keyboard::A;
			sf::Keyboard::Key _jump = sf::Keyboard::Space;
			sf::Keyboard::Key _up = sf::Keyboard::W;
			sf::Keyboard::Key _down = sf::Keyboard::S;
			sf::Keyboard::Key _secondAction = sf::Keyboard::LShift;
			sf::Keyboard::Key _select = sf::Keyboard::Enter;
			sf::Keyboard::Key _escape = sf::Keyboard::Escape;
			sf::Keyboard::Key _menuRight = sf::Keyboard::Right;
			sf::Keyboard::Key _menuLeft = sf::Keyboard::Left;
			sf::Keyboard::Key _menuUp = sf::Keyboard::Up;
			sf::Keyboard::Key _menuDown = sf::Keyboard::Down;
			sf::Mouse::Button _mainMouse = sf::Mouse::Button::Left;
			sf::Mouse::Button _secondMouse = sf::Mouse::Button::Right;
			sf::Mouse::Button _action = sf::Mouse::Button::Left;

			std::vector<bool> _memInputs;

		};
	}
}
