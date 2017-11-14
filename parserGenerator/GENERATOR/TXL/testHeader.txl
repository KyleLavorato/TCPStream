include "../GRM/c.grm"
%include "GRM/cNew.grm"
include "../GRM/ASNOne.Grm"

redefine type_rule_definition
	% scl5
	...
	% C
	| [function_definition_or_declaration]
end redefine

redefine construction_assignment_statement
	% scl5
	...
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

function main
	replace [program]
		P [program]
	by
		P
end functionou