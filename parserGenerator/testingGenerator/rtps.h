/**
 *File:	rtps.hdata
 *
 *Purpose:	Concrete data structures for DDS.
 *
 *Revision History:
 *
 *1.0	- Ali ElShakankiry - June 16 2016
 *	- Initial Version
 * 
 */
#ifndef RTPS_H
#define RTPS_H

#define PIDTOPICNAME_KIND 			(0x05)
#define PICTYPENAME_KIND 			(0x07)
#define PIDRELIABILITY_KIND 		(0x1A)
#define PIDENDPOINTGUID_KIND 		(0x5A)
#define PIDMULTICASTLOCATOR_KIND 	(0x30)
#define PIDUNICASTLOCATOR_KIND 		(0x2F)
#define PIDSENTINAL_KIND 			(0x01)

#define PIDPROTOVERSION_KIND				(0x15)
#define PIDPARTICIPANTGUID_KIND				(0x50)
#define PIDVENDORID_KIND					(0x16)
#define PIDPARTICIPANTBUILTENDPOINTS_KIND	(0x44)
#define PIDBUILTENDPOINTSET_KIND			(0x58)
#define PIDMETATRAFFICUNILOCATOR_KIND		(0x32)
#define PIDDEFMULTILOCATOR_KIND				(0x48)
#define PIDPARTICIPANTLIVECOUNT_KIND		(0x34)
#define PIDPARTICIPANTLEASE_KIND			(0x02)
#define PIDDEFUNILOCATOR_KIND				(0x31)
#define PIDMETATRAFFICMULTILOCATOR_KIND		(0x33)

#define ACKNACK_VAL		(0x06)
#define HEARTBEAT_VAL	(0x07)
#define GAP_VAL			(0x08)
#define INFO_TS_VAL 	(0x09)	
#define INFO_DST_VAL	(0x0E)
#define DATASUB_VAL 	(0x15)

#define DATAWSUB_VAL 	(0x16)
#define DATARSUB_VAL 	(0x17)
#define DATAPSUB_VAL 	(0x18)

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>
//#include <netinet/ip.h>*/

//#include "common.h"
#include "packet.h"

bool parseRTPSPacket(PDU *thePDU, struct HeaderInfo *header, char *name);
bool parseRTPSPacket(PDU *thePDU, char *name);
//enum PARTICIPANTPARAMSType { PIDPROTOVERSION_VAL, PIDPARTICIPANTGUID_VAL, PIDVENDORID_VAL,  PIDPARTICIPANTBUILTENDPOINTS_VAL, PIDBUILTENDPOINTSET_VAL, PIDMETATRAFFICUNILOCATOR_VAL, PIDDEFMULTILOCATOR_VAL, PIDPARTICIPANTLIVECOUNT_VAL,  PIDPARTICIPANTLEASE_VAL, PIDSENTINAL_VAL,  PIDDEFUNILOCATOR_VAL,  PIDMETATRAFFICMULTILOCATOR_VAL };
//enum TOPICPARMSType { PIDTOPICNAME_VAL, PICTYPENAME_VAL, PIDRELIABILITY_VAL, PIDENDPOINTGUID_VAL, PIDMULTICASTLOCATOR_VAL, PIDUNICASTLOCATOR_VAL, PIDSENTINAL_VAL1 };
//enum SUBMESSAGEType { ACKNACK_VAL, HEARTBEAT_VAL, INFO_TS_VAL, INFO_DST_VAL, DATASUB_VAL, DATAWSUB_VAL, DATARSUB_VAL, DATAPSUB_VAL };


//NOTE: Had to move this to the top because it is used by other structs
struct GUIDPREFIX {
	uint32_t hostID;
	uint32_t appID;
	uint32_t counter;
	void walk(const char * indent) {
		printf("%sGUIDPREFIX\n", indent);
		printf("%s\thostID: 0x%X\n", indent, hostID);
		printf("%s\tappID: 0x%X\n", indent, appID);
		printf("%s\tcounter: 0x%X\n", indent, counter);
	}
};

struct SNSTATE {
	uint64_t bitmapBase;
	uint32_t nmBits;
	uint32_t slack;
	void walk(const char * indent) {
		printf("%s\tbitmapBase: 0x%llX\n", indent, bitmapBase);
		printf("%s\tnmBits: 0x%X\n", indent, nmBits);
		printf("%s\tslack: 0x%X\n", indent, slack);
	}
};

struct ENTITYID {
	uint32_t key; //This is a 3 byte integer
	uint8_t kind;
	void walk(const char * indent) {
		printf("%sENTITYID\n", indent);
		printf("%s\tkey: 0x%X\n", indent, key);
		printf("%s\tkind: 0x%X\n", indent, kind);
	}
};

struct PIDSENTINAL {
	uint16_t parameterKind;
	uint16_t parameterLength;
	void walk(const char * indent) {
		printf("%sPIDSENTINAL\n", indent);
		printf("%s\tparameterKind: 0x%X\n", indent, parameterKind);
		printf("%s\tparameterLength: 0x%X\n", indent, parameterLength);
	}	
};

struct PIDPARTICIPANTLEASE {
	uint16_t parameterKind;
	uint16_t parameterLength;
	uint64_t duration;
	void walk(const char * indent) {
		printf("%sPIDPARTICIPANTLEASE\n", indent);
		printf("%s\tparameterKind: 0x%X\n", indent, parameterKind);
		printf("%s\tparameterLength: 0x%X\n", indent, parameterLength);
		printf("%s\tduration: 0x%" PRIu64 "\n", indent, duration);
	}
};

struct PIDPARTICIPANTLIVECOUNT {
	uint16_t parameterKind;
	uint16_t parameterLength;
	uint32_t manualLiveCount;
	void walk(const char * indent) {
		printf("%sPIDPARTICIPANTLIVECOUNT\n", indent);
		printf("%s\tparameterKind: 0x%X\n", indent, parameterKind);
		printf("%s\tparameterLength: 0x%X\n", indent, parameterLength);
		printf("%s\tmanualLiveCount: 0x%X\n", indent, manualLiveCount);
	}
};

struct LOCATOR {
	uint32_t kind;
	uint32_t port;
	unsigned char address[16];
	void walk(const char * indent) {
		printf("%s\tLOCATOR\n", indent);
		printf("%s\tkind: 0x%X\n", indent, kind);
		printf("%s\tport: 0x%X\n", indent, port);
		printf("%s\taddress: 0x", indent);
		for(int i = 0; i < 16; ++i)
			printf(" %0.2X", address[i]);
		printf("\n");
	}
};

struct PIDDEFMULTILOCATOR {
	uint16_t parameterKind;
	uint16_t parameterLength;
	LOCATOR locator;
	void walk(const char * indent) {
		printf("%sPIDDEFMULTILOCATOR\n", indent);
		printf("%s\tparameterKind: 0x%X\n", indent, parameterKind);
		printf("%s\tparameterLength: 0x%X\n", indent, parameterLength);
		locator.walk(indent);
	}
};

struct PIDDEFUNILOCATOR {
	uint16_t parameterKind;
	uint16_t parameterLength;
	LOCATOR locator;
	void walk(const char * indent) {
		printf("%sPIDDEFUNILOCATOR\n", indent);
		printf("%s\tparameterKind: 0x%X\n", indent, parameterKind);
		printf("%s\tparameterLength: 0x%X\n", indent, parameterLength);
		locator.walk(indent);
	}
};

struct PIDMETATRAFFICMULTILOCATOR {
	uint16_t parameterKind;
	uint16_t parameterLength;
	LOCATOR locator;
	void walk(const char * indent) {
		printf("%sPIDMETATRAFFICMULTILOCATOR\n", indent);
		printf("%s\tparameterKind: 0x%X\n", indent, parameterKind);
		printf("%s\tparameterLength: 0x%X\n", indent, parameterLength);
		locator.walk(indent);
	}
};

struct PIDMETATRAFFICUNILOCATOR {
	uint16_t parameterKind;
	uint16_t parameterLength;
	LOCATOR locator;
	void walk(const char * indent) {
		printf("%sPIDMETATRAFFICUNILOCATOR\n", indent);
		printf("%s\tparameterKind: 0x%X\n", indent, parameterKind);
		printf("%s\tparameterLength: 0x%X\n", indent, parameterLength);
		locator.walk(indent);
	}
};

struct PIDBUILTENDPOINTSET {
	uint16_t parameterKind;
	uint16_t parameterLength;
	uint32_t builtIn;
	void walk(const char * indent) {
		printf("%sPIDBUILTENDPOINTSET\n", indent);
		printf("%s\tparameterKind: 0x%X\n", indent, parameterKind);
		printf("%s\tparameterLength: 0x%X\n", indent, parameterLength);
		printf("%s\tbuiltIn: 0x%X\n", indent, builtIn);
	}
};

struct PIDPARTICIPANTBUILTENDPOINTS {
	uint16_t parameterKind;
	uint16_t parameterLength;
	uint32_t builtIn;
	void walk(const char * indent) {
		printf("%sPIDPARTICIPANTBUILTENDPOINTS\n", indent);
		printf("%s\tparameterKind: 0x%X\n", indent, parameterKind);
		printf("%s\tparameterLength: 0x%X\n", indent, parameterLength);
		printf("%s\tbuiltIn: 0x%X\n", indent, builtIn);
	}
};

struct PIDVENDORID {
	uint16_t parameterKind;
	uint16_t parameterLength;
	uint32_t vendorID;
	void walk(const char * indent) {
		printf("%sPIDVENDORID\n", indent);
		printf("%s\tparameterKind: 0x%X\n", indent, parameterKind);
		printf("%s\tparameterLength: 0x%X\n", indent, parameterLength);
		printf("%s\tvendorID: 0x%X\n", indent, vendorID);
	}
};

struct PIDPARTICIPANTGUID {
	uint16_t parameterKind;
	uint16_t parameterLength;
	GUIDPREFIX participantGUID;
	ENTITYID entityID;
	void walk(const char * indent) {
		printf("%sPIDPARTICIPANTGUID\n", indent);
		printf("%s\tparameterKind: 0x%X\n", indent, parameterKind);
		printf("%s\tparameterLength: 0x%X\n", indent, parameterLength);
		participantGUID.walk(indent);
		entityID.walk(indent);
	}
};

struct PIDPROTOVERSION {
	uint16_t parameterKind;
	uint16_t parameterLength;
	uint16_t protocolVersion;
	uint16_t slackBytes;
	void walk(const char * indent) {
		printf("%sPIDPROTOVERSION\n", indent);
		printf("%s\tparameterKind: 0x%X\n", indent, parameterKind);
		printf("%s\tparameterLength: 0x%X\n", indent, parameterLength);
		printf("%s\tprotocolVersion: 0x%X\n", indent, protocolVersion);
		printf("%s\tslackBytes: 0x%X\n", indent, slackBytes);
	}
};

struct PARTICIPANTPARAMS {
	uint32_t						type;
	PIDPROTOVERSION 			 	*pidprotoversion = NULL;
	PIDPARTICIPANTGUID 			 	*pidparticipantguid = NULL;
	PIDVENDORID 				 	*pidvendorid = NULL;
	PIDPARTICIPANTBUILTENDPOINTS 	*pidparticipantbuiltendpoints = NULL;
	PIDBUILTENDPOINTSET 		 	*pidbuiltendpointset = NULL;
	PIDMETATRAFFICUNILOCATOR 	 	*pidmetatrafficunilocator = NULL;
	PIDDEFMULTILOCATOR 				*piddefmultilocator = NULL;
	PIDPARTICIPANTLIVECOUNT 		*pidparticipantlivecount = NULL;
	PIDPARTICIPANTLEASE  			*pidparticipantlease  = NULL;
	PIDSENTINAL 					*pidsentinal = NULL;
	PIDDEFUNILOCATOR 				*piddefunilocator = NULL;
	PIDMETATRAFFICMULTILOCATOR 		*pidmetatrafficmultilocator = NULL;	
};

//Stack
struct ParticipantList {
    PARTICIPANTPARAMS * data;
    struct ParticipantList * next;
};

struct HEARTBEAT {
	uint8_t kind;
	uint8_t flags;
	uint16_t nextHeader;
	ENTITYID readerEnt;
	ENTITYID writerEnt;
	//unsigned char firstSeq[8];
	//unsigned char lastSeq[8];
	uint64_t firstSeq;
	uint64_t lastSeq;
	uint32_t count;
	void walk(const char * indent) {
		printf("%sHEARTBEAT\n", indent);
		printf("%s\tkind: 0x%X\n", indent, kind);
		printf("%s\tflags: 0x%X\n", indent, flags);
		printf("%s\tnextHeader: 0x%X\n", indent, nextHeader);
		readerEnt.walk(indent);
		writerEnt.walk(indent);
		printf("%s\tfirstSeq: 0x%" PRIu64 "\n", indent, firstSeq);
		printf("%s\tlastSeq: 0x%" PRIu64 "\n", indent, lastSeq);
		printf("%s\tcount: 0x%X\n", indent, count);
	}
};

struct GAP {
	uint8_t kind;
	uint8_t flags;
	uint16_t nextHeader;
	ENTITYID readerEnt;
	ENTITYID writerEnt;
	uint64_t gapStart;
	uint64_t bitmapBase;
	uint32_t nmBits;
	uint32_t bitmap;
	void walk(const char * indent) {
		printf("%sGAP\n",indent);
		printf("%s\tkind: 0x%X\n", indent, kind);
		printf("%s\tflags: 0x%X\n", indent, flags);
		printf("%s\tnextHeader: 0x%X\n", indent, nextHeader);
		readerEnt.walk(indent);
		writerEnt.walk(indent);
		printf("%s\tgapStart: 0x%" PRIu64 "\n", indent, gapStart);
		printf("%s\tbitmapBase: 0x%" PRIu64 "\n", indent, bitmapBase);
		printf("%s\tnmBits: 0x%X\n", indent, nmBits);
		printf("%s\tbitmap: 0x%X\n", indent, bitmap);
	}
};

struct ACKNACK {
	uint8_t kind;
	uint8_t flags;
	uint16_t nextHeader;
	ENTITYID readerEnt;
	ENTITYID writerEnt;
	SNSTATE readerSN;
	uint32_t count;	
	void walk(const char * indent) {
		printf("%sACKNACK\n",indent);
		printf("%s\tkind: 0x%X\n", indent, kind);
		printf("%s\tflags: 0x%X\n", indent, flags);
		printf("%s\tnextHeader: 0x%X\n", indent, nextHeader);
		readerEnt.walk(indent);
		writerEnt.walk(indent);
		readerSN.walk(indent);
		printf("%s\tcounter: 0x%X\n", indent, count);
	}
};

struct INFO_TS {
	uint8_t kind;
	uint8_t flags;
	uint16_t nextHeader;
	uint64_t timeStamp;
	void walk(const char * indent) {
		printf("%sINFO_TS\n", indent);
		printf("%skind: 0x%X\n", indent, kind);
		printf("%sflags: 0x%X\n", indent, flags);
		printf("%snextHeader: 0x%X\n", indent, nextHeader);
		printf("%stimeStamp: 0x%" PRIu64 "\n", indent, timeStamp);
	}
};

struct INFO_DST {
	uint8_t kind;
	uint8_t flags;
	uint16_t nextHeader;
	GUIDPREFIX guidPfx;	
	void walk(const char * indent) {
		printf("%sINFO_DST\n", indent);
		printf("%s\tkind: 0x%X\n", indent, kind);
		printf("%s\tflags: 0x%X\n", indent, flags);
		printf("%s\tnextHeader: 0x%X\n", indent, nextHeader);
		guidPfx.walk(indent);
	}
};

struct PIDUNICASTLOCATOR {
	uint16_t parameterKind;
	uint16_t parameterLength;
	LOCATOR locator;
	void walk(const char * indent) {
		printf("%sPIDUNICASTLOCATOR\n", indent);
		printf("%s\tparameterKind: 0x%X\n", indent, parameterKind);
		printf("%s\tparameterLength: 0x%X\n", indent, parameterLength);
		locator.walk(indent);
	}
};

struct PIDMULTICASTLOCATOR {
	uint16_t parameterKind;
	uint16_t parameterLength;
	LOCATOR locator;
	void walk(const char * indent) {
		printf("%sPIDMULTICASTLOCATOR\n", indent);
		printf("%s\tparameterKind: 0x%X\n", indent, parameterKind);
		printf("%s\tparameterLength: 0x%X\n", indent, parameterLength);
		locator.walk(indent);
	}	
};

struct PIDENDPOINTGUID {
	uint16_t parameterKind;
	uint16_t parameterLength;
	GUIDPREFIX participantGUID;
	ENTITYID entityID;
	void walk(const char * indent) {
		printf("%sPIDENDPOINTGUID\n", indent);
		printf("%s\tparameterKind: 0x%X\n", indent, parameterKind);
		printf("%s\tparameterLength: 0x%X\n", indent, parameterLength);
		char tab[5];
		strcpy(tab, indent);
		strcat(tab, "\t");
		participantGUID.walk(tab);
		entityID.walk(tab);
	}
};

struct PIDRELIABILITY {
	uint16_t parameterKind;
	uint16_t parameterLength;
	uint32_t reliabilityQOS;
	unsigned char *slack;
	void walk(const char * indent) {
		printf("%sPIDRELIABILITY\n", indent);
		printf("%s\tparameterKind: 0x%X\n", indent, parameterKind);
		printf("%s\tparameterLength: 0x%X\n", indent, parameterLength);
		printf("%s\treliabilityQOS: 0x%X\n", indent, reliabilityQOS);
		//NOTE: might not print due to null bytes
		printf("%s\tslack: %s\n", indent, slack);
		printf("%s\tNOTE: might not print due to null bytes\n", indent);
	}
};

struct PICTYPENAME {
	uint16_t parameterKind;
	uint16_t parameterLength;
	unsigned char *name;
	void walk(const char * indent) {
		printf("%sPICTYPENAME\n", indent);
		printf("%s\tparameterKind: 0x%X\n", indent, parameterKind);
		printf("%s\tparameterLength: 0x%X\n", indent, parameterLength);
		printf("%s\tname: %s\n", indent, name);
	}
};

struct PIDTOPICNAME {
	uint16_t parameterKind;
	uint16_t parameterLength;
	unsigned char *name;
	void walk(const char * indent) {
		printf("%sPIDTOPICNAME\n", indent);
		printf("%s\tparameterKind: 0x%X\n", indent, parameterKind);
		printf("%s\tparameterLength: 0x%X\n", indent, parameterLength);
		printf("%s\tname: %s\n", indent, name);
	}
};

struct TOPICPARMS {
	uint32_t 			type;
	//union {
	PIDTOPICNAME 		*pidtopicname = NULL;
	PICTYPENAME 		*pictypename = NULL;
	PIDRELIABILITY 		*pidreliability = NULL;
	PIDENDPOINTGUID 	*pidendpointguid = NULL;
	PIDMULTICASTLOCATOR *pidmulticastlocator = NULL;
	PIDUNICASTLOCATOR 	*pidunicastlocator = NULL;
	PIDSENTINAL 		*pidsentinal = NULL;
    //} ptr;
};

//Stack
struct TopicList {
    TOPICPARMS *data;
    struct TopicList *next;
};

struct DATA {
	uint8_t kind;
	uint8_t flags;
	uint16_t nextHeader;
	uint16_t extraFlags;
	uint16_t inlineQos;
	ENTITYID readerEnt;
	ENTITYID writerEnt;
	uint64_t writerSEQ;
	void walk(const char * indent) {
		printf("%s\tkind: 0x%X\n", indent, kind);
		printf("%s\tflags: 0x%X\n", indent, flags);
		printf("%s\tnextHeader: 0x%X\n", indent, nextHeader);
		printf("%s\textraFlags: 0x%X\n", indent, extraFlags);
		printf("%s\tinlineQos: 0x%X\n", indent, inlineQos);
		readerEnt.walk(indent);
		writerEnt.walk(indent);
		printf("%s\twriterSEQ: 0x%" PRIu64 "\n", indent, writerSEQ);
	}
/*	-- SerializedData -- size is based on next header
	--		      -- type is based on writer Entity*/
};

struct DATASUB {
	DATA *data;
	unsigned char *serializedData;
	unsigned long dataLength;
	void walk(const char * indent) {
		data->walk(indent);
		printf("%sserializedData: ", indent);
		for(int i = 0; i < dataLength; ++i)
			printf("%0.2X ", serializedData[i]);
		printf("\n");

	}
	/*	-- SerializedData -- size is based on next header
	--		      -- type is based on writer Entity*/
};

struct DATARSUB {
	DATA *data;
	uint16_t encapsKind;
	uint16_t encapsOpts;
	unsigned long topicCount;
	TOPICPARMS *topicData;

	bool TopicAnnounced()
	{
		return (topicCount != 0);
	}

	unsigned char* GetTopicName()
	{
		for (int  i = 0; i < topicCount; i++)
		{
			if (topicData[i].type == PIDTOPICNAME_KIND)
				return topicData[i].pidtopicname->name;
		}
	}


	void walk(const char * indent) {
		printf("%sDATARSUB\n", indent);
		data->walk(indent);
		printf("%s\tencapsKind: 0x%X\n", indent, encapsKind);
		printf("%s\tencapsOpts: 0x%X\n", indent, encapsOpts);
		for(int i = 0; i < topicCount; ++i) {
			switch(topicData[i].type) {
				case PIDTOPICNAME_KIND:
					topicData[i].pidtopicname->walk(indent);
					break;
				case PICTYPENAME_KIND:
					topicData[i].pictypename->walk(indent);
					break;
				case PIDRELIABILITY_KIND:
					topicData[i].pidreliability->walk(indent);
					break;
				case PIDENDPOINTGUID_KIND:
					topicData[i].pidendpointguid->walk(indent);
					break;
				case PIDMULTICASTLOCATOR_KIND:
					topicData[i].pidmulticastlocator->walk(indent);
					break;
				case PIDUNICASTLOCATOR_KIND:
					topicData[i].pidunicastlocator->walk(indent);
					break;
				case PIDSENTINAL_KIND:
					topicData[i].pidsentinal->walk(indent);
					break;
			}
		}
	}
};

struct DATAPSUB {
	DATA *data;
	uint16_t encapsKind;
	uint16_t encapsOpts;
	unsigned long particCount = 0;
	PARTICIPANTPARAMS *particData;
	void walk(const char * indent) {
		printf("%sDATAPSUB\n", indent);
		data->walk(indent);
		printf("%s\tencapsKind: 0x%X\n", indent, encapsKind);
		printf("%s\tencapsOpts: 0x%X\n", indent, encapsOpts);
		for(int i = 0; i < particCount; ++i) {
			switch(particData[i].type) {
				case PIDPROTOVERSION_KIND:
					particData[i].pidprotoversion->walk(indent);
					break;
				case PIDPARTICIPANTGUID_KIND:
					particData[i].pidparticipantguid->walk(indent);
					break;
				case PIDVENDORID_KIND:
					particData[i].pidvendorid->walk(indent);
					break;
				case PIDPARTICIPANTBUILTENDPOINTS_KIND:
					particData[i].pidparticipantbuiltendpoints->walk(indent);
					break;
				case PIDBUILTENDPOINTSET_KIND:
					particData[i].pidbuiltendpointset->walk(indent);
					break;
				case PIDMETATRAFFICUNILOCATOR_KIND:
					particData[i].pidmetatrafficunilocator->walk(indent);
					break;
				case PIDDEFMULTILOCATOR_KIND:
					particData[i].piddefmultilocator->walk(indent);
					break;
				case PIDPARTICIPANTLIVECOUNT_KIND:
					particData[i].pidparticipantlivecount->walk(indent);
					break;
				case PIDPARTICIPANTLEASE_KIND:
					particData[i].pidparticipantlease->walk(indent);
					break;
				case PIDSENTINAL_KIND:
					particData[i].pidsentinal->walk(indent);
					break;
				case PIDDEFUNILOCATOR_KIND:
					particData[i].piddefunilocator->walk(indent);
					break;
				case PIDMETATRAFFICMULTILOCATOR_KIND:
					particData[i].pidmetatrafficmultilocator->walk(indent);
					break;
			}
		}
	}
};

struct DATAWSUB {
	DATA *data;
	uint16_t encapsKind;
	uint16_t encapsOpts;
	unsigned long topicCount = 0;
	TOPICPARMS *topicData;

	bool TopicAnnounced()
	{
		return (topicCount != 0);
	}

	unsigned char* GetTopicName()
	{
		for (int  i = 0; i < topicCount; i++)
		{
			if (topicData[i].type == PIDTOPICNAME_KIND)
				return topicData[i].pidtopicname->name;
		}
	}
	
	void walk(const char * indent) {
		printf("%sDATAWSUB\n", indent);
		data->walk(indent);
		printf("%s\tencapsKind: 0x%X\n", indent, encapsKind);
		printf("%s\tencapsOpts: 0x%X\n", indent, encapsOpts);
		for(int i = 0; i < topicCount; ++i) {
			switch(topicData[i].type) {
				case PIDTOPICNAME_KIND:
					topicData[i].pidtopicname->walk(indent);
					break;
				case PICTYPENAME_KIND:
					topicData[i].pictypename->walk(indent);
					break;
				case PIDRELIABILITY_KIND:
					topicData[i].pidreliability->walk(indent);
					break;
				case PIDENDPOINTGUID_KIND:
					topicData[i].pidendpointguid->walk(indent);
					break;
				case PIDMULTICASTLOCATOR_KIND:
					topicData[i].pidmulticastlocator->walk(indent);
					break;
				case PIDUNICASTLOCATOR_KIND:
					topicData[i].pidunicastlocator->walk(indent);
					break;
				case PIDSENTINAL_KIND:
					topicData[i].pidsentinal->walk(indent);
					break;
			}
		}
	}
};

struct RTPSHeader {
	char protoName[5];
	uint16_t version;
	uint16_t vendorId;
	void walk() {
		printf("HEADER\n");
		printf("\tprotoName: %s\n", protoName);
		printf("\tversion: 0x%X\n", version);
		printf("\tvendorId: 0x%X\n", vendorId);
	}
};

struct SUBMESSAGE {
/*	union {
		ACKNACK ack;
		INFO_TS infoTS;
		INFO_DST infoDST;
	};*/
	uint16_t	type;
	ACKNACK 	*acknack = NULL;
	HEARTBEAT 	*heartbeat = NULL;
	GAP 		*gap = NULL;
	INFO_TS 	*infoTS = NULL;
	INFO_DST 	*infoDST = NULL;
	DATASUB 	*datasub = NULL;
	DATAWSUB 	*datawsub = NULL;
	DATARSUB 	*datarsub = NULL;
	DATAPSUB 	*datapsub = NULL;
};

//Stack
struct SubMsgList {
    SUBMESSAGE * data;
    struct SubMsgList * next;
};

struct RTPSMainModule {
	RTPSHeader Header;
	GUIDPREFIX guidPrefix;
	unsigned long subMsgCount = 0;
	SUBMESSAGE *subMsg = NULL;

	bool TopicAnnounced()
	{
		for(int i = 0; i < subMsgCount; i++)
		{
			if (subMsg[i].type == DATAWSUB_VAL)
			{
				if (subMsg[i].datawsub->TopicAnnounced())
					return true;
			}
			if (subMsg[i].type == DATARSUB_VAL)
			{
				if (subMsg[i].datarsub->TopicAnnounced())
					return true;
			}
		}


		return false;
	}

	bool ParticipantArrived()
	{
		for(int i = 0; i < subMsgCount; i++)
		{
			if (subMsg[i].type == DATAPSUB_VAL)
				return true;
		}	

		return false;
	}

	void TopicName()
	{
		for(int i = 0; i < subMsgCount; i++)
		{
			if (subMsg[i].type == DATAWSUB_VAL)
			{
				printf("Topic Name writer:\n");
				subMsg[i].datawsub->GetTopicName();
			}
			else if (subMsg[i].type == DATARSUB_VAL)
			{
				printf("Topic Name Reader:\n");
				subMsg[i].datarsub->GetTopicName();
			}
		}
	}

	void walk() {
		printf("Main Module\n");
		Header.walk();
		guidPrefix.walk("");
		printf("\n");
		for(int i = 0; i < subMsgCount; ++i) {
			printf("SUBMESSAGE : %d\n", i+1);
			switch(subMsg[i].type) {
				case ACKNACK_VAL:
					subMsg[i].acknack->walk("\t");
					break;
				case HEARTBEAT_VAL:
					subMsg[i].heartbeat->walk("\t");
					break;
				case GAP_VAL:
					subMsg[i].gap->walk("\t");
					break;
				case INFO_TS_VAL:
					subMsg[i].infoTS->walk("\t");
					break;
				case INFO_DST_VAL:
					subMsg[i].infoDST->walk("\t");
					break;
				case DATASUB_VAL:
					subMsg[i].datasub->walk("\t");
					break;
				case DATAWSUB_VAL:
					subMsg[i].datawsub->walk("\t");
					break;
				case DATARSUB_VAL:
					subMsg[i].datarsub->walk("\t");
					break;
				case DATAPSUB_VAL:
					subMsg[i].datapsub->walk("\t");
					break;
			}
		}	
	}
};

#endif /*RTPS_H */
