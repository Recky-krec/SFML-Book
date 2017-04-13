#include "SceneNode.hpp"

#include "SFML/Graphics.hpp"
#include "Command.hpp"
#include "Category.hpp"

#include <cassert>
#include <iostream>

SceneNode::SceneNode()
: children()
, parent(nullptr)

{
}

void SceneNode::attachChild(Ptr child)
{
	// set its parent pointer to the current node
	child->parent = this;
	// add it to the list of children
	children.push_back(std::move(child));
}

SceneNode::Ptr SceneNode::detachChild(const SceneNode& node)
{
	auto found = std::find_if(children.begin(), children.end(), [&] (Ptr& p) { return p.get() == &node; });
	assert(found != children.end());

	Ptr result = std::move(*found);
	result->parent = nullptr;
	children.erase(found);
	return result;
}

void SceneNode::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	//combines the parent's absolute transform with the current node's relative one
	//the result is the absolute transform of the current node
	states.transform *= getTransform(); //Now, states.transform contains the absolute world transform
	// Draw node and children with changed transform
	drawCurrent(target, states);
	drawChildren(target, states); // we're using draw recursively

}

void SceneNode::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
	// Do nothing by default
}

void SceneNode::drawChildren(sf::RenderTarget& target, sf::RenderStates states) const
{
	for (const Ptr& child : children)
	{
		child->draw(target, states);
	}
}

void SceneNode::update(sf::Time dt)
{
	updateCurrent(dt); 
	updateChildren(dt); // we're using update recursively
}

void SceneNode::updateCurrent(sf::Time dt)
{
	// Do nothing by default
}

void SceneNode::updateChildren(sf::Time dt)
{
	for (const Ptr& child : children)
	{
		child->update(dt);
	}
}

sf::Vector2f SceneNode::getWorldPosition() const
{
	return getWorldTransform() * sf::Vector2f();
}

sf::Transform SceneNode::getWorldTransform() const
{
	sf::Transform transform = sf::Transform::Identity;

	for (const SceneNode* node = this; node != nullptr; node = node->parent) //it goes up on the hierarchy
		transform = node->getTransform() * transform;

	return transform;
}

unsigned int SceneNode::getCategory() const
{
	return Category::Scene;
}

void SceneNode::onCommand(const Command& command, sf::Time dt)
{
	if (command.category & getCategory())
		command.action(*this, dt);

	for (Ptr& child : children)
	{
		child->onCommand(command, dt);
	}


}