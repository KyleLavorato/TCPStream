#ifndef IGMP_H
#define IGMP_H
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>
#include "packet.h"
#include "globals.h"
#define V3Report_IGMP_VAL (1)
#define Query_IGMP_VAL (2)
#define V2Report_IGMP_VAL (3)
#define V2Leave_IGMP_VAL (4)
typedef struct {
    uint8_t type;
    uint8_t maxresptime;
    uint16_t checksum;
    uint32_t groupaddr;
} V2Report_IGMP;
typedef struct {
    uint8_t type;
    uint8_t maxresptime;
    uint16_t checksum;
    uint32_t groupaddr;
} V2Leave_IGMP;
typedef struct {
    uint32_t srcaddr;
} SOURCEADDRESS_IGMP;
typedef struct {
    uint8_t recordtype;
    uint8_t auxdatalen;
    uint16_t numsources;
    uint32_t groupaddr;
    unsigned long srcaddrslength;
    unsigned long srcaddrscount;
    SOURCEADDRESS_IGMP *srcaddrs;
} GROUPRECORD_IGMP;
typedef struct {
    uint8_t type;
    uint8_t reserved;
    uint16_t checksum;
    uint16_t secondreserved;
    uint16_t numgrps;
    unsigned long grouprecordinfolength;
    unsigned long grouprecordinfocount;
    GROUPRECORD_IGMP *grouprecordinfo;
} V3Report_IGMP;
typedef struct {
    uint8_t resvsqrv;
    uint8_t qqic;
    uint16_t numsources;
    unsigned long srcaddrslength;
    unsigned long srcaddrscount;
    SOURCEADDRESS_IGMP *srcaddrs;
} V3Addition_IGMP;
typedef struct {
    uint8_t type;
    uint8_t maxresptime;
    uint16_t checksum;
    uint32_t groupaddr;
    V3Addition_IGMP *v3add;
} Query_IGMP;
typedef struct {
    uint32_t type;
    union {
        V3Report_IGMP v3report_igmp;
        Query_IGMP query_igmp;
        V2Report_IGMP v2report_igmp;
        V2Leave_IGMP v2leave_igmp;
    } ptr;
} PDU_IGMP;
void V3Report_IGMP_callback (V3Report_IGMP * v3report_igmp, PDU * thePDU);
void Query_IGMP_callback (Query_IGMP * query_igmp, PDU * thePDU);
void V2Report_IGMP_callback (V2Report_IGMP * v2report_igmp, PDU * thePDU);
void V2Leave_IGMP_callback (V2Leave_IGMP * v2leave_igmp, PDU * thePDU);
bool parseIGMP (PDU_IGMP * pdu_igmp, PDU * thePDU, char * name, uint8_t endianness);
void freePDU_IGMP (PDU_IGMP * mainpdu);
#endif
