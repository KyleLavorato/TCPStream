#ifndef PSR_H
#define PSR_H
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>
#include "packet.h"
#include "globals.h"
typedef struct {
    uint32_t radar$id;
    uint32_t target$id;
    double azimuth;
    double distance;
    double radial$speed;
    double ground$speed;
    uint32_t timestamp;
    double radar$latitude;
    double radar$longitude;
} PSRPositionType_PSR;
bool parsePSR (PDU_PSR * pdu_psr, PDU * thePDU, char * name, uint8_t endianness);
void freePDU_PSR (PDU_PSR * mainpdu);
#endif
