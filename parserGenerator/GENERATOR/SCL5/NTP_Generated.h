#ifndef NTP_H
#define NTP_H
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>
#include "packet.h"
#include "globals.h"
typedef struct {
    uint8_t flags;
    uint8_t peerstratum;
    uint8_t peerinterval;
    uint8_t peerprecision;
    uint32_t rootdelay;
    uint32_t rootdispersion;
    uint32_t referenceid;
    uint64_t referencets;
    uint64_t origints;
    uint64_t recievets;
    uint64_t transmitts;
} PDU_NTP;
bool parseNTP (PDU_NTP * pdu_ntp, PDU * thePDU, char * name, uint8_t endianness);
void freePDU_NTP (PDU_NTP * mainpdu);
#endif
