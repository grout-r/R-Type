#include "Waves.hh"

Waves::Waves(int count, sf::Time time, sf::vector2i pos, sf::vector2f speed, float coeff)
  : _count(count), _time(time), _pos(pos), _speed(speed), _coeff(coeff)
{}

Waves::~Waves() {}

void		Waves::pop()
{
  _time = _time - _frequency:
  _count = _count - 1;
}

int	        &Waves::getCount() const
{
  return _count;
}

sf::Time	&Waves::getTime() const
{
  return _time;
}

sf::Vector2i   &Waves::getSize() const
{
  return _size;
}

sf::Vector2f   &Waves::getCoeff() const
{
  return _coeff;
}
