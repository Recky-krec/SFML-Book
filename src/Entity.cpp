#include "Entity.hpp"

void Entity::setVelocity(sf::Vector2f pVelocity)
{
	velocity = pVelocity;
}

void Entity::setVelocity(float vx, float vy)
{
	velocity.x = vx;
	velocity.y = vy;
}

sf::Vector2f Entity::getVelocity() const
{
	return velocity;
}

void Entity::updateCurrent(sf::Time dt)
{
	//expression move(offset) is a shortcut for setPosition(getPosition() + offset)
	this->move(velocity * dt.asSeconds());
}

void Entity::accelerate(sf::Vector2f pVelocity)
{
	velocity += pVelocity;
}

void Entity::accelerate(float vx, float vy)
{
	velocity.x += vx;
	velocity.y += vy;
}