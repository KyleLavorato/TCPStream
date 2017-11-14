#ifndef UDP_H
#define UDP_H
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>
#include "packet.h"
#include "globals.h"
#include "RTPS_Generated.h"
#include "NTP_Generated.h"
#define PDU_RTPS_VAL (1)
#define PDU_NTP_VAL (2)
typedef struct {
    uint32_t type;
    union {
        PDU_RTPS pdu_rtps;
        PDU_NTP pdu_ntp;
    } ptr;
} PDU_UDP;
bool parseUDP (PDU_UDP * pdu_udp, PDU * thePDU, char * name, uint8_t endianness);
void freePDU_UDP (PDU_UDP * mainpdu);
#endif
