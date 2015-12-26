#pragma once
#include "Player.hh"
#include "GraphicalItem.h"

class PlayerGraphical : public Player, public GraphicalItem
{
public:
  PlayerGraphical(sf::Vector2f const& speed, sf::Vector2f const& pos, unsigned int id);
  bool		update(std::vector<IObject*>&, sf::Clock const&);
  bool		update(sf::Clock const&);
  sf::Drawable*		getDrawable();

  private:
  sf::Sprite*       _spriteMoving;
  sf::Sprite*       _spriteStatic;
  sf::Vector2f      _lastPos;
};
