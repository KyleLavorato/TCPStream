#define BIGENDIAN (0x0)
#define LITTLEENDIAN (0x1)
#include "HTTP_Generated.h"
#include "pglobals.h"
#include "putilities.h"
void freePDU_HTTP (PDU_HTTP *mainpdu);
bool parseHTTP (PDU_HTTP *pdu_http, PDUP *thePDU, char *progname, uint8_t endianness);
bool parsePacket (Packet_HTTP *packet_http, PDUP *thePDU, char *progname, uint8_t endianness);

bool parseHTTP (PDU_HTTP *pdu_http, PDUP *thePDU, char *progname, uint8_t endianness) {
    unsigned long pos = thePDU->curPos;
    unsigned long remaining = thePDU->remaining;
    if (parsePacket (&pdu_http->ptr.packet_http, thePDU, progname, endianness)) {
        pdu_http->type = Packet_HTTP_VAL;
        return true;
    }
    return false;
}

bool parsePacket (Packet_HTTP *packet_http, PDUP *thePDU, char *progname, uint8_t endianness) {
    if (!lengthRemaining (thePDU, 0, progname)) {
        return false;
    }
    return true;
}

void freePDU_HTTP (PDU_HTTP *mainpdu) {
}

