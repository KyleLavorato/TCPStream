 #include "cglobals.h"
//#include "callback.h"
#include "Constraints.h"
#include "StringHash.h"
#include "globals.h"

#include "NTP_Generated.h"
#include "ARP_Generated.h"
#include "RTPS_Generated.h"
#include "IGMP_Generated.h"

#include <stdio.h>
#include <assert.h>
#include <arpa/inet.h>


#define NoPrint

uint32_t GenerelQueryAddress = 0x00000000; // General query comes with 0.0.0.0
uint32_t GeneralleaveAddress = 0xE0000002; // General leave comes to 224.0.0.2

//void FULL_RTPS_callback (struct FULL_RTPS * full_rtps, PDU * thePDU);
/*
callback constraintcallback  = {
    Query_IGMP, V2Report_IGMP, V2Leave_IGMP, V3Report_IGMP, PDU_RTPS,
};
*/
////*******************************************************************************************************//////////
uint32_t GetNetFromIPAddress(uint32_t IP)
{
	return (IP & 0xffffff00);
}

bool DoIPsFromSameNet(uint32_t IP1, uint32_t IP2)
{
	return (GetNetFromIPAddress(IP1) == GetNetFromIPAddress(IP2));
}

int  IsGroupAddress(uint32_t IP)
{
	uint32_t d = (IP & 0xff000000); 
	return (d) >= 0xe0000000;
}

int IsUniCastChannel(uint32_t SrcIP, uint32_t dstIP)
{
	return ((IsGroupAddress(SrcIP) == 0) && (IsGroupAddress(dstIP) == 0));
}

#define SIZEFactgroupaddressLists 256
#define ProbeValFactgroupaddressLists 389


typedef struct 
{
	uint32_t m_key; //group Address
} hashgroupaddressLists;

hashgroupaddressLists factsgroupaddressLists[SIZEFactgroupaddressLists];


int hashPosgroupaddressLists(uint32_t key)
{
  return key % SIZEFactgroupaddressLists;
}

int GetNextPosgroupaddressLists(int pos)
{
  return (pos + ProbeValFactgroupaddressLists ) % SIZEFactgroupaddressLists;

}

int insertValuegroupaddressLists(uint32_t key)
{
	int pos = hashPosgroupaddressLists(key);

     int originpos = pos;

     do
     {
       if (factsgroupaddressLists[pos].m_key == 0)
       {
          factsgroupaddressLists[pos].m_key = key;
          return pos;
       }
       else
       {
        if (factsgroupaddressLists[pos].m_key == key)
        {
          return pos;
        }

       }

       pos = GetNextPosgroupaddressLists(pos);

     } while (pos != originpos);

     return -1;

}

int deleteValuegroupaddressLists(uint32_t key)
{
	int pos = hashPosgroupaddressLists(key);
    int originpos = pos;

	 do
	 {
	   if (factsgroupaddressLists[pos].m_key == key)
	   {
	   	  factsgroupaddressLists[pos].m_key = 0;
	      return pos;
	   }

	   pos = GetNextPosgroupaddressLists(pos);

	 }while (pos != originpos);

	 return -1;
}


int HasValuegroupaddressLists(uint32_t key)
{
	int pos = hashPosgroupaddressLists(key);
    int originpos = pos;

	 do
	 {
	   if (factsgroupaddressLists[pos].m_key == key)
	      return pos;
	   pos = GetNextPosgroupaddressLists(pos);

	 }while (pos != originpos);

	 return -1;
}


#define SIZEFactC5 256
#define ProbeValFactC5 389

typedef struct 
{
	uint32_t m_key1; //IP Address
	uint32_t m_key2; //Group Address
	uint32_t m_key3; // instantiate
} hashC5Facts;

hashC5Facts factsC5Lists[SIZEFactC5];


int hashPosC5Facts(uint32_t key1, uint32_t key2, uint32_t key3)
{
  unsigned res = key1 * key2 * key3; 
  return res % SIZEFactgroupaddressLists;
}

int GetNextPosC5Facts(int pos)
{
  return (pos + ProbeValFactC5 ) % SIZEFactC5;

}

int insertValueC5Facts(uint32_t key1, uint32_t key2, uint32_t key3)
{
	int pos = hashPosC5Facts(key1, key2, key3);

     int originpos = pos;

     do
     {
       if (factsC5Lists[pos].m_key1 == 0)
       {
          factsC5Lists[pos].m_key1 = key1;
          factsC5Lists[pos].m_key2 = key2;
          factsC5Lists[pos].m_key3 = key3;
          return pos;
       }
       else
       {
        if (factsC5Lists[pos].m_key1 == key1 &&
        	factsC5Lists[pos].m_key2 == key2 &&
        	factsC5Lists[pos].m_key3 == key3)
        {
          return pos;
        }

       }

       pos = GetNextPosgroupaddressLists(pos);

     } while (pos != originpos);

     return -1;
}


void Query_IGMP_callback(Query_IGMP * q, PDU * thePDU){
	
}

void V2Report_IGMP_callback(V2Report_IGMP * v, PDU * thePDU) {
	
}

void V2Leave_IGMP_callback(V2Leave_IGMP * v, PDU * thePDU) {

}

void V3Report_IGMP_callback(V3Report_IGMP * v, PDU * thePDU) {
	
}

void FULL_RTPS_callback(FULL_RTPS * r, PDU * thePDU) 
{
	fprintf(traceFile,"\t(Full callback reached)");

}

// ADDED FROM ORIGINAL //

void DATAPSUB_RTPS_callback (FULL_RTPS * full_rtps, DATAPSUB_RTPS * datapsub_rtps, PDU * thePDU) {
	if (traceFile) fprintf(traceFile," | DATAPSUB");
}

void DATASUB_RTPS_callback (FULL_RTPS * full_rtps, DATASUB_RTPS * datasub_rtps, PDU * thePDU) {
	if (traceFile) fprintf(traceFile," | DATASUB");
}

void ACKNACK_RTPS_callback (FULL_RTPS * full_rtps, ACKNACK_RTPS * acknack_rtps, PDU * thePDU) {
	if (traceFile) fprintf(traceFile," | ACKNACK");
}

void HEARTBEAT_RTPS_callback (FULL_RTPS * full_rtps, HEARTBEAT_RTPS * heartbeat_rtps, PDU * thePDU) {
	if (traceFile) fprintf(traceFile," | HEARTBEAT");
	//walkFULLRTPS(full_rtps);
	//walkHEARTBEAT(heartbeat_rtps);
}

void INFO$DST_RTPS_callback (FULL_RTPS * full_rtps, INFO$DST_RTPS * info$dst_rtps, PDU * thePDU) {
	if (traceFile) fprintf(traceFile," | INFO_DST");
	//walkFULLRTPS(full_rtps);
	//walkINFO$DST(info$dst_rtps);
}

void INFO$TS_RTPS_callback (FULL_RTPS * full_rtps, INFO$TS_RTPS * info$ts_rtps, PDU * thePDU) {
	if (traceFile) fprintf(traceFile," | INFO_TS");
}

void DATAWSUB_RTPS_callback (FULL_RTPS * full_rtps, DATAWSUB_RTPS * datawsub_rtps, PDU * thePDU) {
	if (traceFile) fprintf(traceFile," | DATAWSUB");
}

void DATARSUB_RTPS_callback (FULL_RTPS * full_rtps, DATARSUB_RTPS * datarsub_rtps, PDU * thePDU) {
	if (traceFile) fprintf(traceFile," | DATARSUB");
}

void GAP_RTPS_callback (FULL_RTPS * full_rtps, GAP_RTPS * gap_rtps, PDU * thePDU) {
	if (traceFile) fprintf(traceFile," | GAP");
}

void QOSPARM_RTPS_callback (QOSPARM_RTPS * qosparm_rtps, PDU * thePDU) {
  ;
}


// END ADDED //

////*******************************************************************************************************//////////




