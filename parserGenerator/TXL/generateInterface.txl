include "../GRM/c.grm"

define program
	[repeat config]
	| [repeat preprocessor]
		[repeat function_definition_or_declaration]
		[opt preprocessor]
end define

define config
	[protocol] ': [list packet_type] '> [endian] '< [skip_bits] ';
	| [repeat function_definition_or_declaration]
end define

define protocol
	[id]
end define

define packet_type
	[id]
end define

define endian
	'B
	| 'L
end define

define skip_bits
	[number]
end define

function main
	replace [program]
		P [program]
	
	construct auxData [repeat declaration_or_statement]
		_
	export auxData

	construct count [number]
		'1
	export count

	construct packetTypes [repeat id]
		_
	export packetTypes
		packetTypes

	deconstruct P
		Configs [repeat config]

	by
		P [generateTypes each Configs]
			[addAuxiliaryData]
end function

function generateTypes Config [config]
	replace [program]
		P [program]

	deconstruct [config] Config
		Proto [protocol] ': PT [list packet_type] '> E [endian] '< SB [skip_bits] ';
	deconstruct [protocol] Proto
		Type [id]
	import packetTypes [repeat id]
	export packetTypes
		packetTypes [. Type]

	construct caseStmt [repeat declaration_or_statement]
		_ [generateCase Config]
	import auxData [repeat declaration_or_statement]
	export auxData
		auxData [. caseStmt]

	by
		P
end function

function generateCase Config [config]
	replace [repeat declaration_or_statement]
		Stmts [repeat declaration_or_statement]
	
	deconstruct [config] Config 
		Proto [protocol] ': PT [list packet_type] '> E [endian] '< SB [skip_bits] ';
	deconstruct [protocol] Proto
		packetType [id]

	construct pduName [id]
		_ [+ "PDU_"] [+ packetType]
	construct pduNameLower [id]
		pduName [tolower]
	construct typeName [id]
		packetType [+ "_TYPE"]

	construct endianType [id]
		_ [generateLittleEndian E] [generateBigEndian E]
	construct skipStmt [repeat declaration_or_statement]
		_ [generateSkipStatement SB]
	construct parseStmts [repeat declaration_or_statement]
		paredPDU = parseName('& pduNameLower, thePDU, progname, endianness);
		freeName('& pduNameLower);
		break;
	construct restStmts [repeat declaration_or_statement]
		skipStmt [. parseStmts]

	construct parseName [id]
		_ [+ "parse"] [+ packetType]
	construct freeName [id]
		_ [+ "freePDU_"] [+ packetType]

	construct Body [repeat declaration_or_statement]
		case typeName:
		{
			pduName pduNameLower;
			endianness = endianType;
			restStmts
		}

	by
		Stmts [. Body]
end function

function generateLittleEndian E [endian]
	replace [id]
		blank [id]
	deconstruct [endian] E
		'L
	by
		LITTLEENDIAN
end function

function generateBigEndian E [endian]
	replace [id]
		blank [id]
	deconstruct [endian] E
		'B
	by
		BIGENDIAN
end function

function generateSkipStatement SB [skip_bits]
	deconstruct [skip_bits] SB
		Bits [number]
	where
		Bits [> 0]
	replace [repeat declaration_or_statement]
		Stmts [repeat declaration_or_statement]
	construct uintType [id]
		_ [+ "uint"] [+ Bits] [+ "_t"]
	construct getName [id]
		_ [+ "get"] [+ Bits] [+ "_e"]
	construct skipStmt [repeat declaration_or_statement]
		uintType SKIPBITS = getName(thePDU, endianness);
	by
		Stmts [. skipStmt]
end function

function addAuxiliaryData
	replace [program]
		P [program]

	import packetTypes [repeat id]
	construct FinalHeaderIncludes [repeat preprocessor]
		_ [generateIncludes each packetTypes]
	construct FinalHeaderDefines [repeat preprocessor]
		_ [generateDefines each packetTypes]
	construct FinalHeaders [repeat preprocessor]
		FinalHeaderIncludes [. FinalHeaderDefines]

	construct Includes [repeat preprocessor]
		'#define BIGENDIAN (0x0)
		'#define LITTLEENDIAN (0x1)
		'#include "packet.h"
		'#include "putilities.h"
		FinalHeaders

	construct defaultCase [repeat declaration_or_statement]
		default:
		{
			free(thePDU)
			thePDU = NULL;
			return 0;
		}
	import auxData [repeat declaration_or_statement]
	construct switchBody [repeat declaration_or_statement]
		auxData [. defaultCase]

	construct parseBody [repeat declaration_or_statement]
		char *progname = argString;

		bool parsedPDU;
		PDUP * thePDU;
		thePDU = (PDUP*)malloc(sizeof(PDUP));

		thePDU->len = dataLength;
		thePDU->watermark= dataLength;
		thePDU->curPos = 0;
		thePDU->data = (unsigned char *)data;

		thePDU ->curPos = 0;
		thePDU ->curBitPos = 0;
		thePDU ->remaining = thePDU ->len;
		thePDU->header = NULL;
		uint8_t endianness;

		uint32_t NETBIOS = get32_e (thePDU, endianness);

		switch (type) {
			switchBody
		}

		free(thePDU);
		thePDU = NULL;
		return 1;

	construct Stmts [repeat function_definition_or_declaration]
		int parseData(const unsigned char *data, const unsigned lng dataLength, int type) {
			parseBody
		}

	by
		Includes
		Stmts
end function

function generateIncludes packetType [id]
	replace [repeat preprocessor]
		P [repeat preprocessor]

	construct ModuleHeader [stringlit]
		_ [+ "#include \""] [+ packetType] [+ "_Generated"] [+ ".h\""]
	construct ModuleHeaderPRE [opt preprocessor]
		_ [parse ModuleHeader]
	deconstruct ModuleHeaderPRE
		FinalHeaderInclude [preprocessor]

	by
		P [. FinalHeaderInclude]
end function

function generateDefines packetType [id]
	replace [repeat preprocessor]
		P [repeat preprocessor]

	import count [number]
	construct ModuleHeader [stringlit]
		_ [+ "#define "] [+ packetType] [+ "_TYPE ("] [+ count] [+ ")"]
	construct ModuleHeaderPRE [opt preprocessor]
		_ [parse ModuleHeader]
	deconstruct ModuleHeaderPRE
		FinalHeaderDefine [preprocessor]
	export count
		count [+ 1]

	by
		P [. FinalHeaderDefine]
end function