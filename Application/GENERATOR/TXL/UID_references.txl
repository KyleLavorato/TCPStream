% Generate Header
% Ali El-Shakankiry
% Queen's University, Jan 2017

% Copyright 2017 Thomas Dean

% Revision history:

% 1.1 Documentation			- KPL	26 06 2017
% 1.0 Initial revision 		- AES 	01 01 2017 

% This program walks through a SCL5 definition of a protocol with unique 
% naming in definitions and ensures that all references match and also
% uniquely names them

% The input to the program is a SCL5 file named "protocol"_declarations.scl5. 
% The input file is a SCL5 description of a protocol that has uniquely named
% definitions from the previous TXL script.

% The output of this program is a SCL5 file named "protocol"_UID.scl5.
% The output file is the input SCL5 file with unique naming of all references.


% Base grammars

include "ASNOne.Grm"

% Local grammar overrides

define pair
 [id] [id]
end define

define dot_rp
	'. [referenced_element]
end define

redefine referenced_element
	[referencable_primaries] [repeat dot_rp]
end redefine

redefine construction_assignment_statement
		[decl] '::= [type_decision] [opt scl_additions]				[NL]
end redefine

% Main rule followed by other rules in topological order

function main
	replace [program]
		P [program]
	by
		P [renRefUserFieldTypes]
		[createExportTable]
end function


% Step 1: Uniquely name all user defined types and references
rule renRefUserFieldTypes
	skipping [module_definition]
	replace $ [module_definition]
		ID [id] 'DEFINITIONS OP [opt tag_default] '::= 'BEGIN
			Exports [opt export_block]
			Imports [opt import_block]
			Body [repeat rule_definition]
		'END
	construct P [pair]
		E E
	export NameList [repeat pair]
		P 	% Global variable to hold the name [id] ^ [id] 
			% pairs of rule names
	by
		ID 'DEFINITIONS OP '::= 'BEGIN 
		Exports [renameExports ID]	% Uniquely name the [export_block] references
									% with the [id] of the protocol (module)
		Imports [renameImports]		% Uniquely name the [import_block] references
		Body [addDecls]
				[renameUserFieldTypes]
				[renameRefContraint Body]
				[renameConstructionAssignments ID]
		'END
end rule

% Rename all the references in the module's [export_block]
% to be unique names
rule renameExports Id [id]
	skipping [export_block]
	replace $ [export_block]
		'EXPORTS LIST [list decl] ';
	by
		'EXPORTS LIST [renameExportRefs Id] ';	% Cycle through the list of [decl]
												% adding unique naming to themn
end rule

% Recursive function to rename all the elements in a [list decl]
% with a unique named based on the parameter [id]. The function
% renames the first element in the list and is then called again
% on the rest until there is no rest left
function renameExportRefs ModuleName [id]
	replace [list decl]
		REF [id] ', REST [list decl]
	by
		REF [+ "_"] [+ ModuleName] '^ REF ', REST [renameExportRefs ModuleName]
		% Rename the first element with a unique name and repeat process on the rest
end function

% Function to rename all the imported references in 
% the [import_block] to a unique name based on the
% imported module
rule renameImports
	skipping [import_block]
	replace $ [import_block]
		'IMPORTS DECLS [list decl] 'FROM MODULE [id] ', REST [list import_list] ';
	by
		'IMPORTS DECLS [renameImportRefs MODULE] 'FROM MODULE ', REST [renameImportsList] ';
		% Rename all the references imported from the first module and call another function
		% to rename the remaining module imports
end rule

% Recursive function to rename all the elements in a [list decl]
% with a unique named based on the parameter [id]. The function
% renames the first element in the list and is then called again
% on the rest until there is no rest left
function renameImportRefs ModuleName [id]
	replace [list decl]
		REF [id] ', REST [list decl]
	by
		REF [+ "_"] [+ ModuleName] '^ REF ', REST [renameImportRefs ModuleName]
end function

% Function to rename all the references from a 
% [list import_list] of multiple other modules
% The rule will recursively iterate through the
% full [import_list]
rule renameImportsList
	replace $ [list import_list]
		DECLS [list decl] 'FROM MODULE [id] ', REST [list import_list]
	by
		DECLS [renameImportRefs MODULE] 'FROM MODULE ', REST
		% Rename the references from the first import in the list and repeat on
		% the remaining [import_list] list elements
end rule


% Step 1.1: Iterate through all [rule_definition]'s and
% save the UNIQUENAME [id] ^ SHORTNAME [id] [id] pairs in
% the global variable NameList for later use
rule addDecls
	skipping [rule_definition]
	replace $ [rule_definition]
		RD [rule_definition]
	by
		RD [addTypeRuleDef]
			[addConstructionAssignment]
end rule

% Function to save the name [id] ^ [id] pair of
% all [type_rule_definition] rules if the pair has
% not already been saved in the global variable
function addTypeRuleDef
	replace [rule_definition]
		First [id] '^ Short [id] '::= TP [type] OP [opt scl_additions]
	import NameList [repeat pair]	% Load the already discovered pairs
	construct check [repeat pair]
		NameList [checkIfPresent Short]	% Test if the pair has already been found
	construct newpair [pair]
		First Short	% First time pair has been encountered; Save it
	export NameList
		NameList [. newpair]	% Append the pair to the global and save the change
	by
		First '^ Short '::= TP OP	% No replacement
end function

% Function to test if the parameter [id] is already
% saved in the [repeat pair] under test 
function checkIfPresent ID [id]
	match [repeat pair]
		RE [repeat pair]
	deconstruct not * [pair] RE
		First [id] ID 	% Will only pass if ID is not present
end function

% Function to save the name [id] ^ [id] pair of
% all [type_decision] rules if the pair has
% not already been saved in the global variable
function addConstructionAssignment
	replace [rule_definition]
		First [id] '^ Short [id] '::= TP [type_decision]
	import NameList [repeat pair]	% Load the already discovered pairs
	construct check [repeat pair]
		NameList [checkIfPresent Short]	% Test if the pair has already been found
	construct newpair [pair]
		First Short	% First time pair has been encountered; Save it
	export NameList
		NameList [. newpair]	% Append the pair to the global and save the change
	by
		First '^ Short '::= TP 	% No replacement
end function


% Step 1.2: Find any user defined types in all the
% [rule_definition]'s. If the [id] of the type matches
% an [id] stored in the global name pairs then replace
% the [id] with the unique name [id] stored in the pair
% as its old type no longer exits as it has been renamed
rule renameUserFieldTypes
	import NameList [repeat pair]
	skipping [named_type]
	replace $ [named_type]
		DECL [decl] T [type]	% Iterate through all the [named_type]'s
	by
		DECL T [replaceSizeType NameList]
			[replaceSetOfType NameList]
end rule

% Function to check the [type] reference in any size type definitions
% to see if it needs to be updated to the unique name reference
function replaceSizeType NL [repeat pair]
	replace [type]
		ID [id] SC [size_constraint] OP [opt endian] OPSL [opt slack]
	deconstruct * [pair] NL
		First [id] ID 	% Current [id] for the type has been previously
						% found and therefore has a unique name. The
						% reference here must be updated to the unique name
	by
		First SC OP OPSL 	% Replace old short reference with unique name
end function

% Function to check the [type] reference in any set of type definitions
% to see if it needs to be updated to the unique name reference
function replaceSetOfType NL [repeat pair]
	replace [type]
		'SET 'OF ID [id] SC [size_constraint]
	deconstruct * [pair] NL
		First [id] ID 	% Current [id] for the type has been previously
						% found and therefore has a unique name. The
						% reference here must be updated to the unique name
	by
		'SET 'OF First SC 	% Replace old short reference with unique name
end function


% Step 1.3: 
rule renameRefContraint Rules [repeat rule_definition]
	skipping [type_rule_definition]
	replace $ [type_rule_definition]
		R [type_rule_definition]
	by 
		R [doSeq Rules]
end rule

rule doSeq Rules [repeat rule_definition]
	skipping [type_rule_definition]
	replace $ [type_rule_definition]
		D [decl] '::= 'SEQUENCE OS [opt size_constraint] '{
			EL [list element_type] OP [opt ',]
		'} ENC [opt encoding_grammar_indicator] SZ [opt size_markers_block]
		'<transfer>
		RETR [repeat transfer_statement]
		'</transfer>
		CST [opt constraints_block]
	by
		D '::= 'SEQUENCE OS '{
			EL OP
		'} ENC SZ 
		'<transfer>
		RETR [checkBackConstraint EL Rules D] [checkForwardConstraint EL Rules D]
		'</transfer>
		CST
end rule

rule checkBackConstraint Elist [list element_type] Rules [repeat rule_definition] RefName [decl]
	replace $ [back_block]
		'Back '{ OR [or_expression] '}
	deconstruct not OR
		'GLOBAL '( RE [referenced_element] ') '== REST [relational_expression] 
	by
		'Back '{ OR [renameTransferStatement Elist Rules] [renameTransferFromRuleDef Elist Rules] [checkForUndefinedStats RefName] '}
end rule

rule renameTransferStatement Elist [list element_type] Rules [repeat rule_definition]
	skipping [referenced_element]
	replace $ [referenced_element]
		SHORT [id] REST [repeat dot_rp]
	deconstruct * [named_type]  Elist
		FULL [id] '^ SHORT TYPE [type]
	by
		FULL REST [recurseRename TYPE Rules]
end rule

function recurseRename Type [type] Rules [repeat rule_definition]
	replace [repeat dot_rp]
		'. ID [id] REST [repeat dot_rp]
	deconstruct Type
		RTYPE [id] _ [size_constraint]
	deconstruct * [rule_definition] Rules
		RTYPE '^ Short [id] '::= 'SEQUENCE _ [opt size_constraint] '{
			EL [list element_type] _ [opt ',]
		'} _ [opt scl_additions]
	deconstruct * [named_type] EL
		FULL [id] '^ ID TYPE2 [type]
	by
		'. FULL REST [recurseRename TYPE2 Rules]
end function

rule renameTransferFromRuleDef Elist [list element_type] Rules [repeat rule_definition]
	skipping [referenced_element]
	replace $ [referenced_element]
		SHORT [id] REST [repeat dot_rp]
	deconstruct * [rule_definition] Rules
		FULL [id] '^ SHORT '::= 'SEQUENCE _ [opt size_constraint] '{
			EL [list element_type] _ [opt ',]
		'} _ [opt scl_additions]
	by
		FULL REST
end rule

% Possible issue - what if the first id has been renamed ( with underscores )
% and additional ids have not been renamed? Need to check for that
rule checkForUndefinedStats RefName [decl]
	skipping [referenced_element]
	replace $ [referenced_element]
		ID [id] REST [repeat dot_rp]
	construct US [number]
		_ [index ID "_"]
	deconstruct US
		0
	deconstruct RefName
		LONG [id] '^ SHORT [id]
 	construct err [id]
		_ [+ "Undefined statement reference \""]
		[+ ID]
		[+ "\" in type rule \""]
		[+ LONG]
		[+ "\""]
		[print]
	by
		ID REST
end rule

rule checkForwardConstraint Elist [list element_type] Rules [repeat rule_definition] RefName [decl]
	replace $ [forward_block]
		'Forward '{ OR [or_expression] '}
	by
		'Forward '{ OR [renameTransferStatement Elist Rules] [renameTransferFromRuleDef Elist Rules] '}
end rule


% Step 1.4: Rename the references in any [type_decision]
% rules to have the proper unique names for the type they
% represent by appending the module name
rule renameConstructionAssignments ModName [id]
	skipping [construction_assignment_statement]
	replace $ [construction_assignment_statement]
		CA [construction_assignment_statement]
	by
		CA [addConstDef ModName]
end rule

% Find all type decision rules in the module and rename
% the [type_decision] references portion
function addConstDef ModName [id]
	replace [construction_assignment_statement]
		First [id] '^ Short [id] '::= TD [type_decision] OPT [opt scl_additions]
	by
		First '^ Short '::= TD [renConst ModName] OPT
end function

%% NOTE: type decisions that have a '.' are considered part of an import's module, and so are renamed
%% accordingly in renTRImports

% Function to break apart a [type_decision] into its
% elements and rename them to their new unique names
rule renConst ModName [id]
	skipping [type_decision]
	replace $ [type_decision]
		'( TR [type_reference] ALT [repeat alternative_decision]')
	by
		'( TR [renTR ModName] [renTRImports] ALT [recurseRenConst ModName] [recurseRenConstImports] ')
		% Rename the first [type_reference] and then the remaining set of [alternative_decision]
end rule

% Basic rename of the reference by adding the module
% name; This is the definition of its unique name
% so no matching is required
function renTR ModName [id]
	replace [type_reference]
		ID [id]
	construct NEW [id]
		ID [+ "_"] [+ ModName]
	by
		NEW
end function

% Basic rename of a type decision reference that has
% been imported. The unique name is defined as appending
% the [id] to the end of the [dotID]'s [id]
function renTRImports
	replace [type_reference]
		ID [id] OP [dotID]
	deconstruct OP
		'. TR [id]
	construct IMPORTID [id]
		TR [+ "_"] [+ ID]
	by
		ID '. IMPORTID
end function

% Basic rename of the next reference in the set
% of [alternative_decision]. Rename the next by 
% adding the module name per definition and repeat
% on the remaining portion of [alternative_decision]
function recurseRenConst ModName [id]
	replace [repeat alternative_decision]
		'| ID [id] REST [repeat alternative_decision]
	construct NEW [id]
		ID [+ "_"] [+ ModName]
	by
		'| NEW REST [recurseRenConst ModName]
end function

% Basic rename of a set of [alternative_decision] that has
% been imported. The unique name is defined as appending the
% [id] to the end of the [dotID]'s [id]. Repeat by calling
% on the remaining portion of [alternative_decision]
function recurseRenConstImports
	replace [repeat alternative_decision]
		'| ID [id] OP [dotID] REST [repeat alternative_decision]
	deconstruct OP
		'. TR [id]
	construct IMPORTID [id]
		TR [+ "_"] [+ ID]
	by
		'| ID '. IMPORTID REST [recurseRenConstImports]
end function


% Step 2: Create an export table file of all the references
% that this module exports. This file will be named "ModuleName".exports
% and will be used to check against imports in other modules when
% they import this one
rule createExportTable
	skipping [module_definition]
	replace $ [module_definition]
		ID [id] 'DEFINITIONS OP [opt tag_default] '::= 'BEGIN
			Exports [opt export_block]
			Imports [opt import_block]
			Body [repeat rule_definition]
		'END
	by
		ID 'DEFINITIONS OP '::= 'BEGIN
			Exports [checkExports ID]	% Iterate through the contents
										% of the module's [export_block]
			Imports 
			Body
		'END 	% No replacement
end rule

% Break the [export_block] into its terminal and [decl]
% list
rule checkExports ModuleName [id]
	skipping [export_block]
	replace $ [export_block]
		'EXPORTS DECL [list decl] '; 
	by
		'EXPORTS DECL [checkExport ModuleName] '; 	% No replacement
		% Send the list of [decl] to be exported
end rule

% Construct the export table file which contains the
% list of all references being exported from this module
function checkExport ModuleName [id]
	replace [list decl]
		LIST [list decl]
	construct ExportTable [import_list]
		LIST 'FROM ModuleName 	% Construct as an import list as
								% the other modules will read this
								% module's exports as imports;
								% Need to use the [import_list] grammar
	construct outputFile [stringlit]
		_ [+ "INTERMEDIATE/"] [+ ModuleName] [+ ".exports"]
	construct output [import_list]
		ExportTable [write outputFile]	% Write the table to the
										% specified filename
	by
		LIST 	% No replacement
end function