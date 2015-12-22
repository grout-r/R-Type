#include "GameCore.hh"

GameCore::GameCore(std::string const&ip, std::string const& port)
  : _clients(new std::vector<GamerInfo*>()),
    _network(new UDPNetworkHandler(ip, port, _clients)),
    _map(new MapController()),
    _factory(new FactoryManager(_map, "./level/Level1.lvl")),
    _referential(sf::Time(sf::microseconds(16666))),
    _running(true)
{
  _factory->initialiseLevel();
  this->run();
}

GameCore::~GameCore()
{
  for (auto& client : *_clients)
    {
      delete client;
    }
  delete _clients;
}

bool		GameCore::run()
{
  int count;
  sf::Time elapsed;

  if (!_network->initSocket())
    return false;

  _clock.restart();
  while (_running)
    {
      this->updateMap();

      while (_running && ((elapsed = getElapsedTimeSinceLoop()) > sf::microseconds(0)))
      	{
	  receivePacket();
	}
    }
}

void		GameCore::updateMap()
{
  std::vector<IObject*>		*aliens;
  std::vector<IServerPacket<ServerUDPResponse>*>	*toSend;

  _map->updateMap(_clock);
  aliens = _factory->update(_clock);
  for (auto it = aliens->begin(); it != aliens->end(); ++it)
    {
      _map->addObject(*it);
      updateMap();
    }
  toSend = generatePackets(aliens);
  toSend->insert(std::begin(*toSend), std::begin(*(_map->getMap())), std::end(*(_map->getMap())));
  this->sendMap(NULL, toSend);
  delete toSend;
}

sf::Time	GameCore::getElapsedTimeSinceLoop()
{
  sf::Time ret;

  ret = sf::microseconds(_clock.getElapsedTime().asMicroseconds() % _referential.asMicroseconds());
  return ret;
}

std::vector<IServerPacket<ServerUDPResponse>*>*		GameCore::generatePackets(std::vector<IObject*>* aliens)
{
  std::vector<IServerPacket<ServerUDPResponse>*>*	ret = new std::vector<IServerPacket<ServerUDPResponse>*>;

    for (std::vector<IObject*>::iterator it = aliens->begin(); it != aliens->end(); ++it)
      ret->push_back(new CreIAPacket(CRE_IA, 0, _maxId++, (*it)->getPos().x, (*it)->getPos().y, static_cast<Alien*>((*it))->getRealType()));
    return ret;
}

void							GameCore::sendMap(GamerInfo* client, std::vector<IServerPacket<ServerUDPResponse>*> *toSendMap)
{
  IServerPacket<ServerUDPResponse>*			packetToSend;

  while (!toSendMap->empty())
    {
      packetToSend = toSendMap->back();
      if (client)
	_network->sendTo(client, packetToSend);
      else
	_network->broadcast(packetToSend);
      delete packetToSend;
      toSendMap->pop_back();
    }
}

bool					GameCore::receivePacket()
{
  GamerInfo*				client;
  IClientPacket<ClientUDPCommand>*	packet;

  if ((client = _network->selectClient()))
    {
      packet = _network->receiveFrom(client);
      if (packet)
	processPacket(client, packet);
    }
  return true;
}

bool					GameCore::processPacket(GamerInfo* client,
								IClientPacket<ClientUDPCommand>* packet)
{
  switch (packet->getCommandType())
    {
    case CAUTH_UDP:
      authGamer(client, packet);
      break;
    case FIRE:
      gamerTryShoot(client, packet);
      break;
    case SEND_MOVE:
      gamerMove(client, packet);
      break;
    case DISCONNECT:
      gamerDisconnect(client, packet);
      break;
    default:
      break;
    }
  return true;
}


void							GameCore::authGamer(GamerInfo* client, IClientPacket<ClientUDPCommand>* packet)
{
  Player*						player;

  if (!client->isAuth())
    {
      client->setName(static_cast<CAuthUDPPacket*>(packet)->getData()->data);
      client->setAuth(true);
      client->setID(_maxId++);
      _map->addObject(new Player(sf::Vector2f(10,6), sf::Vector2f(50,50), client->getID()));
    }
   player = static_cast<Player*>(_map->getPlayer(client->getID()));
   _map->generatePacketsMap(player);
   _network->sendTo(client, new AuthUDPPacket(AUTH_UDP, 0, SUCCESS));
   this->sendMap(client, _map->getMap());
   _network->broadcast(new CrePlayPacket(CRE_PLAY, 0, player->getId(), player->getPos().x, player->getPos().y));
}

void					GameCore::gamerTryShoot(GamerInfo* client, IClientPacket<ClientUDPCommand>* packet)
{
  Player*				player = static_cast<Player*>(_map->getPlayer(client->getID()));

  if (player && client->isAuth())
    {
      player->tryShoot();
    }
}


void					GameCore::gamerMove(GamerInfo* client, IClientPacket<ClientUDPCommand>* packet)
{
  Player*				player = static_cast<Player*>(_map->getPlayer(client->getID()));

  if (player && client->isAuth())
    {
      player->setDirection(static_cast<SendMovePacket*>(packet)->getData()->dir);
      _map->updatePlayer(player, _clock);
      _network->broadcast(new MovePacket(MOVE, 0, client->getID(), player->getPos().x, player->getPos().y));
    }
}

void					GameCore::gamerDisconnect(GamerInfo* client, IClientPacket<ClientUDPCommand>* packet)
{
  _map->deletePlayer(client->getID());
}
