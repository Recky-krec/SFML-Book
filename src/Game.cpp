#include "Game.hpp"

#include "SFML/Graphics.hpp"

Game::Game()
: window(sf::VideoMode(1280.f, 720.f), "SFML-GameDev")	//Resolution / Title
, world(window)											//World object
, timePerFrame(sf::seconds(1.f / 60.f))					//Frames per second (60FPS)
, isPaused(false)										//At the start, it isn't paused ;)

{
}

void Game::run()
{
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	
	while(window.isOpen())
	{
		processEvents();
		sf::Time deltaTime = clock.restart();
		timeSinceLastUpdate += deltaTime;

		//Getting game logic to run at constant rate
		while(timeSinceLastUpdate > timePerFrame)
		{
			timeSinceLastUpdate -= timePerFrame;
			processEvents();
			
			if (!isPaused)
			{
				update(timePerFrame);
			}	
		}
		render();

	}
}

void Game::processEvents()
{
	CommandQueue& commands = world.getCommandQueue();
	
	sf::Event event;
	while(window.pollEvent(event))
	{
		//Handling Events
		player.handleEvent(event, commands);

		switch(event.type)
		{
			case sf::Event::Closed:
			{
				window.close();
			}
			case sf::Event::GainedFocus:
			{
				isPaused = false;
				break;
			}
			case sf::Event::LostFocus:
			{
				isPaused = true;
				break;
			}
		}
	}
	//Handling realtime input
	player.handleRealtimeInput(commands);
}

void Game::update(sf::Time timePerFrame)
{
	//Updating logic
	world.update(timePerFrame);
}

void Game::render()
{
	window.clear();	
	world.draw();
	window.setView(window.getDefaultView());
	window.display();
}

