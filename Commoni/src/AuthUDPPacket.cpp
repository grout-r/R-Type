# include <string.h>
# include "AuthUDPPacket.h"

AuthUDPPacket::AuthUDPPacket(ServerUDPResponse resp, int idx, int success, std::string const& name) : AServerPacket<ServerUDPResponse>(resp, sizeof(*_data) + sizeof(*_header)), _data(new AuthUDPData)
{
  _header->magic = MAGIC;
  _header->command = resp;
  _header->size = sizeof(*_data);
  _header->idx = idx;
  _data->success = success;
  bzero(_data->name, 256);
  memcpy(&(_data->name), name.c_str(), name.size());
  _data->magic = MAGIC;
}

AuthUDPPacket::AuthUDPPacket(ServerUDPHeader* header)
  : AServerPacket<ServerUDPResponse>(header->command, header->size + sizeof(*_header)), _data(new AuthUDPData), _header(header)
{
}

AuthUDPPacket::~AuthUDPPacket()
{
}

void			AuthUDPPacket::setRawData(char *data)
{
  memcpy(_data, (void *)data, sizeof(*_data));
}

AuthUDPData*		AuthUDPPacket::getData() const
{
  return _data;
}

bool			AuthUDPPacket::checkHeader()
{
  if (_header->magic != MAGIC)
    return false;
  else if (_header->command < AUTH_UDP || _header->command > MOVE)
    return false;
  else if (_header->size < 0)
    return false;
  return true;
}

char*				AuthUDPPacket::deserialize()
{
  char*				buff = new char[sizeof(*_header) + sizeof(*_data) + 1];

  memcpy(buff, _header, sizeof(*_header));
  memcpy(buff + sizeof(*_header), _data, sizeof(*_data));
  buff[sizeof(*_header) + sizeof(*_data)] = 0;
  return buff;
}