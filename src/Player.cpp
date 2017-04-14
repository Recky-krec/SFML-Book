#include "Player.hpp"

#include "SFML/Graphics.hpp"

#include "Aircraft.hpp"
#include "Command.hpp"
#include "Category.hpp"

struct AircraftMover
{

public:
			AircraftMover(float vx, float vy) : velocity(vx, vy) {}	
	void 	operator() (Aircraft& aircraft, sf::Time) const
	{
		aircraft.accelerate(velocity);
	}

private:
	sf::Vector2f velocity;
};


Player::Player()
{
	// Set initial key bindings
	keyBinding[sf::Keyboard::Left] = MoveLeft;
	keyBinding[sf::Keyboard::Right] = MoveRight;
	keyBinding[sf::Keyboard::Down] = MoveDown;
	keyBinding[sf::Keyboard::Up] = MoveUp;

	// Set initial action bindings
	initializeActions();

	// Assign all categories to player's aircraft
	for (auto& pair : actionBinding)
		pair.second.category = Category::PlayerAircraft;
}

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
	// Traverse all assigned keys and check if they are pressed
	for (auto pair : keyBinding)
	{
		// If key is pressed, lookup action and trigger corresponding command
		if (sf::Keyboard::isKeyPressed(pair.first) && isRealtimeAction(pair.second))
			commands.push(actionBinding[pair.second]);
	}
}

void Player::assignKey(Action action, sf::Keyboard::Key key)
{
	// Remove all keys that already map to action
	for (auto itr = keyBinding.begin(); itr != keyBinding.end(); )
	{
		if (itr->second == action)
			keyBinding.erase(itr++);
		else
			++itr;
	}

	// Insert new binding
	keyBinding[key] = action;
	//keyBinding.insert(std::make_pair(key, action));
}

sf::Keyboard::Key Player::getAssignedKey(Action action) const
{
	for (auto pair : keyBinding)
	{
		if(pair.second == action)
			return pair.first;
	}
	return sf::Keyboard::Unknown;
}

void Player::initializeActions()
{
	const float playerSpeed = 30.f;

	actionBinding[MoveLeft].action = derivedAction<Aircraft>(AircraftMover(-playerSpeed, 0.f));
	actionBinding[MoveRight].action = derivedAction<Aircraft>(AircraftMover(playerSpeed, 0.f));
	actionBinding[MoveDown].action = derivedAction<Aircraft>(AircraftMover(0.f, playerSpeed));
	actionBinding[MoveUp].action = derivedAction<Aircraft>(AircraftMover(0.f, -playerSpeed));
}

bool Player::isRealtimeAction(Action action)
{
	switch(action)
	{
		case MoveLeft:
		case MoveRight:
		case MoveDown:
		case MoveUp:
			return true;

		default:
			return false;
	}
}