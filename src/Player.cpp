#include "Player.hpp"

#include "SFML/Graphics.hpp"

#include "Aircraft.hpp"
#include "Command.hpp"
#include "Category.hpp"

struct AircraftMover
{
	AircraftMover(float vx, float vy)
	: velocity(vx, vy)
	{
	}

	void operator() (Aircraft& aircraft, sf::Time) const
	{
		aircraft.accelerate(velocity);
	}

	sf::Vector2f velocity;
};



void Player::handleEvent(const sf::Event& event, CommandQueue& commands)
{
	//Show player position
	if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::P)
	{
		Command output;
		output.category = Category::PlayerAircraft;
		output.action = [] (SceneNode& s, sf::Time)
		{
			std::cout << s.getPosition().x << ", " << s.getPosition().y << std::endl;
		};
		commands.push(output);
	}

}

void Player::handleRealtimeInput(CommandQueue& commands)
{
	const float playerSpeed = 30.f;

	//Move left
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		Command moveLeft;
		moveLeft.category = Category::PlayerAircraft;
		moveLeft.action = derivedAction<Aircraft>(AircraftMover(-playerSpeed, 0.f));
		commands.push(moveLeft);
	}

	//Move right
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		Command moveRight;
		moveRight.category = Category::PlayerAircraft;
		moveRight.action = derivedAction<Aircraft>(AircraftMover(playerSpeed, 0.f));
		commands.push(moveRight);
	}

	//Move up
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		Command moveUp;
		moveUp.category = Category::PlayerAircraft;
		moveUp.action = derivedAction<Aircraft>(AircraftMover(0.f, -playerSpeed));
		commands.push(moveUp);
	}

	//Move down
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		Command moveDown;
		moveDown.category = Category::PlayerAircraft;
		moveDown.action = derivedAction<Aircraft>(AircraftMover(0.f, playerSpeed));
		commands.push(moveDown);
	}

}