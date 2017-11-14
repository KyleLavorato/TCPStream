#define BIGENDIAN (0x0)
#define LITTLEENDIAN (0x1)
#include "RTPS_Generated.h"
#include "pglobals.h"
#include "putilities.h"
void freePDU_RTPS (PDU_RTPS *mainpdu);
bool parseRTPS (PDU_RTPS *pdu_rtps, PDU *thePDU, char *progname, uint8_t endianness);
bool parseFULL (FULL_RTPS *full_rtps, PDU *thePDU, char *progname, uint8_t endianness);
SUBMESSAGE_RTPS *parseSetOfSUBMESSAGE (PDU *thePDU, int n, int *size, char *progname, uint8_t endianness);
bool parsePING (PING_RTPS *ping_rtps, PDU *thePDU, char *progname, uint8_t endianness);
bool parseHEADER (HEADER_RTPS *header_rtps, PDU *thePDU, char *progname, uint8_t endianness);
bool parseGUIDPREFIX (GUIDPREFIX_RTPS *guidprefix_rtps, PDU *thePDU, char *progname, uint8_t endianness);
bool parseSUBMESSAGE (SUBMESSAGE_RTPS *submessage_rtps, PDU *thePDU, char *progname, uint8_t endianness);
bool parseDATASUB (DATASUB_RTPS *datasub_rtps, PDU *thePDU, char *progname, uint8_t endianness);
bool parseQOSPARM (QOSPARM_RTPS *qosparm_rtps, PDU *thePDU, char *progname, uint8_t endianness);
QOSPARMS_RTPS *parseSetOfQOSPARMS_O (PDU *thePDU, int n, int *size, char *progname, uint8_t endianness);
bool parseQOSPARMS (QOSPARMS_RTPS *qosparms_rtps, PDU *thePDU, char *progname, uint8_t endianness);
bool parsePIDSTATUSINFO (PIDSTATUSINFO_RTPS *pidstatusinfo_rtps, PDU *thePDU, char *progname, uint8_t endianness);
bool parsePIDSTATUSINFO_O (PIDSTATUSINFO_RTPS *pidstatusinfo_rtps, PDU *thePDU, char *progname, uint16_t *type, uint8_t endianness);
bool parsePIDKEYHASH (PIDKEYHASH_RTPS *pidkeyhash_rtps, PDU *thePDU, char *progname, uint8_t endianness);
bool parsePIDKEYHASH_O (PIDKEYHASH_RTPS *pidkeyhash_rtps, PDU *thePDU, char *progname, uint16_t *type, uint8_t endianness);
bool parseTOPICS (TOPICS_RTPS *topics_rtps, PDU *thePDU, char *progname, uint8_t endianness);
TOPICPARMS_RTPS *parseSetOfTOPICPARMS_O (PDU *thePDU, int n, int *size, char *progname, uint8_t endianness);
bool parseDATAWSUB (DATAWSUB_RTPS *datawsub_rtps, PDU *thePDU, char *progname, uint8_t endianness);
bool parseTOPICPARMS (TOPICPARMS_RTPS *topicparms_rtps, PDU *thePDU, char *progname, uint8_t endianness);
bool parsePIDTYPEMAXSIZESERIALIZED (PIDTYPEMAXSIZESERIALIZED_RTPS *pidtypemaxsizeserialized_rtps, PDU *thePDU, char *progname, uint8_t endianness);
bool parsePIDTYPEMAXSIZESERIALIZED_O (PIDTYPEMAXSIZESERIALIZED_RTPS *pidtypemaxsizeserialized_rtps, PDU *thePDU, char *progname, uint16_t *type, uint8_t
  endianness);
bool parsePIDLIFESPAN (PIDLIFESPAN_RTPS *pidlifespan_rtps, PDU *thePDU, char *progname, uint8_t endianness);
bool parsePIDLIFESPAN_O (PIDLIFESPAN_RTPS *pidlifespan_rtps, PDU *thePDU, char *progname, uint16_t *type, uint8_t endianness);
bool parsePIDDURABILITYSERVICE (PIDDURABILITYSERVICE_RTPS *piddurabilityservice_rtps, PDU *thePDU, char *progname, uint8_t endianness);
bool parsePIDDURABILITYSERVICE_O (PIDDURABILITYSERVICE_RTPS *piddurabilityservice_rtps, PDU *thePDU, char *progname, uint16_t *type, uint8_t endianness);
bool parsePIDPERSISTENCE (PIDPERSISTENCE_RTPS *pidpersistence_rtps, PDU *thePDU, char *progname, uint8_t endianness);
bool parsePIDPERSISTENCE_O (PIDPERSISTENCE_RTPS *pidpersistence_rtps, PDU *thePDU, char *progname, uint16_t *type, uint8_t endianness);
bool parsePIDOWNERSHIPSTRENGTH (PIDOWNERSHIPSTRENGTH_RTPS *pidownershipstrength_rtps, PDU *thePDU, char *progname, uint8_t endianness);
bool parsePIDOWNERSHIPSTRENGTH_O (PIDOWNERSHIPSTRENGTH_RTPS *pidownershipstrength_rtps, PDU *thePDU, char *progname, uint16_t *type, uint8_t endianness);
bool parsePIDSENDQUEUESIZE (PIDSENDQUEUESIZE_RTPS *pidsendqueuesize_rtps, PDU *thePDU, char *progname, uint8_t endianness);
bool parsePIDSENDQUEUESIZE_O (PIDSENDQUEUESIZE_RTPS *pidsendqueuesize_rtps, PDU *thePDU, char *progname, uint16_t *type, uint8_t endianness);
bool parsePIDEXPECTSACK (PIDEXPECTSACK_RTPS *pidexpectsack_rtps, PDU *thePDU, char *progname, uint8_t endianness);
bool parsePIDEXPECTSACK_O (PIDEXPECTSACK_RTPS *pidexpectsack_rtps, PDU *thePDU, char *progname, uint16_t *type, uint8_t endianness);
bool parsePIDTYPECODE (PIDTYPECODE_RTPS *pidtypecode_rtps, PDU *thePDU, char *progname, uint8_t endianness);
bool parsePIDTYPECODE_O (PIDTYPECODE_RTPS *pidtypecode_rtps, PDU *thePDU, char *progname, uint16_t *type, uint8_t endianness);
bool parsePIDTYPEOBJECT (PIDTYPEOBJECT_RTPS *pidtypeobject_rtps, PDU *thePDU, char *progname, uint8_t endianness);
bool parsePIDTYPEOBJECT_O (PIDTYPEOBJECT_RTPS *pidtypeobject_rtps, PDU *thePDU, char *progname, uint16_t *type, uint8_t endianness);
bool parsePIDTYPECONSISTENCY (PIDTYPECONSISTENCY_RTPS *pidtypeconsistency_rtps, PDU *thePDU, char *progname, uint8_t endianness);
bool parsePIDTYPECONSISTENCY_O (PIDTYPECONSISTENCY_RTPS *pidtypeconsistency_rtps, PDU *thePDU, char *progname, uint16_t *type, uint8_t endianness);
bool parseTYPECONSISTENCYKIND (TYPECONSISTENCYKIND_RTPS *typeconsistencykind_rtps, PDU *thePDU, char *progname, uint8_t endianness);
bool parsePIDEXPECTSVIRTUALHB (PIDEXPECTSVIRTUALHB_RTPS *pidexpectsvirtualhb_rtps, PDU *thePDU, char *progname, uint8_t endianness);
bool parsePIDEXPECTSVIRTUALHB_O (PIDEXPECTSVIRTUALHB_RTPS *pidexpectsvirtualhb_rtps, PDU *thePDU, char *progname, uint16_t *type, uint8_t endianness);
bool parsePIDDISABLEPOSITIVEACKS (PIDDISABLEPOSITIVEACKS_RTPS *piddisablepositiveacks_rtps, PDU *thePDU, char *progname, uint8_t endianness);
bool parsePIDDISABLEPOSITIVEACKS_O (PIDDISABLEPOSITIVEACKS_RTPS *piddisablepositiveacks_rtps, PDU *thePDU, char *progname, uint16_t *type, uint8_t endianness);
bool parseFLAG (FLAG_RTPS *flag_rtps, PDU *thePDU, char *progname, uint8_t endianness);
bool parsePIDSERVICEKIND (PIDSERVICEKIND_RTPS *pidservicekind_rtps, PDU *thePDU, char *progname, uint8_t endianness);
bool parsePIDSERVICEKIND_O (PIDSERVICEKIND_RTPS *pidservicekind_rtps, PDU *thePDU, char *progname, uint16_t *type, uint8_t endianness);
bool parsePIDENTITYVIRTUALGUID (PIDENTITYVIRTUALGUID_RTPS *pidentityvirtualguid_rtps, PDU *thePDU, char *progname, uint8_t endianness);
bool parsePIDENTITYVIRTUALGUID_O (PIDENTITYVIRTUALGUID_RTPS *pidentityvirtualguid_rtps, PDU *thePDU, char *progname, uint16_t *type, uint8_t endianness);
bool parseVIRTUALGUID (VIRTUALGUID_RTPS *virtualguid_rtps, PDU *thePDU, char *progname, uint8_t endianness);
bool parsePIDGROUPENTITYID (PIDGROUPENTITYID_RTPS *pidgroupentityid_rtps, PDU *thePDU, char *progname, uint8_t endianness);
bool parsePIDGROUPENTITYID_O (PIDGROUPENTITYID_RTPS *pidgroupentityid_rtps, PDU *thePDU, char *progname, uint16_t *type, uint8_t endianness);
bool parsePIDLATENCYBUDGET (PIDLATENCYBUDGET_RTPS *pidlatencybudget_rtps, PDU *thePDU, char *progname, uint8_t endianness);
bool parsePIDLATENCYBUDGET_O (PIDLATENCYBUDGET_RTPS *pidlatencybudget_rtps, PDU *thePDU, char *progname, uint16_t *type, uint8_t endianness);
bool parsePIDDEADLINE (PIDDEADLINE_RTPS *piddeadline_rtps, PDU *thePDU, char *progname, uint8_t endianness);
bool parsePIDDEADLINE_O (PIDDEADLINE_RTPS *piddeadline_rtps, PDU *thePDU, char *progname, uint16_t *type, uint8_t endianness);
bool parsePIDDESTINATIONORDER (PIDDESTINATIONORDER_RTPS *piddestinationorder_rtps, PDU *thePDU, char *progname, uint8_t endianness);
bool parsePIDDESTINATIONORDER_O (PIDDESTINATIONORDER_RTPS *piddestinationorder_rtps, PDU *thePDU, char *progname, uint16_t *type, uint8_t endianness);
bool parsePIDPRESENTATION (PIDPRESENTATION_RTPS *pidpresentation_rtps, PDU *thePDU, char *progname, uint8_t endianness);
bool parsePIDPRESENTATION_O (PIDPRESENTATION_RTPS *pidpresentation_rtps, PDU *thePDU, char *progname, uint16_t *type, uint8_t endianness);
bool parsePRESENTATION (PRESENTATION_RTPS *presentation_rtps, PDU *thePDU, char *progname, uint8_t endianness);
bool parsePIDOWNERSHIP (PIDOWNERSHIP_RTPS *pidownership_rtps, PDU *thePDU, char *progname, uint8_t endianness);
bool parsePIDOWNERSHIP_O (PIDOWNERSHIP_RTPS *pidownership_rtps, PDU *thePDU, char *progname, uint16_t *type, uint8_t endianness);
bool parsePIDDIRECTCOMMUNICATION (PIDDIRECTCOMMUNICATION_RTPS *piddirectcommunication_rtps, PDU *thePDU, char *progname, uint8_t endianness);
bool parsePIDDIRECTCOMMUNICATION_O (PIDDIRECTCOMMUNICATION_RTPS *piddirectcommunication_rtps, PDU *thePDU, char *progname, uint16_t *type, uint8_t endianness);
bool parseDIRECTCOMMUNICATION (DIRECTCOMMUNICATION_RTPS *directcommunication_rtps, PDU *thePDU, char *progname, uint8_t endianness);
bool parsePIDDURABILITY (PIDDURABILITY_RTPS *piddurability_rtps, PDU *thePDU, char *progname, uint8_t endianness);
bool parsePIDDURABILITY_O (PIDDURABILITY_RTPS *piddurability_rtps, PDU *thePDU, char *progname, uint16_t *type, uint8_t endianness);
bool parsePIDLIVELINESS (PIDLIVELINESS_RTPS *pidliveliness_rtps, PDU *thePDU, char *progname, uint8_t endianness);
bool parsePIDLIVELINESS_O (PIDLIVELINESS_RTPS *pidliveliness_rtps, PDU *thePDU, char *progname, uint16_t *type, uint8_t endianness);
bool parsePIDTIMEBASEDFILTER (PIDTIMEBASEDFILTER_RTPS *pidtimebasedfilter_rtps, PDU *thePDU, char *progname, uint8_t endianness);
bool parsePIDTIMEBASEDFILTER_O (PIDTIMEBASEDFILTER_RTPS *pidtimebasedfilter_rtps, PDU *thePDU, char *progname, uint16_t *type, uint8_t endianness);
bool parsePIDRECVQUEUE (PIDRECVQUEUE_RTPS *pidrecvqueue_rtps, PDU *thePDU, char *progname, uint8_t endianness);
bool parsePIDRECVQUEUE_O (PIDRECVQUEUE_RTPS *pidrecvqueue_rtps, PDU *thePDU, char *progname, uint16_t *type, uint8_t endianness);
bool parsePIDACKKIND (PIDACKKIND_RTPS *pidackkind_rtps, PDU *thePDU, char *progname, uint8_t endianness);
bool parsePIDACKKIND_O (PIDACKKIND_RTPS *pidackkind_rtps, PDU *thePDU, char *progname, uint16_t *type, uint8_t endianness);
bool parsePIDTOPICNAME (PIDTOPICNAME_RTPS *pidtopicname_rtps, PDU *thePDU, char *progname, uint8_t endianness);
bool parsePIDTOPICNAME_O (PIDTOPICNAME_RTPS *pidtopicname_rtps, PDU *thePDU, char *progname, uint16_t *type, uint8_t endianness);
bool parsePIDUNKNOWN (PIDUNKNOWN_RTPS *pidunknown_rtps, PDU *thePDU, char *progname, uint8_t endianness);
bool parsePIDUNKNOWN_O (PIDUNKNOWN_RTPS *pidunknown_rtps, PDU *thePDU, char *progname, uint16_t *type, uint8_t endianness);
bool parsePIDTYPENAME (PIDTYPENAME_RTPS *pidtypename_rtps, PDU *thePDU, char *progname, uint8_t endianness);
bool parsePIDTYPENAME_O (PIDTYPENAME_RTPS *pidtypename_rtps, PDU *thePDU, char *progname, uint16_t *type, uint8_t endianness);
bool parseNESTEDSTRING (NESTEDSTRING_RTPS *nestedstring_rtps, PDU *thePDU, char *progname, uint8_t endianness);
bool parsePIDRELIABILITY (PIDRELIABILITY_RTPS *pidreliability_rtps, PDU *thePDU, char *progname, uint8_t endianness);
bool parsePIDRELIABILITY_O (PIDRELIABILITY_RTPS *pidreliability_rtps, PDU *thePDU, char *progname, uint16_t *type, uint8_t endianness);
bool parsePIDENDPOINTGUID (PIDENDPOINTGUID_RTPS *pidendpointguid_rtps, PDU *thePDU, char *progname, uint8_t endianness);
bool parsePIDENDPOINTGUID_O (PIDENDPOINTGUID_RTPS *pidendpointguid_rtps, PDU *thePDU, char *progname, uint16_t *type, uint8_t endianness);
bool parsePIDMULTICASTLOCATOR (PIDMULTICASTLOCATOR_RTPS *pidmulticastlocator_rtps, PDU *thePDU, char *progname, uint8_t endianness);
bool parsePIDMULTICASTLOCATOR_O (PIDMULTICASTLOCATOR_RTPS *pidmulticastlocator_rtps, PDU *thePDU, char *progname, uint16_t *type, uint8_t endianness);
bool parsePIDUNICASTLOCATOR (PIDUNICASTLOCATOR_RTPS *pidunicastlocator_rtps, PDU *thePDU, char *progname, uint8_t endianness);
bool parsePIDUNICASTLOCATOR_O (PIDUNICASTLOCATOR_RTPS *pidunicastlocator_rtps, PDU *thePDU, char *progname, uint16_t *type, uint8_t endianness);
bool parsePARTICIPANTS (PARTICIPANTS_RTPS *participants_rtps, PDU *thePDU, char *progname, uint8_t endianness);
PARTICIPANTPARAMS_RTPS *parseSetOfPARTICIPANTPARAMS_O (PDU *thePDU, int n, int *size, char *progname, uint8_t endianness);
bool parseDATAPSUB (DATAPSUB_RTPS *datapsub_rtps, PDU *thePDU, char *progname, uint8_t endianness);
bool parseDATARSUB (DATARSUB_RTPS *datarsub_rtps, PDU *thePDU, char *progname, uint8_t endianness);
bool parseINFO$DST (INFO$DST_RTPS *info$dst_rtps, PDU *thePDU, char *progname, uint8_t endianness);
bool parseINFO$TS (INFO$TS_RTPS *info$ts_rtps, PDU *thePDU, char *progname, uint8_t endianness);
bool parseACKNACK (ACKNACK_RTPS *acknack_rtps, PDU *thePDU, char *progname, uint8_t endianness);
bool parseHEARTBEAT (HEARTBEAT_RTPS *heartbeat_rtps, PDU *thePDU, char *progname, uint8_t endianness);
bool parseGAP (GAP_RTPS *gap_rtps, PDU *thePDU, char *progname, uint8_t endianness);
bool parsePARTICIPANTPARAMS (PARTICIPANTPARAMS_RTPS *participantparams_rtps, PDU *thePDU, char *progname, uint8_t endianness);
bool parsePIDPRODUCTVERSION (PIDPRODUCTVERSION_RTPS *pidproductversion_rtps, PDU *thePDU, char *progname, uint8_t endianness);
bool parsePIDPRODUCTVERSION_O (PIDPRODUCTVERSION_RTPS *pidproductversion_rtps, PDU *thePDU, char *progname, uint16_t *type, uint8_t endianness);
bool parsePRODUCTVERSION (PRODUCTVERSION_RTPS *productversion_rtps, PDU *thePDU, char *progname, uint8_t endianness);
bool parsePIDTRANSPORTINFOLIST (PIDTRANSPORTINFOLIST_RTPS *pidtransportinfolist_rtps, PDU *thePDU, char *progname, uint8_t endianness);
bool parsePIDTRANSPORTINFOLIST_O (PIDTRANSPORTINFOLIST_RTPS *pidtransportinfolist_rtps, PDU *thePDU, char *progname, uint16_t *type, uint8_t endianness);
bool parseTRANSPORTS (TRANSPORTS_RTPS *transports_rtps, PDU *thePDU, char *progname, uint8_t endianness);
TRANSPORTINFO_RTPS *parseSetOfTRANSPORTINFO (PDU *thePDU, int size, char *progname, uint8_t endianness);
bool parseTRANSPORTINFO (TRANSPORTINFO_RTPS *transportinfo_rtps, PDU *thePDU, char *progname, uint8_t endianness);
bool parsePIDDOMAINID (PIDDOMAINID_RTPS *piddomainid_rtps, PDU *thePDU, char *progname, uint8_t endianness);
bool parsePIDDOMAINID_O (PIDDOMAINID_RTPS *piddomainid_rtps, PDU *thePDU, char *progname, uint16_t *type, uint8_t endianness);
bool parsePIDPEERHOSTEPOCH (PIDPEERHOSTEPOCH_RTPS *pidpeerhostepoch_rtps, PDU *thePDU, char *progname, uint8_t endianness);
bool parsePIDPEERHOSTEPOCH_O (PIDPEERHOSTEPOCH_RTPS *pidpeerhostepoch_rtps, PDU *thePDU, char *progname, uint16_t *type, uint8_t endianness);
bool parsePIDROLENAME (PIDROLENAME_RTPS *pidrolename_rtps, PDU *thePDU, char *progname, uint8_t endianness);
bool parsePIDROLENAME_O (PIDROLENAME_RTPS *pidrolename_rtps, PDU *thePDU, char *progname, uint16_t *type, uint8_t endianness);
bool parsePIDENTITYNAME (PIDENTITYNAME_RTPS *pidentityname_rtps, PDU *thePDU, char *progname, uint8_t endianness);
bool parsePIDENTITYNAME_O (PIDENTITYNAME_RTPS *pidentityname_rtps, PDU *thePDU, char *progname, uint16_t *type, uint8_t endianness);
bool parsePIDPROPERTYLIST (PIDPROPERTYLIST_RTPS *pidpropertylist_rtps, PDU *thePDU, char *progname, uint8_t endianness);
bool parsePIDPROPERTYLIST_O (PIDPROPERTYLIST_RTPS *pidpropertylist_rtps, PDU *thePDU, char *progname, uint16_t *type, uint8_t endianness);
bool parsePROPERTYLIST (PROPERTYLIST_RTPS *propertylist_rtps, PDU *thePDU, char *progname, uint8_t endianness);
PROPERTY_RTPS *parseSetOfPROPERTY (PDU *thePDU, int size, char *progname, uint8_t endianness);
bool parsePROPERTY (PROPERTY_RTPS *property_rtps, PDU *thePDU, char *progname, uint8_t endianness);
bool parsePIDPROTOVERSION (PIDPROTOVERSION_RTPS *pidprotoversion_rtps, PDU *thePDU, char *progname, uint8_t endianness);
bool parsePIDPROTOVERSION_O (PIDPROTOVERSION_RTPS *pidprotoversion_rtps, PDU *thePDU, char *progname, uint16_t *type, uint8_t endianness);
bool parsePROTOCOLVERSION (PROTOCOLVERSION_RTPS *protocolversion_rtps, PDU *thePDU, char *progname, uint8_t endianness);
bool parsePIDPARTICIPANTGUID (PIDPARTICIPANTGUID_RTPS *pidparticipantguid_rtps, PDU *thePDU, char *progname, uint8_t endianness);
bool parsePIDPARTICIPANTGUID_O (PIDPARTICIPANTGUID_RTPS *pidparticipantguid_rtps, PDU *thePDU, char *progname, uint16_t *type, uint8_t endianness);
bool parsePARTICIPANTGUID (PARTICIPANTGUID_RTPS *participantguid_rtps, PDU *thePDU, char *progname, uint8_t endianness);
bool parsePIDVENDORID (PIDVENDORID_RTPS *pidvendorid_rtps, PDU *thePDU, char *progname, uint8_t endianness);
bool parsePIDVENDORID_O (PIDVENDORID_RTPS *pidvendorid_rtps, PDU *thePDU, char *progname, uint16_t *type, uint8_t endianness);
bool parseVENDORID (VENDORID_RTPS *vendorid_rtps, PDU *thePDU, char *progname, uint8_t endianness);
bool parsePIDPARTICIPANTBUILTENDPOINTS (PIDPARTICIPANTBUILTENDPOINTS_RTPS *pidparticipantbuiltendpoints_rtps, PDU *thePDU, char *progname, uint8_t endianness);
bool parsePIDPARTICIPANTBUILTENDPOINTS_O (PIDPARTICIPANTBUILTENDPOINTS_RTPS *pidparticipantbuiltendpoints_rtps, PDU *thePDU, char *progname, uint16_t *type,
  uint8_t endianness);
bool parsePIDBUILTINENDPOINTSET (PIDBUILTINENDPOINTSET_RTPS *pidbuiltinendpointset_rtps, PDU *thePDU, char *progname, uint8_t endianness);
bool parsePIDBUILTINENDPOINTSET_O (PIDBUILTINENDPOINTSET_RTPS *pidbuiltinendpointset_rtps, PDU *thePDU, char *progname, uint16_t *type, uint8_t endianness);
bool parseFLAGS (FLAGS_RTPS *flags_rtps, PDU *thePDU, char *progname, uint8_t endianness);
bool parsePIDMETATRAFFICUNILOCATOR (PIDMETATRAFFICUNILOCATOR_RTPS *pidmetatrafficunilocator_rtps, PDU *thePDU, char *progname, uint8_t endianness);
bool parsePIDMETATRAFFICUNILOCATOR_O (PIDMETATRAFFICUNILOCATOR_RTPS *pidmetatrafficunilocator_rtps, PDU *thePDU, char *progname, uint16_t *type, uint8_t
  endianness);
bool parsePIDMETATRAFFICMULTILOCATOR (PIDMETATRAFFICMULTILOCATOR_RTPS *pidmetatrafficmultilocator_rtps, PDU *thePDU, char *progname, uint8_t endianness);
bool parsePIDMETATRAFFICMULTILOCATOR_O (PIDMETATRAFFICMULTILOCATOR_RTPS *pidmetatrafficmultilocator_rtps, PDU *thePDU, char *progname, uint16_t *type, uint8_t
  endianness);
bool parsePIDDEFUNILOCATOR (PIDDEFUNILOCATOR_RTPS *piddefunilocator_rtps, PDU *thePDU, char *progname, uint8_t endianness);
bool parsePIDDEFUNILOCATOR_O (PIDDEFUNILOCATOR_RTPS *piddefunilocator_rtps, PDU *thePDU, char *progname, uint16_t *type, uint8_t endianness);
bool parsePIDDEFMULTILOCATOR (PIDDEFMULTILOCATOR_RTPS *piddefmultilocator_rtps, PDU *thePDU, char *progname, uint8_t endianness);
bool parsePIDDEFMULTILOCATOR_O (PIDDEFMULTILOCATOR_RTPS *piddefmultilocator_rtps, PDU *thePDU, char *progname, uint16_t *type, uint8_t endianness);
bool parseLOCATOR (LOCATOR_RTPS *locator_rtps, PDU *thePDU, char *progname, uint8_t endianness);
bool parsePIDPARTICIPANTLIVECOUNT (PIDPARTICIPANTLIVECOUNT_RTPS *pidparticipantlivecount_rtps, PDU *thePDU, char *progname, uint8_t endianness);
bool parsePIDPARTICIPANTLIVECOUNT_O (PIDPARTICIPANTLIVECOUNT_RTPS *pidparticipantlivecount_rtps, PDU *thePDU, char *progname, uint16_t *type, uint8_t endianness
  );
bool parsePIDPARTICIPANTLEASE (PIDPARTICIPANTLEASE_RTPS *pidparticipantlease_rtps, PDU *thePDU, char *progname, uint8_t endianness);
bool parsePIDPARTICIPANTLEASE_O (PIDPARTICIPANTLEASE_RTPS *pidparticipantlease_rtps, PDU *thePDU, char *progname, uint16_t *type, uint8_t endianness);
bool parseLEASEDURATION (LEASEDURATION_RTPS *leaseduration_rtps, PDU *thePDU, char *progname, uint8_t endianness);
bool parsePIDSENTINAL (PIDSENTINAL_RTPS *pidsentinal_rtps, PDU *thePDU, char *progname, uint8_t endianness);
bool parsePIDSENTINAL_O (PIDSENTINAL_RTPS *pidsentinal_rtps, PDU *thePDU, char *progname, uint16_t *type, uint8_t endianness);
bool parseENTITYID (ENTITYID_RTPS *entityid_rtps, PDU *thePDU, char *progname, uint8_t endianness);
bool parseSNSTATE (SNSTATE_RTPS *snstate_rtps, PDU *thePDU, char *progname, uint8_t endianness);
bool parseSLACK (SLACK_RTPS *slack_rtps, PDU *thePDU, char *progname, uint8_t endianness);

bool parseRTPS (PDU_RTPS *pdu_rtps, PDU *thePDU, char *progname, uint8_t endianness) {
    unsigned long pos = thePDU->curPos;
    unsigned long remaining = thePDU->remaining;
    if (parseFULL (&pdu_rtps->ptr.full_rtps, thePDU, progname, endianness)) {
        pdu_rtps->type = FULL_RTPS_VAL;
        return true;
    }
    thePDU->curPos = pos;
    thePDU->remaining = remaining;
    if (parsePING (&pdu_rtps->ptr.ping_rtps, thePDU, progname, endianness)) {
        pdu_rtps->type = PING_RTPS_VAL;
        return true;
    }
    return false;
}

bool parseFULL (FULL_RTPS *full_rtps, PDU *thePDU, char *progname, uint8_t endianness) {
    if (!lengthRemaining (thePDU, 0, progname)) {
        return false;
    }
    full_rtps->submsg = NULL;
    HEADER_RTPS header;
    if (!parseHEADER (&header, thePDU, progname, endianness)) {
        return false;
    }
    full_rtps->header = header;
    if (!(full_rtps->header.protoname == 1381257299|| 1381257304)) {
        return false;
    }
    GUIDPREFIX_RTPS guidprefix;
    if (!parseGUIDPREFIX (&guidprefix, thePDU, progname, endianness)) {
        return false;
    }
    full_rtps->guidprefix = guidprefix;
    int size = 0;
    full_rtps->submsglength = thePDU->curPos;
    full_rtps->submsg = parseSetOfSUBMESSAGE (thePDU, 0, &size, progname, endianness);
    if (full_rtps->submsg == NULL) {
        return false;
    }
    full_rtps->submsgcount = size;
    full_rtps->submsglength = thePDU->curPos - full_rtps->submsglength;
    if (thePDU->remaining != 0) {
        return false;
    }
    FULL_RTPS_callback (full_rtps, thePDU);
    return true;
}

bool parsePING (PING_RTPS *ping_rtps, PDU *thePDU, char *progname, uint8_t endianness) {
    if (!lengthRemaining (thePDU, 8, progname)) {
        return false;
    }
    HEADER_RTPS header;
    if (!parseHEADER (&header, thePDU, progname, endianness)) {
        return false;
    }
    ping_rtps->header = header;
    if (!(ping_rtps->header.protoname == 1381257299|| 1381257304)) {
        return false;
    }
    ping_rtps->ping = get64_e (thePDU, endianness);
    if (!(ping_rtps->ping == 5639707757994659399)) {
        return false;
    }
    return true;
}

bool parseHEADER (HEADER_RTPS *header_rtps, PDU *thePDU, char *progname, uint8_t endianness) {
    if (!lengthRemaining (thePDU, 8, progname)) {
        return false;
    }
    header_rtps->protoname = get32_e (thePDU, endianness);
    header_rtps->version = get16_e (thePDU, endianness);
    header_rtps->vendorid = get16_e (thePDU, endianness);
    return true;
}

bool parseGUIDPREFIX (GUIDPREFIX_RTPS *guidprefix_rtps, PDU *thePDU, char *progname, uint8_t endianness) {
    if (!lengthRemaining (thePDU, 12, progname)) {
        return false;
    }
    guidprefix_rtps->hostid = get32_e (thePDU, endianness);
    guidprefix_rtps->appid = get32_e (thePDU, endianness);
    guidprefix_rtps->counter = get32_e (thePDU, endianness);
    return true;
}

bool parseSUBMESSAGE (SUBMESSAGE_RTPS *submessage_rtps, PDU *thePDU, char *progname, uint8_t endianness) {
    unsigned long pos = thePDU->curPos;
    unsigned long remaining = thePDU->remaining;
    if (parseDATAPSUB (&submessage_rtps->ptr.datapsub_rtps, thePDU, progname, endianness)) {
        submessage_rtps->type = DATAPSUB_RTPS_VAL;
        return true;
    }
    thePDU->curPos = pos;
    thePDU->remaining = remaining;
    if (parseDATASUB (&submessage_rtps->ptr.datasub_rtps, thePDU, progname, endianness)) {
        submessage_rtps->type = DATASUB_RTPS_VAL;
        return true;
    }
    thePDU->curPos = pos;
    thePDU->remaining = remaining;
    if (parseACKNACK (&submessage_rtps->ptr.acknack_rtps, thePDU, progname, endianness)) {
        submessage_rtps->type = ACKNACK_RTPS_VAL;
        return true;
    }
    thePDU->curPos = pos;
    thePDU->remaining = remaining;
    if (parseHEARTBEAT (&submessage_rtps->ptr.heartbeat_rtps, thePDU, progname, endianness)) {
        submessage_rtps->type = HEARTBEAT_RTPS_VAL;
        return true;
    }
    thePDU->curPos = pos;
    thePDU->remaining = remaining;
    if (parseINFO$DST (&submessage_rtps->ptr.info$dst_rtps, thePDU, progname, endianness)) {
        submessage_rtps->type = INFO$DST_RTPS_VAL;
        return true;
    }
    thePDU->curPos = pos;
    thePDU->remaining = remaining;
    if (parseINFO$TS (&submessage_rtps->ptr.info$ts_rtps, thePDU, progname, endianness)) {
        submessage_rtps->type = INFO$TS_RTPS_VAL;
        return true;
    }
    thePDU->curPos = pos;
    thePDU->remaining = remaining;
    if (parseDATAWSUB (&submessage_rtps->ptr.datawsub_rtps, thePDU, progname, endianness)) {
        submessage_rtps->type = DATAWSUB_RTPS_VAL;
        return true;
    }
    thePDU->curPos = pos;
    thePDU->remaining = remaining;
    if (parseDATARSUB (&submessage_rtps->ptr.datarsub_rtps, thePDU, progname, endianness)) {
        submessage_rtps->type = DATARSUB_RTPS_VAL;
        return true;
    }
    thePDU->curPos = pos;
    thePDU->remaining = remaining;
    if (parseGAP (&submessage_rtps->ptr.gap_rtps, thePDU, progname, endianness)) {
        submessage_rtps->type = GAP_RTPS_VAL;
        return true;
    }
    return false;
}

bool parseDATASUB (DATASUB_RTPS *datasub_rtps, PDU *thePDU, char *progname, uint8_t endianness) {
    if (!lengthRemaining (thePDU, 16, progname)) {
        return false;
    }
    datasub_rtps->inlineqos = NULL;
    datasub_rtps->kind = get8_e (thePDU, endianness);
    if (!(datasub_rtps->kind == 21)) {
        return false;
    }
    datasub_rtps->flags = get8_e (thePDU, endianness);
    endianness = datasub_rtps->flags & 1;
    datasub_rtps->nextheader = get16_e (thePDU, endianness);
    unsigned long extraflagsPOS = thePDU->curPos;
    datasub_rtps->extraflags = get16_e (thePDU, endianness);
    datasub_rtps->qosoffset = get16_e (thePDU, endianness);
    ENTITYID_RTPS readerent;
    if (!parseENTITYID (&readerent, thePDU, progname, BIGENDIAN)) {
        return false;
    }
    datasub_rtps->readerent = readerent;
    ENTITYID_RTPS writerent;
    if (!parseENTITYID (&writerent, thePDU, progname, BIGENDIAN)) {
        return false;
    }
    datasub_rtps->writerent = writerent;
    if (!(datasub_rtps->writerent.kind == 2||datasub_rtps->writerent.kind == 3)) {
        return false;
    }
    datasub_rtps->writerseq = get64_e (thePDU, endianness);
    if (datasub_rtps->flags & 2) {
        datasub_rtps->inlineqos = (QOSPARM_RTPS *) malloc (sizeof (QOSPARM_RTPS));
        if (datasub_rtps->inlineqos == NULL) {
            return false;
        }
        if (!parseQOSPARM (datasub_rtps->inlineqos, thePDU, progname, endianness)) {
            free (datasub_rtps->inlineqos);
            datasub_rtps->inlineqos = NULL;
            return false;
        }
    }
    else {
        datasub_rtps->inlineqos = NULL;
    }
    unsigned long serializeddataPOS = thePDU->curPos;
    unsigned long remaining = thePDU->remaining;
    if (!lengthRemaining (thePDU, (datasub_rtps->nextheader) ? datasub_rtps->nextheader - (serializeddataPOS - extraflagsPOS) : remaining, progname)) {
        return false;
    }
    datasub_rtps->serializeddata = (unsigned char *) malloc (sizeof (unsigned char) * ((datasub_rtps->nextheader) ? datasub_rtps->nextheader - (
      serializeddataPOS - extraflagsPOS) : remaining));
    if (datasub_rtps->serializeddata == NULL) {
        fprintf (stderr, "%s: internal malloc error file: %s line: %d \n", progname, __FILE__, __LINE__);
        return false;
    }
    datasub_rtps->serializeddata_length = (datasub_rtps->nextheader) ? datasub_rtps->nextheader - (serializeddataPOS - extraflagsPOS) : remaining;
    memcpy (datasub_rtps->serializeddata, &thePDU->data[thePDU->curPos], (datasub_rtps->nextheader) ? datasub_rtps->nextheader - (serializeddataPOS -
      extraflagsPOS) : remaining);
    thePDU->curPos += (datasub_rtps->nextheader) ? datasub_rtps->nextheader - (serializeddataPOS - extraflagsPOS) : remaining;
    if (datasub_rtps->serializeddata[(datasub_rtps->nextheader) ? datasub_rtps->nextheader - (serializeddataPOS - extraflagsPOS) : remaining - 1] != '\0') {
    }
    return true;
}

bool parseQOSPARM (QOSPARM_RTPS *qosparm_rtps, PDU *thePDU, char *progname, uint8_t endianness) {
    if (!lengthRemaining (thePDU, 0, progname)) {
        return false;
    }
    qosparm_rtps->qos = NULL;
    int size = 0;
    qosparm_rtps->qoslength = thePDU->curPos;
    qosparm_rtps->qos = parseSetOfQOSPARMS_O (thePDU, 0, &size, progname, endianness);
    if (qosparm_rtps->qos == NULL) {
        return false;
    }
    qosparm_rtps->qoscount = size;
    qosparm_rtps->qoslength = thePDU->curPos - qosparm_rtps->qoslength;
    return true;
}

bool parseQOSPARMS (QOSPARMS_RTPS *qosparms_rtps, PDU *thePDU, char *progname, uint8_t endianness) {
    if (!lengthRemaining (thePDU, 2, progname)) {
        return false;
    }
    uint16_t type = get16_e (thePDU, endianness);
    switch (type) {
    case 113 :
        if (parsePIDSTATUSINFO_O (&qosparms_rtps->ptr.pidstatusinfo_rtps, thePDU, progname, &type, endianness)) {
            qosparms_rtps->type = PIDSTATUSINFO_RTPS_VAL;
        }
        else {
            return false;
        }
        break;
    case 112 :
        if (parsePIDKEYHASH_O (&qosparms_rtps->ptr.pidkeyhash_rtps, thePDU, progname, &type, endianness)) {
            qosparms_rtps->type = PIDKEYHASH_RTPS_VAL;
        }
        else {
            return false;
        }
        break;
    case 1 :
        if (parsePIDSENTINAL_O (&qosparms_rtps->ptr.pidsentinal_rtps, thePDU, progname, &type, endianness)) {
            qosparms_rtps->type = PIDSENTINAL_RTPS_VAL;
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

bool parsePIDSTATUSINFO (PIDSTATUSINFO_RTPS *pidstatusinfo_rtps, PDU *thePDU, char *progname, uint8_t endianness) {
    if (!lengthRemaining (thePDU, 4, progname)) {
        return false;
    }
    pidstatusinfo_rtps->flags = NULL;
    pidstatusinfo_rtps->parameterkind = get16_e (thePDU, endianness);
    if (!(pidstatusinfo_rtps->parameterkind == 113)) {
        return false;
    }
    pidstatusinfo_rtps->parameterlength = get16_e (thePDU, endianness);
    unsigned long remaining = thePDU->remaining;
    if (!lengthRemaining (thePDU, pidstatusinfo_rtps->parameterlength, progname)) {
        return false;
    }
    pidstatusinfo_rtps->flags = (unsigned char *) malloc (sizeof (unsigned char) * (pidstatusinfo_rtps->parameterlength));
    if (pidstatusinfo_rtps->flags == NULL) {
        fprintf (stderr, "%s: internal malloc error file: %s line: %d \n", progname, __FILE__, __LINE__);
        return false;
    }
    pidstatusinfo_rtps->flags_length = pidstatusinfo_rtps->parameterlength;
    memcpy (pidstatusinfo_rtps->flags, &thePDU->data[thePDU->curPos], pidstatusinfo_rtps->parameterlength);
    thePDU->curPos += pidstatusinfo_rtps->parameterlength;
    if (pidstatusinfo_rtps->flags[pidstatusinfo_rtps->parameterlength - 1] != '\0') {
    }
    return true;
}

bool parsePIDSTATUSINFO_O (PIDSTATUSINFO_RTPS *pidstatusinfo_rtps, PDU *thePDU, char *progname, uint16_t *type, uint8_t endianness) {
    pidstatusinfo_rtps->parameterkind = *type;
    if (!lengthRemaining (thePDU, 2, progname)) {
        return false;
    }
    pidstatusinfo_rtps->flags = NULL;
    pidstatusinfo_rtps->parameterlength = get16_e (thePDU, endianness);
    unsigned long remaining = thePDU->remaining;
    if (!lengthRemaining (thePDU, pidstatusinfo_rtps->parameterlength, progname)) {
        return false;
    }
    pidstatusinfo_rtps->flags = (unsigned char *) malloc (sizeof (unsigned char) * (pidstatusinfo_rtps->parameterlength));
    if (pidstatusinfo_rtps->flags == NULL) {
        fprintf (stderr, "%s: internal malloc error file: %s line: %d \n", progname, __FILE__, __LINE__);
        return false;
    }
    pidstatusinfo_rtps->flags_length = pidstatusinfo_rtps->parameterlength;
    memcpy (pidstatusinfo_rtps->flags, &thePDU->data[thePDU->curPos], pidstatusinfo_rtps->parameterlength);
    thePDU->curPos += pidstatusinfo_rtps->parameterlength;
    if (pidstatusinfo_rtps->flags[pidstatusinfo_rtps->parameterlength - 1] != '\0') {
    }
    return true;
}

bool parsePIDKEYHASH (PIDKEYHASH_RTPS *pidkeyhash_rtps, PDU *thePDU, char *progname, uint8_t endianness) {
    if (!lengthRemaining (thePDU, 4, progname)) {
        return false;
    }
    pidkeyhash_rtps->guid = NULL;
    pidkeyhash_rtps->parameterkind = get16_e (thePDU, endianness);
    if (!(pidkeyhash_rtps->parameterkind == 112)) {
        return false;
    }
    pidkeyhash_rtps->parameterlength = get16_e (thePDU, endianness);
    unsigned long remaining = thePDU->remaining;
    if (!lengthRemaining (thePDU, pidkeyhash_rtps->parameterlength, progname)) {
        return false;
    }
    pidkeyhash_rtps->guid = (unsigned char *) malloc (sizeof (unsigned char) * (pidkeyhash_rtps->parameterlength));
    if (pidkeyhash_rtps->guid == NULL) {
        fprintf (stderr, "%s: internal malloc error file: %s line: %d \n", progname, __FILE__, __LINE__);
        return false;
    }
    pidkeyhash_rtps->guid_length = pidkeyhash_rtps->parameterlength;
    memcpy (pidkeyhash_rtps->guid, &thePDU->data[thePDU->curPos], pidkeyhash_rtps->parameterlength);
    thePDU->curPos += pidkeyhash_rtps->parameterlength;
    if (pidkeyhash_rtps->guid[pidkeyhash_rtps->parameterlength - 1] != '\0') {
    }
    return true;
}

bool parsePIDKEYHASH_O (PIDKEYHASH_RTPS *pidkeyhash_rtps, PDU *thePDU, char *progname, uint16_t *type, uint8_t endianness) {
    pidkeyhash_rtps->parameterkind = *type;
    if (!lengthRemaining (thePDU, 2, progname)) {
        return false;
    }
    pidkeyhash_rtps->guid = NULL;
    pidkeyhash_rtps->parameterlength = get16_e (thePDU, endianness);
    unsigned long remaining = thePDU->remaining;
    if (!lengthRemaining (thePDU, pidkeyhash_rtps->parameterlength, progname)) {
        return false;
    }
    pidkeyhash_rtps->guid = (unsigned char *) malloc (sizeof (unsigned char) * (pidkeyhash_rtps->parameterlength));
    if (pidkeyhash_rtps->guid == NULL) {
        fprintf (stderr, "%s: internal malloc error file: %s line: %d \n", progname, __FILE__, __LINE__);
        return false;
    }
    pidkeyhash_rtps->guid_length = pidkeyhash_rtps->parameterlength;
    memcpy (pidkeyhash_rtps->guid, &thePDU->data[thePDU->curPos], pidkeyhash_rtps->parameterlength);
    thePDU->curPos += pidkeyhash_rtps->parameterlength;
    if (pidkeyhash_rtps->guid[pidkeyhash_rtps->parameterlength - 1] != '\0') {
    }
    return true;
}

bool parseTOPICS (TOPICS_RTPS *topics_rtps, PDU *thePDU, char *progname, uint8_t endianness) {
    if (!lengthRemaining (thePDU, 4, progname)) {
        return false;
    }
    topics_rtps->topicdata = NULL;
    topics_rtps->encapskind = get16_e (thePDU, BIGENDIAN);
    topics_rtps->encapsopts = get16_e (thePDU, BIGENDIAN);
    int size = 0;
    topics_rtps->topicdatalength = thePDU->curPos;
    topics_rtps->topicdata = parseSetOfTOPICPARMS_O (thePDU, 0, &size, progname, endianness);
    if (topics_rtps->topicdata == NULL) {
        return false;
    }
    topics_rtps->topicdatacount = size;
    topics_rtps->topicdatalength = thePDU->curPos - topics_rtps->topicdatalength;
    return true;
}

bool parseDATAWSUB (DATAWSUB_RTPS *datawsub_rtps, PDU *thePDU, char *progname, uint8_t endianness) {
    if (!lengthRemaining (thePDU, 16, progname)) {
        return false;
    }
    datawsub_rtps->inlineqos = NULL;
    datawsub_rtps->serializeddata = NULL;
    datawsub_rtps->kind = get8_e (thePDU, endianness);
    if (!(datawsub_rtps->kind == 21)) {
        return false;
    }
    datawsub_rtps->flags = get8_e (thePDU, endianness);
    endianness = datawsub_rtps->flags & 1;
    datawsub_rtps->nextheader = get16_e (thePDU, endianness);
    datawsub_rtps->extraflags = get16_e (thePDU, endianness);
    datawsub_rtps->qosoffset = get16_e (thePDU, endianness);
    ENTITYID_RTPS readerent;
    if (!parseENTITYID (&readerent, thePDU, progname, BIGENDIAN)) {
        return false;
    }
    datawsub_rtps->readerent = readerent;
    ENTITYID_RTPS writerent;
    if (!parseENTITYID (&writerent, thePDU, progname, BIGENDIAN)) {
        return false;
    }
    datawsub_rtps->writerent = writerent;
    if (!(datawsub_rtps->writerent.key == 3)) {
        return false;
    }
    if (!(datawsub_rtps->writerent.kind == 194)) {
        return false;
    }
    datawsub_rtps->writerseq = get64_e (thePDU, endianness);
    if (datawsub_rtps->flags & 2) {
        datawsub_rtps->inlineqos = (QOSPARM_RTPS *) malloc (sizeof (QOSPARM_RTPS));
        if (datawsub_rtps->inlineqos == NULL) {
            return false;
        }
        if (!parseQOSPARM (datawsub_rtps->inlineqos, thePDU, progname, endianness)) {
            free (datawsub_rtps->inlineqos);
            datawsub_rtps->inlineqos = NULL;
            return false;
        }
    }
    else {
        datawsub_rtps->inlineqos = NULL;
    }
    if (datawsub_rtps->flags & 12) {
        datawsub_rtps->serializeddata = (TOPICS_RTPS *) malloc (sizeof (TOPICS_RTPS));
        if (datawsub_rtps->serializeddata == NULL) {
            return false;
        }
        if (!parseTOPICS (datawsub_rtps->serializeddata, thePDU, progname, endianness)) {
            free (datawsub_rtps->serializeddata);
            datawsub_rtps->serializeddata = NULL;
            return false;
        }
    }
    else {
        datawsub_rtps->serializeddata = NULL;
    }
    return true;
}

bool parseTOPICPARMS (TOPICPARMS_RTPS *topicparms_rtps, PDU *thePDU, char *progname, uint8_t endianness) {
    if (!lengthRemaining (thePDU, 2, progname)) {
        return false;
    }
    uint16_t type = get16_e (thePDU, endianness);
    switch (type) {
    case 5 :
        if (parsePIDTOPICNAME_O (&topicparms_rtps->ptr.pidtopicname_rtps, thePDU, progname, &type, endianness)) {
            topicparms_rtps->type = PIDTOPICNAME_RTPS_VAL;
        }
        else {
            return false;
        }
        break;
    case 7 :
        if (parsePIDTYPENAME_O (&topicparms_rtps->ptr.pidtypename_rtps, thePDU, progname, &type, endianness)) {
            topicparms_rtps->type = PIDTYPENAME_RTPS_VAL;
        }
        else {
            return false;
        }
        break;
    case 26 :
        if (parsePIDRELIABILITY_O (&topicparms_rtps->ptr.pidreliability_rtps, thePDU, progname, &type, endianness)) {
            topicparms_rtps->type = PIDRELIABILITY_RTPS_VAL;
        }
        else {
            return false;
        }
        break;
    case 90 :
        if (parsePIDENDPOINTGUID_O (&topicparms_rtps->ptr.pidendpointguid_rtps, thePDU, progname, &type, endianness)) {
            topicparms_rtps->type = PIDENDPOINTGUID_RTPS_VAL;
        }
        else {
            return false;
        }
        break;
    case 48 :
        if (parsePIDMULTICASTLOCATOR_O (&topicparms_rtps->ptr.pidmulticastlocator_rtps, thePDU, progname, &type, endianness)) {
            topicparms_rtps->type = PIDMULTICASTLOCATOR_RTPS_VAL;
        }
        else {
            return false;
        }
        break;
    case 47 :
        if (parsePIDUNICASTLOCATOR_O (&topicparms_rtps->ptr.pidunicastlocator_rtps, thePDU, progname, &type, endianness)) {
            topicparms_rtps->type = PIDUNICASTLOCATOR_RTPS_VAL;
        }
        else {
            return false;
        }
        break;
    case 1 :
        if (parsePIDSENTINAL_O (&topicparms_rtps->ptr.pidsentinal_rtps, thePDU, progname, &type, endianness)) {
            topicparms_rtps->type = PIDSENTINAL_RTPS_VAL;
        }
        else {
            return false;
        }
        break;
    case 45058 :
        if (parsePIDUNKNOWN_O (&topicparms_rtps->ptr.pidunknown_rtps, thePDU, progname, &type, endianness)) {
            topicparms_rtps->type = PIDUNKNOWN_RTPS_VAL;
        }
        else {
            return false;
        }
        break;
    case 32779 :
        if (parsePIDACKKIND_O (&topicparms_rtps->ptr.pidackkind_rtps, thePDU, progname, &type, endianness)) {
            topicparms_rtps->type = PIDACKKIND_RTPS_VAL;
        }
        else {
            return false;
        }
        break;
    case 24 :
        if (parsePIDRECVQUEUE_O (&topicparms_rtps->ptr.pidrecvqueue_rtps, thePDU, progname, &type, endianness)) {
            topicparms_rtps->type = PIDRECVQUEUE_RTPS_VAL;
        }
        else {
            return false;
        }
        break;
    case 4 :
        if (parsePIDTIMEBASEDFILTER_O (&topicparms_rtps->ptr.pidtimebasedfilter_rtps, thePDU, progname, &type, endianness)) {
            topicparms_rtps->type = PIDTIMEBASEDFILTER_RTPS_VAL;
        }
        else {
            return false;
        }
        break;
    case 27 :
        if (parsePIDLIVELINESS_O (&topicparms_rtps->ptr.pidliveliness_rtps, thePDU, progname, &type, endianness)) {
            topicparms_rtps->type = PIDLIVELINESS_RTPS_VAL;
        }
        else {
            return false;
        }
        break;
    case 29 :
        if (parsePIDDURABILITY_O (&topicparms_rtps->ptr.piddurability_rtps, thePDU, progname, &type, endianness)) {
            topicparms_rtps->type = PIDDURABILITY_RTPS_VAL;
        }
        else {
            return false;
        }
        break;
    case 32785 :
        if (parsePIDDIRECTCOMMUNICATION_O (&topicparms_rtps->ptr.piddirectcommunication_rtps, thePDU, progname, &type, endianness)) {
            topicparms_rtps->type = PIDDIRECTCOMMUNICATION_RTPS_VAL;
        }
        else {
            return false;
        }
        break;
    case 31 :
        if (parsePIDOWNERSHIP_O (&topicparms_rtps->ptr.pidownership_rtps, thePDU, progname, &type, endianness)) {
            topicparms_rtps->type = PIDOWNERSHIP_RTPS_VAL;
        }
        else {
            return false;
        }
        break;
    case 33 :
        if (parsePIDPRESENTATION_O (&topicparms_rtps->ptr.pidpresentation_rtps, thePDU, progname, &type, endianness)) {
            topicparms_rtps->type = PIDPRESENTATION_RTPS_VAL;
        }
        else {
            return false;
        }
        break;
    case 37 :
        if (parsePIDDESTINATIONORDER_O (&topicparms_rtps->ptr.piddestinationorder_rtps, thePDU, progname, &type, endianness)) {
            topicparms_rtps->type = PIDDESTINATIONORDER_RTPS_VAL;
        }
        else {
            return false;
        }
        break;
    case 35 :
        if (parsePIDDEADLINE_O (&topicparms_rtps->ptr.piddeadline_rtps, thePDU, progname, &type, endianness)) {
            topicparms_rtps->type = PIDDEADLINE_RTPS_VAL;
        }
        else {
            return false;
        }
        break;
    case 39 :
        if (parsePIDLATENCYBUDGET_O (&topicparms_rtps->ptr.pidlatencybudget_rtps, thePDU, progname, &type, endianness)) {
            topicparms_rtps->type = PIDLATENCYBUDGET_RTPS_VAL;
        }
        else {
            return false;
        }
        break;
    case 83 :
        if (parsePIDGROUPENTITYID_O (&topicparms_rtps->ptr.pidgroupentityid_rtps, thePDU, progname, &type, endianness)) {
            topicparms_rtps->type = PIDGROUPENTITYID_RTPS_VAL;
        }
        else {
            return false;
        }
        break;
    case 32770 :
        if (parsePIDENTITYVIRTUALGUID_O (&topicparms_rtps->ptr.pidentityvirtualguid_rtps, thePDU, progname, &type, endianness)) {
            topicparms_rtps->type = PIDENTITYVIRTUALGUID_RTPS_VAL;
        }
        else {
            return false;
        }
        break;
    case 32771 :
        if (parsePIDSERVICEKIND_O (&topicparms_rtps->ptr.pidservicekind_rtps, thePDU, progname, &type, endianness)) {
            topicparms_rtps->type = PIDSERVICEKIND_RTPS_VAL;
        }
        else {
            return false;
        }
        break;
    case 21 :
        if (parsePIDPROTOVERSION_O (&topicparms_rtps->ptr.pidprotoversion_rtps, thePDU, progname, &type, endianness)) {
            topicparms_rtps->type = PIDPROTOVERSION_RTPS_VAL;
        }
        else {
            return false;
        }
        break;
    case 32768 :
        if (parsePIDPRODUCTVERSION_O (&topicparms_rtps->ptr.pidproductversion_rtps, thePDU, progname, &type, endianness)) {
            topicparms_rtps->type = PIDPRODUCTVERSION_RTPS_VAL;
        }
        else {
            return false;
        }
        break;
    case 32773 :
        if (parsePIDDISABLEPOSITIVEACKS_O (&topicparms_rtps->ptr.piddisablepositiveacks_rtps, thePDU, progname, &type, endianness)) {
            topicparms_rtps->type = PIDDISABLEPOSITIVEACKS_RTPS_VAL;
        }
        else {
            return false;
        }
        break;
    case 32777 :
        if (parsePIDEXPECTSVIRTUALHB_O (&topicparms_rtps->ptr.pidexpectsvirtualhb_rtps, thePDU, progname, &type, endianness)) {
            topicparms_rtps->type = PIDEXPECTSVIRTUALHB_RTPS_VAL;
        }
        else {
            return false;
        }
        break;
    case 116 :
        if (parsePIDTYPECONSISTENCY_O (&topicparms_rtps->ptr.pidtypeconsistency_rtps, thePDU, progname, &type, endianness)) {
            topicparms_rtps->type = PIDTYPECONSISTENCY_RTPS_VAL;
        }
        else {
            return false;
        }
        break;
    case 114 :
        if (parsePIDTYPEOBJECT_O (&topicparms_rtps->ptr.pidtypeobject_rtps, thePDU, progname, &type, endianness)) {
            topicparms_rtps->type = PIDTYPEOBJECT_RTPS_VAL;
        }
        else {
            return false;
        }
        break;
    case 32772 :
        if (parsePIDTYPECODE_O (&topicparms_rtps->ptr.pidtypecode_rtps, thePDU, progname, &type, endianness)) {
            topicparms_rtps->type = PIDTYPECODE_RTPS_VAL;
        }
        else {
            return false;
        }
        break;
    case 22 :
        if (parsePIDVENDORID_O (&topicparms_rtps->ptr.pidvendorid_rtps, thePDU, progname, &type, endianness)) {
            topicparms_rtps->type = PIDVENDORID_RTPS_VAL;
        }
        else {
            return false;
        }
        break;
    case 98 :
        if (parsePIDENTITYNAME_O (&topicparms_rtps->ptr.pidentityname_rtps, thePDU, progname, &type, endianness)) {
            topicparms_rtps->type = PIDENTITYNAME_RTPS_VAL;
        }
        else {
            return false;
        }
        break;
    case 16 :
        if (parsePIDEXPECTSACK_O (&topicparms_rtps->ptr.pidexpectsack_rtps, thePDU, progname, &type, endianness)) {
            topicparms_rtps->type = PIDEXPECTSACK_RTPS_VAL;
        }
        else {
            return false;
        }
        break;
    case 19 :
        if (parsePIDSENDQUEUESIZE_O (&topicparms_rtps->ptr.pidsendqueuesize_rtps, thePDU, progname, &type, endianness)) {
            topicparms_rtps->type = PIDSENDQUEUESIZE_RTPS_VAL;
        }
        else {
            return false;
        }
        break;
    case 6 :
        if (parsePIDOWNERSHIPSTRENGTH_O (&topicparms_rtps->ptr.pidownershipstrength_rtps, thePDU, progname, &type, endianness)) {
            topicparms_rtps->type = PIDOWNERSHIPSTRENGTH_RTPS_VAL;
        }
        else {
            return false;
        }
        break;
    case 3 :
        if (parsePIDPERSISTENCE_O (&topicparms_rtps->ptr.pidpersistence_rtps, thePDU, progname, &type, endianness)) {
            topicparms_rtps->type = PIDPERSISTENCE_RTPS_VAL;
        }
        else {
            return false;
        }
        break;
    case 43 :
        if (parsePIDLIFESPAN_O (&topicparms_rtps->ptr.pidlifespan_rtps, thePDU, progname, &type, endianness)) {
            topicparms_rtps->type = PIDLIFESPAN_RTPS_VAL;
        }
        else {
            return false;
        }
        break;
    case 96 :
        if (parsePIDTYPEMAXSIZESERIALIZED_O (&topicparms_rtps->ptr.pidtypemaxsizeserialized_rtps, thePDU, progname, &type, endianness)) {
            topicparms_rtps->type = PIDTYPEMAXSIZESERIALIZED_RTPS_VAL;
        }
        else {
            return false;
        }
        break;
    case 30 :
        if (parsePIDDURABILITYSERVICE_O (&topicparms_rtps->ptr.piddurabilityservice_rtps, thePDU, progname, &type, endianness)) {
            topicparms_rtps->type = PIDDURABILITYSERVICE_RTPS_VAL;
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

bool parsePIDTYPEMAXSIZESERIALIZED (PIDTYPEMAXSIZESERIALIZED_RTPS *pidtypemaxsizeserialized_rtps, PDU *thePDU, char *progname, uint8_t endianness) {
    if (!lengthRemaining (thePDU, 4, progname)) {
        return false;
    }
    pidtypemaxsizeserialized_rtps->value = NULL;
    pidtypemaxsizeserialized_rtps->parameterkind = get16_e (thePDU, endianness);
    if (!(pidtypemaxsizeserialized_rtps->parameterkind == 96)) {
        return false;
    }
    pidtypemaxsizeserialized_rtps->parameterlength = get16_e (thePDU, endianness);
    unsigned long remaining = thePDU->remaining;
    if (!lengthRemaining (thePDU, pidtypemaxsizeserialized_rtps->parameterlength, progname)) {
        return false;
    }
    pidtypemaxsizeserialized_rtps->value = (unsigned char *) malloc (sizeof (unsigned char) * (pidtypemaxsizeserialized_rtps->parameterlength));
    if (pidtypemaxsizeserialized_rtps->value == NULL) {
        fprintf (stderr, "%s: internal malloc error file: %s line: %d \n", progname, __FILE__, __LINE__);
        return false;
    }
    pidtypemaxsizeserialized_rtps->value_length = pidtypemaxsizeserialized_rtps->parameterlength;
    memcpy (pidtypemaxsizeserialized_rtps->value, &thePDU->data[thePDU->curPos], pidtypemaxsizeserialized_rtps->parameterlength);
    thePDU->curPos += pidtypemaxsizeserialized_rtps->parameterlength;
    if (pidtypemaxsizeserialized_rtps->value[pidtypemaxsizeserialized_rtps->parameterlength - 1] != '\0') {
    }
    return true;
}

bool parsePIDTYPEMAXSIZESERIALIZED_O (PIDTYPEMAXSIZESERIALIZED_RTPS *pidtypemaxsizeserialized_rtps, PDU *thePDU, char *progname, uint16_t *type, uint8_t
  endianness) {
    pidtypemaxsizeserialized_rtps->parameterkind = *type;
    if (!lengthRemaining (thePDU, 2, progname)) {
        return false;
    }
    pidtypemaxsizeserialized_rtps->value = NULL;
    pidtypemaxsizeserialized_rtps->parameterlength = get16_e (thePDU, endianness);
    unsigned long remaining = thePDU->remaining;
    if (!lengthRemaining (thePDU, pidtypemaxsizeserialized_rtps->parameterlength, progname)) {
        return false;
    }
    pidtypemaxsizeserialized_rtps->value = (unsigned char *) malloc (sizeof (unsigned char) * (pidtypemaxsizeserialized_rtps->parameterlength));
    if (pidtypemaxsizeserialized_rtps->value == NULL) {
        fprintf (stderr, "%s: internal malloc error file: %s line: %d \n", progname, __FILE__, __LINE__);
        return false;
    }
    pidtypemaxsizeserialized_rtps->value_length = pidtypemaxsizeserialized_rtps->parameterlength;
    memcpy (pidtypemaxsizeserialized_rtps->value, &thePDU->data[thePDU->curPos], pidtypemaxsizeserialized_rtps->parameterlength);
    thePDU->curPos += pidtypemaxsizeserialized_rtps->parameterlength;
    if (pidtypemaxsizeserialized_rtps->value[pidtypemaxsizeserialized_rtps->parameterlength - 1] != '\0') {
    }
    return true;
}

bool parsePIDLIFESPAN (PIDLIFESPAN_RTPS *pidlifespan_rtps, PDU *thePDU, char *progname, uint8_t endianness) {
    if (!lengthRemaining (thePDU, 4, progname)) {
        return false;
    }
    pidlifespan_rtps->leaseduration = NULL;
    pidlifespan_rtps->parameterkind = get16_e (thePDU, endianness);
    if (!(pidlifespan_rtps->parameterkind == 43)) {
        return false;
    }
    pidlifespan_rtps->parameterlength = get16_e (thePDU, endianness);
    unsigned long remaining = thePDU->remaining;
    if (!lengthRemaining (thePDU, pidlifespan_rtps->parameterlength, progname)) {
        return false;
    }
    pidlifespan_rtps->leaseduration = (unsigned char *) malloc (sizeof (unsigned char) * (pidlifespan_rtps->parameterlength));
    if (pidlifespan_rtps->leaseduration == NULL) {
        fprintf (stderr, "%s: internal malloc error file: %s line: %d \n", progname, __FILE__, __LINE__);
        return false;
    }
    pidlifespan_rtps->leaseduration_length = pidlifespan_rtps->parameterlength;
    memcpy (pidlifespan_rtps->leaseduration, &thePDU->data[thePDU->curPos], pidlifespan_rtps->parameterlength);
    thePDU->curPos += pidlifespan_rtps->parameterlength;
    if (pidlifespan_rtps->leaseduration[pidlifespan_rtps->parameterlength - 1] != '\0') {
    }
    return true;
}

bool parsePIDLIFESPAN_O (PIDLIFESPAN_RTPS *pidlifespan_rtps, PDU *thePDU, char *progname, uint16_t *type, uint8_t endianness) {
    pidlifespan_rtps->parameterkind = *type;
    if (!lengthRemaining (thePDU, 2, progname)) {
        return false;
    }
    pidlifespan_rtps->leaseduration = NULL;
    pidlifespan_rtps->parameterlength = get16_e (thePDU, endianness);
    unsigned long remaining = thePDU->remaining;
    if (!lengthRemaining (thePDU, pidlifespan_rtps->parameterlength, progname)) {
        return false;
    }
    pidlifespan_rtps->leaseduration = (unsigned char *) malloc (sizeof (unsigned char) * (pidlifespan_rtps->parameterlength));
    if (pidlifespan_rtps->leaseduration == NULL) {
        fprintf (stderr, "%s: internal malloc error file: %s line: %d \n", progname, __FILE__, __LINE__);
        return false;
    }
    pidlifespan_rtps->leaseduration_length = pidlifespan_rtps->parameterlength;
    memcpy (pidlifespan_rtps->leaseduration, &thePDU->data[thePDU->curPos], pidlifespan_rtps->parameterlength);
    thePDU->curPos += pidlifespan_rtps->parameterlength;
    if (pidlifespan_rtps->leaseduration[pidlifespan_rtps->parameterlength - 1] != '\0') {
    }
    return true;
}

bool parsePIDDURABILITYSERVICE (PIDDURABILITYSERVICE_RTPS *piddurabilityservice_rtps, PDU *thePDU, char *progname, uint8_t endianness) {
    if (!lengthRemaining (thePDU, 4, progname)) {
        return false;
    }
    piddurabilityservice_rtps->durabilityservice = NULL;
    piddurabilityservice_rtps->parameterkind = get16_e (thePDU, endianness);
    if (!(piddurabilityservice_rtps->parameterkind == 30)) {
        return false;
    }
    piddurabilityservice_rtps->parameterlength = get16_e (thePDU, endianness);
    unsigned long remaining = thePDU->remaining;
    if (!lengthRemaining (thePDU, piddurabilityservice_rtps->parameterlength, progname)) {
        return false;
    }
    piddurabilityservice_rtps->durabilityservice = (unsigned char *) malloc (sizeof (unsigned char) * (piddurabilityservice_rtps->parameterlength));
    if (piddurabilityservice_rtps->durabilityservice == NULL) {
        fprintf (stderr, "%s: internal malloc error file: %s line: %d \n", progname, __FILE__, __LINE__);
        return false;
    }
    piddurabilityservice_rtps->durabilityservice_length = piddurabilityservice_rtps->parameterlength;
    memcpy (piddurabilityservice_rtps->durabilityservice, &thePDU->data[thePDU->curPos], piddurabilityservice_rtps->parameterlength);
    thePDU->curPos += piddurabilityservice_rtps->parameterlength;
    if (piddurabilityservice_rtps->durabilityservice[piddurabilityservice_rtps->parameterlength - 1] != '\0') {
    }
    return true;
}

bool parsePIDDURABILITYSERVICE_O (PIDDURABILITYSERVICE_RTPS *piddurabilityservice_rtps, PDU *thePDU, char *progname, uint16_t *type, uint8_t endianness) {
    piddurabilityservice_rtps->parameterkind = *type;
    if (!lengthRemaining (thePDU, 2, progname)) {
        return false;
    }
    piddurabilityservice_rtps->durabilityservice = NULL;
    piddurabilityservice_rtps->parameterlength = get16_e (thePDU, endianness);
    unsigned long remaining = thePDU->remaining;
    if (!lengthRemaining (thePDU, piddurabilityservice_rtps->parameterlength, progname)) {
        return false;
    }
    piddurabilityservice_rtps->durabilityservice = (unsigned char *) malloc (sizeof (unsigned char) * (piddurabilityservice_rtps->parameterlength));
    if (piddurabilityservice_rtps->durabilityservice == NULL) {
        fprintf (stderr, "%s: internal malloc error file: %s line: %d \n", progname, __FILE__, __LINE__);
        return false;
    }
    piddurabilityservice_rtps->durabilityservice_length = piddurabilityservice_rtps->parameterlength;
    memcpy (piddurabilityservice_rtps->durabilityservice, &thePDU->data[thePDU->curPos], piddurabilityservice_rtps->parameterlength);
    thePDU->curPos += piddurabilityservice_rtps->parameterlength;
    if (piddurabilityservice_rtps->durabilityservice[piddurabilityservice_rtps->parameterlength - 1] != '\0') {
    }
    return true;
}

bool parsePIDPERSISTENCE (PIDPERSISTENCE_RTPS *pidpersistence_rtps, PDU *thePDU, char *progname, uint8_t endianness) {
    if (!lengthRemaining (thePDU, 4, progname)) {
        return false;
    }
    pidpersistence_rtps->leaseduration = NULL;
    pidpersistence_rtps->parameterkind = get16_e (thePDU, endianness);
    if (!(pidpersistence_rtps->parameterkind == 3)) {
        return false;
    }
    pidpersistence_rtps->parameterlength = get16_e (thePDU, endianness);
    unsigned long remaining = thePDU->remaining;
    if (!lengthRemaining (thePDU, pidpersistence_rtps->parameterlength, progname)) {
        return false;
    }
    pidpersistence_rtps->leaseduration = (unsigned char *) malloc (sizeof (unsigned char) * (pidpersistence_rtps->parameterlength));
    if (pidpersistence_rtps->leaseduration == NULL) {
        fprintf (stderr, "%s: internal malloc error file: %s line: %d \n", progname, __FILE__, __LINE__);
        return false;
    }
    pidpersistence_rtps->leaseduration_length = pidpersistence_rtps->parameterlength;
    memcpy (pidpersistence_rtps->leaseduration, &thePDU->data[thePDU->curPos], pidpersistence_rtps->parameterlength);
    thePDU->curPos += pidpersistence_rtps->parameterlength;
    if (pidpersistence_rtps->leaseduration[pidpersistence_rtps->parameterlength - 1] != '\0') {
    }
    return true;
}

bool parsePIDPERSISTENCE_O (PIDPERSISTENCE_RTPS *pidpersistence_rtps, PDU *thePDU, char *progname, uint16_t *type, uint8_t endianness) {
    pidpersistence_rtps->parameterkind = *type;
    if (!lengthRemaining (thePDU, 2, progname)) {
        return false;
    }
    pidpersistence_rtps->leaseduration = NULL;
    pidpersistence_rtps->parameterlength = get16_e (thePDU, endianness);
    unsigned long remaining = thePDU->remaining;
    if (!lengthRemaining (thePDU, pidpersistence_rtps->parameterlength, progname)) {
        return false;
    }
    pidpersistence_rtps->leaseduration = (unsigned char *) malloc (sizeof (unsigned char) * (pidpersistence_rtps->parameterlength));
    if (pidpersistence_rtps->leaseduration == NULL) {
        fprintf (stderr, "%s: internal malloc error file: %s line: %d \n", progname, __FILE__, __LINE__);
        return false;
    }
    pidpersistence_rtps->leaseduration_length = pidpersistence_rtps->parameterlength;
    memcpy (pidpersistence_rtps->leaseduration, &thePDU->data[thePDU->curPos], pidpersistence_rtps->parameterlength);
    thePDU->curPos += pidpersistence_rtps->parameterlength;
    if (pidpersistence_rtps->leaseduration[pidpersistence_rtps->parameterlength - 1] != '\0') {
    }
    return true;
}

bool parsePIDOWNERSHIPSTRENGTH (PIDOWNERSHIPSTRENGTH_RTPS *pidownershipstrength_rtps, PDU *thePDU, char *progname, uint8_t endianness) {
    if (!lengthRemaining (thePDU, 4, progname)) {
        return false;
    }
    pidownershipstrength_rtps->strength = NULL;
    pidownershipstrength_rtps->parameterkind = get16_e (thePDU, endianness);
    if (!(pidownershipstrength_rtps->parameterkind == 6)) {
        return false;
    }
    pidownershipstrength_rtps->parameterlength = get16_e (thePDU, endianness);
    unsigned long remaining = thePDU->remaining;
    if (!lengthRemaining (thePDU, pidownershipstrength_rtps->parameterlength, progname)) {
        return false;
    }
    pidownershipstrength_rtps->strength = (unsigned char *) malloc (sizeof (unsigned char) * (pidownershipstrength_rtps->parameterlength));
    if (pidownershipstrength_rtps->strength == NULL) {
        fprintf (stderr, "%s: internal malloc error file: %s line: %d \n", progname, __FILE__, __LINE__);
        return false;
    }
    pidownershipstrength_rtps->strength_length = pidownershipstrength_rtps->parameterlength;
    memcpy (pidownershipstrength_rtps->strength, &thePDU->data[thePDU->curPos], pidownershipstrength_rtps->parameterlength);
    thePDU->curPos += pidownershipstrength_rtps->parameterlength;
    if (pidownershipstrength_rtps->strength[pidownershipstrength_rtps->parameterlength - 1] != '\0') {
    }
    return true;
}

bool parsePIDOWNERSHIPSTRENGTH_O (PIDOWNERSHIPSTRENGTH_RTPS *pidownershipstrength_rtps, PDU *thePDU, char *progname, uint16_t *type, uint8_t endianness) {
    pidownershipstrength_rtps->parameterkind = *type;
    if (!lengthRemaining (thePDU, 2, progname)) {
        return false;
    }
    pidownershipstrength_rtps->strength = NULL;
    pidownershipstrength_rtps->parameterlength = get16_e (thePDU, endianness);
    unsigned long remaining = thePDU->remaining;
    if (!lengthRemaining (thePDU, pidownershipstrength_rtps->parameterlength, progname)) {
        return false;
    }
    pidownershipstrength_rtps->strength = (unsigned char *) malloc (sizeof (unsigned char) * (pidownershipstrength_rtps->parameterlength));
    if (pidownershipstrength_rtps->strength == NULL) {
        fprintf (stderr, "%s: internal malloc error file: %s line: %d \n", progname, __FILE__, __LINE__);
        return false;
    }
    pidownershipstrength_rtps->strength_length = pidownershipstrength_rtps->parameterlength;
    memcpy (pidownershipstrength_rtps->strength, &thePDU->data[thePDU->curPos], pidownershipstrength_rtps->parameterlength);
    thePDU->curPos += pidownershipstrength_rtps->parameterlength;
    if (pidownershipstrength_rtps->strength[pidownershipstrength_rtps->parameterlength - 1] != '\0') {
    }
    return true;
}

bool parsePIDSENDQUEUESIZE (PIDSENDQUEUESIZE_RTPS *pidsendqueuesize_rtps, PDU *thePDU, char *progname, uint8_t endianness) {
    if (!lengthRemaining (thePDU, 4, progname)) {
        return false;
    }
    pidsendqueuesize_rtps->queuesize = NULL;
    pidsendqueuesize_rtps->parameterkind = get16_e (thePDU, endianness);
    if (!(pidsendqueuesize_rtps->parameterkind == 19)) {
        return false;
    }
    pidsendqueuesize_rtps->parameterlength = get16_e (thePDU, endianness);
    unsigned long remaining = thePDU->remaining;
    if (!lengthRemaining (thePDU, pidsendqueuesize_rtps->parameterlength, progname)) {
        return false;
    }
    pidsendqueuesize_rtps->queuesize = (unsigned char *) malloc (sizeof (unsigned char) * (pidsendqueuesize_rtps->parameterlength));
    if (pidsendqueuesize_rtps->queuesize == NULL) {
        fprintf (stderr, "%s: internal malloc error file: %s line: %d \n", progname, __FILE__, __LINE__);
        return false;
    }
    pidsendqueuesize_rtps->queuesize_length = pidsendqueuesize_rtps->parameterlength;
    memcpy (pidsendqueuesize_rtps->queuesize, &thePDU->data[thePDU->curPos], pidsendqueuesize_rtps->parameterlength);
    thePDU->curPos += pidsendqueuesize_rtps->parameterlength;
    if (pidsendqueuesize_rtps->queuesize[pidsendqueuesize_rtps->parameterlength - 1] != '\0') {
    }
    return true;
}

bool parsePIDSENDQUEUESIZE_O (PIDSENDQUEUESIZE_RTPS *pidsendqueuesize_rtps, PDU *thePDU, char *progname, uint16_t *type, uint8_t endianness) {
    pidsendqueuesize_rtps->parameterkind = *type;
    if (!lengthRemaining (thePDU, 2, progname)) {
        return false;
    }
    pidsendqueuesize_rtps->queuesize = NULL;
    pidsendqueuesize_rtps->parameterlength = get16_e (thePDU, endianness);
    unsigned long remaining = thePDU->remaining;
    if (!lengthRemaining (thePDU, pidsendqueuesize_rtps->parameterlength, progname)) {
        return false;
    }
    pidsendqueuesize_rtps->queuesize = (unsigned char *) malloc (sizeof (unsigned char) * (pidsendqueuesize_rtps->parameterlength));
    if (pidsendqueuesize_rtps->queuesize == NULL) {
        fprintf (stderr, "%s: internal malloc error file: %s line: %d \n", progname, __FILE__, __LINE__);
        return false;
    }
    pidsendqueuesize_rtps->queuesize_length = pidsendqueuesize_rtps->parameterlength;
    memcpy (pidsendqueuesize_rtps->queuesize, &thePDU->data[thePDU->curPos], pidsendqueuesize_rtps->parameterlength);
    thePDU->curPos += pidsendqueuesize_rtps->parameterlength;
    if (pidsendqueuesize_rtps->queuesize[pidsendqueuesize_rtps->parameterlength - 1] != '\0') {
    }
    return true;
}

bool parsePIDEXPECTSACK (PIDEXPECTSACK_RTPS *pidexpectsack_rtps, PDU *thePDU, char *progname, uint8_t endianness) {
    if (!lengthRemaining (thePDU, 4, progname)) {
        return false;
    }
    pidexpectsack_rtps->expectsack = NULL;
    pidexpectsack_rtps->parameterkind = get16_e (thePDU, endianness);
    if (!(pidexpectsack_rtps->parameterkind == 16)) {
        return false;
    }
    pidexpectsack_rtps->parameterlength = get16_e (thePDU, endianness);
    unsigned long remaining = thePDU->remaining;
    if (!lengthRemaining (thePDU, pidexpectsack_rtps->parameterlength, progname)) {
        return false;
    }
    pidexpectsack_rtps->expectsack = (unsigned char *) malloc (sizeof (unsigned char) * (pidexpectsack_rtps->parameterlength));
    if (pidexpectsack_rtps->expectsack == NULL) {
        fprintf (stderr, "%s: internal malloc error file: %s line: %d \n", progname, __FILE__, __LINE__);
        return false;
    }
    pidexpectsack_rtps->expectsack_length = pidexpectsack_rtps->parameterlength;
    memcpy (pidexpectsack_rtps->expectsack, &thePDU->data[thePDU->curPos], pidexpectsack_rtps->parameterlength);
    thePDU->curPos += pidexpectsack_rtps->parameterlength;
    if (pidexpectsack_rtps->expectsack[pidexpectsack_rtps->parameterlength - 1] != '\0') {
    }
    return true;
}

bool parsePIDEXPECTSACK_O (PIDEXPECTSACK_RTPS *pidexpectsack_rtps, PDU *thePDU, char *progname, uint16_t *type, uint8_t endianness) {
    pidexpectsack_rtps->parameterkind = *type;
    if (!lengthRemaining (thePDU, 2, progname)) {
        return false;
    }
    pidexpectsack_rtps->expectsack = NULL;
    pidexpectsack_rtps->parameterlength = get16_e (thePDU, endianness);
    unsigned long remaining = thePDU->remaining;
    if (!lengthRemaining (thePDU, pidexpectsack_rtps->parameterlength, progname)) {
        return false;
    }
    pidexpectsack_rtps->expectsack = (unsigned char *) malloc (sizeof (unsigned char) * (pidexpectsack_rtps->parameterlength));
    if (pidexpectsack_rtps->expectsack == NULL) {
        fprintf (stderr, "%s: internal malloc error file: %s line: %d \n", progname, __FILE__, __LINE__);
        return false;
    }
    pidexpectsack_rtps->expectsack_length = pidexpectsack_rtps->parameterlength;
    memcpy (pidexpectsack_rtps->expectsack, &thePDU->data[thePDU->curPos], pidexpectsack_rtps->parameterlength);
    thePDU->curPos += pidexpectsack_rtps->parameterlength;
    if (pidexpectsack_rtps->expectsack[pidexpectsack_rtps->parameterlength - 1] != '\0') {
    }
    return true;
}

bool parsePIDTYPECODE (PIDTYPECODE_RTPS *pidtypecode_rtps, PDU *thePDU, char *progname, uint8_t endianness) {
    if (!lengthRemaining (thePDU, 4, progname)) {
        return false;
    }
    pidtypecode_rtps->typeobjectcode = NULL;
    pidtypecode_rtps->parameterkind = get16_e (thePDU, endianness);
    if (!(pidtypecode_rtps->parameterkind == 32772)) {
        return false;
    }
    pidtypecode_rtps->parameterlength = get16_e (thePDU, endianness);
    unsigned long remaining = thePDU->remaining;
    if (!lengthRemaining (thePDU, pidtypecode_rtps->parameterlength, progname)) {
        return false;
    }
    pidtypecode_rtps->typeobjectcode = (unsigned char *) malloc (sizeof (unsigned char) * (pidtypecode_rtps->parameterlength));
    if (pidtypecode_rtps->typeobjectcode == NULL) {
        fprintf (stderr, "%s: internal malloc error file: %s line: %d \n", progname, __FILE__, __LINE__);
        return false;
    }
    pidtypecode_rtps->typeobjectcode_length = pidtypecode_rtps->parameterlength;
    memcpy (pidtypecode_rtps->typeobjectcode, &thePDU->data[thePDU->curPos], pidtypecode_rtps->parameterlength);
    thePDU->curPos += pidtypecode_rtps->parameterlength;
    if (pidtypecode_rtps->typeobjectcode[pidtypecode_rtps->parameterlength - 1] != '\0') {
    }
    return true;
}

bool parsePIDTYPECODE_O (PIDTYPECODE_RTPS *pidtypecode_rtps, PDU *thePDU, char *progname, uint16_t *type, uint8_t endianness) {
    pidtypecode_rtps->parameterkind = *type;
    if (!lengthRemaining (thePDU, 2, progname)) {
        return false;
    }
    pidtypecode_rtps->typeobjectcode = NULL;
    pidtypecode_rtps->parameterlength = get16_e (thePDU, endianness);
    unsigned long remaining = thePDU->remaining;
    if (!lengthRemaining (thePDU, pidtypecode_rtps->parameterlength, progname)) {
        return false;
    }
    pidtypecode_rtps->typeobjectcode = (unsigned char *) malloc (sizeof (unsigned char) * (pidtypecode_rtps->parameterlength));
    if (pidtypecode_rtps->typeobjectcode == NULL) {
        fprintf (stderr, "%s: internal malloc error file: %s line: %d \n", progname, __FILE__, __LINE__);
        return false;
    }
    pidtypecode_rtps->typeobjectcode_length = pidtypecode_rtps->parameterlength;
    memcpy (pidtypecode_rtps->typeobjectcode, &thePDU->data[thePDU->curPos], pidtypecode_rtps->parameterlength);
    thePDU->curPos += pidtypecode_rtps->parameterlength;
    if (pidtypecode_rtps->typeobjectcode[pidtypecode_rtps->parameterlength - 1] != '\0') {
    }
    return true;
}

bool parsePIDTYPEOBJECT (PIDTYPEOBJECT_RTPS *pidtypeobject_rtps, PDU *thePDU, char *progname, uint8_t endianness) {
    if (!lengthRemaining (thePDU, 4, progname)) {
        return false;
    }
    pidtypeobject_rtps->typeobject = NULL;
    pidtypeobject_rtps->parameterkind = get16_e (thePDU, endianness);
    if (!(pidtypeobject_rtps->parameterkind == 114)) {
        return false;
    }
    pidtypeobject_rtps->parameterlength = get16_e (thePDU, endianness);
    unsigned long remaining = thePDU->remaining;
    if (!lengthRemaining (thePDU, pidtypeobject_rtps->parameterlength, progname)) {
        return false;
    }
    pidtypeobject_rtps->typeobject = (unsigned char *) malloc (sizeof (unsigned char) * (pidtypeobject_rtps->parameterlength));
    if (pidtypeobject_rtps->typeobject == NULL) {
        fprintf (stderr, "%s: internal malloc error file: %s line: %d \n", progname, __FILE__, __LINE__);
        return false;
    }
    pidtypeobject_rtps->typeobject_length = pidtypeobject_rtps->parameterlength;
    memcpy (pidtypeobject_rtps->typeobject, &thePDU->data[thePDU->curPos], pidtypeobject_rtps->parameterlength);
    thePDU->curPos += pidtypeobject_rtps->parameterlength;
    if (pidtypeobject_rtps->typeobject[pidtypeobject_rtps->parameterlength - 1] != '\0') {
    }
    return true;
}

bool parsePIDTYPEOBJECT_O (PIDTYPEOBJECT_RTPS *pidtypeobject_rtps, PDU *thePDU, char *progname, uint16_t *type, uint8_t endianness) {
    pidtypeobject_rtps->parameterkind = *type;
    if (!lengthRemaining (thePDU, 2, progname)) {
        return false;
    }
    pidtypeobject_rtps->typeobject = NULL;
    pidtypeobject_rtps->parameterlength = get16_e (thePDU, endianness);
    unsigned long remaining = thePDU->remaining;
    if (!lengthRemaining (thePDU, pidtypeobject_rtps->parameterlength, progname)) {
        return false;
    }
    pidtypeobject_rtps->typeobject = (unsigned char *) malloc (sizeof (unsigned char) * (pidtypeobject_rtps->parameterlength));
    if (pidtypeobject_rtps->typeobject == NULL) {
        fprintf (stderr, "%s: internal malloc error file: %s line: %d \n", progname, __FILE__, __LINE__);
        return false;
    }
    pidtypeobject_rtps->typeobject_length = pidtypeobject_rtps->parameterlength;
    memcpy (pidtypeobject_rtps->typeobject, &thePDU->data[thePDU->curPos], pidtypeobject_rtps->parameterlength);
    thePDU->curPos += pidtypeobject_rtps->parameterlength;
    if (pidtypeobject_rtps->typeobject[pidtypeobject_rtps->parameterlength - 1] != '\0') {
    }
    return true;
}

bool parsePIDTYPECONSISTENCY (PIDTYPECONSISTENCY_RTPS *pidtypeconsistency_rtps, PDU *thePDU, char *progname, uint8_t endianness) {
    if (!lengthRemaining (thePDU, 4, progname)) {
        return false;
    }
    pidtypeconsistency_rtps->parameterkind = get16_e (thePDU, endianness);
    if (!(pidtypeconsistency_rtps->parameterkind == 116)) {
        return false;
    }
    pidtypeconsistency_rtps->parameterlength = get16_e (thePDU, endianness);
    unsigned long pos = thePDU->curPos;
    if (!lengthRemaining (thePDU, pidtypeconsistency_rtps->parameterlength, progname)) {
        return false;
    }
    PDU constrainedPDU;
    constrainedPDU.data = thePDU->data;
    constrainedPDU.len = pidtypeconsistency_rtps->parameterlength;
    constrainedPDU.watermark = thePDU->watermark;
    constrainedPDU.curPos = pos;
    constrainedPDU.curBitPos = 0;
    constrainedPDU.remaining = pidtypeconsistency_rtps->parameterlength;
    TYPECONSISTENCYKIND_RTPS typeconsistencykind;
    if (!parseTYPECONSISTENCYKIND (&typeconsistencykind, &constrainedPDU, progname, endianness)) {
        return false;
    }
    pidtypeconsistency_rtps->typeconsistencykind = typeconsistencykind;
    thePDU->curPos += constrainedPDU.len;
    return true;
}

bool parsePIDTYPECONSISTENCY_O (PIDTYPECONSISTENCY_RTPS *pidtypeconsistency_rtps, PDU *thePDU, char *progname, uint16_t *type, uint8_t endianness) {
    pidtypeconsistency_rtps->parameterkind = *type;
    if (!lengthRemaining (thePDU, 2, progname)) {
        return false;
    }
    pidtypeconsistency_rtps->parameterlength = get16_e (thePDU, endianness);
    unsigned long pos = thePDU->curPos;
    if (!lengthRemaining (thePDU, pidtypeconsistency_rtps->parameterlength, progname)) {
        return false;
    }
    PDU constrainedPDU;
    constrainedPDU.data = thePDU->data;
    constrainedPDU.len = pidtypeconsistency_rtps->parameterlength;
    constrainedPDU.watermark = thePDU->watermark;
    constrainedPDU.curPos = pos;
    constrainedPDU.curBitPos = 0;
    constrainedPDU.remaining = pidtypeconsistency_rtps->parameterlength;
    TYPECONSISTENCYKIND_RTPS typeconsistencykind;
    if (!parseTYPECONSISTENCYKIND (&typeconsistencykind, &constrainedPDU, progname, endianness)) {
        return false;
    }
    pidtypeconsistency_rtps->typeconsistencykind = typeconsistencykind;
    thePDU->curPos += constrainedPDU.len;
    return true;
}

bool parseTYPECONSISTENCYKIND (TYPECONSISTENCYKIND_RTPS *typeconsistencykind_rtps, PDU *thePDU, char *progname, uint8_t endianness) {
    if (!lengthRemaining (thePDU, 2, progname)) {
        return false;
    }
    typeconsistencykind_rtps->kind = get16_e (thePDU, endianness);
    return true;
}

bool parsePIDEXPECTSVIRTUALHB (PIDEXPECTSVIRTUALHB_RTPS *pidexpectsvirtualhb_rtps, PDU *thePDU, char *progname, uint8_t endianness) {
    if (!lengthRemaining (thePDU, 4, progname)) {
        return false;
    }
    pidexpectsvirtualhb_rtps->parameterkind = get16_e (thePDU, endianness);
    if (!(pidexpectsvirtualhb_rtps->parameterkind == 32777)) {
        return false;
    }
    pidexpectsvirtualhb_rtps->parameterlength = get16_e (thePDU, endianness);
    unsigned long pos = thePDU->curPos;
    if (!lengthRemaining (thePDU, pidexpectsvirtualhb_rtps->parameterlength, progname)) {
        return false;
    }
    PDU constrainedPDU;
    constrainedPDU.data = thePDU->data;
    constrainedPDU.len = pidexpectsvirtualhb_rtps->parameterlength;
    constrainedPDU.watermark = thePDU->watermark;
    constrainedPDU.curPos = pos;
    constrainedPDU.curBitPos = 0;
    constrainedPDU.remaining = pidexpectsvirtualhb_rtps->parameterlength;
    FLAG_RTPS expectsvirtualhb;
    if (!parseFLAG (&expectsvirtualhb, &constrainedPDU, progname, endianness)) {
        return false;
    }
    pidexpectsvirtualhb_rtps->expectsvirtualhb = expectsvirtualhb;
    thePDU->curPos += constrainedPDU.len;
    return true;
}

bool parsePIDEXPECTSVIRTUALHB_O (PIDEXPECTSVIRTUALHB_RTPS *pidexpectsvirtualhb_rtps, PDU *thePDU, char *progname, uint16_t *type, uint8_t endianness) {
    pidexpectsvirtualhb_rtps->parameterkind = *type;
    if (!lengthRemaining (thePDU, 2, progname)) {
        return false;
    }
    pidexpectsvirtualhb_rtps->parameterlength = get16_e (thePDU, endianness);
    unsigned long pos = thePDU->curPos;
    if (!lengthRemaining (thePDU, pidexpectsvirtualhb_rtps->parameterlength, progname)) {
        return false;
    }
    PDU constrainedPDU;
    constrainedPDU.data = thePDU->data;
    constrainedPDU.len = pidexpectsvirtualhb_rtps->parameterlength;
    constrainedPDU.watermark = thePDU->watermark;
    constrainedPDU.curPos = pos;
    constrainedPDU.curBitPos = 0;
    constrainedPDU.remaining = pidexpectsvirtualhb_rtps->parameterlength;
    FLAG_RTPS expectsvirtualhb;
    if (!parseFLAG (&expectsvirtualhb, &constrainedPDU, progname, endianness)) {
        return false;
    }
    pidexpectsvirtualhb_rtps->expectsvirtualhb = expectsvirtualhb;
    thePDU->curPos += constrainedPDU.len;
    return true;
}

bool parsePIDDISABLEPOSITIVEACKS (PIDDISABLEPOSITIVEACKS_RTPS *piddisablepositiveacks_rtps, PDU *thePDU, char *progname, uint8_t endianness) {
    if (!lengthRemaining (thePDU, 4, progname)) {
        return false;
    }
    piddisablepositiveacks_rtps->parameterkind = get16_e (thePDU, endianness);
    if (!(piddisablepositiveacks_rtps->parameterkind == 32773)) {
        return false;
    }
    piddisablepositiveacks_rtps->parameterlength = get16_e (thePDU, endianness);
    unsigned long pos = thePDU->curPos;
    if (!lengthRemaining (thePDU, piddisablepositiveacks_rtps->parameterlength, progname)) {
        return false;
    }
    PDU constrainedPDU;
    constrainedPDU.data = thePDU->data;
    constrainedPDU.len = piddisablepositiveacks_rtps->parameterlength;
    constrainedPDU.watermark = thePDU->watermark;
    constrainedPDU.curPos = pos;
    constrainedPDU.curBitPos = 0;
    constrainedPDU.remaining = piddisablepositiveacks_rtps->parameterlength;
    FLAG_RTPS disablepositiveacks;
    if (!parseFLAG (&disablepositiveacks, &constrainedPDU, progname, endianness)) {
        return false;
    }
    piddisablepositiveacks_rtps->disablepositiveacks = disablepositiveacks;
    thePDU->curPos += constrainedPDU.len;
    return true;
}

bool parsePIDDISABLEPOSITIVEACKS_O (PIDDISABLEPOSITIVEACKS_RTPS *piddisablepositiveacks_rtps, PDU *thePDU, char *progname, uint16_t *type, uint8_t endianness) {
    piddisablepositiveacks_rtps->parameterkind = *type;
    if (!lengthRemaining (thePDU, 2, progname)) {
        return false;
    }
    piddisablepositiveacks_rtps->parameterlength = get16_e (thePDU, endianness);
    unsigned long pos = thePDU->curPos;
    if (!lengthRemaining (thePDU, piddisablepositiveacks_rtps->parameterlength, progname)) {
        return false;
    }
    PDU constrainedPDU;
    constrainedPDU.data = thePDU->data;
    constrainedPDU.len = piddisablepositiveacks_rtps->parameterlength;
    constrainedPDU.watermark = thePDU->watermark;
    constrainedPDU.curPos = pos;
    constrainedPDU.curBitPos = 0;
    constrainedPDU.remaining = piddisablepositiveacks_rtps->parameterlength;
    FLAG_RTPS disablepositiveacks;
    if (!parseFLAG (&disablepositiveacks, &constrainedPDU, progname, endianness)) {
        return false;
    }
    piddisablepositiveacks_rtps->disablepositiveacks = disablepositiveacks;
    thePDU->curPos += constrainedPDU.len;
    return true;
}

bool parseFLAG (FLAG_RTPS *flag_rtps, PDU *thePDU, char *progname, uint8_t endianness) {
    if (!lengthRemaining (thePDU, 1, progname)) {
        return false;
    }
    flag_rtps->flag = get8_e (thePDU, endianness);
    return true;
}

bool parsePIDSERVICEKIND (PIDSERVICEKIND_RTPS *pidservicekind_rtps, PDU *thePDU, char *progname, uint8_t endianness) {
    if (!lengthRemaining (thePDU, 4, progname)) {
        return false;
    }
    pidservicekind_rtps->servicekind = NULL;
    pidservicekind_rtps->parameterkind = get16_e (thePDU, endianness);
    if (!(pidservicekind_rtps->parameterkind == 32771)) {
        return false;
    }
    pidservicekind_rtps->parameterlength = get16_e (thePDU, endianness);
    unsigned long remaining = thePDU->remaining;
    if (!lengthRemaining (thePDU, pidservicekind_rtps->parameterlength, progname)) {
        return false;
    }
    pidservicekind_rtps->servicekind = (unsigned char *) malloc (sizeof (unsigned char) * (pidservicekind_rtps->parameterlength));
    if (pidservicekind_rtps->servicekind == NULL) {
        fprintf (stderr, "%s: internal malloc error file: %s line: %d \n", progname, __FILE__, __LINE__);
        return false;
    }
    pidservicekind_rtps->servicekind_length = pidservicekind_rtps->parameterlength;
    memcpy (pidservicekind_rtps->servicekind, &thePDU->data[thePDU->curPos], pidservicekind_rtps->parameterlength);
    thePDU->curPos += pidservicekind_rtps->parameterlength;
    if (pidservicekind_rtps->servicekind[pidservicekind_rtps->parameterlength - 1] != '\0') {
    }
    return true;
}

bool parsePIDSERVICEKIND_O (PIDSERVICEKIND_RTPS *pidservicekind_rtps, PDU *thePDU, char *progname, uint16_t *type, uint8_t endianness) {
    pidservicekind_rtps->parameterkind = *type;
    if (!lengthRemaining (thePDU, 2, progname)) {
        return false;
    }
    pidservicekind_rtps->servicekind = NULL;
    pidservicekind_rtps->parameterlength = get16_e (thePDU, endianness);
    unsigned long remaining = thePDU->remaining;
    if (!lengthRemaining (thePDU, pidservicekind_rtps->parameterlength, progname)) {
        return false;
    }
    pidservicekind_rtps->servicekind = (unsigned char *) malloc (sizeof (unsigned char) * (pidservicekind_rtps->parameterlength));
    if (pidservicekind_rtps->servicekind == NULL) {
        fprintf (stderr, "%s: internal malloc error file: %s line: %d \n", progname, __FILE__, __LINE__);
        return false;
    }
    pidservicekind_rtps->servicekind_length = pidservicekind_rtps->parameterlength;
    memcpy (pidservicekind_rtps->servicekind, &thePDU->data[thePDU->curPos], pidservicekind_rtps->parameterlength);
    thePDU->curPos += pidservicekind_rtps->parameterlength;
    if (pidservicekind_rtps->servicekind[pidservicekind_rtps->parameterlength - 1] != '\0') {
    }
    return true;
}

bool parsePIDENTITYVIRTUALGUID (PIDENTITYVIRTUALGUID_RTPS *pidentityvirtualguid_rtps, PDU *thePDU, char *progname, uint8_t endianness) {
    if (!lengthRemaining (thePDU, 4, progname)) {
        return false;
    }
    pidentityvirtualguid_rtps->parameterkind = get16_e (thePDU, endianness);
    if (!(pidentityvirtualguid_rtps->parameterkind == 32770)) {
        return false;
    }
    pidentityvirtualguid_rtps->parameterlength = get16_e (thePDU, endianness);
    unsigned long pos = thePDU->curPos;
    if (!lengthRemaining (thePDU, pidentityvirtualguid_rtps->parameterlength, progname)) {
        return false;
    }
    PDU constrainedPDU;
    constrainedPDU.data = thePDU->data;
    constrainedPDU.len = pidentityvirtualguid_rtps->parameterlength;
    constrainedPDU.watermark = thePDU->watermark;
    constrainedPDU.curPos = pos;
    constrainedPDU.curBitPos = 0;
    constrainedPDU.remaining = pidentityvirtualguid_rtps->parameterlength;
    VIRTUALGUID_RTPS virtualguid;
    if (!parseVIRTUALGUID (&virtualguid, &constrainedPDU, progname, endianness)) {
        return false;
    }
    pidentityvirtualguid_rtps->virtualguid = virtualguid;
    thePDU->curPos += constrainedPDU.len;
    return true;
}

bool parsePIDENTITYVIRTUALGUID_O (PIDENTITYVIRTUALGUID_RTPS *pidentityvirtualguid_rtps, PDU *thePDU, char *progname, uint16_t *type, uint8_t endianness) {
    pidentityvirtualguid_rtps->parameterkind = *type;
    if (!lengthRemaining (thePDU, 2, progname)) {
        return false;
    }
    pidentityvirtualguid_rtps->parameterlength = get16_e (thePDU, endianness);
    unsigned long pos = thePDU->curPos;
    if (!lengthRemaining (thePDU, pidentityvirtualguid_rtps->parameterlength, progname)) {
        return false;
    }
    PDU constrainedPDU;
    constrainedPDU.data = thePDU->data;
    constrainedPDU.len = pidentityvirtualguid_rtps->parameterlength;
    constrainedPDU.watermark = thePDU->watermark;
    constrainedPDU.curPos = pos;
    constrainedPDU.curBitPos = 0;
    constrainedPDU.remaining = pidentityvirtualguid_rtps->parameterlength;
    VIRTUALGUID_RTPS virtualguid;
    if (!parseVIRTUALGUID (&virtualguid, &constrainedPDU, progname, endianness)) {
        return false;
    }
    pidentityvirtualguid_rtps->virtualguid = virtualguid;
    thePDU->curPos += constrainedPDU.len;
    return true;
}

bool parseVIRTUALGUID (VIRTUALGUID_RTPS *virtualguid_rtps, PDU *thePDU, char *progname, uint8_t endianness) {
    if (!lengthRemaining (thePDU, 0, progname)) {
        return false;
    }
    GUIDPREFIX_RTPS guidprefix;
    if (!parseGUIDPREFIX (&guidprefix, thePDU, progname, BIGENDIAN)) {
        return false;
    }
    virtualguid_rtps->guidprefix = guidprefix;
    ENTITYID_RTPS virtualguidsuffix;
    if (!parseENTITYID (&virtualguidsuffix, thePDU, progname, BIGENDIAN)) {
        return false;
    }
    virtualguid_rtps->virtualguidsuffix = virtualguidsuffix;
    return true;
}

bool parsePIDGROUPENTITYID (PIDGROUPENTITYID_RTPS *pidgroupentityid_rtps, PDU *thePDU, char *progname, uint8_t endianness) {
    if (!lengthRemaining (thePDU, 4, progname)) {
        return false;
    }
    pidgroupentityid_rtps->parameterkind = get16_e (thePDU, endianness);
    if (!(pidgroupentityid_rtps->parameterkind == 83)) {
        return false;
    }
    pidgroupentityid_rtps->parameterlength = get16_e (thePDU, endianness);
    unsigned long pos = thePDU->curPos;
    if (!lengthRemaining (thePDU, pidgroupentityid_rtps->parameterlength, progname)) {
        return false;
    }
    PDU constrainedPDU;
    constrainedPDU.data = thePDU->data;
    constrainedPDU.len = pidgroupentityid_rtps->parameterlength;
    constrainedPDU.watermark = thePDU->watermark;
    constrainedPDU.curPos = pos;
    constrainedPDU.curBitPos = 0;
    constrainedPDU.remaining = pidgroupentityid_rtps->parameterlength;
    ENTITYID_RTPS groupentityid;
    if (!parseENTITYID (&groupentityid, &constrainedPDU, progname, endianness)) {
        return false;
    }
    pidgroupentityid_rtps->groupentityid = groupentityid;
    thePDU->curPos += constrainedPDU.len;
    return true;
}

bool parsePIDGROUPENTITYID_O (PIDGROUPENTITYID_RTPS *pidgroupentityid_rtps, PDU *thePDU, char *progname, uint16_t *type, uint8_t endianness) {
    pidgroupentityid_rtps->parameterkind = *type;
    if (!lengthRemaining (thePDU, 2, progname)) {
        return false;
    }
    pidgroupentityid_rtps->parameterlength = get16_e (thePDU, endianness);
    unsigned long pos = thePDU->curPos;
    if (!lengthRemaining (thePDU, pidgroupentityid_rtps->parameterlength, progname)) {
        return false;
    }
    PDU constrainedPDU;
    constrainedPDU.data = thePDU->data;
    constrainedPDU.len = pidgroupentityid_rtps->parameterlength;
    constrainedPDU.watermark = thePDU->watermark;
    constrainedPDU.curPos = pos;
    constrainedPDU.curBitPos = 0;
    constrainedPDU.remaining = pidgroupentityid_rtps->parameterlength;
    ENTITYID_RTPS groupentityid;
    if (!parseENTITYID (&groupentityid, &constrainedPDU, progname, endianness)) {
        return false;
    }
    pidgroupentityid_rtps->groupentityid = groupentityid;
    thePDU->curPos += constrainedPDU.len;
    return true;
}

bool parsePIDLATENCYBUDGET (PIDLATENCYBUDGET_RTPS *pidlatencybudget_rtps, PDU *thePDU, char *progname, uint8_t endianness) {
    if (!lengthRemaining (thePDU, 4, progname)) {
        return false;
    }
    pidlatencybudget_rtps->leaseduration = NULL;
    pidlatencybudget_rtps->parameterkind = get16_e (thePDU, endianness);
    if (!(pidlatencybudget_rtps->parameterkind == 39)) {
        return false;
    }
    pidlatencybudget_rtps->parameterlength = get16_e (thePDU, endianness);
    unsigned long remaining = thePDU->remaining;
    if (!lengthRemaining (thePDU, pidlatencybudget_rtps->parameterlength, progname)) {
        return false;
    }
    pidlatencybudget_rtps->leaseduration = (unsigned char *) malloc (sizeof (unsigned char) * (pidlatencybudget_rtps->parameterlength));
    if (pidlatencybudget_rtps->leaseduration == NULL) {
        fprintf (stderr, "%s: internal malloc error file: %s line: %d \n", progname, __FILE__, __LINE__);
        return false;
    }
    pidlatencybudget_rtps->leaseduration_length = pidlatencybudget_rtps->parameterlength;
    memcpy (pidlatencybudget_rtps->leaseduration, &thePDU->data[thePDU->curPos], pidlatencybudget_rtps->parameterlength);
    thePDU->curPos += pidlatencybudget_rtps->parameterlength;
    if (pidlatencybudget_rtps->leaseduration[pidlatencybudget_rtps->parameterlength - 1] != '\0') {
    }
    return true;
}

bool parsePIDLATENCYBUDGET_O (PIDLATENCYBUDGET_RTPS *pidlatencybudget_rtps, PDU *thePDU, char *progname, uint16_t *type, uint8_t endianness) {
    pidlatencybudget_rtps->parameterkind = *type;
    if (!lengthRemaining (thePDU, 2, progname)) {
        return false;
    }
    pidlatencybudget_rtps->leaseduration = NULL;
    pidlatencybudget_rtps->parameterlength = get16_e (thePDU, endianness);
    unsigned long remaining = thePDU->remaining;
    if (!lengthRemaining (thePDU, pidlatencybudget_rtps->parameterlength, progname)) {
        return false;
    }
    pidlatencybudget_rtps->leaseduration = (unsigned char *) malloc (sizeof (unsigned char) * (pidlatencybudget_rtps->parameterlength));
    if (pidlatencybudget_rtps->leaseduration == NULL) {
        fprintf (stderr, "%s: internal malloc error file: %s line: %d \n", progname, __FILE__, __LINE__);
        return false;
    }
    pidlatencybudget_rtps->leaseduration_length = pidlatencybudget_rtps->parameterlength;
    memcpy (pidlatencybudget_rtps->leaseduration, &thePDU->data[thePDU->curPos], pidlatencybudget_rtps->parameterlength);
    thePDU->curPos += pidlatencybudget_rtps->parameterlength;
    if (pidlatencybudget_rtps->leaseduration[pidlatencybudget_rtps->parameterlength - 1] != '\0') {
    }
    return true;
}

bool parsePIDDEADLINE (PIDDEADLINE_RTPS *piddeadline_rtps, PDU *thePDU, char *progname, uint8_t endianness) {
    if (!lengthRemaining (thePDU, 4, progname)) {
        return false;
    }
    piddeadline_rtps->leaseduration = NULL;
    piddeadline_rtps->parameterkind = get16_e (thePDU, endianness);
    if (!(piddeadline_rtps->parameterkind == 35)) {
        return false;
    }
    piddeadline_rtps->parameterlength = get16_e (thePDU, endianness);
    unsigned long remaining = thePDU->remaining;
    if (!lengthRemaining (thePDU, piddeadline_rtps->parameterlength, progname)) {
        return false;
    }
    piddeadline_rtps->leaseduration = (unsigned char *) malloc (sizeof (unsigned char) * (piddeadline_rtps->parameterlength));
    if (piddeadline_rtps->leaseduration == NULL) {
        fprintf (stderr, "%s: internal malloc error file: %s line: %d \n", progname, __FILE__, __LINE__);
        return false;
    }
    piddeadline_rtps->leaseduration_length = piddeadline_rtps->parameterlength;
    memcpy (piddeadline_rtps->leaseduration, &thePDU->data[thePDU->curPos], piddeadline_rtps->parameterlength);
    thePDU->curPos += piddeadline_rtps->parameterlength;
    if (piddeadline_rtps->leaseduration[piddeadline_rtps->parameterlength - 1] != '\0') {
    }
    return true;
}

bool parsePIDDEADLINE_O (PIDDEADLINE_RTPS *piddeadline_rtps, PDU *thePDU, char *progname, uint16_t *type, uint8_t endianness) {
    piddeadline_rtps->parameterkind = *type;
    if (!lengthRemaining (thePDU, 2, progname)) {
        return false;
    }
    piddeadline_rtps->leaseduration = NULL;
    piddeadline_rtps->parameterlength = get16_e (thePDU, endianness);
    unsigned long remaining = thePDU->remaining;
    if (!lengthRemaining (thePDU, piddeadline_rtps->parameterlength, progname)) {
        return false;
    }
    piddeadline_rtps->leaseduration = (unsigned char *) malloc (sizeof (unsigned char) * (piddeadline_rtps->parameterlength));
    if (piddeadline_rtps->leaseduration == NULL) {
        fprintf (stderr, "%s: internal malloc error file: %s line: %d \n", progname, __FILE__, __LINE__);
        return false;
    }
    piddeadline_rtps->leaseduration_length = piddeadline_rtps->parameterlength;
    memcpy (piddeadline_rtps->leaseduration, &thePDU->data[thePDU->curPos], piddeadline_rtps->parameterlength);
    thePDU->curPos += piddeadline_rtps->parameterlength;
    if (piddeadline_rtps->leaseduration[piddeadline_rtps->parameterlength - 1] != '\0') {
    }
    return true;
}

bool parsePIDDESTINATIONORDER (PIDDESTINATIONORDER_RTPS *piddestinationorder_rtps, PDU *thePDU, char *progname, uint8_t endianness) {
    if (!lengthRemaining (thePDU, 4, progname)) {
        return false;
    }
    piddestinationorder_rtps->kind = NULL;
    piddestinationorder_rtps->parameterkind = get16_e (thePDU, endianness);
    if (!(piddestinationorder_rtps->parameterkind == 37)) {
        return false;
    }
    piddestinationorder_rtps->parameterlength = get16_e (thePDU, endianness);
    unsigned long remaining = thePDU->remaining;
    if (!lengthRemaining (thePDU, piddestinationorder_rtps->parameterlength, progname)) {
        return false;
    }
    piddestinationorder_rtps->kind = (unsigned char *) malloc (sizeof (unsigned char) * (piddestinationorder_rtps->parameterlength));
    if (piddestinationorder_rtps->kind == NULL) {
        fprintf (stderr, "%s: internal malloc error file: %s line: %d \n", progname, __FILE__, __LINE__);
        return false;
    }
    piddestinationorder_rtps->kind_length = piddestinationorder_rtps->parameterlength;
    memcpy (piddestinationorder_rtps->kind, &thePDU->data[thePDU->curPos], piddestinationorder_rtps->parameterlength);
    thePDU->curPos += piddestinationorder_rtps->parameterlength;
    if (piddestinationorder_rtps->kind[piddestinationorder_rtps->parameterlength - 1] != '\0') {
    }
    return true;
}

bool parsePIDDESTINATIONORDER_O (PIDDESTINATIONORDER_RTPS *piddestinationorder_rtps, PDU *thePDU, char *progname, uint16_t *type, uint8_t endianness) {
    piddestinationorder_rtps->parameterkind = *type;
    if (!lengthRemaining (thePDU, 2, progname)) {
        return false;
    }
    piddestinationorder_rtps->kind = NULL;
    piddestinationorder_rtps->parameterlength = get16_e (thePDU, endianness);
    unsigned long remaining = thePDU->remaining;
    if (!lengthRemaining (thePDU, piddestinationorder_rtps->parameterlength, progname)) {
        return false;
    }
    piddestinationorder_rtps->kind = (unsigned char *) malloc (sizeof (unsigned char) * (piddestinationorder_rtps->parameterlength));
    if (piddestinationorder_rtps->kind == NULL) {
        fprintf (stderr, "%s: internal malloc error file: %s line: %d \n", progname, __FILE__, __LINE__);
        return false;
    }
    piddestinationorder_rtps->kind_length = piddestinationorder_rtps->parameterlength;
    memcpy (piddestinationorder_rtps->kind, &thePDU->data[thePDU->curPos], piddestinationorder_rtps->parameterlength);
    thePDU->curPos += piddestinationorder_rtps->parameterlength;
    if (piddestinationorder_rtps->kind[piddestinationorder_rtps->parameterlength - 1] != '\0') {
    }
    return true;
}

bool parsePIDPRESENTATION (PIDPRESENTATION_RTPS *pidpresentation_rtps, PDU *thePDU, char *progname, uint8_t endianness) {
    if (!lengthRemaining (thePDU, 4, progname)) {
        return false;
    }
    pidpresentation_rtps->parameterkind = get16_e (thePDU, endianness);
    if (!(pidpresentation_rtps->parameterkind == 33)) {
        return false;
    }
    pidpresentation_rtps->parameterlength = get16_e (thePDU, endianness);
    unsigned long pos = thePDU->curPos;
    if (!lengthRemaining (thePDU, pidpresentation_rtps->parameterlength, progname)) {
        return false;
    }
    PDU constrainedPDU;
    constrainedPDU.data = thePDU->data;
    constrainedPDU.len = pidpresentation_rtps->parameterlength;
    constrainedPDU.watermark = thePDU->watermark;
    constrainedPDU.curPos = pos;
    constrainedPDU.curBitPos = 0;
    constrainedPDU.remaining = pidpresentation_rtps->parameterlength;
    PRESENTATION_RTPS presentation;
    if (!parsePRESENTATION (&presentation, &constrainedPDU, progname, endianness)) {
        return false;
    }
    pidpresentation_rtps->presentation = presentation;
    thePDU->curPos += constrainedPDU.len;
    return true;
}

bool parsePIDPRESENTATION_O (PIDPRESENTATION_RTPS *pidpresentation_rtps, PDU *thePDU, char *progname, uint16_t *type, uint8_t endianness) {
    pidpresentation_rtps->parameterkind = *type;
    if (!lengthRemaining (thePDU, 2, progname)) {
        return false;
    }
    pidpresentation_rtps->parameterlength = get16_e (thePDU, endianness);
    unsigned long pos = thePDU->curPos;
    if (!lengthRemaining (thePDU, pidpresentation_rtps->parameterlength, progname)) {
        return false;
    }
    PDU constrainedPDU;
    constrainedPDU.data = thePDU->data;
    constrainedPDU.len = pidpresentation_rtps->parameterlength;
    constrainedPDU.watermark = thePDU->watermark;
    constrainedPDU.curPos = pos;
    constrainedPDU.curBitPos = 0;
    constrainedPDU.remaining = pidpresentation_rtps->parameterlength;
    PRESENTATION_RTPS presentation;
    if (!parsePRESENTATION (&presentation, &constrainedPDU, progname, endianness)) {
        return false;
    }
    pidpresentation_rtps->presentation = presentation;
    thePDU->curPos += constrainedPDU.len;
    return true;
}

bool parsePRESENTATION (PRESENTATION_RTPS *presentation_rtps, PDU *thePDU, char *progname, uint8_t endianness) {
    if (!lengthRemaining (thePDU, 6, progname)) {
        return false;
    }
    presentation_rtps->accessscope = get32_e (thePDU, endianness);
    presentation_rtps->coherentaccess = get8_e (thePDU, endianness);
    presentation_rtps->orderedaccess = get8_e (thePDU, endianness);
    return true;
}

bool parsePIDOWNERSHIP (PIDOWNERSHIP_RTPS *pidownership_rtps, PDU *thePDU, char *progname, uint8_t endianness) {
    if (!lengthRemaining (thePDU, 4, progname)) {
        return false;
    }
    pidownership_rtps->kind = NULL;
    pidownership_rtps->parameterkind = get16_e (thePDU, endianness);
    if (!(pidownership_rtps->parameterkind == 31)) {
        return false;
    }
    pidownership_rtps->parameterlength = get16_e (thePDU, endianness);
    unsigned long remaining = thePDU->remaining;
    if (!lengthRemaining (thePDU, pidownership_rtps->parameterlength, progname)) {
        return false;
    }
    pidownership_rtps->kind = (unsigned char *) malloc (sizeof (unsigned char) * (pidownership_rtps->parameterlength));
    if (pidownership_rtps->kind == NULL) {
        fprintf (stderr, "%s: internal malloc error file: %s line: %d \n", progname, __FILE__, __LINE__);
        return false;
    }
    pidownership_rtps->kind_length = pidownership_rtps->parameterlength;
    memcpy (pidownership_rtps->kind, &thePDU->data[thePDU->curPos], pidownership_rtps->parameterlength);
    thePDU->curPos += pidownership_rtps->parameterlength;
    if (pidownership_rtps->kind[pidownership_rtps->parameterlength - 1] != '\0') {
    }
    return true;
}

bool parsePIDOWNERSHIP_O (PIDOWNERSHIP_RTPS *pidownership_rtps, PDU *thePDU, char *progname, uint16_t *type, uint8_t endianness) {
    pidownership_rtps->parameterkind = *type;
    if (!lengthRemaining (thePDU, 2, progname)) {
        return false;
    }
    pidownership_rtps->kind = NULL;
    pidownership_rtps->parameterlength = get16_e (thePDU, endianness);
    unsigned long remaining = thePDU->remaining;
    if (!lengthRemaining (thePDU, pidownership_rtps->parameterlength, progname)) {
        return false;
    }
    pidownership_rtps->kind = (unsigned char *) malloc (sizeof (unsigned char) * (pidownership_rtps->parameterlength));
    if (pidownership_rtps->kind == NULL) {
        fprintf (stderr, "%s: internal malloc error file: %s line: %d \n", progname, __FILE__, __LINE__);
        return false;
    }
    pidownership_rtps->kind_length = pidownership_rtps->parameterlength;
    memcpy (pidownership_rtps->kind, &thePDU->data[thePDU->curPos], pidownership_rtps->parameterlength);
    thePDU->curPos += pidownership_rtps->parameterlength;
    if (pidownership_rtps->kind[pidownership_rtps->parameterlength - 1] != '\0') {
    }
    return true;
}

bool parsePIDDIRECTCOMMUNICATION (PIDDIRECTCOMMUNICATION_RTPS *piddirectcommunication_rtps, PDU *thePDU, char *progname, uint8_t endianness) {
    if (!lengthRemaining (thePDU, 4, progname)) {
        return false;
    }
    piddirectcommunication_rtps->parameterkind = get16_e (thePDU, endianness);
    if (!(piddirectcommunication_rtps->parameterkind == 32785)) {
        return false;
    }
    piddirectcommunication_rtps->parameterlength = get16_e (thePDU, endianness);
    unsigned long pos = thePDU->curPos;
    if (!lengthRemaining (thePDU, piddirectcommunication_rtps->parameterlength, progname)) {
        return false;
    }
    PDU constrainedPDU;
    constrainedPDU.data = thePDU->data;
    constrainedPDU.len = piddirectcommunication_rtps->parameterlength;
    constrainedPDU.watermark = thePDU->watermark;
    constrainedPDU.curPos = pos;
    constrainedPDU.curBitPos = 0;
    constrainedPDU.remaining = piddirectcommunication_rtps->parameterlength;
    DIRECTCOMMUNICATION_RTPS directcommunication;
    if (!parseDIRECTCOMMUNICATION (&directcommunication, &constrainedPDU, progname, endianness)) {
        return false;
    }
    piddirectcommunication_rtps->directcommunication = directcommunication;
    thePDU->curPos += constrainedPDU.len;
    return true;
}

bool parsePIDDIRECTCOMMUNICATION_O (PIDDIRECTCOMMUNICATION_RTPS *piddirectcommunication_rtps, PDU *thePDU, char *progname, uint16_t *type, uint8_t endianness) {
    piddirectcommunication_rtps->parameterkind = *type;
    if (!lengthRemaining (thePDU, 2, progname)) {
        return false;
    }
    piddirectcommunication_rtps->parameterlength = get16_e (thePDU, endianness);
    unsigned long pos = thePDU->curPos;
    if (!lengthRemaining (thePDU, piddirectcommunication_rtps->parameterlength, progname)) {
        return false;
    }
    PDU constrainedPDU;
    constrainedPDU.data = thePDU->data;
    constrainedPDU.len = piddirectcommunication_rtps->parameterlength;
    constrainedPDU.watermark = thePDU->watermark;
    constrainedPDU.curPos = pos;
    constrainedPDU.curBitPos = 0;
    constrainedPDU.remaining = piddirectcommunication_rtps->parameterlength;
    DIRECTCOMMUNICATION_RTPS directcommunication;
    if (!parseDIRECTCOMMUNICATION (&directcommunication, &constrainedPDU, progname, endianness)) {
        return false;
    }
    piddirectcommunication_rtps->directcommunication = directcommunication;
    thePDU->curPos += constrainedPDU.len;
    return true;
}

bool parseDIRECTCOMMUNICATION (DIRECTCOMMUNICATION_RTPS *directcommunication_rtps, PDU *thePDU, char *progname, uint8_t endianness) {
    if (!lengthRemaining (thePDU, 1, progname)) {
        return false;
    }
    directcommunication_rtps->directcommunication = get8_e (thePDU, endianness);
    return true;
}

bool parsePIDDURABILITY (PIDDURABILITY_RTPS *piddurability_rtps, PDU *thePDU, char *progname, uint8_t endianness) {
    if (!lengthRemaining (thePDU, 4, progname)) {
        return false;
    }
    piddurability_rtps->durability = NULL;
    piddurability_rtps->parameterkind = get16_e (thePDU, endianness);
    if (!(piddurability_rtps->parameterkind == 29)) {
        return false;
    }
    piddurability_rtps->parameterlength = get16_e (thePDU, endianness);
    unsigned long remaining = thePDU->remaining;
    if (!lengthRemaining (thePDU, piddurability_rtps->parameterlength, progname)) {
        return false;
    }
    piddurability_rtps->durability = (unsigned char *) malloc (sizeof (unsigned char) * (piddurability_rtps->parameterlength));
    if (piddurability_rtps->durability == NULL) {
        fprintf (stderr, "%s: internal malloc error file: %s line: %d \n", progname, __FILE__, __LINE__);
        return false;
    }
    piddurability_rtps->durability_length = piddurability_rtps->parameterlength;
    memcpy (piddurability_rtps->durability, &thePDU->data[thePDU->curPos], piddurability_rtps->parameterlength);
    thePDU->curPos += piddurability_rtps->parameterlength;
    if (piddurability_rtps->durability[piddurability_rtps->parameterlength - 1] != '\0') {
    }
    return true;
}

bool parsePIDDURABILITY_O (PIDDURABILITY_RTPS *piddurability_rtps, PDU *thePDU, char *progname, uint16_t *type, uint8_t endianness) {
    piddurability_rtps->parameterkind = *type;
    if (!lengthRemaining (thePDU, 2, progname)) {
        return false;
    }
    piddurability_rtps->durability = NULL;
    piddurability_rtps->parameterlength = get16_e (thePDU, endianness);
    unsigned long remaining = thePDU->remaining;
    if (!lengthRemaining (thePDU, piddurability_rtps->parameterlength, progname)) {
        return false;
    }
    piddurability_rtps->durability = (unsigned char *) malloc (sizeof (unsigned char) * (piddurability_rtps->parameterlength));
    if (piddurability_rtps->durability == NULL) {
        fprintf (stderr, "%s: internal malloc error file: %s line: %d \n", progname, __FILE__, __LINE__);
        return false;
    }
    piddurability_rtps->durability_length = piddurability_rtps->parameterlength;
    memcpy (piddurability_rtps->durability, &thePDU->data[thePDU->curPos], piddurability_rtps->parameterlength);
    thePDU->curPos += piddurability_rtps->parameterlength;
    if (piddurability_rtps->durability[piddurability_rtps->parameterlength - 1] != '\0') {
    }
    return true;
}

bool parsePIDLIVELINESS (PIDLIVELINESS_RTPS *pidliveliness_rtps, PDU *thePDU, char *progname, uint8_t endianness) {
    if (!lengthRemaining (thePDU, 4, progname)) {
        return false;
    }
    pidliveliness_rtps->liveliness = NULL;
    pidliveliness_rtps->parameterkind = get16_e (thePDU, endianness);
    if (!(pidliveliness_rtps->parameterkind == 27)) {
        return false;
    }
    pidliveliness_rtps->parameterlength = get16_e (thePDU, endianness);
    unsigned long remaining = thePDU->remaining;
    if (!lengthRemaining (thePDU, pidliveliness_rtps->parameterlength, progname)) {
        return false;
    }
    pidliveliness_rtps->liveliness = (unsigned char *) malloc (sizeof (unsigned char) * (pidliveliness_rtps->parameterlength));
    if (pidliveliness_rtps->liveliness == NULL) {
        fprintf (stderr, "%s: internal malloc error file: %s line: %d \n", progname, __FILE__, __LINE__);
        return false;
    }
    pidliveliness_rtps->liveliness_length = pidliveliness_rtps->parameterlength;
    memcpy (pidliveliness_rtps->liveliness, &thePDU->data[thePDU->curPos], pidliveliness_rtps->parameterlength);
    thePDU->curPos += pidliveliness_rtps->parameterlength;
    if (pidliveliness_rtps->liveliness[pidliveliness_rtps->parameterlength - 1] != '\0') {
    }
    return true;
}

bool parsePIDLIVELINESS_O (PIDLIVELINESS_RTPS *pidliveliness_rtps, PDU *thePDU, char *progname, uint16_t *type, uint8_t endianness) {
    pidliveliness_rtps->parameterkind = *type;
    if (!lengthRemaining (thePDU, 2, progname)) {
        return false;
    }
    pidliveliness_rtps->liveliness = NULL;
    pidliveliness_rtps->parameterlength = get16_e (thePDU, endianness);
    unsigned long remaining = thePDU->remaining;
    if (!lengthRemaining (thePDU, pidliveliness_rtps->parameterlength, progname)) {
        return false;
    }
    pidliveliness_rtps->liveliness = (unsigned char *) malloc (sizeof (unsigned char) * (pidliveliness_rtps->parameterlength));
    if (pidliveliness_rtps->liveliness == NULL) {
        fprintf (stderr, "%s: internal malloc error file: %s line: %d \n", progname, __FILE__, __LINE__);
        return false;
    }
    pidliveliness_rtps->liveliness_length = pidliveliness_rtps->parameterlength;
    memcpy (pidliveliness_rtps->liveliness, &thePDU->data[thePDU->curPos], pidliveliness_rtps->parameterlength);
    thePDU->curPos += pidliveliness_rtps->parameterlength;
    if (pidliveliness_rtps->liveliness[pidliveliness_rtps->parameterlength - 1] != '\0') {
    }
    return true;
}

bool parsePIDTIMEBASEDFILTER (PIDTIMEBASEDFILTER_RTPS *pidtimebasedfilter_rtps, PDU *thePDU, char *progname, uint8_t endianness) {
    if (!lengthRemaining (thePDU, 4, progname)) {
        return false;
    }
    pidtimebasedfilter_rtps->leaseduration = NULL;
    pidtimebasedfilter_rtps->parameterkind = get16_e (thePDU, endianness);
    if (!(pidtimebasedfilter_rtps->parameterkind == 4)) {
        return false;
    }
    pidtimebasedfilter_rtps->parameterlength = get16_e (thePDU, endianness);
    unsigned long remaining = thePDU->remaining;
    if (!lengthRemaining (thePDU, pidtimebasedfilter_rtps->parameterlength, progname)) {
        return false;
    }
    pidtimebasedfilter_rtps->leaseduration = (unsigned char *) malloc (sizeof (unsigned char) * (pidtimebasedfilter_rtps->parameterlength));
    if (pidtimebasedfilter_rtps->leaseduration == NULL) {
        fprintf (stderr, "%s: internal malloc error file: %s line: %d \n", progname, __FILE__, __LINE__);
        return false;
    }
    pidtimebasedfilter_rtps->leaseduration_length = pidtimebasedfilter_rtps->parameterlength;
    memcpy (pidtimebasedfilter_rtps->leaseduration, &thePDU->data[thePDU->curPos], pidtimebasedfilter_rtps->parameterlength);
    thePDU->curPos += pidtimebasedfilter_rtps->parameterlength;
    if (pidtimebasedfilter_rtps->leaseduration[pidtimebasedfilter_rtps->parameterlength - 1] != '\0') {
    }
    return true;
}

bool parsePIDTIMEBASEDFILTER_O (PIDTIMEBASEDFILTER_RTPS *pidtimebasedfilter_rtps, PDU *thePDU, char *progname, uint16_t *type, uint8_t endianness) {
    pidtimebasedfilter_rtps->parameterkind = *type;
    if (!lengthRemaining (thePDU, 2, progname)) {
        return false;
    }
    pidtimebasedfilter_rtps->leaseduration = NULL;
    pidtimebasedfilter_rtps->parameterlength = get16_e (thePDU, endianness);
    unsigned long remaining = thePDU->remaining;
    if (!lengthRemaining (thePDU, pidtimebasedfilter_rtps->parameterlength, progname)) {
        return false;
    }
    pidtimebasedfilter_rtps->leaseduration = (unsigned char *) malloc (sizeof (unsigned char) * (pidtimebasedfilter_rtps->parameterlength));
    if (pidtimebasedfilter_rtps->leaseduration == NULL) {
        fprintf (stderr, "%s: internal malloc error file: %s line: %d \n", progname, __FILE__, __LINE__);
        return false;
    }
    pidtimebasedfilter_rtps->leaseduration_length = pidtimebasedfilter_rtps->parameterlength;
    memcpy (pidtimebasedfilter_rtps->leaseduration, &thePDU->data[thePDU->curPos], pidtimebasedfilter_rtps->parameterlength);
    thePDU->curPos += pidtimebasedfilter_rtps->parameterlength;
    if (pidtimebasedfilter_rtps->leaseduration[pidtimebasedfilter_rtps->parameterlength - 1] != '\0') {
    }
    return true;
}

bool parsePIDRECVQUEUE (PIDRECVQUEUE_RTPS *pidrecvqueue_rtps, PDU *thePDU, char *progname, uint8_t endianness) {
    if (!lengthRemaining (thePDU, 4, progname)) {
        return false;
    }
    pidrecvqueue_rtps->queuesize = NULL;
    pidrecvqueue_rtps->parameterkind = get16_e (thePDU, endianness);
    if (!(pidrecvqueue_rtps->parameterkind == 24)) {
        return false;
    }
    pidrecvqueue_rtps->parameterlength = get16_e (thePDU, endianness);
    unsigned long remaining = thePDU->remaining;
    if (!lengthRemaining (thePDU, pidrecvqueue_rtps->parameterlength, progname)) {
        return false;
    }
    pidrecvqueue_rtps->queuesize = (unsigned char *) malloc (sizeof (unsigned char) * (pidrecvqueue_rtps->parameterlength));
    if (pidrecvqueue_rtps->queuesize == NULL) {
        fprintf (stderr, "%s: internal malloc error file: %s line: %d \n", progname, __FILE__, __LINE__);
        return false;
    }
    pidrecvqueue_rtps->queuesize_length = pidrecvqueue_rtps->parameterlength;
    memcpy (pidrecvqueue_rtps->queuesize, &thePDU->data[thePDU->curPos], pidrecvqueue_rtps->parameterlength);
    thePDU->curPos += pidrecvqueue_rtps->parameterlength;
    if (pidrecvqueue_rtps->queuesize[pidrecvqueue_rtps->parameterlength - 1] != '\0') {
    }
    return true;
}

bool parsePIDRECVQUEUE_O (PIDRECVQUEUE_RTPS *pidrecvqueue_rtps, PDU *thePDU, char *progname, uint16_t *type, uint8_t endianness) {
    pidrecvqueue_rtps->parameterkind = *type;
    if (!lengthRemaining (thePDU, 2, progname)) {
        return false;
    }
    pidrecvqueue_rtps->queuesize = NULL;
    pidrecvqueue_rtps->parameterlength = get16_e (thePDU, endianness);
    unsigned long remaining = thePDU->remaining;
    if (!lengthRemaining (thePDU, pidrecvqueue_rtps->parameterlength, progname)) {
        return false;
    }
    pidrecvqueue_rtps->queuesize = (unsigned char *) malloc (sizeof (unsigned char) * (pidrecvqueue_rtps->parameterlength));
    if (pidrecvqueue_rtps->queuesize == NULL) {
        fprintf (stderr, "%s: internal malloc error file: %s line: %d \n", progname, __FILE__, __LINE__);
        return false;
    }
    pidrecvqueue_rtps->queuesize_length = pidrecvqueue_rtps->parameterlength;
    memcpy (pidrecvqueue_rtps->queuesize, &thePDU->data[thePDU->curPos], pidrecvqueue_rtps->parameterlength);
    thePDU->curPos += pidrecvqueue_rtps->parameterlength;
    if (pidrecvqueue_rtps->queuesize[pidrecvqueue_rtps->parameterlength - 1] != '\0') {
    }
    return true;
}

bool parsePIDACKKIND (PIDACKKIND_RTPS *pidackkind_rtps, PDU *thePDU, char *progname, uint8_t endianness) {
    if (!lengthRemaining (thePDU, 4, progname)) {
        return false;
    }
    pidackkind_rtps->ackkind = NULL;
    pidackkind_rtps->parameterkind = get16_e (thePDU, endianness);
    if (!(pidackkind_rtps->parameterkind == 32779)) {
        return false;
    }
    pidackkind_rtps->parameterlength = get16_e (thePDU, endianness);
    unsigned long remaining = thePDU->remaining;
    if (!lengthRemaining (thePDU, pidackkind_rtps->parameterlength, progname)) {
        return false;
    }
    pidackkind_rtps->ackkind = (unsigned char *) malloc (sizeof (unsigned char) * (pidackkind_rtps->parameterlength));
    if (pidackkind_rtps->ackkind == NULL) {
        fprintf (stderr, "%s: internal malloc error file: %s line: %d \n", progname, __FILE__, __LINE__);
        return false;
    }
    pidackkind_rtps->ackkind_length = pidackkind_rtps->parameterlength;
    memcpy (pidackkind_rtps->ackkind, &thePDU->data[thePDU->curPos], pidackkind_rtps->parameterlength);
    thePDU->curPos += pidackkind_rtps->parameterlength;
    if (pidackkind_rtps->ackkind[pidackkind_rtps->parameterlength - 1] != '\0') {
    }
    return true;
}

bool parsePIDACKKIND_O (PIDACKKIND_RTPS *pidackkind_rtps, PDU *thePDU, char *progname, uint16_t *type, uint8_t endianness) {
    pidackkind_rtps->parameterkind = *type;
    if (!lengthRemaining (thePDU, 2, progname)) {
        return false;
    }
    pidackkind_rtps->ackkind = NULL;
    pidackkind_rtps->parameterlength = get16_e (thePDU, endianness);
    unsigned long remaining = thePDU->remaining;
    if (!lengthRemaining (thePDU, pidackkind_rtps->parameterlength, progname)) {
        return false;
    }
    pidackkind_rtps->ackkind = (unsigned char *) malloc (sizeof (unsigned char) * (pidackkind_rtps->parameterlength));
    if (pidackkind_rtps->ackkind == NULL) {
        fprintf (stderr, "%s: internal malloc error file: %s line: %d \n", progname, __FILE__, __LINE__);
        return false;
    }
    pidackkind_rtps->ackkind_length = pidackkind_rtps->parameterlength;
    memcpy (pidackkind_rtps->ackkind, &thePDU->data[thePDU->curPos], pidackkind_rtps->parameterlength);
    thePDU->curPos += pidackkind_rtps->parameterlength;
    if (pidackkind_rtps->ackkind[pidackkind_rtps->parameterlength - 1] != '\0') {
    }
    return true;
}

bool parsePIDTOPICNAME (PIDTOPICNAME_RTPS *pidtopicname_rtps, PDU *thePDU, char *progname, uint8_t endianness) {
    if (!lengthRemaining (thePDU, 4, progname)) {
        return false;
    }
    pidtopicname_rtps->parameterkind = get16_e (thePDU, endianness);
    if (!(pidtopicname_rtps->parameterkind == 5)) {
        return false;
    }
    pidtopicname_rtps->parameterlength = get16_e (thePDU, endianness);
    unsigned long pos = thePDU->curPos;
    if (!lengthRemaining (thePDU, pidtopicname_rtps->parameterlength, progname)) {
        return false;
    }
    PDU constrainedPDU;
    constrainedPDU.data = thePDU->data;
    constrainedPDU.len = pidtopicname_rtps->parameterlength;
    constrainedPDU.watermark = thePDU->watermark;
    constrainedPDU.curPos = pos;
    constrainedPDU.curBitPos = 0;
    constrainedPDU.remaining = pidtopicname_rtps->parameterlength;
    NESTEDSTRING_RTPS topicname;
    if (!parseNESTEDSTRING (&topicname, &constrainedPDU, progname, endianness)) {
        return false;
    }
    pidtopicname_rtps->topicname = topicname;
    thePDU->curPos += constrainedPDU.len;
    return true;
}

bool parsePIDTOPICNAME_O (PIDTOPICNAME_RTPS *pidtopicname_rtps, PDU *thePDU, char *progname, uint16_t *type, uint8_t endianness) {
    pidtopicname_rtps->parameterkind = *type;
    if (!lengthRemaining (thePDU, 2, progname)) {
        return false;
    }
    pidtopicname_rtps->parameterlength = get16_e (thePDU, endianness);
    unsigned long pos = thePDU->curPos;
    if (!lengthRemaining (thePDU, pidtopicname_rtps->parameterlength, progname)) {
        return false;
    }
    PDU constrainedPDU;
    constrainedPDU.data = thePDU->data;
    constrainedPDU.len = pidtopicname_rtps->parameterlength;
    constrainedPDU.watermark = thePDU->watermark;
    constrainedPDU.curPos = pos;
    constrainedPDU.curBitPos = 0;
    constrainedPDU.remaining = pidtopicname_rtps->parameterlength;
    NESTEDSTRING_RTPS topicname;
    if (!parseNESTEDSTRING (&topicname, &constrainedPDU, progname, endianness)) {
        return false;
    }
    pidtopicname_rtps->topicname = topicname;
    thePDU->curPos += constrainedPDU.len;
    return true;
}

bool parsePIDUNKNOWN (PIDUNKNOWN_RTPS *pidunknown_rtps, PDU *thePDU, char *progname, uint8_t endianness) {
    if (!lengthRemaining (thePDU, 20, progname)) {
        return false;
    }
    pidunknown_rtps->parameterkind = get16_e (thePDU, endianness);
    if (!(pidunknown_rtps->parameterkind == 45058)) {
        return false;
    }
    memcpy (pidunknown_rtps->slackbytes, &thePDU->data[thePDU->curPos], 18);
    thePDU->curPos += 18;
    if (pidunknown_rtps->slackbytes[18 - 1] != '\0') {
    }
    return true;
}

bool parsePIDUNKNOWN_O (PIDUNKNOWN_RTPS *pidunknown_rtps, PDU *thePDU, char *progname, uint16_t *type, uint8_t endianness) {
    pidunknown_rtps->parameterkind = *type;
    if (!lengthRemaining (thePDU, 18, progname)) {
        return false;
    }
    memcpy (pidunknown_rtps->slackbytes, &thePDU->data[thePDU->curPos], 18);
    thePDU->curPos += 18;
    if (pidunknown_rtps->slackbytes[18 - 1] != '\0') {
    }
    return true;
}

bool parsePIDTYPENAME (PIDTYPENAME_RTPS *pidtypename_rtps, PDU *thePDU, char *progname, uint8_t endianness) {
    if (!lengthRemaining (thePDU, 4, progname)) {
        return false;
    }
    pidtypename_rtps->parameterkind = get16_e (thePDU, endianness);
    if (!(pidtypename_rtps->parameterkind == 7)) {
        return false;
    }
    pidtypename_rtps->parameterlength = get16_e (thePDU, endianness);
    unsigned long pos = thePDU->curPos;
    if (!lengthRemaining (thePDU, pidtypename_rtps->parameterlength, progname)) {
        return false;
    }
    PDU constrainedPDU;
    constrainedPDU.data = thePDU->data;
    constrainedPDU.len = pidtypename_rtps->parameterlength;
    constrainedPDU.watermark = thePDU->watermark;
    constrainedPDU.curPos = pos;
    constrainedPDU.curBitPos = 0;
    constrainedPDU.remaining = pidtypename_rtps->parameterlength;
    NESTEDSTRING_RTPS typename;
    if (!parseNESTEDSTRING (&typename, &constrainedPDU, progname, endianness)) {
        return false;
    }
    pidtypename_rtps->typename = typename;
    thePDU->curPos += constrainedPDU.len;
    return true;
}

bool parsePIDTYPENAME_O (PIDTYPENAME_RTPS *pidtypename_rtps, PDU *thePDU, char *progname, uint16_t *type, uint8_t endianness) {
    pidtypename_rtps->parameterkind = *type;
    if (!lengthRemaining (thePDU, 2, progname)) {
        return false;
    }
    pidtypename_rtps->parameterlength = get16_e (thePDU, endianness);
    unsigned long pos = thePDU->curPos;
    if (!lengthRemaining (thePDU, pidtypename_rtps->parameterlength, progname)) {
        return false;
    }
    PDU constrainedPDU;
    constrainedPDU.data = thePDU->data;
    constrainedPDU.len = pidtypename_rtps->parameterlength;
    constrainedPDU.watermark = thePDU->watermark;
    constrainedPDU.curPos = pos;
    constrainedPDU.curBitPos = 0;
    constrainedPDU.remaining = pidtypename_rtps->parameterlength;
    NESTEDSTRING_RTPS typename;
    if (!parseNESTEDSTRING (&typename, &constrainedPDU, progname, endianness)) {
        return false;
    }
    pidtypename_rtps->typename = typename;
    thePDU->curPos += constrainedPDU.len;
    return true;
}

bool parseNESTEDSTRING (NESTEDSTRING_RTPS *nestedstring_rtps, PDU *thePDU, char *progname, uint8_t endianness) {
    if (!lengthRemaining (thePDU, 4, progname)) {
        return false;
    }
    nestedstring_rtps->name = NULL;
    nestedstring_rtps->namelength = get32_e (thePDU, endianness);
    unsigned long remaining = thePDU->remaining;
    if (!lengthRemaining (thePDU, nestedstring_rtps->namelength, progname)) {
        return false;
    }
    nestedstring_rtps->name = (unsigned char *) malloc (sizeof (unsigned char) * (nestedstring_rtps->namelength));
    if (nestedstring_rtps->name == NULL) {
        fprintf (stderr, "%s: internal malloc error file: %s line: %d \n", progname, __FILE__, __LINE__);
        return false;
    }
    nestedstring_rtps->name_length = nestedstring_rtps->namelength;
    memcpy (nestedstring_rtps->name, &thePDU->data[thePDU->curPos], nestedstring_rtps->namelength);
    thePDU->curPos += nestedstring_rtps->namelength;
    if (nestedstring_rtps->name[nestedstring_rtps->namelength - 1] != '\0') {
    }
    return true;
}

bool parsePIDRELIABILITY (PIDRELIABILITY_RTPS *pidreliability_rtps, PDU *thePDU, char *progname, uint8_t endianness) {
    if (!lengthRemaining (thePDU, 8, progname)) {
        return false;
    }
    pidreliability_rtps->slack = NULL;
    pidreliability_rtps->parameterkind = get16_e (thePDU, endianness);
    if (!(pidreliability_rtps->parameterkind == 26)) {
        return false;
    }
    pidreliability_rtps->parameterlength = get16_e (thePDU, endianness);
    pidreliability_rtps->reliabilityqos = get32_e (thePDU, endianness);
    unsigned long remaining = thePDU->remaining;
    if (!lengthRemaining (thePDU, pidreliability_rtps->parameterlength - sizeof (pidreliability_rtps->reliabilityqos), progname)) {
        return false;
    }
    pidreliability_rtps->slack = (unsigned char *) malloc (sizeof (unsigned char) * (pidreliability_rtps->parameterlength - sizeof (
      pidreliability_rtps->reliabilityqos)));
    if (pidreliability_rtps->slack == NULL) {
        fprintf (stderr, "%s: internal malloc error file: %s line: %d \n", progname, __FILE__, __LINE__);
        return false;
    }
    pidreliability_rtps->slack_length = pidreliability_rtps->parameterlength - sizeof (pidreliability_rtps->reliabilityqos);
    memcpy (pidreliability_rtps->slack, &thePDU->data[thePDU->curPos], pidreliability_rtps->parameterlength - sizeof (pidreliability_rtps->reliabilityqos));
    thePDU->curPos += pidreliability_rtps->parameterlength - sizeof (pidreliability_rtps->reliabilityqos);
    if (pidreliability_rtps->slack[pidreliability_rtps->parameterlength - sizeof (pidreliability_rtps->reliabilityqos) - 1] != '\0') {
    }
    return true;
}

bool parsePIDRELIABILITY_O (PIDRELIABILITY_RTPS *pidreliability_rtps, PDU *thePDU, char *progname, uint16_t *type, uint8_t endianness) {
    pidreliability_rtps->parameterkind = *type;
    if (!lengthRemaining (thePDU, 6, progname)) {
        return false;
    }
    pidreliability_rtps->slack = NULL;
    pidreliability_rtps->parameterlength = get16_e (thePDU, endianness);
    pidreliability_rtps->reliabilityqos = get32_e (thePDU, endianness);
    unsigned long remaining = thePDU->remaining;
    if (!lengthRemaining (thePDU, pidreliability_rtps->parameterlength - sizeof (pidreliability_rtps->reliabilityqos), progname)) {
        return false;
    }
    pidreliability_rtps->slack = (unsigned char *) malloc (sizeof (unsigned char) * (pidreliability_rtps->parameterlength - sizeof (
      pidreliability_rtps->reliabilityqos)));
    if (pidreliability_rtps->slack == NULL) {
        fprintf (stderr, "%s: internal malloc error file: %s line: %d \n", progname, __FILE__, __LINE__);
        return false;
    }
    pidreliability_rtps->slack_length = pidreliability_rtps->parameterlength - sizeof (pidreliability_rtps->reliabilityqos);
    memcpy (pidreliability_rtps->slack, &thePDU->data[thePDU->curPos], pidreliability_rtps->parameterlength - sizeof (pidreliability_rtps->reliabilityqos));
    thePDU->curPos += pidreliability_rtps->parameterlength - sizeof (pidreliability_rtps->reliabilityqos);
    if (pidreliability_rtps->slack[pidreliability_rtps->parameterlength - sizeof (pidreliability_rtps->reliabilityqos) - 1] != '\0') {
    }
    return true;
}

bool parsePIDENDPOINTGUID (PIDENDPOINTGUID_RTPS *pidendpointguid_rtps, PDU *thePDU, char *progname, uint8_t endianness) {
    if (!lengthRemaining (thePDU, 4, progname)) {
        return false;
    }
    pidendpointguid_rtps->parameterkind = get16_e (thePDU, endianness);
    if (!(pidendpointguid_rtps->parameterkind == 90)) {
        return false;
    }
    pidendpointguid_rtps->parameterlength = get16_e (thePDU, endianness);
    GUIDPREFIX_RTPS participantguid;
    if (!parseGUIDPREFIX (&participantguid, thePDU, progname, BIGENDIAN)) {
        return false;
    }
    pidendpointguid_rtps->participantguid = participantguid;
    ENTITYID_RTPS entityid;
    if (!parseENTITYID (&entityid, thePDU, progname, BIGENDIAN)) {
        return false;
    }
    pidendpointguid_rtps->entityid = entityid;
    return true;
}

bool parsePIDENDPOINTGUID_O (PIDENDPOINTGUID_RTPS *pidendpointguid_rtps, PDU *thePDU, char *progname, uint16_t *type, uint8_t endianness) {
    pidendpointguid_rtps->parameterkind = *type;
    if (!lengthRemaining (thePDU, 2, progname)) {
        return false;
    }
    pidendpointguid_rtps->parameterlength = get16_e (thePDU, endianness);
    GUIDPREFIX_RTPS participantguid;
    if (!parseGUIDPREFIX (&participantguid, thePDU, progname, BIGENDIAN)) {
        return false;
    }
    pidendpointguid_rtps->participantguid = participantguid;
    ENTITYID_RTPS entityid;
    if (!parseENTITYID (&entityid, thePDU, progname, BIGENDIAN)) {
        return false;
    }
    pidendpointguid_rtps->entityid = entityid;
    return true;
}

bool parsePIDMULTICASTLOCATOR (PIDMULTICASTLOCATOR_RTPS *pidmulticastlocator_rtps, PDU *thePDU, char *progname, uint8_t endianness) {
    if (!lengthRemaining (thePDU, 4, progname)) {
        return false;
    }
    pidmulticastlocator_rtps->parameterkind = get16_e (thePDU, endianness);
    if (!(pidmulticastlocator_rtps->parameterkind == 48)) {
        return false;
    }
    pidmulticastlocator_rtps->parameterlength = get16_e (thePDU, endianness);
    unsigned long pos = thePDU->curPos;
    if (!lengthRemaining (thePDU, pidmulticastlocator_rtps->parameterlength, progname)) {
        return false;
    }
    PDU constrainedPDU;
    constrainedPDU.data = thePDU->data;
    constrainedPDU.len = pidmulticastlocator_rtps->parameterlength;
    constrainedPDU.watermark = thePDU->watermark;
    constrainedPDU.curPos = pos;
    constrainedPDU.curBitPos = 0;
    constrainedPDU.remaining = pidmulticastlocator_rtps->parameterlength;
    LOCATOR_RTPS locator;
    if (!parseLOCATOR (&locator, &constrainedPDU, progname, endianness)) {
        return false;
    }
    pidmulticastlocator_rtps->locator = locator;
    thePDU->curPos += constrainedPDU.len;
    return true;
}

bool parsePIDMULTICASTLOCATOR_O (PIDMULTICASTLOCATOR_RTPS *pidmulticastlocator_rtps, PDU *thePDU, char *progname, uint16_t *type, uint8_t endianness) {
    pidmulticastlocator_rtps->parameterkind = *type;
    if (!lengthRemaining (thePDU, 2, progname)) {
        return false;
    }
    pidmulticastlocator_rtps->parameterlength = get16_e (thePDU, endianness);
    unsigned long pos = thePDU->curPos;
    if (!lengthRemaining (thePDU, pidmulticastlocator_rtps->parameterlength, progname)) {
        return false;
    }
    PDU constrainedPDU;
    constrainedPDU.data = thePDU->data;
    constrainedPDU.len = pidmulticastlocator_rtps->parameterlength;
    constrainedPDU.watermark = thePDU->watermark;
    constrainedPDU.curPos = pos;
    constrainedPDU.curBitPos = 0;
    constrainedPDU.remaining = pidmulticastlocator_rtps->parameterlength;
    LOCATOR_RTPS locator;
    if (!parseLOCATOR (&locator, &constrainedPDU, progname, endianness)) {
        return false;
    }
    pidmulticastlocator_rtps->locator = locator;
    thePDU->curPos += constrainedPDU.len;
    return true;
}

bool parsePIDUNICASTLOCATOR (PIDUNICASTLOCATOR_RTPS *pidunicastlocator_rtps, PDU *thePDU, char *progname, uint8_t endianness) {
    if (!lengthRemaining (thePDU, 4, progname)) {
        return false;
    }
    pidunicastlocator_rtps->parameterkind = get16_e (thePDU, endianness);
    if (!(pidunicastlocator_rtps->parameterkind == 47)) {
        return false;
    }
    pidunicastlocator_rtps->parameterlength = get16_e (thePDU, endianness);
    unsigned long pos = thePDU->curPos;
    if (!lengthRemaining (thePDU, pidunicastlocator_rtps->parameterlength, progname)) {
        return false;
    }
    PDU constrainedPDU;
    constrainedPDU.data = thePDU->data;
    constrainedPDU.len = pidunicastlocator_rtps->parameterlength;
    constrainedPDU.watermark = thePDU->watermark;
    constrainedPDU.curPos = pos;
    constrainedPDU.curBitPos = 0;
    constrainedPDU.remaining = pidunicastlocator_rtps->parameterlength;
    LOCATOR_RTPS locator;
    if (!parseLOCATOR (&locator, &constrainedPDU, progname, endianness)) {
        return false;
    }
    pidunicastlocator_rtps->locator = locator;
    thePDU->curPos += constrainedPDU.len;
    return true;
}

bool parsePIDUNICASTLOCATOR_O (PIDUNICASTLOCATOR_RTPS *pidunicastlocator_rtps, PDU *thePDU, char *progname, uint16_t *type, uint8_t endianness) {
    pidunicastlocator_rtps->parameterkind = *type;
    if (!lengthRemaining (thePDU, 2, progname)) {
        return false;
    }
    pidunicastlocator_rtps->parameterlength = get16_e (thePDU, endianness);
    unsigned long pos = thePDU->curPos;
    if (!lengthRemaining (thePDU, pidunicastlocator_rtps->parameterlength, progname)) {
        return false;
    }
    PDU constrainedPDU;
    constrainedPDU.data = thePDU->data;
    constrainedPDU.len = pidunicastlocator_rtps->parameterlength;
    constrainedPDU.watermark = thePDU->watermark;
    constrainedPDU.curPos = pos;
    constrainedPDU.curBitPos = 0;
    constrainedPDU.remaining = pidunicastlocator_rtps->parameterlength;
    LOCATOR_RTPS locator;
    if (!parseLOCATOR (&locator, &constrainedPDU, progname, endianness)) {
        return false;
    }
    pidunicastlocator_rtps->locator = locator;
    thePDU->curPos += constrainedPDU.len;
    return true;
}

bool parsePARTICIPANTS (PARTICIPANTS_RTPS *participants_rtps, PDU *thePDU, char *progname, uint8_t endianness) {
    if (!lengthRemaining (thePDU, 4, progname)) {
        return false;
    }
    participants_rtps->particdata = NULL;
    participants_rtps->encapskind = get16_e (thePDU, BIGENDIAN);
    participants_rtps->encapsopts = get16_e (thePDU, BIGENDIAN);
    int size = 0;
    participants_rtps->particdatalength = thePDU->curPos;
    participants_rtps->particdata = parseSetOfPARTICIPANTPARAMS_O (thePDU, 0, &size, progname, endianness);
    if (participants_rtps->particdata == NULL) {
        return false;
    }
    participants_rtps->particdatacount = size;
    participants_rtps->particdatalength = thePDU->curPos - participants_rtps->particdatalength;
    return true;
}

bool parseDATAPSUB (DATAPSUB_RTPS *datapsub_rtps, PDU *thePDU, char *progname, uint8_t endianness) {
    if (!lengthRemaining (thePDU, 16, progname)) {
        return false;
    }
    datapsub_rtps->inlineqos = NULL;
    datapsub_rtps->serializeddata = NULL;
    datapsub_rtps->kind = get8_e (thePDU, endianness);
    if (!(datapsub_rtps->kind == 21)) {
        return false;
    }
    datapsub_rtps->flags = get8_e (thePDU, endianness);
    endianness = datapsub_rtps->flags & 1;
    datapsub_rtps->nextheader = get16_e (thePDU, endianness);
    datapsub_rtps->extraflags = get16_e (thePDU, endianness);
    datapsub_rtps->qosoffset = get16_e (thePDU, endianness);
    ENTITYID_RTPS readerent;
    if (!parseENTITYID (&readerent, thePDU, progname, BIGENDIAN)) {
        return false;
    }
    datapsub_rtps->readerent = readerent;
    ENTITYID_RTPS writerent;
    if (!parseENTITYID (&writerent, thePDU, progname, BIGENDIAN)) {
        return false;
    }
    datapsub_rtps->writerent = writerent;
    if (!(datapsub_rtps->writerent.key == 256)) {
        return false;
    }
    if (!(datapsub_rtps->writerent.kind == 194)) {
        return false;
    }
    datapsub_rtps->writerseq = get64_e (thePDU, endianness);
    if (datapsub_rtps->flags & 2) {
        datapsub_rtps->inlineqos = (QOSPARM_RTPS *) malloc (sizeof (QOSPARM_RTPS));
        if (datapsub_rtps->inlineqos == NULL) {
            return false;
        }
        if (!parseQOSPARM (datapsub_rtps->inlineqos, thePDU, progname, endianness)) {
            free (datapsub_rtps->inlineqos);
            datapsub_rtps->inlineqos = NULL;
            return false;
        }
    }
    else {
        datapsub_rtps->inlineqos = NULL;
    }
    if (datapsub_rtps->flags & 12) {
        datapsub_rtps->serializeddata = (PARTICIPANTS_RTPS *) malloc (sizeof (PARTICIPANTS_RTPS));
        if (datapsub_rtps->serializeddata == NULL) {
            return false;
        }
        if (!parsePARTICIPANTS (datapsub_rtps->serializeddata, thePDU, progname, endianness)) {
            free (datapsub_rtps->serializeddata);
            datapsub_rtps->serializeddata = NULL;
            return false;
        }
    }
    else {
        datapsub_rtps->serializeddata = NULL;
    }
    return true;
}

bool parseDATARSUB (DATARSUB_RTPS *datarsub_rtps, PDU *thePDU, char *progname, uint8_t endianness) {
    if (!lengthRemaining (thePDU, 16, progname)) {
        return false;
    }
    datarsub_rtps->inlineqos = NULL;
    datarsub_rtps->serializeddata = NULL;
    datarsub_rtps->kind = get8_e (thePDU, endianness);
    if (!(datarsub_rtps->kind == 21)) {
        return false;
    }
    datarsub_rtps->flags = get8_e (thePDU, endianness);
    endianness = datarsub_rtps->flags & 1;
    datarsub_rtps->nextheader = get16_e (thePDU, endianness);
    datarsub_rtps->extraflags = get16_e (thePDU, endianness);
    datarsub_rtps->qosoffset = get16_e (thePDU, endianness);
    ENTITYID_RTPS readerent;
    if (!parseENTITYID (&readerent, thePDU, progname, BIGENDIAN)) {
        return false;
    }
    datarsub_rtps->readerent = readerent;
    ENTITYID_RTPS writerent;
    if (!parseENTITYID (&writerent, thePDU, progname, BIGENDIAN)) {
        return false;
    }
    datarsub_rtps->writerent = writerent;
    if (!(datarsub_rtps->writerent.key == 4)) {
        return false;
    }
    if (!(datarsub_rtps->writerent.kind == 194)) {
        return false;
    }
    datarsub_rtps->writerseq = get64_e (thePDU, endianness);
    if (datarsub_rtps->flags & 2) {
        datarsub_rtps->inlineqos = (QOSPARM_RTPS *) malloc (sizeof (QOSPARM_RTPS));
        if (datarsub_rtps->inlineqos == NULL) {
            return false;
        }
        if (!parseQOSPARM (datarsub_rtps->inlineqos, thePDU, progname, endianness)) {
            free (datarsub_rtps->inlineqos);
            datarsub_rtps->inlineqos = NULL;
            return false;
        }
    }
    else {
        datarsub_rtps->inlineqos = NULL;
    }
    if (datarsub_rtps->flags & 12) {
        datarsub_rtps->serializeddata = (TOPICS_RTPS *) malloc (sizeof (TOPICS_RTPS));
        if (datarsub_rtps->serializeddata == NULL) {
            return false;
        }
        if (!parseTOPICS (datarsub_rtps->serializeddata, thePDU, progname, endianness)) {
            free (datarsub_rtps->serializeddata);
            datarsub_rtps->serializeddata = NULL;
            return false;
        }
    }
    else {
        datarsub_rtps->serializeddata = NULL;
    }
    return true;
}

bool parseINFO$DST (INFO$DST_RTPS *info$dst_rtps, PDU *thePDU, char *progname, uint8_t endianness) {
    if (!lengthRemaining (thePDU, 4, progname)) {
        return false;
    }
    info$dst_rtps->kind = get8_e (thePDU, endianness);
    if (!(info$dst_rtps->kind == 14)) {
        return false;
    }
    info$dst_rtps->flags = get8_e (thePDU, endianness);
    endianness = info$dst_rtps->flags & 1;
    info$dst_rtps->nextheader = get16_e (thePDU, endianness);
    GUIDPREFIX_RTPS guidpfx;
    if (!parseGUIDPREFIX (&guidpfx, thePDU, progname, BIGENDIAN)) {
        return false;
    }
    info$dst_rtps->guidpfx = guidpfx;
    return true;
}

bool parseINFO$TS (INFO$TS_RTPS *info$ts_rtps, PDU *thePDU, char *progname, uint8_t endianness) {
    if (!lengthRemaining (thePDU, 12, progname)) {
        return false;
    }
    info$ts_rtps->kind = get8_e (thePDU, endianness);
    if (!(info$ts_rtps->kind == 9)) {
        return false;
    }
    info$ts_rtps->flags = get8_e (thePDU, endianness);
    endianness = info$ts_rtps->flags & 1;
    info$ts_rtps->nextheader = get16_e (thePDU, endianness);
    info$ts_rtps->timestamp = get64_e (thePDU, endianness);
    return true;
}

bool parseACKNACK (ACKNACK_RTPS *acknack_rtps, PDU *thePDU, char *progname, uint8_t endianness) {
    if (!lengthRemaining (thePDU, 8, progname)) {
        return false;
    }
    acknack_rtps->kind = get8_e (thePDU, endianness);
    if (!(acknack_rtps->kind == 6)) {
        return false;
    }
    acknack_rtps->flags = get8_e (thePDU, endianness);
    endianness = acknack_rtps->flags & 1;
    acknack_rtps->nextheader = get16_e (thePDU, endianness);
    ENTITYID_RTPS readerent;
    if (!parseENTITYID (&readerent, thePDU, progname, BIGENDIAN)) {
        return false;
    }
    acknack_rtps->readerent = readerent;
    ENTITYID_RTPS writerent;
    if (!parseENTITYID (&writerent, thePDU, progname, BIGENDIAN)) {
        return false;
    }
    acknack_rtps->writerent = writerent;
    SNSTATE_RTPS readersn;
    if (!parseSNSTATE (&readersn, thePDU, progname, endianness)) {
        return false;
    }
    acknack_rtps->readersn = readersn;
    acknack_rtps->counter = get32_e (thePDU, endianness);
    return true;
}

bool parseHEARTBEAT (HEARTBEAT_RTPS *heartbeat_rtps, PDU *thePDU, char *progname, uint8_t endianness) {
    if (!lengthRemaining (thePDU, 24, progname)) {
        return false;
    }
    heartbeat_rtps->kind = get8_e (thePDU, endianness);
    if (!(heartbeat_rtps->kind == 7)) {
        return false;
    }
    heartbeat_rtps->flags = get8_e (thePDU, endianness);
    endianness = heartbeat_rtps->flags & 1;
    heartbeat_rtps->nextheader = get16_e (thePDU, endianness);
    ENTITYID_RTPS readerent;
    if (!parseENTITYID (&readerent, thePDU, progname, BIGENDIAN)) {
        return false;
    }
    heartbeat_rtps->readerent = readerent;
    ENTITYID_RTPS writerent;
    if (!parseENTITYID (&writerent, thePDU, progname, BIGENDIAN)) {
        return false;
    }
    heartbeat_rtps->writerent = writerent;
    heartbeat_rtps->firstseq = get64_e (thePDU, endianness);
    heartbeat_rtps->lastseq = get64_e (thePDU, endianness);
    heartbeat_rtps->count = get32_e (thePDU, endianness);
    return true;
}

bool parseGAP (GAP_RTPS *gap_rtps, PDU *thePDU, char *progname, uint8_t endianness) {
    if (!lengthRemaining (thePDU, 12, progname)) {
        return false;
    }
    gap_rtps->kind = get8_e (thePDU, endianness);
    if (!(gap_rtps->kind == 8)) {
        return false;
    }
    gap_rtps->flags = get8_e (thePDU, endianness);
    endianness = gap_rtps->flags & 1;
    gap_rtps->nextheader = get16_e (thePDU, endianness);
    ENTITYID_RTPS readerent;
    if (!parseENTITYID (&readerent, thePDU, progname, BIGENDIAN)) {
        return false;
    }
    gap_rtps->readerent = readerent;
    ENTITYID_RTPS writerent;
    if (!parseENTITYID (&writerent, thePDU, progname, BIGENDIAN)) {
        return false;
    }
    gap_rtps->writerent = writerent;
    gap_rtps->gapstart = get64_e (thePDU, endianness);
    SNSTATE_RTPS snstate;
    if (!parseSNSTATE (&snstate, thePDU, progname, endianness)) {
        return false;
    }
    gap_rtps->snstate = snstate;
    return true;
}

bool parsePARTICIPANTPARAMS (PARTICIPANTPARAMS_RTPS *participantparams_rtps, PDU *thePDU, char *progname, uint8_t endianness) {
    if (!lengthRemaining (thePDU, 2, progname)) {
        return false;
    }
    uint16_t type = get16_e (thePDU, endianness);
    switch (type) {
    case 21 :
        if (parsePIDPROTOVERSION_O (&participantparams_rtps->ptr.pidprotoversion_rtps, thePDU, progname, &type, endianness)) {
            participantparams_rtps->type = PIDPROTOVERSION_RTPS_VAL;
        }
        else {
            return false;
        }
        break;
    case 80 :
        if (parsePIDPARTICIPANTGUID_O (&participantparams_rtps->ptr.pidparticipantguid_rtps, thePDU, progname, &type, endianness)) {
            participantparams_rtps->type = PIDPARTICIPANTGUID_RTPS_VAL;
        }
        else {
            return false;
        }
        break;
    case 22 :
        if (parsePIDVENDORID_O (&participantparams_rtps->ptr.pidvendorid_rtps, thePDU, progname, &type, endianness)) {
            participantparams_rtps->type = PIDVENDORID_RTPS_VAL;
        }
        else {
            return false;
        }
        break;
    case 68 :
        if (parsePIDPARTICIPANTBUILTENDPOINTS_O (&participantparams_rtps->ptr.pidparticipantbuiltendpoints_rtps, thePDU, progname, &type, endianness)) {
            participantparams_rtps->type = PIDPARTICIPANTBUILTENDPOINTS_RTPS_VAL;
        }
        else {
            return false;
        }
        break;
    case 88 :
        if (parsePIDBUILTINENDPOINTSET_O (&participantparams_rtps->ptr.pidbuiltinendpointset_rtps, thePDU, progname, &type, endianness)) {
            participantparams_rtps->type = PIDBUILTINENDPOINTSET_RTPS_VAL;
        }
        else {
            return false;
        }
        break;
    case 50 :
        if (parsePIDMETATRAFFICUNILOCATOR_O (&participantparams_rtps->ptr.pidmetatrafficunilocator_rtps, thePDU, progname, &type, endianness)) {
            participantparams_rtps->type = PIDMETATRAFFICUNILOCATOR_RTPS_VAL;
        }
        else {
            return false;
        }
        break;
    case 72 :
        if (parsePIDDEFMULTILOCATOR_O (&participantparams_rtps->ptr.piddefmultilocator_rtps, thePDU, progname, &type, endianness)) {
            participantparams_rtps->type = PIDDEFMULTILOCATOR_RTPS_VAL;
        }
        else {
            return false;
        }
        break;
    case 52 :
        if (parsePIDPARTICIPANTLIVECOUNT_O (&participantparams_rtps->ptr.pidparticipantlivecount_rtps, thePDU, progname, &type, endianness)) {
            participantparams_rtps->type = PIDPARTICIPANTLIVECOUNT_RTPS_VAL;
        }
        else {
            return false;
        }
        break;
    case 2 :
        if (parsePIDPARTICIPANTLEASE_O (&participantparams_rtps->ptr.pidparticipantlease_rtps, thePDU, progname, &type, endianness)) {
            participantparams_rtps->type = PIDPARTICIPANTLEASE_RTPS_VAL;
        }
        else {
            return false;
        }
        break;
    case 1 :
        if (parsePIDSENTINAL_O (&participantparams_rtps->ptr.pidsentinal_rtps, thePDU, progname, &type, endianness)) {
            participantparams_rtps->type = PIDSENTINAL_RTPS_VAL;
        }
        else {
            return false;
        }
        break;
    case 49 :
        if (parsePIDDEFUNILOCATOR_O (&participantparams_rtps->ptr.piddefunilocator_rtps, thePDU, progname, &type, endianness)) {
            participantparams_rtps->type = PIDDEFUNILOCATOR_RTPS_VAL;
        }
        else {
            return false;
        }
        break;
    case 51 :
        if (parsePIDMETATRAFFICMULTILOCATOR_O (&participantparams_rtps->ptr.pidmetatrafficmultilocator_rtps, thePDU, progname, &type, endianness)) {
            participantparams_rtps->type = PIDMETATRAFFICMULTILOCATOR_RTPS_VAL;
        }
        else {
            return false;
        }
        break;
    case 89 :
        if (parsePIDPROPERTYLIST_O (&participantparams_rtps->ptr.pidpropertylist_rtps, thePDU, progname, &type, endianness)) {
            participantparams_rtps->type = PIDPROPERTYLIST_RTPS_VAL;
        }
        else {
            return false;
        }
        break;
    case 98 :
        if (parsePIDENTITYNAME_O (&participantparams_rtps->ptr.pidentityname_rtps, thePDU, progname, &type, endianness)) {
            participantparams_rtps->type = PIDENTITYNAME_RTPS_VAL;
        }
        else {
            return false;
        }
        break;
    case 32778 :
        if (parsePIDROLENAME_O (&participantparams_rtps->ptr.pidrolename_rtps, thePDU, progname, &type, endianness)) {
            participantparams_rtps->type = PIDROLENAME_RTPS_VAL;
        }
        else {
            return false;
        }
        break;
    case 32782 :
        if (parsePIDPEERHOSTEPOCH_O (&participantparams_rtps->ptr.pidpeerhostepoch_rtps, thePDU, progname, &type, endianness)) {
            participantparams_rtps->type = PIDPEERHOSTEPOCH_RTPS_VAL;
        }
        else {
            return false;
        }
        break;
    case 32783 :
        if (parsePIDDOMAINID_O (&participantparams_rtps->ptr.piddomainid_rtps, thePDU, progname, &type, endianness)) {
            participantparams_rtps->type = PIDDOMAINID_RTPS_VAL;
        }
        else {
            return false;
        }
        break;
    case 32784 :
        if (parsePIDTRANSPORTINFOLIST_O (&participantparams_rtps->ptr.pidtransportinfolist_rtps, thePDU, progname, &type, endianness)) {
            participantparams_rtps->type = PIDTRANSPORTINFOLIST_RTPS_VAL;
        }
        else {
            return false;
        }
        break;
    case 32768 :
        if (parsePIDPRODUCTVERSION_O (&participantparams_rtps->ptr.pidproductversion_rtps, thePDU, progname, &type, endianness)) {
            participantparams_rtps->type = PIDPRODUCTVERSION_RTPS_VAL;
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

bool parsePIDPRODUCTVERSION (PIDPRODUCTVERSION_RTPS *pidproductversion_rtps, PDU *thePDU, char *progname, uint8_t endianness) {
    if (!lengthRemaining (thePDU, 4, progname)) {
        return false;
    }
    pidproductversion_rtps->parameterkind = get16_e (thePDU, endianness);
    if (!(pidproductversion_rtps->parameterkind == 32768)) {
        return false;
    }
    pidproductversion_rtps->parameterlength = get16_e (thePDU, endianness);
    unsigned long pos = thePDU->curPos;
    if (!lengthRemaining (thePDU, pidproductversion_rtps->parameterlength, progname)) {
        return false;
    }
    PDU constrainedPDU;
    constrainedPDU.data = thePDU->data;
    constrainedPDU.len = pidproductversion_rtps->parameterlength;
    constrainedPDU.watermark = thePDU->watermark;
    constrainedPDU.curPos = pos;
    constrainedPDU.curBitPos = 0;
    constrainedPDU.remaining = pidproductversion_rtps->parameterlength;
    PRODUCTVERSION_RTPS productversion;
    if (!parsePRODUCTVERSION (&productversion, &constrainedPDU, progname, endianness)) {
        return false;
    }
    pidproductversion_rtps->productversion = productversion;
    thePDU->curPos += constrainedPDU.len;
    return true;
}

bool parsePIDPRODUCTVERSION_O (PIDPRODUCTVERSION_RTPS *pidproductversion_rtps, PDU *thePDU, char *progname, uint16_t *type, uint8_t endianness) {
    pidproductversion_rtps->parameterkind = *type;
    if (!lengthRemaining (thePDU, 2, progname)) {
        return false;
    }
    pidproductversion_rtps->parameterlength = get16_e (thePDU, endianness);
    unsigned long pos = thePDU->curPos;
    if (!lengthRemaining (thePDU, pidproductversion_rtps->parameterlength, progname)) {
        return false;
    }
    PDU constrainedPDU;
    constrainedPDU.data = thePDU->data;
    constrainedPDU.len = pidproductversion_rtps->parameterlength;
    constrainedPDU.watermark = thePDU->watermark;
    constrainedPDU.curPos = pos;
    constrainedPDU.curBitPos = 0;
    constrainedPDU.remaining = pidproductversion_rtps->parameterlength;
    PRODUCTVERSION_RTPS productversion;
    if (!parsePRODUCTVERSION (&productversion, &constrainedPDU, progname, endianness)) {
        return false;
    }
    pidproductversion_rtps->productversion = productversion;
    thePDU->curPos += constrainedPDU.len;
    return true;
}

bool parsePRODUCTVERSION (PRODUCTVERSION_RTPS *productversion_rtps, PDU *thePDU, char *progname, uint8_t endianness) {
    if (!lengthRemaining (thePDU, 4, progname)) {
        return false;
    }
    productversion_rtps->major = get8_e (thePDU, endianness);
    productversion_rtps->minor = get8_e (thePDU, endianness);
    productversion_rtps->release = get8_e (thePDU, endianness);
    productversion_rtps->revision = get8_e (thePDU, endianness);
    return true;
}

bool parsePIDTRANSPORTINFOLIST (PIDTRANSPORTINFOLIST_RTPS *pidtransportinfolist_rtps, PDU *thePDU, char *progname, uint8_t endianness) {
    if (!lengthRemaining (thePDU, 4, progname)) {
        return false;
    }
    pidtransportinfolist_rtps->parameterkind = get16_e (thePDU, endianness);
    if (!(pidtransportinfolist_rtps->parameterkind == 32784)) {
        return false;
    }
    pidtransportinfolist_rtps->parameterlength = get16_e (thePDU, endianness);
    unsigned long pos = thePDU->curPos;
    if (!lengthRemaining (thePDU, pidtransportinfolist_rtps->parameterlength, progname)) {
        return false;
    }
    PDU constrainedPDU;
    constrainedPDU.data = thePDU->data;
    constrainedPDU.len = pidtransportinfolist_rtps->parameterlength;
    constrainedPDU.watermark = thePDU->watermark;
    constrainedPDU.curPos = pos;
    constrainedPDU.curBitPos = 0;
    constrainedPDU.remaining = pidtransportinfolist_rtps->parameterlength;
    TRANSPORTS_RTPS transports;
    if (!parseTRANSPORTS (&transports, &constrainedPDU, progname, endianness)) {
        return false;
    }
    pidtransportinfolist_rtps->transports = transports;
    if (constrainedPDU.remaining != 0) {
        return false;
    }
    thePDU->curPos += constrainedPDU.len;
    return true;
}

bool parsePIDTRANSPORTINFOLIST_O (PIDTRANSPORTINFOLIST_RTPS *pidtransportinfolist_rtps, PDU *thePDU, char *progname, uint16_t *type, uint8_t endianness) {
    pidtransportinfolist_rtps->parameterkind = *type;
    if (!lengthRemaining (thePDU, 2, progname)) {
        return false;
    }
    pidtransportinfolist_rtps->parameterlength = get16_e (thePDU, endianness);
    unsigned long pos = thePDU->curPos;
    if (!lengthRemaining (thePDU, pidtransportinfolist_rtps->parameterlength, progname)) {
        return false;
    }
    PDU constrainedPDU;
    constrainedPDU.data = thePDU->data;
    constrainedPDU.len = pidtransportinfolist_rtps->parameterlength;
    constrainedPDU.watermark = thePDU->watermark;
    constrainedPDU.curPos = pos;
    constrainedPDU.curBitPos = 0;
    constrainedPDU.remaining = pidtransportinfolist_rtps->parameterlength;
    TRANSPORTS_RTPS transports;
    if (!parseTRANSPORTS (&transports, &constrainedPDU, progname, endianness)) {
        return false;
    }
    pidtransportinfolist_rtps->transports = transports;
    if (constrainedPDU.remaining != 0) {
        return false;
    }
    thePDU->curPos += constrainedPDU.len;
    return true;
}

bool parseTRANSPORTS (TRANSPORTS_RTPS *transports_rtps, PDU *thePDU, char *progname, uint8_t endianness) {
    if (!lengthRemaining (thePDU, 4, progname)) {
        return false;
    }
    transports_rtps->info = NULL;
    transports_rtps->transportnum = get32_e (thePDU, endianness);
    transports_rtps->infocount = transports_rtps->transportnum;
    transports_rtps->infolength = thePDU->curPos;
    transports_rtps->info = parseSetOfTRANSPORTINFO (thePDU, transports_rtps->transportnum, progname, endianness);
    if (transports_rtps->info == NULL) {
        return false;
    }
    transports_rtps->infolength = thePDU->curPos - transports_rtps->infolength;
    return true;
}

bool parseTRANSPORTINFO (TRANSPORTINFO_RTPS *transportinfo_rtps, PDU *thePDU, char *progname, uint8_t endianness) {
    if (!lengthRemaining (thePDU, 8, progname)) {
        return false;
    }
    transportinfo_rtps->classid = get32_e (thePDU, endianness);
    transportinfo_rtps->messagesizemax = get32_e (thePDU, endianness);
    return true;
}

bool parsePIDDOMAINID (PIDDOMAINID_RTPS *piddomainid_rtps, PDU *thePDU, char *progname, uint8_t endianness) {
    if (!lengthRemaining (thePDU, 4, progname)) {
        return false;
    }
    piddomainid_rtps->domainid = NULL;
    piddomainid_rtps->parameterkind = get16_e (thePDU, endianness);
    if (!(piddomainid_rtps->parameterkind == 32783)) {
        return false;
    }
    piddomainid_rtps->parameterlength = get16_e (thePDU, endianness);
    unsigned long remaining = thePDU->remaining;
    if (!lengthRemaining (thePDU, piddomainid_rtps->parameterlength, progname)) {
        return false;
    }
    piddomainid_rtps->domainid = (unsigned char *) malloc (sizeof (unsigned char) * (piddomainid_rtps->parameterlength));
    if (piddomainid_rtps->domainid == NULL) {
        fprintf (stderr, "%s: internal malloc error file: %s line: %d \n", progname, __FILE__, __LINE__);
        return false;
    }
    piddomainid_rtps->domainid_length = piddomainid_rtps->parameterlength;
    memcpy (piddomainid_rtps->domainid, &thePDU->data[thePDU->curPos], piddomainid_rtps->parameterlength);
    thePDU->curPos += piddomainid_rtps->parameterlength;
    if (piddomainid_rtps->domainid[piddomainid_rtps->parameterlength - 1] != '\0') {
    }
    return true;
}

bool parsePIDDOMAINID_O (PIDDOMAINID_RTPS *piddomainid_rtps, PDU *thePDU, char *progname, uint16_t *type, uint8_t endianness) {
    piddomainid_rtps->parameterkind = *type;
    if (!lengthRemaining (thePDU, 2, progname)) {
        return false;
    }
    piddomainid_rtps->domainid = NULL;
    piddomainid_rtps->parameterlength = get16_e (thePDU, endianness);
    unsigned long remaining = thePDU->remaining;
    if (!lengthRemaining (thePDU, piddomainid_rtps->parameterlength, progname)) {
        return false;
    }
    piddomainid_rtps->domainid = (unsigned char *) malloc (sizeof (unsigned char) * (piddomainid_rtps->parameterlength));
    if (piddomainid_rtps->domainid == NULL) {
        fprintf (stderr, "%s: internal malloc error file: %s line: %d \n", progname, __FILE__, __LINE__);
        return false;
    }
    piddomainid_rtps->domainid_length = piddomainid_rtps->parameterlength;
    memcpy (piddomainid_rtps->domainid, &thePDU->data[thePDU->curPos], piddomainid_rtps->parameterlength);
    thePDU->curPos += piddomainid_rtps->parameterlength;
    if (piddomainid_rtps->domainid[piddomainid_rtps->parameterlength - 1] != '\0') {
    }
    return true;
}

bool parsePIDPEERHOSTEPOCH (PIDPEERHOSTEPOCH_RTPS *pidpeerhostepoch_rtps, PDU *thePDU, char *progname, uint8_t endianness) {
    if (!lengthRemaining (thePDU, 4, progname)) {
        return false;
    }
    pidpeerhostepoch_rtps->hostepoch = NULL;
    pidpeerhostepoch_rtps->parameterkind = get16_e (thePDU, endianness);
    if (!(pidpeerhostepoch_rtps->parameterkind == 32782)) {
        return false;
    }
    pidpeerhostepoch_rtps->parameterlength = get16_e (thePDU, endianness);
    unsigned long remaining = thePDU->remaining;
    if (!lengthRemaining (thePDU, pidpeerhostepoch_rtps->parameterlength, progname)) {
        return false;
    }
    pidpeerhostepoch_rtps->hostepoch = (unsigned char *) malloc (sizeof (unsigned char) * (pidpeerhostepoch_rtps->parameterlength));
    if (pidpeerhostepoch_rtps->hostepoch == NULL) {
        fprintf (stderr, "%s: internal malloc error file: %s line: %d \n", progname, __FILE__, __LINE__);
        return false;
    }
    pidpeerhostepoch_rtps->hostepoch_length = pidpeerhostepoch_rtps->parameterlength;
    memcpy (pidpeerhostepoch_rtps->hostepoch, &thePDU->data[thePDU->curPos], pidpeerhostepoch_rtps->parameterlength);
    thePDU->curPos += pidpeerhostepoch_rtps->parameterlength;
    if (pidpeerhostepoch_rtps->hostepoch[pidpeerhostepoch_rtps->parameterlength - 1] != '\0') {
    }
    return true;
}

bool parsePIDPEERHOSTEPOCH_O (PIDPEERHOSTEPOCH_RTPS *pidpeerhostepoch_rtps, PDU *thePDU, char *progname, uint16_t *type, uint8_t endianness) {
    pidpeerhostepoch_rtps->parameterkind = *type;
    if (!lengthRemaining (thePDU, 2, progname)) {
        return false;
    }
    pidpeerhostepoch_rtps->hostepoch = NULL;
    pidpeerhostepoch_rtps->parameterlength = get16_e (thePDU, endianness);
    unsigned long remaining = thePDU->remaining;
    if (!lengthRemaining (thePDU, pidpeerhostepoch_rtps->parameterlength, progname)) {
        return false;
    }
    pidpeerhostepoch_rtps->hostepoch = (unsigned char *) malloc (sizeof (unsigned char) * (pidpeerhostepoch_rtps->parameterlength));
    if (pidpeerhostepoch_rtps->hostepoch == NULL) {
        fprintf (stderr, "%s: internal malloc error file: %s line: %d \n", progname, __FILE__, __LINE__);
        return false;
    }
    pidpeerhostepoch_rtps->hostepoch_length = pidpeerhostepoch_rtps->parameterlength;
    memcpy (pidpeerhostepoch_rtps->hostepoch, &thePDU->data[thePDU->curPos], pidpeerhostepoch_rtps->parameterlength);
    thePDU->curPos += pidpeerhostepoch_rtps->parameterlength;
    if (pidpeerhostepoch_rtps->hostepoch[pidpeerhostepoch_rtps->parameterlength - 1] != '\0') {
    }
    return true;
}

bool parsePIDROLENAME (PIDROLENAME_RTPS *pidrolename_rtps, PDU *thePDU, char *progname, uint8_t endianness) {
    if (!lengthRemaining (thePDU, 4, progname)) {
        return false;
    }
    pidrolename_rtps->parameterkind = get16_e (thePDU, endianness);
    if (!(pidrolename_rtps->parameterkind == 32778)) {
        return false;
    }
    pidrolename_rtps->parameterlength = get16_e (thePDU, endianness);
    unsigned long pos = thePDU->curPos;
    if (!lengthRemaining (thePDU, pidrolename_rtps->parameterlength, progname)) {
        return false;
    }
    PDU constrainedPDU;
    constrainedPDU.data = thePDU->data;
    constrainedPDU.len = pidrolename_rtps->parameterlength;
    constrainedPDU.watermark = thePDU->watermark;
    constrainedPDU.curPos = pos;
    constrainedPDU.curBitPos = 0;
    constrainedPDU.remaining = pidrolename_rtps->parameterlength;
    NESTEDSTRING_RTPS rolename;
    if (!parseNESTEDSTRING (&rolename, &constrainedPDU, progname, endianness)) {
        return false;
    }
    pidrolename_rtps->rolename = rolename;
    thePDU->curPos += constrainedPDU.len;
    return true;
}

bool parsePIDROLENAME_O (PIDROLENAME_RTPS *pidrolename_rtps, PDU *thePDU, char *progname, uint16_t *type, uint8_t endianness) {
    pidrolename_rtps->parameterkind = *type;
    if (!lengthRemaining (thePDU, 2, progname)) {
        return false;
    }
    pidrolename_rtps->parameterlength = get16_e (thePDU, endianness);
    unsigned long pos = thePDU->curPos;
    if (!lengthRemaining (thePDU, pidrolename_rtps->parameterlength, progname)) {
        return false;
    }
    PDU constrainedPDU;
    constrainedPDU.data = thePDU->data;
    constrainedPDU.len = pidrolename_rtps->parameterlength;
    constrainedPDU.watermark = thePDU->watermark;
    constrainedPDU.curPos = pos;
    constrainedPDU.curBitPos = 0;
    constrainedPDU.remaining = pidrolename_rtps->parameterlength;
    NESTEDSTRING_RTPS rolename;
    if (!parseNESTEDSTRING (&rolename, &constrainedPDU, progname, endianness)) {
        return false;
    }
    pidrolename_rtps->rolename = rolename;
    thePDU->curPos += constrainedPDU.len;
    return true;
}

bool parsePIDENTITYNAME (PIDENTITYNAME_RTPS *pidentityname_rtps, PDU *thePDU, char *progname, uint8_t endianness) {
    if (!lengthRemaining (thePDU, 4, progname)) {
        return false;
    }
    pidentityname_rtps->parameterkind = get16_e (thePDU, endianness);
    if (!(pidentityname_rtps->parameterkind == 98)) {
        return false;
    }
    pidentityname_rtps->parameterlength = get16_e (thePDU, endianness);
    unsigned long pos = thePDU->curPos;
    if (!lengthRemaining (thePDU, pidentityname_rtps->parameterlength, progname)) {
        return false;
    }
    PDU constrainedPDU;
    constrainedPDU.data = thePDU->data;
    constrainedPDU.len = pidentityname_rtps->parameterlength;
    constrainedPDU.watermark = thePDU->watermark;
    constrainedPDU.curPos = pos;
    constrainedPDU.curBitPos = 0;
    constrainedPDU.remaining = pidentityname_rtps->parameterlength;
    NESTEDSTRING_RTPS entityname;
    if (!parseNESTEDSTRING (&entityname, &constrainedPDU, progname, endianness)) {
        return false;
    }
    pidentityname_rtps->entityname = entityname;
    thePDU->curPos += constrainedPDU.len;
    return true;
}

bool parsePIDENTITYNAME_O (PIDENTITYNAME_RTPS *pidentityname_rtps, PDU *thePDU, char *progname, uint16_t *type, uint8_t endianness) {
    pidentityname_rtps->parameterkind = *type;
    if (!lengthRemaining (thePDU, 2, progname)) {
        return false;
    }
    pidentityname_rtps->parameterlength = get16_e (thePDU, endianness);
    unsigned long pos = thePDU->curPos;
    if (!lengthRemaining (thePDU, pidentityname_rtps->parameterlength, progname)) {
        return false;
    }
    PDU constrainedPDU;
    constrainedPDU.data = thePDU->data;
    constrainedPDU.len = pidentityname_rtps->parameterlength;
    constrainedPDU.watermark = thePDU->watermark;
    constrainedPDU.curPos = pos;
    constrainedPDU.curBitPos = 0;
    constrainedPDU.remaining = pidentityname_rtps->parameterlength;
    NESTEDSTRING_RTPS entityname;
    if (!parseNESTEDSTRING (&entityname, &constrainedPDU, progname, endianness)) {
        return false;
    }
    pidentityname_rtps->entityname = entityname;
    thePDU->curPos += constrainedPDU.len;
    return true;
}

bool parsePIDPROPERTYLIST (PIDPROPERTYLIST_RTPS *pidpropertylist_rtps, PDU *thePDU, char *progname, uint8_t endianness) {
    if (!lengthRemaining (thePDU, 4, progname)) {
        return false;
    }
    pidpropertylist_rtps->parameterkind = get16_e (thePDU, endianness);
    if (!(pidpropertylist_rtps->parameterkind == 89)) {
        return false;
    }
    pidpropertylist_rtps->parameterlength = get16_e (thePDU, endianness);
    unsigned long pos = thePDU->curPos;
    if (!lengthRemaining (thePDU, pidpropertylist_rtps->parameterlength, progname)) {
        return false;
    }
    PDU constrainedPDU;
    constrainedPDU.data = thePDU->data;
    constrainedPDU.len = pidpropertylist_rtps->parameterlength;
    constrainedPDU.watermark = thePDU->watermark;
    constrainedPDU.curPos = pos;
    constrainedPDU.curBitPos = 0;
    constrainedPDU.remaining = pidpropertylist_rtps->parameterlength;
    PROPERTYLIST_RTPS properties;
    if (!parsePROPERTYLIST (&properties, &constrainedPDU, progname, endianness)) {
        return false;
    }
    pidpropertylist_rtps->properties = properties;
    if (constrainedPDU.remaining != 0) {
        return false;
    }
    thePDU->curPos += constrainedPDU.len;
    return true;
}

bool parsePIDPROPERTYLIST_O (PIDPROPERTYLIST_RTPS *pidpropertylist_rtps, PDU *thePDU, char *progname, uint16_t *type, uint8_t endianness) {
    pidpropertylist_rtps->parameterkind = *type;
    if (!lengthRemaining (thePDU, 2, progname)) {
        return false;
    }
    pidpropertylist_rtps->parameterlength = get16_e (thePDU, endianness);
    unsigned long pos = thePDU->curPos;
    if (!lengthRemaining (thePDU, pidpropertylist_rtps->parameterlength, progname)) {
        return false;
    }
    PDU constrainedPDU;
    constrainedPDU.data = thePDU->data;
    constrainedPDU.len = pidpropertylist_rtps->parameterlength;
    constrainedPDU.watermark = thePDU->watermark;
    constrainedPDU.curPos = pos;
    constrainedPDU.curBitPos = 0;
    constrainedPDU.remaining = pidpropertylist_rtps->parameterlength;
    PROPERTYLIST_RTPS properties;
    if (!parsePROPERTYLIST (&properties, &constrainedPDU, progname, endianness)) {
        return false;
    }
    pidpropertylist_rtps->properties = properties;
    if (constrainedPDU.remaining != 0) {
        return false;
    }
    thePDU->curPos += constrainedPDU.len;
    return true;
}

bool parsePROPERTYLIST (PROPERTYLIST_RTPS *propertylist_rtps, PDU *thePDU, char *progname, uint8_t endianness) {
    if (!lengthRemaining (thePDU, 4, progname)) {
        return false;
    }
    propertylist_rtps->list = NULL;
    propertylist_rtps->numproperties = get32_e (thePDU, endianness);
    propertylist_rtps->listcount = propertylist_rtps->numproperties;
    propertylist_rtps->listlength = thePDU->curPos;
    propertylist_rtps->list = parseSetOfPROPERTY (thePDU, propertylist_rtps->numproperties, progname, endianness);
    if (propertylist_rtps->list == NULL) {
        return false;
    }
    propertylist_rtps->listlength = thePDU->curPos - propertylist_rtps->listlength;
    return true;
}

bool parsePROPERTY (PROPERTY_RTPS *property_rtps, PDU *thePDU, char *progname, uint8_t endianness) {
    if (!lengthRemaining (thePDU, 0, progname)) {
        return false;
    }
    unsigned long posname = thePDU->curPos;
    NESTEDSTRING_RTPS name;
    if (!parseNESTEDSTRING (&name, thePDU, progname, endianness)) {
        return false;
    }
    property_rtps->name = name;
    if (!lengthRemaining (thePDU, (((thePDU->curPos - posname) % 4 ? 4 - ((thePDU->curPos - posname) % 4) : 0)), progname)) {
        return false;
    }
    thePDU->curPos += (((thePDU->curPos - posname) % 4 ? 4 - ((thePDU->curPos - posname) % 4) : 0));
    unsigned long posvalue = thePDU->curPos;
    NESTEDSTRING_RTPS value;
    if (!parseNESTEDSTRING (&value, thePDU, progname, endianness)) {
        return false;
    }
    property_rtps->value = value;
    if (!lengthRemaining (thePDU, (((thePDU->curPos - posvalue) % 4 ? 4 - ((thePDU->curPos - posvalue) % 4) : 0)), progname)) {
        return false;
    }
    thePDU->curPos += (((thePDU->curPos - posvalue) % 4 ? 4 - ((thePDU->curPos - posvalue) % 4) : 0));
    return true;
}

bool parsePIDPROTOVERSION (PIDPROTOVERSION_RTPS *pidprotoversion_rtps, PDU *thePDU, char *progname, uint8_t endianness) {
    if (!lengthRemaining (thePDU, 4, progname)) {
        return false;
    }
    pidprotoversion_rtps->parameterkind = get16_e (thePDU, endianness);
    if (!(pidprotoversion_rtps->parameterkind == 21)) {
        return false;
    }
    pidprotoversion_rtps->parameterlength = get16_e (thePDU, endianness);
    unsigned long pos = thePDU->curPos;
    if (!lengthRemaining (thePDU, pidprotoversion_rtps->parameterlength, progname)) {
        return false;
    }
    PDU constrainedPDU;
    constrainedPDU.data = thePDU->data;
    constrainedPDU.len = pidprotoversion_rtps->parameterlength;
    constrainedPDU.watermark = thePDU->watermark;
    constrainedPDU.curPos = pos;
    constrainedPDU.curBitPos = 0;
    constrainedPDU.remaining = pidprotoversion_rtps->parameterlength;
    PROTOCOLVERSION_RTPS protocolversion;
    if (!parsePROTOCOLVERSION (&protocolversion, &constrainedPDU, progname, endianness)) {
        return false;
    }
    pidprotoversion_rtps->protocolversion = protocolversion;
    thePDU->curPos += constrainedPDU.len;
    return true;
}

bool parsePIDPROTOVERSION_O (PIDPROTOVERSION_RTPS *pidprotoversion_rtps, PDU *thePDU, char *progname, uint16_t *type, uint8_t endianness) {
    pidprotoversion_rtps->parameterkind = *type;
    if (!lengthRemaining (thePDU, 2, progname)) {
        return false;
    }
    pidprotoversion_rtps->parameterlength = get16_e (thePDU, endianness);
    unsigned long pos = thePDU->curPos;
    if (!lengthRemaining (thePDU, pidprotoversion_rtps->parameterlength, progname)) {
        return false;
    }
    PDU constrainedPDU;
    constrainedPDU.data = thePDU->data;
    constrainedPDU.len = pidprotoversion_rtps->parameterlength;
    constrainedPDU.watermark = thePDU->watermark;
    constrainedPDU.curPos = pos;
    constrainedPDU.curBitPos = 0;
    constrainedPDU.remaining = pidprotoversion_rtps->parameterlength;
    PROTOCOLVERSION_RTPS protocolversion;
    if (!parsePROTOCOLVERSION (&protocolversion, &constrainedPDU, progname, endianness)) {
        return false;
    }
    pidprotoversion_rtps->protocolversion = protocolversion;
    thePDU->curPos += constrainedPDU.len;
    return true;
}

bool parsePROTOCOLVERSION (PROTOCOLVERSION_RTPS *protocolversion_rtps, PDU *thePDU, char *progname, uint8_t endianness) {
    if (!lengthRemaining (thePDU, 2, progname)) {
        return false;
    }
    protocolversion_rtps->major = get8_e (thePDU, endianness);
    protocolversion_rtps->minor = get8_e (thePDU, endianness);
    return true;
}

bool parsePIDPARTICIPANTGUID (PIDPARTICIPANTGUID_RTPS *pidparticipantguid_rtps, PDU *thePDU, char *progname, uint8_t endianness) {
    if (!lengthRemaining (thePDU, 4, progname)) {
        return false;
    }
    pidparticipantguid_rtps->parameterkind = get16_e (thePDU, endianness);
    if (!(pidparticipantguid_rtps->parameterkind == 80)) {
        return false;
    }
    pidparticipantguid_rtps->parameterlength = get16_e (thePDU, endianness);
    unsigned long pos = thePDU->curPos;
    if (!lengthRemaining (thePDU, pidparticipantguid_rtps->parameterlength, progname)) {
        return false;
    }
    PDU constrainedPDU;
    constrainedPDU.data = thePDU->data;
    constrainedPDU.len = pidparticipantguid_rtps->parameterlength;
    constrainedPDU.watermark = thePDU->watermark;
    constrainedPDU.curPos = pos;
    constrainedPDU.curBitPos = 0;
    constrainedPDU.remaining = pidparticipantguid_rtps->parameterlength;
    PARTICIPANTGUID_RTPS participantguid;
    if (!parsePARTICIPANTGUID (&participantguid, &constrainedPDU, progname, endianness)) {
        return false;
    }
    pidparticipantguid_rtps->participantguid = participantguid;
    thePDU->curPos += constrainedPDU.len;
    return true;
}

bool parsePIDPARTICIPANTGUID_O (PIDPARTICIPANTGUID_RTPS *pidparticipantguid_rtps, PDU *thePDU, char *progname, uint16_t *type, uint8_t endianness) {
    pidparticipantguid_rtps->parameterkind = *type;
    if (!lengthRemaining (thePDU, 2, progname)) {
        return false;
    }
    pidparticipantguid_rtps->parameterlength = get16_e (thePDU, endianness);
    unsigned long pos = thePDU->curPos;
    if (!lengthRemaining (thePDU, pidparticipantguid_rtps->parameterlength, progname)) {
        return false;
    }
    PDU constrainedPDU;
    constrainedPDU.data = thePDU->data;
    constrainedPDU.len = pidparticipantguid_rtps->parameterlength;
    constrainedPDU.watermark = thePDU->watermark;
    constrainedPDU.curPos = pos;
    constrainedPDU.curBitPos = 0;
    constrainedPDU.remaining = pidparticipantguid_rtps->parameterlength;
    PARTICIPANTGUID_RTPS participantguid;
    if (!parsePARTICIPANTGUID (&participantguid, &constrainedPDU, progname, endianness)) {
        return false;
    }
    pidparticipantguid_rtps->participantguid = participantguid;
    thePDU->curPos += constrainedPDU.len;
    return true;
}

bool parsePARTICIPANTGUID (PARTICIPANTGUID_RTPS *participantguid_rtps, PDU *thePDU, char *progname, uint8_t endianness) {
    if (!lengthRemaining (thePDU, 0, progname)) {
        return false;
    }
    GUIDPREFIX_RTPS guid;
    if (!parseGUIDPREFIX (&guid, thePDU, progname, BIGENDIAN)) {
        return false;
    }
    participantguid_rtps->guid = guid;
    ENTITYID_RTPS entityid;
    if (!parseENTITYID (&entityid, thePDU, progname, BIGENDIAN)) {
        return false;
    }
    participantguid_rtps->entityid = entityid;
    return true;
}

bool parsePIDVENDORID (PIDVENDORID_RTPS *pidvendorid_rtps, PDU *thePDU, char *progname, uint8_t endianness) {
    if (!lengthRemaining (thePDU, 4, progname)) {
        return false;
    }
    pidvendorid_rtps->parameterkind = get16_e (thePDU, endianness);
    if (!(pidvendorid_rtps->parameterkind == 22)) {
        return false;
    }
    pidvendorid_rtps->parameterlength = get16_e (thePDU, endianness);
    unsigned long pos = thePDU->curPos;
    if (!lengthRemaining (thePDU, pidvendorid_rtps->parameterlength, progname)) {
        return false;
    }
    PDU constrainedPDU;
    constrainedPDU.data = thePDU->data;
    constrainedPDU.len = pidvendorid_rtps->parameterlength;
    constrainedPDU.watermark = thePDU->watermark;
    constrainedPDU.curPos = pos;
    constrainedPDU.curBitPos = 0;
    constrainedPDU.remaining = pidvendorid_rtps->parameterlength;
    VENDORID_RTPS vendor;
    if (!parseVENDORID (&vendor, &constrainedPDU, progname, endianness)) {
        return false;
    }
    pidvendorid_rtps->vendor = vendor;
    thePDU->curPos += constrainedPDU.len;
    return true;
}

bool parsePIDVENDORID_O (PIDVENDORID_RTPS *pidvendorid_rtps, PDU *thePDU, char *progname, uint16_t *type, uint8_t endianness) {
    pidvendorid_rtps->parameterkind = *type;
    if (!lengthRemaining (thePDU, 2, progname)) {
        return false;
    }
    pidvendorid_rtps->parameterlength = get16_e (thePDU, endianness);
    unsigned long pos = thePDU->curPos;
    if (!lengthRemaining (thePDU, pidvendorid_rtps->parameterlength, progname)) {
        return false;
    }
    PDU constrainedPDU;
    constrainedPDU.data = thePDU->data;
    constrainedPDU.len = pidvendorid_rtps->parameterlength;
    constrainedPDU.watermark = thePDU->watermark;
    constrainedPDU.curPos = pos;
    constrainedPDU.curBitPos = 0;
    constrainedPDU.remaining = pidvendorid_rtps->parameterlength;
    VENDORID_RTPS vendor;
    if (!parseVENDORID (&vendor, &constrainedPDU, progname, endianness)) {
        return false;
    }
    pidvendorid_rtps->vendor = vendor;
    thePDU->curPos += constrainedPDU.len;
    return true;
}

bool parseVENDORID (VENDORID_RTPS *vendorid_rtps, PDU *thePDU, char *progname, uint8_t endianness) {
    if (!lengthRemaining (thePDU, 2, progname)) {
        return false;
    }
    vendorid_rtps->vendorid = get16_e (thePDU, endianness);
    return true;
}

bool parsePIDPARTICIPANTBUILTENDPOINTS (PIDPARTICIPANTBUILTENDPOINTS_RTPS *pidparticipantbuiltendpoints_rtps, PDU *thePDU, char *progname, uint8_t endianness) {
    if (!lengthRemaining (thePDU, 8, progname)) {
        return false;
    }
    pidparticipantbuiltendpoints_rtps->parameterkind = get16_e (thePDU, endianness);
    if (!(pidparticipantbuiltendpoints_rtps->parameterkind == 68)) {
        return false;
    }
    pidparticipantbuiltendpoints_rtps->parameterlength = get16_e (thePDU, endianness);
    pidparticipantbuiltendpoints_rtps->builtin = get32_e (thePDU, endianness);
    return true;
}

bool parsePIDPARTICIPANTBUILTENDPOINTS_O (PIDPARTICIPANTBUILTENDPOINTS_RTPS *pidparticipantbuiltendpoints_rtps, PDU *thePDU, char *progname, uint16_t *type,
  uint8_t endianness) {
    pidparticipantbuiltendpoints_rtps->parameterkind = *type;
    if (!lengthRemaining (thePDU, 6, progname)) {
        return false;
    }
    pidparticipantbuiltendpoints_rtps->parameterlength = get16_e (thePDU, endianness);
    pidparticipantbuiltendpoints_rtps->builtin = get32_e (thePDU, endianness);
    return true;
}

bool parsePIDBUILTINENDPOINTSET (PIDBUILTINENDPOINTSET_RTPS *pidbuiltinendpointset_rtps, PDU *thePDU, char *progname, uint8_t endianness) {
    if (!lengthRemaining (thePDU, 4, progname)) {
        return false;
    }
    pidbuiltinendpointset_rtps->parameterkind = get16_e (thePDU, endianness);
    if (!(pidbuiltinendpointset_rtps->parameterkind == 88)) {
        return false;
    }
    pidbuiltinendpointset_rtps->parameterlength = get16_e (thePDU, endianness);
    unsigned long pos = thePDU->curPos;
    if (!lengthRemaining (thePDU, pidbuiltinendpointset_rtps->parameterlength, progname)) {
        return false;
    }
    PDU constrainedPDU;
    constrainedPDU.data = thePDU->data;
    constrainedPDU.len = pidbuiltinendpointset_rtps->parameterlength;
    constrainedPDU.watermark = thePDU->watermark;
    constrainedPDU.curPos = pos;
    constrainedPDU.curBitPos = 0;
    constrainedPDU.remaining = pidbuiltinendpointset_rtps->parameterlength;
    FLAGS_RTPS builtin;
    if (!parseFLAGS (&builtin, &constrainedPDU, progname, endianness)) {
        return false;
    }
    pidbuiltinendpointset_rtps->builtin = builtin;
    thePDU->curPos += constrainedPDU.len;
    return true;
}

bool parsePIDBUILTINENDPOINTSET_O (PIDBUILTINENDPOINTSET_RTPS *pidbuiltinendpointset_rtps, PDU *thePDU, char *progname, uint16_t *type, uint8_t endianness) {
    pidbuiltinendpointset_rtps->parameterkind = *type;
    if (!lengthRemaining (thePDU, 2, progname)) {
        return false;
    }
    pidbuiltinendpointset_rtps->parameterlength = get16_e (thePDU, endianness);
    unsigned long pos = thePDU->curPos;
    if (!lengthRemaining (thePDU, pidbuiltinendpointset_rtps->parameterlength, progname)) {
        return false;
    }
    PDU constrainedPDU;
    constrainedPDU.data = thePDU->data;
    constrainedPDU.len = pidbuiltinendpointset_rtps->parameterlength;
    constrainedPDU.watermark = thePDU->watermark;
    constrainedPDU.curPos = pos;
    constrainedPDU.curBitPos = 0;
    constrainedPDU.remaining = pidbuiltinendpointset_rtps->parameterlength;
    FLAGS_RTPS builtin;
    if (!parseFLAGS (&builtin, &constrainedPDU, progname, endianness)) {
        return false;
    }
    pidbuiltinendpointset_rtps->builtin = builtin;
    thePDU->curPos += constrainedPDU.len;
    return true;
}

bool parseFLAGS (FLAGS_RTPS *flags_rtps, PDU *thePDU, char *progname, uint8_t endianness) {
    if (!lengthRemaining (thePDU, 4, progname)) {
        return false;
    }
    flags_rtps->flags = get32_e (thePDU, endianness);
    return true;
}

bool parsePIDMETATRAFFICUNILOCATOR (PIDMETATRAFFICUNILOCATOR_RTPS *pidmetatrafficunilocator_rtps, PDU *thePDU, char *progname, uint8_t endianness) {
    if (!lengthRemaining (thePDU, 4, progname)) {
        return false;
    }
    pidmetatrafficunilocator_rtps->parameterkind = get16_e (thePDU, endianness);
    if (!(pidmetatrafficunilocator_rtps->parameterkind == 50)) {
        return false;
    }
    pidmetatrafficunilocator_rtps->parameterlength = get16_e (thePDU, endianness);
    unsigned long pos = thePDU->curPos;
    if (!lengthRemaining (thePDU, pidmetatrafficunilocator_rtps->parameterlength, progname)) {
        return false;
    }
    PDU constrainedPDU;
    constrainedPDU.data = thePDU->data;
    constrainedPDU.len = pidmetatrafficunilocator_rtps->parameterlength;
    constrainedPDU.watermark = thePDU->watermark;
    constrainedPDU.curPos = pos;
    constrainedPDU.curBitPos = 0;
    constrainedPDU.remaining = pidmetatrafficunilocator_rtps->parameterlength;
    LOCATOR_RTPS locator;
    if (!parseLOCATOR (&locator, &constrainedPDU, progname, endianness)) {
        return false;
    }
    pidmetatrafficunilocator_rtps->locator = locator;
    thePDU->curPos += constrainedPDU.len;
    return true;
}

bool parsePIDMETATRAFFICUNILOCATOR_O (PIDMETATRAFFICUNILOCATOR_RTPS *pidmetatrafficunilocator_rtps, PDU *thePDU, char *progname, uint16_t *type, uint8_t
  endianness) {
    pidmetatrafficunilocator_rtps->parameterkind = *type;
    if (!lengthRemaining (thePDU, 2, progname)) {
        return false;
    }
    pidmetatrafficunilocator_rtps->parameterlength = get16_e (thePDU, endianness);
    unsigned long pos = thePDU->curPos;
    if (!lengthRemaining (thePDU, pidmetatrafficunilocator_rtps->parameterlength, progname)) {
        return false;
    }
    PDU constrainedPDU;
    constrainedPDU.data = thePDU->data;
    constrainedPDU.len = pidmetatrafficunilocator_rtps->parameterlength;
    constrainedPDU.watermark = thePDU->watermark;
    constrainedPDU.curPos = pos;
    constrainedPDU.curBitPos = 0;
    constrainedPDU.remaining = pidmetatrafficunilocator_rtps->parameterlength;
    LOCATOR_RTPS locator;
    if (!parseLOCATOR (&locator, &constrainedPDU, progname, endianness)) {
        return false;
    }
    pidmetatrafficunilocator_rtps->locator = locator;
    thePDU->curPos += constrainedPDU.len;
    return true;
}

bool parsePIDMETATRAFFICMULTILOCATOR (PIDMETATRAFFICMULTILOCATOR_RTPS *pidmetatrafficmultilocator_rtps, PDU *thePDU, char *progname, uint8_t endianness) {
    if (!lengthRemaining (thePDU, 4, progname)) {
        return false;
    }
    pidmetatrafficmultilocator_rtps->parameterkind = get16_e (thePDU, endianness);
    if (!(pidmetatrafficmultilocator_rtps->parameterkind == 51)) {
        return false;
    }
    pidmetatrafficmultilocator_rtps->parameterlength = get16_e (thePDU, endianness);
    unsigned long pos = thePDU->curPos;
    if (!lengthRemaining (thePDU, pidmetatrafficmultilocator_rtps->parameterlength, progname)) {
        return false;
    }
    PDU constrainedPDU;
    constrainedPDU.data = thePDU->data;
    constrainedPDU.len = pidmetatrafficmultilocator_rtps->parameterlength;
    constrainedPDU.watermark = thePDU->watermark;
    constrainedPDU.curPos = pos;
    constrainedPDU.curBitPos = 0;
    constrainedPDU.remaining = pidmetatrafficmultilocator_rtps->parameterlength;
    LOCATOR_RTPS locator;
    if (!parseLOCATOR (&locator, &constrainedPDU, progname, endianness)) {
        return false;
    }
    pidmetatrafficmultilocator_rtps->locator = locator;
    thePDU->curPos += constrainedPDU.len;
    return true;
}

bool parsePIDMETATRAFFICMULTILOCATOR_O (PIDMETATRAFFICMULTILOCATOR_RTPS *pidmetatrafficmultilocator_rtps, PDU *thePDU, char *progname, uint16_t *type, uint8_t
  endianness) {
    pidmetatrafficmultilocator_rtps->parameterkind = *type;
    if (!lengthRemaining (thePDU, 2, progname)) {
        return false;
    }
    pidmetatrafficmultilocator_rtps->parameterlength = get16_e (thePDU, endianness);
    unsigned long pos = thePDU->curPos;
    if (!lengthRemaining (thePDU, pidmetatrafficmultilocator_rtps->parameterlength, progname)) {
        return false;
    }
    PDU constrainedPDU;
    constrainedPDU.data = thePDU->data;
    constrainedPDU.len = pidmetatrafficmultilocator_rtps->parameterlength;
    constrainedPDU.watermark = thePDU->watermark;
    constrainedPDU.curPos = pos;
    constrainedPDU.curBitPos = 0;
    constrainedPDU.remaining = pidmetatrafficmultilocator_rtps->parameterlength;
    LOCATOR_RTPS locator;
    if (!parseLOCATOR (&locator, &constrainedPDU, progname, endianness)) {
        return false;
    }
    pidmetatrafficmultilocator_rtps->locator = locator;
    thePDU->curPos += constrainedPDU.len;
    return true;
}

bool parsePIDDEFUNILOCATOR (PIDDEFUNILOCATOR_RTPS *piddefunilocator_rtps, PDU *thePDU, char *progname, uint8_t endianness) {
    if (!lengthRemaining (thePDU, 4, progname)) {
        return false;
    }
    piddefunilocator_rtps->parameterkind = get16_e (thePDU, endianness);
    if (!(piddefunilocator_rtps->parameterkind == 49)) {
        return false;
    }
    piddefunilocator_rtps->parameterlength = get16_e (thePDU, endianness);
    unsigned long pos = thePDU->curPos;
    if (!lengthRemaining (thePDU, piddefunilocator_rtps->parameterlength, progname)) {
        return false;
    }
    PDU constrainedPDU;
    constrainedPDU.data = thePDU->data;
    constrainedPDU.len = piddefunilocator_rtps->parameterlength;
    constrainedPDU.watermark = thePDU->watermark;
    constrainedPDU.curPos = pos;
    constrainedPDU.curBitPos = 0;
    constrainedPDU.remaining = piddefunilocator_rtps->parameterlength;
    LOCATOR_RTPS locator;
    if (!parseLOCATOR (&locator, &constrainedPDU, progname, endianness)) {
        return false;
    }
    piddefunilocator_rtps->locator = locator;
    thePDU->curPos += constrainedPDU.len;
    return true;
}

bool parsePIDDEFUNILOCATOR_O (PIDDEFUNILOCATOR_RTPS *piddefunilocator_rtps, PDU *thePDU, char *progname, uint16_t *type, uint8_t endianness) {
    piddefunilocator_rtps->parameterkind = *type;
    if (!lengthRemaining (thePDU, 2, progname)) {
        return false;
    }
    piddefunilocator_rtps->parameterlength = get16_e (thePDU, endianness);
    unsigned long pos = thePDU->curPos;
    if (!lengthRemaining (thePDU, piddefunilocator_rtps->parameterlength, progname)) {
        return false;
    }
    PDU constrainedPDU;
    constrainedPDU.data = thePDU->data;
    constrainedPDU.len = piddefunilocator_rtps->parameterlength;
    constrainedPDU.watermark = thePDU->watermark;
    constrainedPDU.curPos = pos;
    constrainedPDU.curBitPos = 0;
    constrainedPDU.remaining = piddefunilocator_rtps->parameterlength;
    LOCATOR_RTPS locator;
    if (!parseLOCATOR (&locator, &constrainedPDU, progname, endianness)) {
        return false;
    }
    piddefunilocator_rtps->locator = locator;
    thePDU->curPos += constrainedPDU.len;
    return true;
}

bool parsePIDDEFMULTILOCATOR (PIDDEFMULTILOCATOR_RTPS *piddefmultilocator_rtps, PDU *thePDU, char *progname, uint8_t endianness) {
    if (!lengthRemaining (thePDU, 4, progname)) {
        return false;
    }
    piddefmultilocator_rtps->parameterkind = get16_e (thePDU, endianness);
    if (!(piddefmultilocator_rtps->parameterkind == 72)) {
        return false;
    }
    piddefmultilocator_rtps->parameterlength = get16_e (thePDU, endianness);
    LOCATOR_RTPS locator;
    if (!parseLOCATOR (&locator, thePDU, progname, endianness)) {
        return false;
    }
    piddefmultilocator_rtps->locator = locator;
    return true;
}

bool parsePIDDEFMULTILOCATOR_O (PIDDEFMULTILOCATOR_RTPS *piddefmultilocator_rtps, PDU *thePDU, char *progname, uint16_t *type, uint8_t endianness) {
    piddefmultilocator_rtps->parameterkind = *type;
    if (!lengthRemaining (thePDU, 2, progname)) {
        return false;
    }
    piddefmultilocator_rtps->parameterlength = get16_e (thePDU, endianness);
    LOCATOR_RTPS locator;
    if (!parseLOCATOR (&locator, thePDU, progname, endianness)) {
        return false;
    }
    piddefmultilocator_rtps->locator = locator;
    return true;
}

bool parseLOCATOR (LOCATOR_RTPS *locator_rtps, PDU *thePDU, char *progname, uint8_t endianness) {
    if (!lengthRemaining (thePDU, 24, progname)) {
        return false;
    }
    locator_rtps->kind = get32_e (thePDU, endianness);
    locator_rtps->port = get32_e (thePDU, endianness);
    memcpy (locator_rtps->address, &thePDU->data[thePDU->curPos], 16);
    thePDU->curPos += 16;
    if (locator_rtps->address[16 - 1] != '\0') {
    }
    return true;
}

bool parsePIDPARTICIPANTLIVECOUNT (PIDPARTICIPANTLIVECOUNT_RTPS *pidparticipantlivecount_rtps, PDU *thePDU, char *progname, uint8_t endianness) {
    if (!lengthRemaining (thePDU, 8, progname)) {
        return false;
    }
    pidparticipantlivecount_rtps->parameterkind = get16_e (thePDU, endianness);
    if (!(pidparticipantlivecount_rtps->parameterkind == 52)) {
        return false;
    }
    pidparticipantlivecount_rtps->parameterlength = get16_e (thePDU, endianness);
    pidparticipantlivecount_rtps->manuallivecount = get32_e (thePDU, endianness);
    return true;
}

bool parsePIDPARTICIPANTLIVECOUNT_O (PIDPARTICIPANTLIVECOUNT_RTPS *pidparticipantlivecount_rtps, PDU *thePDU, char *progname, uint16_t *type, uint8_t endianness
  ) {
    pidparticipantlivecount_rtps->parameterkind = *type;
    if (!lengthRemaining (thePDU, 6, progname)) {
        return false;
    }
    pidparticipantlivecount_rtps->parameterlength = get16_e (thePDU, endianness);
    pidparticipantlivecount_rtps->manuallivecount = get32_e (thePDU, endianness);
    return true;
}

bool parsePIDPARTICIPANTLEASE (PIDPARTICIPANTLEASE_RTPS *pidparticipantlease_rtps, PDU *thePDU, char *progname, uint8_t endianness) {
    if (!lengthRemaining (thePDU, 4, progname)) {
        return false;
    }
    pidparticipantlease_rtps->parameterkind = get16_e (thePDU, endianness);
    if (!(pidparticipantlease_rtps->parameterkind == 2)) {
        return false;
    }
    pidparticipantlease_rtps->parameterlength = get16_e (thePDU, endianness);
    unsigned long pos = thePDU->curPos;
    if (!lengthRemaining (thePDU, pidparticipantlease_rtps->parameterlength, progname)) {
        return false;
    }
    PDU constrainedPDU;
    constrainedPDU.data = thePDU->data;
    constrainedPDU.len = pidparticipantlease_rtps->parameterlength;
    constrainedPDU.watermark = thePDU->watermark;
    constrainedPDU.curPos = pos;
    constrainedPDU.curBitPos = 0;
    constrainedPDU.remaining = pidparticipantlease_rtps->parameterlength;
    LEASEDURATION_RTPS duration;
    if (!parseLEASEDURATION (&duration, &constrainedPDU, progname, endianness)) {
        return false;
    }
    pidparticipantlease_rtps->duration = duration;
    thePDU->curPos += constrainedPDU.len;
    return true;
}

bool parsePIDPARTICIPANTLEASE_O (PIDPARTICIPANTLEASE_RTPS *pidparticipantlease_rtps, PDU *thePDU, char *progname, uint16_t *type, uint8_t endianness) {
    pidparticipantlease_rtps->parameterkind = *type;
    if (!lengthRemaining (thePDU, 2, progname)) {
        return false;
    }
    pidparticipantlease_rtps->parameterlength = get16_e (thePDU, endianness);
    unsigned long pos = thePDU->curPos;
    if (!lengthRemaining (thePDU, pidparticipantlease_rtps->parameterlength, progname)) {
        return false;
    }
    PDU constrainedPDU;
    constrainedPDU.data = thePDU->data;
    constrainedPDU.len = pidparticipantlease_rtps->parameterlength;
    constrainedPDU.watermark = thePDU->watermark;
    constrainedPDU.curPos = pos;
    constrainedPDU.curBitPos = 0;
    constrainedPDU.remaining = pidparticipantlease_rtps->parameterlength;
    LEASEDURATION_RTPS duration;
    if (!parseLEASEDURATION (&duration, &constrainedPDU, progname, endianness)) {
        return false;
    }
    pidparticipantlease_rtps->duration = duration;
    thePDU->curPos += constrainedPDU.len;
    return true;
}

bool parseLEASEDURATION (LEASEDURATION_RTPS *leaseduration_rtps, PDU *thePDU, char *progname, uint8_t endianness) {
    if (!lengthRemaining (thePDU, 8, progname)) {
        return false;
    }
    leaseduration_rtps->seconds = get32_e (thePDU, endianness);
    leaseduration_rtps->fraction = get32_e (thePDU, endianness);
    return true;
}

bool parsePIDSENTINAL (PIDSENTINAL_RTPS *pidsentinal_rtps, PDU *thePDU, char *progname, uint8_t endianness) {
    if (!lengthRemaining (thePDU, 4, progname)) {
        return false;
    }
    pidsentinal_rtps->parameterkind = get16_e (thePDU, endianness);
    if (!(pidsentinal_rtps->parameterkind == 1)) {
        return false;
    }
    pidsentinal_rtps->parameterlength = get16_e (thePDU, endianness);
    return true;
}

bool parsePIDSENTINAL_O (PIDSENTINAL_RTPS *pidsentinal_rtps, PDU *thePDU, char *progname, uint16_t *type, uint8_t endianness) {
    pidsentinal_rtps->parameterkind = *type;
    if (!lengthRemaining (thePDU, 2, progname)) {
        return false;
    }
    pidsentinal_rtps->parameterlength = get16_e (thePDU, endianness);
    return true;
}

bool parseENTITYID (ENTITYID_RTPS *entityid_rtps, PDU *thePDU, char *progname, uint8_t endianness) {
    if (!lengthRemaining (thePDU, 4, progname)) {
        return false;
    }
    entityid_rtps->key = get24_e (thePDU, endianness);
    entityid_rtps->kind = get8_e (thePDU, endianness);
    return true;
}

bool parseSNSTATE (SNSTATE_RTPS *snstate_rtps, PDU *thePDU, char *progname, uint8_t endianness) {
    if (!lengthRemaining (thePDU, 12, progname)) {
        return false;
    }
    snstate_rtps->bitmap = NULL;
    snstate_rtps->bitmapbase = get64_e (thePDU, endianness);
    snstate_rtps->nmbits = get32_e (thePDU, endianness);
    if (snstate_rtps->nmbits & 15) {
        snstate_rtps->bitmap = (SLACK_RTPS *) malloc (sizeof (SLACK_RTPS));
        if (snstate_rtps->bitmap == NULL) {
            return false;
        }
        if (!parseSLACK (snstate_rtps->bitmap, thePDU, progname, endianness)) {
            free (snstate_rtps->bitmap);
            snstate_rtps->bitmap = NULL;
            return false;
        }
    }
    else {
        snstate_rtps->bitmap = NULL;
    }
    return true;
}

bool parseSLACK (SLACK_RTPS *slack_rtps, PDU *thePDU, char *progname, uint8_t endianness) {
    if (!lengthRemaining (thePDU, 4, progname)) {
        return false;
    }
    slack_rtps->slack = get32_e (thePDU, endianness);
    return true;
}

void freePDU_RTPS (PDU_RTPS *mainpdu) {
    if (mainpdu->type == PING_RTPS_VAL) {
    }
    if (mainpdu->type == FULL_RTPS_VAL) {
        if (mainpdu->ptr.full_rtps.submsg != NULL) {
            for (int i = 0; i < mainpdu->ptr.full_rtps.submsgcount; ++i) {
                if (&mainpdu->ptr.full_rtps.submsg [i] != NULL) {
                    if (mainpdu->ptr.full_rtps.submsg [i].type > 0) {
                        switch (mainpdu->ptr.full_rtps.submsg [i].type) {
                        case DATAPSUB_RTPS_VAL :
                            {
                                if (mainpdu->ptr.full_rtps.submsg [i].ptr.datapsub_rtps.inlineqos != NULL) {
                                    if (mainpdu->ptr.full_rtps.submsg [i].ptr.datapsub_rtps.inlineqos->qos != NULL) {
                                        for (int j = 0; j < mainpdu->ptr.full_rtps.submsg [i].ptr.datapsub_rtps.inlineqos->qoscount; ++j) {
                                            if (&mainpdu->ptr.full_rtps.submsg [i].ptr.datapsub_rtps.inlineqos->qos [j] != NULL) {
                                                if (mainpdu->ptr.full_rtps.submsg [i].ptr.datapsub_rtps.inlineqos->qos [j].type > 0) {
                                                    switch (mainpdu->ptr.full_rtps.submsg [i].ptr.datapsub_rtps.inlineqos->qos [j].type) {
                                                    case PIDSTATUSINFO_RTPS_VAL :
                                                        {
                                                            if (mainpdu->ptr.full_rtps.submsg [i].ptr.datapsub_rtps.inlineqos->qos 
                                                              [j].ptr.pidstatusinfo_rtps.flags != NULL) {
                                                                free (mainpdu->ptr.full_rtps.submsg [i].ptr.datapsub_rtps.inlineqos->qos 
                                                                  [j].ptr.pidstatusinfo_rtps.flags);
                                                                mainpdu->ptr.full_rtps.submsg [i].ptr.datapsub_rtps.inlineqos->qos 
                                                                  [j].ptr.pidstatusinfo_rtps.flags = NULL;
                                                            }
                                                        }
                                                        break;
                                                    case PIDKEYHASH_RTPS_VAL :
                                                        {
                                                            if (mainpdu->ptr.full_rtps.submsg [i].ptr.datapsub_rtps.inlineqos->qos [j].ptr.pidkeyhash_rtps.guid
                                                              != NULL) {
                                                                free (mainpdu->ptr.full_rtps.submsg [i].ptr.datapsub_rtps.inlineqos->qos 
                                                                  [j].ptr.pidkeyhash_rtps.guid);
                                                                mainpdu->ptr.full_rtps.submsg [i].ptr.datapsub_rtps.inlineqos->qos [j].ptr.pidkeyhash_rtps.guid
                                                                  = NULL;
                                                            }
                                                        }
                                                        break;
                                                    case PIDSENTINAL_RTPS_VAL :
                                                        {
                                                        }
                                                        break;
                                                    }
                                                }
                                            }
                                        }
                                        if (mainpdu->ptr.full_rtps.submsg [i].ptr.datapsub_rtps.inlineqos->qos != NULL) {
                                            free (mainpdu->ptr.full_rtps.submsg [i].ptr.datapsub_rtps.inlineqos->qos);
                                            mainpdu->ptr.full_rtps.submsg [i].ptr.datapsub_rtps.inlineqos->qos = NULL;
                                        }
                                    }
                                }
                                if (mainpdu->ptr.full_rtps.submsg [i].ptr.datapsub_rtps.inlineqos != NULL) {
                                    free (mainpdu->ptr.full_rtps.submsg [i].ptr.datapsub_rtps.inlineqos);
                                    mainpdu->ptr.full_rtps.submsg [i].ptr.datapsub_rtps.inlineqos = NULL;
                                }
                                if (mainpdu->ptr.full_rtps.submsg [i].ptr.datapsub_rtps.serializeddata != NULL) {
                                    if (mainpdu->ptr.full_rtps.submsg [i].ptr.datapsub_rtps.serializeddata->particdata != NULL) {
                                        for (int j = 0; j < mainpdu->ptr.full_rtps.submsg [i].ptr.datapsub_rtps.serializeddata->particdatacount; ++j) {
                                            if (&mainpdu->ptr.full_rtps.submsg [i].ptr.datapsub_rtps.serializeddata->particdata [j] != NULL) {
                                                if (mainpdu->ptr.full_rtps.submsg [i].ptr.datapsub_rtps.serializeddata->particdata [j].type > 0) {
                                                    switch (mainpdu->ptr.full_rtps.submsg [i].ptr.datapsub_rtps.serializeddata->particdata [j].type) {
                                                    case PIDPROTOVERSION_RTPS_VAL :
                                                        {
                                                        }
                                                        break;
                                                    case PIDPARTICIPANTGUID_RTPS_VAL :
                                                        {
                                                        }
                                                        break;
                                                    case PIDVENDORID_RTPS_VAL :
                                                        {
                                                        }
                                                        break;
                                                    case PIDPARTICIPANTBUILTENDPOINTS_RTPS_VAL :
                                                        {
                                                        }
                                                        break;
                                                    case PIDBUILTINENDPOINTSET_RTPS_VAL :
                                                        {
                                                        }
                                                        break;
                                                    case PIDMETATRAFFICUNILOCATOR_RTPS_VAL :
                                                        {
                                                        }
                                                        break;
                                                    case PIDDEFMULTILOCATOR_RTPS_VAL :
                                                        {
                                                        }
                                                        break;
                                                    case PIDPARTICIPANTLIVECOUNT_RTPS_VAL :
                                                        {
                                                        }
                                                        break;
                                                    case PIDPARTICIPANTLEASE_RTPS_VAL :
                                                        {
                                                        }
                                                        break;
                                                    case PIDSENTINAL_RTPS_VAL :
                                                        {
                                                        }
                                                        break;
                                                    case PIDDEFUNILOCATOR_RTPS_VAL :
                                                        {
                                                        }
                                                        break;
                                                    case PIDMETATRAFFICMULTILOCATOR_RTPS_VAL :
                                                        {
                                                        }
                                                        break;
                                                    case PIDPROPERTYLIST_RTPS_VAL :
                                                        {
                                                            if (mainpdu->ptr.full_rtps.submsg [i].ptr.datapsub_rtps.serializeddata->particdata 
                                                              [j].ptr.pidpropertylist_rtps.properties.list != NULL) {
                                                                for (int k = 0; k < mainpdu->ptr.full_rtps.submsg 
                                                                  [i].ptr.datapsub_rtps.serializeddata->particdata 
                                                                  [j].ptr.pidpropertylist_rtps.properties.listcount; ++k) {
                                                                    if (&mainpdu->ptr.full_rtps.submsg [i].ptr.datapsub_rtps.serializeddata->particdata 
                                                                      [j].ptr.pidpropertylist_rtps.properties.list [k] != NULL) {
                                                                        if (mainpdu->ptr.full_rtps.submsg [i].ptr.datapsub_rtps.serializeddata->particdata 
                                                                          [j].ptr.pidpropertylist_rtps.properties.list [k].name.name != NULL) {
                                                                            free (mainpdu->ptr.full_rtps.submsg 
                                                                              [i].ptr.datapsub_rtps.serializeddata->particdata 
                                                                              [j].ptr.pidpropertylist_rtps.properties.list [k].name.name);
                                                                            mainpdu->ptr.full_rtps.submsg [i].ptr.datapsub_rtps.serializeddata->particdata 
                                                                              [j].ptr.pidpropertylist_rtps.properties.list [k].name.name = NULL;
                                                                        }
                                                                        if (mainpdu->ptr.full_rtps.submsg [i].ptr.datapsub_rtps.serializeddata->particdata 
                                                                          [j].ptr.pidpropertylist_rtps.properties.list [k].value.name != NULL) {
                                                                            free (mainpdu->ptr.full_rtps.submsg 
                                                                              [i].ptr.datapsub_rtps.serializeddata->particdata 
                                                                              [j].ptr.pidpropertylist_rtps.properties.list [k].value.name);
                                                                            mainpdu->ptr.full_rtps.submsg [i].ptr.datapsub_rtps.serializeddata->particdata 
                                                                              [j].ptr.pidpropertylist_rtps.properties.list [k].value.name = NULL;
                                                                        }
                                                                    }
                                                                }
                                                                if (mainpdu->ptr.full_rtps.submsg [i].ptr.datapsub_rtps.serializeddata->particdata 
                                                                  [j].ptr.pidpropertylist_rtps.properties.list != NULL) {
                                                                    free (mainpdu->ptr.full_rtps.submsg [i].ptr.datapsub_rtps.serializeddata->particdata 
                                                                      [j].ptr.pidpropertylist_rtps.properties.list);
                                                                    mainpdu->ptr.full_rtps.submsg [i].ptr.datapsub_rtps.serializeddata->particdata 
                                                                      [j].ptr.pidpropertylist_rtps.properties.list = NULL;
                                                                }
                                                            }
                                                        }
                                                        break;
                                                    case PIDENTITYNAME_RTPS_VAL :
                                                        {
                                                            if (mainpdu->ptr.full_rtps.submsg [i].ptr.datapsub_rtps.serializeddata->particdata 
                                                              [j].ptr.pidentityname_rtps.entityname.name != NULL) {
                                                                free (mainpdu->ptr.full_rtps.submsg [i].ptr.datapsub_rtps.serializeddata->particdata 
                                                                  [j].ptr.pidentityname_rtps.entityname.name);
                                                                mainpdu->ptr.full_rtps.submsg [i].ptr.datapsub_rtps.serializeddata->particdata 
                                                                  [j].ptr.pidentityname_rtps.entityname.name = NULL;
                                                            }
                                                        }
                                                        break;
                                                    case PIDROLENAME_RTPS_VAL :
                                                        {
                                                            if (mainpdu->ptr.full_rtps.submsg [i].ptr.datapsub_rtps.serializeddata->particdata 
                                                              [j].ptr.pidrolename_rtps.rolename.name != NULL) {
                                                                free (mainpdu->ptr.full_rtps.submsg [i].ptr.datapsub_rtps.serializeddata->particdata 
                                                                  [j].ptr.pidrolename_rtps.rolename.name);
                                                                mainpdu->ptr.full_rtps.submsg [i].ptr.datapsub_rtps.serializeddata->particdata 
                                                                  [j].ptr.pidrolename_rtps.rolename.name = NULL;
                                                            }
                                                        }
                                                        break;
                                                    case PIDPEERHOSTEPOCH_RTPS_VAL :
                                                        {
                                                            if (mainpdu->ptr.full_rtps.submsg [i].ptr.datapsub_rtps.serializeddata->particdata 
                                                              [j].ptr.pidpeerhostepoch_rtps.hostepoch != NULL) {
                                                                free (mainpdu->ptr.full_rtps.submsg [i].ptr.datapsub_rtps.serializeddata->particdata 
                                                                  [j].ptr.pidpeerhostepoch_rtps.hostepoch);
                                                                mainpdu->ptr.full_rtps.submsg [i].ptr.datapsub_rtps.serializeddata->particdata 
                                                                  [j].ptr.pidpeerhostepoch_rtps.hostepoch = NULL;
                                                            }
                                                        }
                                                        break;
                                                    case PIDDOMAINID_RTPS_VAL :
                                                        {
                                                            if (mainpdu->ptr.full_rtps.submsg [i].ptr.datapsub_rtps.serializeddata->particdata 
                                                              [j].ptr.piddomainid_rtps.domainid != NULL) {
                                                                free (mainpdu->ptr.full_rtps.submsg [i].ptr.datapsub_rtps.serializeddata->particdata 
                                                                  [j].ptr.piddomainid_rtps.domainid);
                                                                mainpdu->ptr.full_rtps.submsg [i].ptr.datapsub_rtps.serializeddata->particdata 
                                                                  [j].ptr.piddomainid_rtps.domainid = NULL;
                                                            }
                                                        }
                                                        break;
                                                    case PIDTRANSPORTINFOLIST_RTPS_VAL :
                                                        {
                                                            if (mainpdu->ptr.full_rtps.submsg [i].ptr.datapsub_rtps.serializeddata->particdata 
                                                              [j].ptr.pidtransportinfolist_rtps.transports.info != NULL) {
                                                                for (int k = 0; k < mainpdu->ptr.full_rtps.submsg 
                                                                  [i].ptr.datapsub_rtps.serializeddata->particdata 
                                                                  [j].ptr.pidtransportinfolist_rtps.transports.infocount; ++k) {
                                                                    if (&mainpdu->ptr.full_rtps.submsg [i].ptr.datapsub_rtps.serializeddata->particdata 
                                                                      [j].ptr.pidtransportinfolist_rtps.transports.info [k] != NULL) {
                                                                    }
                                                                }
                                                                if (mainpdu->ptr.full_rtps.submsg [i].ptr.datapsub_rtps.serializeddata->particdata 
                                                                  [j].ptr.pidtransportinfolist_rtps.transports.info != NULL) {
                                                                    free (mainpdu->ptr.full_rtps.submsg [i].ptr.datapsub_rtps.serializeddata->particdata 
                                                                      [j].ptr.pidtransportinfolist_rtps.transports.info);
                                                                    mainpdu->ptr.full_rtps.submsg [i].ptr.datapsub_rtps.serializeddata->particdata 
                                                                      [j].ptr.pidtransportinfolist_rtps.transports.info = NULL;
                                                                }
                                                            }
                                                        }
                                                        break;
                                                    case PIDPRODUCTVERSION_RTPS_VAL :
                                                        {
                                                        }
                                                        break;
                                                    }
                                                }
                                            }
                                        }
                                        if (mainpdu->ptr.full_rtps.submsg [i].ptr.datapsub_rtps.serializeddata->particdata != NULL) {
                                            free (mainpdu->ptr.full_rtps.submsg [i].ptr.datapsub_rtps.serializeddata->particdata);
                                            mainpdu->ptr.full_rtps.submsg [i].ptr.datapsub_rtps.serializeddata->particdata = NULL;
                                        }
                                    }
                                }
                                if (mainpdu->ptr.full_rtps.submsg [i].ptr.datapsub_rtps.serializeddata != NULL) {
                                    free (mainpdu->ptr.full_rtps.submsg [i].ptr.datapsub_rtps.serializeddata);
                                    mainpdu->ptr.full_rtps.submsg [i].ptr.datapsub_rtps.serializeddata = NULL;
                                }
                            }
                            break;
                        case DATASUB_RTPS_VAL :
                            {
                                if (mainpdu->ptr.full_rtps.submsg [i].ptr.datasub_rtps.inlineqos != NULL) {
                                    if (mainpdu->ptr.full_rtps.submsg [i].ptr.datasub_rtps.inlineqos->qos != NULL) {
                                        for (int j = 0; j < mainpdu->ptr.full_rtps.submsg [i].ptr.datasub_rtps.inlineqos->qoscount; ++j) {
                                            if (&mainpdu->ptr.full_rtps.submsg [i].ptr.datasub_rtps.inlineqos->qos [j] != NULL) {
                                                if (mainpdu->ptr.full_rtps.submsg [i].ptr.datasub_rtps.inlineqos->qos [j].type > 0) {
                                                    switch (mainpdu->ptr.full_rtps.submsg [i].ptr.datasub_rtps.inlineqos->qos [j].type) {
                                                    case PIDSTATUSINFO_RTPS_VAL :
                                                        {
                                                            if (mainpdu->ptr.full_rtps.submsg [i].ptr.datasub_rtps.inlineqos->qos 
                                                              [j].ptr.pidstatusinfo_rtps.flags != NULL) {
                                                                free (mainpdu->ptr.full_rtps.submsg [i].ptr.datasub_rtps.inlineqos->qos 
                                                                  [j].ptr.pidstatusinfo_rtps.flags);
                                                                mainpdu->ptr.full_rtps.submsg [i].ptr.datasub_rtps.inlineqos->qos 
                                                                  [j].ptr.pidstatusinfo_rtps.flags = NULL;
                                                            }
                                                        }
                                                        break;
                                                    case PIDKEYHASH_RTPS_VAL :
                                                        {
                                                            if (mainpdu->ptr.full_rtps.submsg [i].ptr.datasub_rtps.inlineqos->qos [j].ptr.pidkeyhash_rtps.guid
                                                              != NULL) {
                                                                free (mainpdu->ptr.full_rtps.submsg [i].ptr.datasub_rtps.inlineqos->qos 
                                                                  [j].ptr.pidkeyhash_rtps.guid);
                                                                mainpdu->ptr.full_rtps.submsg [i].ptr.datasub_rtps.inlineqos->qos [j].ptr.pidkeyhash_rtps.guid =
                                                                  NULL;
                                                            }
                                                        }
                                                        break;
                                                    case PIDSENTINAL_RTPS_VAL :
                                                        {
                                                        }
                                                        break;
                                                    }
                                                }
                                            }
                                        }
                                        if (mainpdu->ptr.full_rtps.submsg [i].ptr.datasub_rtps.inlineqos->qos != NULL) {
                                            free (mainpdu->ptr.full_rtps.submsg [i].ptr.datasub_rtps.inlineqos->qos);
                                            mainpdu->ptr.full_rtps.submsg [i].ptr.datasub_rtps.inlineqos->qos = NULL;
                                        }
                                    }
                                }
                                if (mainpdu->ptr.full_rtps.submsg [i].ptr.datasub_rtps.inlineqos != NULL) {
                                    free (mainpdu->ptr.full_rtps.submsg [i].ptr.datasub_rtps.inlineqos);
                                    mainpdu->ptr.full_rtps.submsg [i].ptr.datasub_rtps.inlineqos = NULL;
                                }
                                if (mainpdu->ptr.full_rtps.submsg [i].ptr.datasub_rtps.serializeddata != NULL) {
                                    free (mainpdu->ptr.full_rtps.submsg [i].ptr.datasub_rtps.serializeddata);
                                    mainpdu->ptr.full_rtps.submsg [i].ptr.datasub_rtps.serializeddata = NULL;
                                }
                            }
                            break;
                        case ACKNACK_RTPS_VAL :
                            {
                                if (mainpdu->ptr.full_rtps.submsg [i].ptr.acknack_rtps.readersn.bitmap != NULL) {
                                    free (mainpdu->ptr.full_rtps.submsg [i].ptr.acknack_rtps.readersn.bitmap);
                                    mainpdu->ptr.full_rtps.submsg [i].ptr.acknack_rtps.readersn.bitmap = NULL;
                                }
                            }
                            break;
                        case HEARTBEAT_RTPS_VAL :
                            {
                            }
                            break;
                        case INFO$DST_RTPS_VAL :
                            {
                            }
                            break;
                        case INFO$TS_RTPS_VAL :
                            {
                            }
                            break;
                        case DATAWSUB_RTPS_VAL :
                            {
                                if (mainpdu->ptr.full_rtps.submsg [i].ptr.datawsub_rtps.inlineqos != NULL) {
                                    if (mainpdu->ptr.full_rtps.submsg [i].ptr.datawsub_rtps.inlineqos->qos != NULL) {
                                        for (int j = 0; j < mainpdu->ptr.full_rtps.submsg [i].ptr.datawsub_rtps.inlineqos->qoscount; ++j) {
                                            if (&mainpdu->ptr.full_rtps.submsg [i].ptr.datawsub_rtps.inlineqos->qos [j] != NULL) {
                                                if (mainpdu->ptr.full_rtps.submsg [i].ptr.datawsub_rtps.inlineqos->qos [j].type > 0) {
                                                    switch (mainpdu->ptr.full_rtps.submsg [i].ptr.datawsub_rtps.inlineqos->qos [j].type) {
                                                    case PIDSTATUSINFO_RTPS_VAL :
                                                        {
                                                            if (mainpdu->ptr.full_rtps.submsg [i].ptr.datawsub_rtps.inlineqos->qos 
                                                              [j].ptr.pidstatusinfo_rtps.flags != NULL) {
                                                                free (mainpdu->ptr.full_rtps.submsg [i].ptr.datawsub_rtps.inlineqos->qos 
                                                                  [j].ptr.pidstatusinfo_rtps.flags);
                                                                mainpdu->ptr.full_rtps.submsg [i].ptr.datawsub_rtps.inlineqos->qos 
                                                                  [j].ptr.pidstatusinfo_rtps.flags = NULL;
                                                            }
                                                        }
                                                        break;
                                                    case PIDKEYHASH_RTPS_VAL :
                                                        {
                                                            if (mainpdu->ptr.full_rtps.submsg [i].ptr.datawsub_rtps.inlineqos->qos [j].ptr.pidkeyhash_rtps.guid
                                                              != NULL) {
                                                                free (mainpdu->ptr.full_rtps.submsg [i].ptr.datawsub_rtps.inlineqos->qos 
                                                                  [j].ptr.pidkeyhash_rtps.guid);
                                                                mainpdu->ptr.full_rtps.submsg [i].ptr.datawsub_rtps.inlineqos->qos [j].ptr.pidkeyhash_rtps.guid
                                                                  = NULL;
                                                            }
                                                        }
                                                        break;
                                                    case PIDSENTINAL_RTPS_VAL :
                                                        {
                                                        }
                                                        break;
                                                    }
                                                }
                                            }
                                        }
                                        if (mainpdu->ptr.full_rtps.submsg [i].ptr.datawsub_rtps.inlineqos->qos != NULL) {
                                            free (mainpdu->ptr.full_rtps.submsg [i].ptr.datawsub_rtps.inlineqos->qos);
                                            mainpdu->ptr.full_rtps.submsg [i].ptr.datawsub_rtps.inlineqos->qos = NULL;
                                        }
                                    }
                                }
                                if (mainpdu->ptr.full_rtps.submsg [i].ptr.datawsub_rtps.inlineqos != NULL) {
                                    free (mainpdu->ptr.full_rtps.submsg [i].ptr.datawsub_rtps.inlineqos);
                                    mainpdu->ptr.full_rtps.submsg [i].ptr.datawsub_rtps.inlineqos = NULL;
                                }
                                if (mainpdu->ptr.full_rtps.submsg [i].ptr.datawsub_rtps.serializeddata != NULL) {
                                    if (mainpdu->ptr.full_rtps.submsg [i].ptr.datawsub_rtps.serializeddata->topicdata != NULL) {
                                        for (int j = 0; j < mainpdu->ptr.full_rtps.submsg [i].ptr.datawsub_rtps.serializeddata->topicdatacount; ++j) {
                                            if (&mainpdu->ptr.full_rtps.submsg [i].ptr.datawsub_rtps.serializeddata->topicdata [j] != NULL) {
                                                if (mainpdu->ptr.full_rtps.submsg [i].ptr.datawsub_rtps.serializeddata->topicdata [j].type > 0) {
                                                    switch (mainpdu->ptr.full_rtps.submsg [i].ptr.datawsub_rtps.serializeddata->topicdata [j].type) {
                                                    case PIDTOPICNAME_RTPS_VAL :
                                                        {
                                                            if (mainpdu->ptr.full_rtps.submsg [i].ptr.datawsub_rtps.serializeddata->topicdata 
                                                              [j].ptr.pidtopicname_rtps.topicname.name != NULL) {
                                                                free (mainpdu->ptr.full_rtps.submsg [i].ptr.datawsub_rtps.serializeddata->topicdata 
                                                                  [j].ptr.pidtopicname_rtps.topicname.name);
                                                                mainpdu->ptr.full_rtps.submsg [i].ptr.datawsub_rtps.serializeddata->topicdata 
                                                                  [j].ptr.pidtopicname_rtps.topicname.name = NULL;
                                                            }
                                                        }
                                                        break;
                                                    case PIDTYPENAME_RTPS_VAL :
                                                        {
                                                            if (mainpdu->ptr.full_rtps.submsg [i].ptr.datawsub_rtps.serializeddata->topicdata 
                                                              [j].ptr.pidtypename_rtps.typename.name != NULL) {
                                                                free (mainpdu->ptr.full_rtps.submsg [i].ptr.datawsub_rtps.serializeddata->topicdata 
                                                                  [j].ptr.pidtypename_rtps.typename.name);
                                                                mainpdu->ptr.full_rtps.submsg [i].ptr.datawsub_rtps.serializeddata->topicdata 
                                                                  [j].ptr.pidtypename_rtps.typename.name = NULL;
                                                            }
                                                        }
                                                        break;
                                                    case PIDRELIABILITY_RTPS_VAL :
                                                        {
                                                            if (mainpdu->ptr.full_rtps.submsg [i].ptr.datawsub_rtps.serializeddata->topicdata 
                                                              [j].ptr.pidreliability_rtps.slack != NULL) {
                                                                free (mainpdu->ptr.full_rtps.submsg [i].ptr.datawsub_rtps.serializeddata->topicdata 
                                                                  [j].ptr.pidreliability_rtps.slack);
                                                                mainpdu->ptr.full_rtps.submsg [i].ptr.datawsub_rtps.serializeddata->topicdata 
                                                                  [j].ptr.pidreliability_rtps.slack = NULL;
                                                            }
                                                        }
                                                        break;
                                                    case PIDENDPOINTGUID_RTPS_VAL :
                                                        {
                                                        }
                                                        break;
                                                    case PIDMULTICASTLOCATOR_RTPS_VAL :
                                                        {
                                                        }
                                                        break;
                                                    case PIDUNICASTLOCATOR_RTPS_VAL :
                                                        {
                                                        }
                                                        break;
                                                    case PIDSENTINAL_RTPS_VAL :
                                                        {
                                                        }
                                                        break;
                                                    case PIDUNKNOWN_RTPS_VAL :
                                                        {
                                                        }
                                                        break;
                                                    case PIDACKKIND_RTPS_VAL :
                                                        {
                                                            if (mainpdu->ptr.full_rtps.submsg [i].ptr.datawsub_rtps.serializeddata->topicdata 
                                                              [j].ptr.pidackkind_rtps.ackkind != NULL) {
                                                                free (mainpdu->ptr.full_rtps.submsg [i].ptr.datawsub_rtps.serializeddata->topicdata 
                                                                  [j].ptr.pidackkind_rtps.ackkind);
                                                                mainpdu->ptr.full_rtps.submsg [i].ptr.datawsub_rtps.serializeddata->topicdata 
                                                                  [j].ptr.pidackkind_rtps.ackkind = NULL;
                                                            }
                                                        }
                                                        break;
                                                    case PIDRECVQUEUE_RTPS_VAL :
                                                        {
                                                            if (mainpdu->ptr.full_rtps.submsg [i].ptr.datawsub_rtps.serializeddata->topicdata 
                                                              [j].ptr.pidrecvqueue_rtps.queuesize != NULL) {
                                                                free (mainpdu->ptr.full_rtps.submsg [i].ptr.datawsub_rtps.serializeddata->topicdata 
                                                                  [j].ptr.pidrecvqueue_rtps.queuesize);
                                                                mainpdu->ptr.full_rtps.submsg [i].ptr.datawsub_rtps.serializeddata->topicdata 
                                                                  [j].ptr.pidrecvqueue_rtps.queuesize = NULL;
                                                            }
                                                        }
                                                        break;
                                                    case PIDTIMEBASEDFILTER_RTPS_VAL :
                                                        {
                                                            if (mainpdu->ptr.full_rtps.submsg [i].ptr.datawsub_rtps.serializeddata->topicdata 
                                                              [j].ptr.pidtimebasedfilter_rtps.leaseduration != NULL) {
                                                                free (mainpdu->ptr.full_rtps.submsg [i].ptr.datawsub_rtps.serializeddata->topicdata 
                                                                  [j].ptr.pidtimebasedfilter_rtps.leaseduration);
                                                                mainpdu->ptr.full_rtps.submsg [i].ptr.datawsub_rtps.serializeddata->topicdata 
                                                                  [j].ptr.pidtimebasedfilter_rtps.leaseduration = NULL;
                                                            }
                                                        }
                                                        break;
                                                    case PIDLIVELINESS_RTPS_VAL :
                                                        {
                                                            if (mainpdu->ptr.full_rtps.submsg [i].ptr.datawsub_rtps.serializeddata->topicdata 
                                                              [j].ptr.pidliveliness_rtps.liveliness != NULL) {
                                                                free (mainpdu->ptr.full_rtps.submsg [i].ptr.datawsub_rtps.serializeddata->topicdata 
                                                                  [j].ptr.pidliveliness_rtps.liveliness);
                                                                mainpdu->ptr.full_rtps.submsg [i].ptr.datawsub_rtps.serializeddata->topicdata 
                                                                  [j].ptr.pidliveliness_rtps.liveliness = NULL;
                                                            }
                                                        }
                                                        break;
                                                    case PIDDURABILITY_RTPS_VAL :
                                                        {
                                                            if (mainpdu->ptr.full_rtps.submsg [i].ptr.datawsub_rtps.serializeddata->topicdata 
                                                              [j].ptr.piddurability_rtps.durability != NULL) {
                                                                free (mainpdu->ptr.full_rtps.submsg [i].ptr.datawsub_rtps.serializeddata->topicdata 
                                                                  [j].ptr.piddurability_rtps.durability);
                                                                mainpdu->ptr.full_rtps.submsg [i].ptr.datawsub_rtps.serializeddata->topicdata 
                                                                  [j].ptr.piddurability_rtps.durability = NULL;
                                                            }
                                                        }
                                                        break;
                                                    case PIDDIRECTCOMMUNICATION_RTPS_VAL :
                                                        {
                                                        }
                                                        break;
                                                    case PIDOWNERSHIP_RTPS_VAL :
                                                        {
                                                            if (mainpdu->ptr.full_rtps.submsg [i].ptr.datawsub_rtps.serializeddata->topicdata 
                                                              [j].ptr.pidownership_rtps.kind != NULL) {
                                                                free (mainpdu->ptr.full_rtps.submsg [i].ptr.datawsub_rtps.serializeddata->topicdata 
                                                                  [j].ptr.pidownership_rtps.kind);
                                                                mainpdu->ptr.full_rtps.submsg [i].ptr.datawsub_rtps.serializeddata->topicdata 
                                                                  [j].ptr.pidownership_rtps.kind = NULL;
                                                            }
                                                        }
                                                        break;
                                                    case PIDPRESENTATION_RTPS_VAL :
                                                        {
                                                        }
                                                        break;
                                                    case PIDDESTINATIONORDER_RTPS_VAL :
                                                        {
                                                            if (mainpdu->ptr.full_rtps.submsg [i].ptr.datawsub_rtps.serializeddata->topicdata 
                                                              [j].ptr.piddestinationorder_rtps.kind != NULL) {
                                                                free (mainpdu->ptr.full_rtps.submsg [i].ptr.datawsub_rtps.serializeddata->topicdata 
                                                                  [j].ptr.piddestinationorder_rtps.kind);
                                                                mainpdu->ptr.full_rtps.submsg [i].ptr.datawsub_rtps.serializeddata->topicdata 
                                                                  [j].ptr.piddestinationorder_rtps.kind = NULL;
                                                            }
                                                        }
                                                        break;
                                                    case PIDDEADLINE_RTPS_VAL :
                                                        {
                                                            if (mainpdu->ptr.full_rtps.submsg [i].ptr.datawsub_rtps.serializeddata->topicdata 
                                                              [j].ptr.piddeadline_rtps.leaseduration != NULL) {
                                                                free (mainpdu->ptr.full_rtps.submsg [i].ptr.datawsub_rtps.serializeddata->topicdata 
                                                                  [j].ptr.piddeadline_rtps.leaseduration);
                                                                mainpdu->ptr.full_rtps.submsg [i].ptr.datawsub_rtps.serializeddata->topicdata 
                                                                  [j].ptr.piddeadline_rtps.leaseduration = NULL;
                                                            }
                                                        }
                                                        break;
                                                    case PIDLATENCYBUDGET_RTPS_VAL :
                                                        {
                                                            if (mainpdu->ptr.full_rtps.submsg [i].ptr.datawsub_rtps.serializeddata->topicdata 
                                                              [j].ptr.pidlatencybudget_rtps.leaseduration != NULL) {
                                                                free (mainpdu->ptr.full_rtps.submsg [i].ptr.datawsub_rtps.serializeddata->topicdata 
                                                                  [j].ptr.pidlatencybudget_rtps.leaseduration);
                                                                mainpdu->ptr.full_rtps.submsg [i].ptr.datawsub_rtps.serializeddata->topicdata 
                                                                  [j].ptr.pidlatencybudget_rtps.leaseduration = NULL;
                                                            }
                                                        }
                                                        break;
                                                    case PIDGROUPENTITYID_RTPS_VAL :
                                                        {
                                                        }
                                                        break;
                                                    case PIDENTITYVIRTUALGUID_RTPS_VAL :
                                                        {
                                                        }
                                                        break;
                                                    case PIDSERVICEKIND_RTPS_VAL :
                                                        {
                                                            if (mainpdu->ptr.full_rtps.submsg [i].ptr.datawsub_rtps.serializeddata->topicdata 
                                                              [j].ptr.pidservicekind_rtps.servicekind != NULL) {
                                                                free (mainpdu->ptr.full_rtps.submsg [i].ptr.datawsub_rtps.serializeddata->topicdata 
                                                                  [j].ptr.pidservicekind_rtps.servicekind);
                                                                mainpdu->ptr.full_rtps.submsg [i].ptr.datawsub_rtps.serializeddata->topicdata 
                                                                  [j].ptr.pidservicekind_rtps.servicekind = NULL;
                                                            }
                                                        }
                                                        break;
                                                    case PIDPROTOVERSION_RTPS_VAL :
                                                        {
                                                        }
                                                        break;
                                                    case PIDPRODUCTVERSION_RTPS_VAL :
                                                        {
                                                        }
                                                        break;
                                                    case PIDDISABLEPOSITIVEACKS_RTPS_VAL :
                                                        {
                                                        }
                                                        break;
                                                    case PIDEXPECTSVIRTUALHB_RTPS_VAL :
                                                        {
                                                        }
                                                        break;
                                                    case PIDTYPECONSISTENCY_RTPS_VAL :
                                                        {
                                                        }
                                                        break;
                                                    case PIDTYPEOBJECT_RTPS_VAL :
                                                        {
                                                            if (mainpdu->ptr.full_rtps.submsg [i].ptr.datawsub_rtps.serializeddata->topicdata 
                                                              [j].ptr.pidtypeobject_rtps.typeobject != NULL) {
                                                                free (mainpdu->ptr.full_rtps.submsg [i].ptr.datawsub_rtps.serializeddata->topicdata 
                                                                  [j].ptr.pidtypeobject_rtps.typeobject);
                                                                mainpdu->ptr.full_rtps.submsg [i].ptr.datawsub_rtps.serializeddata->topicdata 
                                                                  [j].ptr.pidtypeobject_rtps.typeobject = NULL;
                                                            }
                                                        }
                                                        break;
                                                    case PIDTYPECODE_RTPS_VAL :
                                                        {
                                                            if (mainpdu->ptr.full_rtps.submsg [i].ptr.datawsub_rtps.serializeddata->topicdata 
                                                              [j].ptr.pidtypecode_rtps.typeobjectcode != NULL) {
                                                                free (mainpdu->ptr.full_rtps.submsg [i].ptr.datawsub_rtps.serializeddata->topicdata 
                                                                  [j].ptr.pidtypecode_rtps.typeobjectcode);
                                                                mainpdu->ptr.full_rtps.submsg [i].ptr.datawsub_rtps.serializeddata->topicdata 
                                                                  [j].ptr.pidtypecode_rtps.typeobjectcode = NULL;
                                                            }
                                                        }
                                                        break;
                                                    case PIDVENDORID_RTPS_VAL :
                                                        {
                                                        }
                                                        break;
                                                    case PIDENTITYNAME_RTPS_VAL :
                                                        {
                                                            if (mainpdu->ptr.full_rtps.submsg [i].ptr.datawsub_rtps.serializeddata->topicdata 
                                                              [j].ptr.pidentityname_rtps.entityname.name != NULL) {
                                                                free (mainpdu->ptr.full_rtps.submsg [i].ptr.datawsub_rtps.serializeddata->topicdata 
                                                                  [j].ptr.pidentityname_rtps.entityname.name);
                                                                mainpdu->ptr.full_rtps.submsg [i].ptr.datawsub_rtps.serializeddata->topicdata 
                                                                  [j].ptr.pidentityname_rtps.entityname.name = NULL;
                                                            }
                                                        }
                                                        break;
                                                    case PIDEXPECTSACK_RTPS_VAL :
                                                        {
                                                            if (mainpdu->ptr.full_rtps.submsg [i].ptr.datawsub_rtps.serializeddata->topicdata 
                                                              [j].ptr.pidexpectsack_rtps.expectsack != NULL) {
                                                                free (mainpdu->ptr.full_rtps.submsg [i].ptr.datawsub_rtps.serializeddata->topicdata 
                                                                  [j].ptr.pidexpectsack_rtps.expectsack);
                                                                mainpdu->ptr.full_rtps.submsg [i].ptr.datawsub_rtps.serializeddata->topicdata 
                                                                  [j].ptr.pidexpectsack_rtps.expectsack = NULL;
                                                            }
                                                        }
                                                        break;
                                                    case PIDSENDQUEUESIZE_RTPS_VAL :
                                                        {
                                                            if (mainpdu->ptr.full_rtps.submsg [i].ptr.datawsub_rtps.serializeddata->topicdata 
                                                              [j].ptr.pidsendqueuesize_rtps.queuesize != NULL) {
                                                                free (mainpdu->ptr.full_rtps.submsg [i].ptr.datawsub_rtps.serializeddata->topicdata 
                                                                  [j].ptr.pidsendqueuesize_rtps.queuesize);
                                                                mainpdu->ptr.full_rtps.submsg [i].ptr.datawsub_rtps.serializeddata->topicdata 
                                                                  [j].ptr.pidsendqueuesize_rtps.queuesize = NULL;
                                                            }
                                                        }
                                                        break;
                                                    case PIDOWNERSHIPSTRENGTH_RTPS_VAL :
                                                        {
                                                            if (mainpdu->ptr.full_rtps.submsg [i].ptr.datawsub_rtps.serializeddata->topicdata 
                                                              [j].ptr.pidownershipstrength_rtps.strength != NULL) {
                                                                free (mainpdu->ptr.full_rtps.submsg [i].ptr.datawsub_rtps.serializeddata->topicdata 
                                                                  [j].ptr.pidownershipstrength_rtps.strength);
                                                                mainpdu->ptr.full_rtps.submsg [i].ptr.datawsub_rtps.serializeddata->topicdata 
                                                                  [j].ptr.pidownershipstrength_rtps.strength = NULL;
                                                            }
                                                        }
                                                        break;
                                                    case PIDPERSISTENCE_RTPS_VAL :
                                                        {
                                                            if (mainpdu->ptr.full_rtps.submsg [i].ptr.datawsub_rtps.serializeddata->topicdata 
                                                              [j].ptr.pidpersistence_rtps.leaseduration != NULL) {
                                                                free (mainpdu->ptr.full_rtps.submsg [i].ptr.datawsub_rtps.serializeddata->topicdata 
                                                                  [j].ptr.pidpersistence_rtps.leaseduration);
                                                                mainpdu->ptr.full_rtps.submsg [i].ptr.datawsub_rtps.serializeddata->topicdata 
                                                                  [j].ptr.pidpersistence_rtps.leaseduration = NULL;
                                                            }
                                                        }
                                                        break;
                                                    case PIDLIFESPAN_RTPS_VAL :
                                                        {
                                                            if (mainpdu->ptr.full_rtps.submsg [i].ptr.datawsub_rtps.serializeddata->topicdata 
                                                              [j].ptr.pidlifespan_rtps.leaseduration != NULL) {
                                                                free (mainpdu->ptr.full_rtps.submsg [i].ptr.datawsub_rtps.serializeddata->topicdata 
                                                                  [j].ptr.pidlifespan_rtps.leaseduration);
                                                                mainpdu->ptr.full_rtps.submsg [i].ptr.datawsub_rtps.serializeddata->topicdata 
                                                                  [j].ptr.pidlifespan_rtps.leaseduration = NULL;
                                                            }
                                                        }
                                                        break;
                                                    case PIDTYPEMAXSIZESERIALIZED_RTPS_VAL :
                                                        {
                                                            if (mainpdu->ptr.full_rtps.submsg [i].ptr.datawsub_rtps.serializeddata->topicdata 
                                                              [j].ptr.pidtypemaxsizeserialized_rtps.value != NULL) {
                                                                free (mainpdu->ptr.full_rtps.submsg [i].ptr.datawsub_rtps.serializeddata->topicdata 
                                                                  [j].ptr.pidtypemaxsizeserialized_rtps.value);
                                                                mainpdu->ptr.full_rtps.submsg [i].ptr.datawsub_rtps.serializeddata->topicdata 
                                                                  [j].ptr.pidtypemaxsizeserialized_rtps.value = NULL;
                                                            }
                                                        }
                                                        break;
                                                    case PIDDURABILITYSERVICE_RTPS_VAL :
                                                        {
                                                            if (mainpdu->ptr.full_rtps.submsg [i].ptr.datawsub_rtps.serializeddata->topicdata 
                                                              [j].ptr.piddurabilityservice_rtps.durabilityservice != NULL) {
                                                                free (mainpdu->ptr.full_rtps.submsg [i].ptr.datawsub_rtps.serializeddata->topicdata 
                                                                  [j].ptr.piddurabilityservice_rtps.durabilityservice);
                                                                mainpdu->ptr.full_rtps.submsg [i].ptr.datawsub_rtps.serializeddata->topicdata 
                                                                  [j].ptr.piddurabilityservice_rtps.durabilityservice = NULL;
                                                            }
                                                        }
                                                        break;
                                                    }
                                                }
                                            }
                                        }
                                        if (mainpdu->ptr.full_rtps.submsg [i].ptr.datawsub_rtps.serializeddata->topicdata != NULL) {
                                            free (mainpdu->ptr.full_rtps.submsg [i].ptr.datawsub_rtps.serializeddata->topicdata);
                                            mainpdu->ptr.full_rtps.submsg [i].ptr.datawsub_rtps.serializeddata->topicdata = NULL;
                                        }
                                    }
                                }
                                if (mainpdu->ptr.full_rtps.submsg [i].ptr.datawsub_rtps.serializeddata != NULL) {
                                    free (mainpdu->ptr.full_rtps.submsg [i].ptr.datawsub_rtps.serializeddata);
                                    mainpdu->ptr.full_rtps.submsg [i].ptr.datawsub_rtps.serializeddata = NULL;
                                }
                            }
                            break;
                        case DATARSUB_RTPS_VAL :
                            {
                                if (mainpdu->ptr.full_rtps.submsg [i].ptr.datarsub_rtps.inlineqos != NULL) {
                                    if (mainpdu->ptr.full_rtps.submsg [i].ptr.datarsub_rtps.inlineqos->qos != NULL) {
                                        for (int j = 0; j < mainpdu->ptr.full_rtps.submsg [i].ptr.datarsub_rtps.inlineqos->qoscount; ++j) {
                                            if (&mainpdu->ptr.full_rtps.submsg [i].ptr.datarsub_rtps.inlineqos->qos [j] != NULL) {
                                                if (mainpdu->ptr.full_rtps.submsg [i].ptr.datarsub_rtps.inlineqos->qos [j].type > 0) {
                                                    switch (mainpdu->ptr.full_rtps.submsg [i].ptr.datarsub_rtps.inlineqos->qos [j].type) {
                                                    case PIDSTATUSINFO_RTPS_VAL :
                                                        {
                                                            if (mainpdu->ptr.full_rtps.submsg [i].ptr.datarsub_rtps.inlineqos->qos 
                                                              [j].ptr.pidstatusinfo_rtps.flags != NULL) {
                                                                free (mainpdu->ptr.full_rtps.submsg [i].ptr.datarsub_rtps.inlineqos->qos 
                                                                  [j].ptr.pidstatusinfo_rtps.flags);
                                                                mainpdu->ptr.full_rtps.submsg [i].ptr.datarsub_rtps.inlineqos->qos 
                                                                  [j].ptr.pidstatusinfo_rtps.flags = NULL;
                                                            }
                                                        }
                                                        break;
                                                    case PIDKEYHASH_RTPS_VAL :
                                                        {
                                                            if (mainpdu->ptr.full_rtps.submsg [i].ptr.datarsub_rtps.inlineqos->qos [j].ptr.pidkeyhash_rtps.guid
                                                              != NULL) {
                                                                free (mainpdu->ptr.full_rtps.submsg [i].ptr.datarsub_rtps.inlineqos->qos 
                                                                  [j].ptr.pidkeyhash_rtps.guid);
                                                                mainpdu->ptr.full_rtps.submsg [i].ptr.datarsub_rtps.inlineqos->qos [j].ptr.pidkeyhash_rtps.guid
                                                                  = NULL;
                                                            }
                                                        }
                                                        break;
                                                    case PIDSENTINAL_RTPS_VAL :
                                                        {
                                                        }
                                                        break;
                                                    }
                                                }
                                            }
                                        }
                                        if (mainpdu->ptr.full_rtps.submsg [i].ptr.datarsub_rtps.inlineqos->qos != NULL) {
                                            free (mainpdu->ptr.full_rtps.submsg [i].ptr.datarsub_rtps.inlineqos->qos);
                                            mainpdu->ptr.full_rtps.submsg [i].ptr.datarsub_rtps.inlineqos->qos = NULL;
                                        }
                                    }
                                }
                                if (mainpdu->ptr.full_rtps.submsg [i].ptr.datarsub_rtps.inlineqos != NULL) {
                                    free (mainpdu->ptr.full_rtps.submsg [i].ptr.datarsub_rtps.inlineqos);
                                    mainpdu->ptr.full_rtps.submsg [i].ptr.datarsub_rtps.inlineqos = NULL;
                                }
                                if (mainpdu->ptr.full_rtps.submsg [i].ptr.datarsub_rtps.serializeddata != NULL) {
                                    if (mainpdu->ptr.full_rtps.submsg [i].ptr.datarsub_rtps.serializeddata->topicdata != NULL) {
                                        for (int j = 0; j < mainpdu->ptr.full_rtps.submsg [i].ptr.datarsub_rtps.serializeddata->topicdatacount; ++j) {
                                            if (&mainpdu->ptr.full_rtps.submsg [i].ptr.datarsub_rtps.serializeddata->topicdata [j] != NULL) {
                                                if (mainpdu->ptr.full_rtps.submsg [i].ptr.datarsub_rtps.serializeddata->topicdata [j].type > 0) {
                                                    switch (mainpdu->ptr.full_rtps.submsg [i].ptr.datarsub_rtps.serializeddata->topicdata [j].type) {
                                                    case PIDTOPICNAME_RTPS_VAL :
                                                        {
                                                            if (mainpdu->ptr.full_rtps.submsg [i].ptr.datarsub_rtps.serializeddata->topicdata 
                                                              [j].ptr.pidtopicname_rtps.topicname.name != NULL) {
                                                                free (mainpdu->ptr.full_rtps.submsg [i].ptr.datarsub_rtps.serializeddata->topicdata 
                                                                  [j].ptr.pidtopicname_rtps.topicname.name);
                                                                mainpdu->ptr.full_rtps.submsg [i].ptr.datarsub_rtps.serializeddata->topicdata 
                                                                  [j].ptr.pidtopicname_rtps.topicname.name = NULL;
                                                            }
                                                        }
                                                        break;
                                                    case PIDTYPENAME_RTPS_VAL :
                                                        {
                                                            if (mainpdu->ptr.full_rtps.submsg [i].ptr.datarsub_rtps.serializeddata->topicdata 
                                                              [j].ptr.pidtypename_rtps.typename.name != NULL) {
                                                                free (mainpdu->ptr.full_rtps.submsg [i].ptr.datarsub_rtps.serializeddata->topicdata 
                                                                  [j].ptr.pidtypename_rtps.typename.name);
                                                                mainpdu->ptr.full_rtps.submsg [i].ptr.datarsub_rtps.serializeddata->topicdata 
                                                                  [j].ptr.pidtypename_rtps.typename.name = NULL;
                                                            }
                                                        }
                                                        break;
                                                    case PIDRELIABILITY_RTPS_VAL :
                                                        {
                                                            if (mainpdu->ptr.full_rtps.submsg [i].ptr.datarsub_rtps.serializeddata->topicdata 
                                                              [j].ptr.pidreliability_rtps.slack != NULL) {
                                                                free (mainpdu->ptr.full_rtps.submsg [i].ptr.datarsub_rtps.serializeddata->topicdata 
                                                                  [j].ptr.pidreliability_rtps.slack);
                                                                mainpdu->ptr.full_rtps.submsg [i].ptr.datarsub_rtps.serializeddata->topicdata 
                                                                  [j].ptr.pidreliability_rtps.slack = NULL;
                                                            }
                                                        }
                                                        break;
                                                    case PIDENDPOINTGUID_RTPS_VAL :
                                                        {
                                                        }
                                                        break;
                                                    case PIDMULTICASTLOCATOR_RTPS_VAL :
                                                        {
                                                        }
                                                        break;
                                                    case PIDUNICASTLOCATOR_RTPS_VAL :
                                                        {
                                                        }
                                                        break;
                                                    case PIDSENTINAL_RTPS_VAL :
                                                        {
                                                        }
                                                        break;
                                                    case PIDUNKNOWN_RTPS_VAL :
                                                        {
                                                        }
                                                        break;
                                                    case PIDACKKIND_RTPS_VAL :
                                                        {
                                                            if (mainpdu->ptr.full_rtps.submsg [i].ptr.datarsub_rtps.serializeddata->topicdata 
                                                              [j].ptr.pidackkind_rtps.ackkind != NULL) {
                                                                free (mainpdu->ptr.full_rtps.submsg [i].ptr.datarsub_rtps.serializeddata->topicdata 
                                                                  [j].ptr.pidackkind_rtps.ackkind);
                                                                mainpdu->ptr.full_rtps.submsg [i].ptr.datarsub_rtps.serializeddata->topicdata 
                                                                  [j].ptr.pidackkind_rtps.ackkind = NULL;
                                                            }
                                                        }
                                                        break;
                                                    case PIDRECVQUEUE_RTPS_VAL :
                                                        {
                                                            if (mainpdu->ptr.full_rtps.submsg [i].ptr.datarsub_rtps.serializeddata->topicdata 
                                                              [j].ptr.pidrecvqueue_rtps.queuesize != NULL) {
                                                                free (mainpdu->ptr.full_rtps.submsg [i].ptr.datarsub_rtps.serializeddata->topicdata 
                                                                  [j].ptr.pidrecvqueue_rtps.queuesize);
                                                                mainpdu->ptr.full_rtps.submsg [i].ptr.datarsub_rtps.serializeddata->topicdata 
                                                                  [j].ptr.pidrecvqueue_rtps.queuesize = NULL;
                                                            }
                                                        }
                                                        break;
                                                    case PIDTIMEBASEDFILTER_RTPS_VAL :
                                                        {
                                                            if (mainpdu->ptr.full_rtps.submsg [i].ptr.datarsub_rtps.serializeddata->topicdata 
                                                              [j].ptr.pidtimebasedfilter_rtps.leaseduration != NULL) {
                                                                free (mainpdu->ptr.full_rtps.submsg [i].ptr.datarsub_rtps.serializeddata->topicdata 
                                                                  [j].ptr.pidtimebasedfilter_rtps.leaseduration);
                                                                mainpdu->ptr.full_rtps.submsg [i].ptr.datarsub_rtps.serializeddata->topicdata 
                                                                  [j].ptr.pidtimebasedfilter_rtps.leaseduration = NULL;
                                                            }
                                                        }
                                                        break;
                                                    case PIDLIVELINESS_RTPS_VAL :
                                                        {
                                                            if (mainpdu->ptr.full_rtps.submsg [i].ptr.datarsub_rtps.serializeddata->topicdata 
                                                              [j].ptr.pidliveliness_rtps.liveliness != NULL) {
                                                                free (mainpdu->ptr.full_rtps.submsg [i].ptr.datarsub_rtps.serializeddata->topicdata 
                                                                  [j].ptr.pidliveliness_rtps.liveliness);
                                                                mainpdu->ptr.full_rtps.submsg [i].ptr.datarsub_rtps.serializeddata->topicdata 
                                                                  [j].ptr.pidliveliness_rtps.liveliness = NULL;
                                                            }
                                                        }
                                                        break;
                                                    case PIDDURABILITY_RTPS_VAL :
                                                        {
                                                            if (mainpdu->ptr.full_rtps.submsg [i].ptr.datarsub_rtps.serializeddata->topicdata 
                                                              [j].ptr.piddurability_rtps.durability != NULL) {
                                                                free (mainpdu->ptr.full_rtps.submsg [i].ptr.datarsub_rtps.serializeddata->topicdata 
                                                                  [j].ptr.piddurability_rtps.durability);
                                                                mainpdu->ptr.full_rtps.submsg [i].ptr.datarsub_rtps.serializeddata->topicdata 
                                                                  [j].ptr.piddurability_rtps.durability = NULL;
                                                            }
                                                        }
                                                        break;
                                                    case PIDDIRECTCOMMUNICATION_RTPS_VAL :
                                                        {
                                                        }
                                                        break;
                                                    case PIDOWNERSHIP_RTPS_VAL :
                                                        {
                                                            if (mainpdu->ptr.full_rtps.submsg [i].ptr.datarsub_rtps.serializeddata->topicdata 
                                                              [j].ptr.pidownership_rtps.kind != NULL) {
                                                                free (mainpdu->ptr.full_rtps.submsg [i].ptr.datarsub_rtps.serializeddata->topicdata 
                                                                  [j].ptr.pidownership_rtps.kind);
                                                                mainpdu->ptr.full_rtps.submsg [i].ptr.datarsub_rtps.serializeddata->topicdata 
                                                                  [j].ptr.pidownership_rtps.kind = NULL;
                                                            }
                                                        }
                                                        break;
                                                    case PIDPRESENTATION_RTPS_VAL :
                                                        {
                                                        }
                                                        break;
                                                    case PIDDESTINATIONORDER_RTPS_VAL :
                                                        {
                                                            if (mainpdu->ptr.full_rtps.submsg [i].ptr.datarsub_rtps.serializeddata->topicdata 
                                                              [j].ptr.piddestinationorder_rtps.kind != NULL) {
                                                                free (mainpdu->ptr.full_rtps.submsg [i].ptr.datarsub_rtps.serializeddata->topicdata 
                                                                  [j].ptr.piddestinationorder_rtps.kind);
                                                                mainpdu->ptr.full_rtps.submsg [i].ptr.datarsub_rtps.serializeddata->topicdata 
                                                                  [j].ptr.piddestinationorder_rtps.kind = NULL;
                                                            }
                                                        }
                                                        break;
                                                    case PIDDEADLINE_RTPS_VAL :
                                                        {
                                                            if (mainpdu->ptr.full_rtps.submsg [i].ptr.datarsub_rtps.serializeddata->topicdata 
                                                              [j].ptr.piddeadline_rtps.leaseduration != NULL) {
                                                                free (mainpdu->ptr.full_rtps.submsg [i].ptr.datarsub_rtps.serializeddata->topicdata 
                                                                  [j].ptr.piddeadline_rtps.leaseduration);
                                                                mainpdu->ptr.full_rtps.submsg [i].ptr.datarsub_rtps.serializeddata->topicdata 
                                                                  [j].ptr.piddeadline_rtps.leaseduration = NULL;
                                                            }
                                                        }
                                                        break;
                                                    case PIDLATENCYBUDGET_RTPS_VAL :
                                                        {
                                                            if (mainpdu->ptr.full_rtps.submsg [i].ptr.datarsub_rtps.serializeddata->topicdata 
                                                              [j].ptr.pidlatencybudget_rtps.leaseduration != NULL) {
                                                                free (mainpdu->ptr.full_rtps.submsg [i].ptr.datarsub_rtps.serializeddata->topicdata 
                                                                  [j].ptr.pidlatencybudget_rtps.leaseduration);
                                                                mainpdu->ptr.full_rtps.submsg [i].ptr.datarsub_rtps.serializeddata->topicdata 
                                                                  [j].ptr.pidlatencybudget_rtps.leaseduration = NULL;
                                                            }
                                                        }
                                                        break;
                                                    case PIDGROUPENTITYID_RTPS_VAL :
                                                        {
                                                        }
                                                        break;
                                                    case PIDENTITYVIRTUALGUID_RTPS_VAL :
                                                        {
                                                        }
                                                        break;
                                                    case PIDSERVICEKIND_RTPS_VAL :
                                                        {
                                                            if (mainpdu->ptr.full_rtps.submsg [i].ptr.datarsub_rtps.serializeddata->topicdata 
                                                              [j].ptr.pidservicekind_rtps.servicekind != NULL) {
                                                                free (mainpdu->ptr.full_rtps.submsg [i].ptr.datarsub_rtps.serializeddata->topicdata 
                                                                  [j].ptr.pidservicekind_rtps.servicekind);
                                                                mainpdu->ptr.full_rtps.submsg [i].ptr.datarsub_rtps.serializeddata->topicdata 
                                                                  [j].ptr.pidservicekind_rtps.servicekind = NULL;
                                                            }
                                                        }
                                                        break;
                                                    case PIDPROTOVERSION_RTPS_VAL :
                                                        {
                                                        }
                                                        break;
                                                    case PIDPRODUCTVERSION_RTPS_VAL :
                                                        {
                                                        }
                                                        break;
                                                    case PIDDISABLEPOSITIVEACKS_RTPS_VAL :
                                                        {
                                                        }
                                                        break;
                                                    case PIDEXPECTSVIRTUALHB_RTPS_VAL :
                                                        {
                                                        }
                                                        break;
                                                    case PIDTYPECONSISTENCY_RTPS_VAL :
                                                        {
                                                        }
                                                        break;
                                                    case PIDTYPEOBJECT_RTPS_VAL :
                                                        {
                                                            if (mainpdu->ptr.full_rtps.submsg [i].ptr.datarsub_rtps.serializeddata->topicdata 
                                                              [j].ptr.pidtypeobject_rtps.typeobject != NULL) {
                                                                free (mainpdu->ptr.full_rtps.submsg [i].ptr.datarsub_rtps.serializeddata->topicdata 
                                                                  [j].ptr.pidtypeobject_rtps.typeobject);
                                                                mainpdu->ptr.full_rtps.submsg [i].ptr.datarsub_rtps.serializeddata->topicdata 
                                                                  [j].ptr.pidtypeobject_rtps.typeobject = NULL;
                                                            }
                                                        }
                                                        break;
                                                    case PIDTYPECODE_RTPS_VAL :
                                                        {
                                                            if (mainpdu->ptr.full_rtps.submsg [i].ptr.datarsub_rtps.serializeddata->topicdata 
                                                              [j].ptr.pidtypecode_rtps.typeobjectcode != NULL) {
                                                                free (mainpdu->ptr.full_rtps.submsg [i].ptr.datarsub_rtps.serializeddata->topicdata 
                                                                  [j].ptr.pidtypecode_rtps.typeobjectcode);
                                                                mainpdu->ptr.full_rtps.submsg [i].ptr.datarsub_rtps.serializeddata->topicdata 
                                                                  [j].ptr.pidtypecode_rtps.typeobjectcode = NULL;
                                                            }
                                                        }
                                                        break;
                                                    case PIDVENDORID_RTPS_VAL :
                                                        {
                                                        }
                                                        break;
                                                    case PIDENTITYNAME_RTPS_VAL :
                                                        {
                                                            if (mainpdu->ptr.full_rtps.submsg [i].ptr.datarsub_rtps.serializeddata->topicdata 
                                                              [j].ptr.pidentityname_rtps.entityname.name != NULL) {
                                                                free (mainpdu->ptr.full_rtps.submsg [i].ptr.datarsub_rtps.serializeddata->topicdata 
                                                                  [j].ptr.pidentityname_rtps.entityname.name);
                                                                mainpdu->ptr.full_rtps.submsg [i].ptr.datarsub_rtps.serializeddata->topicdata 
                                                                  [j].ptr.pidentityname_rtps.entityname.name = NULL;
                                                            }
                                                        }
                                                        break;
                                                    case PIDEXPECTSACK_RTPS_VAL :
                                                        {
                                                            if (mainpdu->ptr.full_rtps.submsg [i].ptr.datarsub_rtps.serializeddata->topicdata 
                                                              [j].ptr.pidexpectsack_rtps.expectsack != NULL) {
                                                                free (mainpdu->ptr.full_rtps.submsg [i].ptr.datarsub_rtps.serializeddata->topicdata 
                                                                  [j].ptr.pidexpectsack_rtps.expectsack);
                                                                mainpdu->ptr.full_rtps.submsg [i].ptr.datarsub_rtps.serializeddata->topicdata 
                                                                  [j].ptr.pidexpectsack_rtps.expectsack = NULL;
                                                            }
                                                        }
                                                        break;
                                                    case PIDSENDQUEUESIZE_RTPS_VAL :
                                                        {
                                                            if (mainpdu->ptr.full_rtps.submsg [i].ptr.datarsub_rtps.serializeddata->topicdata 
                                                              [j].ptr.pidsendqueuesize_rtps.queuesize != NULL) {
                                                                free (mainpdu->ptr.full_rtps.submsg [i].ptr.datarsub_rtps.serializeddata->topicdata 
                                                                  [j].ptr.pidsendqueuesize_rtps.queuesize);
                                                                mainpdu->ptr.full_rtps.submsg [i].ptr.datarsub_rtps.serializeddata->topicdata 
                                                                  [j].ptr.pidsendqueuesize_rtps.queuesize = NULL;
                                                            }
                                                        }
                                                        break;
                                                    case PIDOWNERSHIPSTRENGTH_RTPS_VAL :
                                                        {
                                                            if (mainpdu->ptr.full_rtps.submsg [i].ptr.datarsub_rtps.serializeddata->topicdata 
                                                              [j].ptr.pidownershipstrength_rtps.strength != NULL) {
                                                                free (mainpdu->ptr.full_rtps.submsg [i].ptr.datarsub_rtps.serializeddata->topicdata 
                                                                  [j].ptr.pidownershipstrength_rtps.strength);
                                                                mainpdu->ptr.full_rtps.submsg [i].ptr.datarsub_rtps.serializeddata->topicdata 
                                                                  [j].ptr.pidownershipstrength_rtps.strength = NULL;
                                                            }
                                                        }
                                                        break;
                                                    case PIDPERSISTENCE_RTPS_VAL :
                                                        {
                                                            if (mainpdu->ptr.full_rtps.submsg [i].ptr.datarsub_rtps.serializeddata->topicdata 
                                                              [j].ptr.pidpersistence_rtps.leaseduration != NULL) {
                                                                free (mainpdu->ptr.full_rtps.submsg [i].ptr.datarsub_rtps.serializeddata->topicdata 
                                                                  [j].ptr.pidpersistence_rtps.leaseduration);
                                                                mainpdu->ptr.full_rtps.submsg [i].ptr.datarsub_rtps.serializeddata->topicdata 
                                                                  [j].ptr.pidpersistence_rtps.leaseduration = NULL;
                                                            }
                                                        }
                                                        break;
                                                    case PIDLIFESPAN_RTPS_VAL :
                                                        {
                                                            if (mainpdu->ptr.full_rtps.submsg [i].ptr.datarsub_rtps.serializeddata->topicdata 
                                                              [j].ptr.pidlifespan_rtps.leaseduration != NULL) {
                                                                free (mainpdu->ptr.full_rtps.submsg [i].ptr.datarsub_rtps.serializeddata->topicdata 
                                                                  [j].ptr.pidlifespan_rtps.leaseduration);
                                                                mainpdu->ptr.full_rtps.submsg [i].ptr.datarsub_rtps.serializeddata->topicdata 
                                                                  [j].ptr.pidlifespan_rtps.leaseduration = NULL;
                                                            }
                                                        }
                                                        break;
                                                    case PIDTYPEMAXSIZESERIALIZED_RTPS_VAL :
                                                        {
                                                            if (mainpdu->ptr.full_rtps.submsg [i].ptr.datarsub_rtps.serializeddata->topicdata 
                                                              [j].ptr.pidtypemaxsizeserialized_rtps.value != NULL) {
                                                                free (mainpdu->ptr.full_rtps.submsg [i].ptr.datarsub_rtps.serializeddata->topicdata 
                                                                  [j].ptr.pidtypemaxsizeserialized_rtps.value);
                                                                mainpdu->ptr.full_rtps.submsg [i].ptr.datarsub_rtps.serializeddata->topicdata 
                                                                  [j].ptr.pidtypemaxsizeserialized_rtps.value = NULL;
                                                            }
                                                        }
                                                        break;
                                                    case PIDDURABILITYSERVICE_RTPS_VAL :
                                                        {
                                                            if (mainpdu->ptr.full_rtps.submsg [i].ptr.datarsub_rtps.serializeddata->topicdata 
                                                              [j].ptr.piddurabilityservice_rtps.durabilityservice != NULL) {
                                                                free (mainpdu->ptr.full_rtps.submsg [i].ptr.datarsub_rtps.serializeddata->topicdata 
                                                                  [j].ptr.piddurabilityservice_rtps.durabilityservice);
                                                                mainpdu->ptr.full_rtps.submsg [i].ptr.datarsub_rtps.serializeddata->topicdata 
                                                                  [j].ptr.piddurabilityservice_rtps.durabilityservice = NULL;
                                                            }
                                                        }
                                                        break;
                                                    }
                                                }
                                            }
                                        }
                                        if (mainpdu->ptr.full_rtps.submsg [i].ptr.datarsub_rtps.serializeddata->topicdata != NULL) {
                                            free (mainpdu->ptr.full_rtps.submsg [i].ptr.datarsub_rtps.serializeddata->topicdata);
                                            mainpdu->ptr.full_rtps.submsg [i].ptr.datarsub_rtps.serializeddata->topicdata = NULL;
                                        }
                                    }
                                }
                                if (mainpdu->ptr.full_rtps.submsg [i].ptr.datarsub_rtps.serializeddata != NULL) {
                                    free (mainpdu->ptr.full_rtps.submsg [i].ptr.datarsub_rtps.serializeddata);
                                    mainpdu->ptr.full_rtps.submsg [i].ptr.datarsub_rtps.serializeddata = NULL;
                                }
                            }
                            break;
                        case GAP_RTPS_VAL :
                            {
                                if (mainpdu->ptr.full_rtps.submsg [i].ptr.gap_rtps.snstate.bitmap != NULL) {
                                    free (mainpdu->ptr.full_rtps.submsg [i].ptr.gap_rtps.snstate.bitmap);
                                    mainpdu->ptr.full_rtps.submsg [i].ptr.gap_rtps.snstate.bitmap = NULL;
                                }
                            }
                            break;
                        }
                    }
                }
            }
            if (mainpdu->ptr.full_rtps.submsg != NULL) {
                free (mainpdu->ptr.full_rtps.submsg);
                mainpdu->ptr.full_rtps.submsg = NULL;
            }
        }
    }
}

SUBMESSAGE_RTPS *parseSetOfSUBMESSAGE (PDU *thePDU, int n, int *size, char *progname, uint8_t endianness) {
    SUBMESSAGE_RTPS submsg;
    if (!parseSUBMESSAGE (&submsg, thePDU, progname, endianness)) {
        if (n == 0) {
            *size = 0;
            return NULL;
        }
        SUBMESSAGE_RTPS *result = (SUBMESSAGE_RTPS *) malloc ((n) *sizeof(SUBMESSAGE_RTPS));
        if (result == NULL) {
            fprintf (stderr, "%s: internal malloc error file: %s line: %d \n", progname, __FILE__, __LINE__);
            return NULL;
        }
        *size = n;
        return result;
    }
    else {
        SUBMESSAGE_RTPS *result = parseSetOfSUBMESSAGE (thePDU, n +1, size, progname, endianness);
        result[n] = submsg;
        return result;
    }
}

QOSPARMS_RTPS *parseSetOfQOSPARMS_O (PDU *thePDU, int n, int *size, char *progname, uint8_t endianness) {
    QOSPARMS_RTPS qos;
    if (parseQOSPARMS (&qos, thePDU, progname, endianness)) {
        if (qos.type == PIDSENTINAL_RTPS_VAL) {
            QOSPARMS_RTPS *result = (QOSPARMS_RTPS *) malloc ((n + 1) * sizeof (QOSPARMS_RTPS));
            if (result == NULL) {
                return NULL;
            }
            *size = n + 1;
            result[n] = qos;
            return result;
        }
        else {
            QOSPARMS_RTPS *result = parseSetOfQOSPARMS_O (thePDU, n +1, size, progname, endianness);
            if (result != NULL) {
                result[n] = qos;
            }
            return result;
        }
    }
    else {
        if (n == 0) {
            *size = 0;
            return NULL;
        }
        else {
            return NULL;
        }
    }
}

TOPICPARMS_RTPS *parseSetOfTOPICPARMS_O (PDU *thePDU, int n, int *size, char *progname, uint8_t endianness) {
    TOPICPARMS_RTPS topicdata;
    if (parseTOPICPARMS (&topicdata, thePDU, progname, endianness)) {
        if (topicdata.type == PIDSENTINAL_RTPS_VAL) {
            TOPICPARMS_RTPS *result = (TOPICPARMS_RTPS *) malloc ((n + 1) * sizeof (TOPICPARMS_RTPS));
            if (result == NULL) {
                return NULL;
            }
            *size = n + 1;
            result[n] = topicdata;
            return result;
        }
        else {
            TOPICPARMS_RTPS *result = parseSetOfTOPICPARMS_O (thePDU, n +1, size, progname, endianness);
            if (result != NULL) {
                result[n] = topicdata;
            }
            return result;
        }
    }
    else {
        if (n == 0) {
            *size = 0;
            return NULL;
        }
        else {
            return NULL;
        }
    }
}

PARTICIPANTPARAMS_RTPS *parseSetOfPARTICIPANTPARAMS_O (PDU *thePDU, int n, int *size, char *progname, uint8_t endianness) {
    PARTICIPANTPARAMS_RTPS particdata;
    if (parsePARTICIPANTPARAMS (&particdata, thePDU, progname, endianness)) {
        if (particdata.type == PIDSENTINAL_RTPS_VAL) {
            PARTICIPANTPARAMS_RTPS *result = (PARTICIPANTPARAMS_RTPS *) malloc ((n + 1) * sizeof (PARTICIPANTPARAMS_RTPS));
            if (result == NULL) {
                return NULL;
            }
            *size = n + 1;
            result[n] = particdata;
            return result;
        }
        else {
            PARTICIPANTPARAMS_RTPS *result = parseSetOfPARTICIPANTPARAMS_O (thePDU, n +1, size, progname, endianness);
            if (result != NULL) {
                result[n] = particdata;
            }
            return result;
        }
    }
    else {
        if (n == 0) {
            *size = 0;
            return NULL;
        }
        else {
            return NULL;
        }
    }
}

TRANSPORTINFO_RTPS *parseSetOfTRANSPORTINFO (PDU *thePDU, int size, char *progname, uint8_t endianness) {
    TRANSPORTINFO_RTPS *result = (TRANSPORTINFO_RTPS *) malloc (size *sizeof(TRANSPORTINFO_RTPS));
    if (result == NULL) {
        return NULL;
    }
    for (int i = 0; i < size; ++i) {
        TRANSPORTINFO_RTPS info;
        if (parseTRANSPORTINFO (&info, thePDU, progname, endianness))
            result[i] = info;
        else
            return NULL;
    }
    return result;
}

PROPERTY_RTPS *parseSetOfPROPERTY (PDU *thePDU, int size, char *progname, uint8_t endianness) {
    PROPERTY_RTPS *result = (PROPERTY_RTPS *) malloc (size *sizeof(PROPERTY_RTPS));
    if (result == NULL) {
        return NULL;
    }
    for (int i = 0; i < size; ++i) {
        PROPERTY_RTPS list;
        if (parsePROPERTY (&list, thePDU, progname, endianness))
            result[i] = list;
        else
            return NULL;
    }
    return result;
}

