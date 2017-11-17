#ifndef SMB2_H
#define SMB2_H
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>
#include "packet.h"
#include "globals.h"
#define NEGOTIATE_SMB2_VAL (1)
#define HEADER$SYNC_SMB2_VAL (2)
#define INTEGRITY_SMB2_VAL (3)
#define ENCRYPTION_SMB2_VAL (4)
#define INTEGRITY$RESPONSE_SMB2_VAL (5)
#define ENCRYPTION$RESPONSE_SMB2_VAL (6)
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
    uint16_t alg;
} HASHALG_SMB2;
typedef struct {
    uint16_t hashalgcnt;
    uint16_t saltlength;
    unsigned long hashalglength;
    unsigned long hashalgcount;
    HASHALG_SMB2 *hashalg;
    unsigned long salt_length;
    unsigned char *salt;
} INTEGRITY_SMB2;
typedef struct {
    uint16_t cipherdata;
} CIPHER_SMB2;
typedef struct {
    uint16_t ciphercnt;
    unsigned long cipherslength;
    unsigned long cipherscount;
    CIPHER_SMB2 *ciphers;
} ENCRYPTION_SMB2;
typedef struct {
    uint32_t type;
    union {
        INTEGRITY_SMB2 integrity_smb2;
        ENCRYPTION_SMB2 encryption_smb2;
    } ptr;
} CONTEXTDATA_SMB2;
typedef struct {
    uint16_t contexttype;
    uint16_t datalength;
    uint32_t reserved;
    CONTEXTDATA_SMB2 data;
    unsigned long padding_length;
    unsigned char *padding;
} NEGOTIATECONTEXT_SMB2;
typedef struct {
    HEADER_SMB2 header;
    uint16_t structuresize;
    uint16_t dialectcount;
    uint16_t securitymode;
    uint16_t reserved;
    uint32_t capabilities;
    unsigned char clientguid [16];
    uint32_t negcontextoff;
    uint16_t negcontextcnt;
    uint16_t reserved2;
    unsigned long dialectslength;
    unsigned long dialectscount;
    DIALECT_SMB2 *dialects;
    unsigned long padding_length;
    unsigned char *padding;
    unsigned long negcontextlistlength;
    unsigned long negcontextlistcount;
    NEGOTIATECONTEXT_SMB2 *negcontextlist;
} NEGOTIATE_SMB2;
typedef struct {
    uint32_t type;
    union {
        NEGOTIATE_SMB2 negotiate_smb2;
    } ptr;
} PDU_SMB2;
typedef struct {
    uint16_t hashalgcnt;
    uint16_t saltlength;
    unsigned long hashalglength;
    unsigned long hashalgcount;
    HASHALG_SMB2 *hashalg;
    unsigned long salt_length;
    unsigned char *salt;
} INTEGRITY$RESPONSE_SMB2;
typedef struct {
    uint16_t ciphercnt;
    unsigned long cipherslength;
    unsigned long cipherscount;
    CIPHER_SMB2 *ciphers;
} ENCRYPTION$RESPONSE_SMB2;
typedef struct {
    uint32_t type;
    union {
        INTEGRITY$RESPONSE_SMB2 integrity$response_smb2;
        ENCRYPTION$RESPONSE_SMB2 encryption$response_smb2;
    } ptr;
} CONTEXTDATA$RESPONSE_SMB2;
typedef struct {
    uint16_t contexttype;
    uint16_t datalength;
    uint32_t reserved;
    CONTEXTDATA$RESPONSE_SMB2 data;
    unsigned long padding_length;
    unsigned char *padding;
} NEGOTIATECONTEXT$RESPONSE_SMB2;
typedef struct {
    HEADER_SMB2 header;
    uint16_t structuresize;
    uint16_t securitymode;
    uint16_t dialectrevision;
    uint16_t negcontextcnt;
    unsigned char serverguid [16];
    uint32_t capabilities;
    uint32_t maxtransize;
    uint32_t maxreadsize;
    uint32_t maxwritesize;
    uint64_t syetemtime;
    uint64_t serverstarttime;
    uint16_t secbufferoffset;
    uint16_t secbufferlength;
    uint32_t negcontextoff;
    unsigned long buffer_length;
    unsigned char *buffer;
    unsigned long padding_length;
    unsigned char *padding;
    unsigned long negcontextlistlength;
    unsigned long negcontextlistcount;
    NEGOTIATECONTEXT$RESPONSE_SMB2 *negcontextlist;
} NEGOTIATE$RESPONSE_SMB2;
bool parseSMB2 (PDU_SMB2 * pdu_smb2, PDUP * thePDU, char * name, uint8_t endianness);
void freePDU_SMB2 (PDU_SMB2 * mainpdu);
#endif
