# include <string.h>
# include "CAuthUDPPacket.h"

CAuthUDPPacket::CAuthUDPPacket(ClientUDPCommand resp, int idx, int success, std::string const& name) : AClientPacket<ClientUDPCommand>(resp, sizeof(*_data)), _data(new CAuthUDPData)
{
  _header->magic = MAGIC;
  _header->command = resp;
  _header->size = sizeof(*_data);
  _header->idx = idx;
  bzero(_data->data, 256);
  memcpy(&(_data->data), name.c_str(), name.size());
  _data->magic = MAGIC;
}

CAuthUDPPacket::CAuthUDPPacket(ClientUDPHeader* header)
  : AClientPacket<ClientUDPCommand>(header->command, header->size), _data(new CAuthUDPData), _header(header)
{
}

CAuthUDPPacket::~CAuthUDPPacket()
{
}

void			CAuthUDPPacket::setRawData(std::string const& data)
{
  void*			buff;

  buff = (void*)data.c_str();
  memcpy(_data, buff, sizeof(*_data));
}

CAuthUDPData*		CAuthUDPPacket::getData() const
{
  return _data;
}

bool			CAuthUDPPacket::checkHeader()
{
  if (_header->magic != MAGIC)
    return false;
  else if (_header->command < CAUTH_UDP || _header->command > DISCONNECT)
    return false;
  else if (_header->size < 0)
    return false;
  return true;
}

std::string const&		CAuthUDPPacket::deserialize()
{
  char*				buff = new char[sizeof(*_header) + sizeof(*_data) + 1];
  static std::string		ret;

  memcpy(buff, _header, sizeof(*_header));
  memcpy(buff + sizeof(*_header), _data, sizeof(*_data));
  buff[sizeof(*_header) + sizeof(*_data)] = 0;
  ret = buff;
  return ret;
}
