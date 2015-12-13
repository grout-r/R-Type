#include "Client.h"
#include "CNetworkHandler.hh"
#include <iostream>
#include "NetworkDefines.h"


Client::Client(std::string const & ip, std::string const & port)
	: _network(new CNetworkHandler(ip, port))
{
  if (_network->initSocket())
    {
      start();
    }
}

Client::~Client()
{
  delete _network;
}

void Client::start()
{
  std::string		str;
  std::string		str2;

  while (1)
    {
      std::getline(std::cin, str);

      std::cout << str << std::endl;
      str2 = str.substr(str.find(" "), std::string::npos);
      int i = std::atoi(str.c_str());
      switch (i)
      	{
	case 1:
	  _network->sendToServer(new NewGamePacket(ADD_GAME, str2));
	  _network->receiveFromServer();
	  break;
	case 2:
	  _network->sendToServer(new NickPacket(AUTH_TCP, "lalla"));
	  _network->receiveFromServer();
	  break;
	// case 2:
	//   _network->sendToServer()
      	}
      // std::cout << "SERVER : " << _network->getPacket() << std::endl;
    }
}
