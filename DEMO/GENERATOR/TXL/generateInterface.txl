include "c.grm"

define program
	[repeat config]
	| [repeat preprocessor]
		[repeat function_definition_or_declaration]
		[opt preprocessor]
end define

define config
	[protocol] ': [list packet_type] '> [endian] '< [skip_bits] [opt debug_flag] ';
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

define debug_flag
	'-DEBUG
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

	construct debugTypes [repeat id]
		_
	export debugTypes
		debugTypes

	deconstruct P
		Configs [repeat config]

	by
		P [generateDebugTypes each Configs]
			[generateTypes each Configs]
			[addAuxiliaryData]
end function

function generateTypes Config [config]
	replace [program]
		P [program]

	deconstruct [config] Config
		Proto [protocol] ': PT [list packet_type] '> E [endian] '< SB [skip_bits] D [opt debug_flag]';
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

function generateDebugTypes Config [config]
	replace [program]
		P [program]

	deconstruct [config] Config
		Proto [protocol] ': PT [list packet_type] '> E [endian] '< SB [skip_bits] D [debug_flag]';
	deconstruct [protocol] Proto
		Type [id]
	import debugTypes [repeat id]
	export debugTypes
		debugTypes [. Type]

	by
		P
end function

function generateCase Config [config]
	replace [repeat declaration_or_statement]
		Stmts [repeat declaration_or_statement]
	
	deconstruct [config] Config 
		Proto [protocol] ': PT [list packet_type] '> E [endian] '< SB [skip_bits] D [opt debug_flag] ';
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
		_ [generateStd packetType pduNameLower] [generateDebug packetType pduNameLower]
	construct restStmts [repeat declaration_or_statement]
		skipStmt [. parseStmts]

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

function generateStd	packetType [id] pduNameLower [id]
	import debugTypes [repeat id]
	deconstruct not * [id] debugTypes
		packetType

	replace [repeat declaration_or_statement]
		Stmts [repeat declaration_or_statement]

	construct parseName [id]
		_ [+ "parse"] [+ packetType]
	construct freeName [id]
		_ [+ "freePDU_"] [+ packetType]

	construct parseStmts [repeat declaration_or_statement]
		parsedPDU = parseName('& pduNameLower, thePDU, progname, endianness);
		freeName('& pduNameLower);
		break;

	by
		Stmts [. parseStmts]
end function

function generateDebug	packetType [id] pduNameLower [id]
	import debugTypes [repeat id]
	deconstruct * [id] debugTypes
		packetType

	replace [repeat declaration_or_statement]
		Stmts [repeat declaration_or_statement]

	construct parseName [id]
		_ [+ "parse"] [+ packetType]
	construct freeName [id]
		_ [+ "freePDU_"] [+ packetType]
	construct passName [id]
		_ [+ "i"] [+ packetType]
	construct failName [id]
		_ [+ "i"] [+ packetType] [+ "f"]

	construct parseStmts [repeat declaration_or_statement]
		parsedPDU = parseName('& pduNameLower, thePDU, progname, endianness);
		if (parsedPDU) 
			passName ++;
		else
			failName ++;
		freeName('& pduNameLower);
		break;

	by
		Stmts [. parseStmts]
end function

function addAuxiliaryData
	replace [program]
		P [program]

	import packetTypes [repeat id]
	import debugTypes [repeat id]
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
			iFail++;
			free(thePDU);
			thePDU = NULL;
			return 0;
		}
	import auxData [repeat declaration_or_statement]
	construct switchBody [repeat declaration_or_statement]
		auxData [. defaultCase]

	construct parseBody [repeat declaration_or_statement]
		char *progname = argString;

		iTotal++;
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

		switch (type) {
			switchBody
		}

		free(thePDU);
		thePDU = NULL;
		return parsedPDU;

	construct declareCounts [repeat function_definition_or_declaration]
		'long iTotal = 0;
		'long iFail = 0;

	construct declareDebugs [repeat function_definition_or_declaration]
		_ [generateProtocolCounters each debugTypes]

	construct declares [repeat function_definition_or_declaration]
		declareCounts [. declareDebugs]

	construct parseFunc [repeat function_definition_or_declaration]
		int parseData(const unsigned char *data, const unsigned 'long dataLength, int type) {
			parseBody
		}

	construct printTotal [repeat declaration_or_statement]
		printf( "Total Packets: %lu \n", iTotal);
		printf( "Unparsable Packets: %lu \n", iFail);

	construct printBody [repeat declaration_or_statement]
		_ [generateDebugPrints each debugTypes] [. printTotal]

	construct stats [repeat function_definition_or_declaration]
		void printStats() {
			printBody
		}

	by
		Includes
		declares [. parseFunc] [. stats]
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

function generateProtocolCounters packetType [id]
	replace [repeat function_definition_or_declaration]
		Stmts [repeat function_definition_or_declaration]
	
	construct passName [id]
		_ [+ "i"] [+ packetType]
	construct failName [id]
		_ [+ "i"] [+ packetType] [+ "f"]
	
	construct declares [repeat function_definition_or_declaration]
		'long passName = 0;
		'long failName = 0;

	by
		Stmts [. declares]
end function

function generateDebugPrints packetType [id]
	replace [repeat declaration_or_statement]
		Stmts [repeat declaration_or_statement]

	construct passName [id]
		_ [+ "i"] [+ packetType]
	construct failName [id]
		_ [+ "i"] [+ packetType] [+ "f"]

	construct linePass [stringlit]
		_ [+ ""] [+ packetType] [+ " Parsed: %lu \n"]
	construct lineFail [stringlit]
		_ [+ ""] [+ packetType] [+ " Failed: %lu \n"]

	construct print [repeat declaration_or_statement]
		printf( linePass, passName);
		printf( lineFail, failName);

	by
		Stmts [. print]
end function