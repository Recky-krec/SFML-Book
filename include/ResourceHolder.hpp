#ifndef RESOURCEHOLDER_HPP
#define RESOURCEHOLDER_HPP

#include "SFML/Graphics.hpp"

#include "ResourceIdentifiers.hpp"

#include <memory>
#include <string>
#include <cassert>

template<typename Resource, typename Identifier>
class ResourceHolder
{
public:
	void 					load(Identifier id, const std::string& filename);
	template <typename T>
	void 					load(Identifier id, const std::string& filename, const T& secondParam);

	Resource&				get(Identifier id);
	const Resource& 		get(Identifier id) const;


private:
	std::map<Textures::ID, std::unique_ptr<sf::Texture>> textureMap;

};

#include "ResourceHolder.inl"
#endif // RESOURCEHOLDER_HPP
