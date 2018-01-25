#ifndef FTP_H
#define FTP_H
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>
#include "packet.h"
#include "globals.h"
#define Packet_FTP_VAL (1)
typedef struct {
} Packet_FTP;
typedef struct {
    uint32_t type;
    union {
        Packet_FTP packet_ftp;
    } ptr;
} PDU_FTP;
bool parseFTP (PDU_FTP * pdu_ftp, PDUP * thePDU, char * name, uint8_t endianness);
void freePDU_FTP (PDU_FTP * mainpdu);
#endif
