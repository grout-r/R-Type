#include "DokanAlien.hh"
#include "BasicAlienProjectile.hh"
#include <stdlib.h>

extern unsigned int _maxId;

DokanAlien::DokanAlien(sf::Vector2f const& speed, sf::Vector2f const& pos, unsigned int id, float coeff)
  : Alien(speed, pos, sf::Vector2i(100, 100), id, coeff)
{
  _life = 3;
  _realType = ObjectInfo::DOKAN;
  _f = 1;
  _rad = M_PI / 4;
  _a = 6;
}

DokanAlien::~DokanAlien()
{}


bool		DokanAlien::update(sf::Clock const& clock, std::vector<IObject*>& map)
{
  this->update(clock);
  this->collision(map);
  return (_isAlive);
}

bool		DokanAlien::update(sf::Clock const& clock)
{
  if (_pos.x + _size.x < 0 || _pos.x > MAP_SIZE_X
      || _pos.y + _size.y < 0 || _pos.y > MAP_SIZE_Y)
    _isAlive = false;
  this->_pos.x = this->_pos.x - this->_speed.x;
  this->_pos.y = _pos.y - (_a * cos((0.23 * _f * (this->_pos.x / (150 * _coeff)) * M_PI) + M_PI * _coeff + _rad));
  if (static_cast<int>(_pos.x + _pauseShoot) % 320 == 0)
    _isShoot = true;
  return true;
}

IObject		*DokanAlien::BasicShoot()
{
  sf::Vector2f pos;
  sf::Vector2f speed;

  pos.x = _pos.x;
  pos.y = _pos.y + (_size.y / 2);
  _isShoot = false;
  speed.x = _speed.y + (_speed.y / 3);
  speed.y = speed.x;
  return new BasicAlienProjectile(speed, pos, _maxId++);
}
