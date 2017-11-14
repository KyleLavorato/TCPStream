#ifndef ARP_H
#define ARP_H
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>
#include "packet.h"
#include "globals.h"
typedef struct {
    uint16_t hwtype;
    uint16_t protocoltype;
    uint8_t hwsize;
    uint8_t protocolsize;
    uint16_t opcode;
    uint64_t sendermac;
    uint32_t senderip;
    uint64_t targetmac;
    uint32_t targetip;
} PDU_ARP;
bool parseARP (PDU_ARP * pdu_arp, PDU * thePDU, char * name, uint8_t endianness);
void freePDU_ARP (PDU_ARP * mainpdu);
#endif
