include "ASNOne.Grm"

%redefine decl
%	[id] [opt hashID]
%end redefine

%define hashID
%   '# [id]
%end define
redefine construction_assignment_statement
	[decl] '::= [type_decision] [opt scl_additions]				[NL]
end redefine

function main
	replace [program]
		P [program]
	by
		P [findImports]
end function

%renRefFieldTypes
%renRefConstraints

rule findImports
	skipping [module_definition]
	replace $ [module_definition]
		ID [id] 'DEFINITIONS OP [opt tag_default] '::= 'BEGIN
			Exports [opt export_block]
			Imports [opt import_block]
			Body [repeat rule_definition]
		'END
	by
		ID 'DEFINITIONS OP '::= 'BEGIN 
		Exports
		Imports [checkBlock ID]
		Body
		'END
end rule

rule checkBlock ModuleName [id]
	skipping [import_block]
	replace $ [import_block]
		'IMPORTS LIST [list import_list+] ';
	%construct ExportTable [repeat import_list]
	%	_ [read "Exports.txt"]
	by
		'IMPORTS LIST [checkImportLists ModuleName] ';
end rule

function checkImportLists ModuleName [id]
	replace [list import_list+]
		LIST [list decl] 'FROM MOD [id] ', REST [list import_list+]
	by
		LIST  'FROM MOD [checkList ModuleName LIST] ', REST [checkImportLists ModuleName]
end function

function checkList Modulename [id] LIST [list decl]
	replace [id]
		ImportModuleName [id]
	construct File [stringlit]
		_ [+ ImportModuleName] [+ ".exports"]
	construct ExportTable [opt import_list]
		_ [read File]
	deconstruct ExportTable
		EXLIST [list decl] 'FROM MOD [id]
	by
		ImportModuleName [checkEachImport EXLIST Modulename each LIST]

end function

function checkEachImport EXLIST [list decl] ModuleName [id] ImportItem [decl]
	match [id]
		ImportModuleName [id]
	deconstruct not * [list decl] EXLIST
		ImportItem
	deconstruct ImportItem
	    _ [id] '^ ImportItemName [id]

	construct QUIT [stringlit]
		_ [+ "Undefined import  \""]
		[+ ImportItemName]
		[+ "\" from module \""]
		[+ ImportModuleName]
		[+ "\" in module \""]
		[+ ModuleName]
		[+ "\""]
		[print]
		[quit 99]
end function