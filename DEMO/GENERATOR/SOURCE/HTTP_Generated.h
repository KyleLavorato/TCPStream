#ifndef HTTP_H
#define HTTP_H
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>
#include "packet.h"
#include "globals.h"
#define Packet_HTTP_VAL (1)
typedef struct {
} Packet_HTTP;
typedef struct {
    uint32_t type;
    union {
        Packet_HTTP packet_http;
    } ptr;
} PDU_HTTP;
bool parseHTTP (PDU_HTTP * pdu_http, PDUP * thePDU, char * name, uint8_t endianness);
void freePDU_HTTP (PDU_HTTP * mainpdu);
#endif
