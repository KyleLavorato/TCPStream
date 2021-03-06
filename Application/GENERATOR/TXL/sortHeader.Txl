% Sort Header
% Ali El-Shakankiry
% Queen's University, Jan 2017

% Copyright 2017 Thomas Dean

% Revision history:

% 1.1 Documentation			- KPL	26 06 2017
% 1.0 Initial revision 		- AES 	01 01 2017 

% This program walks through a .h header file for the c language and sorts it
% so everything is declared before it is referenced

% The input to the program is a .h file named "protocol"_Generated.h.unsorted.
% The input file has been generated by the previous TXL script for use in a
% parser for the specified protocol.

% The output of this program is a header file named "protocol"_Generated.h
% The output file is the header file where everything is declared before it
% is referenced elsewhere in the file.

% Base grammar

include "c.grm"

% Local grammar overries

define program
	[cprogram]
end define

% Main rule followed by other rules in topological order

rule main
	replace [program]
		P [program]
	construct newP [program]
		P [sortStructs]
	deconstruct not P
		newP	% Only replace if a change has been made
	by
		newP
end rule


% Step 1: Sort all the structs, ensuring that if a struct references
% another struct that is has already been defined above. The sort
% method is a bubble sort implimented through TXL recursion
rule sortStructs
	skipping [declaration]
	replace $ [repeat function_definition_or_declaration]
		'typedef aStruct [struct_or_union_specifier] ';
		Rest [repeat function_definition_or_declaration]
	deconstruct * [struct_or_union_body] aStruct
		Body [struct_or_union_body]
	construct NestedNames [repeat upperlowerid]
		_ [^ Body]	% Pull all the names from the struct body
	where 
		Rest [containsStructDef each NestedNames]
	by
		Rest [insertStruct1 NestedNames aStruct]
				[insertStruct2 NestedNames aStruct]
end rule

function containsStructDef Name [upperlowerid]
	match * [decl_qualifier_or_type_specifier]
		struct Body [struct_or_union_body] Name
end function

function insertStruct1 NestedNames [repeat upperlowerid] aStruct [struct_or_union_specifier]
	replace [repeat function_definition_or_declaration]
		A [function_definition_or_declaration]
		Rest [repeat function_definition_or_declaration]
	where not 
		Rest [containsStructDef each NestedNames]
	by
		A
		typedef aStruct ';
		Rest
end function

function insertStruct2 NestedNames[repeat upperlowerid] aStruct [struct_or_union_specifier]
	replace [repeat function_definition_or_declaration]
		A [function_definition_or_declaration]
		Rest [repeat function_definition_or_declaration]
	where  
		Rest [containsStructDef each NestedNames]
	by
		A
		Rest [insertStruct1 NestedNames aStruct]
				[insertStruct2 NestedNames aStruct]
end function
