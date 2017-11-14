
include "../GRM/c.grm"


define program
  [cprogram]
end define

function main
  replace [program]
     FD [repeat function_definition_or_declaration]
  construct ModName [id]
      'Foo
  construct PRENAME [stringlit]
    _ [+ "#ifndef "]
      [+ ModName]
  construct PRE [opt preprocessor]
    _ [parse PRENAME]
  deconstruct PRE
     PRE2 [preprocessor]
  construct PREFD [function_definition_or_declaration]
     PRE2
  by
     PREFD
end function
