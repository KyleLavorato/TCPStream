#include "packet.h"
#include "globals.h"

#define BIGENDIAN (0x0)
#define LITTLEENDIAN (0x1)

#define SMB2_TYPE (1)
#define HTTP_TYPE (2)

int parseData(const unsigned char *data, const unsigned long dataLength, int type);
