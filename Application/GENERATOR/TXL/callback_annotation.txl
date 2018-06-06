% Callback Annotation
% Kyle Lavorato
% Queen's University, June 2017

% Copyright 2017 Thomas Dean

% Revision history:

% 1.3 Type decision ^ Callback 		- KPL	20 06 2017
% 1.2 Addition of Callback Final	- KPL	19 06 2017
% 1.1 Documentation and Bug Fix		- KPL	16 06 2017
% 1.0 Initial revision 				- KPL	14 06 2017

% This program searches through a SCL5 file for any "Callback" in the transfer
% statement that can be optimized. A callback can be optimized if the final
% element in the definition SEQUENCE is a SET OF [TYPE].

% The input to the program is a SCL5 file named "protocol"_UID.scl5. The input
% file has been transformed from the base scl5 already through two TXL scripts
% in the TXL pipeline to ensure all naming is unique.

% The output of this program is a SCL5 file named 
% "protocol"_UID_callbackAnnotated.scl5. The output file has added annotations
% to any detected Callback's in the input file where optimization is possible


% Base grammar

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

redefine callback_annotation
     [id] [id]  % New callback annotated with the original type (eg full_rtps)
   | '@ [id] % Original callback annotated with what is being optimized
   | '^ [id] [id]
   | 'Final
   | '# [id] [opt callback_annotation] % Intermediate form for this TXL script
end define

% Main rule followed by other rules in topological order

function main
	replace [program]
		P [program]

	% Global variable to hold any intermediate callbacks that indicate 
	% the type decision rule that the parent callback refers to
	construct callbackSetOf [repeat callback_annotation]
	export callbackSetOf

	% Global variable to hold any intermediate callbacks that indicate
	% they need a callback with annotation placed in the specified definition
	construct placeCallback [repeat callback_annotation]
	export placeCallback
	
	% Extraction of all the rule definitions
	construct ALLRULES [repeat rule_definition]
		_ [^ P]

	by
		P [annotateInitialCallback ALLRULES]
		  [checkForSetOfCallback]
		  [annotateMinorCallback]
		  [replaceCallbackFinal]
end function


% Step 1: Find all original callbacks in the scl5 specification; Annotate them
% if they are optimizable and populate the referenced intermediate form 
% in global: callbackSetOf
rule annotateInitialCallback RULES [repeat rule_definition]
	replace $ [type_rule_definition]
		LONG [id] '^ SHORT [id] '::= 'SEQUENCE OS [opt size_constraint] '{
			LE [list element_type] OC [opt ',]
		'} OP [opt scl_additions]
	where
		OP [matchCallback]	% Only process the rule if it contains a callback
	deconstruct not * [transfer_statement] OP
		'Callback 'Final
	construct callbackAnnotation [opt callback_annotation]
		_ [findFinalSetOf each LE]	% Create a callback annotation only if the 
									% callback can be optimized; Otherwise EOF
	deconstruct [opt callback_annotation] callbackAnnotation
		'# SUBSHORT [id] '@ TYPE [id]	% If the constructed annotation is EOF
										% then the statement cannot be optimized
	construct tempCallbackConstruct [callback_annotation]
		'# TYPE LONG SUBSHORT	% Create an intermediate annotation to go in
								% callbackSetOf to indicate callbacks need to
								% be generated for the types in the LONG 
								% type decision
	deconstruct * [construction_assignment_statement] RULES
		TYPE '^ SHORTSUB [id] '::= '( TRSUB [type_reference] RTRSUB [repeat alternative_decision] ') OPSUB [opt scl_additions]
		% In order for the callback to be valid for annotation the SET OF [TYPE] must be a type desicion
	import callbackSetOf [repeat callback_annotation]
	export callbackSetOf
		callbackSetOf [. tempCallbackConstruct]
	construct finalCallbackAnnotation [opt callback_annotation]
		'@ TYPE % The annotation that will be added to the original callback
	construct newAdditions [opt scl_additions]
		OP [appendCallbackAnnotation finalCallbackAnnotation]	% Add the annotation
																% to the callback
	by
		LONG '^ SHORT '::= 'SEQUENCE OS '{
			LE OC
		'} newAdditions
end rule

% Attempt to find a callback transfer statement
function matchCallback
	match * [transfer_statement]
		'Callback OP [opt callback_annotation]
end function

% NOTE:
% The method to cycle through the [list element_type] is somewhat complicated
% The final element must be checked to see if it is a SET OF type and if so, 
% generate an annotation; To accomplish this, every non-set of will replace
% with EOF and any SET OF will create an annotation. The final result will
% be the result of the last element replacement as desired.

% Function used to cycle through a [list element_type]; SEE NOTE ABOVE
function findFinalSetOf LE [element_type]
	replace [opt callback_annotation]
		OP [opt callback_annotation]
	construct annotation [opt callback_annotation]
		_ [generateAnnotation LE]
	by
		annotation
end function

% Function to replace the existing annotation with a newly generated annotation
% if the [element_type] is a SET OF type; SEE NOTE ABOVE
function generateAnnotation LE [element_type]
	replace [opt callback_annotation]
		OP [opt callback_annotation]
	deconstruct [element_type] LE
		LONG [id] '^ SHORT [id] 'SET 'OF TYPE [id] '('SIZE 'CONSTRAINED')
	by
		'# SHORT '@ TYPE % The new annotaion for the original callback inside a temp
end function

% Function to find the original callback in the transfer_rules_block and append the
% annotation while preserving the rest of the scl_additions
function appendCallbackAnnotation ANN [opt callback_annotation]
	replace [opt scl_additions]
		GR [opt encoding_grammar_indicator] SZ [opt size_markers_block] 
		TR [opt transfer_rules_block]
    	CB [opt constraints_block] 
    deconstruct [opt transfer_rules_block] TR
    	'<transfer>
    	TS [repeat transfer_statement]
    	'</transfer>
    deconstruct * [transfer_statement] TS
    	'Callback OP [opt callback_annotation]
    construct AnnotatedTS [repeat transfer_statement]
    	_ [saveTS each TS] [annotateCallbackLine ANN each TS]	% Add the annotation
    															% and preserve other
    															% transfer statements
    construct AnnotatedTR [opt transfer_rules_block]
    	'<transfer>
    	AnnotatedTS
    	'</transfer>
    by
    	GR
    	SZ
    	AnnotatedTR
    	CB
end function

% Function to save any transfer_statement that is not a callback
function saveTS TS [transfer_statement]
	where not
		TS [matchCallback]
	replace [repeat transfer_statement]
		RTS [repeat transfer_statement]
	by
		RTS [. TS]
end function

% Function to append an annotation and save a Callback transfer_statement
function annotateCallbackLine ANN [opt callback_annotation] TS [transfer_statement]
	where
		TS [matchCallback]
	replace [repeat transfer_statement]
		RTS [repeat transfer_statement]
	construct annotatedCallback [transfer_statement]
		'Callback ANN
	by
		RTS [. annotatedCallback]
end function


% Step 2: Cycle through all type definition modules, checking if they 
% have a pending callback optimization in the global variable callbackSetOf.
% If there is a pending optimization, populate the global variable placeCallback
% for each type in the type decision and add the callback to the type decision module
rule checkForSetOfCallback
	replace $ [construction_assignment_statement]
		LONG [id] '^ SHORT [id] '::= '( TR [type_reference] RTR [repeat alternative_decision] ') OPT [opt scl_additions]
	import callbackSetOf [repeat callback_annotation]
	construct UNUSED [opt callback_annotation]
		_ [checkForSetOfMatch LONG TR each callbackSetOf] [unpackRTR LONG each RTR]
	construct NewOPT [opt scl_additions]
		OPT [annotateTypeDecisionWithTransfer LONG each callbackSetOf] [annotateTypeDecisionWithoutTransfer LONG each callbackSetOf]
	by
		LONG '^ SHORT '::= '( TR RTR ') NewOPT
end rule

% Function to check if the [id] from the type decision module and the [id] 
% from each of the global variable's annotation entries match. If there is a
% match then an annotation is generated for the passed in [type_reference]
function checkForSetOfMatch LONG [id] TR [type_reference] TEMP [callback_annotation]
	replace [opt callback_annotation]
		P [opt callback_annotation]
	deconstruct [callback_annotation] TEMP
		'# TYPE [id] ANN [opt callback_annotation]
	where
		TYPE [matchCallbackLong LONG]	% Only run if the LONG matches the [id]
										% in the [callback_annotation]
	construct minorAnnotations [repeat callback_annotation]
		_ [genMinorAnnotations ANN TR]
	import placeCallback [repeat callback_annotation]
	export placeCallback
		placeCallback [. minorAnnotations]
	by
		P 
end function

% Check if the [id] matches the [id] in LONG
function matchCallbackLong LONG [id]
	match [id]
		LONG
end function

% Function to generate the temporary form [callback_annotation] to be used
% in generating the optimized callbacks in Step 3
function genMinorAnnotations ANN [opt callback_annotation] TR [type_reference]
	replace [repeat callback_annotation]
		callANN [repeat callback_annotation]
	deconstruct [type_reference] TR
		TYPE [id] OPT [opt dotID]
	construct newANN [callback_annotation]
		'# TYPE ANN	% Temporary form for the optimizd callback; TYPE is the 
					% module that needs the callback; ANN is the annotation
	by
		callANN [. newANN]
end function

% Function to unpack the [alternative_decision] from the type decision
% module and call checkForSetOfMatch for each [type_reference] in the 
% unpacked data
function unpackRTR LONG [id] RTR [alternative_decision]
	replace [opt callback_annotation]
		P [opt callback_annotation]
	deconstruct [alternative_decision] RTR
		'| TR [type_reference]
	import callbackSetOf [repeat callback_annotation]
	construct UNUSED [opt callback_annotation]
		_ [checkForSetOfMatch LONG TR each callbackSetOf]
	by
		P
end function

% Function to append an annotated type decision callback to an existing 
% [transfer_rules_block] in a type decision module
function annotateTypeDecisionWithTransfer LONG [id] TEMP [callback_annotation]
	replace [opt scl_additions]
		GR [opt encoding_grammar_indicator] 
		SZ [opt size_markers_block] 
		TR [opt transfer_rules_block]
    	CB [opt constraints_block] 
    deconstruct [opt transfer_rules_block] TR
    	'<transfer>
    	TS [repeat transfer_statement]
    	'</transfer> 
	deconstruct [callback_annotation] TEMP
		'# TYPE [id] ID1 [id] ID2 [id]
	where
		TYPE [matchCallbackLong LONG]	% Only run if the LONG matches the [id]
										% in the [callback_annotation]
	construct callback [transfer_statement]
		'Callback '^ ID1 ID2
	by
		GR
		SZ
		'<transfer>
		TS [. callback]
		'</transfer>
		CB
end function

% Function to add a [transfer_rules_block] and annotated type decision callback
% in a type decision module
function annotateTypeDecisionWithoutTransfer LONG [id] TEMP [callback_annotation]
	replace [opt scl_additions]
		GR [opt encoding_grammar_indicator] 
		SZ [opt size_markers_block] 
		TR [opt transfer_rules_block]
    	CB [opt constraints_block] 
    deconstruct not [opt transfer_rules_block] TR
    	'<transfer>
    	TS [repeat transfer_statement]
    	'</transfer> 
	deconstruct [callback_annotation] TEMP
		'# TYPE [id] ID1 [id] ID2 [id]
	where
		TYPE [matchCallbackLong LONG]	% Only run if the LONG matches the [id]
										% in the [callback_annotation]
	construct callback [transfer_statement]
		'Callback '^ ID1 ID2
	by
		GR
		SZ
		'<transfer>
		callback
		'</transfer>
		CB
end function


% Step 3: Cycle through all sequence definition modules, checking if they 
% have a pending callback placement in the global variable placeCallback.
% If there is a pending placement then generate and append a Callback with
% the annotation to the module's [transfer_rules_block]
rule annotateMinorCallback
	replace $ [type_rule_definition]
		LONG [id] '^ SHORT [id] '::= 'SEQUENCE OS [opt size_constraint] '{
			LE [list element_type] OC [opt ',]
		'} OP [opt scl_additions]
	import placeCallback [repeat callback_annotation]
	construct newAdditions [opt scl_additions]
		OP [checkForMinorMatchWithTransfer LONG each placeCallback] [checkForMinorMatchWithoutTransfer LONG each placeCallback]
	by
		LONG '^ SHORT '::= 'SEQUENCE OS '{
			LE OC
		'} newAdditions
end rule

% Function to check if the [id] from the module and the [id] from each of 
% the global variable's annotation entries match. If there is a match then 
% a Callback is appended to the [transfer_rules_block] with annotation
function checkForMinorMatchWithTransfer LONG [id] TEMP [callback_annotation]
	replace [opt scl_additions]
		GR [opt encoding_grammar_indicator] 
		SZ [opt size_markers_block] 
		TR [opt transfer_rules_block]
    	CB [opt constraints_block]
    deconstruct [opt transfer_rules_block] TR
    	'<transfer>
    	TS [repeat transfer_statement]
    	'</transfer> 
	deconstruct [callback_annotation] TEMP
		'# TYPE [id] ANN [opt callback_annotation]
	where
		TYPE [matchCallbackLong LONG]
	construct newCallback [transfer_statement]
		'Callback ANN
    construct newTR [opt transfer_rules_block]
    	'<transfer>
    	TS [. newCallback]
    	'</transfer>
	by
		GR
		SZ
		newTR
		CB
end function

% Function to check if the [id] from the module and the [id] from each of 
% the global variable's annotation entries match. If there is a match then 
% a Callback with annotation and a [transfer_rules_block] is generated
function checkForMinorMatchWithoutTransfer LONG [id] TEMP [callback_annotation]
	replace [opt scl_additions]
		GR [opt encoding_grammar_indicator] 
		SZ [opt size_markers_block] 
		TR [opt transfer_rules_block]
    	CB [opt constraints_block] 
    deconstruct not [opt transfer_rules_block] TR
    	'<transfer>
    	TS [repeat transfer_statement]
    	'</transfer> 
	deconstruct [callback_annotation] TEMP
		'# TYPE [id] ANN [opt callback_annotation]
	where
		TYPE [matchCallbackLong LONG]
	construct newCallback [transfer_statement]
		'Callback ANN
    construct newTR [opt transfer_rules_block]
    	'<transfer>
    	newCallback
    	'</transfer>
	by
		GR
		SZ
		newTR
		CB
end function


% Step 4: Find any callbacks that have been annotated as 'Final and remove
% the annotation as the remainder of the TXL pipeline expects them to have
% no annotation
rule replaceCallbackFinal
	replace $ [type_rule_definition]
		LONG [id] '^ SHORT [id] '::= 'SEQUENCE OS [opt size_constraint] '{
			LE [list element_type] OC [opt ',]
		'} OP [opt scl_additions]
	deconstruct * [transfer_statement] OP
		'Callback 'Final
	construct finalCallbackAnnotation [opt callback_annotation]
		_ 	% Remove Final annotation from the callback
	construct newAdditions [opt scl_additions]
		OP [appendCallbackAnnotation finalCallbackAnnotation]	% Add the annotation
																% to the callback
	by
		LONG '^ SHORT '::= 'SEQUENCE OS '{
			LE OC
		'} newAdditions
end rule