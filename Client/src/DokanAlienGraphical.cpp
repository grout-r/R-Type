#include "DokanAlienGraphical.hh"

DokanAlienGraphical::DokanAlienGraphical(sf::Vector2f speed, sf::Vector2f pos, unsigned int id, float coeff)
  : DokanAlien(speed, pos, id, coeff), GraphicalItem()
{
	_sprite->setTexture(*(ac->getAlien(DOKAN)));
	_sprite->setPosition(
	_pos.x / SCREENRATIO,
	_pos.y / SCREENRATIO
	);
}

bool DokanAlienGraphical::update(sf::Clock const& clock)
{
  bool	ret;

  _sprite->setRotation(_sprite->getRotation() + 1);
  ret = DokanAlien::update(clock);
  _sprite->setPosition(
		_pos.x,
		_pos.y
		);
	return (ret);
}

bool	DokanAlienGraphical::update(std::vector<IObject*>&, sf::Clock const&)
{
  return (true);
}