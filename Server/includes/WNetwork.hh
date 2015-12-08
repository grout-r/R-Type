#ifndef WNETWORK_H_
# define WNETWORK_H_

# ifdef _WIN32

# include <winsock2.h>
# include <ws2tcpip.h>

# include "INetwork.hh"

# pragma comment(lib, "Ws2_32.lib")

template <class T>
class WNetwork : public INetwork<T>
{
private:
  T*					_socket;
  SOCKET				_listen;
  struct addrinfo*			_addr;
  fd_set*				_readSet;

public:
  WNetwork();
  ~WNetwork();

public:
  bool					initServerSocket(std::string const &ip, std::string const &port);
  SOCKET					acceptSocket();
  TransmitStatus			recvData(void *data, int size, SOCKET, ClientDatas *addr);
  TransmitStatus			sendData(void *data, int size, SOCKET, ClientDatas *addr);
  SOCKET					getFd() const;
  void					selectClients(std::vector<SOCKET>& fd, struct timeval *to);
  bool					closeConnection(SOCKET);
};

# include "WNetwork.tpp"

#endif

#endif
