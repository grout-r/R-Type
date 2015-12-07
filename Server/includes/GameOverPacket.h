# include "IServerPacket.h"

class GameOverPacket : public IServerPacket
{
 public:
  GameOverPacket(ServerResponse, GameOverData const&);
  ~GameOverPacket();

  std::string const&		deserialize();

 private:
  ServerResponse		_response;
  GameOverData*			_data;
};