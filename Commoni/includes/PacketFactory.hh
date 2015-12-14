#ifndef PACKETFACTORY_H_
# define PACKETFACTORY_H_

#include "IClientPacket.hh"
#include "IServerPacket.hh"
#include "NewGamePacket.h"
#include "NickPacket.h"
#include "JoinPacket.hh"
#include "AuthTCPPacket.h"
#include "GameInfoPacket.h"
#include "GameListPacket.h"
#include "DesGamePacket.h"
#include "FailPacket.h"
#include "GameOverPacket.h"
#include "AuthUDPPacket.h"
#include "CrePlayPacket.h"
#include "DelPlayPacket.h"
#include "CreShotPacket.h"
#include "DelShotPacket.h"
#include "CreIAPacket.h"
#include "DelIAPacket.h"
#include "SendMovePacket.h"
#include "FirePacket.h"
#include "CAuthUDPPacket.h"
#include "NetworkDefines.h"

class PacketFactory
{
public:
  PacketFactory();
  virtual ~PacketFactory();

  IClientPacket<ClientTCPCommand>*		build(ClientTCPHeader*);
  IClientPacket<ClientUDPCommand>*		build(ClientUDPHeader*);
  IServerPacket<ServerTCPResponse>*		build(ServerTCPHeader*);
  IServerPacket<ServerUDPResponse>*		build(ServerUDPHeader*);
};

#endif
