#include "PacketFactory.hh"
#include "NewGamePacket.h"

PacketFactory::PacketFactory()
{}

PacketFactory::~PacketFactory()
{}

IClientPacket*		PacketFactory::build(ClientCommand cmd, std::string const& data)
{
  switch(cmd)
    {
    // case DESCRIBE_GAME:
    //   return new DescribePacket(data)
    //   break;
    // case SET_NICK:
    //   return new SetNickPacket(data)
    //   break;
    // case JOIN_GAME:
    //   return new JoinPacket(data)
    //   break;
    case CREATE_GAME:
      return new NewGamePacket(data);
      break;
    default:
      return NULL;
    }
}

std::string const&	PacketFactory::disassemble(IClientPacket* packet)
{
  std::string		ret;

  // ret +=
}
