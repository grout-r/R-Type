#ifndef CREPLAYPACKET_H_
# define CREPLAYPACKET_H_

# include "AServerPacket.hh"

class CrePlayPacket : public AServerPacket<ServerUDPResponse>
{
 public:
  CrePlayPacket(ServerUDPResponse, int, float, float);
  CrePlayPacket(ServerUDPHeader*);
  ~CrePlayPacket();

  std::string const&		deserialize();
  bool				checkHeader();
  void				setRawData(char *);
  CrePlayData*			getData() const;

 private:
  CrePlayData*			_data;
  ServerUDPHeader*		_header;
};


#endif /* !CREPLAYPACKET_H_ */
