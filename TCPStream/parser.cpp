#include <iostream>
#include "packet.h" 
#include "SMB2_Generated.h"
#include "putilities.h"
using namespace std;

#define BIGENDIAN (0x0)
#define LITTLEENDIAN (0x1)

#define SMB2_TYPE (1)
#define HTTP_TYPE (2)

int parseData(char *progname, const unsigned char *data, const unsigned long dataLength, int type) {
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
	uint8_t endianness;

	uint32_t NETBIOS = get32_e (thePDU, endianness); // Skip the NETBIOS 4 byte layer

	indent = 0;

	switch (type) {
		case 1:
			PDU_SMB2 pdu_smb2;
			endianness = LITTLEENDIAN; // SMB2 is Little Endian
			parsedPDU = parseSMB2(&pdu_smb2, thePDU, progname, endianness);
			if (parsedPDU == true){
				cout << endl << "#### Parsed SMB ####" << endl;
			} else { 
				cout << endl << "#### FAILED PARSE ####" << endl;
			}
			freePDU_SMB2(&pdu_smb2);
			break;
		case 2:
			// Add parseHTTP()
			break;
		default:
			free(thePDU);
			thePDU = NULL;
			return 0;
	}
	free(thePDU);
	thePDU = NULL;
	return 1;
}