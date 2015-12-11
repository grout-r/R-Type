#ifndef JOIN_PACKET_
# define JOIN_PACKET_

# include "AClientPacket.hh"

class JoinPacket : public AClientPacket<ClientTCPCommand>
{
public:
  JoinPacket(ClientTCPCommand command, int id);
  JoinPacket(ClientTCPHeader*);
  ~JoinPacket();

private:
  ClientTCPHeader*	_header;
  JoinData*		_data;

public:
  void			setRawData(std::string const&);
  JoinData*		getData() const;
  bool			checkHeader();
  std::string const&	deserialize();
};

#endif