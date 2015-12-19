#ifndef _BOMB_HH_
# define _BOMB_HH_

# include "Projectile.hh"

class Bomb : public Projectile
{
public:
  Bomb(ObjectInfo::Type, sf::Vector2f, sf::Vector2i, unsigned int);
  ~Bomb();

public:
  bool				update(sf::Clock const&, std::vector<IObject*>&);
  bool				update(sf::Clock const&);
  void	        boum();

private:
  short		_countDown;
};

# endif
