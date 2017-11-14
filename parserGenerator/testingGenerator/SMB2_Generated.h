#ifndef SMB2_H
#define SMB2_H
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>
#include "packet.h"
#include "globals.h"
#define TEST_SMB2_VAL (1)
#define NEGOTIATE_SMB2_VAL (2)
#define HEADER$ASYNC_SMB2_VAL (3)
#define HEADER$SYNC_SMB2_VAL (4)
typedef struct {
    uint32_t protoid;
    uint16_t structuresize;
    uint16_t creditcharge;
    uint32_t ntstatus;
    uint16_t command;
    uint16_t creditreq;
    uint32_t flags;
    uint32_t nextcommand;
    uint64_t messageid;
    uint64_t asyncid;
    uint64_t sessionid;
    unsigned char signature [16];
} HEADER$ASYNC_SMB2;
typedef struct {
    uint32_t protoid;
    uint16_t structuresize;
    uint16_t creditcharge;
    uint32_t ntstatus;
    uint16_t command;
    uint16_t creditreq;
    uint32_t flags;
    uint32_t nextcommand;
    uint64_t messageid;
    uint32_t reserved;
    uint32_t treeid;
    uint64_t sessionid;
    unsigned char signature [16];
} HEADER$SYNC_SMB2;
typedef struct {
    uint32_t type;
    union {
        HEADER$ASYNC_SMB2 header$async_smb2;
        HEADER$SYNC_SMB2 header$sync_smb2;
    } ptr;
} HEADER_SMB2;
typedef struct {
    HEADER_SMB2 header;
} TEST_SMB2;
typedef struct {
    uint16_t value;
} DIALECT_SMB2;
typedef struct {
    HEADER_SMB2 header;
    uint16_t structuresize;
    uint16_t dialectcount;
    uint16_t securitymode;
    uint16_t reserved;
    uint32_t capabilities;
    unsigned char clientguid [16];
    uint32_t negclientoffset;
    uint16_t negcontextcnt;
    uint16_t reserved2;
    unsigned long dialectslength;
    unsigned long dialectscount;
    DIALECT_SMB2 *dialects;
} NEGOTIATE_SMB2;
typedef struct {
    uint32_t type;
    union {
        TEST_SMB2 test_smb2;
        NEGOTIATE_SMB2 negotiate_smb2;
    } ptr;
} PDU_SMB2;
bool parseSMB2 (PDU_SMB2 * pdu_smb2, PDU * thePDU, char * name, uint8_t endianness);
void freePDU_SMB2 (PDU_SMB2 * mainpdu);
#endif
