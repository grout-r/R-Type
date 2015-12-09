#ifndef ISERVERPACKET_H_
# define ISERVERPACKET_H_

# include "NetworkDefines.h"

typedef struct
{
  uint32_t			magic;
  ServerTCPResponse		command;
  uint32_t			size;
} __attribute__ ((packed))	ServerTCPHeader;

typedef struct
{
  uint32_t			magic;
  ServerUDPResponse		command;
  uint32_t			size;
  uint32_t			idx;
} __attribute__ ((packed))	ServerUDPHeader;

typedef struct
{
  uint32_t			data;
  uint32_t			magic;
} __attribute__ ((packed))	integerData;

typedef struct
{
  uint32_t			id;
  uint32_t			port;
  uint32_t			magic;
} __attribute__ ((packed))	GameInfoData;

typedef struct
{
  uint32_t			id;
  char				gameName[256];
  char				players[256];
  uint32_t			magic;
} __attribute__ ((packed))	DesGameData;

typedef struct
{
  uint32_t			success;
  char				name[256];
  uint32_t			magic;
}				AuthUDPData;

typedef struct
{
  float				x;
  float				y;
  uint32_t			magic;
}				CrePlayData;

typedef integerData GameOverData;
typedef integerData AuthTCPData;
typedef integerData GameListData;


template <typename T>
class IServerPacket
{
public:
  virtual ~IServerPacket() {};

public:
  virtual std::string const&	deserialize() = 0;
  virtual T			getCommandType() const = 0;
};

#endif
