#include <iostream>
#include <algorithm>
#include "MapController.hh"
#include "ObjectInfo.hpp"
#include "Alien.hh"
#include "Player.hh"

unsigned int _maxId;

MapController::MapController()
  : _deserializedMap(new std::vector<IServerPacket<ServerUDPResponse>*>)
{}

MapController::~MapController()
{
  delete _deserializedMap;
}

void			MapController::generatePacketsMap(IObject* player)
{
  for (std::vector<IObject*>::iterator it = _map.begin(); it != _map.end(); ++it)
    {
      if (*it == player)
	continue ;
      switch ((*it)->getObjType())
	{
	case ObjectInfo::PLAYER :
	  _deserializedMap->push_back(new CrePlayPacket(CRE_PLAY, 0, (*it)->getId(), (*it)->getPos().x + (*it)->getSize().x, (*it)->getPos().y));
	  break ;
	case ObjectInfo::SHOT :
	  _deserializedMap->push_back(new CreObjPacket(CRE_OBJ, 0, (*it)->getId(), (*it)->getPos().x, (*it)->getPos().y, (*it)->getSpeed().x, ObjectInfo::PLAYERREGULAR));
	  break ;
	default :
	  break ;
	}
    }
}

std::vector<IServerPacket<ServerUDPResponse>*>*	MapController::getMap() const
{
  return _deserializedMap;
}

void		MapController::addObject(IObject* obj)
{
  _map.push_back(obj);
}

void		MapController::updateMap(sf::Clock const& clock)
{
  auto it = _map.begin();

  _toAppend.clear();
  _deserializedMap->clear();
  while (it != _map.end())
    {
      (*it)->update(clock, _map);
      checkNewObj(it, (*it));
      if (it == _map.end())
	break;
      ++it;
    }
  _map.insert(std::end(_map), std::begin(_toAppend), std::end(_toAppend));
}

void		MapController::checkNewObj(std::vector<IObject*>::iterator& it, IObject* obj)
{
  if (obj->isShooting())
    {
      obj->setShooting(false);
      if (obj->getObjType() == ObjectInfo::PLAYER)
  	{
	  BasicPlayerProjectile* shot = static_cast<Player*>(obj)->BasicShoot();
  	  _toAppend.push_back(shot);
	  _deserializedMap->push_back(new CreObjPacket(CRE_OBJ, 0, _maxId - 1, shot->getPos().x, shot->getPos().y, shot->getSpeed().x, ObjectInfo::PLAYERREGULAR));
  	}
      if (obj->getObjType() == ObjectInfo::ALIEN)
  	{
	  BasicAlienProjectile* shot = static_cast<Alien*>(obj)->BasicShoot();
  	  _toAppend.push_back(shot);
  	  _deserializedMap->push_back(new CreObjPacket(CRE_OBJ, 0, _maxId - 1, shot->getPos().x, shot->getPos().y, shot->getSpeed().x, ObjectInfo::ALIENREGULAR));
  	}
    }
  if (!obj->isAlive())
    {
      if (obj->getObjType() == ObjectInfo::ALIEN)
	std::cout << "DELETING !!" << std::endl;
	
      _deserializedMap->push_back(new DelItemPacket(DEL_ITEM, 0, obj->getId()));
      delete this->getPlayer(obj->getId());
      it = _map.erase(it);
    }
}

void		MapController::updatePlayer(IObject* player, sf::Clock const& clock)
{
  player->update(clock, _map);
}

IObject*	MapController::getPlayer(int id)
{
  if (id == -1)
    return NULL;
  for (std::vector<IObject*>::iterator it = _map.begin(); it != _map.end(); ++it)
    {
      if ((*it)->getId() == id)
	return (*it);
    }
  return NULL;
}

void		MapController::deletePlayer(int id)
{
  delete (this->getPlayer(id));
  _map.erase(std::find(_map.begin(), _map.end(), this->getPlayer(id)));
}
