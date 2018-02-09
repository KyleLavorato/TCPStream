#define BIGENDIAN (0x0)
#define LITTLEENDIAN (0x1)
#include "packet.h"
#include "putilities.h"
#include <string>
#include "HTTP_Generated.h"
#include "SMB2_Generated.h"
#include "FTP_Generated.h"
#include "HTTPS_Generated.h"
#define HTTP_TYPE (1)
#define SMB2_TYPE (2)
#define FTP_TYPE (3)
#define HTTPS_TYPE (4)
int parseData (const unsigned char * data, const unsigned long dataLength, int type);
void printStats ();
int getConstantForProtocol (const std::string& protocol);
