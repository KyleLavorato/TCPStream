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
		Proto [protocol] ': PT [list packet_type] '> E [endian] '< SB [skip_bits] D [opt debug_flag] ';
	deconstruct [protocol] Proto
		Type [id]
	import packetTypes [repeat id]
	export packetTypes
		packetTypes [. Type]

	by
		P
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
		'#include <string>
		FinalHeaders

	construct Stmts [repeat function_definition_or_declaration]
		int parseData(const unsigned char *data, const unsigned 'long dataLength, int type);

	construct stats [repeat function_definition_or_declaration]
		void printStats();

	construct stringAnd [id]
		_ [+ "std::string"] [+ "&"]
	construct getConstant [repeat function_definition_or_declaration]
		int getConstantForProtocol(const stringAnd 'protocol);

	by
		Includes
		Stmts [. stats] [. getConstant]
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