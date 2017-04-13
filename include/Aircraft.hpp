#ifndef AIRCRAFT_HPP
#define AIRCRAFT_HPP

#include "SFML/Graphics.hpp"
#include "Entity.hpp"
#include "ResourceHolder.hpp"
#include "ResourceIdentifiers.hpp"

class Aircraft : public Entity // inherits indirectly SceneNode
{

public:
	enum Type
	{
		Eagle,
		Raptor,
	};

public:
	explicit 			 Aircraft(Type pType, const TextureHolder& textures);
	
	virtual unsigned int getCategory() const;

private:
	virtual void		 drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;

private:
	Type 				type;
	sf::Sprite 			sprite;

};

#endif //AIRCRAFT_HPP
