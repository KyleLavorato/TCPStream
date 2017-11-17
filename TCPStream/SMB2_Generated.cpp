#define BIGENDIAN (0x0)
#define LITTLEENDIAN (0x1)
#include "SMB2_Generated.h"
#include "pglobals.h"
#include "putilities.h"
void freePDU_SMB2 (PDU_SMB2 *mainpdu);
bool parseSMB2 (PDU_SMB2 *pdu_smb2, PDUP *thePDU, char *progname, uint8_t endianness);
bool parseTEST (TEST_SMB2 *test_smb2, PDUP *thePDU, char *progname, uint8_t endianness);
bool parseHEADER (HEADER_SMB2 *header_smb2, PDUP *thePDU, char *progname, uint8_t endianness);
bool parseHEADER$SYNC (HEADER$SYNC_SMB2 *header$sync_smb2, PDUP *thePDU, char *progname, uint8_t endianness);
bool parseNEGOTIATE (NEGOTIATE_SMB2 *negotiate_smb2, PDUP *thePDU, char *progname, uint8_t endianness);
DIALECT_SMB2 *parseSetOfDIALECT (PDUP *thePDU, int size, char *progname, uint8_t endianness);
NEGOTIATECONTEXT_SMB2 *parseSetOfNEGOTIATECONTEXT (PDUP *thePDU, int size, char *progname, uint8_t endianness);
bool parseDIALECT (DIALECT_SMB2 *dialect_smb2, PDUP *thePDU, char *progname, uint8_t endianness);
bool parseNEGOTIATECONTEXT (NEGOTIATECONTEXT_SMB2 *negotiatecontext_smb2, PDUP *thePDU, char *progname, uint8_t endianness);
bool parseCONTEXTDATA (CONTEXTDATA_SMB2 *contextdata_smb2, PDUP *thePDU, char *progname, uint8_t endianness);
bool parseINTEGRITY (INTEGRITY_SMB2 *integrity_smb2, PDUP *thePDU, char *progname, uint8_t endianness);
bool parseHASHALG (HASHALG_SMB2 *hashalg_smb2, PDUP *thePDU, char *progname, uint8_t endianness);
bool parseENCRYPTION (ENCRYPTION_SMB2 *encryption_smb2, PDUP *thePDU, char *progname, uint8_t endianness);
bool parseCIPHER (CIPHER_SMB2 *cipher_smb2, PDUP *thePDU, char *progname, uint8_t endianness);
bool parseNEGOTIATE$RESPONSE (NEGOTIATE$RESPONSE_SMB2 *negotiate$response_smb2, PDUP *thePDU, char *progname, uint8_t endianness);
NEGOTIATECONTEXT$RESPONSE_SMB2 *parseSetOfNEGOTIATECONTEXT$RESPONSE (PDUP *thePDU, int size, char *progname, uint8_t endianness);
bool parseNEGOTIATECONTEXT$RESPONSE (NEGOTIATECONTEXT$RESPONSE_SMB2 *negotiatecontext$response_smb2, PDUP *thePDU, char *progname, uint8_t endianness);
bool parseCONTEXTDATA$RESPONSE (CONTEXTDATA$RESPONSE_SMB2 *contextdata$response_smb2, PDUP *thePDU, char *progname, uint8_t endianness);
bool parseINTEGRITY$RESPONSE (INTEGRITY$RESPONSE_SMB2 *integrity$response_smb2, PDUP *thePDU, char *progname, uint8_t endianness);
HASHALG_SMB2 *parseSetOfHASHALG (PDUP *thePDU, int size, char *progname, uint8_t endianness);
bool parseENCRYPTION$RESPONSE (ENCRYPTION$RESPONSE_SMB2 *encryption$response_smb2, PDUP *thePDU, char *progname, uint8_t endianness);
CIPHER_SMB2 *parseSetOfCIPHER (PDUP *thePDU, int size, char *progname, uint8_t endianness);

bool parseSMB2 (PDU_SMB2 *pdu_smb2, PDUP *thePDU, char *progname, uint8_t endianness) {
    unsigned long pos = thePDU->curPos;
    unsigned long remaining = thePDU->remaining;
    if (parseNEGOTIATE (&pdu_smb2->ptr.negotiate_smb2, thePDU, progname, endianness)) {
        pdu_smb2->type = NEGOTIATE_SMB2_VAL;
        return true;
    }
    return false;
}

bool parseTEST (TEST_SMB2 *test_smb2, PDUP *thePDU, char *progname, uint8_t endianness) {
    fprintf (stderr, "%*sParse TEST\n", indent, "");
    indent += 2;
    if (!lengthRemaining (thePDU, 0, progname)) {
        return false;
    }
    HEADER_SMB2 header;
    if (!parseHEADER (&header, thePDU, progname, endianness)) {
        return false;
    }
    test_smb2->header = header;
    fprintf (stderr, "%*sEND TEST\n", indent, "");
    indent -= 2;
    return true;
}

bool parseHEADER (HEADER_SMB2 *header_smb2, PDUP *thePDU, char *progname, uint8_t endianness) {
    unsigned long pos = thePDU->curPos;
    unsigned long remaining = thePDU->remaining;
    if (parseHEADER$SYNC (&header_smb2->ptr.header$sync_smb2, thePDU, progname, endianness)) {
        header_smb2->type = HEADER$SYNC_SMB2_VAL;
        return true;
    }
    return false;
}

bool parseHEADER$SYNC (HEADER$SYNC_SMB2 *header$sync_smb2, PDUP *thePDU, char *progname, uint8_t endianness) {
    fprintf (stderr, "%*sParse HEADER$SYNC\n", indent, "");
    indent += 2;
    if (!lengthRemaining (thePDU, 64, progname)) {
        return false;
    }
    header$sync_smb2->protoid = get32_e (thePDU, endianness);
    fprintf (stderr, "%*sprotoID: %08x \n", indent, "", header$sync_smb2->protoid);
    if (!(header$sync_smb2->protoid == 0x424D53FE)) {
        return false;
    }
    header$sync_smb2->structuresize = get16_e (thePDU, endianness);
    fprintf (stderr, "%*sstructureSize: %04x \n", indent, "", header$sync_smb2->structuresize);
    if (!(header$sync_smb2->structuresize == 64)) {
        return false;
    }
    header$sync_smb2->creditcharge = get16_e (thePDU, endianness);
    fprintf (stderr, "%*screditCharge: %04x \n", indent, "", header$sync_smb2->creditcharge);
    header$sync_smb2->ntstatus = get32_e (thePDU, endianness);
    fprintf (stderr, "%*sntStatus: %08x \n", indent, "", header$sync_smb2->ntstatus);
    header$sync_smb2->command = get16_e (thePDU, endianness);
    fprintf (stderr, "%*scommand: %04x \n", indent, "", header$sync_smb2->command);
    header$sync_smb2->creditreq = get16_e (thePDU, endianness);
    fprintf (stderr, "%*screditREQ: %04x \n", indent, "", header$sync_smb2->creditreq);
    header$sync_smb2->flags = get32_e (thePDU, endianness);
    fprintf (stderr, "%*sflags: %08x \n", indent, "", header$sync_smb2->flags);
    if (!((header$sync_smb2->flags& 0x00000002) != 2)) {
        return false;
    }
    header$sync_smb2->nextcommand = get32_e (thePDU, endianness);
    fprintf (stderr, "%*snextCommand: %08x \n", indent, "", header$sync_smb2->nextcommand);
    header$sync_smb2->messageid = get64_e (thePDU, endianness);
    fprintf (stderr, "%*smessageId: %016lx \n", indent, "", header$sync_smb2->messageid);
    header$sync_smb2->reserved = get32_e (thePDU, endianness);
    fprintf (stderr, "%*sreserved: %08x \n", indent, "", header$sync_smb2->reserved);
    header$sync_smb2->treeid = get32_e (thePDU, endianness);
    fprintf (stderr, "%*streeId: %08x \n", indent, "", header$sync_smb2->treeid);
    header$sync_smb2->sessionid = get64_e (thePDU, endianness);
    fprintf (stderr, "%*ssessionId: %016lx \n", indent, "", header$sync_smb2->sessionid);
    memcpy (header$sync_smb2->signature, &thePDU->data[thePDU->curPos], 16);
    thePDU->curPos += 16;
    if (header$sync_smb2->signature[16 - 1] != '\0') {
    }
    fprintf (stderr, "%*ssignature: ", indent, "");
    for (int q = 0; q < 16; q++) {
        fprintf (stderr, "%02x ", header$sync_smb2->signature[q]);
    }
    fprintf (stderr, "\n");
    fprintf (stderr, "%*sEND HEADER$SYNC\n", indent, "");
    indent -= 2;
    return true;
}

bool parseNEGOTIATE (NEGOTIATE_SMB2 *negotiate_smb2, PDUP *thePDU, char *progname, uint8_t endianness) {
    fprintf (stderr, "%*sParse NEGOTIATE\n", indent, "");
    indent += 2;
    if (!lengthRemaining (thePDU, 36, progname)) {
        return false;
    }
    negotiate_smb2->dialects = NULL;
    negotiate_smb2->padding = NULL;
    negotiate_smb2->negcontextlist = NULL;
    HEADER_SMB2 header;
    if (!parseHEADER (&header, thePDU, progname, endianness)) {
        return false;
    }
    negotiate_smb2->header = header;
    negotiate_smb2->structuresize = get16_e (thePDU, endianness);
    fprintf (stderr, "%*sstructureSize: %04x \n", indent, "", negotiate_smb2->structuresize);
    negotiate_smb2->dialectcount = get16_e (thePDU, endianness);
    fprintf (stderr, "%*sdialectCount: %04x \n", indent, "", negotiate_smb2->dialectcount);
    negotiate_smb2->securitymode = get16_e (thePDU, endianness);
    fprintf (stderr, "%*ssecurityMode: %04x \n", indent, "", negotiate_smb2->securitymode);
    if (!(negotiate_smb2->securitymode == 0x0001 ||negotiate_smb2->securitymode == 0x0002)) {
        return false;
    }
    negotiate_smb2->reserved = get16_e (thePDU, endianness);
    fprintf (stderr, "%*sreserved: %04x \n", indent, "", negotiate_smb2->reserved);
    negotiate_smb2->capabilities = get32_e (thePDU, endianness);
    fprintf (stderr, "%*scapabilities: %08x \n", indent, "", negotiate_smb2->capabilities);
    memcpy (negotiate_smb2->clientguid, &thePDU->data[thePDU->curPos], 16);
    thePDU->curPos += 16;
    if (negotiate_smb2->clientguid[16 - 1] != '\0') {
    }
    fprintf (stderr, "%*sclientGuid: ", indent, "");
    for (int q = 0; q < 16; q++) {
        fprintf (stderr, "%02x ", negotiate_smb2->clientguid[q]);
    }
    fprintf (stderr, "\n");
    negotiate_smb2->negcontextoff = get32_e (thePDU, endianness);
    fprintf (stderr, "%*snegContextOff: %08x \n", indent, "", negotiate_smb2->negcontextoff);
    negotiate_smb2->negcontextcnt = get16_e (thePDU, endianness);
    fprintf (stderr, "%*snegContextCnt: %04x \n", indent, "", negotiate_smb2->negcontextcnt);
    negotiate_smb2->reserved2 = get16_e (thePDU, endianness);
    fprintf (stderr, "%*sreserved2: %04x \n", indent, "", negotiate_smb2->reserved2);
    negotiate_smb2->dialectscount = negotiate_smb2->dialectcount;
    negotiate_smb2->dialectslength = thePDU->curPos;
    negotiate_smb2->dialects = parseSetOfDIALECT (thePDU, negotiate_smb2->dialectcount, progname, endianness);
    if (negotiate_smb2->dialects == NULL) {
        return false;
    }
    negotiate_smb2->dialectslength = thePDU->curPos - negotiate_smb2->dialectslength;
    if (lengthRemaining (thePDU, 8 - ((64 + 36 + negotiate_smb2->dialectcount * 2) % 8), progname)) {
        negotiate_smb2->padding = (unsigned char *) malloc (sizeof (unsigned char) * (8 - ((64 + 36 + negotiate_smb2->dialectcount * 2) % 8)));
        if (negotiate_smb2->padding == NULL) {
            fprintf (stderr, "%s: internal malloc error file: %s line: %d \n", progname, __FILE__, __LINE__);
            return false;
        }
        negotiate_smb2->padding_length = 8 - ((64 + 36 + negotiate_smb2->dialectcount * 2) % 8);
        memcpy (negotiate_smb2->padding, &thePDU->data[thePDU->curPos], 8 - ((64 + 36 + negotiate_smb2->dialectcount * 2) % 8));
        thePDU->curPos += 8 - ((64 + 36 + negotiate_smb2->dialectcount * 2) % 8);
        if (negotiate_smb2->padding[8 - ((64 + 36 + negotiate_smb2->dialectcount * 2) % 8) - 1] != '\0') {
        }
        fprintf (stderr, "%*spadding: ", indent, "");
        for (int q = 0; q < 8 - ((64 + 36 + negotiate_smb2->dialectcount * 2) % 8); q++) {
            fprintf (stderr, "%02x ", negotiate_smb2->padding[q]);
        }
        fprintf (stderr, "\n");
    }
    negotiate_smb2->negcontextlistcount = negotiate_smb2->negcontextcnt;
    negotiate_smb2->negcontextlistlength = thePDU->curPos;
    negotiate_smb2->negcontextlist = parseSetOfNEGOTIATECONTEXT (thePDU, negotiate_smb2->negcontextcnt, progname, endianness);
    if (negotiate_smb2->negcontextlist == NULL) {
        return false;
    }
    negotiate_smb2->negcontextlistlength = thePDU->curPos - negotiate_smb2->negcontextlistlength;
    fprintf (stderr, "%*sEND NEGOTIATE\n", indent, "");
    indent -= 2;
    return true;
}

bool parseDIALECT (DIALECT_SMB2 *dialect_smb2, PDUP *thePDU, char *progname, uint8_t endianness) {
    fprintf (stderr, "%*sParse DIALECT\n", indent, "");
    indent += 2;
    if (!lengthRemaining (thePDU, 2, progname)) {
        return false;
    }
    dialect_smb2->value = get16_e (thePDU, endianness);
    fprintf (stderr, "%*svalue: %04x \n", indent, "", dialect_smb2->value);
    if (!(dialect_smb2->value == 0x0202 ||dialect_smb2->value == 0x0210 ||dialect_smb2->value == 0x0300 ||dialect_smb2->value == 0x0302 ||dialect_smb2->value == 0x0311)) {
        return false;
    }
    fprintf (stderr, "%*sEND DIALECT\n", indent, "");
    indent -= 2;
    return true;
}

bool parseNEGOTIATECONTEXT (NEGOTIATECONTEXT_SMB2 *negotiatecontext_smb2, PDUP *thePDU, char *progname, uint8_t endianness) {
    fprintf (stderr, "%*sParse NEGOTIATECONTEXT\n", indent, "");
    indent += 2;
    if (!lengthRemaining (thePDU, 8, progname)) {
        return false;
    }
    negotiatecontext_smb2->padding = NULL;
    negotiatecontext_smb2->contexttype = get16_e (thePDU, endianness);
    fprintf (stderr, "%*scontextType: %04x \n", indent, "", negotiatecontext_smb2->contexttype);
    if (!(negotiatecontext_smb2->contexttype == 0x0001 ||negotiatecontext_smb2->contexttype == 0x0002)) {
        return false;
    }
    negotiatecontext_smb2->datalength = get16_e (thePDU, endianness);
    fprintf (stderr, "%*sdataLength: %04x \n", indent, "", negotiatecontext_smb2->datalength);
    negotiatecontext_smb2->reserved = get32_e (thePDU, endianness);
    fprintf (stderr, "%*sreserved: %08x \n", indent, "", negotiatecontext_smb2->reserved);
    CONTEXTDATA_SMB2 data;
    if (!parseCONTEXTDATA (&data, thePDU, progname, endianness)) {
        return false;
    }
    negotiatecontext_smb2->data = data;
    if (lengthRemaining (thePDU, (8 - ((8 + negotiatecontext_smb2->datalength) % 8)), progname)) {
        negotiatecontext_smb2->padding = (unsigned char *) malloc (sizeof (unsigned char) * ((8 - ((8 + negotiatecontext_smb2->datalength) % 8))));
        if (negotiatecontext_smb2->padding == NULL) {
            fprintf (stderr, "%s: internal malloc error file: %s line: %d \n", progname, __FILE__, __LINE__);
            return false;
        }
        negotiatecontext_smb2->padding_length = (8 - ((8 + negotiatecontext_smb2->datalength) % 8));
        memcpy (negotiatecontext_smb2->padding, &thePDU->data[thePDU->curPos], (8 - ((8 + negotiatecontext_smb2->datalength) % 8)));
        thePDU->curPos += (8 - ((8 + negotiatecontext_smb2->datalength) % 8));
        if (negotiatecontext_smb2->padding[(8 - ((8 + negotiatecontext_smb2->datalength) % 8)) - 1] != '\0') {
        }
        fprintf (stderr, "%*spadding: ", indent, "");
        for (int q = 0; q < (8 - ((8 + negotiatecontext_smb2->datalength) % 8)); q++) {
            fprintf (stderr, "%02x ", negotiatecontext_smb2->padding[q]);
        }
        fprintf (stderr, "\n");
    }
    fprintf (stderr, "%*sEND NEGOTIATECONTEXT\n", indent, "");
    indent -= 2;
    return true;
}

bool parseCONTEXTDATA (CONTEXTDATA_SMB2 *contextdata_smb2, PDUP *thePDU, char *progname, uint8_t endianness) {
    unsigned long pos = thePDU->curPos;
    unsigned long remaining = thePDU->remaining;
    if (parseINTEGRITY (&contextdata_smb2->ptr.integrity_smb2, thePDU, progname, endianness)) {
        contextdata_smb2->type = INTEGRITY_SMB2_VAL;
        return true;
    }
    thePDU->curPos = pos;
    thePDU->remaining = remaining;
    if (parseENCRYPTION (&contextdata_smb2->ptr.encryption_smb2, thePDU, progname, endianness)) {
        contextdata_smb2->type = ENCRYPTION_SMB2_VAL;
        return true;
    }
    return false;
}

bool parseINTEGRITY (INTEGRITY_SMB2 *integrity_smb2, PDUP *thePDU, char *progname, uint8_t endianness) {
    fprintf (stderr, "%*sParse INTEGRITY\n", indent, "");
    indent += 2;
    if (!lengthRemaining (thePDU, 4, progname)) {
        return false;
    }
    integrity_smb2->hashalg = NULL;
    integrity_smb2->salt = NULL;
    integrity_smb2->hashalgcnt = get16_e (thePDU, endianness);
    fprintf (stderr, "%*shashAlgCnt: %04x \n", indent, "", integrity_smb2->hashalgcnt);
    integrity_smb2->saltlength = get16_e (thePDU, endianness);
    fprintf (stderr, "%*ssaltLength: %04x \n", indent, "", integrity_smb2->saltlength);
    integrity_smb2->hashalgcount = integrity_smb2->hashalgcnt;
    integrity_smb2->hashalglength = thePDU->curPos;
    integrity_smb2->hashalg = parseSetOfHASHALG (thePDU, integrity_smb2->hashalgcnt, progname, endianness);
    if (integrity_smb2->hashalg == NULL) {
        return false;
    }
    integrity_smb2->hashalglength = thePDU->curPos - integrity_smb2->hashalglength;
    if (!lengthRemaining (thePDU, integrity_smb2->saltlength, progname)) {
        return false;
    }
    integrity_smb2->salt = (unsigned char *) malloc (sizeof (unsigned char) * (integrity_smb2->saltlength));
    if (integrity_smb2->salt == NULL) {
        fprintf (stderr, "%s: internal malloc error file: %s line: %d \n", progname, __FILE__, __LINE__);
        return false;
    }
    integrity_smb2->salt_length = integrity_smb2->saltlength;
    memcpy (integrity_smb2->salt, &thePDU->data[thePDU->curPos], integrity_smb2->saltlength);
    thePDU->curPos += integrity_smb2->saltlength;
    if (integrity_smb2->salt[integrity_smb2->saltlength - 1] != '\0') {
    }
    fprintf (stderr, "%*ssalt: ", indent, "");
    for (int q = 0; q < integrity_smb2->saltlength; q++) {
        fprintf (stderr, "%02x ", integrity_smb2->salt[q]);
    }
    fprintf (stderr, "\n");
    fprintf (stderr, "%*sEND INTEGRITY\n", indent, "");
    indent -= 2;
    return true;
}

bool parseHASHALG (HASHALG_SMB2 *hashalg_smb2, PDUP *thePDU, char *progname, uint8_t endianness) {
    fprintf (stderr, "%*sParse HASHALG\n", indent, "");
    indent += 2;
    if (!lengthRemaining (thePDU, 2, progname)) {
        return false;
    }
    hashalg_smb2->alg = get16_e (thePDU, endianness);
    fprintf (stderr, "%*salg: %04x \n", indent, "", hashalg_smb2->alg);
    fprintf (stderr, "%*sEND HASHALG\n", indent, "");
    indent -= 2;
    return true;
}

bool parseENCRYPTION (ENCRYPTION_SMB2 *encryption_smb2, PDUP *thePDU, char *progname, uint8_t endianness) {
    fprintf (stderr, "%*sParse ENCRYPTION\n", indent, "");
    indent += 2;
    if (!lengthRemaining (thePDU, 2, progname)) {
        return false;
    }
    encryption_smb2->ciphers = NULL;
    encryption_smb2->ciphercnt = get16_e (thePDU, endianness);
    fprintf (stderr, "%*scipherCnt: %04x \n", indent, "", encryption_smb2->ciphercnt);
    encryption_smb2->cipherscount = encryption_smb2->ciphercnt;
    encryption_smb2->cipherslength = thePDU->curPos;
    encryption_smb2->ciphers = parseSetOfCIPHER (thePDU, encryption_smb2->ciphercnt, progname, endianness);
    if (encryption_smb2->ciphers == NULL) {
        return false;
    }
    encryption_smb2->cipherslength = thePDU->curPos - encryption_smb2->cipherslength;
    fprintf (stderr, "%*sEND ENCRYPTION\n", indent, "");
    indent -= 2;
    return true;
}

bool parseCIPHER (CIPHER_SMB2 *cipher_smb2, PDUP *thePDU, char *progname, uint8_t endianness) {
    fprintf (stderr, "%*sParse CIPHER\n", indent, "");
    indent += 2;
    if (!lengthRemaining (thePDU, 2, progname)) {
        return false;
    }
    cipher_smb2->cipherdata = get16_e (thePDU, endianness);
    fprintf (stderr, "%*scipherData: %04x \n", indent, "", cipher_smb2->cipherdata);
    fprintf (stderr, "%*sEND CIPHER\n", indent, "");
    indent -= 2;
    return true;
}

bool parseNEGOTIATE$RESPONSE (NEGOTIATE$RESPONSE_SMB2 *negotiate$response_smb2, PDUP *thePDU, char *progname, uint8_t endianness) {
    fprintf (stderr, "%*sParse NEGOTIATE$RESPONSE\n", indent, "");
    indent += 2;
    if (!lengthRemaining (thePDU, 64, progname)) {
        return false;
    }
    negotiate$response_smb2->buffer = NULL;
    negotiate$response_smb2->padding = NULL;
    negotiate$response_smb2->negcontextlist = NULL;
    HEADER_SMB2 header;
    if (!parseHEADER (&header, thePDU, progname, endianness)) {
        return false;
    }
    negotiate$response_smb2->header = header;
    negotiate$response_smb2->structuresize = get16_e (thePDU, endianness);
    fprintf (stderr, "%*sstructureSize: %04x \n", indent, "", negotiate$response_smb2->structuresize);
    if (!(negotiate$response_smb2->structuresize == 65)) {
        return false;
    }
    negotiate$response_smb2->securitymode = get16_e (thePDU, endianness);
    fprintf (stderr, "%*ssecurityMode: %04x \n", indent, "", negotiate$response_smb2->securitymode);
    if (!(negotiate$response_smb2->securitymode == 0x0001 ||negotiate$response_smb2->securitymode == 0x0002)) {
        return false;
    }
    negotiate$response_smb2->dialectrevision = get16_e (thePDU, endianness);
    fprintf (stderr, "%*sdialectRevision: %04x \n", indent, "", negotiate$response_smb2->dialectrevision);
    negotiate$response_smb2->negcontextcnt = get16_e (thePDU, endianness);
    fprintf (stderr, "%*snegContextCnt: %04x \n", indent, "", negotiate$response_smb2->negcontextcnt);
    memcpy (negotiate$response_smb2->serverguid, &thePDU->data[thePDU->curPos], 16);
    thePDU->curPos += 16;
    if (negotiate$response_smb2->serverguid[16 - 1] != '\0') {
    }
    fprintf (stderr, "%*sserverGuid: ", indent, "");
    for (int q = 0; q < 16; q++) {
        fprintf (stderr, "%02x ", negotiate$response_smb2->serverguid[q]);
    }
    fprintf (stderr, "\n");
    negotiate$response_smb2->capabilities = get32_e (thePDU, endianness);
    fprintf (stderr, "%*scapabilities: %08x \n", indent, "", negotiate$response_smb2->capabilities);
    negotiate$response_smb2->maxtransize = get32_e (thePDU, endianness);
    fprintf (stderr, "%*smaxTranSize: %08x \n", indent, "", negotiate$response_smb2->maxtransize);
    negotiate$response_smb2->maxreadsize = get32_e (thePDU, endianness);
    fprintf (stderr, "%*smaxReadSize: %08x \n", indent, "", negotiate$response_smb2->maxreadsize);
    negotiate$response_smb2->maxwritesize = get32_e (thePDU, endianness);
    fprintf (stderr, "%*smaxWriteSize: %08x \n", indent, "", negotiate$response_smb2->maxwritesize);
    negotiate$response_smb2->syetemtime = get64_e (thePDU, endianness);
    fprintf (stderr, "%*ssyetemTime: %016lx \n", indent, "", negotiate$response_smb2->syetemtime);
    negotiate$response_smb2->serverstarttime = get64_e (thePDU, endianness);
    fprintf (stderr, "%*sserverStartTime: %016lx \n", indent, "", negotiate$response_smb2->serverstarttime);
    negotiate$response_smb2->secbufferoffset = get16_e (thePDU, endianness);
    fprintf (stderr, "%*ssecBufferOffset: %04x \n", indent, "", negotiate$response_smb2->secbufferoffset);
    negotiate$response_smb2->secbufferlength = get16_e (thePDU, endianness);
    fprintf (stderr, "%*ssecBufferLength: %04x \n", indent, "", negotiate$response_smb2->secbufferlength);
    negotiate$response_smb2->negcontextoff = get32_e (thePDU, endianness);
    fprintf (stderr, "%*snegContextOff: %08x \n", indent, "", negotiate$response_smb2->negcontextoff);
    if (!lengthRemaining (thePDU, negotiate$response_smb2->secbufferlength, progname)) {
        return false;
    }
    negotiate$response_smb2->buffer = (unsigned char *) malloc (sizeof (unsigned char) * (negotiate$response_smb2->secbufferlength));
    if (negotiate$response_smb2->buffer == NULL) {
        fprintf (stderr, "%s: internal malloc error file: %s line: %d \n", progname, __FILE__, __LINE__);
        return false;
    }
    negotiate$response_smb2->buffer_length = negotiate$response_smb2->secbufferlength;
    memcpy (negotiate$response_smb2->buffer, &thePDU->data[thePDU->curPos], negotiate$response_smb2->secbufferlength);
    thePDU->curPos += negotiate$response_smb2->secbufferlength;
    if (negotiate$response_smb2->buffer[negotiate$response_smb2->secbufferlength - 1] != '\0') {
    }
    fprintf (stderr, "%*sbuffer: ", indent, "");
    for (int q = 0; q < negotiate$response_smb2->secbufferlength; q++) {
        fprintf (stderr, "%02x ", negotiate$response_smb2->buffer[q]);
    }
    fprintf (stderr, "\n");
    if (!lengthRemaining (thePDU, 8 - ((64 + 64 + negotiate$response_smb2->secbufferlength) % 8), progname)) {
        return false;
    }
    negotiate$response_smb2->padding = (unsigned char *) malloc (sizeof (unsigned char) * (8 - ((64 + 64 + negotiate$response_smb2->secbufferlength) % 8)));
    if (negotiate$response_smb2->padding == NULL) {
        fprintf (stderr, "%s: internal malloc error file: %s line: %d \n", progname, __FILE__, __LINE__);
        return false;
    }
    negotiate$response_smb2->padding_length = 8 - ((64 + 64 + negotiate$response_smb2->secbufferlength) % 8);
    memcpy (negotiate$response_smb2->padding, &thePDU->data[thePDU->curPos], 8 - ((64 + 64 + negotiate$response_smb2->secbufferlength) % 8));
    thePDU->curPos += 8 - ((64 + 64 + negotiate$response_smb2->secbufferlength) % 8);
    if (negotiate$response_smb2->padding[8 - ((64 + 64 + negotiate$response_smb2->secbufferlength) % 8) - 1] != '\0') {
    }
    fprintf (stderr, "%*spadding: ", indent, "");
    for (int q = 0; q < 8 - ((64 + 64 + negotiate$response_smb2->secbufferlength) % 8); q++) {
        fprintf (stderr, "%02x ", negotiate$response_smb2->padding[q]);
    }
    fprintf (stderr, "\n");
    negotiate$response_smb2->negcontextlistcount = negotiate$response_smb2->negcontextcnt;
    negotiate$response_smb2->negcontextlistlength = thePDU->curPos;
    negotiate$response_smb2->negcontextlist = parseSetOfNEGOTIATECONTEXT$RESPONSE (thePDU, negotiate$response_smb2->negcontextcnt, progname, endianness);
    if (negotiate$response_smb2->negcontextlist == NULL) {
        return false;
    }
    negotiate$response_smb2->negcontextlistlength = thePDU->curPos - negotiate$response_smb2->negcontextlistlength;
    fprintf (stderr, "%*sEND NEGOTIATE$RESPONSE\n", indent, "");
    indent -= 2;
    return true;
}

bool parseNEGOTIATECONTEXT$RESPONSE (NEGOTIATECONTEXT$RESPONSE_SMB2 *negotiatecontext$response_smb2, PDUP *thePDU, char *progname, uint8_t endianness) {
    fprintf (stderr, "%*sParse NEGOTIATECONTEXT$RESPONSE\n", indent, "");
    indent += 2;
    if (!lengthRemaining (thePDU, 8, progname)) {
        return false;
    }
    negotiatecontext$response_smb2->padding = NULL;
    negotiatecontext$response_smb2->contexttype = get16_e (thePDU, endianness);
    fprintf (stderr, "%*scontextType: %04x \n", indent, "", negotiatecontext$response_smb2->contexttype);
    if (!(negotiatecontext$response_smb2->contexttype == 0x0001 ||negotiatecontext$response_smb2->contexttype == 0x0002)) {
        return false;
    }
    negotiatecontext$response_smb2->datalength = get16_e (thePDU, endianness);
    fprintf (stderr, "%*sdataLength: %04x \n", indent, "", negotiatecontext$response_smb2->datalength);
    negotiatecontext$response_smb2->reserved = get32_e (thePDU, endianness);
    fprintf (stderr, "%*sreserved: %08x \n", indent, "", negotiatecontext$response_smb2->reserved);
    CONTEXTDATA$RESPONSE_SMB2 data;
    if (!parseCONTEXTDATA$RESPONSE (&data, thePDU, progname, endianness)) {
        return false;
    }
    negotiatecontext$response_smb2->data = data;
    if (lengthRemaining (thePDU, (8 - ((8 + negotiatecontext$response_smb2->datalength) % 8)), progname)) {
        negotiatecontext$response_smb2->padding = (unsigned char *) malloc (sizeof (unsigned char) * ((8 - ((8 + negotiatecontext$response_smb2->datalength) % 8))));
        if (negotiatecontext$response_smb2->padding == NULL) {
            fprintf (stderr, "%s: internal malloc error file: %s line: %d \n", progname, __FILE__, __LINE__);
            return false;
        }
        negotiatecontext$response_smb2->padding_length = (8 - ((8 + negotiatecontext$response_smb2->datalength) % 8));
        memcpy (negotiatecontext$response_smb2->padding, &thePDU->data[thePDU->curPos], (8 - ((8 + negotiatecontext$response_smb2->datalength) % 8)));
        thePDU->curPos += (8 - ((8 + negotiatecontext$response_smb2->datalength) % 8));
        if (negotiatecontext$response_smb2->padding[(8 - ((8 + negotiatecontext$response_smb2->datalength) % 8)) - 1] != '\0') {
        }
        fprintf (stderr, "%*spadding: ", indent, "");
        for (int q = 0; q < (8 - ((8 + negotiatecontext$response_smb2->datalength) % 8)); q++) {
            fprintf (stderr, "%02x ", negotiatecontext$response_smb2->padding[q]);
        }
        fprintf (stderr, "\n");
    }
    fprintf (stderr, "%*sEND NEGOTIATECONTEXT$RESPONSE\n", indent, "");
    indent -= 2;
    return true;
}

bool parseCONTEXTDATA$RESPONSE (CONTEXTDATA$RESPONSE_SMB2 *contextdata$response_smb2, PDUP *thePDU, char *progname, uint8_t endianness) {
    unsigned long pos = thePDU->curPos;
    unsigned long remaining = thePDU->remaining;
    if (parseINTEGRITY$RESPONSE (&contextdata$response_smb2->ptr.integrity$response_smb2, thePDU, progname, endianness)) {
        contextdata$response_smb2->type = INTEGRITY$RESPONSE_SMB2_VAL;
        return true;
    }
    thePDU->curPos = pos;
    thePDU->remaining = remaining;
    if (parseENCRYPTION$RESPONSE (&contextdata$response_smb2->ptr.encryption$response_smb2, thePDU, progname, endianness)) {
        contextdata$response_smb2->type = ENCRYPTION$RESPONSE_SMB2_VAL;
        return true;
    }
    return false;
}

bool parseINTEGRITY$RESPONSE (INTEGRITY$RESPONSE_SMB2 *integrity$response_smb2, PDUP *thePDU, char *progname, uint8_t endianness) {
    fprintf (stderr, "%*sParse INTEGRITY$RESPONSE\n", indent, "");
    indent += 2;
    if (!lengthRemaining (thePDU, 4, progname)) {
        return false;
    }
    integrity$response_smb2->hashalg = NULL;
    integrity$response_smb2->salt = NULL;
    integrity$response_smb2->hashalgcnt = get16_e (thePDU, endianness);
    fprintf (stderr, "%*shashAlgCnt: %04x \n", indent, "", integrity$response_smb2->hashalgcnt);
    if (!(integrity$response_smb2->hashalgcnt == 1)) {
        return false;
    }
    integrity$response_smb2->saltlength = get16_e (thePDU, endianness);
    fprintf (stderr, "%*ssaltLength: %04x \n", indent, "", integrity$response_smb2->saltlength);
    integrity$response_smb2->hashalgcount = integrity$response_smb2->hashalgcnt;
    integrity$response_smb2->hashalglength = thePDU->curPos;
    integrity$response_smb2->hashalg = parseSetOfHASHALG (thePDU, integrity$response_smb2->hashalgcnt, progname, endianness);
    if (integrity$response_smb2->hashalg == NULL) {
        return false;
    }
    integrity$response_smb2->hashalglength = thePDU->curPos - integrity$response_smb2->hashalglength;
    if (!lengthRemaining (thePDU, integrity$response_smb2->saltlength, progname)) {
        return false;
    }
    integrity$response_smb2->salt = (unsigned char *) malloc (sizeof (unsigned char) * (integrity$response_smb2->saltlength));
    if (integrity$response_smb2->salt == NULL) {
        fprintf (stderr, "%s: internal malloc error file: %s line: %d \n", progname, __FILE__, __LINE__);
        return false;
    }
    integrity$response_smb2->salt_length = integrity$response_smb2->saltlength;
    memcpy (integrity$response_smb2->salt, &thePDU->data[thePDU->curPos], integrity$response_smb2->saltlength);
    thePDU->curPos += integrity$response_smb2->saltlength;
    if (integrity$response_smb2->salt[integrity$response_smb2->saltlength - 1] != '\0') {
    }
    fprintf (stderr, "%*ssalt: ", indent, "");
    for (int q = 0; q < integrity$response_smb2->saltlength; q++) {
        fprintf (stderr, "%02x ", integrity$response_smb2->salt[q]);
    }
    fprintf (stderr, "\n");
    fprintf (stderr, "%*sEND INTEGRITY$RESPONSE\n", indent, "");
    indent -= 2;
    return true;
}

bool parseENCRYPTION$RESPONSE (ENCRYPTION$RESPONSE_SMB2 *encryption$response_smb2, PDUP *thePDU, char *progname, uint8_t endianness) {
    fprintf (stderr, "%*sParse ENCRYPTION$RESPONSE\n", indent, "");
    indent += 2;
    if (!lengthRemaining (thePDU, 2, progname)) {
        return false;
    }
    encryption$response_smb2->ciphers = NULL;
    encryption$response_smb2->ciphercnt = get16_e (thePDU, endianness);
    fprintf (stderr, "%*scipherCnt: %04x \n", indent, "", encryption$response_smb2->ciphercnt);
    if (!(encryption$response_smb2->ciphercnt == 1)) {
        return false;
    }
    encryption$response_smb2->cipherscount = encryption$response_smb2->ciphercnt;
    encryption$response_smb2->cipherslength = thePDU->curPos;
    encryption$response_smb2->ciphers = parseSetOfCIPHER (thePDU, encryption$response_smb2->ciphercnt, progname, endianness);
    if (encryption$response_smb2->ciphers == NULL) {
        return false;
    }
    encryption$response_smb2->cipherslength = thePDU->curPos - encryption$response_smb2->cipherslength;
    fprintf (stderr, "%*sEND ENCRYPTION$RESPONSE\n", indent, "");
    indent -= 2;
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
        if (mainpdu->ptr.negotiate_smb2.padding != NULL) {
            free (mainpdu->ptr.negotiate_smb2.padding);
            mainpdu->ptr.negotiate_smb2.padding = NULL;
        }
        if (mainpdu->ptr.negotiate_smb2.negcontextlist != NULL) {
            for (int i = 0; i < mainpdu->ptr.negotiate_smb2.negcontextlistcount; ++i) {
                if (&mainpdu->ptr.negotiate_smb2.negcontextlist [i] != NULL) {
                    if (mainpdu->ptr.negotiate_smb2.negcontextlist [i].padding != NULL) {
                        free (mainpdu->ptr.negotiate_smb2.negcontextlist [i].padding);
                        mainpdu->ptr.negotiate_smb2.negcontextlist [i].padding = NULL;
                    }
                }
            }
            if (mainpdu->ptr.negotiate_smb2.negcontextlist != NULL) {
                free (mainpdu->ptr.negotiate_smb2.negcontextlist);
                mainpdu->ptr.negotiate_smb2.negcontextlist = NULL;
            }
        }
    }
}

DIALECT_SMB2 *parseSetOfDIALECT (PDUP *thePDU, int size, char *progname, uint8_t endianness) {
    DIALECT_SMB2 *result = (DIALECT_SMB2 *) malloc (size *sizeof(DIALECT_SMB2));
    if (result == NULL) {
        return NULL;
    }
    for (int i = 0; i < size; ++i) {
        DIALECT_SMB2 dialects;
        if (parseDIALECT (&dialects, thePDU, progname, endianness))
            result[i] = dialects;
        else
            return NULL;
    }
    return result;
}

NEGOTIATECONTEXT_SMB2 *parseSetOfNEGOTIATECONTEXT (PDUP *thePDU, int size, char *progname, uint8_t endianness) {
    NEGOTIATECONTEXT_SMB2 *result = (NEGOTIATECONTEXT_SMB2 *) malloc (size *sizeof(NEGOTIATECONTEXT_SMB2));
    if (result == NULL) {
        return NULL;
    }
    for (int i = 0; i < size; ++i) {
        NEGOTIATECONTEXT_SMB2 negcontextlist;
        if (parseNEGOTIATECONTEXT (&negcontextlist, thePDU, progname, endianness))
            result[i] = negcontextlist;
        else
            return NULL;
    }
    return result;
}

NEGOTIATECONTEXT$RESPONSE_SMB2 *parseSetOfNEGOTIATECONTEXT$RESPONSE (PDUP *thePDU, int size, char *progname, uint8_t endianness) {
    NEGOTIATECONTEXT$RESPONSE_SMB2 *result = (NEGOTIATECONTEXT$RESPONSE_SMB2 *) malloc (size *sizeof(NEGOTIATECONTEXT$RESPONSE_SMB2));
    if (result == NULL) {
        return NULL;
    }
    for (int i = 0; i < size; ++i) {
        NEGOTIATECONTEXT$RESPONSE_SMB2 negcontextlist;
        if (parseNEGOTIATECONTEXT$RESPONSE (&negcontextlist, thePDU, progname, endianness))
            result[i] = negcontextlist;
        else
            return NULL;
    }
    return result;
}

HASHALG_SMB2 *parseSetOfHASHALG (PDUP *thePDU, int size, char *progname, uint8_t endianness) {
    HASHALG_SMB2 *result = (HASHALG_SMB2 *) malloc (size *sizeof(HASHALG_SMB2));
    if (result == NULL) {
        return NULL;
    }
    for (int i = 0; i < size; ++i) {
        HASHALG_SMB2 hashalg;
        if (parseHASHALG (&hashalg, thePDU, progname, endianness))
            result[i] = hashalg;
        else
            return NULL;
    }
    return result;
}

CIPHER_SMB2 *parseSetOfCIPHER (PDUP *thePDU, int size, char *progname, uint8_t endianness) {
    CIPHER_SMB2 *result = (CIPHER_SMB2 *) malloc (size *sizeof(CIPHER_SMB2));
    if (result == NULL) {
        return NULL;
    }
    for (int i = 0; i < size; ++i) {
        CIPHER_SMB2 ciphers;
        if (parseCIPHER (&ciphers, thePDU, progname, endianness))
            result[i] = ciphers;
        else
            return NULL;
    }
    return result;
}

