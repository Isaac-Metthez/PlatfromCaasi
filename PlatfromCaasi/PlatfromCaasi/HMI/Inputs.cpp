#include "Inputs.h"
#include <SFML/Graphics.hpp>

namespace platfrom
{
    namespace hmi
    {
#pragma region Inputs 
#pragma region Constructors
		Inputs::Inputs()
		{
			_memInputs.reserve(10);
			_memInputs.push_back(sf::Keyboard::isKeyPressed(_right));
			_memInputs.push_back(sf::Keyboard::isKeyPressed(_left));
			_memInputs.push_back(sf::Keyboard::isKeyPressed(_jump));
			_memInputs.push_back(sf::Keyboard::isKeyPressed(_up));
			_memInputs.push_back(sf::Keyboard::isKeyPressed(_down));
			_memInputs.push_back(sf::Mouse::isButtonPressed(_action));
			_memInputs.push_back(sf::Keyboard::isKeyPressed(_secondAction));
			_memInputs.push_back(sf::Keyboard::isKeyPressed(_select));
			_memInputs.push_back(sf::Keyboard::isKeyPressed(_escape));
			_memInputs.push_back(sf::Mouse::isButtonPressed(_mainMouse));
			_memInputs.push_back(sf::Mouse::isButtonPressed(_secondMouse));
			_memInputs.push_back(sf::Keyboard::isKeyPressed(_menuRight));
			_memInputs.push_back(sf::Keyboard::isKeyPressed(_menuLeft));
			_memInputs.push_back(sf::Keyboard::isKeyPressed(_menuUp));
			_memInputs.push_back(sf::Keyboard::isKeyPressed(_menuDown));
		}
#pragma endregion
#pragma region Public Methods
		bool Inputs::pressedKey(sf::Keyboard::Key &pressed)
		{
			for (int i = 0; i < sf::Keyboard::Key::KeyCount; i++)
			{
				if (sf::Keyboard::isKeyPressed(static_cast<sf::Keyboard::Key>(i)))
				{
					pressed = static_cast<sf::Keyboard::Key>(i);
					return true;
				}
			}
			return false;
		}
		bool Inputs::right()
		{
			return sf::Keyboard::isKeyPressed(_right);
		}
		bool Inputs::left()
		{
			return  sf::Keyboard::isKeyPressed(_left);
		}
		bool Inputs::jump()
		{
			return  sf::Keyboard::isKeyPressed(_jump);
		}
		bool Inputs::up()
		{
			return sf::Keyboard::isKeyPressed(_up);
		}
		bool Inputs::down()
		{
			return sf::Keyboard::isKeyPressed(_down);
		}
		bool Inputs::action()
		{
			return sf::Mouse::isButtonPressed(_action);
		}
		bool Inputs::secondAction()
		{
			return sf::Keyboard::isKeyPressed(_secondAction);
		}
		bool Inputs::select()
		{
			return sf::Keyboard::isKeyPressed(_select);
		}
		bool Inputs::escape()
		{
			return sf::Keyboard::isKeyPressed(_escape);
		}

		bool Inputs::mainMouse()
		{
			return sf::Mouse::isButtonPressed(_mainMouse);
		}

		bool Inputs::secondMouse()
		{
			return sf::Mouse::isButtonPressed(_secondMouse);
		}

		bool Inputs::menuRight()
		{
			return sf::Keyboard::isKeyPressed(_menuRight);
		}

		bool Inputs::menuLeft()
		{
			return sf::Keyboard::isKeyPressed(_menuLeft);
		}

		bool Inputs::menuUp()
		{
			return sf::Keyboard::isKeyPressed(_menuUp);
		}

		bool Inputs::menuDown()
		{
			return sf::Keyboard::isKeyPressed(_menuDown);
		}

		bool Inputs::reRight()
		{
			if (_memInputs[0])
			{
				_memInputs[0] = sf::Keyboard::isKeyPressed(_right);
				return false;
			}
			else
			{
				return _memInputs[0] = sf::Keyboard::isKeyPressed(_right);
			}
		}
		bool Inputs::reLeft()
		{
			if (_memInputs[1])
			{
				_memInputs[1] = sf::Keyboard::isKeyPressed(_left);
				return false;
			}
			else
			{
				return _memInputs[1] = sf::Keyboard::isKeyPressed(_left);
			}
		}
		bool Inputs::reJump()
		{
			if (_memInputs[2])
			{
				_memInputs[2] = sf::Keyboard::isKeyPressed(_jump);
				return false;
			}
			else
			{
				return _memInputs[2] = sf::Keyboard::isKeyPressed(_jump);
			}
		}
		bool Inputs::reUp()
		{
			if (_memInputs[3])
			{
				_memInputs[3] = sf::Keyboard::isKeyPressed(_up);
				return false;
			}
			else
			{
				return _memInputs[3] = sf::Keyboard::isKeyPressed(_up);
			}
		}
		bool Inputs::reDown()
		{
			if (_memInputs[4])
			{
				_memInputs[4] = sf::Keyboard::isKeyPressed(_down);
				return false;
			}
			else
			{
				return _memInputs[4] = sf::Keyboard::isKeyPressed(_down);
			}
		}
		bool Inputs::reAction()
		{
			if (_memInputs[5])
			{
				_memInputs[5] = sf::Mouse::isButtonPressed(_action);
				return false;
			}
			else
			{
				return _memInputs[5] = sf::Mouse::isButtonPressed(_action);
			}
		}
		bool Inputs::reSecondAction()
		{
			if (_memInputs[6])
			{
				_memInputs[6] = sf::Keyboard::isKeyPressed(_secondAction);
				return false;
			}
			else
			{
				return _memInputs[6] = sf::Keyboard::isKeyPressed(_secondAction);
			}
		}
		bool Inputs::reSelect()
		{
			if (_memInputs[7])
			{
				_memInputs[7] = sf::Keyboard::isKeyPressed(_select);
				return false;
			}
			else
			{
				return _memInputs[7] = sf::Keyboard::isKeyPressed(_select);
			}
		}
		bool Inputs::reEscape()
		{
			if (_memInputs[8])
			{
				_memInputs[8] = sf::Keyboard::isKeyPressed(_escape);
				return false;
			}
			else
			{
				return _memInputs[8] = sf::Keyboard::isKeyPressed(_escape);
			}
		}

		bool Inputs::reMainMouse()
		{
			if (_memInputs[9])
			{
				_memInputs[9] = sf::Mouse::isButtonPressed(_mainMouse);
				return false;
			}
			else
			{
				return _memInputs[9] = sf::Mouse::isButtonPressed(_mainMouse);
			}
		}

		bool Inputs::reSecondMouse()
		{
			if (_memInputs[10])
			{
				_memInputs[10] = sf::Mouse::isButtonPressed(_secondMouse);
				return false;
			}
			else
			{
				return _memInputs[10] = sf::Mouse::isButtonPressed(_secondMouse);
			}
		}

		bool Inputs::reMenuRight()
		{
			if (_memInputs[11])
			{
				_memInputs[11]= sf::Keyboard::isKeyPressed(_menuRight);
				return false;
			}
			else
			{
				return _memInputs[11] = sf::Keyboard::isKeyPressed(_menuRight);
			}
		}

		bool Inputs::reMenuLeft()
		{
			if (_memInputs[12])
			{
				_memInputs[12] = sf::Keyboard::isKeyPressed(_menuLeft);
				return false;
			}
			else
			{
				return _memInputs[12] = sf::Keyboard::isKeyPressed(_menuLeft);
			}
		}

		bool Inputs::reMenuUp()
		{
			if (_memInputs[13])
			{
				_memInputs[13] = sf::Keyboard::isKeyPressed(_menuUp);
				return false;
			}
			else
			{
				return _memInputs[13] = sf::Keyboard::isKeyPressed(_menuUp);
			}
		}

		bool Inputs::reMenuDown()
		{
			if (_memInputs[14])
			{
				_memInputs[14] = sf::Keyboard::isKeyPressed(_menuDown);
				return false;
			}
			else
			{
				return _memInputs[14] = sf::Keyboard::isKeyPressed(_menuDown);
			}
		}


#pragma endregion
#pragma endregion
	}
}
