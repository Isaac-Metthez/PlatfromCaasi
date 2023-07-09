#include "FireBall.h"

namespace platfrom
{
	namespace logic
	{
#pragma region FireBall 
#pragma region Constructors
		FireBall::FireBall(sf::Vector2f pos)
		{
			_pos = pos;
			_hitBox = new hitBoxes::SphericalHitBox({ {0,0,8} });
			_acc = sf::Vector2f(0, simplePhysics::GRAVITY);
			_skin.setSize({ 8,8 });
			_skin.setScale({ _skin.getSize().x / 3.f,  _skin.getSize().y / 3.f });
			_skin.setOrigin(_skin.getSize() / 2.f);
		}
		FireBall::FireBall(std::ifstream& is)
		{
			is >> _pos;
			_hitBox = new hitBoxes::SphericalHitBox({ {0,0,8} });
			_acc = sf::Vector2f(0, simplePhysics::GRAVITY);
			_skin.setSize({ 8, 8 });
			_skin.setScale({ _skin.getSize().x / 3.f,  _skin.getSize().y / 3.f });
			_skin.setOrigin(_skin.getSize() / 2.f);
		}
#pragma endregion
#pragma region Public Methods
		Entity& FireBall::drawEntity(sf::RenderWindow& window, const sf::Vector2f refPos)
		{
			if (Platfrom::getConfig().getShowHitboxes())
				_hitBox->draw(window, _pos - refPos);
			_skin.setPosition(_pos - refPos);
			_skin.setTexture(Platfrom::getTexture().Fireball());
			window.draw(_skin);
			return *this;
		}
		bool FireBall::isOnView(const sf::View& view)
		{
			bool result = Entity::isOnView(view);
			if (!result && _thrown)
				Platfrom::getPage().removeEntity(this);
			return result;
		}
		bool FireBall::getReaction(Entity& hitting, sf::Vector2f collision)
		{
			auto* player = dynamic_cast<Character*>(&hitting);
			if (!_owner
				&& !_thrown
				&& Platfrom::getInputs().secondAction()
				&& player)
			{
				player->addToCarriedCollection(this); 
				_owner = player;
			}
			return !_owner;
		}
		void FireBall::fling(sf::Vector2f thrownVec)
		{
			_vel = thrownVec * 2.f;
			_thrown = true;
		}
		void FireBall::carry(sf::Vector2f newPosition)
		{
			_pos = newPosition;
			_vel = { 0,0 };
		}
		bool FireBall::hit(Entity& hitting, sf::Vector2f collision)
		{
			if (!_owner
			&& !dynamic_cast<Character*>(&hitting))
				return Entity::hit(hitting, collision);
			if (_thrown && 
				hitting.getReaction(*this, collision) &&
				&hitting != _owner && 
				!_owner->isInCarriedCollection(dynamic_cast<Portable*>(&hitting)))
			{
				Platfrom::getPage().removeEntity(this); 
				PersonifiedEntity* damaged = dynamic_cast<PersonifiedEntity*>(&hitting);
				if (damaged)
					damaged->kill();
			}
			return false;
		}
		std::ostream& FireBall::serialize(std::ostream& os) const
		{
			return os << typeid(*this).name() << " "
				<< _pos
				<< std::endl;
		}
#pragma endregion
#pragma endregion

	}
}