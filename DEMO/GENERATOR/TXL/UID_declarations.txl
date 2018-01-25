% Generate Header
% Ali El-Shakankiry
% Queen's University, Jan 2017

% Copyright 2017 Thomas Dean

% Revision history:

% 1.1 Documentation			- KPL	26 06 2017
% 1.0 Initial revision 		- AES 	01 01 2017 

% This program walks through a SCL5 definition of a protocol and ensures 
% unique naming for all definitions by appending the protocol name in hat notation

% The input to the program is a SCL5 file named "protocol".scl5. The input 
% file is a SCL5 description of a protocol that the user wants to generate
% a parser for

% The output of this program is a SCL5 file named "protocol"_declarations.scl5.
% The output file is the original SCL5 file with unique naming of all definitions.


% Base grammars

include "ASNOne.Grm"

% Local grammar overrides

redefine construction_assignment_statement
	[decl] '::= [type_decision] [opt scl_additions]				[NL]
end redefine

% Main rule followed by other rules in topological order

function main
   replace [program]
	  P [program]
   by
	P [noUnderscores]
		[doDecls]
end function


% Step 1: Find any undercores in the SCL5 specification and replace them
% with the '$' character. Since underscores will be used to seperate the
% naming and unique name addition they are to not be used anywhere else
% Emit a warning to notify the user of the change in their name in SCL5
% NOTE: The '$' character was chosen out of simplicity as it is usable
% in both SCL5 and c naming without causing any issues or bugs
rule noUnderscores
	replace $ [id]
		ID [id]
	construct US [number]
		_ [index ID "_"]	% Get the position of the "_" character in ID
	deconstruct not US
		0	% If the location is 0 a "_" was not found; Only contine if not 0
	construct Err [id]
	_ [+ "Warning, \""] [+ US] [+ "\" declaration \""] [+ ID] [+ "\" contains underscore '_' "]
	construct Message [id]
		_	[message Err]	% Send error message to the console output
	construct LenS [number]
		_ [# ID]	% Get the length of ID
	construct sub1 [number]
		US[- 1]		% The end location of the content before the location of "_"
	construct sub2 [number]
		US[+ 1]		% The start location of the content after the location of the "_"
	construct ID2 [id]
		ID[:sub2 LenS]	% The content after the location of the "_"
	construct NEWID [id]
		ID[:0 sub1] [+ "$"] [+ ID2]	% The two halves joined together by the "$"
	by
		NEWID
end rule

% Step 2: 
rule doDecls
	replace $ [module_definition]
		ID [id] 'DEFINITIONS TAG [opt tag_default] ::= 'BEGIN
		EX [opt export_block]
		IM [opt import_block]
		RERULE [repeat rule_definition]
		'END
	by
		ID 'DEFINITIONS TAG ::= 'BEGIN
		EX
		IM
		RERULE [renameTypeRule ID]
				[renameValueRule ID]
				[renameConstAssignment ID]	
		'END		
end rule

% Function to rename a type rule using unique naming by adding the
% protocol name to the start of it. The name gets annotated into the
% form LONGNAME ^ ORIGINALNAME. Also must rename all its elements
rule renameTypeRule ModName [id]
	skipping [type_rule_definition]
	replace $ [type_rule_definition]
		ID [id] '::= TYPE [type] ADD [opt scl_additions]
	construct UniqueRuleName [id]
		ID [+ '_ ] [+ ModName]	% Unique name using protocol
	by
		UniqueRuleName '^ ID '::= TYPE [renameType UniqueRuleName] ADD
		% Replace by the new name form and rename the type to be unique as well
end rule

% Function to rename a type of a rule to be unique
% The unique prefix is passed in as a parameter
function renameType RuleName [id]
	replace [type]
		T [type]
	by
		T [renameSequenceType RuleName]
			[renameSetType RuleName]
end function

% Function to rename a sequence rule to be unique
rule renameSequenceType RuleName [id]
	skipping [sequence_type]
	replace $ [sequence_type]
		'SEQUENCE OS [opt size_constraint] '{
			LE [list element_type] OC [opt ',]
		'}
	by
		'SEQUENCE OS '{
			LE [renameElementType RuleName] OC	% Rename each [element_type] to be unique
		'}
end rule

% Function to rename an [element_type] to be unique
rule renameElementType RuleName [id]
	skipping [element_type]
	replace $ [element_type]
		E [element_type]
	by
		E [renameNamedType RuleName]
end rule

% Function to rename a [named_type] to be unique using the
% form LONGNAME ^ ORIGINALNAME
rule renameNamedType RuleName [id]
	skipping [named_type]
	replace $ [named_type]
		ID [id] TYPE [type]
	construct UniqueElementName [id]
		ID [+ '_ ] [+ RuleName] [+ " ^ "] [+ ID]
	by
		UniqueElementName TYPE
end rule

% Function to rename a Set rule to be unique
rule renameSetType RuleName [id]
	skipping [set_type]
	replace $ [set_type]
		'SET OS [opt size_constraint] '{
			LE [list element_type]
		'}
	by
		'SET OS '{
			LE [renameElementType RuleName]	% Rename each [element_type] to be unique
		'}
end rule

% Function to rename a value rule using unique naming by adding the
% protocol name to the start of it. The name gets annotated into the
% form LONGNAME ^ ORIGINALNAME
rule renameValueRule ModName [id]
	skipping [value_rule_definition]
	replace $ [value_rule_definition]
		ID [id] TYPE [type] '::= V [value]
	construct UniqueRuleName [id]
		ID [+ '_ ] [+ ModName]
	by
		UniqueRuleName '^ ID TYPE '::= V	
end rule

% Function to rename a constant assignment using unique naming by adding the
% protocol name to the start of it. The name gets annotated into the
% form LONGNAME ^ ORIGINALNAME
rule renameConstAssignment ModName [id]
	skipping [construction_assignment_statement]
	replace $ [construction_assignment_statement]
		ID [id] '::= TYPE [type_decision] OPT [opt scl_additions]
	construct UniqueRuleName [id]
		ID [+ '_ ] [+ ModName]
	by
		UniqueRuleName '^ ID  '::= TYPE OPT
end rule