include "../GRM/c.grm"
include "../GRM/ASNOne.Grm"

redefine type_rule_definition
	% C
	% scl5 
	[decl] [opt annotation] '::= [type] [opt scl_additions]
 | [repeat function_definition_or_declaration]
	end 
redefine

redefine construction_assignment_statement
	% scl5
	...
	| [decl] [opt optimizable] '::= [type_decision]	
	% C
	| [repeat function_definition_or_declaration]
end redefine

redefine program
	...
	| [repeat preprocessor]
		[repeat rule_definition]
		[opt preprocessor]
end redefine

define optimizable
	'@ 'optimizable
end define

define annotation
	%size    %value
	'@ [number] [number] [opt optimizable]
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
	[id] [opt hatID] [opt annotation] [opt optimizable]
end redefine

redefine constant
	...
	| 'NULL
end redefine

redefine cexpression
	...
	| [relational_expression]
end redefine

define derefID
	[SPOFF]'->[id][SPON]
	| [SPOFF]'.[id][SPON]
	%'->[id]
	%| '.[id]
end define

redefine constant
	...
	| [constant] [repeat derefID][SPOFF]'[[id]'][SPON]
	%| [id] [repeat derefID] '[i']
	| [constant] [repeat derefID]
	%| [id] [repeat derefID]
	| [relational_expression]
end redefine

redefine size_of_expn
	...
	| 'sizeof '( [referenced_element] ')
end redefine

redefine referencable_primaries
	...
	| [SPOFF][id]'->[id][SPON]
end redefine

redefine alternative_decision
	...
	| [repeat alternative_decision]
end redefine

redefine label
	...
	| [EX][SP][SP] 'case [constant_cexpression] ': [IN] [NL] [unlabeled_statement]
end redefine

function main
	replace [program]
		P [program]
	by
		P
end function