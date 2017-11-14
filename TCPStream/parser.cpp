#include <iostream>
#include "packet.h" 
#include "SMB2_Generated.h"

#define BIGENDIAN (0x0)

void parseData(char *progname, unsigned char *data, unsigned long dataLength) {
	bool parsedPDU;
	PDUP * thePDU;
	thePDU = (PDUP*)malloc(sizeof(PDUP));
	// if (thePDU == NULL){
	// 	fprintf(stderr,"%s: internal malloc error file: %s line: %d\n",progname, __FILE__ , __LINE__);
	// 	exit(1);
	// }
	thePDU->len = dataLength; // Put the length of the data here
	thePDU->watermark= dataLength;
	thePDU->curPos = 0;
	thePDU->data = data; // Put the data passed in here

	thePDU ->curPos = 0;
	thePDU ->curBitPos = 0;
	thePDU ->remaining = thePDU ->len;
	thePDU->header = NULL;
	uint8_t endianness = BIGENDIAN;
	PDU_SMB2 pdu_smb2;

	parsedPDU = parseSMB2(&pdu_smb2, thePDU, progname, endianness);
	if (parsedPDU == true){
		//fprintf(stderr,"Parsed packet %d\n",count);
		if (traceFile) fprintf(traceFile,"\n");
	} else { 
		//fprintf(stderr, "Couldn't Parse packet # %d\n", count+1);
		if (traceFile) fprintf(traceFile,"\t\t\tFAILED\n");
		++failed;
	}
	freePDU_SMB2(&pdu_smb2);
	free(thePDU);
	thePDU = NULL;
}