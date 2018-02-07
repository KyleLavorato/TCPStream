#define BIGENDIAN (0x0)
#define LITTLEENDIAN (0x1)
#include "HTTPS_Generated.h"
#include "pglobals.h"
#include "putilities.h"
void freePDU_HTTPS (PDU_HTTPS *mainpdu);
bool parseHTTPS (PDU_HTTPS *pdu_https, PDUP *thePDU, char *progname, uint8_t endianness);
bool parsePacket (Packet_HTTPS *packet_https, PDUP *thePDU, char *progname, uint8_t endianness);

bool parseHTTPS (PDU_HTTPS *pdu_https, PDUP *thePDU, char *progname, uint8_t endianness) {
    unsigned long pos = thePDU->curPos;
    unsigned long remaining = thePDU->remaining;
    if (parsePacket (&pdu_https->ptr.packet_https, thePDU, progname, endianness)) {
        pdu_https->type = Packet_HTTPS_VAL;
        return true;
    }
    return false;
}

bool parsePacket (Packet_HTTPS *packet_https, PDUP *thePDU, char *progname, uint8_t endianness) {
    if (!lengthRemaining (thePDU, 0, progname)) {
        return false;
    }
    return true;
}

void freePDU_HTTPS (PDU_HTTPS *mainpdu) {
}

