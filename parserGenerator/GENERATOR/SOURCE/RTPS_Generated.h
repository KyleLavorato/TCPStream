#ifndef RTPS_H
#define RTPS_H
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>
#include "packet.h"
#include "globals.h"
#define FULL_RTPS_VAL (1)
#define PING_RTPS_VAL (2)
#define DATAPSUB_RTPS_VAL (3)
#define DATASUB_RTPS_VAL (4)
#define ACKNACK_RTPS_VAL (5)
#define HEARTBEAT_RTPS_VAL (6)
#define INFO$DST_RTPS_VAL (7)
#define INFO$TS_RTPS_VAL (8)
#define DATAWSUB_RTPS_VAL (9)
#define DATARSUB_RTPS_VAL (10)
#define GAP_RTPS_VAL (11)
#define PIDSTATUSINFO_RTPS_VAL (12)
#define PIDKEYHASH_RTPS_VAL (13)
#define PIDSENTINAL_RTPS_VAL (14)
#define PIDTOPICNAME_RTPS_VAL (15)
#define PIDTYPENAME_RTPS_VAL (16)
#define PIDRELIABILITY_RTPS_VAL (17)
#define PIDENDPOINTGUID_RTPS_VAL (18)
#define PIDMULTICASTLOCATOR_RTPS_VAL (19)
#define PIDUNICASTLOCATOR_RTPS_VAL (20)
#define PIDUNKNOWN_RTPS_VAL (21)
#define PIDACKKIND_RTPS_VAL (22)
#define PIDRECVQUEUE_RTPS_VAL (23)
#define PIDTIMEBASEDFILTER_RTPS_VAL (24)
#define PIDLIVELINESS_RTPS_VAL (25)
#define PIDDURABILITY_RTPS_VAL (26)
#define PIDDIRECTCOMMUNICATION_RTPS_VAL (27)
#define PIDOWNERSHIP_RTPS_VAL (28)
#define PIDPRESENTATION_RTPS_VAL (29)
#define PIDDESTINATIONORDER_RTPS_VAL (30)
#define PIDDEADLINE_RTPS_VAL (31)
#define PIDLATENCYBUDGET_RTPS_VAL (32)
#define PIDGROUPENTITYID_RTPS_VAL (33)
#define PIDENTITYVIRTUALGUID_RTPS_VAL (34)
#define PIDSERVICEKIND_RTPS_VAL (35)
#define PIDPROTOVERSION_RTPS_VAL (36)
#define PIDPRODUCTVERSION_RTPS_VAL (37)
#define PIDDISABLEPOSITIVEACKS_RTPS_VAL (38)
#define PIDEXPECTSVIRTUALHB_RTPS_VAL (39)
#define PIDTYPECONSISTENCY_RTPS_VAL (40)
#define PIDTYPEOBJECT_RTPS_VAL (41)
#define PIDTYPECODE_RTPS_VAL (42)
#define PIDVENDORID_RTPS_VAL (43)
#define PIDENTITYNAME_RTPS_VAL (44)
#define PIDEXPECTSACK_RTPS_VAL (45)
#define PIDSENDQUEUESIZE_RTPS_VAL (46)
#define PIDOWNERSHIPSTRENGTH_RTPS_VAL (47)
#define PIDPERSISTENCE_RTPS_VAL (48)
#define PIDLIFESPAN_RTPS_VAL (49)
#define PIDTYPEMAXSIZESERIALIZED_RTPS_VAL (50)
#define PIDDURABILITYSERVICE_RTPS_VAL (51)
#define PIDPARTICIPANTGUID_RTPS_VAL (52)
#define PIDPARTICIPANTBUILTENDPOINTS_RTPS_VAL (53)
#define PIDBUILTINENDPOINTSET_RTPS_VAL (54)
#define PIDMETATRAFFICUNILOCATOR_RTPS_VAL (55)
#define PIDDEFMULTILOCATOR_RTPS_VAL (56)
#define PIDPARTICIPANTLIVECOUNT_RTPS_VAL (57)
#define PIDPARTICIPANTLEASE_RTPS_VAL (58)
#define PIDDEFUNILOCATOR_RTPS_VAL (59)
#define PIDMETATRAFFICMULTILOCATOR_RTPS_VAL (60)
#define PIDPROPERTYLIST_RTPS_VAL (61)
#define PIDROLENAME_RTPS_VAL (62)
#define PIDPEERHOSTEPOCH_RTPS_VAL (63)
#define PIDDOMAINID_RTPS_VAL (64)
#define PIDTRANSPORTINFOLIST_RTPS_VAL (65)
typedef struct {
    uint32_t protoname;
    uint16_t version;
    uint16_t vendorid;
} HEADER_RTPS;
typedef struct {
    HEADER_RTPS header;
    uint64_t ping;
} PING_RTPS;
typedef struct {
    uint32_t hostid;
    uint32_t appid;
    uint32_t counter;
} GUIDPREFIX_RTPS;
typedef struct {
    HEADER_RTPS header;
    GUIDPREFIX_RTPS guidprefix;
    unsigned long submsglength;
    unsigned long submsgcount;
} FULL_RTPS;
typedef struct {
    uint32_t type;
    union {
        FULL_RTPS full_rtps;
        PING_RTPS ping_rtps;
    } ptr;
} PDU_RTPS;
typedef struct {
    uint16_t parameterkind;
    uint16_t parameterlength;
    unsigned long flags_length;
    unsigned char *flags;
} PIDSTATUSINFO_RTPS;
typedef struct {
    uint16_t parameterkind;
    uint16_t parameterlength;
    unsigned long guid_length;
    unsigned char *guid;
} PIDKEYHASH_RTPS;
typedef struct {
    uint16_t parameterkind;
    uint16_t parameterlength;
    unsigned long value_length;
    unsigned char *value;
} PIDTYPEMAXSIZESERIALIZED_RTPS;
typedef struct {
    uint16_t parameterkind;
    uint16_t parameterlength;
    unsigned long leaseduration_length;
    unsigned char *leaseduration;
} PIDLIFESPAN_RTPS;
typedef struct {
    uint16_t parameterkind;
    uint16_t parameterlength;
    unsigned long durabilityservice_length;
    unsigned char *durabilityservice;
} PIDDURABILITYSERVICE_RTPS;
typedef struct {
    uint16_t parameterkind;
    uint16_t parameterlength;
    unsigned long leaseduration_length;
    unsigned char *leaseduration;
} PIDPERSISTENCE_RTPS;
typedef struct {
    uint16_t parameterkind;
    uint16_t parameterlength;
    unsigned long strength_length;
    unsigned char *strength;
} PIDOWNERSHIPSTRENGTH_RTPS;
typedef struct {
    uint16_t parameterkind;
    uint16_t parameterlength;
    unsigned long queuesize_length;
    unsigned char *queuesize;
} PIDSENDQUEUESIZE_RTPS;
typedef struct {
    uint16_t parameterkind;
    uint16_t parameterlength;
    unsigned long expectsack_length;
    unsigned char *expectsack;
} PIDEXPECTSACK_RTPS;
typedef struct {
    uint16_t parameterkind;
    uint16_t parameterlength;
    unsigned long typeobjectcode_length;
    unsigned char *typeobjectcode;
} PIDTYPECODE_RTPS;
typedef struct {
    uint16_t parameterkind;
    uint16_t parameterlength;
    unsigned long typeobject_length;
    unsigned char *typeobject;
} PIDTYPEOBJECT_RTPS;
typedef struct {
    uint16_t kind;
} TYPECONSISTENCYKIND_RTPS;
typedef struct {
    uint16_t parameterkind;
    uint16_t parameterlength;
    TYPECONSISTENCYKIND_RTPS typeconsistencykind;
} PIDTYPECONSISTENCY_RTPS;
typedef struct {
    uint8_t flag;
} FLAG_RTPS;
typedef struct {
    uint16_t parameterkind;
    uint16_t parameterlength;
    FLAG_RTPS disablepositiveacks;
} PIDDISABLEPOSITIVEACKS_RTPS;
typedef struct {
    uint16_t parameterkind;
    uint16_t parameterlength;
    FLAG_RTPS expectsvirtualhb;
} PIDEXPECTSVIRTUALHB_RTPS;
typedef struct {
    uint16_t parameterkind;
    uint16_t parameterlength;
    unsigned long servicekind_length;
    unsigned char *servicekind;
} PIDSERVICEKIND_RTPS;
typedef struct {
    uint16_t parameterkind;
    uint16_t parameterlength;
    unsigned long leaseduration_length;
    unsigned char *leaseduration;
} PIDLATENCYBUDGET_RTPS;
typedef struct {
    uint16_t parameterkind;
    uint16_t parameterlength;
    unsigned long leaseduration_length;
    unsigned char *leaseduration;
} PIDDEADLINE_RTPS;
typedef struct {
    uint16_t parameterkind;
    uint16_t parameterlength;
    unsigned long kind_length;
    unsigned char *kind;
} PIDDESTINATIONORDER_RTPS;
typedef struct {
    uint32_t accessscope;
    uint8_t coherentaccess;
    uint8_t orderedaccess;
} PRESENTATION_RTPS;
typedef struct {
    uint16_t parameterkind;
    uint16_t parameterlength;
    PRESENTATION_RTPS presentation;
} PIDPRESENTATION_RTPS;
typedef struct {
    uint16_t parameterkind;
    uint16_t parameterlength;
    unsigned long kind_length;
    unsigned char *kind;
} PIDOWNERSHIP_RTPS;
typedef struct {
    uint8_t directcommunication;
} DIRECTCOMMUNICATION_RTPS;
typedef struct {
    uint16_t parameterkind;
    uint16_t parameterlength;
    DIRECTCOMMUNICATION_RTPS directcommunication;
} PIDDIRECTCOMMUNICATION_RTPS;
typedef struct {
    uint16_t parameterkind;
    uint16_t parameterlength;
    unsigned long durability_length;
    unsigned char *durability;
} PIDDURABILITY_RTPS;
typedef struct {
    uint16_t parameterkind;
    uint16_t parameterlength;
    unsigned long liveliness_length;
    unsigned char *liveliness;
} PIDLIVELINESS_RTPS;
typedef struct {
    uint16_t parameterkind;
    uint16_t parameterlength;
    unsigned long leaseduration_length;
    unsigned char *leaseduration;
} PIDTIMEBASEDFILTER_RTPS;
typedef struct {
    uint16_t parameterkind;
    uint16_t parameterlength;
    unsigned long queuesize_length;
    unsigned char *queuesize;
} PIDRECVQUEUE_RTPS;
typedef struct {
    uint16_t parameterkind;
    uint16_t parameterlength;
    unsigned long ackkind_length;
    unsigned char *ackkind;
} PIDACKKIND_RTPS;
typedef struct {
    uint16_t parameterkind;
    unsigned char slackbytes [18];
} PIDUNKNOWN_RTPS;
typedef struct {
    uint32_t namelength;
    unsigned long name_length;
    unsigned char *name;
} NESTEDSTRING_RTPS;
typedef struct {
    uint16_t parameterkind;
    uint16_t parameterlength;
    NESTEDSTRING_RTPS typename;
} PIDTYPENAME_RTPS;
typedef struct {
    uint16_t parameterkind;
    uint16_t parameterlength;
    NESTEDSTRING_RTPS topicname;
} PIDTOPICNAME_RTPS;
typedef struct {
    uint16_t parameterkind;
    uint16_t parameterlength;
    uint32_t reliabilityqos;
    unsigned long slack_length;
    unsigned char *slack;
} PIDRELIABILITY_RTPS;
typedef struct {
    uint8_t kind;
    uint8_t flags;
    uint16_t nextheader;
    GUIDPREFIX_RTPS guidpfx;
} INFO$DST_RTPS;
typedef struct {
    uint8_t kind;
    uint8_t flags;
    uint16_t nextheader;
    uint64_t timestamp;
} INFO$TS_RTPS;
typedef struct {
    uint8_t major;
    uint8_t minor;
    uint8_t release;
    uint8_t revision;
} PRODUCTVERSION_RTPS;
typedef struct {
    uint16_t parameterkind;
    uint16_t parameterlength;
    PRODUCTVERSION_RTPS productversion;
} PIDPRODUCTVERSION_RTPS;
typedef struct {
    uint32_t classid;
    uint32_t messagesizemax;
} TRANSPORTINFO_RTPS;
typedef struct {
    uint32_t transportnum;
    unsigned long infolength;
    unsigned long infocount;
    TRANSPORTINFO_RTPS *info;
} TRANSPORTS_RTPS;
typedef struct {
    uint16_t parameterkind;
    uint16_t parameterlength;
    TRANSPORTS_RTPS transports;
} PIDTRANSPORTINFOLIST_RTPS;
typedef struct {
    uint16_t parameterkind;
    uint16_t parameterlength;
    unsigned long domainid_length;
    unsigned char *domainid;
} PIDDOMAINID_RTPS;
typedef struct {
    uint16_t parameterkind;
    uint16_t parameterlength;
    unsigned long hostepoch_length;
    unsigned char *hostepoch;
} PIDPEERHOSTEPOCH_RTPS;
typedef struct {
    uint16_t parameterkind;
    uint16_t parameterlength;
    NESTEDSTRING_RTPS rolename;
} PIDROLENAME_RTPS;
typedef struct {
    uint16_t parameterkind;
    uint16_t parameterlength;
    NESTEDSTRING_RTPS entityname;
} PIDENTITYNAME_RTPS;
typedef struct {
    NESTEDSTRING_RTPS name;
    NESTEDSTRING_RTPS value;
} PROPERTY_RTPS;
typedef struct {
    uint32_t numproperties;
    unsigned long listlength;
    unsigned long listcount;
    PROPERTY_RTPS *list;
} PROPERTYLIST_RTPS;
typedef struct {
    uint16_t parameterkind;
    uint16_t parameterlength;
    PROPERTYLIST_RTPS properties;
} PIDPROPERTYLIST_RTPS;
typedef struct {
    uint8_t major;
    uint8_t minor;
} PROTOCOLVERSION_RTPS;
typedef struct {
    uint16_t parameterkind;
    uint16_t parameterlength;
    PROTOCOLVERSION_RTPS protocolversion;
} PIDPROTOVERSION_RTPS;
typedef struct {
    uint16_t vendorid;
} VENDORID_RTPS;
typedef struct {
    uint16_t parameterkind;
    uint16_t parameterlength;
    VENDORID_RTPS vendor;
} PIDVENDORID_RTPS;
typedef struct {
    uint16_t parameterkind;
    uint16_t parameterlength;
    uint32_t builtin;
} PIDPARTICIPANTBUILTENDPOINTS_RTPS;
typedef struct {
    uint32_t flags;
} FLAGS_RTPS;
typedef struct {
    uint16_t parameterkind;
    uint16_t parameterlength;
    FLAGS_RTPS builtin;
} PIDBUILTINENDPOINTSET_RTPS;
typedef struct {
    uint32_t kind;
    uint32_t port;
    unsigned char address [16];
} LOCATOR_RTPS;
typedef struct {
    uint16_t parameterkind;
    uint16_t parameterlength;
    LOCATOR_RTPS locator;
} PIDDEFMULTILOCATOR_RTPS;
typedef struct {
    uint16_t parameterkind;
    uint16_t parameterlength;
    LOCATOR_RTPS locator;
} PIDMETATRAFFICMULTILOCATOR_RTPS;
typedef struct {
    uint16_t parameterkind;
    uint16_t parameterlength;
    LOCATOR_RTPS locator;
} PIDMULTICASTLOCATOR_RTPS;
typedef struct {
    uint16_t parameterkind;
    uint16_t parameterlength;
    LOCATOR_RTPS locator;
} PIDDEFUNILOCATOR_RTPS;
typedef struct {
    uint16_t parameterkind;
    uint16_t parameterlength;
    LOCATOR_RTPS locator;
} PIDMETATRAFFICUNILOCATOR_RTPS;
typedef struct {
    uint16_t parameterkind;
    uint16_t parameterlength;
    LOCATOR_RTPS locator;
} PIDUNICASTLOCATOR_RTPS;
typedef struct {
    uint16_t parameterkind;
    uint16_t parameterlength;
    uint32_t manuallivecount;
} PIDPARTICIPANTLIVECOUNT_RTPS;
typedef struct {
    uint32_t seconds;
    uint32_t fraction;
} LEASEDURATION_RTPS;
typedef struct {
    uint16_t parameterkind;
    uint16_t parameterlength;
    LEASEDURATION_RTPS duration;
} PIDPARTICIPANTLEASE_RTPS;
typedef struct {
    uint16_t parameterkind;
    uint16_t parameterlength;
} PIDSENTINAL_RTPS;
typedef struct {
    uint32_t type;
    union {
        PIDSTATUSINFO_RTPS pidstatusinfo_rtps;
        PIDKEYHASH_RTPS pidkeyhash_rtps;
        PIDSENTINAL_RTPS pidsentinal_rtps;
    } ptr;
} QOSPARMS_RTPS;
typedef struct {
    unsigned long qoslength;
    unsigned long qoscount;
    QOSPARMS_RTPS *qos;
} QOSPARM_RTPS;
typedef struct {
    uint32_t key;
    uint8_t kind;
} ENTITYID_RTPS;
typedef struct {
    GUIDPREFIX_RTPS guid;
    ENTITYID_RTPS entityid;
} PARTICIPANTGUID_RTPS;
typedef struct {
    uint16_t parameterkind;
    uint16_t parameterlength;
    PARTICIPANTGUID_RTPS participantguid;
} PIDPARTICIPANTGUID_RTPS;
typedef struct {
    uint32_t type;
    union {
        PIDPROTOVERSION_RTPS pidprotoversion_rtps;
        PIDPARTICIPANTGUID_RTPS pidparticipantguid_rtps;
        PIDVENDORID_RTPS pidvendorid_rtps;
        PIDPARTICIPANTBUILTENDPOINTS_RTPS pidparticipantbuiltendpoints_rtps;
        PIDBUILTINENDPOINTSET_RTPS pidbuiltinendpointset_rtps;
        PIDMETATRAFFICUNILOCATOR_RTPS pidmetatrafficunilocator_rtps;
        PIDDEFMULTILOCATOR_RTPS piddefmultilocator_rtps;
        PIDPARTICIPANTLIVECOUNT_RTPS pidparticipantlivecount_rtps;
        PIDPARTICIPANTLEASE_RTPS pidparticipantlease_rtps;
        PIDSENTINAL_RTPS pidsentinal_rtps;
        PIDDEFUNILOCATOR_RTPS piddefunilocator_rtps;
        PIDMETATRAFFICMULTILOCATOR_RTPS pidmetatrafficmultilocator_rtps;
        PIDPROPERTYLIST_RTPS pidpropertylist_rtps;
        PIDENTITYNAME_RTPS pidentityname_rtps;
        PIDROLENAME_RTPS pidrolename_rtps;
        PIDPEERHOSTEPOCH_RTPS pidpeerhostepoch_rtps;
        PIDDOMAINID_RTPS piddomainid_rtps;
        PIDTRANSPORTINFOLIST_RTPS pidtransportinfolist_rtps;
        PIDPRODUCTVERSION_RTPS pidproductversion_rtps;
    } ptr;
} PARTICIPANTPARAMS_RTPS;
typedef struct {
    uint16_t encapskind;
    uint16_t encapsopts;
    unsigned long particdatalength;
    unsigned long particdatacount;
    PARTICIPANTPARAMS_RTPS *particdata;
} PARTICIPANTS_RTPS;
typedef struct {
    uint8_t kind;
    uint8_t flags;
    uint16_t nextheader;
    ENTITYID_RTPS readerent;
    ENTITYID_RTPS writerent;
    uint64_t firstseq;
    uint64_t lastseq;
    uint32_t count;
} HEARTBEAT_RTPS;
typedef struct {
    GUIDPREFIX_RTPS guidprefix;
    ENTITYID_RTPS virtualguidsuffix;
} VIRTUALGUID_RTPS;
typedef struct {
    uint16_t parameterkind;
    uint16_t parameterlength;
    VIRTUALGUID_RTPS virtualguid;
} PIDENTITYVIRTUALGUID_RTPS;
typedef struct {
    uint8_t kind;
    uint8_t flags;
    uint16_t nextheader;
    uint16_t extraflags;
    uint16_t qosoffset;
    ENTITYID_RTPS readerent;
    ENTITYID_RTPS writerent;
    uint64_t writerseq;
    QOSPARM_RTPS *inlineqos;
    unsigned long serializeddata_length;
    unsigned char *serializeddata;
} DATASUB_RTPS;
typedef struct {
    uint8_t kind;
    uint8_t flags;
    uint16_t nextheader;
    uint16_t extraflags;
    uint16_t qosoffset;
    ENTITYID_RTPS readerent;
    ENTITYID_RTPS writerent;
    uint64_t writerseq;
    QOSPARM_RTPS *inlineqos;
    PARTICIPANTS_RTPS *serializeddata;
} DATAPSUB_RTPS;
typedef struct {
    uint16_t parameterkind;
    uint16_t parameterlength;
    GUIDPREFIX_RTPS participantguid;
    ENTITYID_RTPS entityid;
} PIDENDPOINTGUID_RTPS;
typedef struct {
    uint16_t parameterkind;
    uint16_t parameterlength;
    ENTITYID_RTPS groupentityid;
} PIDGROUPENTITYID_RTPS;
typedef struct {
    uint32_t type;
    union {
        PIDTOPICNAME_RTPS pidtopicname_rtps;
        PIDTYPENAME_RTPS pidtypename_rtps;
        PIDRELIABILITY_RTPS pidreliability_rtps;
        PIDENDPOINTGUID_RTPS pidendpointguid_rtps;
        PIDMULTICASTLOCATOR_RTPS pidmulticastlocator_rtps;
        PIDUNICASTLOCATOR_RTPS pidunicastlocator_rtps;
        PIDSENTINAL_RTPS pidsentinal_rtps;
        PIDUNKNOWN_RTPS pidunknown_rtps;
        PIDACKKIND_RTPS pidackkind_rtps;
        PIDRECVQUEUE_RTPS pidrecvqueue_rtps;
        PIDTIMEBASEDFILTER_RTPS pidtimebasedfilter_rtps;
        PIDLIVELINESS_RTPS pidliveliness_rtps;
        PIDDURABILITY_RTPS piddurability_rtps;
        PIDDIRECTCOMMUNICATION_RTPS piddirectcommunication_rtps;
        PIDOWNERSHIP_RTPS pidownership_rtps;
        PIDPRESENTATION_RTPS pidpresentation_rtps;
        PIDDESTINATIONORDER_RTPS piddestinationorder_rtps;
        PIDDEADLINE_RTPS piddeadline_rtps;
        PIDLATENCYBUDGET_RTPS pidlatencybudget_rtps;
        PIDGROUPENTITYID_RTPS pidgroupentityid_rtps;
        PIDENTITYVIRTUALGUID_RTPS pidentityvirtualguid_rtps;
        PIDSERVICEKIND_RTPS pidservicekind_rtps;
        PIDPROTOVERSION_RTPS pidprotoversion_rtps;
        PIDPRODUCTVERSION_RTPS pidproductversion_rtps;
        PIDDISABLEPOSITIVEACKS_RTPS piddisablepositiveacks_rtps;
        PIDEXPECTSVIRTUALHB_RTPS pidexpectsvirtualhb_rtps;
        PIDTYPECONSISTENCY_RTPS pidtypeconsistency_rtps;
        PIDTYPEOBJECT_RTPS pidtypeobject_rtps;
        PIDTYPECODE_RTPS pidtypecode_rtps;
        PIDVENDORID_RTPS pidvendorid_rtps;
        PIDENTITYNAME_RTPS pidentityname_rtps;
        PIDEXPECTSACK_RTPS pidexpectsack_rtps;
        PIDSENDQUEUESIZE_RTPS pidsendqueuesize_rtps;
        PIDOWNERSHIPSTRENGTH_RTPS pidownershipstrength_rtps;
        PIDPERSISTENCE_RTPS pidpersistence_rtps;
        PIDLIFESPAN_RTPS pidlifespan_rtps;
        PIDTYPEMAXSIZESERIALIZED_RTPS pidtypemaxsizeserialized_rtps;
        PIDDURABILITYSERVICE_RTPS piddurabilityservice_rtps;
    } ptr;
} TOPICPARMS_RTPS;
typedef struct {
    uint16_t encapskind;
    uint16_t encapsopts;
    unsigned long topicdatalength;
    unsigned long topicdatacount;
    TOPICPARMS_RTPS *topicdata;
} TOPICS_RTPS;
typedef struct {
    uint8_t kind;
    uint8_t flags;
    uint16_t nextheader;
    uint16_t extraflags;
    uint16_t qosoffset;
    ENTITYID_RTPS readerent;
    ENTITYID_RTPS writerent;
    uint64_t writerseq;
    QOSPARM_RTPS *inlineqos;
    TOPICS_RTPS *serializeddata;
} DATAWSUB_RTPS;
typedef struct {
    uint8_t kind;
    uint8_t flags;
    uint16_t nextheader;
    uint16_t extraflags;
    uint16_t qosoffset;
    ENTITYID_RTPS readerent;
    ENTITYID_RTPS writerent;
    uint64_t writerseq;
    QOSPARM_RTPS *inlineqos;
    TOPICS_RTPS *serializeddata;
} DATARSUB_RTPS;
typedef struct {
    uint32_t slack;
} SLACK_RTPS;
typedef struct {
    uint64_t bitmapbase;
    uint32_t nmbits;
    SLACK_RTPS *bitmap;
} SNSTATE_RTPS;
typedef struct {
    uint8_t kind;
    uint8_t flags;
    uint16_t nextheader;
    ENTITYID_RTPS readerent;
    ENTITYID_RTPS writerent;
    uint64_t gapstart;
    SNSTATE_RTPS snstate;
} GAP_RTPS;
typedef struct {
    uint8_t kind;
    uint8_t flags;
    uint16_t nextheader;
    ENTITYID_RTPS readerent;
    ENTITYID_RTPS writerent;
    SNSTATE_RTPS readersn;
    uint32_t counter;
} ACKNACK_RTPS;
typedef struct {
    uint32_t type;
    union {
        DATAPSUB_RTPS datapsub_rtps;
        DATASUB_RTPS datasub_rtps;
        ACKNACK_RTPS acknack_rtps;
        HEARTBEAT_RTPS heartbeat_rtps;
        INFO$DST_RTPS info$dst_rtps;
        INFO$TS_RTPS info$ts_rtps;
        DATAWSUB_RTPS datawsub_rtps;
        DATARSUB_RTPS datarsub_rtps;
        GAP_RTPS gap_rtps;
    } ptr;
} SUBMESSAGE_RTPS;
void DATASUB_RTPS_callback (FULL_RTPS * full_rtps, DATASUB_RTPS * datasub_rtps, PDU * thePDU);
void DATAWSUB_RTPS_callback (FULL_RTPS * full_rtps, DATAWSUB_RTPS * datawsub_rtps, PDU * thePDU);
void DATAPSUB_RTPS_callback (FULL_RTPS * full_rtps, DATAPSUB_RTPS * datapsub_rtps, PDU * thePDU);
void DATARSUB_RTPS_callback (FULL_RTPS * full_rtps, DATARSUB_RTPS * datarsub_rtps, PDU * thePDU);
void INFO$DST_RTPS_callback (FULL_RTPS * full_rtps, INFO$DST_RTPS * info$dst_rtps, PDU * thePDU);
void INFO$TS_RTPS_callback (FULL_RTPS * full_rtps, INFO$TS_RTPS * info$ts_rtps, PDU * thePDU);
void ACKNACK_RTPS_callback (FULL_RTPS * full_rtps, ACKNACK_RTPS * acknack_rtps, PDU * thePDU);
void HEARTBEAT_RTPS_callback (FULL_RTPS * full_rtps, HEARTBEAT_RTPS * heartbeat_rtps, PDU * thePDU);
void GAP_RTPS_callback (FULL_RTPS * full_rtps, GAP_RTPS * gap_rtps, PDU * thePDU);
bool parseRTPS (PDU_RTPS * pdu_rtps, PDU * thePDU, char * name, uint8_t endianness);
void freePDU_RTPS (PDU_RTPS * mainpdu);
void freeDATASUB_RTPS (DATASUB_RTPS * datasub_rtps);
void freeDATAWSUB_RTPS (DATAWSUB_RTPS * datawsub_rtps);
void freeDATAPSUB_RTPS (DATAPSUB_RTPS * datapsub_rtps);
void freeDATARSUB_RTPS (DATARSUB_RTPS * datarsub_rtps);
void freeINFO$DST_RTPS (INFO$DST_RTPS * info$dst_rtps);
void freeINFO$TS_RTPS (INFO$TS_RTPS * info$ts_rtps);
void freeACKNACK_RTPS (ACKNACK_RTPS * acknack_rtps);
void freeHEARTBEAT_RTPS (HEARTBEAT_RTPS * heartbeat_rtps);
void freeGAP_RTPS (GAP_RTPS * gap_rtps);
#endif
