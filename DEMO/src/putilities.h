#ifndef PUTILITIES_H
#define PUTILITIES_H

#include "globals.h"
#include "pglobals.h"

bool lengthRemaining(PDUP * thePDU, unsigned long length, char * name);
bool checkSlack(PDUP * thePDU, unsigned long len);
uint8_t get8_e(PDUP * thePDU, uint8_t endianness);
uint16_t get16_e(PDUP * thePDU, uint8_t endianness);
uint32_t get24_e(PDUP * thePDU, uint8_t endianness);
uint32_t get32_e(PDUP * thePDU, uint8_t endianness);
uint64_t get48_e(PDUP * thePDU, uint8_t endianness);
uint64_t get64_e(PDUP * thePDU, uint8_t endianness);
float getReal4_e(PDUP * thePDU, uint8_t endianness);
double getReal8_e(PDUP * thePDU, uint8_t endianness);
uint8_t get8(PDUP * thePDU);
uint16_t get16(PDUP * thePDU);
uint32_t get24(PDUP * thePDU);
uint32_t get32(PDUP * thePDU);
uint64_t get64(PDUP * thePDU);
float getReal4(PDUP * thePDU);
double getReal8(PDUP * thePDU);
#endif /* PUTILITIES_H */