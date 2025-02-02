#pragma once
# include "ScantAlien.hh"
# include "GraphicalItem.h"

class ScantAlienGraphical : public ScantAlien, public GraphicalItem
{
public:
  ScantAlienGraphical(sf::Vector2f const& speed, sf::Vector2f const& pos, unsigned int, float coeff);

public:
  bool				update(sf::Clock const&);
  bool				update(std::vector<IObject*>&, sf::Clock const&);
};
