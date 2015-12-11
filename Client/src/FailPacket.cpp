# include <string.h>
# include "FailPacket.h"

FailPacket::FailPacket(ServerTCPResponse resp) : AServerPacket<ServerTCPResponse>(resp), _header(new ServerTCPHeader)
{
  _header->command = resp;
  _header->magic = MAGIC;
  _header->size = 0;

}

FailPacket::~FailPacket()
{
}

std::string const&		FailPacket::deserialize()
{
  char*				buff = new char[sizeof(*_header) + 1];
  static std::string		ret;

  memcpy(buff, _header, sizeof(*_header));
  buff[sizeof(*_header)] = 0;
  ret = buff;
  return ret;
}

bool				FailPacket::checkHeader()
{
  if (_header->magic != MAGIC)
    return false;
  else if (_header->command < AUTH || _header->command > FAIL)
    return false;
  else if (_header->size < 0)
    return false;
  return true;
}

void				FailPacket::setRawData(std::string const& data)
{
}
