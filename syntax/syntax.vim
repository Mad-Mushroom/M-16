" M-16 Syntax for VIM

if exists("b:current_syntax")
  finish
endif

syn keyword mSpecial \$
syn keyword mReg a b c d f h l z
syn keyword mTodo contained TODO
syn match mComment ";.*$" contains=mTodo
syn match mDirective "^\s*[@][a-zA-Z]\+"
syn match mMacroArg "%[a-zA-Z0-9_]\+"
syn match mNumber "0x[0-9a-fA-F]\+"
syn match mNumber "\<[0-9]\+D\=\>"
syn match mOp "^\s*[a-zA-Z0-9_]\+\s"
syn match mOp "^\s*[a-zA-Z0-9_]\+$"
syn match mMicroOp "^\s*[~]\=[a-zA-Z0-9_]\+[,]\s*\([~]\=[a-zA-Z0-9_]\+[,]\=\s*\)\+"

syn region mLabel start="^\s*[a-zA-Z0-9_.]" end=":" oneline contains=mLabelName,mMacroArg,mAddr
syn region mString start='"' end='"'
syn region mAddr start='\[' end='\]' contains=mMacroArg,mAddrLabel

syn match mLabelName "^[a-zA-Z0-9_\.]\+:\=" contained
syn match mAddrLabel '[a-zA-Z0-9_\.]\+' contained

let b:current_syntax = "m16"
hi def link mSpecial Special
hi def link mTodo Todo
hi def link mComment Comment
hi def link mLabelName Label
hi def link mAddrLabel Label
hi def link mDirective Macro
hi def link mOp Function
hi def link mMicroOp Function
hi def link mMacroArg Special
hi def link mReg Identifier
hi def link mNumber Number
hi def link mString String
