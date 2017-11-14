#define BIGENDIAN (0x0)
#define LITTLEENDIAN (0x1)
#include "UDP_Generated.h"
#include "pglobals.h"
#include "putilities.h"
void freePDU_UDP (PDU_UDP *mainpdu);
bool parseUDP (PDU_UDP *pdu_udp, PDU *thePDU, char *progname, uint8_t endianness);

bool parseUDP (PDU_UDP *pdu_udp, PDU *thePDU, char *progname, uint8_t endianness) {
    unsigned long pos = thePDU->curPos;
    unsigned long remaining = thePDU->remaining;
    if (parseRTPS (&pdu_udp->ptr.pdu_rtps, thePDU, progname, endianness)) {
        pdu_udp->type = PDU_RTPS_VAL;
        return true;
    }
    thePDU->curPos = pos;
    thePDU->remaining = remaining;
    if (parseNTP (&pdu_udp->ptr.pdu_ntp, thePDU, progname, endianness)) {
        pdu_udp->type = PDU_NTP_VAL;
        return true;
    }
    return false;
}

void freePDU_UDP (PDU_UDP *mainpdu) {
    if (mainpdu->type == PDU_RTPS_VAL)
        freePDU_RTPS (&mainpdu->ptr.pdu_rtps);
    else if (mainpdu->type == PDU_NTP_VAL)
        freePDU_NTP (&mainpdu->ptr.pdu_ntp);
}

