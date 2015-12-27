# include "BonusSpeed.hh"

BonusSpeed::BonusSpeed(sf::Vector2f const& speed,
		       sf::Vector2f const& pos,
		       unsigned int id,
		       float coeff)
  : ABonus(speed, pos, sf::Vector2i(50, 50), id),
    _stay(false),
    _fact(-1)
{
}

BonusSpeed::~BonusSpeed()
{
}

void		BonusSpeed::actionBonus(Object* player)
{
  static_cast<Player*>(player)->speedUp();
}

bool		BonusSpeed::update(const sf::Clock& clock)
{
  if (_pos.x + _size.x < 0 || _pos.x > MAP_SIZE_X
      || _pos.y + _size.y < 0 || _pos.y > MAP_SIZE_Y)
    _isAlive = false;
  if (this->_pos.x <= MAP_SIZE_X / 3)
    {
      _fact *= -1;
      _stay = true;
    }
  if (_stay && this->_pos.x >= 2 * MAP_SIZE_X / 3)
    _fact *= -1;
  this->_pos.x = this->_pos.x + _fact * this->_speed.x;
  this->_pos.y -= 1;
  return true;
}

bool		BonusSpeed::update(const sf::Clock& clock, std::vector<IObject*>& map)
{
  this->update(clock);
  this->collision(map);
  return _isAlive;
}
