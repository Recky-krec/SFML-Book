#ifndef SPRITENODE_HPP
#define SPRITENODE_HPP

#include "SFML/Graphics.hpp"
#include "SceneNode.hpp"

class SpriteNode : public SceneNode
{
public:
	explicit 			SpriteNode(const sf::Texture& texture);
						SpriteNode(const sf::Texture& texture, const sf::IntRect& rect);

private:
	virtual void 		drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;

private:
	sf::Sprite 			sprite;

};

#endif //SPRITENODE_HPP
