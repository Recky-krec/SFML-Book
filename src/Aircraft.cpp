#include "Aircraft.hpp"
#include "SFML/Graphics.hpp"

Textures::ID toTextureID(Aircraft::Type pType)
{
	switch (pType)
	{
		case Aircraft::Eagle:
			return Textures::Eagle;

		case Aircraft::Raptor:
			return Textures::Raptor;

	}
}

Aircraft::Aircraft(Type pType, const TextureHolder& textures)
: type(pType) 								//Initialises the type of aircraft
, sprite(textures.get(toTextureID(pType))) 	//Initialises the sprite
{
	//Aligning the origin of the sprite to the center
	sf::FloatRect bounds = sprite.getLocalBounds();
	sprite.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
}

void Aircraft::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
	//window,draw(...)
	target.draw(sprite, states);
}

unsigned int Aircraft::getCategory() const
{
	switch(type)
	{
		case Eagle:
			return Category::PlayerAircraft;

		/*case Raptor:
			return Category::EnemyAircraft;*/

		default:
			return Category::EnemyAircraft;
	}
}