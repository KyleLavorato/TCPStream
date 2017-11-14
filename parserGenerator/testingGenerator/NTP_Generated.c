#define BIGENDIAN (0x0)
#define LITTLEENDIAN (0x1)
#include "NTP_Generated.h"
#include "pglobals.h"
#include "putilities.h"
void freePDU_NTP (PDU_NTP *mainpdu);
bool parseNTP (PDU_NTP *pdu_ntp, PDU *thePDU, char *progname, uint8_t endianness);

bool parseNTP (PDU_NTP *pdu_ntp, PDU *thePDU, char *progname, uint8_t endianness) {
    if (!lengthRemaining (thePDU, 48, progname)) {
        return false;
    }
    pdu_ntp->flags = get8_e (thePDU, endianness);
    if (!((pdu_ntp->flags& 56) == 32)) {
        return false;
    }
    pdu_ntp->peerstratum = get8_e (thePDU, endianness);
    pdu_ntp->peerinterval = get8_e (thePDU, endianness);
    pdu_ntp->peerprecision = get8_e (thePDU, endianness);
    pdu_ntp->rootdelay = get32_e (thePDU, endianness);
    pdu_ntp->rootdispersion = get32_e (thePDU, endianness);
    pdu_ntp->referenceid = get32_e (thePDU, endianness);
    pdu_ntp->referencets = get64_e (thePDU, endianness);
    pdu_ntp->origints = get64_e (thePDU, endianness);
    pdu_ntp->recievets = get64_e (thePDU, endianness);
    pdu_ntp->transmitts = get64_e (thePDU, endianness);
    return true;
}

void freePDU_NTP (PDU_NTP *mainpdu) {
}

