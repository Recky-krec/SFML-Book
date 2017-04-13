#ifndef GAME_H
#define GAME_H

#include "SFML/Graphics.hpp"
#include "World.hpp"
#include "Player.hpp"

class Game
{

public:
						Game();
	void				run();
  
private:

	void				processEvents();
	void				update(sf::Time timePerFrame);
	void				render();

private:

	sf::RenderWindow	window;
	sf::Time 			timePerFrame;
	bool 				isPaused;
	World 				world;
	Player 				player;
	
};

#endif // GAME_H
	