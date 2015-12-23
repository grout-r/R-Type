#include "Obstacle.hh"

Obstacle::Obstacle(sf::Vector2f speed, sf::Vector2f pos, unsigned int id, float coeff)
  : Alien(speed, pos, sf::Vector2i(800, 200), id, coeff)
{
  _realType = ObjectInfo::OBSTACLE;
}

Obstacle::~Obstacle()
{
}

bool		        Obstacle::update(sf::Clock const& clock, std::vector<IObject*>&)
{
  this->update(clock);
  return true;
}

bool		        Obstacle::update(sf::Clock const&)
{
  _pos.x -= _speed.x;
  return true;
}

IObject*		Obstacle::BasicShoot()
{
  return NULL;
}