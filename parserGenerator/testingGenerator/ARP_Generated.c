#define BIGENDIAN (0x0)
#define LITTLEENDIAN (0x1)
#include "ARP_Generated.h"
#include "pglobals.h"
#include "putilities.h"
void freePDU_ARP (PDU_ARP *mainpdu);
bool parseARP (PDU_ARP *pdu_arp, PDU *thePDU, char *progname, uint8_t endianness);

bool parseARP (PDU_ARP *pdu_arp, PDU *thePDU, char *progname, uint8_t endianness) {
    if (!lengthRemaining (thePDU, 28, progname)) {
        return false;
    }
    pdu_arp->hwtype = get16_e (thePDU, endianness);
    pdu_arp->protocoltype = get16_e (thePDU, endianness);
    pdu_arp->hwsize = get8_e (thePDU, endianness);
    pdu_arp->protocolsize = get8_e (thePDU, endianness);
    pdu_arp->opcode = get16_e (thePDU, endianness);
    pdu_arp->sendermac = get48_e (thePDU, endianness);
    pdu_arp->senderip = get32_e (thePDU, endianness);
    pdu_arp->targetmac = get48_e (thePDU, endianness);
    pdu_arp->targetip = get32_e (thePDU, endianness);
    return true;
}

void freePDU_ARP (PDU_ARP *mainpdu) {
}

