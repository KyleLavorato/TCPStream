#ifndef HTTPS_H
#define HTTPS_H
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>
#include "packet.h"
#include "globals.h"
#define Packet_HTTPS_VAL (1)
typedef struct {
} Packet_HTTPS;
typedef struct {
    uint32_t type;
    union {
        Packet_HTTPS packet_https;
    } ptr;
} PDU_HTTPS;
bool parseHTTPS (PDU_HTTPS * pdu_https, PDUP * thePDU, char * name, uint8_t endianness);
void freePDU_HTTPS (PDU_HTTPS * mainpdu);
#endif
