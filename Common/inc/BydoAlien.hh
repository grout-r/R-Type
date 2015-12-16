#ifndef _BYDO_ALIEN_HH_
# define _BYDO_ALIEN_HH_

# include "Alien.hh"

class BydoAlien : public Alien
{
public:
  BydoAlien(sf::Vector2f speed, sf::Vector2f pos, unsigned int id, float coeff);
  ~BydoAlien();

public:
  bool				update(std::vector<IObject*>&, sf::Clock const&);
  bool				update(sf::Clock const&);
  IObject	*BasicShoot();
};

# endif
