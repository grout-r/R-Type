#include <string.h>
#include "NickPacket.h"
#include <unistd.h>

NickPacket::NickPacket(ClientTCPCommand command, std::string const& name)
  : AClientPacket<ClientTCPCommand>(command, sizeof(*_data) + sizeof(*_header)), _data(new NickData), _header(new ClientTCPHeader)
{
  _header->magic = MAGIC;
  _header->command = command;
  _header->size = sizeof(*_data);
  bzero(_data->data, sizeof(*_data));
  memcpy(&(_data->data), name.c_str(), name.size());
}

NickPacket::NickPacket(ClientTCPHeader* header)
  : AClientPacket<ClientTCPCommand>(header->command, header->size + sizeof(*_header)), _data(new NickData), _header(header)
{
  std::cout << "there" << std::endl;
}

NickPacket::~NickPacket()
{
}

void			NickPacket::setRawData(std::string const& data)
{
  void*			buff;

  buff = (void*)data.c_str();
  memcpy(_data, buff, sizeof(*_data));
}

NickData*		NickPacket::getData() const
{
  return _data;
}

bool			NickPacket::checkHeader()
{
  if (_header->magic != MAGIC)
    return false;
  else if (_header->command < AUTH_TCP|| _header->command > QUIT)
    return false;
  else if (_header->size < 0)
    return false;
  return true;
}

char*				NickPacket::deserialize()
{
  char*				buff = new char[sizeof(*_header) + sizeof(*_data) + 1];

  memcpy(buff, _header, sizeof(*_header));
  memcpy(buff + sizeof(*_header), _data, sizeof(*_data));
  buff[sizeof(*_header) + sizeof(*_data)] = 0;
  return buff;
}
