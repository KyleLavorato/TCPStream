#define BIGENDIAN (0x0)
#define LITTLEENDIAN (0x1)
#include "IGMP_Generated.h"
#include "pglobals.h"
#include "putilities.h"
void freePDU_IGMP (PDU_IGMP *mainpdu);
bool parseIGMP (PDU_IGMP *pdu_igmp, PDU *thePDU, char *progname, uint8_t endianness);
bool parseQuery (Query_IGMP *query_igmp, PDU *thePDU, char *progname, uint8_t endianness);
bool parseQuery_O (Query_IGMP *query_igmp, PDU *thePDU, char *progname, uint8_t *type, uint8_t endianness);
bool parseV3Addition (V3Addition_IGMP *v3addition_igmp, PDU *thePDU, char *progname, uint8_t endianness);
bool parseV2Report (V2Report_IGMP *v2report_igmp, PDU *thePDU, char *progname, uint8_t endianness);
bool parseV2Report_O (V2Report_IGMP *v2report_igmp, PDU *thePDU, char *progname, uint8_t *type, uint8_t endianness);
bool parseV2Leave (V2Leave_IGMP *v2leave_igmp, PDU *thePDU, char *progname, uint8_t endianness);
bool parseV2Leave_O (V2Leave_IGMP *v2leave_igmp, PDU *thePDU, char *progname, uint8_t *type, uint8_t endianness);
bool parseV3Report (V3Report_IGMP *v3report_igmp, PDU *thePDU, char *progname, uint8_t endianness);
bool parseV3Report_O (V3Report_IGMP *v3report_igmp, PDU *thePDU, char *progname, uint8_t *type, uint8_t endianness);
GROUPRECORD_IGMP *parseSetOfGROUPRECORD (PDU *thePDU, int size, char *progname, uint8_t endianness);
bool parseGROUPRECORD (GROUPRECORD_IGMP *grouprecord_igmp, PDU *thePDU, char *progname, uint8_t endianness);
SOURCEADDRESS_IGMP *parseSetOfSOURCEADDRESS (PDU *thePDU, int size, char *progname, uint8_t endianness);
bool parseSOURCEADDRESS (SOURCEADDRESS_IGMP *sourceaddress_igmp, PDU *thePDU, char *progname, uint8_t endianness);

bool parseIGMP (PDU_IGMP *pdu_igmp, PDU *thePDU, char *progname, uint8_t endianness) {
    if (!lengthRemaining (thePDU, 1, progname)) {
        return false;
    }
    uint8_t type = get8_e (thePDU, endianness);
    switch (type) {
    case 34 :
        if (parseV3Report_O (&pdu_igmp->ptr.v3report_igmp, thePDU, progname, &type, endianness)) {
            pdu_igmp->type = V3Report_IGMP_VAL;
            V3Report_IGMP_callback (&pdu_igmp->ptr.v3report_igmp, thePDU);
        }
        else {
            return false;
        }
        break;
    case 17 :
        if (parseQuery_O (&pdu_igmp->ptr.query_igmp, thePDU, progname, &type, endianness)) {
            pdu_igmp->type = Query_IGMP_VAL;
            Query_IGMP_callback (&pdu_igmp->ptr.query_igmp, thePDU);
        }
        else {
            return false;
        }
        break;
    case 22 :
        if (parseV2Report_O (&pdu_igmp->ptr.v2report_igmp, thePDU, progname, &type, endianness)) {
            pdu_igmp->type = V2Report_IGMP_VAL;
            V2Report_IGMP_callback (&pdu_igmp->ptr.v2report_igmp, thePDU);
        }
        else {
            return false;
        }
        break;
    case 23 :
        if (parseV2Leave_O (&pdu_igmp->ptr.v2leave_igmp, thePDU, progname, &type, endianness)) {
            pdu_igmp->type = V2Leave_IGMP_VAL;
            V2Leave_IGMP_callback (&pdu_igmp->ptr.v2leave_igmp, thePDU);
        }
        else {
            return false;
        }
        break;
    default :
        return false;
    }
    return true;
}

bool parseQuery (Query_IGMP *query_igmp, PDU *thePDU, char *progname, uint8_t endianness) {
    if (!lengthRemaining (thePDU, 8, progname)) {
        return false;
    }
    query_igmp->v3add = NULL;
    query_igmp->type = get8_e (thePDU, endianness);
    if (!(query_igmp->type == 17)) {
        return false;
    }
    query_igmp->maxresptime = get8_e (thePDU, endianness);
    query_igmp->checksum = get16_e (thePDU, endianness);
    query_igmp->groupaddr = get32_e (thePDU, endianness);
    if (thePDU->remaining) {
        query_igmp->v3add = (V3Addition_IGMP *) malloc (sizeof (V3Addition_IGMP));
        if (query_igmp->v3add == NULL) {
            return false;
        }
        if (!parseV3Addition (query_igmp->v3add, thePDU, progname, endianness)) {
            free (query_igmp->v3add);
            query_igmp->v3add = NULL;
            return false;
        }
    }
    else {
        query_igmp->v3add = NULL;
    }
    return true;
}

bool parseQuery_O (Query_IGMP *query_igmp, PDU *thePDU, char *progname, uint8_t *type, uint8_t endianness) {
    query_igmp->type = *type;
    if (!lengthRemaining (thePDU, 7, progname)) {
        return false;
    }
    query_igmp->v3add = NULL;
    query_igmp->maxresptime = get8_e (thePDU, endianness);
    query_igmp->checksum = get16_e (thePDU, endianness);
    query_igmp->groupaddr = get32_e (thePDU, endianness);
    if (thePDU->remaining) {
        query_igmp->v3add = (V3Addition_IGMP *) malloc (sizeof (V3Addition_IGMP));
        if (query_igmp->v3add == NULL) {
            return false;
        }
        if (!parseV3Addition (query_igmp->v3add, thePDU, progname, endianness)) {
            free (query_igmp->v3add);
            query_igmp->v3add = NULL;
            return false;
        }
    }
    else {
        query_igmp->v3add = NULL;
    }
    return true;
}

bool parseV3Addition (V3Addition_IGMP *v3addition_igmp, PDU *thePDU, char *progname, uint8_t endianness) {
    if (!lengthRemaining (thePDU, 4, progname)) {
        return false;
    }
    v3addition_igmp->srcaddrs = NULL;
    v3addition_igmp->resvsqrv = get8_e (thePDU, endianness);
    v3addition_igmp->qqic = get8_e (thePDU, endianness);
    v3addition_igmp->numsources = get16_e (thePDU, endianness);
    v3addition_igmp->srcaddrscount = v3addition_igmp->numsources;
    v3addition_igmp->srcaddrslength = thePDU->curPos;
    v3addition_igmp->srcaddrs = parseSetOfSOURCEADDRESS (thePDU, v3addition_igmp->numsources, progname, endianness);
    if (v3addition_igmp->srcaddrs == NULL) {
        return false;
    }
    v3addition_igmp->srcaddrslength = thePDU->curPos - v3addition_igmp->srcaddrslength;
    return true;
}

bool parseV2Report (V2Report_IGMP *v2report_igmp, PDU *thePDU, char *progname, uint8_t endianness) {
    if (!lengthRemaining (thePDU, 8, progname)) {
        return false;
    }
    v2report_igmp->type = get8_e (thePDU, endianness);
    if (!(v2report_igmp->type == 22)) {
        return false;
    }
    v2report_igmp->maxresptime = get8_e (thePDU, endianness);
    v2report_igmp->checksum = get16_e (thePDU, endianness);
    v2report_igmp->groupaddr = get32_e (thePDU, endianness);
    return true;
}

bool parseV2Report_O (V2Report_IGMP *v2report_igmp, PDU *thePDU, char *progname, uint8_t *type, uint8_t endianness) {
    v2report_igmp->type = *type;
    if (!lengthRemaining (thePDU, 7, progname)) {
        return false;
    }
    v2report_igmp->maxresptime = get8_e (thePDU, endianness);
    v2report_igmp->checksum = get16_e (thePDU, endianness);
    v2report_igmp->groupaddr = get32_e (thePDU, endianness);
    return true;
}

bool parseV2Leave (V2Leave_IGMP *v2leave_igmp, PDU *thePDU, char *progname, uint8_t endianness) {
    if (!lengthRemaining (thePDU, 8, progname)) {
        return false;
    }
    v2leave_igmp->type = get8_e (thePDU, endianness);
    if (!(v2leave_igmp->type == 23)) {
        return false;
    }
    v2leave_igmp->maxresptime = get8_e (thePDU, endianness);
    v2leave_igmp->checksum = get16_e (thePDU, endianness);
    v2leave_igmp->groupaddr = get32_e (thePDU, endianness);
    return true;
}

bool parseV2Leave_O (V2Leave_IGMP *v2leave_igmp, PDU *thePDU, char *progname, uint8_t *type, uint8_t endianness) {
    v2leave_igmp->type = *type;
    if (!lengthRemaining (thePDU, 7, progname)) {
        return false;
    }
    v2leave_igmp->maxresptime = get8_e (thePDU, endianness);
    v2leave_igmp->checksum = get16_e (thePDU, endianness);
    v2leave_igmp->groupaddr = get32_e (thePDU, endianness);
    return true;
}

bool parseV3Report (V3Report_IGMP *v3report_igmp, PDU *thePDU, char *progname, uint8_t endianness) {
    if (!lengthRemaining (thePDU, 8, progname)) {
        return false;
    }
    v3report_igmp->grouprecordinfo = NULL;
    v3report_igmp->type = get8_e (thePDU, endianness);
    if (!(v3report_igmp->type == 34)) {
        return false;
    }
    v3report_igmp->reserved = get8_e (thePDU, endianness);
    v3report_igmp->checksum = get16_e (thePDU, endianness);
    v3report_igmp->secondreserved = get16_e (thePDU, endianness);
    v3report_igmp->numgrps = get16_e (thePDU, endianness);
    v3report_igmp->grouprecordinfocount = v3report_igmp->numgrps;
    v3report_igmp->grouprecordinfolength = thePDU->curPos;
    v3report_igmp->grouprecordinfo = parseSetOfGROUPRECORD (thePDU, v3report_igmp->numgrps, progname, endianness);
    if (v3report_igmp->grouprecordinfo == NULL) {
        return false;
    }
    v3report_igmp->grouprecordinfolength = thePDU->curPos - v3report_igmp->grouprecordinfolength;
    return true;
}

bool parseV3Report_O (V3Report_IGMP *v3report_igmp, PDU *thePDU, char *progname, uint8_t *type, uint8_t endianness) {
    v3report_igmp->type = *type;
    if (!lengthRemaining (thePDU, 7, progname)) {
        return false;
    }
    v3report_igmp->grouprecordinfo = NULL;
    v3report_igmp->reserved = get8_e (thePDU, endianness);
    v3report_igmp->checksum = get16_e (thePDU, endianness);
    v3report_igmp->secondreserved = get16_e (thePDU, endianness);
    v3report_igmp->numgrps = get16_e (thePDU, endianness);
    v3report_igmp->grouprecordinfocount = v3report_igmp->numgrps;
    v3report_igmp->grouprecordinfolength = thePDU->curPos;
    v3report_igmp->grouprecordinfo = parseSetOfGROUPRECORD (thePDU, v3report_igmp->numgrps, progname, endianness);
    if (v3report_igmp->grouprecordinfo == NULL) {
        return false;
    }
    v3report_igmp->grouprecordinfolength = thePDU->curPos - v3report_igmp->grouprecordinfolength;
    return true;
}

bool parseGROUPRECORD (GROUPRECORD_IGMP *grouprecord_igmp, PDU *thePDU, char *progname, uint8_t endianness) {
    if (!lengthRemaining (thePDU, 8, progname)) {
        return false;
    }
    grouprecord_igmp->srcaddrs = NULL;
    grouprecord_igmp->recordtype = get8_e (thePDU, endianness);
    grouprecord_igmp->auxdatalen = get8_e (thePDU, endianness);
    grouprecord_igmp->numsources = get16_e (thePDU, endianness);
    grouprecord_igmp->groupaddr = get32_e (thePDU, endianness);
    grouprecord_igmp->srcaddrscount = grouprecord_igmp->numsources;
    grouprecord_igmp->srcaddrslength = thePDU->curPos;
    grouprecord_igmp->srcaddrs = parseSetOfSOURCEADDRESS (thePDU, grouprecord_igmp->numsources, progname, endianness);
    if (grouprecord_igmp->srcaddrs == NULL) {
        return false;
    }
    grouprecord_igmp->srcaddrslength = thePDU->curPos - grouprecord_igmp->srcaddrslength;
    return true;
}

bool parseSOURCEADDRESS (SOURCEADDRESS_IGMP *sourceaddress_igmp, PDU *thePDU, char *progname, uint8_t endianness) {
    if (!lengthRemaining (thePDU, 4, progname)) {
        return false;
    }
    sourceaddress_igmp->srcaddr = get32_e (thePDU, endianness);
    return true;
}

void freePDU_IGMP (PDU_IGMP *mainpdu) {
    if (mainpdu->type == Query_IGMP_VAL) {
        if (mainpdu->ptr.query_igmp.v3add != NULL) {
            if (mainpdu->ptr.query_igmp.v3add->srcaddrs != NULL) {
                for (int i = 0; i < mainpdu->ptr.query_igmp.v3add->srcaddrscount; ++i) {
                    if (&mainpdu->ptr.query_igmp.v3add->srcaddrs [i] != NULL) {
                    }
                }
                if (mainpdu->ptr.query_igmp.v3add->srcaddrs != NULL) {
                    free (mainpdu->ptr.query_igmp.v3add->srcaddrs);
                    mainpdu->ptr.query_igmp.v3add->srcaddrs = NULL;
                }
            }
        }
        if (mainpdu->ptr.query_igmp.v3add != NULL) {
            free (mainpdu->ptr.query_igmp.v3add);
            mainpdu->ptr.query_igmp.v3add = NULL;
        }
    }
    if (mainpdu->type == V2Report_IGMP_VAL) {
    }
    if (mainpdu->type == V2Leave_IGMP_VAL) {
    }
    if (mainpdu->type == V3Report_IGMP_VAL) {
        if (mainpdu->ptr.v3report_igmp.grouprecordinfo != NULL) {
            for (int i = 0; i < mainpdu->ptr.v3report_igmp.grouprecordinfocount; ++i) {
                if (&mainpdu->ptr.v3report_igmp.grouprecordinfo [i] != NULL) {
                    if (mainpdu->ptr.v3report_igmp.grouprecordinfo [i].srcaddrs != NULL) {
                        for (int j = 0; j < mainpdu->ptr.v3report_igmp.grouprecordinfo [i].srcaddrscount; ++j) {
                            if (&mainpdu->ptr.v3report_igmp.grouprecordinfo [i].srcaddrs [j] != NULL) {
                            }
                        }
                        if (mainpdu->ptr.v3report_igmp.grouprecordinfo [i].srcaddrs != NULL) {
                            free (mainpdu->ptr.v3report_igmp.grouprecordinfo [i].srcaddrs);
                            mainpdu->ptr.v3report_igmp.grouprecordinfo [i].srcaddrs = NULL;
                        }
                    }
                }
            }
            if (mainpdu->ptr.v3report_igmp.grouprecordinfo != NULL) {
                free (mainpdu->ptr.v3report_igmp.grouprecordinfo);
                mainpdu->ptr.v3report_igmp.grouprecordinfo = NULL;
            }
        }
    }
}

GROUPRECORD_IGMP *parseSetOfGROUPRECORD (PDU *thePDU, int size, char *progname, uint8_t endianness) {
    GROUPRECORD_IGMP *result = (GROUPRECORD_IGMP *) malloc (size *sizeof(GROUPRECORD_IGMP));
    if (result == NULL) {
        return NULL;
    }
    for (int i = 0; i < size; ++i) {
        GROUPRECORD_IGMP grouprecordinfo;
        if (parseGROUPRECORD (&grouprecordinfo, thePDU, progname, endianness))
            result[i] = grouprecordinfo;
        else
            return NULL;
    }
    return result;
}

SOURCEADDRESS_IGMP *parseSetOfSOURCEADDRESS (PDU *thePDU, int size, char *progname, uint8_t endianness) {
    SOURCEADDRESS_IGMP *result = (SOURCEADDRESS_IGMP *) malloc (size *sizeof(SOURCEADDRESS_IGMP));
    if (result == NULL) {
        return NULL;
    }
    for (int i = 0; i < size; ++i) {
        SOURCEADDRESS_IGMP srcaddrs;
        if (parseSOURCEADDRESS (&srcaddrs, thePDU, progname, endianness))
            result[i] = srcaddrs;
        else
            return NULL;
    }
    return result;
}

