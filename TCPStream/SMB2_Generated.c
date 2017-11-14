#define BIGENDIAN (0x0)
#define LITTLEENDIAN (0x1)
#include "SMB2_Generated.h"
#include "pglobals.h"
#include "putilities.h"
void freePDU_SMB2 (PDU_SMB2 *mainpdu);
bool parseSMB2 (PDU_SMB2 *pdu_smb2, PDUP *thePDU, char *progname, uint8_t endianness);
bool parseTEST (TEST_SMB2 *test_smb2, PDUP *thePDU, char *progname, uint8_t endianness);
bool parseHEADER (HEADER_SMB2 *header_smb2, PDUP *thePDU, char *progname, uint8_t endianness);
bool parseHEADER$ASYNC (HEADER$ASYNC_SMB2 *header$async_smb2, PDUP *thePDU, char *progname, uint8_t endianness);
bool parseHEADER$SYNC (HEADER$SYNC_SMB2 *header$sync_smb2, PDUP *thePDU, char *progname, uint8_t endianness);
bool parseNEGOTIATE (NEGOTIATE_SMB2 *negotiate_smb2, PDUP *thePDU, char *progname, uint8_t endianness);
DIALECT_SMB2 *parseSetOfDIALECT (PDUP *thePDU, int n, int *size, char *progname, uint8_t endianness);
bool parseDIALECT (DIALECT_SMB2 *dialect_smb2, PDUP *thePDU, char *progname, uint8_t endianness);

bool parseSMB2 (PDU_SMB2 *pdu_smb2, PDUP *thePDU, char *progname, uint8_t endianness) {
    unsigned long pos = thePDU->curPos;
    unsigned long remaining = thePDU->remaining;
    if (parseTEST (&pdu_smb2->ptr.test_smb2, thePDU, progname, endianness)) {
        pdu_smb2->type = TEST_SMB2_VAL;
        return true;
    }
    thePDU->curPos = pos;
    thePDU->remaining = remaining;
    if (parseNEGOTIATE (&pdu_smb2->ptr.negotiate_smb2, thePDU, progname, endianness)) {
        pdu_smb2->type = NEGOTIATE_SMB2_VAL;
        return true;
    }
    return false;
}

bool parseTEST (TEST_SMB2 *test_smb2, PDUP *thePDU, char *progname, uint8_t endianness) {
    if (!lengthRemaining (thePDU, 0, progname)) {
        return false;
    }
    HEADER_SMB2 header;
    if (!parseHEADER (&header, thePDU, progname, endianness)) {
        return false;
    }
    test_smb2->header = header;
    return true;
}

bool parseHEADER (HEADER_SMB2 *header_smb2, PDUP *thePDU, char *progname, uint8_t endianness) {
    unsigned long pos = thePDU->curPos;
    unsigned long remaining = thePDU->remaining;
    if (parseHEADER$ASYNC (&header_smb2->ptr.header$async_smb2, thePDU, progname, endianness)) {
        header_smb2->type = HEADER$ASYNC_SMB2_VAL;
        return true;
    }
    thePDU->curPos = pos;
    thePDU->remaining = remaining;
    if (parseHEADER$SYNC (&header_smb2->ptr.header$sync_smb2, thePDU, progname, endianness)) {
        header_smb2->type = HEADER$SYNC_SMB2_VAL;
        return true;
    }
    return false;
}

bool parseHEADER$ASYNC (HEADER$ASYNC_SMB2 *header$async_smb2, PDUP *thePDU, char *progname, uint8_t endianness) {
    if (!lengthRemaining (thePDU, 64, progname)) {
        return false;
    }
    header$async_smb2->protoid = get32_e (thePDU, endianness);
    if (!(header$async_smb2->protoid == 0xFE534D42)) {
        return false;
    }
    header$async_smb2->structuresize = get16_e (thePDU, endianness);
    if (!(header$async_smb2->structuresize == 64)) {
        return false;
    }
    header$async_smb2->creditcharge = get16_e (thePDU, endianness);
    header$async_smb2->ntstatus = get32_e (thePDU, endianness);
    header$async_smb2->command = get16_e (thePDU, endianness);
    header$async_smb2->creditreq = get16_e (thePDU, endianness);
    header$async_smb2->flags = get32_e (thePDU, endianness);
    if (!((header$async_smb2->flags& 0x00000002) == 2)) {
        return false;
    }
    header$async_smb2->nextcommand = get32_e (thePDU, endianness);
    header$async_smb2->messageid = get64_e (thePDU, endianness);
    header$async_smb2->asyncid = get64_e (thePDU, endianness);
    header$async_smb2->sessionid = get64_e (thePDU, endianness);
    memcpy (header$async_smb2->signature, &thePDU->data[thePDU->curPos], 16);
    thePDU->curPos += 16;
    if (header$async_smb2->signature[16 - 1] != '\0') {
    }
    return true;
}

bool parseHEADER$SYNC (HEADER$SYNC_SMB2 *header$sync_smb2, PDUP *thePDU, char *progname, uint8_t endianness) {
    if (!lengthRemaining (thePDU, 64, progname)) {
        return false;
    }
    header$sync_smb2->protoid = get32_e (thePDU, endianness);
    if (!(header$sync_smb2->protoid == 0xFE534D42)) {
        return false;
    }
    header$sync_smb2->structuresize = get16_e (thePDU, endianness);
    if (!(header$sync_smb2->structuresize == 64)) {
        return false;
    }
    header$sync_smb2->creditcharge = get16_e (thePDU, endianness);
    header$sync_smb2->ntstatus = get32_e (thePDU, endianness);
    header$sync_smb2->command = get16_e (thePDU, endianness);
    header$sync_smb2->creditreq = get16_e (thePDU, endianness);
    header$sync_smb2->flags = get32_e (thePDU, endianness);
    if (!((header$sync_smb2->flags& 0x00000002) != 2)) {
        return false;
    }
    header$sync_smb2->nextcommand = get32_e (thePDU, endianness);
    header$sync_smb2->messageid = get64_e (thePDU, endianness);
    header$sync_smb2->reserved = get32_e (thePDU, endianness);
    header$sync_smb2->treeid = get32_e (thePDU, endianness);
    header$sync_smb2->sessionid = get64_e (thePDU, endianness);
    memcpy (header$sync_smb2->signature, &thePDU->data[thePDU->curPos], 16);
    thePDU->curPos += 16;
    if (header$sync_smb2->signature[16 - 1] != '\0') {
    }
    return true;
}

bool parseNEGOTIATE (NEGOTIATE_SMB2 *negotiate_smb2, PDUP *thePDU, char *progname, uint8_t endianness) {
    if (!lengthRemaining (thePDU, 36, progname)) {
        return false;
    }
    negotiate_smb2->dialects = NULL;
    HEADER_SMB2 header;
    if (!parseHEADER (&header, thePDU, progname, endianness)) {
        return false;
    }
    negotiate_smb2->header = header;
    negotiate_smb2->structuresize = get16_e (thePDU, endianness);
    negotiate_smb2->dialectcount = get16_e (thePDU, endianness);
    negotiate_smb2->securitymode = get16_e (thePDU, endianness);
    negotiate_smb2->reserved = get16_e (thePDU, endianness);
    negotiate_smb2->capabilities = get32_e (thePDU, endianness);
    memcpy (negotiate_smb2->clientguid, &thePDU->data[thePDU->curPos], 16);
    thePDU->curPos += 16;
    if (negotiate_smb2->clientguid[16 - 1] != '\0') {
    }
    negotiate_smb2->negclientoffset = get32_e (thePDU, endianness);
    negotiate_smb2->negcontextcnt = get16_e (thePDU, endianness);
    negotiate_smb2->reserved2 = get16_e (thePDU, endianness);
    int size = 0;
    negotiate_smb2->dialectslength = thePDU->curPos;
    negotiate_smb2->dialects = parseSetOfDIALECT (thePDU, 0, &size, progname, endianness);
    if (negotiate_smb2->dialects == NULL) {
        return false;
    }
    negotiate_smb2->dialectscount = size;
    negotiate_smb2->dialectslength = thePDU->curPos - negotiate_smb2->dialectslength;
    return true;
}

bool parseDIALECT (DIALECT_SMB2 *dialect_smb2, PDUP *thePDU, char *progname, uint8_t endianness) {
    if (!lengthRemaining (thePDU, 2, progname)) {
        return false;
    }
    dialect_smb2->value = get16_e (thePDU, endianness);
    if (!(dialect_smb2->value == 0x0202 ||dialect_smb2->value == 0x0210 ||dialect_smb2->value == 0x0300 ||dialect_smb2->value == 0x0302 ||dialect_smb2->value == 0x0311)) {
        return false;
    }
    return true;
}

void freePDU_SMB2 (PDU_SMB2 *mainpdu) {
    if (mainpdu->type == NEGOTIATE_SMB2_VAL) {
        if (mainpdu->ptr.negotiate_smb2.dialects != NULL) {
            for (int i = 0; i < mainpdu->ptr.negotiate_smb2.dialectscount; ++i) {
                if (&mainpdu->ptr.negotiate_smb2.dialects [i] != NULL) {
                }
            }
            if (mainpdu->ptr.negotiate_smb2.dialects != NULL) {
                free (mainpdu->ptr.negotiate_smb2.dialects);
                mainpdu->ptr.negotiate_smb2.dialects = NULL;
            }
        }
    }
    if (mainpdu->type == TEST_SMB2_VAL) {
    }
}

DIALECT_SMB2 *parseSetOfDIALECT (PDUP *thePDU, int n, int *size, char *progname, uint8_t endianness) {
    DIALECT_SMB2 dialects;
    if (!parseDIALECT (&dialects, thePDU, progname, endianness)) {
        if (n == 0) {
            *size = 0;
            return NULL;
        }
        DIALECT_SMB2 *result = (DIALECT_SMB2 *) malloc ((n) *sizeof(DIALECT_SMB2));
        if (result == NULL) {
            fprintf (stderr, "%s: internal malloc error file: %s line: %d \n", progname, __FILE__, __LINE__);
            return NULL;
        }
        *size = n;
        return result;
    }
    else {
        DIALECT_SMB2 *result = parseSetOfDIALECT (thePDU, n +1, size, progname, endianness);
        result[n] = dialects;
        return result;
    }
}

