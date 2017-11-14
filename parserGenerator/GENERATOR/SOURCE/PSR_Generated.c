#define BIGENDIAN (0x0)
#define LITTLEENDIAN (0x1)
#include "PSR_Generated.h"
#include "pglobals.h"
#include "putilities.h"
bool parsePSRPositionType (PSRPositionType_PSR *psrpositiontype_psr, PDU *thePDU, char *progname, uint8_t endianness);
extern int AppDat;

bool parsePSRPositionType (PSRPositionType_PSR *psrpositiontype_psr, PDU *thePDU, char *progname, uint8_t endianness) {
    if (AppDat != 2) {
        return false;
    }
    if (!lengthRemaining (thePDU, 60, progname)) {
        return false;
    }
    psrpositiontype_psr->radar$id = get32_e (thePDU, endianness);
    psrpositiontype_psr->target$id = get32_e (thePDU, endianness);
    psrpositiontype_psr->azimuth = getReal8_e (thePDU, endianness);
    psrpositiontype_psr->distance = getReal8_e (thePDU, endianness);
    psrpositiontype_psr->radial$speed = getReal8_e (thePDU, endianness);
    psrpositiontype_psr->ground$speed = getReal8_e (thePDU, endianness);
    psrpositiontype_psr->timestamp = get32_e (thePDU, endianness);
    psrpositiontype_psr->radar$latitude = getReal8_e (thePDU, endianness);
    psrpositiontype_psr->radar$longitude = getReal8_e (thePDU, endianness);
    return true;
}

