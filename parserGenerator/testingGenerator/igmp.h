/**
 * File:	igmp.h
 *
 * Purpose:	Concrete data structures for IGMP.
 *
 * Revision History:
 *
 * 1.0	- Ali ElShakankiry - June 2016
 *	- Initial Version
 * 
 */
#ifndef IGMP_H
#define IGMP_H

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <vector>
#include "assert.h"

#include <netinet/ip.h>
#include "packet.h"

bool parseIGMPPacket(PDU * thePDU, struct HeaderInfo * header, char * name);
enum IGMPType { QUERY, V2REPORT, V2LEAVE, V3REPORT };

struct SourceAddress {
	uint32_t srcAddr;
	void walk() {
		printf("\t\tsrcAddr: 0x%X", srcAddr);
	}
};

struct v3Addition {
	uint8_t	resvSQRV;
	uint8_t QQIC;
	uint16_t numSources;
	SourceAddress *srcAddrs; //number of srcAddrs specified in numSources

	void walk() {
		printf("\tV3Addition\n");
		printf("\tresvSQRV: 0x%X\n", resvSQRV);
		printf("\tQQIC: 0x%X\n", QQIC);
		printf("\tnumSources: 0x%X\n", numSources);
		for(int i = 0; i < numSources; ++i) {
			printf("\tSource Address # %d\n", i+1);
			srcAddrs[i].walk();
		}
	}
};

struct groupRecord {
	uint8_t recordType;
	uint8_t auxDataLen;
	uint16_t numSources;
	uint32_t groupAddr;
	SourceAddress *srcAddrs; //number of srcAddrs specified in numSources

	void GetAllSourceAddress(std::vector<uint32_t> &rsrcAddress)
	{
		for (int i = 0; i < numSources; i ++)
		{
			rsrcAddress.push_back(srcAddrs[i].srcAddr);
		}
	}

	void walk() {
		printf("\trecordType: 0x%X\n", recordType);
		printf("\tauxDataLen: 0x%X\n", auxDataLen);
		printf("\tnumSources: 0x%X\n", recordType);
		printf("\tgroupAddr: 0x%X\n", groupAddr);
		for(int i = 0; i < numSources; ++i) {
			printf("\tSource Address # %d\n", i+1);
			srcAddrs[i].walk();
		}
	}
};

struct Query {
	IGMPType parseType;
	uint8_t type;// = IGMP_MEMBERSHIP_QUERY; //17 or 0x11
	uint8_t maxRespTime;
	uint16_t checksum;
	uint32_t groupAddr;
	v3Addition *v3Add;

	void walk() {
		printf("Query\n");
		printf("type: 0x%X\n", type);
		printf("maxRespTime: 0x%X\n", maxRespTime);
		printf("checksum: 0x%X\n", checksum);
		printf("groupAddr: 0x%X\n", groupAddr);
		if(v3Add != NULL ) {
			v3Add->walk();
		}
	}
};

struct V2Report {
	IGMPType parseType;
	uint8_t type;// = IGMP_V2_MEMBERSHIP_REPORT; //22 or 0x16
	uint8_t maxRespTime;
	uint16_t checksum;
	uint32_t groupAddr;
	void walk() {
		printf("V2Report\n");
		printf("type: 0x%X\n", type);
		printf("maxRespTime: 0x%X\n", maxRespTime);
		printf("checksum: 0x%X\n", checksum);
		printf("groupAddr: 0x%X\n", groupAddr);
	}
};

struct V2Leave {
	IGMPType parseType;
	uint8_t type;// = IGMP_V2_LEAVE_GROUP; //23 or 0x17
	uint8_t maxRespTime;
	uint16_t checksum;
	uint32_t groupAddr;
	void walk() {
		printf("V2Leave\n");
		printf("type: 0x%X\n", type);
		printf("maxRespTime: 0x%X\n", maxRespTime);
		printf("checksum: 0x%X\n", checksum);
		printf("groupAddr: 0x%X\n", groupAddr);
	}
};

struct V3Report {
	IGMPType parseType;
	uint8_t type; //34 or 0x22
	uint8_t reserved; 
	uint16_t checksum;
	uint16_t secondReserved;
	uint16_t numGrps;
	groupRecord *groupRecordInfo; //size of groupRecordInfo is (PDULENGTH - (SIZEOF(type) + SIZEOF(reserved) + SIZEOF(checksum) + SIZEOF(secondReserved) + SIZEOF(numGrps))))
	
	void GetAllSourceAddress(std::vector<uint32_t> &rSourceAddrs)
	{
		for (int i = 0; i < numGrps; i++)
		{
			std::vector<uint32_t> rSrcAddrs;
			groupRecordInfo[i].GetAllSourceAddress(rSrcAddrs);
			rSourceAddrs.insert(rSourceAddrs.end(), rSrcAddrs.begin(), rSrcAddrs.end());
		}
	}

	void GetAllGroupAddress(std::vector<uint32_t> &rGroupAddrs)
	{
		for (int i = 0; i < numGrps; i++)
		{
			rGroupAddrs.push_back(groupRecordInfo[i].groupAddr);
		}
	}

	bool IntendToLeave(int iIndex)
	{
		assert(iIndex < numGrps);
		return (groupRecordInfo[iIndex].recordType == 3);
	}

	void walk() {
		printf("V3Report\n");
		printf("type: 0x%X\n", type);
		printf("reserved: 0x%X\n", reserved);
		printf("checksum: 0x%X\n", checksum);
		printf("secondReserved: 0x%X\n", secondReserved);
		printf("numGrps: 0x%X\n", numGrps);
		for(int i = 0; i < numGrps; ++i) {
			printf("Group Record # %d\n", i+1);
			groupRecordInfo[i].walk();
		}
	}
};

#endif /* IGMP_H */