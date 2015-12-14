#ifndef _IALIEN_FACTORY_HH_
# define _IALIEN_FACTORY_HH_

# include <SFML/System/Clock.hpp>
# include "IObject.hh"
# include "ObjectInfo.hpp"
# include "Waves.hh"

class IAlienFactory
{
public:
  virtual ~IAlienFactory() {};
  virtual IObject		   *getNextEnemy(sf::Clock clock) = 0;
  virtual ObjectInfo::WaveType	   getType() const = 0;
  virtual void			   setWave(Waves) = 0;
};

#endif