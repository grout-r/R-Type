#pragma once

#include "BasicAlienProjectile.hh"
#include "GraphicalItem.h"

class BasicAlienProjectileGrapical : public BasicAlienProjectile, public GraphicalItem
{
public:
	BasicAlienProjectileGrapical(sf::Vector2f speed, sf::Vector2f pos, unsigned int);
	bool			update(sf::Clock const&);
	bool			update(std::vector<IObject*>&, sf::Clock const&) {};
};
