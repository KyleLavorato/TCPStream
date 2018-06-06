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
long iTotal = 0;
long iFail = 0;
long iHTTP = 0;
long iHTTPf = 0;
long iSMB2 = 0;
long iSMB2f = 0;
long iFTP = 0;
long iFTPf = 0;
long iHTTPS = 0;
long iHTTPSf = 0;

int parseData (const unsigned char *data, const unsigned long dataLength, int type) {
    char *progname = argString;
    iTotal++;
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
            if (parsedPDU)
                iHTTP++;
            else
                iHTTPf++;
            freePDU_HTTP (&pdu_http);
            break;
        }
    case SMB2_TYPE :
        {
            PDU_SMB2 pdu_smb2;
            endianness = LITTLEENDIAN;
            uint32_t SKIPBITS = get32_e (thePDU, endianness);
            parsedPDU = parseSMB2 (&pdu_smb2, thePDU, progname, endianness);
            if (parsedPDU)
                iSMB2++;
            else
                iSMB2f++;
            freePDU_SMB2 (&pdu_smb2);
            break;
        }
    case FTP_TYPE :
        {
            PDU_FTP pdu_ftp;
            endianness = BIGENDIAN;
            parsedPDU = parseFTP (&pdu_ftp, thePDU, progname, endianness);
            if (parsedPDU)
                iFTP++;
            else
                iFTPf++;
            freePDU_FTP (&pdu_ftp);
            break;
        }
    case HTTPS_TYPE :
        {
            PDU_HTTPS pdu_https;
            endianness = BIGENDIAN;
            parsedPDU = parseHTTPS (&pdu_https, thePDU, progname, endianness);
            if (parsedPDU)
                iHTTPS++;
            else
                iHTTPSf++;
            freePDU_HTTPS (&pdu_https);
            break;
        }
    default :
        {
            iFail++;
            free (thePDU);
            thePDU = NULL;
            return 0;
        }
    }
    free (thePDU);
    thePDU = NULL;
    return parsedPDU;
}

int getConstantForProtocol (const std::string& protocol) {
    if (!protocol.compare ("HTTP"))
        return 0;
    if (!protocol.compare ("SMB2"))
        return 1;
    if (!protocol.compare ("FTP"))
        return 2;
    if (!protocol.compare ("HTTPS"))
        return 3;
    return -1;
}

void printStats () {
    printf ("HTTP Parsed: %lu \n", iHTTP);
    printf ("HTTP Failed: %lu \n", iHTTPf);
    printf ("SMB2 Parsed: %lu \n", iSMB2);
    printf ("SMB2 Failed: %lu \n", iSMB2f);
    printf ("FTP Parsed: %lu \n", iFTP);
    printf ("FTP Failed: %lu \n", iFTPf);
    printf ("HTTPS Parsed: %lu \n", iHTTPS);
    printf ("HTTPS Failed: %lu \n", iHTTPSf);
    printf ("Total Packets: %lu \n", iTotal);
    printf ("Unparsable Packets: %lu \n", iFail);
}

