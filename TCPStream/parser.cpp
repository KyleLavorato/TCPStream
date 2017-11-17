#include <iostream>
#include "packet.h" 
#include "SMB2_Generated.h"
#include "putilities.h"

#define BIGENDIAN (0x0)
#define LITTLEENDIAN (0x1)

void parseData(char *progname, const unsigned char *data, const unsigned long dataLength) {
	//std::cout << "PARSE START" << std::endl << std::endl;
	bool parsedPDU;
	PDUP * thePDU;
	thePDU = (PDUP*)malloc(sizeof(PDUP));
	// if (thePDU == NULL){
	// 	fprintf(stderr,"%s: internal malloc error file: %s line: %d\n",progname, __FILE__ , __LINE__);
	// 	exit(1);
	// }
	//std::cout << dataLength << std::endl;
	//std::cout << std::hex << data <<std::endl;
	thePDU->len = dataLength; // Put the length of the data here
	thePDU->watermark= dataLength;
	thePDU->curPos = 0;
	thePDU->data = (unsigned char *)data; // Put the data passed in here

	thePDU ->curPos = 0;
	thePDU ->curBitPos = 0;
	thePDU ->remaining = thePDU ->len;
	thePDU->header = NULL;
	uint8_t endianness = LITTLEENDIAN;
	PDU_SMB2 pdu_smb2;

	uint32_t NETBIOS = get32_e (thePDU, endianness);

	parsedPDU = parseSMB2(&pdu_smb2, thePDU, progname, endianness);
	if (parsedPDU == true){
		std::cout << "Parsed SMB" << std::endl;
	} else { 
		std::cout << "FAILED PARSE" << std::endl;
	}
	freePDU_SMB2(&pdu_smb2);
	free(thePDU);
	thePDU = NULL;
}