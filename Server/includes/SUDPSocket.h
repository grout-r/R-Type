#ifndef UDPSOCKET_H_
# define UDPSOCKET_H_

# include "NetworkDefines.h"
# include "SINetwork.hh"
# include "Exceptions.hpp"

class			SUDPSocket
{
private:
  SOCKET		_listen;

public:
  SUDPSocket();
  ~SUDPSocket();

  int			startNetwork(std::string const &ip, std::string const &port, ConnectionData*);
  void			sendData(const void *buffer, int size, SOCKET sock, ClientDatas *addr);
  void			rcvData(void* buffer, int size, SOCKET sock, ClientDatas *addr);
  SOCKET		acceptClient();
};

#endif