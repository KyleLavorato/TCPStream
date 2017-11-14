% Generate Header
% Ali El-Shakankiry
% Queen's University, Jan 2017

% Copyright 2017 Thomas Dean

% Revision history:

% 1.2 Documentation			- KPL	28 06 2017
% 1.1 Callback annotation 	- KPL	14 06 2017
% 1.0 Initial revision 		- AES 	01 01 2017 

% This program walks through a SCL5 file and generates a C source file for
% a parser for the specified protocol.

% The input to the program is a SCL5 file named "protocol"_UID_annotated.scl5.
% The input file has been annotated by the previous TXL scripts, marking it for
% various optimizations and ensuring unique naming.

% The output of this program is a header file named "protocol"_Generated.c. 
% The output file is a full parser for the specified protocol and holds all
% the constraints placed on the data in the SCL5 decsription.


% Base grammars

include "../GRM/ASNOne.Grm"
include "../GRM/c.grm"

% Local grammar overrides

define charlit_or_id
    [charlit] | [id]
end define

define optimizable
	'@'optimizable
end define

define global
	'@ 'GLOBAL
end define

define at
	'@
end define

% Annotations are added to rule names as a pair of numbers
% The first number represents the size of the kind element
% The second number represents the value that the kind element
% is constrained to possess

% To be optimizable the first numbers must match for a type
% decision and the second numbers must all be unique

% An annotation can also include the @ optimizable or
% @ global tags to indicate that the rule annotated with
% those is in fact optimizable by that optimization type
% during code generation

define annotation
	[opt at] [opt number] [opt number] [opt global] [opt optimizable] 
end define

define dot_rp
	'. [referenced_element]
end define

define position_value
  'POS
end define

define HexPair
   [charlit] [charlit]
end define

define derefID
	[SPOFF]'->[id][SPON]
	| [SPOFF]'.[id][SPON]
end define

% Annotations are added to each type reference element of
% a type decision
redefine type_reference
	[id] [opt dotID] [opt annotation]
end redefine

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

% Language transformarions between SCL5 and C

% Annotations are added to the rule that defines each type
% of a type decision
redefine type_rule_definition
	% scl5
	[decl] [opt annotation] '::= [type] [opt scl_additions]
	% C
	| [repeat function_definition_or_declaration]
end redefine

redefine construction_assignment_statement
	% scl5
	[decl] [opt optimizable] '::= [type_decision] [opt scl_additions]				[NL]
	% C
	| [repeat function_definition_or_declaration]
end redefine

redefine program
	...
	| [repeat preprocessor]
		[repeat rule_definition]
		[opt preprocessor]
end redefine

redefine constant
	...
	| [constant] [repeat derefID]'[[id]']
	| [constant] [repeat derefID]
	| [relational_expression]
	| 'NULL
end redefine

redefine size_of_expn
	...
	| 'sizeof '( [referenced_element] ')
end redefine

redefine referencable_primaries
	...
	| [SPOFF][id][repeat derefID][SPON]
end redefine

redefine alternative_decision
	...
	| [repeat alternative_decision]
end redefine

redefine label
	...
	| [EX][SP][SP] 'case [constant_cexpression] ': [IN] [NL] [unlabeled_statement]
end redefine

redefine pos_expression
	...
	| [referenced_element]
end redefine

% Main rule followed by other rules in topological order

% The main idealology of the translation is to do a one-to-one translation
% of a SCL5 description of a rule to C code to parse that rule description.
% Extra functions and code will be generated where necessary, but the main
% transformation is changing one SCL5 rule to a C function

function main
	replace [program]
		P [program]
	
	deconstruct P
		ID [id] 'DEFINITIONS TAG [opt tag_default] ::= 'BEGIN
		OPT [opt module_body]
		'END

	%% GLOBAL VARIABLES %%

	% Logic false value for checking the "-nocallback" program argument
	construct num [number]
		'0
	construct noCallbackArg [number]
		num [checkTXLargs]	% Check the arguments for "-nocallback" and update to true if it is found
	export noCallbackArg 	% Global logic value for the program argument; If set to true then no
							% callbacks are to be generated in the code
	
	% Global variable to hold all the function definition headers that
	% will be added to the top of the program at script end; These
	% must be generated because some functions will be generated in 
	% AuxFunctions and therefore generated below where they are called
	% from, requiring the function header definitions. 
	construct FunctionDeclarations [repeat rule_definition]
	export FunctionDeclarations
	
	% Global variable to hold any function definitions that cannot be
	% generated in a replace and/or are supporting functions that are
	% no derrived straight from a rule. These functions will often be
	% generated as a byproduct of another parse rule to supoprt it and
	% since the main parse rule is the replacement then these functions
	% must be saved in this global (Eg. parseSetOfID functions)
	construct AuxFunctions [repeat rule_definition]
	export AuxFunctions
	
	% Global variable used as a device to test the length of information.
	% When zero the variable is treated as inactive
	construct lengthToCheck [number]
		'0
	export lengthToCheck
	
	% Global variable of the name of the free function for the entire module.
	% Must be saved here until the free function is generated because the
	% module name will be unavailable later
	construct freeName [id]
		_ [+ "free"] [+ "PDU_"] [+ ID]
	export freeName

	%% MAIN PROGRAM %%

	construct TPRULES [repeat type_rule_definition]
		_ [^ P]	% Extract a copy of all the standard type rules in the program
	construct TPDECS [repeat construction_assignment_statement]
		_ [^ P]	% Extract a copy of all the type decision rules in the program
	construct ALLRULES [repeat rule_definition]
		_ [^ P]	% Extract a copy of all the rules in the program
	export ALLRULES
	
	% Note: The first PDU statement to parse may also be a construction_assignment_statement
	% i.e. igmpv2.scl5

	by
		P [checkGlobalConstraints]
			[createFreeFunctionTypeRule ALLRULES]
			[createFreeFunctionTypeDecision ALLRULES]
			[createParseFunctions ID TPRULES TPDECS] % add type decisions list here 
			[addAuxiliaryData]
end function

% Function used to check if the TXL script
% was run with the arugment "-nocallback";
function checkTXLargs 
	import TXLargs [repeat stringlit]	% Import the predefined TXL argument value to check its contents
	deconstruct * [stringlit] TXLargs
		"-nocallback"
	% If "-nocallback" is found in the TXLargs then update the value to a logical true
	replace [number]
		num [number]
	by
		'1 	% Locgic true
end function


% Step 1: Check all the global constraints in any rule definitions
% and save them in a global variable for later user in the TXL script
rule checkGlobalConstraints
	match [program]
		P [program]
	% Global variable to hold any of the global expressions of rules with
	% global constraints
	construct globalConstraints [repeat rule_definition]
	export globalConstraints
	construct checkAllGlobals [program]
		P [checkTypeRules] [checkConstructionAssignments]
end rule

% Step 1.1: Check the [scl_additions] of all type rules to see
% if they contain any global back constraints
rule checkTypeRules
	match $ [type_rule_definition]
		DECL [decl] OPANN [opt annotation] '::= TP [type] SCLADD [opt scl_additions]
	construct checkAdditions [opt scl_additions]
		SCLADD [checkGlobalAdditions]
end rule

% TODO: Only checking for equality and left hand side global + assuming NUM is a number
% because we check for a value in generateOptimizations. Globals will override any optimizable 
% back constraints.

% Check if the [scl_additions] of a rule contains a global
% constraint [transfer_statement]. If it does then construct
% a global expression stating it is external and save it to
% globalConstraints for later use
rule checkGlobalAdditions
	match $ [transfer_statement]
		'Back '{ 'GLOBAL '( RE [referenced_element] ') '== NUM [number] '} 
	deconstruct RE
		ID [id]
	construct globalExpression [repeat rule_definition]
		'extern 'int ID ';
	import globalConstraints [repeat rule_definition]
	export globalConstraints
		globalConstraints [. globalExpression]	% Save the expression for later use
end rule

% Stpe 1.2: Check the [scl_additions] of all type decision rules
% to see if they contain global back constraintss
rule checkConstructionAssignments
	match $ [construction_assignment_statement]
		DECL [decl] OPOP [opt optimizable] '::= TD [type_decision] SCLADD [opt scl_additions]
	construct checkAdditions [opt scl_additions]
		SCLADD [checkGlobalAdditions]
end rule


%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%  For Steps 2 & 3 | See the free function section of the script  %%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%


%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%  Parse [rule_definition] section  %%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

% Step 4: Generate the main parse function for the protocol.
% Parse functions are a one-to-one translation from one SCL5
% rule for a type to a C function to parse that type. Auxiliary
% functions may also be created as support for the main parse
% functions. This rule will translate the entirity of the SCL5
% description into C functions. Always begin parsing from PDU.
rule createParseFunctions ModName [id] TPRULES [repeat type_rule_definition] TPDECS [repeat construction_assignment_statement] % add list of typ decisions	
	replace $ [rule_definition]
		A [rule_definition]
	by
		% There is one rule to deal with the translation of each
		% type of SCL5 description of a type; With and without optimizations
		A 	[doSimpleTypeRule ModName TPRULES TPDECS]
			[doChoiceOptimizedTypeRule ModName TPRULES TPDECS]
			[doSimpleTypeDecision ModName TPRULES TPDECS]
			[doAnnotatedTypeDecision ModName TPRULES TPDECS]
			[doOptimizedTypeDecision ModName TPRULES TPDECS]
			[doGloballyOptimizedTypeDecision ModName TPRULES TPDECS]
end rule


% Note: The naming convention will be standard for all parse
% functions. It will be parse"NAME" where name is the short
% non-unique [id] from the SCL5. Also the parameters for the parse
% fuinction will be standard as well. It will contain the struct
% of the thing being parsed, the PDU data type, a char array for
% the progname, and a uint8 for the endianness. There are also
% optimized versions for some those that are marked as optimizable
% which include an extra type parameter before the endianness
% parameter. The type parameter will be a uint of whatever size is
% specified in the optimization annotation

% Step 4.1: Generate the parse function for a standard type
% rule of the SEQUENCE definition.
rule doSimpleTypeRule ModName [id] TPRULES [repeat type_rule_definition] TPDECS [repeat construction_assignment_statement]
	replace $ [type_rule_definition]
		TypeRule [type_rule_definition]
	deconstruct TypeRule
		LONG [id] '^ SHORT [id] ANN [opt annotation]'::= 'SEQUENCE '{
			LE [list element_type] OC [opt ',]
		'} OP [opt scl_additions]
	import FunctionDeclarations [repeat rule_definition]
	construct funcName [id]
		_ [+ "parse"] [+ SHORT]	% Parse function name
	construct pName [id]
		funcName [checkPDUFName SHORT LONG]	% Check if the parse name is for the PDU type
											% and rename if it is
	construct MNPDU [id]
		_ [+ "PDU_"] [+ ModName]	% Name of the pdu for the module
	% Parse function header definition
	construct pModDecl [rule_definition]
		bool pName (LONG * LONG[tolower], PDU * thePDU, char * 'progname, uint8_t endianness);
	export FunctionDeclarations
		FunctionDeclarations [. pModDecl]	% Save the function header definition
	construct ALLOCNAME [id]
		mainpdu
	construct lower [id]
		LONG[tolower]
	construct mainFunctionBody [repeat declaration_or_statement]
	import lengthToCheck [number]
	export lengthToCheck
		lengthToCheck [zeroLength]	% Reset and save the lengthToCheck value
	% Create a set of statements to initialize all the pointers in the
	% struct to NULL initially for code safety
	construct initializePointers [repeat declaration_or_statement]
		_ [initializePointer lower LONG LE OP each LE]
	% Generate the C code to parse each of the [element_type]'s of the rule
	construct parseBySizes [repeat declaration_or_statement]
		_ [parseBySize lower LONG OP LE each LE ]
	% NOTE: Need to get actual size from annotated scl5 file
	% Generate checks for any global constraints on the rule
	construct globalCheck [repeat declaration_or_statement]
		_ [addGlobalCheck OP]
	% Load the running total size of the rule and generate the length check C code
	import lengthToCheck 
	construct lengthCheck [repeat declaration_or_statement]
		_ [lengthCheck ALLOCNAME lengthToCheck]
	% Generate the C code for a standard callback if present
	construct callback [repeat declaration_or_statement]
		_ [genCallback OP LONG LONG] 
	% Generate successful end of parse
	construct return [repeat declaration_or_statement]
		return true;
	% Generate the optimized version of trhe rule too if it can be optimized
	construct optimizedTypeRule [type_rule_definition]
		TypeRule [doChoiceOptimizedTypeRule ModName TPRULES TPDECS]
	% Extract the statemements from the above generated rule
	construct optimizedTypeRuleDef [repeat function_definition_or_declaration]
		_ [^ optimizedTypeRule]
	by
		bool pName (LONG * LONG[tolower] , PDU * thePDU, char * 'progname, uint8_t endianness) {
			mainFunctionBody [. globalCheck] [. lengthCheck] [. initializePointers] [. parseBySizes] [. callback] [. return]
		}
		optimizedTypeRuleDef	% Add the optimized version of the rule directly below the non-optimized
end rule

% Function to check if the parse function name is for
% parsing the PDU. If it is, it will be changed to instead
% be named to parse the protocol. Ex for RTPS the inital [id]
% would be PDU_RTPS ^ PDU with name parsePDU_RTPS. The desired
% name is parseRTPS; LONG is altered to just contain the RTPS portion
function checkPDUFName SHORT [id] LONG [id]
	replace [id]
		fName [id]
	% Only run if the SHORT is of PDU type
	deconstruct SHORT
		'PDU
	construct index [number]
		_ [index LONG "_"]	% Find the "_" character location
	construct startIndex [number]
		index [+ 1]	% The location one character after the "_"
	construct length [number]
		_ [# LONG]	% The length of the [id]
	construct finalID [id]
		LONG [: startIndex length]	% Get the characters after the "_" to the end
	construct finalName [id]
		_ [+ "parse"] [+ finalID]	% The parse function name
	by
		finalName
end function

% Function to replace a number value with a zero
% to essentially reset it
function zeroLength
	replace [number]
		length [number]
	by
		'0
end function

% Function to check for a Global constraint on the rule
% and if there is one generate the C code check for it
function addGlobalCheck OPSCL [opt scl_additions]
	% Must have a global back constraint; Must be a back
	% constraint as the parse of [list element_type] is done
	deconstruct * [transfer_statement] OPSCL
		'Back '{ 'GLOBAL '( ID [id] ') '== REST [relational_expression] '}
	replace [repeat declaration_or_statement]
		Stmts [repeat declaration_or_statement]
	% Generate the code according to the constraint to verify
	% the requirements
	construct globalCheck [repeat declaration_or_statement]
		if(ID != REST) {
			return false;
		}
	by
		Stmts [. globalCheck]
end function

% Function to generate the length check C code to ensure
% that the information taken from the PDU is the right size
function lengthCheck NAME [id] size [number]
	replace [repeat declaration_or_statement]
		I [repeat declaration_or_statement]
	% Size is a running total of the complete size of everything parsed
	deconstruct size
		finalSize [number]
	by
		if(!lengthRemaining(thePDU, finalSize, 'progname)) {
			return false;
		}
end function

% Function to generate a standard callback statement if a
% non-annotated callback [transfer_statement] is present
function genCallback OP [opt scl_additions] LONG [id] toPass [id]
	import noCallbackArg [number]	% Load the no callback argument of the TXL script
	% The arguement must not be set (0) for callbacks to be generated
	deconstruct not noCallbackArg
		'1
	replace [repeat declaration_or_statement]
		Stmts [repeat declaration_or_statement]
	deconstruct OP
		GR [opt encoding_grammar_indicator] 
		SZ [opt size_markers_block] 
		TR [opt transfer_rules_block]
		CB [opt constraints_block] 
	% Must have a callback statement
	deconstruct * [transfer_statement] TR
		'Callback
	% Follow standard naming for the callback
	construct callName [id]
		_ [+ LONG] [+ "_callback"]
	% The C code to call the callback function
	construct callback [declaration_or_statement]
		callName(toPass[tolower], thePDU);
	by
		Stmts [. callback]	% Append the callback code
end function

% Step 4.2: Generate the parse function for a type
% rule of the SEQUENCE definition that has been optimized
% (Has annotations)
function doChoiceOptimizedTypeRule ModName [id] TPRULES [repeat type_rule_definition] TPDECS [repeat construction_assignment_statement]
	replace [type_rule_definition]
		LONG [id] '^ SHORT [id] '@ size [number] value [number] OPGLOB [opt global] '@ 'optimizable '::= 'SEQUENCE '{
			LE [list element_type] OC [opt ',]
		'} OP [opt scl_additions]
	% The annotation must indicate that the total size of the rule is not 0
	deconstruct not size
		'0
	import FunctionDeclarations [repeat rule_definition]
	construct funcName [id]
		_ [+ "parse"] [+ SHORT]	% Parse function name
	construct pName [id]
		funcName [checkPDUFName SHORT LONG]	% Check if the parse name is for the PDU type
											% and rename if it is
	construct MNPDU [id]
		_ [+ "PDU_"] [+ ModName]	% Name of the pdu for the module
	construct getSize [number]
		size [getBits]	% Get the total size in bits from "size" which is in bytes
	% The size of the uint based on the size in bits
	construct typeSize [id]
		_ [+ "uint"] [+ getSize] [+ "_t"]
	% Parse function header definition; Has the "_O" to indicate it is optimized parse
	construct pModDecl [rule_definition] 
		bool pName [+ "_O"] (LONG * LONG[tolower], PDU * thePDU, char * 'progname, typeSize * 'type, uint8_t endianness);
	export FunctionDeclarations
		FunctionDeclarations [. pModDecl]	% Save the function header definition
	construct ALLOCNAME [id]
		mainpdu
	construct lower [id]
		LONG[tolower]
	construct mainFunctionBody [repeat declaration_or_statement]
	import lengthToCheck [number]
	export lengthToCheck
		lengthToCheck [zeroLength]	% Reset and save the lengthToCheck value
	% Create a set of statements to initialize all the pointers in the
	% struct to NULL initially for code safety
	construct initializePointers [repeat declaration_or_statement]
		_ [initializePointer lower LONG LE OP each LE]
	% Break the list into first element and rest
	deconstruct LE
		ET [element_type] ', REST [list element_type]
	% Generate checks for any global constraints on the rule
	construct globalCheck [repeat declaration_or_statement]
		_ [addGlobalCheck OP]
	% Generate the C code for the first [element_type]; Due to the
	% optimization, we already have parsed it in the type decision
	% and just need to save a value from parameters
	construct addParsedType [repeat declaration_or_statement]
		_ [addType lower LONG ET]
	% Generate the C code to parse each of the [element_type]'s
	% of the rule, but not the first one
	construct parseBySizes [repeat declaration_or_statement]
		_ [parseBySize lower LONG OP REST each REST ]
	% NOTE: Need to get actual size from annotated scl5 file
	% Load the running total size of the rule and generate the length check C code
	import lengthToCheck 
	construct lengthCheck [repeat declaration_or_statement]
		_ [lengthCheck ALLOCNAME lengthToCheck]
	% Generate the C code for a standard callback if present
	construct callback [repeat declaration_or_statement]
		_ [genCallback OP LONG LONG] 
	% Generate successful end of parse
	construct return [repeat declaration_or_statement]
		return true;
	by
		% Extra parameter of the type as it is parsed in the type decision as part of the optimization but not saved there
		bool pName [+ "_O"] (LONG * LONG[tolower] , PDU * thePDU, char * 'progname, typeSize * 'type, uint8_t endianness) {
			mainFunctionBody [. globalCheck] [. addParsedType] [. lengthCheck] [. initializePointers] [. parseBySizes] [. callback] [. return]
		}
end function

% Function to generate the C code to parse an [element_type]
% based on it's type, when it's size and value is already
% known due to the parse optimization
function addType mallocName [id] RuleName [id] ET [element_type] 
	replace [repeat declaration_or_statement]
		Stmts [repeat declaration_or_statement]
	by
	   Stmts [parseIntegerTypebySizeKnown mallocName RuleName ET]
			 [parseOctetStringTypebySizeKnown mallocName RuleName ET]
end function

% Function to parse an Integer with known size. The parse is simply
% saving the value into the correct struct member as it is actually
% parsed in the type decision. The value is passed in the parameter
% "type" (uint of correct size) as a pointer so it must be dereferenced
function parseIntegerTypebySizeKnown mallocName [id] RuleName [id] ET [element_type]
	% Must be integer type
	deconstruct ET
		LONG [id] '^ SHORT [id] 'INTEGER '(SIZE SZ [number] 'BYTES) OP [opt endian] POS [opt position_value]
	% Save the value of type into the correct struct member
	construct Stmt [declaration_or_statement]
		RuleName[tolower] '->SHORT[tolower] = *'type;
	replace [repeat declaration_or_statement]
		Stmts [repeat declaration_or_statement]
	by
		Stmts [. Stmt]
end function

% Function to parse an Octet String with known size. The parse is simply
% saving the value into the correct struct member as it is actually
% parsed in the type decision. The value is passed in the parameter
% "type" (uint of correct size) as a pointer so it must be dereferenced
function parseOctetStringTypebySizeKnown mallocName [id] RuleName [id] ET [element_type]
	% Must be octet string type
	deconstruct ET
		LONG [id] '^ SHORT [id] 'OCTET 'STRING '(SIZE SZ [number] 'BYTES)  OP [opt endian] OPSL [opt slack] POS [opt position_value]
	% Save the value of type into the correct struct member
	construct Stmt [declaration_or_statement]
		RuleName[tolower] '->SHORT[tolower] = *'type;
	replace [repeat declaration_or_statement]
		Stmts [repeat declaration_or_statement]
	by
		Stmts [. Stmt]
end function

% Step 4.3: Generate the parse function for a standard type
% decision rule with no optimizations (Parse or callback)
rule doSimpleTypeDecision ModName [id] TPRULES [repeat type_rule_definition] TPDECS [repeat construction_assignment_statement] 
	% Must have no annotations in the [construction_assignment_statement]
	replace $ [construction_assignment_statement]
		LONG [id] '^ SHORT [id] '::= TD [type_decision] OPT [opt scl_additions]
	% Must not have an annotated callback
	deconstruct not * [transfer_statement] OPT
		'Callback '^ PARENT [id] MallocType [id]
	construct funcName [id]
		_ [+ "parse"] [+ SHORT]	% Parse function name
	construct pName [id]
		funcName [checkPDUFName SHORT LONG]	% Check if the parse name is for the PDU type
											% and rename if it is
	construct MNPDU [id]
		_ [+ "PDU_"] [+ ModName]	% Name of the pdu for the module
	construct ALLOCNAME [id]
		mainpdu
	import FunctionDeclarations [repeat rule_definition]
	% Parse function header definition
	construct pModDecl [rule_definition]
		bool pName (LONG * LONG[tolower], PDU * thePDU, char * 'progname, uint8_t endianness);
	export FunctionDeclarations
		FunctionDeclarations [. pModDecl]	% Save the function header definition
	construct mainFunctionBody [repeat declaration_or_statement]
	construct parseByDecisions [repeat declaration_or_statement]
		_ [parseByDecision ALLOCNAME ModName TD LONG OPT]
	% Generate successful end of parse
	construct return [declaration_or_statement]
		return false;
	by
		bool pName (LONG *  LONG[tolower], PDU * thePDU, char * 'progname, uint8_t endianness) {
			mainFunctionBody [. parseByDecisions] [. return]
		}
end rule

% Function to generate the C code for the first [type_reference]
% in a type decision rule; Will leave the generation of the code
% for the subsequent [alternative_decision] to the next function
function parseByDecision mallocName [id] RuleName [id] TD [type_decision] LONG [id] OP [opt scl_additions]
	replace [repeat declaration_or_statement]
		Stmts [repeat declaration_or_statement]
	deconstruct TD 
		'( TR [type_reference] RTR [repeat alternative_decision] ')
	% Extract the ID from the [type_reference]
	deconstruct TR
		ID [id] DTID [opt dotID] ANN [opt annotation]
	construct typeToPass [id]
		ID [checkDTID DTID]	% Resolve the DotID if one exists
	construct index [number]
		_ [index ID "_"]	% Find the "_" character location
	construct finalIndex [number]
		index [- 1]	% The location one character before the "_"
	construct typeToParse [id]
		ID [: 1 finalIndex]	% Get the characters before the "_"
	% The name of the parse function
	construct pName [id]
		_ [+ "parse"] [+ typeToParse]
	% The name of the constant value for the type
	construct IDVAL [id]
		typeToPass [+ "_VAL"]
	% Code to save the val (kind) for the first type
	construct body [repeat declaration_or_statement]
		LONG[tolower]'->'type = IDVAL;
	construct lowerLong [id]
		LONG[tolower]
	construct lowerTypeToPass [id]
		typeToPass[tolower]
	% Code to pass the result in a callback
	construct IDTOPASS [id]
		_ [+ "&"] [+ lowerLong] [+ "->ptr."] [+ lowerTypeToPass]		
	% Generate a callback if required
	construct callback [repeat declaration_or_statement]
		_ [genCallback OP ID IDTOPASS] 
	% Successful end of parse
	construct return [declaration_or_statement]
		return true;
	% Full C code for the naieve parse for the first decision. The naieve
	% parse will attempt to parse each message type until it finds success
	% in parsing a type
	construct firstDecision [repeat declaration_or_statement]
		unsigned 'long pos = thePDU ->curPos;
		unsigned 'long remaining = thePDU ->remaining;
		if( pName ('& LONG[tolower]->ptr'. typeToPass[tolower], thePDU, 'progname, endianness)) {
			body [. callback] [. return]
		} 
	construct typeRefs [repeat type_reference]
		_ [^ RTR]	% Extract all the [type_reference]'s from the [alternative_decision]'s
	by
		Stmts [. firstDecision]	% Append the first decision code
			 [parseSimpleTypeDecision mallocName LONG OP each typeRefs]	% Generate the code for the rest of the decisions
end function

% Function to resolve a dotID to the actual member
% Eg Moudle.Type to Type
function checkDTID DTID [opt dotID]
	replace [id]
		ID [id]
	% Only run if there is a DotID (Not NULL)
	deconstruct DTID
		'. ID2 [id]
	by
		ID2
end function

% Function to generate C parse code for each deconstructed 
% [alternative_decision] in a type decision rule
function parseSimpleTypeDecision mallocName [id]  LONG [id] OP [opt scl_additions] TR [type_reference] 
	replace [repeat declaration_or_statement]
		Stmts [repeat declaration_or_statement]
	% Extract the ID from the [type_reference]
	deconstruct TR
		ID [id] DTID [opt dotID] ANN [opt annotation]
	construct typeToPass [id]
		ID [checkDTID DTID]	% Resolve the DotID if one exists
	construct index [number]
		_ [index ID "_"]	% Find the "_" character location
	construct finalIndex [number]
		index [- 1]	% The location one character before the "_"
	construct typeToParse [id]
		ID [: 1 finalIndex]	% Get the characters before the "_"
	% The name of the parse function
	construct pName [id]
		_ [+ "parse"] [+ typeToParse]
	% The name of the constant value for the type
	construct IDVAL [id]
		typeToPass [+ "_VAL"]
	% Code to save the val (kind) for the first type
	construct body [repeat declaration_or_statement]
		LONG[tolower]'->'type = IDVAL;
	construct lowerLong [id]
		LONG[tolower]
	construct lowerTypeToPass [id]
		typeToPass[tolower]
	% Code to pass the result in a callback
	construct IDTOPASS [id]
		_ [+ "&"] [+ lowerLong] [+ "->ptr."] [+ lowerTypeToPass]
	% Generate a callback if required
	construct callback [repeat declaration_or_statement]
		_ [genCallback OP ID IDTOPASS] 
	% Successful end of parse
	construct return [declaration_or_statement]
		return true;
	% Full C code for the naieve parse for the decision. The naieve
	% parse will attempt to parse each message type until it finds success
	% in parsing a type
	construct Stmt [repeat declaration_or_statement]
		thePDU ->curPos = pos;
		thePDU ->remaining = remaining;
		if ( pName ('& LONG[tolower]->ptr'. typeToPass[tolower], thePDU, 'progname, endianness)) {
			body [. callback] [. return]
		}
	by
		Stmts [. Stmt]	% Append the decision code
end function

% Step 4.4: Generate the parse function for a type
% decision rule with callback optimizations
rule doAnnotatedTypeDecision ModName [id] TPRULES [repeat type_rule_definition] TPDECS [repeat construction_assignment_statement] 
	% Must have no annotations in the [construction_assignment_statement]
	replace $ [construction_assignment_statement]
		LONG [id] '^ SHORT [id] '::= TD [type_decision] OPT [opt scl_additions]
	% Must have an annotated callback
	deconstruct * [transfer_statement] OPT
		'Callback '^ PARENT [id] MallocType [id]
	construct funcName [id]
		_ [+ "parse"] [+ SHORT]	% Parse function name
	construct pName [id]
		funcName [checkPDUFName SHORT LONG]	% Check if the parse name is for the PDU type
											% and rename if it is
	construct MNPDU [id]
		_ [+ "PDU_"] [+ ModName]	% Name of the pdu for the module
	construct ALLOCNAME [id]
		mainpdu
	import FunctionDeclarations [repeat rule_definition]
	% Parse function header definition
	construct pModDecl [rule_definition] %[function_definition_or_declaration]
		bool pName (PARENT * PARENT[tolower], LONG * LONG[tolower], PDU * thePDU, char * 'progname, uint8_t endianness);
	export FunctionDeclarations
		FunctionDeclarations [. pModDecl]	% Save the function header definition	
	construct mainFunctionBody [repeat declaration_or_statement]
	construct parseByDecisions [repeat declaration_or_statement]
		_ [parseByDecisionAnnotated ALLOCNAME ModName TD LONG OPT]	% Generate the parse body
	% Generate successful end of parse
	construct return [declaration_or_statement]
		return false;
	by
		bool pName (PARENT * PARENT[tolower], LONG *  LONG[tolower], PDU * thePDU, char * 'progname, uint8_t endianness) {
			mainFunctionBody [. parseByDecisions] [. return]
		}
end rule

% Function to generate the C code for the first [type_reference]
% in a callback optimized type decision rule; Will leave the 
% generation of the code for the subsequent [alternative_decision] 
% to the next function
function parseByDecisionAnnotated mallocName [id] RuleName [id] TD [type_decision] LONG [id] OP [opt scl_additions]
	replace [repeat declaration_or_statement]
		Stmts [repeat declaration_or_statement]
	deconstruct TD 
		'( TR [type_reference] RTR [repeat alternative_decision] ')
	% Extract the ID from the [type_reference]
	deconstruct TR
		ID [id] DTID [opt dotID] ANN [opt annotation]
	% Extract the information from the [callback_annotation]
	deconstruct * [transfer_statement] OP
		'Callback '^ PARENT [id] MallocType [id]
	construct typeToPass [id]
		ID [checkDTID DTID]	% Resolve the DotID if one exists
	construct index [number]
		_ [index ID "_"]	% Find the "_" character location
	construct finalIndex [number]
		index [- 1]	% The location one character before the "_"
	construct typeToParse [id]
		ID [: 1 finalIndex]	% Get the characters before the "_"
	% The name of the parse function
	construct pName [id]
		_ [+ "parse"] [+ typeToParse]
	% The name of the constant value for the type
	construct IDVAL [id]
		typeToPass [+ "_VAL"]
	% The count variable for the parent struct
	construct count [id]
		MallocType[tolower] [+ "count"]
	% The length variable for the parent struct
	construct length [id]
		MallocType[tolower] [+ "length"]
	% Name for the typed callback
	construct callbackName [id]
		typeToPass [+ "_callback"]
	% Name to free the message after callback
	construct freeName [id]
		_ [+ "free"] [+ typeToPass]
	% Code to save the information to the parent struct, callback and then free
	construct body [repeat declaration_or_statement]
		PARENT[tolower]->length = thePDU ->curPos - PARENT[tolower]->length;
		PARENT[tolower]->count = '1;
		callbackName(PARENT[tolower], '& LONG[tolower]->ptr.typeToPass[tolower], thePDU);
		freeName('& LONG[tolower]->ptr.typeToPass[tolower]);
	% Successful end of parse
	construct return [declaration_or_statement]
		return true;
	% Full C code for the naieve parse for the first decision. The naieve
	% parse will attempt to parse each message type until it finds success
	% in parsing a type
	construct firstDecision [repeat declaration_or_statement]
		unsigned 'long pos = thePDU ->curPos;
		unsigned 'long remaining = thePDU ->remaining;
		if( pName ('& LONG[tolower]->ptr'. typeToPass[tolower], thePDU, 'progname, endianness)) {
			body [. return]
		} 
	construct typeRefs [repeat type_reference]
		_ [^ RTR]	% Extract all the [type_reference]'s from the [alternative_decision]'s
	by
		Stmts [. firstDecision]	% Append the first decision code
			 [parseAnnotatedTypeDecision mallocName LONG OP each typeRefs]	% Generate the code for the rest of the decisions
end function

% Function to generate C parse code for each deconstructed 
% [alternative_decision] in a callback optimized type decision rule
function parseAnnotatedTypeDecision mallocName [id]  LONG [id] OP [opt scl_additions] TR [type_reference] 
	replace [repeat declaration_or_statement]
		Stmts [repeat declaration_or_statement]
	% Extract the ID from the [type_reference]
	deconstruct TR
		ID [id] DTID [opt dotID] ANN [opt annotation]
	deconstruct * [transfer_statement] OP
		'Callback '^ PARENT [id] MallocType [id]
	construct typeToPass [id]
		ID [checkDTID DTID]	% Resolve the DotID if one exists
	construct index [number]
		_ [index ID "_"]	% Find the "_" character location
	construct finalIndex [number]
		index [- 1]	% The location one character before the "_"
	construct typeToParse [id]
		ID [: 1 finalIndex]	% Get the characters before the "_"
	% The name of the parse function
	construct pName [id]
		_ [+ "parse"] [+ typeToParse]
	% The name of the constant value for the type
	construct IDVAL [id]
		typeToPass [+ "_VAL"]
	% Code to save the val (kind) for the first type
	% The count variable for the parent struct
	construct count [id]
		MallocType[tolower] [+ "count"]
	% The length variable for the parent struct
	construct length [id]
		MallocType[tolower] [+ "length"]
	% Name for the typed callback
	construct callbackName [id]
		typeToPass [+ "_callback"]
	% Name to free the message after callback
	construct freeName [id]
		_ [+ "free"] [+ typeToPass]
	% Code to save the information to the parent struct, callback and then free
	construct body [repeat declaration_or_statement]
		PARENT[tolower]->length = thePDU ->curPos - PARENT[tolower]->length;
		PARENT[tolower]->count = '1;
		callbackName(PARENT[tolower], '& LONG[tolower]->ptr.typeToPass[tolower], thePDU);
		freeName('& LONG[tolower]->ptr.typeToPass[tolower]);
	% Successful end of parse
	construct return [declaration_or_statement]
		return true;
	% Full C code for the naieve parse for the first decision. The naieve
	% parse will attempt to parse each message type until it finds success
	% in parsing a type
	construct Stmt [repeat declaration_or_statement]
		thePDU ->curPos = pos;
		thePDU ->remaining = remaining;
		if ( pName ('& LONG[tolower]->ptr'. typeToPass[tolower], thePDU, 'progname, endianness)) {
			body [. return]
		}
	by
		Stmts [. Stmt]	% Append the decision code
end function

% Step 4.5: Generate the parse function for a standard type
% decision rule with parse optmizations
rule doOptimizedTypeDecision ModName [id] TPRULES [repeat type_rule_definition] TPDECS [repeat construction_assignment_statement]
	% Must have optimizable tag in the definition
	replace $ [construction_assignment_statement]
		LONG [id] '^ SHORT [id] '@ 'optimizable '::= TD [type_decision] OPT [opt scl_additions]
	construct funcName [id]
		_ [+ "parse"] [+ SHORT]	% Parse function name
	construct pName [id]
		funcName [checkPDUFName SHORT LONG]	% Check if the parse name is for the PDU type
											% and rename if it is
	construct MNPDU [id]
		_ [+ "PDU_"] [+ ModName]	% Name of the pdu for the module
	construct ALLOCNAME [id]
		mainpdu
	import FunctionDeclarations [repeat rule_definition]
	% Parse function header definition
	construct pModDecl [rule_definition]
		bool pName (LONG * LONG[tolower], PDU * thePDU, char * 'progname, uint8_t endianness);
	export FunctionDeclarations
		FunctionDeclarations [. pModDecl]	% Save the function header definition
	construct mainFunctionBody [repeat declaration_or_statement]
	deconstruct TD 
		'( TR [type_reference] RTR [repeat alternative_decision] ')
	% Extract the ID from the [type_reference]
	deconstruct TR
		ID [id] DTID [opt dotID] ANN [opt annotation]
	% Extract the information from the annotation
	deconstruct ANN
		'@ SZ [number] value [number] OPGLOB [opt global] '@ 'optimizable
	construct size [number]
		SZ [getBits]	% Convert the size in bytes to bits
	% Load the running total size of the rule and generate the length check C code
	construct lengthCheck [repeat declaration_or_statement]
		_ [lengthCheck ALLOCNAME SZ]
	% Uint variable of proper size to hold the type decision kind
	construct uintDecl [id]
		_ [+ "uint"] [+ size] [+ "_t"]
	% Get function to parse the kind from the PDU
	construct finalSize [id]
		_ [+ "get"] [+ size] [+ "_e"]
	construct GLOB [id]
		'NOTGLOBAL
	% Generate the case statement bodies for each type decision
	construct parseByOptimizedDecisions [repeat declaration_or_statement]
		_ [parseByOptimizedDecision ALLOCNAME ModName TD LONG OPT GLOB]
	construct switchBody [repeat declaration_or_statement]
	% Switch statement for the optimized parse; First and save the kind from
	% thePDU and then switch based on its value. Case bodies are generated by
	% the function called above
	construct switchStmt [repeat declaration_or_statement]
		uintDecl 'type = finalSize (thePDU, endianness);
		switch('type) {
			switchBody [. parseByOptimizedDecisions]		
		}
		return true;	
	by
		bool pName (LONG *  LONG[tolower], PDU * thePDU, char * 'progname, uint8_t endianness) {
			mainFunctionBody [. lengthCheck] [. switchStmt]
		}
end rule

% Function to generate the case statement for the first [type_reference]
% and each remaining [alternative_decision] in a type decision rule
function parseByOptimizedDecision mallocName [id] RuleName [id] TD [type_decision] LONG [id] OP [opt scl_additions] GLOB [id]
	replace [repeat declaration_or_statement]
		Stmts [repeat declaration_or_statement]
	deconstruct TD 
		'( TR [type_reference] RTR [repeat alternative_decision] ')
	% Extract the ID from the [type_reference]
	deconstruct TR
		ID [id] DTID [opt dotID] ANN [opt annotation]
	% Extracxt the annotation information
	deconstruct ANN
		'@ SZ [number] value [number] OPGLOB [opt global] OPOP [opt optimizable]
	where
		ANN [checkGLOBAL] [checkOPTIMIZABLE]	% The annotation must state optimization can be done
												% via standard or global methods
	construct size [number]
		SZ [getBits]		% Convert the size in bytes to bits
	construct index [number]
		_ [index ID "_"]	% Find the "_" character location
	construct finalIndex [number]
		index [- 1]	% The location one character before the "_"
	construct typeToParse [id]
		ID [: 1 finalIndex]	% Get the characters before the "_"
	% The name of the parse function
	construct pName [id]
		_ [+ "parse"] [+ typeToParse] [+ "_O"] %[+ DTID]
	% Uint variable of proper size to hold the type decision kind
	construct uintDecl [id]
		_ [+ "uint"] [+ size] [+ "_t"]
	% Get function to parse the kind from the PDU
	construct finalSize [id]
		_ [+ "get"] [+ size]
	% The name of the constant value for the type
	construct IDVAL [id]
		ID [+ "_VAL"]
	% Code to save the val (kind) for the first type in the member struct
	construct body [repeat declaration_or_statement]
		LONG[tolower]'->'type = IDVAL;
	construct lowerLong [id]
		LONG[tolower]
	construct lowerTypeToPass [id]
		ID[tolower]
	% Code to pass the result in a callback
	construct IDTOPASS [id]
		_ [+ "&"] [+ lowerLong] [+ "->ptr."] [+ lowerTypeToPass]		
	% Generate a callback if required
	construct callback [repeat declaration_or_statement]
		_ [genCallback OP ID IDTOPASS] 
	% Generate the first switch statement body
	construct firstDecision [repeat declaration_or_statement]
		_ [checkDecision value body callback OPGLOB typeToParse LONG ID GLOB]
	construct typeRefs [repeat type_reference]
		_ [^ RTR]	% Extract all the [type_reference]'s from the [alternative_decision]'s
	by
		Stmts [. firstDecision]	% Append the first switch body
			[parseOptimizedTypeDecision mallocName LONG OP GLOB each typeRefs]	% Generate the remaining switch bodies
			 [defaultStatement]	% Generate the default fail statement
end function

% Condition function to check if an annotation is in the GLOBAL form
function checkGLOBAL
	match [opt annotation]
		'@ SZ [number] value [number] '@ 'GLOBAL OPOP [opt optimizable]
end function

% Condition function to check if an annotation is in the OPTIMIZABLE form
function checkOPTIMIZABLE
	match [opt annotation]
		'@ SZ [number] value [number] OPGLOB [opt global] '@ 'optimizable
end function

% Function to generate the switch body for the first option from
% a [type_reference] in a type decision depending on optimization type
function checkDecision VAL [number] body [repeat declaration_or_statement] callback [repeat declaration_or_statement] decType [opt global] typeToParse [id] LONG [id] ID [id] GLOB [id]
	replace [repeat declaration_or_statement]
		Stmts [repeat declaration_or_statement]
	construct decision [repeat declaration_or_statement]
		_ [genGlobalDecision VAL body callback decType typeToParse LONG ID GLOB] [genOptimizedDecision VAL body callback decType typeToParse LONG ID GLOB] 
	by
		Stmts [. decision]
end function

% Function to generate the switch body for the first option from
% a [type_reference] in a type decision for global optimization
function genGlobalDecision VAL [number] body [repeat declaration_or_statement] callback [repeat declaration_or_statement] decType [opt global] typeToParse [id] LONG [id] ID [id] GLOB [id]
	replace [repeat declaration_or_statement]
		Stmts [repeat declaration_or_statement]
	% Must be passed in a GLOBAL indicator
	deconstruct GLOB
		'GLOBAL
	% The name of the parse function
	construct pName [id]
		_ [+ "parse"] [+ typeToParse]	
	% Switch case must consider the dotID when passing parameters; Break after parse as
	% it can only ever be one possible case triggered
	construct decision [repeat declaration_or_statement]
			case VAL :
			if(pName ('& LONG[tolower]->ptr'. ID[tolower], thePDU, 'progname, endianness)){
				body [. callback]
			} else { 
				return false; 
			}
			break;	
	by
		Stmts [. decision]
end function

% Function to generate the switch body for the first option from
% a [type_reference] in a type decision for parse optimization
function genOptimizedDecision VAL [number] body [repeat declaration_or_statement] callback [repeat declaration_or_statement] decType [opt global] typeToParse [id] LONG [id] ID [id] GLOB [id]
	replace [repeat declaration_or_statement]
		Stmts [repeat declaration_or_statement]
	% Must not be passed in the global indicator
	deconstruct not GLOB
		'GLOBAL	
	% The name of the parse function
	construct pName [id]
		_ [+ "parse"] [+ typeToParse] [+ "_O"]
	% Switch case must attempt a parse when triggered and call the optimized
	% parse function; Break after parse as it can only ever be one possible
	% case triggered
	construct decision [repeat declaration_or_statement]
			case VAL :
			if(pName ('& LONG[tolower]->ptr'. ID[tolower], thePDU, 'progname, &'type, endianness)){
				body [. callback]
			} else { 
				return false; 
			}
			break;	
	by
		Stmts [. decision]
end function

% Function to generate a switch case for each deconstructed 
% [alternative_decision] in an optimized type decision rule
function parseOptimizedTypeDecision mallocName [id]  LONG [id] OP [opt scl_additions] GLOB [id] TR [type_reference]
	replace [repeat declaration_or_statement]
		Stmts [repeat declaration_or_statement]
	% Extract the ID from the [type_reference]
	deconstruct TR
		ID [id] DTID [opt dotID] ANN [opt annotation]
	% Extracxt the annotation information
	deconstruct ANN
		'@ SZ [number] value [number] OPGLOB [opt global] OPOP [opt optimizable]
	where
		ANN [checkGLOBAL] [checkOPTIMIZABLE]	% The annotation must state optimization can be done
												% via standard or global methods
	construct size [number]
		SZ [getBits]	% Convert the size in bytes to bits
	construct index [number]
		_ [index ID "_"]	% Find the "_" character location
	construct finalIndex [number]
		index [- 1]	% The location one character before the "_"
	construct typeToParse [id]
		ID [: 1 finalIndex]	% Get the characters before the "_"
	% The name of the parse function
	construct pName [id]
		_ [+ "parse"] [+ typeToParse] [+ "_O"] %[+ DTID]
	% Uint variable of proper size to hold the type decision kind
	construct uintDecl [id]
		_ [+ "uint"] [+ size] [+ "_t"]
	% Get function to parse the kind from the PDU
	construct finalSize [id]
		_ [+ "get"] [+ size]
	% The name of the constant value for the type
	construct IDVAL [id]
		ID [+ "_VAL"]
	% Code to save the val (kind) for the first type in the member struct
	construct body [repeat declaration_or_statement]
		LONG[tolower]'->'type = IDVAL;
	construct lowerLong [id]
		LONG[tolower]
	construct lowerTypeToPass [id]
		ID[tolower]
	% Code to pass the result in a callback
	construct IDTOPASS [id]
		_ [+ "&"] [+ lowerLong] [+ "->ptr."] [+ lowerTypeToPass]		
	% Generate a callback if required
	construct callback [repeat declaration_or_statement]
		_ [genCallback OP ID IDTOPASS] 
	% Generate the switch case for the current [type_reference]
	construct decision [repeat declaration_or_statement]
			_ [checkDecision value body callback OPGLOB typeToParse LONG ID GLOB]
	by
		Stmts [. decision]	% Append the switch case
end function

% Function to generate the default case for a switch statement
% If the default is hit then none of the possible messages met
% the parse; The message is therefore invalid so the parse fails
function defaultStatement
	replace [repeat declaration_or_statement]
		Stmts [repeat declaration_or_statement]
	construct default [repeat declaration_or_statement]
		default :
			return false;
	by
		Stmts [. default]	% Append parse fail
end function

% Step 4.6: Generate the parse function for a standard type
% decision rule with global optimization
rule doGloballyOptimizedTypeDecision ModName [id] TPRULES [repeat type_rule_definition] TPDECS [repeat construction_assignment_statement]
	% Must be both GLOBAL and OPTIMIZABLE
	replace $ [construction_assignment_statement]
		LONG [id] '^ SHORT [id] '@ 'GLOBAL '@ 'optimizable '::= TD [type_decision] OPT [opt scl_additions]
	% Must have a global back constraint
	deconstruct * [transfer_statement] OPT
		'Back '{ 'GLOBAL '( GLOBID [id] ') '}
	construct funcName [id]
		_ [+ "parse"] [+ SHORT]	% Parse function name
	construct pName [id]
		funcName [checkPDUFName SHORT LONG]	% Check if the parse name is for the PDU type
											% and rename if it is
	construct MNPDU [id]
		_ [+ "PDU_"] [+ ModName]	% Name of the pdu for the module
	construct ALLOCNAME [id]
		mainpdu
	import FunctionDeclarations [repeat rule_definition]
	% Parse function header definition
	construct pModDecl [rule_definition]
		bool pName (LONG * LONG[tolower], PDU * thePDU, char * 'progname, uint8_t endianness);
	export FunctionDeclarations
		FunctionDeclarations [. pModDecl]	% Save the function header definition
	construct mainFunctionBody [repeat declaration_or_statement]
	deconstruct TD 
		'( TR [type_reference] RTR [repeat alternative_decision] ')
	% Extract the ID from the [type_reference]
	deconstruct TR
		ID [id] DTID [opt dotID] ANN [opt annotation]
	% Extracxt the annotation information; Must be GLOBAL
	deconstruct ANN
		'@ SZ [number] value [number] '@ GLOBAL
	construct size [number]
		SZ [getBits]	% Convert the size in bytes to bits
	% Load the running total size of the rule and generate the length check C code
	construct lengthCheck [repeat declaration_or_statement]
		_ [lengthCheck ALLOCNAME SZ]
	construct GLOB [id]
		'GLOBAL
	% Generate the case statement bodies for each type decision
	construct parseByOptimizedDecisions [repeat declaration_or_statement]
		_ [parseByOptimizedDecision ALLOCNAME ModName TD LONG OPT GLOB]
	construct switchBody [repeat declaration_or_statement]
	% Switch statement choses a case based on the global ID as a kind
	construct switchStmt [repeat declaration_or_statement]
		switch(GLOBID) {
			switchBody [. parseByOptimizedDecisions]	
		}
		return true;	
	by
		bool pName (LONG *  LONG[tolower], PDU * thePDU, char * 'progname, uint8_t endianness) {
			mainFunctionBody [. lengthCheck] [. switchStmt]
		}
end rule

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%  End Parse [rule_definition] section  %%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%  Initialize Pointer Section  %%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

% Function to initialize any pointers in the struct of the rule
% being parsed. When the parse of a rule is started, any pointers
% must be set to NULL before they are used for code safety.
% MallocName is the name being used to describe the instance of
% the struct and the struct elements follow standard naming
function initializePointer mallocName [id] RuleName [id] LET [list element_type] OP [opt scl_additions] ET [element_type]
	replace [repeat declaration_or_statement]
		Stmts [repeat declaration_or_statement]
	by
		% Attempt to initialize all possible types of pointers that could be in a struct
	   	Stmts [initializeSetOfPointer mallocName RuleName LET ET OP]
				[initializeOptionalPointer mallocName RuleName LET ET]
				[initializeOctetStringSizeConstrainedPointer mallocName RuleName LET ET]
end function

% Initialize pointers that correspond to a SET OF list element
% in a rule. If that rule has an annotated callback of the @ [id]
% type then the pointer should not be initialized as it does not
% exist in the struct for that optimization type
function initializeSetOfPointer mallocName [id] RuleName [id] LET [list element_type] ET [element_type] OP [opt scl_additions] 
	where not
		OP [checkForAnnotatedCallbackRemoval]	% Check for the [callback_annotation]
	% The SET OF [element_type] that needs to be initialized
	deconstruct ET 
		LONG [id] '^ SHORT [id] 'SET 'OF TYPE [id] SZ [size_constraint]
	replace [repeat declaration_or_statement]
		Stmts [repeat declaration_or_statement]
	% The pointer member set to null; Following standard naming
	construct initialize [repeat declaration_or_statement]
		mallocName ->SHORT[tolower] = NULL;
	by
	   Stmts [. initialize]	% Append the initialization to the other statements
end function

% Condition function used to do a deep search on
% [scl_additions] to try and find an @ [id]
% [callback_annotation] to indicate the rule is optimized
function checkForAnnotatedCallbackRemoval
	match * [callback_annotation]
		'@ TYPE [id]
end function

% Initialize pointers that correspond to any [element_type]
% declared with an OPTIONAL tag. Since these are not always
% required to have a value they must be set to NULL until
% they are given a value so it is known when they do not
function initializeOptionalPointer mallocName [id] RuleName [id] LET [list element_type] ET [element_type] 
	% The [element_type] declared as optional
	deconstruct ET 
		LONG [id] '^ SHORT [id] TYPE [type] 'OPTIONAL
	replace [repeat declaration_or_statement]
		Stmts [repeat declaration_or_statement]
	% The pointer member set to null; Following standard naming
	construct initialize [repeat declaration_or_statement]
		mallocName ->SHORT[tolower] = NULL;
	by
	   Stmts [. initialize]	% Append the initialization to the other statements
end function

% Initialize pointers that correspond to OCTET STRING 
% [element_type]'s with a constrained size. These are also 
% represented as pointers in the struct so they must also
% be initialized to NULL for code safety
function initializeOctetStringSizeConstrainedPointer mallocName [id] RuleName [id] LET [list element_type] ET [element_type] 
	% The OCTET STRING [element_type] with constrained size
	deconstruct ET 
		LONG [id] '^ SHORT [id] 'OCTET 'STRING '(SIZE 'CONSTRAINED) OPT [opt endian] OPSL [opt slack]
	replace [repeat declaration_or_statement]
		Stmts [repeat declaration_or_statement]
	% The pointer member set to null; Following standard naming
	construct initialize [repeat declaration_or_statement]
		mallocName ->SHORT[tolower] = NULL;
	by
	   Stmts [. initialize]	% Append the initialization to the other statements
end function

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%  End Initialize Pointer Section  %%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%  Parse [list element_type] Section  %%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

% Function to generate the C code for each SCL5 described [element_type].
% The function builds up a set of statements to create all the code
% necessary to parse the full [list element_type] of a rule. There is
% a seperate function to generate the code to parse each form of
% [element_type] and the different optimizations and constraints that 
% it can have. ET is the [element_type] that code is currently being 
% generated for, the mallocName [id] is the name of the struct instance
% and the remaining paramaters are sections of the rule definition
function parseBySize mallocName [id] RuleName [id] OP [opt scl_additions] LET [list element_type] ET [element_type] 
	replace [repeat declaration_or_statement]
		Stmts [repeat declaration_or_statement]
	by
		Stmts 	[checkPOSElements mallocName ET]
			 	[checkPOSElementsOptional mallocName ET]
			 
			 	% Parse after saving required positions
			 	
			 	%% Parse Built-In [element_type] %%
				[parseIntegerTypebySize mallocName RuleName ET]
			 	[parseReal4Type mallocName RuleName ET]
			 	[parseReal8Type mallocName RuleName ET]
			 	[parseOctetStringTypebySize mallocName RuleName ET]
			 	[parseOctetStringTypebyLargeSize mallocName RuleName ET]
				[parseOctetStringTypeConstrained mallocName RuleName OP LET ET]
			 
			 	%% Parse User Defined [element_type] %%
				[parseUserDefineTypes mallocName RuleName OP LET ET]
			 
			 	%% Parse Set Of [element_type] %%
			 	[parseSetOfTypeDecisionTerminateConstrained mallocName RuleName OP ET]
			 	[parseSetOfTypeDecisionCardinalityConstrained mallocName RuleName OP LET ET]
			 	[parseSetOfTypeDecision mallocName RuleName OP ET]
			 	[parseAnnotatedSetOfTypeDecision mallocName RuleName OP ET]

			 	% IMPORTANT: Have to be the last calls to follow back constraints properly
			 	[checkEndiannessConstraints RuleName ET OP]
			 	[checkBackConstraints mallocName RuleName ET OP]
end function

%% Check for POS tags section

% Check the [element_type] first to see if it is declared
% with a POS tag to save the position. If it is required to
% save the position then generate a line of C code to save
% the current position of the PDU in a variable
function checkPOSElements mallocName [id] ET [element_type]
	replace [repeat declaration_or_statement]
		Stmts [repeat declaration_or_statement]
	% Check for POS tag
	deconstruct ET
		LONG [id] '^ SHORT [id] TP [type] 'POS
	% Save the current position of the PDU in a variable
	construct savePos [declaration_or_statement]
		'unsigned 'long SHORT[tolower][+ "POS"] '= 'thePDU -> 'curPos;
	by
		Stmts [. savePos]	% Add the statement
end function

% Check the [element_type] first to see if it is declared
% with both an optional and POS tag. If it is required to
% save the position then generate a line of C code to save
% the current position of the PDU in a variable. There must
% be a seperate check for [element_type] with both OPTIONAL
% and POS as the previous check will not detect this
function checkPOSElementsOptional mallocName [id] ET [element_type]
	replace [repeat declaration_or_statement]
		Stmts [repeat declaration_or_statement]
	deconstruct ET
		LONG [id] '^ SHORT [id] TP [type] 'OPTIONAL 'POS
	construct savePos [declaration_or_statement]
		'unsigned 'long SHORT[tolower][+ "POS"] '= 'thePDU -> 'curPos;
	by
		Stmts [. savePos]
end function

	%##############################################%
	%#  Parse Built in [element_type] Subsection  #%
	%##############################################%

	% Function to generate the C parse code for an [element_type]
	% of the integer form with known size. 
	function parseIntegerTypebySize mallocName [id] RuleName [id] ET [element_type]
		% Do not parse if in the PDU rule; It is a special case
		deconstruct not mallocName
			mainpdu
		% Must have integer with known size form
		deconstruct ET
			LONG [id] '^ SHORT [id] 'INTEGER '(SIZE SZ [number] 'BYTES) OP [opt endian] POS [opt position_value]
		construct getSize [number]
			SZ [getBits]	% Convert the size description in bytes to bits to know how large to make the uint
		import lengthToCheck [number]
		export lengthToCheck
			lengthToCheck [addToLength SZ]	% Increase the total length of the rule's size by the [element_type] size
		% Generate the function name for getting bits from the pdu
		construct size [id]
			_ [+ "get"] [+ getSize] [+ "_e"]
		construct getEndianness [id]
			_ [getEndianness ET]	% Get the LITTLEENDIAN or BIGENDIAN value from the [element_type]
		% The C code to parse the [element_type] value and store it in the struct member
		construct Stmt [declaration_or_statement]
			RuleName[tolower] '->SHORT[tolower] = size(thePDU, getEndianness);
		replace [repeat declaration_or_statement]
			Stmts [repeat declaration_or_statement]
		by
			Stmts [. Stmt]	% Append the statement
	end function

	% Convert a size saved as bytes to bits 
	% by multiplying by 8
	function getBits
		replace [number]
			Num [number]
		construct Eight [number]
			'8
		construct numBits [number]
			Eight [* Num]
		by 
			numBits
	end function

	% Function to add a number to another number
	function addToLength size [number]
		replace [number]
			length [number]
		by
			size [+ length]
	end function 

	% Function to generate the C parse code for an [element_type]
	% of the real form with a size of 4 bytes (Identifying itself
	% as a real)
	function parseReal4Type mallocName [id] RuleName [id] ET [element_type]
		% Do not parse if in the PDU rule; It is a special case
		deconstruct not mallocName
			mainpdu
		% Must have a real form
		deconstruct ET
			LONG [id] '^ SHORT [id] 'REAL '(SIZE SZ [number] 'BYTES) OP [opt endian] POS [opt position_value]
		construct getSize [number]
			SZ
		where
			SZ [= 4]	% The size must be 4 bytes for it to be a real variable
		import lengthToCheck [number]
		export lengthToCheck
			lengthToCheck [addToLength SZ]	% Increase the total length of the rule's size by the [element_type] size
		% Generate the function name for getting bits from the pdu
		construct size [id]
			_ [+ "getReal4"] [+ "_e"]
		construct getEndianness [id]
			_ [getEndianness ET]	% Get the LITTLEENDIAN or BIGENDIAN value from the [element_type]
		% The C code to parse the [element_type] value and store it in the struct member
		construct Stmt [declaration_or_statement]
			RuleName[tolower] '->SHORT[tolower] = size(thePDU, getEndianness);
		replace [repeat declaration_or_statement]
			Stmts [repeat declaration_or_statement]
		by
			Stmts [. Stmt]	% Append the statement
	end function

	% Function to generate the C parse code for an [element_type]
	% of the real form with a size of 8 bytes (Identifying itself
	% as a double)
	function parseReal8Type mallocName [id] RuleName [id] ET [element_type]
		% Do not parse if in the PDU rule; It is a special case
		deconstruct not mallocName
			mainpdu
		% Must have a real form
		deconstruct ET
			LONG [id] '^ SHORT [id] 'REAL '(SIZE SZ [number] 'BYTES) OP [opt endian] POS [opt position_value]
		construct getSize [number]
			SZ
		where
			SZ [= 8]	% The size must be 8 bytes for it to be a double variable
		import lengthToCheck [number]
		export lengthToCheck
			lengthToCheck [addToLength SZ]	% Increase the total length of the rule's size by the [element_type] size
		% Generate the function name for getting bits from the pdu
		construct size [id]
			_ [+ "getReal8"] [+ "_e"]
		construct getEndianness [id]
			_ [getEndianness ET]	% Get the LITTLEENDIAN or BIGENDIAN value from the [element_type]
		% The C code to parse the [element_type] value and store it in the struct member
		construct Stmt [declaration_or_statement]
			RuleName[tolower] '->SHORT[tolower] = size(thePDU, getEndianness);
		replace [repeat declaration_or_statement]
			Stmts [repeat declaration_or_statement]
		by
			Stmts [. Stmt]	% Append the statement
	end function

	% Function to generate the C parse code for an [element_type]
	% that is an OCTET STRING with a small (Less than 8 bytes) size
	function parseOctetStringTypebySize mallocName [id] RuleName [id] ET [element_type]
		% Must have an OCTET STRING form with defined size
		deconstruct ET
			LONG [id] '^ SHORT [id] 'OCTET 'STRING '(SIZE SZ [number] 'BYTES) OP [opt endian] OPSL [opt slack] POS [opt position_value]
		where
			SZ [<= 8]	% The size must be 8 bytes or less so it fits in a uint64 or smaller iteration
		construct getSize [number]
			SZ [getBits]
		import lengthToCheck [number]
		export lengthToCheck
			lengthToCheck [addToLength SZ]	% Increase the total length of the rule's size by the [element_type] size
		% Generate the function name for getting bits from the pdu. Only get the size of the field even if it is stored
		% in a larger uint
		construct size [id]
			_ [+ "get"] [+ getSize] [+ "_e"]
		construct getEndianness [id]
			_ [getEndianness ET]	% Get the LITTLEENDIAN or BIGENDIAN value from the [element_type]
		% The C code to parse the [element_type] value and store it in the struct member
		construct Stmt [declaration_or_statement]
			RuleName[tolower] '->SHORT[tolower] = size(thePDU, getEndianness);
		replace [repeat declaration_or_statement]
			Stmts [repeat declaration_or_statement]
		by
			Stmts [. Stmt]	% Append the statement
	end function

	% Function to generate the C parse code for an [element_type]
	% that is an OCTET STRING with a large (Greater than 8 bytes) size
	function parseOctetStringTypebyLargeSize mallocName [id] RuleName [id] ET [element_type]
		% Must have an OCTET STRING form with defined size
		deconstruct ET
			LONG [id] '^ SHORT [id] 'OCTET 'STRING '(SIZE SZ [number] 'BYTES) OP [opt endian] OPSL [opt slack] POS [opt position_value]
		where
			SZ [> 8]	% The size must be greater than 8 bytes so it does not fit 
						% in a uint64 and must be allocated in an array
		construct getSize [number]
			SZ [getBits]
		import lengthToCheck [number]
		export lengthToCheck
			lengthToCheck [addToLength SZ]	% Increase the total length of the rule's size by the [element_type] size
		% We have no get data function for sizes greater than 
		% 64 bits so the data must be manually copied from the PDU
		construct thePDU [id]
			'thePDU
		construct data [referencable_primaries]
			thePDU [+ "->data"]
		construct curPos [referencable_primaries]
			thePDU [+ "->curPos"]
		% Manually copy the data from the PDU's data field to our struct member
		% Copies starting at the current location (which is stored in the 
		% PDU [curPos]) and copies SZ [number] bytes. No malloc is required as
		% the size of the array is defined (in the header file)
		construct Stmt [repeat declaration_or_statement]
			memcpy(RuleName[tolower] '->SHORT[tolower], '& data'[curPos'], SZ);
			curPos += SZ;	% Manually increase the current position in the PDU

			if( RuleName[tolower] '->SHORT[tolower] '[ SZ '- '1 '] != ''\0'' ) {
				% This if statement is used for a string safety check. It checks
				% to see if the saved string is null terminated. This is done 
				% because in C if strings are not null terminated that means there
				% is the potential for a buffer overflow attack with unsafe copies.
				% The full vulnerabilites in this section have not been fully
				% evaulated so for now the statement has no function. It could 
				% output a warning or error in the future.
			}
		replace [repeat declaration_or_statement]
			Stmts [repeat declaration_or_statement]
		by
			Stmts [. Stmt]	% Append the statement
	end function

	%% NOTE:
	%% This type of Octet string needs to have a Forward constraint on its size
	%% If it doesn't, we are assuming that the rest of the PDU is part of this
	%% Octet string and saving the remaining length in a dataLength variable inside
	%% struct this string belongs to!
	%% This is currently the case for DATASUBs with serializedDATA in RTPS
	% Function to generate the C parse code for an [element_type]
	% that is an OCTET STRING with a constrained size
	function parseOctetStringTypeConstrained mallocName [id] RuleName [id] OP [opt scl_additions] LET [list element_type] ET [element_type]
		% Must have an OCTET STRING with a constrained size
		deconstruct ET
			LONG [id] '^ SHORT [id] 'OCTET 'STRING '(SIZE 'CONSTRAINED) OPT [opt endian] OPSL [opt slack] POS [opt position_value]
		deconstruct OP
			ENC [opt encoding_grammar_indicator] SZ [opt size_markers_block]
			'<transfer>
			RETR [repeat transfer_statement]
			'</transfer>
			CST [opt constraints_block]
		construct lengthCheck [repeat declaration_or_statement]
		construct convertedExpression [repeat declaration_or_statement]
			lengthCheck [checkLengthToParse LONG RETR RuleName LET]
		replace [repeat declaration_or_statement]
			Stmts [repeat declaration_or_statement]
		by
			Stmts [. convertedExpression]
	end function

	function checkLengthToParse LONG [id] RETR [repeat transfer_statement] RuleName [id] LET [list element_type]
		replace [repeat declaration_or_statement]
			Stmts [repeat declaration_or_statement]
		% Must have a length constraint
		deconstruct * [transfer_statement] RETR
			'Forward '{ 'LENGTH ( LONG ) '== REST [relational_expression] '}
		% Convert the [relational_expression] contents to a simple form
		construct RESTConverted [relational_expression]
			REST [convertIDToShort] [checkOptionalLengths LET RuleName] [convertSizeOf] [convertPOS] [convertPDUREMAINING] 
		% Convert the intermediate expression into the form of the struct and element's instance
		construct expression [constant]
			RESTConverted [convertToFullID RuleName]
		% We have no get data function for sizes greater than 
		% 64 bits so the data must be manually copied from the PDU
		construct thePDU [id]
			'thePDU
		construct data [referencable_primaries]
			thePDU [+ "->data"]
		construct curPos [referencable_primaries]
			thePDU [+ "->curPos"]
		% Save the length remaining in a local variable; The value of this is
		% currently not used
		construct saveLength [repeat declaration_or_statement]
			unsigned 'long remaining = thePDU ->remaining;
		% Since the size is constrained, the size must be checked against the
		% expected size; It fails the parse if it fails the constraint
		construct lengthCheck [repeat declaration_or_statement]
			if(!lengthRemaining(thePDU, expression , progname)) {
				% If we reach this point then we have an incorrect PDU length or type
				return false;
			}
		% Malloc storage space for the array, as the length of the data is now 
		% known; The struct has no defined size for the array as the size is constrained.
		% Manually copy the data from the PDU's data field to our struct member
		% Copies starting at the current location (which is stored in the 
		% PDU [curPos]) and copies the required amount of data
		construct convertExpression [repeat declaration_or_statement]
			% Allocate storage space for the array
			RuleName[tolower]->LONG[convertIDToShort] '= (unsigned char *)malloc(sizeof(unsigned char) * ( expression ));
			% Check the space allocation
			if( RuleName[tolower]->LONG[convertIDToShort] == 'NULL) {
				% If we reach this point then we have had an internal malloc error
				return false;
			}
			% Set the length field of the struct to save the size for later use
			RuleName[tolower]->LONG[convertIDToShort][+ "_length"] = expression;
			% Copy the data to the array
			memcpy( RuleName[tolower]->LONG[convertIDToShort], '& data'[curPos'], expression );
			curPos += expression ;

			% Check the character array termination
			if( RuleName[tolower]->LONG[convertIDToShort] '[ expression '- '1 '] != ''\0'' ) {
				% If we reach this point then we have a non-null terminated character array
				% See "parseOctetStringTypebyLargeSize" for more information
			}
		by
			Stmts [. saveLength] [. lengthCheck] [. convertExpression]	% Append all the generated statements
	end function

	% Convert an [id] in the LONG form of ID_PROTOCOL to the
	% short form of just ID by removing everything including
	% and after the "_"
	rule convertIDToShort 
		replace $ [id]
			ID [id]
		construct index [number]
			_ [index ID "_"]	% Location of the "_"
		construct finalIndex [number]
			index [- 1]	% Location one space behind the "_"
		construct typeToParse [id]
			ID [: 1 finalIndex]	% The contents of the [id] up to the "_"
		by 
			typeToParse[tolower]	% Convert to lowercase
	end rule

	% Check if the [relational_expression] that the length must
	% equal is a SIZEOF expression and fully expand it
	rule checkOptionalLengths LET [list element_type] RuleName [id]
		replace $ [unary_expression]
			SZ [unary_expression]
		deconstruct SZ
			'SIZEOF '( ID [id] ')
		% Find the [element_type] that is the the [id] of
		% the SIZEOF length constraint
		deconstruct * [element_type] LET
			LONG [id] '^ ID TYPE [id] '(SIZE 'DEFINED) OPEND [opt endian] OPSL [opt slack] 'OPTIONAL POS [opt position_value]
		% Load the copy of all the rules and find the rule that
		% defines the type that is the length constraint
		import ALLRULES [repeat rule_definition]
		deconstruct * [type_rule_definition] ALLRULES 
			TYPE '^ SHORTID [id] '::= 'SEQUENCE '{
				LE [list element_type] OC [opt ',]
			'} OP [opt scl_additions]
		% Find the element with constrained length in that type
		deconstruct * [element_type] LE
			LONGLE [id] '^ SHORTLE [id] 'SET 'OF TPLE [id] '(SIZE 'CONSTRAINED)
		by
			% Replace the SETOF with the expanded expression;
			% This is the length element of the instance of the
			% struct which can be evaluated
			RuleName[tolower] -> ID -> SHORTLE[+ "length"]
	end rule

	% Convert the SIZEOF terminal to lowercase
	rule convertSizeOf
		replace $ [size_of_expn]
			'SIZEOF '( RE [referenced_element] ')
		by
			'sizeof '( RE ')
	end rule

	% Convert a POS expression to the form
	% IDPOS
	rule convertPOS
		replace $ [pos_expression]
			'POS '( RE [referenced_element] ')
		deconstruct RE
			ID [id]
		by
			ID[+ "POS"]
	end rule

	% Convert the PDUREMAINING terminal to remaining
	rule convertPDUREMAINING
		replace $ [primary]
			'PDUREMAINING
		by
			'remaining
	end rule

	% If the expression post simplification contains any
	% [id] then it must be converted to a form that represents
	% the instance of the struct so it can be evaluated
	rule convertToFullID RuleName [id]
		replace $ [referencable_primaries]
			RP [referencable_primaries]
		% Must have an [id]
		deconstruct RP
			ID [id]
		% [id] cannot be remaining
		deconstruct not ID
			'remaining
		construct LenID [number]
			_ [# ID]
		construct minusTwo [number]
			LenID [- 2]
		construct LastThree [id]
			ID [: minusTwo LenID]	% Get the last 3 characters of the [id]
									% and ensure they are not POS
		deconstruct not LastThree
			'POS
		by
			RuleName[tolower][+ "->"] [+ ID]	% Have a true [id] so convert to the form
												% that represents its instance
	end rule

	%##################################################%
	%#  End Parse Built in [element_type] Subsection  #%
	%##################################################%

	%##################################################%
	%#  Parse User Defined [element_type] Subsection  #%
	%##################################################%

	% Function to generate the C parse code for a user defined
	% type [element_type]
	function parseUserDefineTypes mallocName [id] RuleName [id] OP [opt scl_additions] LET [list element_type] ET [element_type]
		replace [repeat declaration_or_statement]
			Stmts [repeat declaration_or_statement]
		construct slackModSavePos [repeat declaration_or_statement]		
			_ [checkSlackModSavePos mallocName RuleName ET]
		construct forwardConstraint [repeat declaration_or_statement]
			_ [checkForwardLengthUserDefined mallocName RuleName OP LET ET]
		construct PDUID [id]
			'thePDU
		construct PDU [id]
			PDUID [checkPDU forwardConstraint]
		construct parseDefinedType [repeat declaration_or_statement]
			_ [parseUserDefinedType mallocName ET PDU]
				[parseUserDefinedTypeOptional mallocName OP LET ET PDU]
				[parseUserDefinedTypeOptionalWithNum mallocName OP LET ET PDU]
		construct slacks [repeat declaration_or_statement]
			_ [doSlacks forwardConstraint ET] [doSlackMods ET]
		by
			Stmts [. slackModSavePos] [. forwardConstraint] [. parseDefinedType] [. slacks]
	end function

	function checkSlackModSavePos mallocName [id] RuleName [id] ET [element_type]
		replace [repeat declaration_or_statement]
			Stmts [repeat declaration_or_statement]
		construct slackMod [repeat declaration_or_statement]
			_ [slackMod mallocName RuleName ET] [slackModOptional mallocName RuleName ET]
		by
			Stmts [. slackMod]
	end function

	function slackMod mallocName [id] RuleName [id] ET [element_type]
		replace [repeat declaration_or_statement]
			Stmts [repeat declaration_or_statement]
		deconstruct ET
			LONG [id] '^ SHORT [id] TYPE [id] '(SIZE 'DEFINED)  OPEN [opt endian] 'SLACKMOD4 POS [opt position_value]	
		construct pos [id]
			_ [+ "pos"] [+ SHORT]	
		construct savePos [repeat declaration_or_statement]
			'unsigned 'long pos = thePDU ->curPos;
		by
			Stmts [. savePos]
	end function

	function slackModOptional mallocName [id] RuleName [id] ET [element_type]
		replace [repeat declaration_or_statement]
			Stmts [repeat declaration_or_statement]
		deconstruct ET
			LONG [id] '^ SHORT [id] TYPE [id] '(SIZE 'DEFINED)  OPEN [opt endian] 'SLACKMOD4 'OPTIONAL POS [opt position_value]	
		construct pos [id]
			_ [+ "pos"] [+ SHORT]	
		construct savePos [repeat declaration_or_statement]
			'unsigned 'long pos = thePDU ->curPos;
		by
			Stmts [. savePos]
	end function

	function checkForwardLengthUserDefined mallocName [id] RuleName [id] OP [opt scl_additions] LET [list element_type] ET [element_type]
		deconstruct ET
			LONG [id] '^ SHORT [id] TYPE [id] '(SIZE 'DEFINED)  OPEN [opt endian] OPSL [opt slack] POS [opt position_value]	
		deconstruct OP
			ENC [opt encoding_grammar_indicator] SZ [opt size_markers_block]
			'<transfer>
			RETR [repeat transfer_statement]
			'</transfer>
			CST [opt constraints_block]
		deconstruct * [transfer_statement] RETR
			'Forward '{ 'LENGTH ( LONG ) '== REST [relational_expression] '}
		replace [repeat declaration_or_statement]
			Stmts [repeat declaration_or_statement]
		construct RESTConverted [relational_expression]
			REST [convertIDToShort] [checkOptionalLengths LET RuleName] [convertSizeOf] [convertPOS] [convertPDUREMAINING] 
		%construct expression [cexpression]
		construct expression [constant]
			RESTConverted [convertToFullID RuleName]
		construct lengtherr [stringlit]
			_ [+ "%s: incorrect PDU length or type: %s line: %d\n"]
		construct nullerr [stringlit]
			_ [+ "%s: WARNING, slack is NOT null terminated. file: %s line: %d\n"]
		construct savePos [repeat declaration_or_statement]
			unsigned 'long pos = thePDU ->'curPos;
		construct lengthCheck [repeat declaration_or_statement]
			if(!lengthRemaining(thePDU, expression , progname)) {
				%fprintf(stderr, lengtherr ,progname,__FILE__,__LINE__);
				return false;
			}
		%construct constrainedPDU [id]
		%	'constrainedPDU
		construct convertExpression [repeat declaration_or_statement]
			'PDU 'constrainedPDU;
			constrainedPDU.'data = 'thePDU ->'data;
			constrainedPDU.len = expression;
			constrainedPDU.watermark = 'thePDU ->watermark;
			constrainedPDU.curPos = 'pos;
			constrainedPDU.curBitPos = '0;
			constrainedPDU.remaining = expression;
		by
			Stmts [. savePos] [. lengthCheck] [. convertExpression]
	end function

	function checkPDU constraint [repeat declaration_or_statement]
		replace [id]
			'thePDU
		deconstruct not constraint
			_ [empty]
		
		construct cPDU [id]
			_ [+ "&constrainedPDU"]
		by
			cPDU
	end function

	function parseUserDefinedType mallocName [id] ET [element_type] PDU [id]
		%deconstruct not mallocName
		%	mainpdu
		deconstruct ET
			LONG [id] '^ SHORT [id] TYPE [id] '(SIZE 'DEFINED) OP [opt endian] OPSL [opt slack] POS [opt position_value]
		replace [repeat declaration_or_statement]
			Stmts [repeat declaration_or_statement]
		construct index [number]
			_ [index TYPE "_"]
		construct finalIndex [number]
			index [- 1]
		construct typeToParse [id]
			TYPE [: 1 finalIndex]
		construct pName [id]
			_ [+ "parse"] [+ typeToParse]
		construct getEndianness [id]
			_ [getEndianness ET]
		construct Stmt [repeat declaration_or_statement]
			TYPE SHORT[tolower] ';
			if(!pName(& SHORT[tolower], PDU, 'progname, getEndianness)) {
				%free (mallocName);
				%mallocName = NULL;
				return false;
			}
			mallocName ->SHORT[tolower] = SHORT[tolower]';
		by
			Stmts [. Stmt]
	end function

	function parseUserDefinedTypeOptional mallocName [id] OP [opt scl_additions] LET [list element_type] ET [element_type] PDU [id]
		%deconstruct not mallocName
		%	mainpdu	
		deconstruct ET
			LONG [id] '^ SHORT [id] TYPE [id] '(SIZE 'DEFINED) OPEND [opt endian] OPSL [opt slack] 'OPTIONAL POS [opt position_value]
		deconstruct * [transfer_statement] OP
			'Forward '{ EXISTS( LONG ) '== REST [relational_expression] '} %ID [id] '& NUM [number] '}
		deconstruct not * [transfer_statement] OP
			'Forward '{ EXISTS( LONG ) '== ID [id] '& NUM [number] '}
		%deconstruct *[element_type] LET
		%	ID '^ SHORTMASK [id] TYPEMASK [type]
		replace [repeat declaration_or_statement]
			Stmts [repeat declaration_or_statement]
		construct index [number]
			_ [index TYPE "_"]
		construct finalIndex [number]
			index [- 1]
		construct typeToParse [id]
			TYPE [: 1 finalIndex]
		construct pName [id]
			_ [+ "parse"] [+ typeToParse]
		construct getEndianness [id]
			_ [getEndianness ET]
		construct Stmt [repeat declaration_or_statement]
			if(REST[convertIDToShort] [convertPDUREMAINING] [convertToFullID mallocName]) { %mallocName ->SHORTMASK[tolower] & NUM) {
				mallocName ->SHORT[tolower] = (TYPE *) malloc(sizeof(TYPE));
				if(mallocName ->SHORT[tolower] == NULL) {
					%free (mallocName ->SHORT[tolower]);
					%mallocName ->SHORT[tolower] = NULL;
					return false;
				}
				if(!pName(mallocName ->SHORT[tolower], PDU, 'progname, getEndianness)) {
					free (mallocName ->SHORT[tolower]);
					mallocName ->SHORT[tolower] = NULL;
					return false;
				}
			} else {
				mallocName ->SHORT[tolower] = NULL;
			}
		construct finalStmt [repeat declaration_or_statement]
			Stmt [convertRemaining]
		by
			Stmts [. finalStmt]
	end function

	rule convertRemaining
		replace $ [constant]
			'remaining
		by
			thePDU ->'remaining
	end rule

	function parseUserDefinedTypeOptionalWithNum mallocName [id] OP [opt scl_additions] LET [list element_type] ET [element_type] PDU [id]
		%deconstruct not mallocName
		%	mainpdu	
		deconstruct ET
			LONG [id] '^ SHORT [id] TYPE [id] '(SIZE 'DEFINED) OPEND [opt endian] OPSL [opt slack] 'OPTIONAL POS [opt position_value]
		deconstruct * [transfer_statement] OP
			'Forward '{ EXISTS( LONG ) '== ID [id] '& NUM [number] '}
		deconstruct *[element_type] LET
			ID '^ SHORTMASK [id] TYPEMASK [type]
		replace [repeat declaration_or_statement]
			Stmts [repeat declaration_or_statement]
		construct index [number]
			_ [index TYPE "_"]
		construct finalIndex [number]
			index [- 1]
		construct typeToParse [id]
			TYPE [: 1 finalIndex]
		construct pName [id]
			_ [+ "parse"] [+ typeToParse]
		construct getEndianness [id]
			_ [getEndianness ET]
		construct Stmt [repeat declaration_or_statement]
			if(mallocName ->SHORTMASK[tolower] & NUM) {
				mallocName ->SHORT[tolower] = (TYPE *) malloc(sizeof(TYPE));
				if(mallocName ->SHORT[tolower] == NULL) {
					%free (mallocName ->SHORT[tolower]);
					%mallocName ->SHORT[tolower] = NULL;
					return false;
				}
				if(!pName(mallocName ->SHORT[tolower], PDU, 'progname, getEndianness)) {
					free (mallocName ->SHORT[tolower]);
					mallocName ->SHORT[tolower] = NULL;
					return false;
				}
			} else {
				mallocName ->SHORT[tolower] = NULL;
			}
		by
			Stmts [. Stmt]
	end function

	function doSlacks constraint [repeat declaration_or_statement] ET [element_type]
		replace [repeat declaration_or_statement]
			Stmts [repeat declaration_or_statement]
		deconstruct not constraint
			_ [empty]
		construct slackCheck [repeat declaration_or_statement]
			_ [checkSlack ET] [noSlack ET] [checkSlackOptional ET] [noSlackOptional ET] 
		by
			Stmts [. slackCheck]
	end function

	function checkSlack ET [element_type]
		replace [repeat declaration_or_statement]
			Stmts [repeat declaration_or_statement]
		deconstruct ET
			LONG [id] '^ SHORT [id] TYPE [id] '(SIZE 'DEFINED)  OPEN [opt endian] OPSL [opt slack] POS [opt position_value]	
		deconstruct OPSL
			'SLACK
		construct lengthCheck [repeat declaration_or_statement]
			if(!lengthRemaining(thePDU, (constrainedPDU.len - (constrainedPDU.curPos - 'pos) ) , 'progname)) {
				%fprintf(stderr,"%s: incorrect PDU length or type: %s line: %d\n",progname, __FILE__ , __LINE__);
				return false;
			}	
		construct slack [repeat declaration_or_statement]
			% Skipping slack bytes . . .
			thePDU ->curPos = constrainedPDU.curPos;
			if(!checkSlack(thePDU, constrainedPDU.remaining)) {
				return false;
			}
			%thePDU ->remaining -= (constrainedPDU.len - (thePDU ->'curPos - 'pos) );
		by
			Stmts  [. slack] %[. lengthCheck]
	end function

	function noSlack ET [element_type]
		replace [repeat declaration_or_statement]
			Stmts [repeat declaration_or_statement]
		deconstruct ET
			LONG [id] '^ SHORT [id] TYPE [id] '(SIZE 'DEFINED)  OPEN [opt endian] OPSL [opt slack] POS [opt position_value]	
		deconstruct not OPSL
			'SLACK
		deconstruct not OPSL
			'SLACKMOD4
		construct slack [repeat declaration_or_statement]
			% Ensure slack bytes 
			if(constrainedPDU.remaining != 0) {
				return false;
			}
			thePDU ->curPos += constrainedPDU.len;
		construct lengthCheck [repeat declaration_or_statement]
			if(!lengthRemaining(thePDU, constrainedPDU.len , 'progname)) {
				%fprintf(stderr,"%s: incorrect PDU length or type: %s line: %d\n",progname, __FILE__ , __LINE__);
				return false;
			}
			
		by
			Stmts [. slack] %[. lengthCheck]
	end function

	function checkSlackOptional ET [element_type]
		replace [repeat declaration_or_statement]
			Stmts [repeat declaration_or_statement]
		deconstruct ET
			LONG [id] '^ SHORT [id] TYPE [id] '(SIZE 'DEFINED)  OPEN [opt endian] OPSL [opt slack] 'OPTIONAL POS [opt position_value]	
		deconstruct OPSL
			'SLACK
		construct lengthCheck [repeat declaration_or_statement]
			if(!lengthRemaining(thePDU, (constrainedPDU.len - (constrainedPDU.curPos - 'pos) ) , 'progname)) {
				%fprintf(stderr,"%s: incorrect PDU length or type: %s line: %d\n",progname, __FILE__ , __LINE__);
				return false;
			}
		construct slack [repeat declaration_or_statement]
			% Skipping slack bytes . . .
			thePDU ->curPos = constrainedPDU.curPos;
			if(!checkSlack(thePDU, constrainedPDU.remaining)) {
				return false;
			}
			%thePDU ->remaining -= (constrainedPDU.len - (thePDU ->'curPos - 'pos) );
		by
			Stmts [. slack] %[. lengthCheck] 
	end function

	function noSlackOptional ET [element_type]
		replace [repeat declaration_or_statement]
			Stmts [repeat declaration_or_statement]
		deconstruct ET
			LONG [id] '^ SHORT [id] TYPE [id] '(SIZE 'DEFINED)  OPEN [opt endian] OPSL [opt slack] 'OPTIONAL POS [opt position_value]	
		deconstruct not OPSL
			'SLACK
		deconstruct not OPSL
			'SLACKMOD4
		construct slack [repeat declaration_or_statement]
			% Ensure slack bytes 
			if(constrainedPDU.remaining != 0) {
				return false;
			}
			thePDU ->curPos += constrainedPDU.len;
		construct lengthCheck [repeat declaration_or_statement]
			if(!lengthRemaining(thePDU, constrainedPDU.len , 'progname)) {
				%fprintf(stderr,"%s: incorrect PDU length or type: %s line: %d\n",progname, __FILE__ , __LINE__);
				return false;
			}
		by
			Stmts [. slack] %[. lengthCheck]
	end function

	function doSlackMods ET [element_type]
		replace [repeat declaration_or_statement]
			Stmts [repeat declaration_or_statement]
		construct slackCheck [repeat declaration_or_statement]
			_ [checkSlackMod ET] [checkSlackModOptional ET] 
		by
			Stmts [. slackCheck]
	end function

	function checkSlackMod ET [element_type]
		replace [repeat declaration_or_statement]
			Stmts [repeat declaration_or_statement]
		deconstruct ET
			LONG [id] '^ SHORT [id] TYPE [id] '(SIZE 'DEFINED)  OPEN [opt endian] 'SLACKMOD4 POS [opt position_value]	
		construct pos [id]
			_ [+ "pos"] [+ SHORT]	
		construct lengthCheck [repeat declaration_or_statement]
			if(!lengthRemaining(thePDU, ( ((thePDU ->curPos - pos) '% 4 ? 4 - ((thePDU ->curPos - pos) '% 4) : 0) ) , 'progname)) {
				%fprintf(stderr,"%s: incorrect PDU length or type: %s line: %d\n",progname, __FILE__ , __LINE__);
				return false;
			}
		construct slack [repeat declaration_or_statement]
			% Skipping slack bytes . . .
			%thePDU ->curPos = constrainedPDU.curPos;
			if(!checkSlack(thePDU, ( ((thePDU ->curPos - pos) '% 4 ? 4 - ((thePDU ->curPos - pos) '% 4) : 0) ))) {
				return false;
			}
			%thePDU ->remaining -= ( ((thePDU ->curPos - pos) '% 4 ? 4 - ((thePDU ->curPos - pos) '% 4) : 0) );
		by
			Stmts [. lengthCheck] [. slack] 
	end function

	function checkSlackModOptional ET [element_type]
		replace [repeat declaration_or_statement]
			Stmts [repeat declaration_or_statement]
		deconstruct ET
			LONG [id] '^ SHORT [id] TYPE [id] '(SIZE 'DEFINED)  OPEN [opt endian] 'SLACKMOD4 'OPTIONAL POS [opt position_value]	
		construct pos [id]
			_ [+ "pos"] [+ SHORT]		
		construct lengthCheck [repeat declaration_or_statement]
			if(!lengthRemaining(thePDU, ( ((thePDU ->curPos - pos) '% 4 ? 4 - ((thePDU ->curPos - pos) '% 4) : 0) ) , 'progname)) {
				%fprintf(stderr,"%s: incorrect PDU length or type: %s line: %d\n",progname, __FILE__ , __LINE__);
				return false;
			}	
		construct slack [repeat declaration_or_statement]
			% Skipping slack bytes . . .
			%thePDU ->curPos = constrainedPDU.curPos;
			if(!checkSlack(thePDU, ( ((thePDU ->curPos - pos) '% 4 ? 4 - ((thePDU ->curPos - pos) '% 4) : 0) ))) {
				return false;
			}		
			%thePDU ->curPos += ( ((thePDU ->curPos - pos) '% 4 ? 4 - ((thePDU ->curPos - pos) '% 4) : 0) );
			%thePDU ->remaining -= ( ((thePDU ->curPos - pos) '% 4 ? 4 - ((thePDU ->curPos - pos) '% 4) : 0) );
		by
			Stmts [. lengthCheck] [. slack] 
	end function

	%######################################################%
	%#  End Parse User Defined [element_type] Subsection  #%
	%######################################################%

	%############################################%
	%#  Parse Set Of [element_type] Subsection  #%
	%############################################%

	%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
	%%%%% Recursive Parse Explination %%%%%
	%%%%%   RTPS SUBMESSAGE Example   %%%%%
	%(

	The recursive parse is the mothod to parse and allocate storage
	for any SET OF data types. Since the number of elements of this
	array set that need to be parsed is unknown, an approach like this
	is necessary. This recursive parse will continue parsing new
	messages in the set until it is unable to get a valid result.
	Each message after it is parsed is stored on the stack until
	the full parse is done and we know how many total messages there
	are. Then the correct amount of space can be allocated for the
	entire array and is then stored in the supplied pointer and returned.
	Since the struct for the type decision of any SET OF choices is a
	union, all that is required for the malloc is the number of elements
	needed to be stored in the array as a union allocates space for the
	largest possible element

	In addition this is one area of where there is not a one-to-one
	translation of SCL5 to C code. The recursive parse is an auxiliary
	function used to assist with the parse of the [element_type] as it
	depends on a later type decision rule. The [element_type] itself 
	translates into code to varify the result of the recursive parse

	NOTE: This example uses the RTPS SUBMESSAGE without callback optimization

	Parameters of note:
	int n 		| n is a counter for the total number of elements in the list
	int *size 	| size is an external pointer that is given the value of 
				  of n at the end of the recursion to be saved where required
	
	// Code that calls and deals with the parseSetOf result //

	// Start the recursion here; Value of n is constant 0 since arrays use 0 indexing
	full_rtps->submsg = parseSetOfSUBMESSAGE (thePDU, 0, &size, progname, endianness);
    
	// If the result from the parse is null then it failed
    if (full_rtps->submsg == NULL) {
        return false;
    }

    // Save the count and length of messages
    full_rtps->submsgcount = size;
    full_rtps->submsglength = thePDU->curPos - full_rtps->submsglength;
    
    // If we didn't parse all the submessages properly; Fail parse
    if (thePDU->remaining != 0) {
        return false;
    }

	// parseSetOf function //

	// The function returns a pointer to the array of parsed submessages that has been allocated on the heap
	SUBMESSAGE_RTPS *parseSetOfSUBMESSAGE (PDU *thePDU, int n, int *size, char *progname, uint8_t endianness) {
	    // Current local copy of union struct
	    SUBMESSAGE_RTPS submsg;
	    
		// Attempt to parse a SUBMESSAGE
	    if (!parseSUBMESSAGE (&submsg, thePDU, progname, endianness)) {
	        // If we made it in here then the attempted parse on a submessage failed

	        // If n is 0 then we failed on the first attempted parse and therefore do not have a proper SUMBESSAGE packet
	        // This information is relayed to the main code above by setting the size to 0 to indicate no messages were
	        // parsed and return NULL as the final result so the failed parse will continue to propagate
	        if (n == 0) {
	            *size = 0;
	            return NULL;
	        }

	        // If n was not 0 then we have at least some submessage elements parsed already. This means that the parse
	        // is completed as there are no more valid SUBMESSAGE elements left in the packet. (If the parse ended on
	        // an invalid SUBMESSAGE packet after parsing at least one successfully then the parse will fail in the main 
	        // code above as the remaining data in the PDU will not equal 0) 
	        
			// Declare a new pointer of the return type and allocate it space for the entire amout of parsed messages
	        SUBMESSAGE_RTPS *result = (SUBMESSAGE_RTPS *) malloc ((n) *sizeof(SUBMESSAGE_RTPS));
	        
	        // If for any reason the newly allocated was NULL after the malloc then an internal malloc error occured
	        if (result == NULL) {
	            fprintf (stderr, "%s: internal malloc error file: %s line: %d \n", progname, __FILE__, __LINE__);
	            return NULL;
	        }

	        // Dereference the size value and save it as it would be lost after returning here
	        *size = n;

	        // Begin working down the stack as this is the recursion exit point. Nothing was parsed successfully here
	        // so only the allocated space will need to be returned. Each point lower in the stack will save its parsed
	        // element to the array until it is finally returned to the source call
	        return result;
	    }
	    else {
	    	// If we made it here then the parse of a SUBMESSAGE was successful and must continue by parsing the next element

	    	// Collect the result of the return of the recursion and recursively call the function again. The value of result
	    	// here will be the array with all instances above this stack entry already assigned to array elements
	    	// Note that n is also incremented in the function call here to keep track of the sequence
	        SUBMESSAGE_RTPS *result = parseSetOfSUBMESSAGE (thePDU, n +1, size, progname, endianness);

	        // Assign this parse result to the array element based on its occurance number (n)
	        result[n] = submsg;

	        // Return the array to continue assigning or to the main function if the final occurance
	        return result;
	    }
	}
    
	)%
	%%%%% Recursive Parse Explination %%%%%
	%%%%%   RTPS SUBMESSAGE Example   %%%%%
	%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

	% Function to generate the C parse code for an [element_type]
	% that is a SET OF type with constrained size and a termination constraint
	function parseSetOfTypeDecisionTerminateConstrained mallocName [id] RuleName [id]  OP [opt scl_additions] ET [element_type]
		% Must be a set of with constrained size
		deconstruct ET
			LONG [id] '^ SHORT [id] 'SET 'OF TYPE [id] '(SIZE 'CONSTRAINED)
		deconstruct OP
			EN [opt encoding_grammar_indicator] SZ [opt size_markers_block] TR [opt transfer_rules_block] CON [opt constraints_block] 
		% Must have a terminate constraint on itself requiring it to terminate in a specific type
		deconstruct * [transfer_statement] TR
			'Forward '{ 'TERMINATE ( LONG ) '== RULE [id] '}
		% Cannot have any callback optimization
		deconstruct not * [transfer_statement] TR
			'Callback '@ UNUSED [id]
		import ALLRULES [repeat rule_definition]	% Load the copy of all the rules
		% There must be a type rule defining the type this set of must terminate with
		deconstruct * [rule_definition] ALLRULES
			RULE '^ SHORTID [id] ANN [opt annotation] '::= TP [type] OPTSCL [opt scl_additions]		
		replace [repeat declaration_or_statement]
			Stmts [repeat declaration_or_statement]
		% Convert the long verion of TYPE to a short (TYPE_PROTOCOL to TYPE)
		construct index [number]
			_ [index TYPE "_"]	% The location of the occurance of "_" in the TYPE [id]
		construct finalIndex [number]
			index [- 1]	% The location of the character one spot before the "_"
		construct typeToParse [id]
			TYPE [: 1 finalIndex]	% The text from the start of TYPE to before the "_"
		% Name of the function for the recursive parse; "_0" is added to the name to indicate it is optimized
		construct functionName [id]
			_ [+ "parseSetOf"] [+ typeToParse] [+ "_O"]
		% Name of the function that will parse the type decision
		construct parseFunctionName [id]
			_ [+ "parse"] [+ typeToParse]
		import FunctionDeclarations [repeat rule_definition]	% Load the set of function header definitions
		% Create the function header definition for the recursive parse; This is required as the function will
		% be called before its function body is added to the code as auxiliary functions are added at the end
		% of the translated C code
		construct setDeclaration [rule_definition]
			TYPE * functionName (PDU * thePDU, int n, int *size, char *progname, uint8_t endianness);
		export FunctionDeclarations
			FunctionDeclarations [. setDeclaration]	% Save the function header definition
		import AuxFunctions [repeat rule_definition]	% Load the set of auxiliary functions
		% The value of the type that must terminate the SET OF stream
		construct terminator [id]
			RULE [+ "_VAL"]
		% For information on the recursive parse; See the note at the start of this section
		
		% This specifc recursive parse is optimized because the termination value is known
		% so we know the parse is successful when we find that last value
		construct recursiveParse [rule_definition]
			TYPE * functionName (PDU *thePDU, int n, int *size, char *progname, uint8_t endianness) {
				TYPE SHORT[tolower];
				if( parseFunctionName ('& SHORT[tolower], thePDU, 'progname, endianness)) {
					% Parse of an element was successsful
					if(SHORT[tolower] .'type == terminator) {
						% The parse only succeeds if it ends in the terminator value; Otherwise
						% it has failed so do not allocate space
						TYPE *result = (TYPE *) malloc((n+1) * sizeof(TYPE));
						if (result == NULL) {
							return NULL;
						}
						*size = n+1;
						result '[n'] = SHORT[tolower];
						return result;
					} else {
						% Keep parsing because we have not reached the termination value yet
						TYPE *result = functionName (thePDU, n+1, size, 'progname, endianness);
						if(result != NULL) {
							result '[n'] = SHORT[tolower];
						}
							
						return result;
					}
				} else {
					% Parse of an element has failed so whole parse has failed as it has not ended
					% in the proper element
					if(n == 0) {
						*size = 0;
						return NULL;
					} else {
						return NULL;
					}
				}
			}
		export AuxFunctions
			AuxFunctions [. recursiveParse]	% Save the recursive parse to be added to the C code
		% Generate the one-to-one translated C code related to starting and finishing the parse
		% of the SET OF [element_type]
		construct addedStmts [repeat declaration_or_statement]
			_ [checkForwardLengthConstraint mallocName functionName LONG SHORT OP]
		by
			Stmts [. addedStmts]	% Save the generated C code
	end function

	% Function to generate the C parse code for an [element_type]
	% that is a SET OF type with constrained size and a cardinality constraint
	function parseSetOfTypeDecisionCardinalityConstrained mallocName [id] RuleName [id]  OP [opt scl_additions] LET [list element_type] ET [element_type]
		% Must be a set of with constrained size
		deconstruct ET
			LONG [id] '^ SHORT [id] 'SET 'OF TYPE [id] '(SIZE 'CONSTRAINED)
		deconstruct OP
			EN [opt encoding_grammar_indicator] SZ [opt size_markers_block] TR [opt transfer_rules_block] CON [opt constraints_block] 
		% Cannot have any callback optimization
		deconstruct not * [transfer_statement] TR
			'Callback '@ UNUSED [id]
		% Must have a cardinality constraint on itself requiring it to have a certain number of elements in the set
		deconstruct * [transfer_statement] TR
			'Forward '{ 'CARDINALITY ( LONG ) '== RULE [id] '}
		import ALLRULES [repeat rule_definition]	% Load the copy of all the rules
		% There must be an [element_type] in the list that hold the cardinality value
		deconstruct * [element_type] LET
			RULE '^ SHORTCARD [id] TPCARD [type]
		replace [repeat declaration_or_statement]
			Stmts [repeat declaration_or_statement]
		% Convert the long verion of TYPE to a short (TYPE_PROTOCOL to TYPE)
		construct index [number]
			_ [index TYPE "_"]	% The location of the occurance of "_" in the TYPE [id]
		construct finalIndex [number]
			index [- 1]	% The location of the character one spot before the "_"
		construct typeToParse [id]
			TYPE [: 1 finalIndex]	% The text from the start of TYPE to before the "_"
		% Name of the function for the recursive parse
		construct functionName [id]
			_ [+ "parseSetOf"] [+ typeToParse]
		% Name of the function that will parse the type decision
		construct parseFunctionName [id]
			_ [+ "parse"] [+ typeToParse]
		import FunctionDeclarations [repeat rule_definition]	% Load the set of function header definitions
		% Create the function header definition for the recursive parse; This is required as the function will
		% be called before its function body is added to the code as auxiliary functions are added at the end
		% of the translated C code
		construct  setDeclaration [rule_definition]
			TYPE * functionName (PDU * thePDU, int size, char *progname, uint8_t endianness);
		export FunctionDeclarations
			FunctionDeclarations [. setDeclaration]	% Save the function header definition
		import AuxFunctions [repeat rule_definition]	% Load the set of auxiliary functions
		% A C evaluatable expression to get the cardinality value for the constraint
		construct cardinality [constant]
			mallocName ->SHORTCARD[tolower]
		% For information on the recursive parse; See the note at the start of this section
		
		% This specifc recursive parse is written with a for loop as per the cardinality
		% constraint we know how many elements to expect
		construct recursiveParse [rule_definition]
			TYPE * functionName (PDU *thePDU, int size, char *progname, uint8_t endianness) {
				% We already know the size so allocate that amount of space
				TYPE *result = (TYPE *) malloc( size * sizeof(TYPE));
				if (result == NULL) {
					return NULL;
				}

				% Parse the required number of elements
				for (int i = 0; i < size; ++i) {
					TYPE SHORT[tolower];
					if( parseFunctionName ('& SHORT[tolower], thePDU, 'progname, endianness) )
						% Message parse successful; Save result
						result'[i'] = SHORT[tolower];
					else
						% Message parse unsuccessful; Return NULL (fail)
						return NULL;
				}
				% Entire parse was successful; Return result
				return result;
			}
		export AuxFunctions
			AuxFunctions [. recursiveParse]	% Save the recursive parse to be added to the C code
		construct freeMain [repeat declaration_or_statement]
			_ [checkMain mallocName SHORT]	% Generate the NULL value check for the allocated memory variable
		%% Generate the one-to-one translated C code related to starting and finishing the parse
		%% of the SET OF [element_type]
		% The C code to start the parse of the SET OF element
		construct newStmts [repeat declaration_or_statement]
			% The count of elements will always be the cardinality
			mallocName -> SHORT[tolower][+ "count"] = cardinality;
			% Calculate the initial element length
			mallocName -> SHORT[tolower][+ "length"] = thePDU ->curPos; 
			% Do the parse and save the value to the struct member
			mallocName -> SHORT[tolower] = functionName(thePDU, cardinality, 'progname, endianness);
		% The C code to finish the parse of the SET OF element
		construct endStmts [repeat declaration_or_statement]	
			% Calculate and save the length of elements parsed to the struct instance
			mallocName -> SHORT[tolower][+ "length"] = thePDU ->curPos - mallocName -> SHORT[tolower][+ "length"]; 
		by
			Stmts [. newStmts] [. freeMain] [. endStmts]	% Save the generated C code
	end function

	% Function to generate the C parse code for an [element_type]
	% that is a SET OF type with no special constraints
	function parseSetOfTypeDecision mallocName [id] RuleName [id]  OP [opt scl_additions] ET [element_type]
		% Must be a set of with constrained size
		deconstruct ET
			LONG [id] '^ SHORT [id] 'SET 'OF TYPE [id] '(SIZE 'CONSTRAINED)
		deconstruct OP
			EN [opt encoding_grammar_indicator] SZ [opt size_markers_block] TR [opt transfer_rules_block] CON [opt constraints_block] 
		% Cannot have a termination constraint
		deconstruct not * [transfer_statement] TR
			'Forward '{ 'TERMINATE ( LONG ) '== RULE [id] '}
		% Cannot have a cardinality constraint
		deconstruct not * [transfer_statement] TR
			'Forward '{ 'CARDINALITY ( LONG ) '== RULE [id] '}
		% Cannot have any callback optimization
		deconstruct not * [transfer_statement] TR
			'Callback '@ UNUSED [id]
		replace [repeat declaration_or_statement]
			Stmts [repeat declaration_or_statement]
		% Convert the long verion of TYPE to a short (TYPE_PROTOCOL to TYPE)
		construct index [number]
			_ [index TYPE "_"]	% The location of the occurance of "_" in the TYPE [id]
		construct finalIndex [number]
			index [- 1]	% The location of the character one spot before the "_"
		construct typeToParse [id]
			TYPE [: 1 finalIndex]	% The text from the start of TYPE to before the "_"
		% Name of the function for the recursive parse
		construct functionName [id]
			_ [+ "parseSetOf"] [+ typeToParse]
		% Name of the function that will parse the type decision
		construct parseFunctionName [id]
			_ [+ "parse"] [+ typeToParse]
		import FunctionDeclarations [repeat rule_definition]	% Load the set of function header definitions
		% Create the function header definition for the recursive parse; This is required as the function will
		% be called before its function body is added to the code as auxiliary functions are added at the end
		% of the translated C code
		construct setDeclaration [rule_definition]
			TYPE * functionName (PDU * thePDU, int n, int *size, char *progname, uint8_t endianness);
		export FunctionDeclarations
			FunctionDeclarations [. setDeclaration]	% Save the function header definition
		import AuxFunctions [repeat rule_definition]	% Load the set of auxiliary functions
		% For information on the recursive parse; See the note at the start of this section
		
		% This specifc recursive parse is the standard base case; It is for
		% the case described in the initial note in detail
		construct recursiveParse [rule_definition]
			TYPE * functionName (PDU * thePDU, int n, int *size, char *progname, uint8_t endianness) {
				TYPE SHORT[tolower];

				if (! parseFunctionName('& SHORT[tolower], thePDU, 'progname, endianness)){
					if(n == 0) { 
						*'size = 0; 
						return NULL;
					}
					TYPE * result = (TYPE *)malloc('(n) * sizeof(TYPE));
					if( result == NULL) {
						fprintf(stderr, err, 'progname, __FILE__, __LINE__);
						return NULL;
					}

					*'size = n;
					return result;

				} else {
					TYPE * result = functionName(thePDU,n+1,size, 'progname, endianness);
					result '[n'] = SHORT[tolower];
					return result;
				}
			}
		export AuxFunctions
			AuxFunctions [. recursiveParse]	% Save the recursive parse to be added to the C code
		% Generate the one-to-one translated C code related to starting and finishing the parse
		% of the SET OF [element_type]; Also check for an end constraint on this [element_type]
		construct addedStmts [repeat declaration_or_statement]
			_ [checkForwardLengthConstraint mallocName functionName LONG SHORT OP]
				[checkEndConstraint TR LONG]
		by
			Stmts [. addedStmts]	% Save the generated C code
	end function

	% Function to generate the C parse code for an [element_type]
	% that is a SET OF type with callback optimization
	function parseAnnotatedSetOfTypeDecision mallocName [id] RuleName [id]  OP [opt scl_additions] ET [element_type]
		% Must be a set of with constrained size
		deconstruct ET
			LONG [id] '^ SHORT [id] 'SET 'OF TYPE [id] '(SIZE 'CONSTRAINED)
		deconstruct OP
			EN [opt encoding_grammar_indicator] SZ [opt size_markers_block] TR [opt transfer_rules_block] CON [opt constraints_block] 
		% Cannot have a termination constraint
		deconstruct not * [transfer_statement] TR
			'Forward '{ 'TERMINATE ( LONG ) '== RULE [id] '}
		% Cannot have a cardinality constraint
		deconstruct not * [transfer_statement] TR
			'Forward '{ 'CARDINALITY ( LONG ) '== RULE [id] '}
		% Must have a callback optimization [callback_annotation]
		deconstruct * [transfer_statement] TR
			'Callback '@ UNUSED [id]
		replace [repeat declaration_or_statement]
			Stmts [repeat declaration_or_statement]
		% Convert the long verion of TYPE to a short (TYPE_PROTOCOL to TYPE)
		construct index [number]
			_ [index TYPE "_"]	% The location of the occurance of "_" in the TYPE [id]
		construct finalIndex [number]
			index [- 1]	% The location of the character one spot before the "_"
		construct typeToParse [id]
			TYPE [: 1 finalIndex]	% The text from the start of TYPE to before the "_"
		% Name of the function for the recursive parse
		construct functionName [id]
			_ [+ "parseSetOf"] [+ typeToParse]
		% Name of the function that will parse the type decision
		construct parseFunctionName [id]
			_ [+ "parse"] [+ typeToParse]
		import FunctionDeclarations [repeat rule_definition]	% Load the set of function header definitions
		% Create the function header definition for the recursive parse; This is required as the function will
		% be called before its function body is added to the code as auxiliary functions are added at the end
		% of the translated C code
		construct  setDeclaration [rule_definition]
			TYPE * functionName (RuleName * RuleName[tolower], PDU * thePDU, int n, int *size, char *progname, uint8_t endianness);
		export FunctionDeclarations
			FunctionDeclarations [. setDeclaration]	% Save the function header definition
		import AuxFunctions [repeat rule_definition]	% Load the set of auxiliary functions
		% For information on the recursive parse; See the note at the start of this section
		
		% This specifc recursive parse is for a callback optimization
		% In the callback optimization, no array needs to be constructed
		% as each message will be used with a callback directly after
		% parsing and will never be needed again internally afterwards
		construct recursiveParse [rule_definition]
			TYPE * functionName (RuleName * RuleName[tolower], PDU * thePDU, int n, int *size, char *progname, uint8_t endianness) {
				TYPE SHORT[tolower];
				if (! parseFunctionName(RuleName[tolower], '& SHORT[tolower], thePDU, 'progname, endianness)){
					if(n == 0) { 
						*'size = 0; 
						return NULL;
					}
					*'size = n;
					return NULL;

				} else {
					TYPE * result = functionName(RuleName[tolower], thePDU,n+1,size, 'progname, endianness);
					result = '& SHORT[tolower];
					return result;
				}
			}
		export AuxFunctions
			AuxFunctions [. recursiveParse]	% Save the recursive parse to be added to the C code
		% Generate the one-to-one translated C code related to starting and finishing the parse
		% of the SET OF [element_type]; Also check for an end constraint on this [element_type]
		construct addedStmts [repeat declaration_or_statement]
			_ [checkForwardLengthConstraint mallocName functionName LONG SHORT OP]
				[checkEndConstraint TR LONG]
		by
			Stmts [. addedStmts]	% Save the generated C code
	end function

	%% Check Constraint Section %%

	% Check if there are any length constraints on the SET OF [element_type]
	% and generate any required code to both verify any of those constraints
	% and save the parsed values and supporting data
	function checkForwardLengthConstraint mallocName [id] functionName [id] LONG [id] SHORT [id] OP [opt scl_additions]
		replace [repeat declaration_or_statement]
			Stmts [repeat declaration_or_statement]
		by
			Stmts [withLengthConstraint mallocName functionName LONG SHORT OP]
					[withoutLengthConstraint mallocName functionName LONG SHORT OP]
					[withoutLengthConstraintAnnotatedCallback mallocName functionName LONG SHORT OP]
	end function

	% Function to generate the end of SET OF parse code. In this case, there
	% is a length constraint on the SET OF [element_type]. Additionally since
	% there is a length constraint there cannot be a callback on this rule
	function withLengthConstraint mallocName [id] functionName [id] LONG [id] SHORT [id] OP [opt scl_additions]
		deconstruct OP
			EN [opt encoding_grammar_indicator] SZ [opt size_markers_block] TR [opt transfer_rules_block] CON [opt constraints_block] 
		% Must have a length constraint on the SET OF LONG [id]
		deconstruct * [transfer_statement] TR
			'Forward '{ 'LENGTH ( LONG ) '== REST [relational_expression] '}
		construct convertedREST [relational_expression]
			REST [replacePDULENGTH]	% If REST references the PDU length replace it with an evaluatable statement
		replace [repeat declaration_or_statement]
			Stmts [repeat declaration_or_statement]
		construct freeMain [repeat declaration_or_statement]
			_ [checkMain mallocName SHORT]	% Generate the NULL value check for the allocated memory variable
		% Create and allocate a constrainedPDU to follow the length constraints
		construct newStmts [repeat declaration_or_statement]
			% Variable to hold the number of parse elements
			int size = '0;
			% Allocate the constrainedPDU
			PDU *constrainedPDU;
			constrainedPDU = (PDU*)malloc(sizeof(PDU));
			if (constrainedPDU == NULL){
				% Internal malloc error
				return false;
			}
			% Set the constrainedPDU values to prepare for parse
			constrainedPDU ->len = thePDU ->len;
			constrainedPDU ->watermark= thePDU ->watermark;
			constrainedPDU ->curPos = thePDU ->curPos;
			constrainedPDU ->data = thePDU ->data;
			constrainedPDU ->remaining = convertedREST;
			% Set the initial message element length and do the setof parse
			mallocName -> SHORT[tolower][+ "length"] = thePDU ->curPos; 
			mallocName -> SHORT[tolower] = functionName(constrainedPDU, '0 , &size, 'progname, endianness);

		% C code to save the values supporting the SET OF parse to the struct members
		construct endStmts [repeat declaration_or_statement]
			% Save the number of elements
			mallocName -> SHORT[tolower][+ "count"] = size;
			% Set the current position in thePDU to the proper value
			thePDU ->curPos = constrainedPDU ->curPos;
			% Save the length of the submessages
			mallocName -> SHORT[tolower][+ "length"] = thePDU ->curPos - mallocName -> SHORT[tolower][+ "length"]; 
			% Free the constrainedPDU as it is no longer required and set to null
			free(constrainedPDU);
			constrainedPDU = NULL;
		by 
			Stmts [. newStmts] [. freeMain] [. endStmts]	% Append all the C code
	end function

	% Replace a PDULENGTH terminal with the referencable
	% field thePDU->len which can be evaluated in C
	rule replacePDULENGTH
		replace $ [primary]
			'PDULENGTH
		construct RP [referencable_primaries]
			'thePDU '-> 'len
		by
			RP
	end rule

	% Function to generate the end of SET OF parse code. In this case, there
	% is no length constraint on the SET OF [element_type] and there is no
	% annotated callback
	function withoutLengthConstraint mallocName [id] functionName [id] LONG [id] SHORT [id] OP [opt scl_additions]
		deconstruct OP
			EN [opt encoding_grammar_indicator] SZ [opt size_markers_block] TR [opt transfer_rules_block] CON [opt constraints_block] 
		% Must have no length constraint on the SET OF [id]
		deconstruct not * [transfer_statement] TR
			'Forward '{ 'LENGTH ( LONG ) '== REST [relational_expression] '}
		% Must have no annotated callback optimization
		deconstruct not * [transfer_statement] TR
			'Callback '@ TYPE [id]
		replace [repeat declaration_or_statement]
			Stmts [repeat declaration_or_statement]
		construct freeMain [repeat declaration_or_statement]
			_ [checkMain mallocName SHORT]	% Generate the NULL value check for the allocated memory variable
		% The C code to start the parse of the SET OF element
		construct newStmts [repeat declaration_or_statement]
			% Counter variable for the number of parsed elements
			int size = '0;
			% Calculate the initial element length
			mallocName -> SHORT[tolower][+ "length"] = thePDU ->curPos; 
			% Do the parse and save the value to the struct member
			mallocName -> SHORT[tolower] = functionName(thePDU, '0 , &size, 'progname, endianness);
		% The C code to finish the parse of the SET OF element
		construct endStmts [repeat declaration_or_statement]
			% Save the count of elements parsed to the struct instance
			mallocName -> SHORT[tolower][+ "count"] = size;		
			% Calculate and save the length of elements parsed to the struct instance
			mallocName -> SHORT[tolower][+ "length"] = thePDU ->curPos - mallocName -> SHORT[tolower][+ "length"]; 
		by
			Stmts [. newStmts] [. freeMain] [. endStmts]	% Save the C code in the correct order
	end function

	% Function to generate the end of SET OF parse code. In this case, there
	% is no length constraint on the SET OF [element_type] and there is an
	% annotated callback optimization
	function withoutLengthConstraintAnnotatedCallback mallocName [id] functionName [id] LONG [id] SHORT [id] OP [opt scl_additions]
		deconstruct OP
			EN [opt encoding_grammar_indicator] SZ [opt size_markers_block] TR [opt transfer_rules_block] CON [opt constraints_block] 
		% Must have no length constraint on the SET OF [id]
		deconstruct not * [transfer_statement] TR
			'Forward '{ 'LENGTH ( LONG ) '== REST [relational_expression] '}
		% Must have an annotated callback optimization; This means that the
		% struct for this rule does not store the pointer for the SET OF array,
		% it instead must be created locally
		deconstruct * [transfer_statement] TR
			'Callback '@ TYPE [id]
		replace [repeat declaration_or_statement]
			Stmts [repeat declaration_or_statement]
		construct freeMain [repeat declaration_or_statement]
			_ [checkMainAnnotatedCallback mallocName SHORT]	% Generate the NULL value check for the allocated memory variable
		% The C code to start the parse of the SET OF element
		construct newStmts [repeat declaration_or_statement]
			% Counter variable for the number of parsed elements
			int size = '0;
			% Calculate the initial element length
			mallocName -> SHORT[tolower][+ "length"] = thePDU ->curPos; 
			% Create a local variable to hold the result as it is not stored in a struct
			TYPE * SHORT[tolower];
			SHORT[tolower] = NULL;
			% Do the parse and save the value to the local variable
			SHORT[tolower] = functionName(mallocName, thePDU, '0 , &size, 'progname, endianness);
		% No endStmts as the values are saved elsewhere in this version
		by
			Stmts [. newStmts] [. freeMain]
	end function

	% Function to generate the required null check code
	% depending if this is the main parse function not
	function checkMainAnnotatedCallback mallocName [id] SHORT [id]
		replace [repeat declaration_or_statement]
			decl [repeat declaration_or_statement]
		by
			decl [mainFreeAnnotatedCallback mallocName SHORT] [notMainFreeAnnotatedCallback mallocName SHORT]
	end function

	% Function to generate the null check code for the
	% main parse function when it has an annotated callback.
	% This must free the allocated space before failing the 
	% parse to prevent memory leaks
	function mainFreeAnnotatedCallback mallocName [id] SHORT [id]
		replace [repeat declaration_or_statement]
			decl [repeat declaration_or_statement]
		% The mallocName is mainpdu intidating this is the main parse
		deconstruct mallocName
			'mainpdu
		import freeName [id]
		% If the parsed allocated value is NULL then its parse
		% failed; Must free it before failing the parse
		% Since it is the annotated callback version the SHORT
		% is not stored in a struct
		construct NullCheck [repeat declaration_or_statement]
			if(SHORT[tolower] == NULL) {
				freeName(mallocName);
				return false;		
			}
		by
			decl [. NullCheck]
	end function

	% Function to generate the null check code for any
	% location that is not the main parse function when 
	% it has an annotated callback. Since it is not the 
	% main parse then nothing must be freed
	function notMainFreeAnnotatedCallback mallocName [id] SHORT [id]
		replace [repeat declaration_or_statement]
			decl [repeat declaration_or_statement]
		% The mallocName is not mainpdu indicating it is not main parse
		deconstruct not mallocName
			'mainpdu
		import freeName [id]
		% If the parsed allocated value is NULL then fail
		% the parse. Since it is the annotated callback
		% version the SHORT is not stored in a struct
		construct NullCheck [declaration_or_statement]
			if(SHORT[tolower] == NULL) {
				return false;		
			}
		by
			decl [. NullCheck]
	end function

	% Check if there is an end constraint on the rule
	% and generate the C code to check it
	function checkEndConstraint TR [opt transfer_rules_block] LONG [id]
		deconstruct * [transfer_statement] TR
			'Forward '{ 'END ( LONG ) '}
		replace [repeat declaration_or_statement]
			Stmts [repeat declaration_or_statement]
		% End constraint states that the [element_type]
		% must end the packet; It must have no space remaining
		construct checkEnd [repeat declaration_or_statement]
			if(thePDU ->'remaining != 0) { 
				return false;
			}
		by
			Stmts [. checkEnd]
	end function

	%% End Check Constraint Section %%

	%% Check Free Section %%

	% Function to generate the required null check code
	% depending if this is the main parse function not
	function checkMain mallocName [id] SHORT [id]
		replace [repeat declaration_or_statement]
			decl [repeat declaration_or_statement]
		by
			decl [mainFree mallocName SHORT] [notMainFree mallocName SHORT]
	end function

	% Function to generate the null check code for the
	% main parse function. This must free the allocated
	% space before failing the parse to prevent memory leaks
	function mainFree mallocName [id] SHORT [id]
		replace [repeat declaration_or_statement]
			decl [repeat declaration_or_statement]
		% The mallocName is mainpdu intidating this is the main parse
		deconstruct mallocName
			'mainpdu
		import freeName [id]
		% If the parsed allocated value is NULL then its parse
		% failed; Must free it before failing the parse
		construct NullCheck [repeat declaration_or_statement]
			if(mallocName -> SHORT[tolower] == NULL) {
				freeName(mallocName);
				return false;		
			}
		by
			decl [. NullCheck]	% Save the statements
	end function

	% Function to generate the null check code for any
	% location that is not the main parse function. Since
	% it is not the main parse then nothing must be freed
	function notMainFree mallocName [id] SHORT [id]
		replace [repeat declaration_or_statement]
			decl [repeat declaration_or_statement]
		% The mallocName is not mainpdu indicating it is not main parse
		deconstruct not mallocName
			'mainpdu
		import freeName [id]
		% If the parsed allocated value is NULL then fail
		% the parse
		construct NullCheck [declaration_or_statement]
			if(mallocName -> SHORT[tolower] == NULL) {
				return false;		
			}
		by
			decl [. NullCheck]
	end function

	%% End Check Free Section %%

	%################################################%
	%#  End Parse Set Of [element_type] Subsection  #%
	%################################################%

% Check and follow back constraints

% Check if there are any endianness constraints on the
% [element_type] and generate the C code to evaluate them
function checkEndiannessConstraints RuleName [id] ET [element_type] OP [opt scl_additions] 
	replace [repeat declaration_or_statement]
		Stmts [repeat declaration_or_statement]
	by
		Stmts [changeEndianness RuleName ET OP]
end function

% Generate a statement to save the endianness value if
% the constraint is for the current [element_type] 
function changeEndianness RuleName [id] ET [element_type] OP [opt scl_additions] 
	% Must have an endianness constraint
	deconstruct * [transfer_statement] OP
		'Forward '{ 'ENDIANNESS '== ID [id] '& NUM [number] '}
	% Endianness constraint must be on the current [element_type]
	deconstruct ET
		ID '^ SHORT [id] TYPE [type]
	% Generate a statement to save the endianness value
	% as according to the constraint
	construct Stmt [declaration_or_statement]
		'endianness = RuleName[tolower] '->SHORT[tolower] '& NUM ;
	replace [repeat declaration_or_statement]
		Stmts [repeat declaration_or_statement]
	by
		Stmts [. Stmt]
end function

% Check all the back constraints once the parse of the
%  [element_type] is complete
function checkBackConstraints mallocName [id] RuleName [id] ET [element_type] OP [opt scl_additions] 
	replace [repeat declaration_or_statement]
		Stmts [repeat declaration_or_statement]
	construct RTR [repeat transfer_statement]
		_ [^ OP]	% Extract a copy of all the constraints
	by
		% Check each [transfer_statement] for if it is a back constraint and if so generate code
		Stmts [checkNormalBackConstraints mallocName RuleName ET each RTR]
end function

% Generate C code to check all the back constraints that
% apply to the current [element_type]
function checkNormalBackConstraints mallocName [id] RuleName [id] ET [element_type] TR [transfer_statement] 
	% Cannot be the main PDU
	deconstruct not mallocName
		mainpdu
	% Current [transfer_statement] must be a back constraint
	deconstruct TR
		'Back '{ OR [or_expression] '} 
	construct IDS [repeat id]
		_ [^ OR]	% Extract all the [id]'s from the back constraint
	% Get the first [id] from the extracted
	deconstruct IDS
		ID [id] REST [repeat id]
	% The [element_type] must contain the [id] from the back constraint
	deconstruct ET
		ID '^ SHORT [id] TYPE [type]
	construct ShortEXP [or_expression]
		OR [convertStringlitToHex] [createShortExpression]	% convertStringlitToHex and then convert the
															% LONGs into their SHORT forms
	construct ShortIDS [repeat id]
		_ [^ ShortEXP]	% Extract a copy of all the new SHORT [id]'s
	% Get the fisrt SHORT [id] from the extracted
	deconstruct ShortIDS
		ShortID [id] ShortREST [repeat id]
	% Generate an expression that can be evaluated for the SHORT
	construct finalEXP [or_expression]
		ShortEXP [modifyShortExpression ShortID RuleName] 
	% Generated code to fail the parse if the back constraint is not met
	construct Stmt [repeat declaration_or_statement]
		if(!(finalEXP)) {
			return false;
		}
	replace [repeat declaration_or_statement]
		Stmts [repeat declaration_or_statement]
	by
		Stmts [. Stmt]	% Save the generated code
end function

rule convertStringlitToHex
    replace $ [primary]
        S [charlit]
    construct SLen [number]
        _ [# S] [+ 1]	% Length of the [charlit] increased by 1
    where
    	SLen [> 2]	% Calculated SLen must be greater than 2
    construct HexNum [id]
       _ [unquote ''0x']
         [addEachChar S SLen '1]
   by
      HexNum
end rule

function addEachChar S [charlit] Slen [number] i [number]
    where
       i [< Slen]
    construct E [number]
       i [+ 1]
    construct C [charlit]
    	S [: i i]
    	  [doLookup]
    replace [id]
        N [id]
    by
        N [+ C] [addEachChar S Slen E]
end function

function doLookup
	construct Tbl [repeat HexPair]
		''R' ''52' ''T' ''54' ''P' ''50' ''S' ''53' ''X' ''58'
    replace [charlit]
        C [charlit]
    deconstruct * [HexPair] Tbl
        C N [charlit]
    by
      N
end function 

% Function to modify a LONG [id] and convert it
% to its SHORT form in lowercase
rule createShortExpression
	replace $ [id]
		ID [id]
	construct index [number]
		_ [index ID "_"]	% Location of the first "_" in ID
	construct finalIndex [number]
		index [- 1]	% Location before the first "_"
	construct finalID [id]
		ID [: 1 finalIndex]	% The text from the start of TYPE to before the "_"
	by 
		finalID[tolower]	% The SHORT text in lowercase
end rule

% Function to generate an expression that can be evaluated
% for the value of the SHORT 
rule modifyShortExpression ShortID [id] RuleName [id]
	replace $ [referencable_primaries]
		ID [referencable_primaries]
	deconstruct ID
		ShortID
	by
		RuleName[tolower]'->ShortID
end rule

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%  End Parse [list element_type] Section  %%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%  Check Endianness Section  %%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

% Function to determine whether an [element_type]
% is BIG or LITTLE endian. A different rule is
% used to check each form of [element_type] and only
% the correct option will pass and change the endian
% value
function getEndianness ET [element_type]
	replace [id]
		ID [id]
	% Initial value until the BIG or LITTLE is found
	construct endian [id]
		'endianness
	by
		endian [checkSizeBasedTypeBIG ET]
					[checkSizeBasedTypeLITTLE ET]
					[checkIntegerTypeBIG ET]
					[checkIntegerTypeLITTLE ET]
					[checkRealTypeBIG ET]
					[checkRealTypeLITTLE ET]
					[checkOctetStringBIG ET]
					[checkOctetStringLITTLE ET]
end function

% Determine that a user defined, sized based element is BIGENDIAN
function checkSizeBasedTypeBIG ET [element_type]
	deconstruct ET
		LONG [id] '^ SHORT [id] TYPE [id] SZ [size_constraint] OP [opt endian] POS [opt position_value]
	deconstruct OP
		'BIGENDIAN
	replace [id]
		ID [id]
	by
		'BIGENDIAN
end function

% Determine that a user defined, size based element is LITTLEENDIAN
function checkSizeBasedTypeLITTLE ET [element_type]
	deconstruct ET
		LONG [id] '^ SHORT [id] TYPE [id] SZ [size_constraint] OP [opt endian] POS [opt position_value]
	deconstruct OP
		'LITTLEENDIAN
	replace [id]
		ID [id]
	by
		'LITTLEENDIAN
end function

% Determine that an integer element is BIGENDIAN
function checkIntegerTypeBIG ET [element_type]
	deconstruct ET
		LONG [id] '^ SHORT [id] 'INTEGER SZ [size_constraint] OP [opt endian] POS [opt position_value]
	deconstruct OP
		'BIGENDIAN
	replace [id]
		ID [id]
	by
		'BIGENDIAN
end function

% Determine that an integer element is LITTLEENDIAN
function checkIntegerTypeLITTLE ET [element_type]
	deconstruct ET
		LONG [id] '^ SHORT [id] 'INTEGER SZ [size_constraint] OP [opt endian] POS [opt position_value]
	deconstruct OP
		'LITTLEENDIAN
	replace [id]
		ID [id]
	by
		'LITTLEENDIAN
end function

% Determine that a real element is BIGENDIAN
function checkRealTypeBIG ET [element_type]
	deconstruct ET
		LONG [id] '^ SHORT [id] 'REAL SZ [size_constraint] OP [opt endian] POS [opt position_value]
	deconstruct OP
		'BIGENDIAN
	replace [id]
		ID [id]
	by
		'BIGENDIAN
end function

% Determine that a real element is LITTLEENDIAN
function checkRealTypeLITTLE ET [element_type]
	deconstruct ET
		LONG [id] '^ SHORT [id] 'REAL SZ [size_constraint] OP [opt endian] POS [opt position_value]
	deconstruct OP
		'LITTLEENDIAN
	replace [id]
		ID [id]
	by
		'LITTLEENDIAN
end function

% Determine that an octet string is BIGENDIAN
function checkOctetStringBIG ET [element_type]
	deconstruct ET
		LONG [id] '^ SHORT [id] 'OCTET 'STRING SZ [opt size_constraint] OP [opt endian] OPSL [opt slack] POS [opt position_value]
	deconstruct OP
		'BIGENDIAN
	replace [id]
		ID [id]
	by
		'BIGENDIAN
end function

% Determine that an octet string is LITTLEENDIAN
function checkOctetStringLITTLE ET [element_type]
	deconstruct ET
		LONG [id] '^ SHORT [id] 'OCTET 'STRING SZ [opt size_constraint] OP [opt endian] OPSL [opt slack] POS [opt position_value]
	deconstruct OP
		'LITTLEENDIAN
	replace [id]
		ID [id]
	by
		'LITTLEENDIAN
end function

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%  End Check Endianness Section  %%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

% Step 5: Final assembly of the C program; Add defines and includes
% and function header definitions from the global variable
% Also add the auxiliary functions after the already translated
% code from the global variable
function addAuxiliaryData
	replace [program]
		ID [id] 'DEFINITIONS TAG [opt tag_default] ::= 'BEGIN
		EX [opt export_block]
		IM [opt import_block]
		BODY [repeat rule_definition]
		'END
	import FunctionDeclarations [repeat rule_definition]
	% Include to include the header file for the module (Named from the module ID)
	construct ModuleHeader [stringlit]
		_ [+ "#include \""] [+ ID] [+ "_Generated"] [+ ".h\""]
	% Parse the preprocessor to validate it
	construct ModuleHeaderPRE [opt preprocessor]
		_ [parse ModuleHeader]
	% Get the final include from the parsed section
	deconstruct ModuleHeaderPRE
		FinalHeaderInclude [preprocessor]
	import AuxFunctions [repeat rule_definition]
	% All the standard defines and includes for any module
	construct Includes [repeat preprocessor]
		'#define BIGENDIAN (0x0)
		'#define LITTLEENDIAN (0x1)
		FinalHeaderInclude
		'#include "pglobals.h"
		'#include "putilities.h"
	% Evaluate the contents of the auxiliary function global variable; Eliminating all duplicates
	construct FinalAuxFunctions [repeat rule_definition]
		AuxFunctions [removeDuplicates AuxFunctions] [checkRest AuxFunctions]
	import globalConstraints [repeat rule_definition]
	by
		% The program becomes the includes on the top, then the function header declarations 
		% (with duplicates removed), then the global constraints then the translated BODY, 
		% then finally the already filtered auxiliary function
		Includes
		FunctionDeclarations [removeDuplicates AuxFunctions] [checkRest AuxFunctions] [. globalConstraints] [. BODY] [. FinalAuxFunctions]
end function

% Simple function to remove a duplicate from a set
% of rule definitions by not saving it if it already
% exists
function removeDuplicates AuxFunctions [repeat rule_definition]
	replace [repeat rule_definition]
		Rule [rule_definition] REST [repeat rule_definition]
	% If the rule is already in the REST
	deconstruct * [rule_definition] REST
		Rule
	by
		% Then do not save it and recursively call the functions on the REST
		REST [removeDuplicates REST] [checkRest REST]
end function

% Simple function to save a [rule_definition] if it
% does not already exist
function checkRest AuxFunctions [repeat rule_definition]
	replace [repeat rule_definition]
		Rule [rule_definition] REST [repeat rule_definition]
	% If the rule is not already in REST
	deconstruct not * [rule_definition] REST
		Rule
	by
		% The save it and recursively call the functions on the REST
		Rule REST [removeDuplicates REST] [checkRest REST]
end function

%% END OF STEP 5 %%


%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%  Step 2 & 3 | Free Functions Section  %%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%


% Free Functions to avoid any memory leaks after any parse

% There are two methods to the free function
% A main free function will be generated that can free anything
% that has been allocated from a struct of the main type for the
% protocol through picking the correct type at type decisions

% If there are any callback optimizations, the content of those
% messages that are optimized will be omitted from the main free
% Since as part of the optimization the messages are not allocated
% into an array and saved, they must be free once they reach callback
% as they are not accessable externally. Each message will have its
% own free function that will also be generated in this section. 
% Each message specific function will be called after a callback,
% which is also more efficient as the type is already known


% Step 2: Generate Free Function for any Type Rules where
% some piece of data has been allocated with malloc to
% prevent any memory leaks
function createFreeFunctionTypeRule RULES [repeat rule_definition]
	replace [program]
		P [program]
	% Must be a type rule
	deconstruct * [rule_definition] RULES
		LONG [id] '^ PDU ANN [opt annotation]'::= 'SEQUENCE '{
			LE [list element_type] OC [opt ',]
		'} OP [opt scl_additions]
	% Name for the free function to free the rule
	construct freeName [id]
		_ [+ "free"] [+ LONG]
	construct ALLOCNAME [constant]
		'mainpdu
	construct freeBody [repeat declaration_or_statement]
	% Lexical number for tab indexing
	construct lexicalValue [number]
		1
	% Get the first [element_type] from the list
	deconstruct LE
		ET [element_type] ', REST [list element_type]
	% Generate the free code for each [element_type] if required
	construct mainFree [repeat declaration_or_statement]
		_ [freeMainPDU RULES ALLOCNAME lexicalValue ET each LE]
	import FunctionDeclarations [repeat rule_definition]
	% Generate a function header definition for the free function
	construct freeDecl [rule_definition]
		void freeName(LONG * 'mainpdu);
	export FunctionDeclarations
		FunctionDeclarations [. freeDecl]	% Save the header definition
	% Generate the free function
	construct freeFunction [rule_definition]
		void freeName(LONG * 'mainpdu) {
			freeBody [. mainFree] 
		}
	import AuxFunctions [repeat rule_definition]
	export AuxFunctions
		AuxFunctions [. freeFunction]	% Save the free funtion
	by
		P 	% No replacement
end function
	
% Function to facilitate the generation of free code for
% each [element_type] depending on its type
function freeMainPDU RULES [repeat rule_definition] ALLOCNAME [constant] LVAL [number] previousET [element_type] ET [element_type]
	replace [repeat declaration_or_statement]
		Stmts [repeat declaration_or_statement]
	construct addedStmts [repeat declaration_or_statement]
		_ 	[freeSetOf RULES ALLOCNAME LVAL previousET ET]
			[freeSetOfAnnotatedCallback RULES ALLOCNAME LVAL previousET ET]
			[freeUserDefinedType RULES ALLOCNAME LVAL previousET ET]
			[freeUserDefinedTypeOptional RULES ALLOCNAME LVAL previousET ET]
			[freeOctetStringTypeConstrained RULES ALLOCNAME ET]
	by
		Stmts [. addedStmts]
end function

% Function to generate the free code for a SET OF
% element type
function freeSetOf RULES [repeat rule_definition] ALLOCNAME [constant] LVAL [number] previousET [element_type] ET [element_type]
	% Must be a SET OF type
	deconstruct ET
		LONG [id] '^ SHORT [id] 'SET 'OF TYPE [id] '(SIZE 'CONSTRAINED) POS [opt position_value]
	% Must not have callback optimization
	deconstruct not * [callback_annotation] RULES
		'@ TYPE
	replace [repeat declaration_or_statement]
		Stmts [repeat declaration_or_statement]
	construct shortLower [id]
		SHORT[tolower]
	% Variable for the count of messages in the set
	construct setOf [id]
		_ [+ shortLower] [+ "count"]
	construct index [id]
		_ [getLexicalIndex LVAL]	% Get the index variable (i, j or k) depending on the [number] parameter
									% This is used to keep loop indexing properly set as loops become nested
	construct ALLOCNAMESETOF [constant]
		ALLOCNAME [optionalMember previousET ET setOf]
			[normalMember previousET ET setOf] % Resolve the setOf name to be referencable based on its member type
	construct ALLOCNAMESHORT [constant]
		ALLOCNAME [optionalMember previousET ET shortLower]
			[normalMember previousET ET shortLower] % Resolve the shortLower name to be referencable based on its member type
	construct currentAlloc [constant]
		ALLOCNAME [optionalMember previousET ET shortLower]
			[normalMember previousET ET shortLower] '[ index ']	% Resolve the shortLower name to be referencable based on its member type and add the index call
	% Generate the free code for the setOf type decision; This is what needs to be freed for each type decision element
	construct setOfBody [repeat declaration_or_statement]
		_ [freeTypeDecision RULES currentAlloc TYPE LVAL ET ET] [freeSetOfSequence RULES currentAlloc TYPE LVAL ET ET]
	% To free a SET OF, it must be iterated through with a loop
	% as it is stored as an array. A for loop is used as the number
	% of elements in the array is known and stored in the variable
	% in the sruct under standard naming. For each element free its
	% contents and then set it to NULL. Once all elements are freed
	% then free the pointer and set it to NULL
	construct Stmt [repeat declaration_or_statement]
		for(int index = 0; index < ALLOCNAMESETOF ; ++index) {
			if(& currentAlloc != NULL) {
				setOfBody 
			}
		}
		if(ALLOCNAMESHORT != NULL) {
			free(ALLOCNAMESHORT);
			ALLOCNAMESHORT = NULL;
		}
	construct optionalCheck [repeat declaration_or_statement]
		_ [checkForOptionalPreviousET previousET ALLOCNAME shortLower Stmt] [checkForNotOptionalPreviousET previousET ALLOCNAME shortLower Stmt]
	by
		Stmts [. optionalCheck]
end function

% Function to use the passed in index [number] to
% generate the correct indexing letter based on
% the [number]. Eg index 1 is i, 2 is j, 3 is k
function getLexicalIndex VAL [number]
	replace [id]
		index [id]
	by
		index [first VAL] [second VAL] [third VAL]
end function

% If the index value is one then the index [id]
% is the symbol 'i'
function first VAL [number]
	deconstruct VAL
		1
	replace [id]
		index [id]
	by 
		'i
end function

% If the index value is two then the index [id]
% is the symbol 'j'
function second VAL [number]
	deconstruct VAL
		2
	replace [id]
		index [id]
	by 
		'j
end function

% If the index value is three then the index [id]
% is the symbol 'k
function third VAL [number]
	deconstruct VAL
		3
	replace [id]
		index [id]
	by 
		'k
end function

% Function to resolve an optional member to a C reference
% that can be evaluated. Since it is optional it uses the 
% "->" operator
function optionalMember previousET [element_type] currentET [element_type] shortLower [id]
	deconstruct currentET
		LONG [id] '^ SHORT [id] 'SET 'OF TYPE [id] '(SIZE 'CONSTRAINED) POS [opt position_value]
	construct index [number]
		_ [index LONG "_"]	% Location of the first "_" in LONG
	construct startingIndex [number]
		index [+ 1]	% THe character after the first "_" in LONG
	construct lengthIndex [number]
		_ [# LONG]	% The length of LONG
	construct typeToCheck [id]
		LONG [: startingIndex lengthIndex]	% The characters in LONG from the "_" to the end
	% Previous element must be the specified type
	deconstruct previousET
		LONG2 [id] '^ SHORT2 [id] typeToCheck '(SIZE DEFINED) OPT [opt endian] OPSL [opt slack] 'OPTIONAL
	replace [constant]
		ALLOCNAME [constant]
	by
		ALLOCNAME -> shortLower
end function

% Function to resolve a normal member to a C reference
% that can be evaluated. Since it is normal it uses the 
% "." operator
function normalMember previousET [element_type] currentET [element_type] shortLower [id]
	deconstruct currentET
		LONG [id] '^ SHORT [id] 'SET 'OF TYPE [id] '(SIZE 'CONSTRAINED) POS [opt position_value]
	construct index [number]
		_ [index LONG "_"]	% Location of the first "_" in LONG
	construct startingIndex [number]
		index [+ 1]	% THe character after the first "_" in LONG
	construct lengthIndex [number]
		_ [# LONG]	% The length of LONG
	construct typeToCheck [id]
		LONG [: startingIndex lengthIndex]	% The characters in LONG from the "_" to the end
	% Previous element must not be the specified type
	deconstruct not previousET
		LONG2 [id] '^ SHORT2 [id] typeToCheck '(SIZE DEFINED) OPT [opt endian] OPSL [opt slack] 'OPTIONAL
	replace [constant]
		ALLOCNAME [constant]
	by
		ALLOCNAME .shortLower
end function

% Function to free each element of a type decision; This is
% accomplished by using a switch statement with one switch
% case to free each different type in the type decision
function freeTypeDecision RULES [repeat rule_definition] ALLOCNAME [constant] TYPE [id] LVAL [number] ET [element_type] previousET [element_type]
	% Must be a type decision
	deconstruct * [rule_definition] RULES
		TYPE '^ SHORT [id] OPGLOB [opt global] OPOPT [opt optimizable] '::= '( TR [type_reference] RTR [repeat alternative_decision]')
	% Extract the info from the first [type_reference]
	deconstruct TR
		LONGID [id] OPT [opt dotID] ANN [opt annotation]
	% Generate the constant value for the [type_reference] for the swicth case
	construct SHORTVAL [id]
		_ [+ LONGID] [+ "_VAL"]
	% Increase the lexical val as we are nesting one level in
	construct newLexicalIndex [number]
		LVAL [+ 1]
	construct otherCases [repeat declaration_or_statement]
	% Generate the switch cases for the [alternative_decision]'s
	construct repeatCases [repeat declaration_or_statement]
		otherCases [freeAltDecisions RULES ALLOCNAME newLexicalIndex RTR previousET]
	% Find the type rule definition for the first [type_reference]
	deconstruct * [rule_definition] RULES
		LONGID '^ SHORTID [id] OPTANN [opt annotation]'::= 'SEQUENCE '{
			LE [list element_type] OC [opt ',]
		'} OP [opt scl_additions]
	replace [repeat declaration_or_statement]
		Stmts [repeat declaration_or_statement]
	% Generate a reference for the [id] of the type in the type decision
	construct NewAllocName [constant]
		 ALLOCNAME.'ptr.LONGID[tolower]
	% Generate the free statements for the content of the new reference
	construct TRFreeBody [repeat declaration_or_statement]
		 _ [freeMainPDU RULES NewAllocName newLexicalIndex previousET each LE]
	% Create a switch statement for the type decision. Switch based on the
	% constant value for each different type and free any used elements in 
	% each switch case. Break after each case as there is only one possibility
	construct Stmt [repeat declaration_or_statement]
		if(ALLOCNAME.'type > 0) {
			switch(ALLOCNAME.'type) {
				case SHORTVAL:
				{
					TRFreeBody 
				}
				break;
				repeatCases
			}
		}
	by
		Stmts [. Stmt]
end function

% Generate the switch case statements for the [alternative_decision]
% in the type decision rule
function freeAltDecisions RULES [repeat rule_definition] ALLOCNAME [constant] LVAL [number] RTR [repeat alternative_decision] previousET [element_type]
	% Get the next [type_reference] in the set of the REST
	deconstruct RTR 
		'| LONGID [id] OPT [opt dotID] ANN [opt annotation] REST [repeat alternative_decision]
	replace [repeat declaration_or_statement]
		Stmts [repeat declaration_or_statement]
	% Generate the constant value for the [type_reference] for the swicth case
	construct SHORTVAL [id]
		_ [+ LONGID] [+ "_VAL"]
	% Find the type rule definition for the first [type_reference]
	deconstruct * [rule_definition] RULES
		LONGID '^ SHORTID [id] OPTANN [opt annotation]'::= 'SEQUENCE '{
			LE [list element_type] OC [opt ',]
		'} OP [opt scl_additions]
	% Generate a reference for the [id] of the type in the type decision
	construct NewAllocName [constant]
		 ALLOCNAME.'ptr.LONGID[tolower]
	% Generate the free statements for the content of the new reference
	construct TRFreeBody [repeat declaration_or_statement]
		_ [freeMainPDU RULES NewAllocName LVAL previousET each LE]
	% Generate the switch case for the current [type_reference]
	construct Stmt [repeat declaration_or_statement]
		case SHORTVAL':
		{
			TRFreeBody 
		}
		break;
	by
		Stmts [. Stmt] [freeAltDecisions RULES ALLOCNAME LVAL REST previousET]
		% Recursively add the rest of the case statements until REST is empty
end function

% Generate the code to free a sequence rule that is defined from
% a SET OF rule (Instead of a type decision defining it)
function freeSetOfSequence RULES [repeat rule_definition] ALLOCNAME [constant] TYPE [id] LVAL [number] ET [element_type] previousET [element_type]
	% Find the type rule definition for the first [type_reference]
	deconstruct * [rule_definition] RULES
		TYPE '^ SHORTID [id] OPTANN [opt annotation]'::= 'SEQUENCE '{
			LE [list element_type] OC [opt ',]
		'} OP [opt scl_additions]
	% Increase the lexical val as we are nesting one level in
	construct newLexicalIndex [number]
		LVAL [+ 1]
	replace [repeat declaration_or_statement]
		Stmts [repeat declaration_or_statement]
	% Generate a reference for the [id] of the type in the type decision
	construct NewAllocName [constant]
		 ALLOCNAME
	% Generate the free statements for the content of the new reference
	construct TRFreeBody [repeat declaration_or_statement]
		 _ [freeMainPDU RULES NewAllocName newLexicalIndex previousET each LE]
	construct Stmt [repeat declaration_or_statement]
		TRFreeBody
	by
		Stmts [. Stmt]
end function

function checkForOptionalPreviousET ET [element_type] ALLOCNAME [constant] shortLower [id] Stmt [repeat declaration_or_statement]
	replace [repeat declaration_or_statement]
		Stmts [repeat declaration_or_statement]
	deconstruct ET 
		LONG [id] '^ SHORT [id] TYPE [id] '(SIZE 'DEFINED) OPT [opt endian] OPSL [opt slack] 'OPTIONAL POS [opt position_value]
	construct optionalCheck [repeat declaration_or_statement]
		if(ALLOCNAME != NULL) {
			if(ALLOCNAME ->shortLower != NULL) {
				Stmt
			}
		}
	by
		Stmts [. optionalCheck]
end function

function checkForNotOptionalPreviousET ET [element_type] ALLOCNAME [constant] shortLower [id] Stmt [repeat declaration_or_statement]
	replace [repeat declaration_or_statement]
		Stmts [repeat declaration_or_statement]
	deconstruct not ET 
		LONG [id] '^ SHORT [id] TYPE [id] '(SIZE 'DEFINED) OPT [opt endian] OPSL [opt slack] 'OPTIONAL POS [opt position_value]
	construct optionalCheck [repeat declaration_or_statement]
		if(ALLOCNAME '.shortLower != NULL) {
			Stmt
		}
	by
		Stmts [. optionalCheck]
end function

% Function to generate the free code for a SET OF
% element type with callback optimization; Callback optimization
% does not store the messages in an array so instead individual free
% functions are generated and called for each message type instead of
% freeing in a loop
function freeSetOfAnnotatedCallback RULES [repeat rule_definition] ALLOCNAME [constant] LVAL [number] previousET [element_type] ET [element_type]
	% Must be a SET OF type
	deconstruct ET
		LONG [id] '^ SHORT [id] 'SET 'OF TYPE [id] '(SIZE 'CONSTRAINED) POS [opt position_value]
	% Must have a callback annotation
	deconstruct * [callback_annotation] RULES
		'@ TYPE
	replace [repeat declaration_or_statement]
		Stmts [repeat declaration_or_statement]
	construct shortLower [id]
		SHORT[tolower]
	% Variable for the count of messages in the set
	construct setOf [id]
		_ [+ shortLower] [+ "count"]
	construct index [id]
		_ [getLexicalIndex LVAL]	% Get the index variable (i, j or k) depending on the [number] parameter
									% This is used to keep loop indexing properly set as loops become nested
	construct ALLOCNAMESETOF [constant]
		ALLOCNAME [optionalMember previousET ET setOf]
			[normalMember previousET ET setOf]	% Resolve the setOf name to be referencable based on its member type
	construct ALLOCNAMESHORT [constant]
		ALLOCNAME [optionalMember previousET ET shortLower]
			[normalMember previousET ET shortLower]	% Resolve the shortLower name to be referencable based on its member type
	construct currentAlloc [constant]
		ALLOCNAME [optionalMember previousET ET shortLower]
			[normalMember previousET ET shortLower] '[ index ']	% Resolve the shortLower name to be referencable based on its member type and add the index call
	construct setOfBody [repeat declaration_or_statement]
		_ [freeTypeDecisionAnnotatedCallback RULES currentAlloc TYPE LVAL ET ET] [freeSetOfSequence RULES currentAlloc TYPE LVAL ET ET]
	by
		Stmts 	% No replacement is necessary, the frees are added as auxiliary functions in freeTypeDecisionAnnotatedCallback
end function

% Function to free each element of a type decision; This is
% accomplished by creating a function to free each type of
% message in the type decision that will be called after the
% message callback
function freeTypeDecisionAnnotatedCallback RULES [repeat rule_definition] ALLOCNAME [constant] TYPE [id] LVAL [number] ET [element_type] previousET [element_type]
	% Must be a type decision
	deconstruct * [rule_definition] RULES
		TYPE '^ SHORT [id] OPGLOB [opt global] OPOPT [opt optimizable] '::= '( TR [type_reference] RTR [repeat alternative_decision]') AA [opt scl_additions]
	% Extract the info from the first [type_reference]
	deconstruct TR
		LONGID [id] OPT [opt dotID] ANN [opt annotation]
	construct FreeName [id]
		_ [+ "free"] [+ LONGID]
	% Increase the lexical val as we are nesting one level in
	construct newLexicalIndex [number]
		LVAL [+ 1]
	construct otherCases [repeat declaration_or_statement]
	% Generate the switch cases for the [alternative_decision]'s
	construct repeatCases [repeat declaration_or_statement]
		otherCases [freeAltDecisionsAnnotatedCallback RULES ALLOCNAME newLexicalIndex RTR previousET]
	% Find the type rule definition for the first [type_reference]
	deconstruct * [rule_definition] RULES
		LONGID '^ SHORTID [id] OPTANN [opt annotation]'::= 'SEQUENCE '{
			LE [list element_type] OC [opt ',]
		'} OP [opt scl_additions]
	replace [repeat declaration_or_statement]
		Stmts [repeat declaration_or_statement]
	% Generate a reference for the [id] of the type in the type decision
	construct NewAllocName [constant]
		LONGID[tolower]
	% Generate the free statements for the content of the new reference
	construct TRFreeBody [repeat declaration_or_statement]
		 _ [freeMainPDUPointer RULES NewAllocName newLexicalIndex previousET each LE]
	% Create a free function to free the contents of the Type
	% (Instead of making a switch statement in the normal type)
	construct FreeFunction [rule_definition]
		void FreeName (LONGID * LONGID[tolower]) {
			TRFreeBody
		}
	import AuxFunctions [repeat rule_definition]
	export AuxFunctions
		AuxFunctions [. FreeFunction]	% Save the free function
	% Function definition header for the free function
	construct FreeHeader [rule_definition]
		void FreeName(LONGID * LONGID[tolower]);
	import FunctionDeclarations [repeat rule_definition]
	export FunctionDeclarations
		FunctionDeclarations [. FreeHeader]	% Save the function header
	by
		Stmts
end function

% For the callback optmization version, since the messages
% are not stored in an array, they are stored as pointers
% instead of references. For this method, they must be accessed
% by the "->" operator instead of the "." operator
function freeMainPDUPointer RULES [repeat rule_definition] ALLOCNAME [constant] LVAL [number] previousET [element_type] ET [element_type]
	replace [repeat declaration_or_statement]
		Stmts [repeat declaration_or_statement]
	construct addedStmts [repeat declaration_or_statement]
		_ [freeSetOf RULES ALLOCNAME LVAL previousET ET]
			[freeUserDefinedTypePointer RULES ALLOCNAME LVAL previousET ET]
			[freeUserDefinedTypeOptionalPointer RULES ALLOCNAME LVAL previousET ET]
			[freeOctetStringTypeConstrainedPointer RULES ALLOCNAME ET]
	by
		Stmts [. addedStmts]
end function

% Function to generate the free code for a user defined
% type when the host ALLOCNAME is a pointer so "->"
% must be used
function freeUserDefinedTypePointer RULES [repeat rule_definition] ALLOCNAME [constant] LVAL [number] previousET [element_type] ET [element_type]
	% Must be a user defined type
	deconstruct ET
		LONG [id] '^ SHORT [id] TYPE [id] '(SIZE 'DEFINED)  OPT [opt endian] OPSL [opt slack] POS [opt position_value]
	% Must have a matching rule_definition
	deconstruct * [rule_definition] RULES
		TYPE '^ SHORTID [id] ANN [opt annotation]'::= 'SEQUENCE '{
			LE [list element_type] OC [opt ',]
		'} OP [opt scl_additions]
	% Generate a reference for the member
	construct NewAllocName [constant]
		ALLOCNAME -> SHORT[tolower]
	% Generate the free code for the new reference;
	% Use normal freeMainPDU as the pointer portion
	% has been resolved (Only the first reference has
	% changed with callback optimization)
	construct freeBody [repeat declaration_or_statement]
		_ [freeMainPDU RULES NewAllocName LVAL ET each LE]
	replace [repeat declaration_or_statement]
		Stmts [repeat declaration_or_statement]
	by
		Stmts [. freeBody]	% Save the new free function
end function

% Function to generate the free code for a user defined
% type with an OPTIONAL tag when the host ALLOCNAME is 
% a pointer so "->" must be used
function freeUserDefinedTypeOptionalPointer RULES [repeat rule_definition] ALLOCNAME [constant] LVAL [number] previousET [element_type] ET [element_type]
	% Must be a user defined type with OPTIONAL tag
	deconstruct ET
		LONG [id] '^ SHORT [id] TYPE [id] '(SIZE 'DEFINED) OPT [opt endian] OPSL [opt slack] 'OPTIONAL POS [opt position_value]
	% Must have a matching rule_definition
	deconstruct * [rule_definition] RULES
		TYPE '^ SHORTID [id] ANN [opt annotation]'::= 'SEQUENCE '{
			LE [list element_type] OC [opt ',]
		'} OP [opt scl_additions]
	% The reference must be freed after the main freeBody
	% as the reference has been allocated previously in 
	% this type
	construct Stmt [repeat declaration_or_statement]
		if(ALLOCNAME -> SHORT[tolower] != NULL) {
			free(ALLOCNAME -> SHORT[tolower]);
			ALLOCNAME -> SHORT[tolower] = NULL;
		}
	% Generate a reference for the member
	construct NewAllocName [constant]
		ALLOCNAME -> SHORT[tolower]
	% Generate the free code for the new reference;
	% Use normal freeMainPDU as the pointer portion
	% has been resolved (Only the first reference has
	% changed with callback optimization)
	construct freeBody [repeat declaration_or_statement]
		_ [freeMainPDU RULES NewAllocName LVAL ET each LE]
	replace [repeat declaration_or_statement]
		Stmts [repeat declaration_or_statement]
	by
		Stmts [. freeBody] [. Stmt]	% Save the free function
end function

% Function to generate the free code for an octet string
% type when the host ALLOCNAME is a pointer so "->" 
% must be used
function freeOctetStringTypeConstrainedPointer RULES [repeat rule_definition] ALLOCNAME [constant] ET [element_type]
	% Must be an octet string type with constrained
	deconstruct ET
		LONG [id] '^ SHORT [id] 'OCTET 'STRING '(SIZE 'CONSTRAINED) OPT [opt endian] OPSL [opt slack] POS [opt position_value]
	replace [repeat declaration_or_statement]
		Stmts [repeat declaration_or_statement]
	% Must free the octet string as it is a pointer
	% that has been allocated dynamically due to its
	% constrained size;
	construct Stmt [repeat declaration_or_statement]
		if(ALLOCNAME -> SHORT[tolower] != NULL) {
			free(ALLOCNAME -> SHORT[tolower]);
			ALLOCNAME -> SHORT[tolower] = NULL;
		}	
	by
		Stmts [. Stmt]	% Save the free code
end function

% Generate the free functions and headers for 
% the [alternative_decision] in the type decision rule
function freeAltDecisionsAnnotatedCallback RULES [repeat rule_definition] ALLOCNAME [constant] LVAL [number] RTR [repeat alternative_decision] previousET [element_type]
	% Get the next [type_reference] in the set of the REST
	deconstruct RTR 
		'| LONGID [id] OPT [opt dotID] ANN [opt annotation] REST [repeat alternative_decision]
	replace [repeat declaration_or_statement]
		Stmts [repeat declaration_or_statement]
	% Find the type rule definition for the first [type_reference]
	deconstruct * [rule_definition] RULES
		LONGID '^ SHORTID [id] OPTANN [opt annotation]'::= 'SEQUENCE '{
			LE [list element_type] OC [opt ',]
		'} OP [opt scl_additions]
	% Generate a reference for the [id] of the type in the type decision
	construct NewAllocName [constant]
		 LONGID[tolower]
	% Generate the free statements for the content of the new reference
	construct TRFreeBody [repeat declaration_or_statement]
		_ [freeMainPDUPointer RULES NewAllocName LVAL previousET each LE]	
	% The name for the free function; Standard naming
	construct FreeName [id]
		_ [+ "free"] [+ LONGID]
	% Create a free function to free the contents of the Type
	% (Instead of making a switch statement in the normal type)
	construct FreeFunction [rule_definition]
		void FreeName (LONGID * LONGID[tolower]) {
			TRFreeBody
		}
	import AuxFunctions [repeat rule_definition]
	export AuxFunctions
		AuxFunctions [. FreeFunction]	% Save the free function
	% Function definition header for the free function
	construct FreeHeader [rule_definition]
		void FreeName(LONGID * LONGID[tolower]);
	import FunctionDeclarations [repeat rule_definition]
	export FunctionDeclarations
		FunctionDeclarations [. FreeHeader]	% Save the function header
	by
		Stmts [freeAltDecisionsAnnotatedCallback RULES ALLOCNAME LVAL REST previousET] 
		% Recursively add the rest of the case statements until REST is empty
end function

% Function to generate the free code for a user
% defined type
function freeUserDefinedType RULES [repeat rule_definition] ALLOCNAME [constant] LVAL [number] previousET [element_type] ET [element_type]
	% Must have a user defined type
	deconstruct ET
		LONG [id] '^ SHORT [id] TYPE [id] '(SIZE 'DEFINED)  OPT [opt endian] OPSL [opt slack] POS [opt position_value]
	% Must have a rule_definition for the user defined type
	deconstruct * [rule_definition] RULES
		TYPE '^ SHORTID [id] ANN [opt annotation]'::= 'SEQUENCE '{
			LE [list element_type] OC [opt ',]
		'} OP [opt scl_additions]	
	% Generate a reference for the [id] of the user defined type
	construct NewAllocName [constant]
		ALLOCNAME.SHORT[tolower]
	% Generate the free statements for the content of the new reference
	construct freeBody [repeat declaration_or_statement]
		_ [freeMainPDU RULES NewAllocName LVAL ET each LE]
	replace [repeat declaration_or_statement]
		Stmts [repeat declaration_or_statement]
	by
		Stmts [. freeBody]	% Save the free statements
end function

% Function to generate the free code for a user
% defined type with an OPTIONAL tag
function freeUserDefinedTypeOptional RULES [repeat rule_definition] ALLOCNAME [constant] LVAL [number] previousET [element_type] ET [element_type]
	% Must have a user defined type
	deconstruct ET
		LONG [id] '^ SHORT [id] TYPE [id] '(SIZE 'DEFINED) OPT [opt endian] OPSL [opt slack] 'OPTIONAL POS [opt position_value]
	% Must have a rule_definition for the user defined type
	deconstruct * [rule_definition] RULES
		TYPE '^ SHORTID [id] ANN [opt annotation]'::= 'SEQUENCE '{
			LE [list element_type] OC [opt ',]
		'} OP [opt scl_additions]
	% The reference must be freed after the main freeBody
	% as the reference has been allocated previously in 
	% this type
	construct Stmt [repeat declaration_or_statement]
		if(ALLOCNAME .SHORT[tolower] != NULL) {
			free(ALLOCNAME .SHORT[tolower]);
			ALLOCNAME .SHORT[tolower] = NULL;
		}
	% Generate a reference for the [id] of the user defined type
	construct NewAllocName [constant]
		ALLOCNAME .SHORT[tolower]
	% Generate the free statements for the content of the new reference
	construct freeBody [repeat declaration_or_statement]
		_ [freeMainPDU RULES NewAllocName LVAL ET each LE]
	replace [repeat declaration_or_statement]
		Stmts [repeat declaration_or_statement]
	by
		Stmts [. freeBody] [. Stmt]	% Save the free function
end function

% Function to generate the free code for an octet
% string type
function freeOctetStringTypeConstrained RULES [repeat rule_definition] ALLOCNAME [constant] ET [element_type]
	% Must be an octet string with constrained size
	deconstruct ET
		LONG [id] '^ SHORT [id] 'OCTET 'STRING '(SIZE 'CONSTRAINED) OPT [opt endian] OPSL [opt slack] POS [opt position_value]
	replace [repeat declaration_or_statement]
		Stmts [repeat declaration_or_statement]
	% Must free the octet string as it is a pointer
	% that has been allocated dynamically due to its
	% constrained size;
	construct Stmt [repeat declaration_or_statement]
		if(ALLOCNAME .SHORT[tolower] != NULL) {
			free(ALLOCNAME .SHORT[tolower]);
			ALLOCNAME .SHORT[tolower] = NULL;
		}	
	by
		Stmts [. Stmt]	% Save the free function
end function


% Step 3: Generate the free code for any type decision rules
function createFreeFunctionTypeDecision RULES [repeat rule_definition]
	replace [program]
		P [program]
	by
		P [createFreeInterfaceTypeDecision RULES] [createFreeNormalTypeDecision RULES]
end function

% Function to generate free function code for a type decision
% rule that contains DotID's
function createFreeInterfaceTypeDecision RULES [repeat rule_definition]
	replace [program]
		P [program]
	% Must be a type decision
	deconstruct * [rule_definition] RULES
		LONG [id] '^ PDU OPGLOB [opt global] OPT [opt optimizable]'::= TD [type_decision] OPTSCL [opt scl_additions]
	% Extract the first [type_reference] from the [type_decision]
	deconstruct TD
		'( TR [type_reference] RTR [repeat alternative_decision] ')
	% Must have a DotID
	deconstruct TR
		LONG2 [id] '. ID2 [id] OPANN [opt annotation]
	construct ALLOCNAME [constant]
		'mainpdu
	% Lexical value for loop nesting purposes
	construct LVAL [number]
		1
	% Existing function name to free the DotID
	construct freeDTID [id]
		_ [+ "free"] [+ ID2]
	% Free function name
	construct freeName [id]
		_ [+ "free"] [+ LONG]	
	construct freeBody [repeat declaration_or_statement]
	import FunctionDeclarations [repeat rule_definition]
	% Free function header definition
	construct freeDecl [rule_definition]
		void freeName(LONG * 'mainpdu);
	export FunctionDeclarations
		FunctionDeclarations [. freeDecl]	% Save the header definition
	% Free based on the type; Kind must match the [id]'s constant
	construct mainFree [repeat declaration_or_statement]
		if(mainpdu ->'type == ID2[+ "_VAL"])
			freeDTID(&mainpdu ->'ptr.ID2[tolower]);
	% Generate the if statements for the other [alternative_decision]'s
	construct otherDecisions [repeat declaration_or_statement]
		_ [freeOtherInterfaceDecisions LONG RULES ALLOCNAME LVAL RTR]
	% The full free function
	construct freeFunction [rule_definition]
		void freeName( LONG * 'mainpdu ) {
			freeBody [. mainFree] [. otherDecisions]
		}
	import AuxFunctions [repeat rule_definition]
	export AuxFunctions
		AuxFunctions [. freeFunction]	% Save the free function	
	by
		P 	% No replacement
end function 

% Function to generate the free function code for
% the [alternative_decision] portion of a [type_decision]
function freeOtherInterfaceDecisions RuleName [id] RULES [repeat rule_definition] ALLOCNAME [constant] LVAL [number] RTR [repeat alternative_decision]
	replace [repeat declaration_or_statement]
		Stmts [repeat declaration_or_statement]
	% Get the next [type_reference] information from the REST
	deconstruct RTR
		'| 	LONG [id] '. ID2 [id] OPANN [opt annotation] RESTRTR [repeat alternative_decision]
	% Existing function name to free the DotID
	construct freeDTID [id]
		_ [+ "free"] [+ ID2]
	import FunctionDeclarations [repeat rule_definition]
	export FunctionDeclarations
		FunctionDeclarations	
	% Recursively call the rule for the remaining REST; Will continue
	% recursive calls until REST is empty
	construct otherDecisions [repeat declaration_or_statement]
		_ [freeOtherInterfaceDecisions RuleName RULES ALLOCNAME LVAL RESTRTR]
	% Generate the else if for this DotID and its constant value
	construct freeOtherInterface [repeat declaration_or_statement]
		 else if (mainpdu ->'type == ID2[+ "_VAL"])
			freeDTID(&mainpdu ->'ptr.ID2[tolower]);
	by
		Stmts [. freeOtherInterface]	% Save the elsif code
end function

% Function to generate free function code for a standard type decision
% rule
function createFreeNormalTypeDecision RULES [repeat rule_definition]
	replace [program]
		P [program]
	% Must be a standard type decision rule
	deconstruct * [rule_definition] RULES
		LONG [id] '^ PDU OPGLOB [opt global] OPT [opt optimizable]'::= TD [type_decision] OPTSCL [opt scl_additions]
	% Extract the first [type_reference] from the [type_decision]
	deconstruct TD
		'( TR [type_reference] RTR [repeat alternative_decision] ')
	% Must not have a DotID
	deconstruct TR
		ID [id] OPANN [opt annotation]
	% Free function name
	construct freeName [id]
		_ [+ "free"] [+ LONG]
	construct ALLOCNAME [constant]
		'mainpdu
	construct freeBody [repeat declaration_or_statement]
	% Lexical value for loop nesting purposes
	construct lexicalValue [number]
		1
	% Extract all the [type_reference]'s from the [alternative_decision]
	% and append the first one that was deconstructed
	construct TRList [repeat type_reference]
		_ [^ RTR] [. TR]
	% Generate the free code for each [type_reference]
	construct mainFree [repeat declaration_or_statement]
		_ [freeMainPDUTypeDecision RULES ALLOCNAME lexicalValue each TRList]
	import FunctionDeclarations [repeat rule_definition]
	% Free function header definition
	construct freeDecl [rule_definition]
		void freeName(LONG * 'mainpdu);
	export FunctionDeclarations
		FunctionDeclarations [. freeDecl]	% Save the header definition
	% The full free function
	construct freeFunction [rule_definition]
		void freeName( LONG * 'mainpdu ) {
			freeBody [. mainFree]
		}
	import AuxFunctions [repeat rule_definition]
	export AuxFunctions
		AuxFunctions [. freeFunction]	% Save the free function
	by
		P 	% No replacement
end function

% Function to generate the if statements to free the
% types in a type decision and its related content
function freeMainPDUTypeDecision RULES [repeat rule_definition] ALLOCNAME [constant] LVAL [number] TR [type_reference]
	% Get the info for the current [type_reference]
	deconstruct TR
		LONG [id] OPID [opt dotID] OPANN [opt annotation]
	% Must have a rule defining the [id]
	deconstruct * [rule_definition] RULES
		LONG '^ SHORT [id] ANN [opt annotation]'::= 'SEQUENCE '{
			LE [list element_type] OC [opt ',]
		'} OP [opt scl_additions]
	% Extract the first [element_type] from the list
	deconstruct LE
		ET [element_type] ', REST [list element_type]
	replace [repeat declaration_or_statement]
		Stmts [repeat declaration_or_statement]
	% Reference that can evaluate the type decision element
	construct NewAllocName [constant]
		ALLOCNAME -> 'ptr '.LONG[tolower]
	% Generate any free statements for the [element_type]'s of the type
	construct addedStmts [repeat declaration_or_statement]
		_ [freeMainPDU RULES NewAllocName LVAL ET each LE]
	% Free function code to free the type decision element if its
	% kind matches the constant for that type
	construct checkCase [repeat declaration_or_statement]
		if (mainpdu ->'type == LONG[+ "_VAL"]) {
			addedStmts
		}
	by
		Stmts [. checkCase] 	% Save the if statement
end function

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%  End Step 2 & 3 | Free Functions Section  %%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%