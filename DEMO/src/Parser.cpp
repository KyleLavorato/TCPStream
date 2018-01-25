#define BIGENDIAN (0x0)
#define LITTLEENDIAN (0x1)
#include "packet.h"
#include "putilities.h"
#include "HTTP_Generated.h"
#include "SMB2_Generated.h"
#include "FTP_Generated.h"
#define HTTP_TYPE (1)
#define SMB2_TYPE (2)
#define FTP_TYPE (3)

int parseData (const unsigned char *data, const unsigned long dataLength, int type) {
    char *progname = argString;
    bool parsedPDU;
    PDUP *thePDU;
    thePDU = (PDUP *) malloc (sizeof (PDUP));
    thePDU->len = dataLength;
    thePDU->watermark = dataLength;
    thePDU->curPos = 0;
    thePDU->data = (unsigned char *) data;
    thePDU->curPos = 0;
    thePDU->curBitPos = 0;
    thePDU->remaining = thePDU->len;
    thePDU->header = NULL;
    uint8_t endianness;
    switch (type) {
    case HTTP_TYPE :
        {
            PDU_HTTP pdu_http;
            endianness = BIGENDIAN;
            parsedPDU = parseHTTP (&pdu_http, thePDU, progname, endianness);
            freePDU_HTTP (&pdu_http);
            break;
        }
    case SMB2_TYPE :
        {
            PDU_SMB2 pdu_smb2;
            endianness = LITTLEENDIAN;
            uint32_t SKIPBITS = get32_e (thePDU, endianness);
            parsedPDU = parseSMB2 (&pdu_smb2, thePDU, progname, endianness);
            freePDU_SMB2 (&pdu_smb2);
            break;
        }
    case FTP_TYPE :
        {
            PDU_FTP pdu_ftp;
            endianness = BIGENDIAN;
            parsedPDU = parseFTP (&pdu_ftp, thePDU, progname, endianness);
            freePDU_FTP (&pdu_ftp);
            break;
        }
    default :
        {
            free (thePDU);
            thePDU = NULL;
            return 0;
        }
    }
    free (thePDU);
    thePDU = NULL;
    return parsedPDU;
}

