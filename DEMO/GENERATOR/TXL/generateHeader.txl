% Generate Header
% Ali El-Shakankiry
% Queen's University, Jan 2017

% Copyright 2017 Thomas Dean

% Revision history:

% 1.2 Documentation			- KPL	26 06 2017
% 1.1 Callback annotation 	- KPL	14 06 2017
% 1.0 Initial revision 		- AES 	01 01 2017 

% This program walks through a SCL5 file and generates a header file for
% a parser for the specified protocol.

% The input to the program is a SCL5 file named "protocol"_UID_annotated.scl5.
% The input file has been annotated by the previous TXL scripts, marking it for
% various optimizations and ensuring unique naming.

% The output of this program is a header file named 
% "protocol"_Generated.h.unsorted. The output file describes the protocol in
% terms of c structs.


% Base grammars

include "c.grm"
include "ASNOne.Grm"

% Local grammar overrides

define optimizable
	'@ 'optimizable
end define

define global
	'@ 'GLOBAL
end define

define at
	'@
end define

define annotation
	[opt at] [opt number] [opt number] [opt global] [opt optimizable] 
end define

redefine type_reference
	[id] [opt dotID] [opt annotation]
end redefine

define dot_rp
	'. [referenced_element]
end define

redefine referenced_element
	[referencable_primaries] [repeat dot_rp]
end redefine

redefine decl
    [id] [opt hatID] [opt global] [opt optimizable] 
end redefine

redefine element_type
   [named_type] [opt position_value]
   | [named_type] 'OPTIONAL [opt position_value]
   |	 [named_type] 'DEFAULT [value] 
   | 	 [id]'COMPONENTS 'OF [id] 
end redefine

define position_value
  'POS
end define

% Language transformarions between SCL5 and C

redefine type_rule_definition
	% scl5
	[decl] [opt annotation] '::= [type] [opt scl_additions]
	% C
	| [function_definition_or_declaration]
end redefine

redefine construction_assignment_statement
	% scl5
	[decl] '::= [type_decision] [opt scl_additions]				[NL]
	% C
	| [function_definition_or_declaration]
	| [repeat preprocessor]
end redefine

redefine program
	...
	| [repeat preprocessor]
		[repeat rule_definition]
		[opt preprocessor]
end redefine

redefine member_declaration
	...
	| [decl_specifiers] [list init_declarator] [semi]
end redefine

redefine constant
	...
	| 'NULL
end redefine

redefine alternative_decision
	...
	| [repeat preprocessor]
end redefine

redefine preprocessor
	...
	| [repeat alternative_decision]
end redefine

% Main rule followed by other rules in topological order

function main
	replace [program]
		P [program]

	% Global variable to hold all the function header definitions
	construct AuxFunctionHeaders [repeat rule_definition]
	export AuxFunctionHeaders
	% Global variable to hold all the free function header definitions
	construct AuxFreeHeaders [repeat rule_definition]
	export AuxFreeHeaders
	% Copy of all the [construction_assignment_statement]s in the program
	construct DECS [repeat construction_assignment_statement]
		_ [^ P]
	% Global variable to hold all the DotID imported includes
	construct DTIDIncludes [repeat preprocessor]
	export DTIDIncludes
	by
		P	[createSequenceStructs]
			[createTypeDecisionStructs]
			[structsOnly DECS]
end function


% Step 1: Generate the structs for each sequence module definition and any
% required auxiliary headers required. Sequence modules translate one-to-one
% from the SCL5 into variables of the specified size and type
rule createSequenceStructs
	replace $ [type_rule_definition]
		LONG [id] '^ SHORT [id] ANN [opt annotation] '::= 'SEQUENCE OS [opt size_constraint] '{
			LE [list element_type] OC [opt ',]
		'} OP [opt scl_additions]
	construct body [repeat member_declaration]
		_ [createStructBody OP each LE]
	construct checkCallback [opt scl_additions]
		OP [checkForSequenceCallback LONG] [checkForAnnotatedCallback LONG]
	by
		'typedef 'struct {
			body
		} LONG ;
end rule

% Function to generate the body of a sequence struct. Each [element_type]
% is translated to the proper c variable type and appended to the struct body
function createStructBody OP [opt scl_additions] LE [element_type]
	replace [repeat member_declaration]
		MD [repeat member_declaration]
	by
		MD [addSizeBasedType LE]
			[addSizeBasedOptionalType LE]
			[addSetOfType OP LE]
			[addSetOfTypeAnnotatedCallback OP LE]
			[addInteger LE]
			[addReal4 LE]
			[addReal8 LE]
			[addDynamicOctetString LE]
			[addStaticOctetString LE]
			[addStaticOctetStringLarge LE]
end function

% Function to generate the variable for a [size_based_type] definition;
% This is a variable with a user defined type
function addSizeBasedType LE [element_type]
	deconstruct LE
		LONG [id] '^ SHORT [id] TYPE [id] '('SIZE 'DEFINED') OP [opt endian] OPSL [opt slack] POS [opt position_value]
	construct decl [member_declaration]
		TYPE SHORT[tolower]';
	replace [repeat member_declaration]
		MD [repeat member_declaration]
	by
		MD [. decl]	% Append variable to the body
end function

% Function to generate the variable for a [size_based_type] definition; 
% This is a variable with a user defined type declared as a pointer
function addSizeBasedOptionalType LE [element_type]
	deconstruct LE
		LONG [id] '^ SHORT [id] TYPE [id] '('SIZE 'DEFINED') OP [opt endian] OPSL [opt slack] 'OPTIONAL POS [opt position_value]
	construct decl [member_declaration]
		TYPE * SHORT[tolower]';	% Pointer variable
	replace [repeat member_declaration]
		MD [repeat member_declaration]
	by
		MD [. decl]	% Append variable to the body
end function

% Function to add a variable defined as a SET OF [type] with no annotated
% callback present; This represents an array of elements of [type]. It is
% stored as a pointer to be later allocated and extra integer variables
% are created to hold the length and count of array elements
function addSetOfType OP [opt scl_additions] LE [element_type]
	where not
		OP [checkForAnnotatedCallbackRemoval]	% Only run when no [callback_annotation]
												% is in the [scl_additions]
	deconstruct LE
		LONG [id] '^ SHORT [id] 'SET 'OF TYPE [id] '('SIZE 'CONSTRAINED') POS [opt position_value]
	construct decl [repeat member_declaration]
		'unsigned 'long SHORT[+ "length"][tolower]';
		'unsigned 'long SHORT[+ "Count"][tolower]';
		TYPE '* SHORT[tolower]';
	replace [repeat member_declaration]
		MD [repeat member_declaration]
	by
		MD [. decl] % Append variables to the body
end function

% Deep check to match a parent callback annotation
function checkForAnnotatedCallbackRemoval
	match * [callback_annotation]
		'@ TYPE [id]
end function

% Function to add a variable defined as a SET OF [type] with an annotated
% callback present; This represents an array of elements of [type] where a 
% callback will occur at the end of the parse of each of the possible type 
% decisions. Since the callbacks will be occuring, the array will not be 
% stored in a struct but instead locally in the parser. The count and 
% length variables are still necessary and used.
function addSetOfTypeAnnotatedCallback OP [opt scl_additions] LE [element_type]
	where
		OP [checkForAnnotatedCallbackRemoval]	% Only run when a [callback_annotation]
												% is present in the [scl_additions]
	deconstruct LE
		LONG [id] '^ SHORT [id] 'SET 'OF TYPE [id] '('SIZE 'CONSTRAINED') POS [opt position_value]
	construct decl [repeat member_declaration]
		'unsigned 'long SHORT[+ "length"][tolower]';
		'unsigned 'long SHORT[+ "Count"][tolower]';
		% The pointer element is omitted
	replace [repeat member_declaration]
		MD [repeat member_declaration]
	by
		MD [. decl]	% Append variables to the body
end function

% Function to generate the variable for an [integer_type] definition;
% This is a variable with a specified number of bits required. It is
% stored as a uint# where the # is calculated from the [element_type]
function addInteger LE [element_type]
	deconstruct LE
		LONG [id] '^ SHORT [id] 'INTEGER '( 'SIZE NUM [number] 'BYTES ') OP [opt endian] POS [opt position_value]	
	construct Eight [number]
		'8	% Eight is the base number and is multiplied 
			% by 1, 2, 4 or 8 for a maximum of uint64
	where
		NUM [<= 8]	% If the number of bytes is greater than 8 it
					% cannot be represented as a uint
	construct finalNum [number]
		NUM [checkgt4] [check3]	% Convert the specified number of bytes to
								% 1, 2, 4 or 8 to create a uint8, uint16, 
								% uint32 or uint64, rounded up (The actual
								% size may be bigger than what is required)
	construct NumBits [number]
		Eight [* finalNum]	% 8 * the rounded number gives the uint size
	construct IntType [id]
	   _ [+ 'uint] [+ NumBits] [+ '_t]
	construct decl [member_declaration]
		IntType SHORT[tolower]';
	replace [repeat member_declaration]
		MD [repeat member_declaration]
	by
		MD [. decl]	% Append variable to the body
end function

% Function to round up the number of bytes required from any number
% between 5 and 7 (inclusive) to 8. The data is too large for a
% uint32 and must be stored in a uint64
function checkgt4
	replace [number]
		NUM [number]
	where
		NUM [> 4]
	where 
		NUM [< 8]
	by
		8
end function

% Function to round up the number of bytes required from 3 to 4.
% The data is too large for a uint16 and must be stored in a uint32
function check3
	replace [number]
		NUM [number]
	where
		NUM [= 3]
	by
		4
end function

% Function to generate the variable for an [real_type] definition;
% This is a variable with a specified number of bits required in 
% floating point precision. It is stored as a float as only
% 4 bytes are required
function addReal4 LE [element_type]
	deconstruct LE
		LONG [id] '^ SHORT [id] 'REAL '( 'SIZE NUM [number] 'BYTES ') OP [opt endian]
	where
		NUM [= 4]	% 4 bytes equates to float predefined size
	construct type [id]
		_ [+ 'float]
	construct decl [member_declaration]
		type SHORT[tolower]';
	replace [repeat member_declaration]
		MD [repeat member_declaration]
	by
		MD [. decl]	% Append variable to the body
end function

% Function to generate the variable for an [real_type] definition;
% This is a variable with a specified number of bits required in 
% floating point precision. It is stored as a real as 8 bytes are required
function addReal8 LE [element_type]
	deconstruct LE
		LONG [id] '^ SHORT [id] 'REAL '( 'SIZE NUM [number] 'BYTES ') OP [opt endian]
	where
		NUM [= 8]	% 8 bytes equates to real predefined size
	construct type [id]
		_ [+ 'double]
	construct decl [member_declaration]
		type SHORT[tolower]';
	replace [repeat member_declaration]
		MD [repeat member_declaration]
	by
		MD [. decl]	% Append variable to the body
end function

% Function to generate the variable for a dynamic [octet_type] definition;
% This is a variable with a dynamic size, defined externally. It is represented
% as a character pointer which will be dynamically allocated during the parse.
% The length is stored in a variable for reference
function addDynamicOctetString LE [element_type]
	deconstruct LE
		LONG [id] '^ SHORT [id] 'OCTET 'STRING '( 'SIZE 'CONSTRAINED ') OP [opt endian] OPSL [opt slack] POS [opt position_value]
	construct decl [repeat member_declaration]
		unsigned 'long SHORT[+ "_length"][tolower]';	% Size of the pointer array
		'unsigned 'char '* SHORT[tolower]';	% Dyanmic pointer array
	replace [repeat member_declaration]
		MD [repeat member_declaration]
	by
		MD [. decl]	% Append variable to the body
end function

% Function to generate the variable for an [octet_type] definition;
% This is represented as a uint with a static size to hold all the info
% which is determined from the [element_type] definition
function addStaticOctetString LE [element_type]
	deconstruct LE
		LONG [id] '^ SHORT [id] 'OCTET 'STRING '( 'SIZE NUM [number] 'BYTES ') OP [opt endian] OPSL [opt slack] POS [opt position_value]
	where
		NUM [<= 8]	% If the number of bytes is greater than 8 it
					% cannot be represented as a uint
	construct Eight [number]
		'8 	% Eight is the base number and is multiplied 
			% by 1, 2, 4 or 8 for a maximum of uint64
	construct finalNum [number]
		NUM [checkgt4] [check3]	% Convert the specified number of bytes to
								% 1, 2, 4 or 8 to create a uint8, uint16, 
								% uint32 or uint64, rounded up (The actual
								% size may be bigger than what is required)
	construct NumBits [number]
		Eight [* finalNum]	% 8 * the rounded number gives the uint size
	construct IntType [id]
	   _ [+ 'uint] [+ NumBits] [+ '_t]
	construct decl [member_declaration]
		IntType SHORT[tolower]';
	replace [repeat member_declaration]
		MD [repeat member_declaration]
	by
		MD [. decl]	% Append variable to the body
end function

% Function to generate the variable for an [octet_type] definition;
% This is represented as a character array with a static size 
% that is determined from the [element_type] definition as the
% size is too large for a uint
function addStaticOctetStringLarge LE [element_type]
	deconstruct LE
		LONG [id] '^ SHORT [id] 'OCTET 'STRING '( 'SIZE NUM [number] 'BYTES ') OP [opt endian] OPSL [opt slack] POS [opt position_value]
	where
		NUM [> 8]	% If the size is greater than 8 bytes it is too
					% large to store in a uint and must be stored in
					% an array
	construct decl [member_declaration]
		'unsigned 'char SHORT[tolower]'[NUM'];
	replace [repeat member_declaration]
		MD [repeat member_declaration]
	by
		MD [. decl]	% Append variable to the body
end function

% Function to check if the sequence module has a non-annotated callback
% and generate the required callback function header definition
function checkForSequenceCallback LONG [id]
	replace [opt scl_additions]
		GR [opt encoding_grammar_indicator] 
		SZ [opt size_markers_block] 
		TR [opt transfer_rules_block]
    	CB [opt constraints_block] 
    deconstruct * [transfer_statement] TR
    	'Callback 	% Only run if the callback is not annotated
    construct callName [id]
    	_ [+ LONG] [+ "_callback"]
    construct header [rule_definition]
    	void callName '( LONG * LONG[tolower], PDU *thePDU ');
    import AuxFunctionHeaders [repeat rule_definition]
    export AuxFunctionHeaders
    	AuxFunctionHeaders [. header]	% Append the definition to the global
    by
    	GR SZ TR CB	% No replacement
end function

% Function to check if the sequence module has an annotated callback
% and generate the required callback and free function header definitions
function checkForAnnotatedCallback LONG [id]
	replace [opt scl_additions]
		GR [opt encoding_grammar_indicator] 
		SZ [opt size_markers_block] 
		TR [opt transfer_rules_block]
    	CB [opt constraints_block] 
    deconstruct * [transfer_statement] TR
    	'Callback PARENT [id] NAME [id]	% Only run if callback is annotated
    construct callName [id]
    	_ [+ LONG] [+ "_callback"]
    construct header [rule_definition]
    	void callName '( PARENT * PARENT[tolower], LONG * LONG[tolower], PDU *thePDU ');
    import AuxFunctionHeaders [repeat rule_definition]
    export AuxFunctionHeaders
    	AuxFunctionHeaders [. header]	% Append the definition to the global
    construct freeFunc [id]
		_ [+ "free"] [+ LONG]
    construct free [rule_definition]
		void freeFunc(LONG * LONG[tolower]);
    import AuxFreeHeaders [repeat rule_definition]
    export AuxFreeHeaders
    	AuxFreeHeaders [. free]	% Append the definition to the global
    by
    	GR SZ TR CB % No replacement
end function

% Step 2: Generate the structs for each type decision module definition 
% and any required auxiliary headers required. Type decision modules translate
% into a type variable c union data structure where the body is the SCL5 
% types in the decision
rule createTypeDecisionStructs
	replace $ [construction_assignment_statement]
		LONG [id] '^ SHORT [id] OPTANN [opt optimizable] '::= '( TR [type_reference] RTR [repeat alternative_decision] ') OPT [opt scl_additions]
	construct body [repeat member_declaration]
		_ [addTypeDecisionBody TR RTR] [addTypeDecisionBodyDotID TR RTR]
	construct checkCallback [opt scl_additions]
		OPT [checkForTDCallbacks TR RTR]
	by
		'typedef 'struct {
			'uint32_t 'type';	% Variable to hold the type of the item selected in the union
			'union '{
				body
			'} 'ptr;	% Union is represented by the name 'ptr'
		} LONG ;
end rule

% Function to start generating the body of the union structure where 
% there are no imported references in the initial [type_reference]
% The remaining [repeat alternative_decision] are generated in a
% seperate rule due to the grammar
function addTypeDecisionBody typeRef [type_reference] RaltDec [repeat alternative_decision]
	replace [repeat member_declaration]
		MD [repeat member_declaration]
	deconstruct typeRef
		ID [id] OPTANN [opt annotation]
	construct decl [member_declaration]
		ID ID[tolower];
	by
		MD [. decl] [addAltDecision each RaltDec] [addAltDecisionDotID each RaltDec]
		% Append the [type_reference] value and result from the next function to the body
end function

% Function to deconstruct each [alternative_decision] and generate its
% corresponding union body element and append it to the existing set.
% This function only runs when the [alternative_decision] contains no
% imported references (No DotIDs)
function addAltDecision altDec [alternative_decision]
	replace [repeat member_declaration]
		MD [repeat member_declaration]
	deconstruct altDec
		'| ID [id] OPTANN [opt annotation]	% No DotID
	construct decl [member_declaration]
		ID ID[tolower];
	by
		MD [. decl]	% Append the declaration
end function

% Function to deconstruct each [alternative_decision] and generate its
% corresponding union body element and append it to the existing set.
% This function only runs when the [alternative_decision] contains an
% imported reference (DotID)
function addAltDecisionDotID altDec [alternative_decision]
	replace [repeat member_declaration]
		MD [repeat member_declaration]
	deconstruct altDec
		'| ID [id] OP [opt dotID] OPTANN [opt annotation]
	deconstruct OP
		'. ID2 [id]
	construct INCLUDE [stringlit]
		_ [+ "#include \""] [+ ID] [+ "_Generated.h\""]
	construct INCLUDEPRE [opt preprocessor]
		_ [parse INCLUDE]
	deconstruct INCLUDEPRE
		INCLUDEFINAL [preprocessor]
	import DTIDIncludes [repeat preprocessor]
	export DTIDIncludes
		DTIDIncludes [. INCLUDEFINAL]	% Append to the global includes
	construct decl [member_declaration]
		ID2 ID2[tolower];
	by
		MD [. decl]	% Append the declaration
end function

% Function to start generating the body of the union structure where 
% there are imported references in the initial [type_reference]
% The remaining [repeat alternative_decision] are generated in a
% seperate rule due to the grammar
function addTypeDecisionBodyDotID typeRef [type_reference] RaltDec [repeat alternative_decision]
	replace [repeat member_declaration]
		MD [repeat member_declaration]
	deconstruct typeRef
		ID [id] OP [opt dotID] OPTANN [opt annotation]
	deconstruct OP
		'. ID2 [id]
	construct INCLUDE [stringlit]
		_ [+ "#include \""] [+ ID] [+ "_Generated.h\""]
	construct INCLUDEPRE [opt preprocessor]
		_ [parse INCLUDE]
	deconstruct INCLUDEPRE
		INCLUDEFINAL [preprocessor]
	import DTIDIncludes [repeat preprocessor]
	export DTIDIncludes
		DTIDIncludes [. INCLUDEFINAL]	% Append to the global includes
	construct decl [member_declaration]
		ID2 ID2[tolower];
	by
		MD [. decl] [addAltDecision each RaltDec] [addAltDecisionDotID each RaltDec]
		% Append the [type_reference] value and result from the next function to the body
end function

% Function to check for a non-annotated callback in a type decision 
% module definition. If one is found, a callback function is generated
% for each type in the decision
function checkForTDCallbacks TPR [type_reference] RTR [repeat alternative_decision]
	replace [opt scl_additions]
		GR [opt encoding_grammar_indicator] 
		SZ [opt size_markers_block] 
		TR [opt transfer_rules_block]
    	CB [opt constraints_block] 
    deconstruct * [transfer_statement] TR
    	'Callback 	% No annotation
    deconstruct TPR	% Create callback for [type_reference]
    	LONG [id] OPT [opt dotID] OPTANN [opt annotation]
   construct callName [id]
    	_ [+ LONG] [+ "_callback"] 	
    construct header [rule_definition]
    	void callName '( LONG * LONG[tolower], PDU *thePDU ');
    construct restHeaders [repeat rule_definition]
    	_ [constructFunctionHeaders each RTR]	% Create callbacks for
    											% each RTR element
    import AuxFunctionHeaders [repeat rule_definition]
    export AuxFunctionHeaders
    	AuxFunctionHeaders [. header] [. restHeaders]
    	% Append the callback definitions to the global set
    by
    	GR SZ TR CB	% No replacement
end function

% Function to generate a callback function header for an element
% of a [repeat alternative_decision]
function constructFunctionHeaders TR [alternative_decision]
	replace [repeat rule_definition]
		RL [repeat rule_definition]
	deconstruct TR
		'| LONG [id] OPT [opt dotID] OPTANN [opt annotation]
   construct callName [id]
    	_ [+ LONG] [+ "_callback"] 			
	construct header [rule_definition]
    	void callName '( LONG * LONG[tolower], PDU *thePDU ');
	by
		RL [. header]	% Append the function header definition
end function


% Step 3: Do the final assembly of the header file. All includes,
% defines and auxiliary definitions must be added to the generated
% structs in the proper order
function structsOnly DECS [repeat construction_assignment_statement]
	replace [program]	% Replace entire program to reorder the output
		ID [id] 'DEFINITIONS TAG [opt tag_default] ::= 'BEGIN
		EX [opt export_block]
		IM [opt import_block]
		BODY [repeat rule_definition]	% Sequence of generated structs
		'END
	import AuxFunctionHeaders [repeat rule_definition]	% Load all defined function headers
	import AuxFreeHeaders [repeat rule_definition]	% Load all defined free function headers
	construct IFNDEF [stringlit]
		_ [+ "#ifndef "] [+ ID] [+ "_H"]	% Generate an IFNDEF for the protocol
	construct IFNDEFPRE [opt preprocessor]
		_ [parse IFNDEF]
	deconstruct IFNDEFPRE
		IFNDEFFINAL [preprocessor]
	construct DEFINE [stringlit]
		_ [+ "#define "] [+ ID] [+ "_H"]
	construct DEFINEPRE [opt preprocessor]
		_ [parse DEFINE]
	deconstruct DEFINEPRE
		DEFINEFINAL [preprocessor]
	import DTIDIncludes [repeat preprocessor]
	construct INCLUDES [repeat preprocessor]	% Standard includes required for all parsers
		IFNDEFFINAL
		DEFINEFINAL
		'#include <stdio.h>
		'#include <stdint.h>
		'#include <stdlib.h>
		'#include <string.h>
		'#include <inttypes.h>
		'#include "packet.h"
		'#include "globals.h"
	construct currentVal [number]
		0
	export currentVal	% Global counter for sequential numbering
	construct structs [repeat struct_or_union_specifier]
		_ [^ BODY]	% Pull all generated structs from the program body
	construct AuxDefines [repeat id]
		_ [genIDS each structs]	% Get the [id] of all union struct members
	construct finalDefines [repeat preprocessor]
		_ [genDefines each AuxDefines]	% Generate value defines for 
										% each union struct member
	construct mainParse [id]
		_ [+ "parse"] [+ ID]
	construct mainDS [id]
		_ [+ "PDU_"] [+ ID]
	construct freeFunc [id]
		_ [+ "freePDU_"] [+ ID]
	construct mainParseFunction [rule_definition]
		bool mainParse(mainDS * mainDS[tolower], PDU * thePDU, char * name, uint8_t endianness);  
		% Function header definition to parse a packet of the protocol type
	construct mainFreeFunction [rule_definition]
		void freeFunc(mainDS * 'mainpdu);
		% Function header definition to free a packet of the protocol type
	construct FULLBODY [repeat rule_definition]
	by
		INCLUDES [. DTIDIncludes]	% All predefined includes and globally generated includes (From Import / DotIDs)
		finalDefines				% All the value definitions for elements of union structs
		FULLBODY [. BODY]			% All the previously generated structs from the SCL5 specification
			[. AuxFunctionHeaders]	% Any globally defined function header definitions
			[. mainParseFunction]	% The function header definition to parse the protocol packet
			[. mainFreeFunction]	% The function header definition to free the protocol packet
			[. AuxFreeHeaders]		% Any globally defined free header definitions
		'#endif
end function

% Function to generate a set of [id] values for the elements
% of the type decision union structs
function genIDS fullStruct [struct_or_union_specifier]
	replace [repeat id]
		IDS [repeat id]
	deconstruct fullStruct	% Must be a type decision union struct
		'struct {
			'uint32_t 'type;
			'union body [struct_or_union_body] 'ptr;
		}
	construct bodyIDS [repeat member_declaration]
		_ [^ body]	% Pull all declarations from the struct's body
	construct bodyNames [repeat id]
		_ [getEachID each bodyIDS] % Get the type [id] from each declaration
	construct newIDS [repeat id]
		_ [checkBody IDS each bodyNames]	% Check for unique definitions
	by
		IDS [. newIDS]	% Append the unique [id] declarations
end function

% Function to discover and save the type [id] from a [member_declaration]
function getEachID bodyName [member_declaration]
	replace [repeat id]
		IDS [repeat id]
	deconstruct bodyName
		ID1 [id] ID2[id] ;
	by
		IDS [. ID1] % Append the discovered [id]
end function

% Function to ensure that each discovered [id] is only declared in
% the set one time. If it is already declared it not appended
function checkBody IDLIST [repeat id] bodyName [id]
	replace [repeat id]
		IDS [repeat id]
	deconstruct not * [id] IDLIST	% If found the [id] is already declared
		bodyName
	by
		IDS [. bodyName]	% Append the [id] as it is not yet declared
end function

% Function to generate value defines for each member of union structs;
% The member [id] is passed in through the parameter and the define is
% appended in the replacement. Each member of a union struct needs a 
% unique value to be used in the struct's type variable so it is known
% what is stored in the union after parse
function genDefines ID [id]
	replace [repeat preprocessor]
		DEFINES [repeat preprocessor]
	import currentVal [number]	% Load the global sequence number
	construct nextVal [number]
		currentVal [+ 1]	% Increment the global sequence by one
	export currentVal
		nextVal	% Update the global sequence number
	construct IDVAL [id]
		ID [+ "_VAL"]
	construct DEFINE [stringlit]
		_ [+ "#define "] [+ IDVAL] [+ " ("] [+ nextVal] [+ ")"]
	construct DEFINEPRE [opt preprocessor]
		_ [parse DEFINE]
	deconstruct DEFINEPRE
		DEFINEFINAL [preprocessor]
	by
		DEFINES [. DEFINEFINAL]	% Append the define
end function