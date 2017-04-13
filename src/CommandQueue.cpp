#include "CommandQueue.hpp"
#include "SceneNode.hpp"
#include "Command.hpp"

void CommandQueue::push(const Command& command)
{
	queue.push(command);
}

Command CommandQueue::pop()
{
	Command command = queue.front();
	queue.pop(); //deletes the first elemenet
	return command;
}

bool CommandQueue::isEmpty() const
{
	return queue.empty();
}
