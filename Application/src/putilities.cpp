#include "putilities.h"

bool lengthRemaining(PDUP * thePDU, unsigned long length, char * name) {
	if(thePDU->remaining >= length) {
		thePDU->remaining -= length;
		return true;
	} else {
		//fprintf(stderr,"%s: PDU Length Error file: %s line: %d\n",name, __FILE__ , __LINE__);
		return false;
	}   
}

bool checkSlack(PDUP * thePDU, unsigned long len) {
	while(len > 0) {
		if(thePDU->data[thePDU->curPos++] != '\0')
			return false;
		len--;
	};
	return true;
}

uint8_t get8_e(PDUP * thePDU, uint8_t endianness) {
	return thePDU->data[thePDU->curPos++];
}

uint16_t get16_e(PDUP * thePDU, uint8_t endianness) {
	uint16_t result;
	if((endianness & 0x1) == LITTLEENDIAN) { //Little Endian
		result = thePDU->data[thePDU->curPos] | thePDU->data[thePDU->curPos] << 8;
		thePDU->curPos += 2;
	}
	else { //Big Endian
		result = thePDU->data[thePDU->curPos] << 8 | thePDU->data[thePDU->curPos];
		thePDU->curPos += 2;
	}
	return result;
}

uint32_t get24_e(PDUP * thePDU, uint8_t endianness) {
	uint32_t result = 0;
	if((endianness & 0x1) == LITTLEENDIAN) { //Little Endian
		result = thePDU->data[thePDU->curPos] |
					thePDU->data[thePDU->curPos] << 8 |
					thePDU->data[thePDU->curPos] << 16;
		thePDU->curPos += 3;
	}
	else {//Big Endian
		result = thePDU->data[thePDU->curPos] << 16 |
					thePDU->data[thePDU->curPos] << 8 | 
					  thePDU->data[thePDU->curPos];
		thePDU->curPos += 3;
	}
	return result;
}

uint32_t get32_e(PDUP * thePDU, uint8_t endianness) {
	uint32_t result;
	if((endianness & 0x1) == LITTLEENDIAN) { //Little Endian
		result = thePDU->data[thePDU->curPos] |
					thePDU->data[thePDU->curPos] << 8 |
					thePDU->data[thePDU->curPos] << 16 |
					thePDU->data[thePDU->curPos] << 24;
		thePDU->curPos += 4;
	}
	else { //Big Endian
		result = thePDU->data[thePDU->curPos] << 24 | 
					thePDU->data[thePDU->curPos] << 16 | 
					thePDU->data[thePDU->curPos] << 8 | 
					thePDU->data[thePDU->curPos];
		thePDU->curPos += 4;
	}
	return result;
}

uint64_t get48_e(PDUP * thePDU, uint8_t endianness) {
	uint64_t result;
	//NOTE: ASSUMING ONLY BIGENDIAN (USED FOR ARP)
	result = (uint64_t)0x0000 << 46 |
					(uint64_t)thePDU->data[thePDU->curPos] << 40 | 
					(uint64_t)thePDU->data[thePDU->curPos] << 32 | 
					thePDU->data[thePDU->curPos] << 24 | 
					thePDU->data[thePDU->curPos] << 16 | 
					thePDU->data[thePDU->curPos] << 8 | 
					thePDU->data[thePDU->curPos];
	thePDU->curPos += 6;		
	return result;
}

uint64_t get64_e(PDUP * thePDU, uint8_t endianness) {
	uint64_t result;
	if((endianness & 0x1) == LITTLEENDIAN) 
		result = (uint64_t)get32_e(thePDU, endianness) | (uint64_t)get32_e(thePDU, endianness) << 32;
	else
		result = (uint64_t)get32_e(thePDU, endianness) << 32 | (uint64_t)get32_e(thePDU, endianness);

	return result;
}

float getReal4_e(PDUP * thePDU, uint8_t endianness) {
	uint32_t i = get32_e(thePDU, endianness);
 	return *((float *)&i);
}

double getReal8_e(PDUP * thePDU, uint8_t endianness) {
	uint64_t i = get64_e(thePDU, endianness);
 	return *((double *)&i);
}

uint8_t get8(PDUP * thePDU) {
	return thePDU->data[thePDU->curPos++];;
}

uint16_t get16(PDUP * thePDU) {
	return get16_e(thePDU, BIGENDIAN);
}

uint32_t get24(PDUP * thePDU) {
	return get24_e(thePDU, BIGENDIAN);
}

uint32_t get32(PDUP * thePDU) {
	return get32_e(thePDU, BIGENDIAN);
}

uint64_t get64(PDUP * thePDU) {
	return get64_e(thePDU, BIGENDIAN);
}

float getReal4(PDUP * thePDU) {
	uint32_t i = get32_e(thePDU, BIGENDIAN);
	return *((float *)&i);
}

double getReal8(PDUP * thePDU) {
	uint64_t i = get64_e(thePDU, BIGENDIAN);
	return *((double *)&i);
}