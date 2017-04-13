#ifndef WORLD_HPP
#define WORLD_HPP

#include "SFML/Graphics.hpp"
#include "SceneNode.hpp"
#include "SpriteNode.hpp"
#include "ResourceIdentifiers.hpp"
#include "Aircraft.hpp"
#include "CommandQueue.hpp"
#include <cstdlib>
#include <memory>
#include <array>


class World : private sf::NonCopyable
{

public:
	explicit 				World(sf::RenderWindow& pWindow);
	void					update(sf::Time dt);
	void					draw();

	CommandQueue& 			getCommandQueue();

private:
	void 					loadTextures();
	void 					buildScene();

private:
	enum Layer
		{
			Background,
			Air,
			LayerCount,
		};

private:
	sf::RenderWindow&					window;
	sf::View							worldView;
	TextureHolder						textures;
	SceneNode							sceneGraph;
	std::array<SceneNode*, LayerCount>	sceneLayers;
	CommandQueue						commandQueue;

	sf::FloatRect						worldBounds;
	sf::Vector2f						spawnPosition;
	float 								scrollSpeed;
	Aircraft*							playerAircraft;

};

#endif //WORLD_HPP
