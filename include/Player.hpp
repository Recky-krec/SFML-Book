#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "SFML/Graphics.hpp"

#include "CommandQueue.hpp"

#include <map>

class Player
{
public:
	enum Action
	{
		MoveLeft,
		MoveRight,
		MoveUp,
		MoveDown,

	};

public:
						Player();

	void 				handleEvent(const sf::Event& event, CommandQueue& commands);
	void				handleRealtimeInput(CommandQueue& commands);

	void				assignKey(Action action, sf::Keyboard::Key key);
	sf::Keyboard::Key 	getAssignedKey(Action action) const;

private:
	void 				initializeActions();
	static bool 		isRealtimeAction(Action action);

private:
	std::map<sf::Keyboard::Key, Action> keyBinding;
	std::map<Action, Command>			actionBinding;

};

#endif //PLAYER_HPP