#include <iostream>

template <typename Resource, typename Identifier>
void ResourceHolder<Resource, Identifier>::load(Identifier id, const std::string& filename)
{
	std::unique_ptr<Resource> resource(new Resource());
	if (!resource->loadFromFile(filename))
		throw std::runtime_error("ResourceHolder::load - Failed to load " + filename);
	std::cout << "Succeeded loading from file" + filename << std::endl;


	auto inserted = textureMap.insert(std::make_pair(id, std::move(resource)));
	assert(inserted.second);
}

template <typename Resource, typename Identifier>
Resource& ResourceHolder<Resource, Identifier>::get(Identifier id)
{
	auto found = textureMap.find(id);
	assert(found != textureMap.end());
	return *found->second;
}

template <typename Resource, typename Identifier>
const Resource& ResourceHolder<Resource, Identifier>::get(Identifier id) const
{
	auto found = textureMap.find(id);
	assert(found != textureMap.end());
	return *found->second;
}

template <typename Resource, typename Identifier>
template <typename T>
void ResourceHolder<Resource, Identifier>::load(Identifier id, const std::string& filename, const T& secondParam)
{
	 //overloaded duo to compatibility with shaders
	std::unique_ptr<Resource> resource(new Resource());
	if (!resource->loadFromFile(filename, secondParam))
		throw std::runtime_error("ResourceHolder::load - Failed to load " + filename);
	
	std::cout << "Succeeded loading from file" + filename << std::endl;

	auto inserted = textureMap.insert(std::make_pair(id, std::move(resource)));
	assert(inserted.second);
}