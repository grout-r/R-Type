#ifndef _FACTORY_MANAGER_HH_
# define _FACTORY_MANAGER_HH_

# include <vector>
# include "MapController.hh"
# include "LevelLoader.hh"
# include "AlienFactory.hpp"

class FactoryManager
{
  //changer les char * en std::string
public:
  FactoryManager(MapController* , const char*);
  ~FactoryManager();

  void		update();
  void		initialiseLevel();
  void		changeLevel(char *);

private:
  unsigned int			_nbFactory;
  MapController			*_map;
  LevelLoader			_levelLoader;
  std::vector<IAlienFactory*>	_factories;
};

#endif