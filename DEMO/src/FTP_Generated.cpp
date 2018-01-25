#define BIGENDIAN (0x0)
#define LITTLEENDIAN (0x1)
#include "FTP_Generated.h"
#include "pglobals.h"
#include "putilities.h"
void freePDU_FTP (PDU_FTP *mainpdu);
bool parseFTP (PDU_FTP *pdu_ftp, PDUP *thePDU, char *progname, uint8_t endianness);
bool parsePacket (Packet_FTP *packet_ftp, PDUP *thePDU, char *progname, uint8_t endianness);

bool parseFTP (PDU_FTP *pdu_ftp, PDUP *thePDU, char *progname, uint8_t endianness) {
    unsigned long pos = thePDU->curPos;
    unsigned long remaining = thePDU->remaining;
    if (parsePacket (&pdu_ftp->ptr.packet_ftp, thePDU, progname, endianness)) {
        pdu_ftp->type = Packet_FTP_VAL;
        return true;
    }
    return false;
}

bool parsePacket (Packet_FTP *packet_ftp, PDUP *thePDU, char *progname, uint8_t endianness) {
    if (!lengthRemaining (thePDU, 0, progname)) {
        return false;
    }
    return true;
}

void freePDU_FTP (PDU_FTP *mainpdu) {
}

