#include "World.hpp"

World::World(sf::RenderWindow& pWindow)
: window(pWindow)
, scrollSpeed(-50.f)				//speed world moves relative to us
, worldView(window.getDefaultView())

, worldBounds(
	0.f, 					//left x position
	0.f, 					//top y position
	worldView.getSize().x,			//width
	2000.f)					//height

, spawnPosition(
	worldView.getSize().x / 2.f, 			 //X
	worldBounds.height - worldView.getSize().y /2.f) //Y

, playerAircraft(nullptr)

{
	loadTextures();
	buildScene();
	worldView.setCenter(spawnPosition);
}

void World::loadTextures()
{
	textures.load(Textures::Eagle, "../assets/Eagle.png");
	textures.load(Textures::Raptor, "../assets/Raptor.png");
	textures.load(Textures::Desert, "../assets/tileableDesert.jpeg");
}

void World::buildScene()
{
	// Initialize the different layers
	for (std::size_t i = 0; i < LayerCount; ++i) //size_t is just like an unsigned int
	{
		SceneNode::Ptr layer(new SceneNode());
		sceneLayers[i] = layer.get();
		sceneGraph.attachChild(std::move(layer));
	}

	// Prepare the tiled background
	sf::Texture& texture = textures.get(Textures::Desert);
	sf::IntRect textureRect(worldBounds);
	texture.setRepeated(true);

	// Add the background sprite to the scene
	std::unique_ptr<SpriteNode> backgroundSprite(new SpriteNode(texture, textureRect));
	backgroundSprite->setPosition(worldBounds.left, worldBounds.top);
	sceneLayers[Background]->attachChild(std::move(backgroundSprite));

	// Add player's aircraft
	std::unique_ptr<Aircraft> leader(new Aircraft(Aircraft::Eagle, textures));
	playerAircraft = leader.get();
	playerAircraft->setPosition(spawnPosition);
	playerAircraft->setVelocity(0.f, 0.f);
	sceneLayers[Air]->attachChild(std::move(leader));

	// Add two escorting aircrafts, placed relatively to the main plane
	std::unique_ptr<Aircraft> leftEscort(new Aircraft(Aircraft::Raptor, textures));
	leftEscort->setPosition(-80.f, 50.f);
	playerAircraft->attachChild(std::move(leftEscort));

	std::unique_ptr<Aircraft> rightEscort(new Aircraft(Aircraft::Raptor, textures));
	rightEscort->setPosition(80.f, 50.f); 
	playerAircraft->attachChild(std::move(rightEscort));

}

void World::draw()
{
	window.setView(worldView);
	window.draw(sceneGraph);
}

void World::update(sf::Time dt)
{
	// Scroll the world
	worldView.move(0.f, scrollSpeed * dt.asSeconds());
	playerAircraft->setVelocity(0.f, 0.f);

	// Forward commands to scene graph, adapt velocity (scrolling, diagonal correction)
	while (!commandQueue.isEmpty())
		sceneGraph.onCommand(commandQueue.pop(), dt);

	sf::Vector2f velocity = playerAircraft->getVelocity();

	// If moving diagonally, reduce velocity (to have always same velocity)
	if (velocity.x != 0.f && velocity.y != 0.f)
		playerAircraft->setVelocity(velocity / std::sqrt(2.f));

	//Keep moving at scroll velocity, so it never stops
	playerAircraft->accelerate(0.f, scrollSpeed);

	keepInsideBounds();

	// Apply movements
	sceneGraph.update(dt);
}

CommandQueue& World::getCommandQueue()
{
	return commandQueue;
}

void World::keepInsideBounds()
{
	//Rect at (0,0) with size of view width x view height (1280x720)
	sf::FloatRect viewBounds(worldView.getCenter() - worldView.getSize() / 2.f,
							 worldView.getSize());

	const float borderDistance = 40.f;

	sf::Vector2f position = playerAircraft->getPosition();
	position.x = std::max(position.x, viewBounds.left + borderDistance);
	position.x = std::min (position.x, viewBounds.left + viewBounds.width - borderDistance);

	position.y = std::max(position.y, viewBounds.top + borderDistance);
	position.y = std::min(position.y, viewBounds.top + viewBounds.height - borderDistance);

	playerAircraft->setPosition(position);
}