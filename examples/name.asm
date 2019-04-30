;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;               Start of Code Segment                 ;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
main:
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; LoadImmidiate(A, B) {                               ;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	rssb print_arg
	rssb print_arg
	rssb print_arg
	rssb print_arg
	rssb $+7
	rssb zero
	rssb zero
	rssb print_arg
	rssb acc
	rssb acc
	rssb neg
	rssb str_intro
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; }                                                   ;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; Call() {                                            ;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;Store our location in the stack.
	rssb $+34
	rssb $+33
	rssb $+32
	rssb $+31
	rssb ___REBEC_STACK_POINTER___
	rssb zero
	rssb zero
	rssb $+27
	rssb $+27
	rssb $+26
	rssb $+25
	rssb $+24
	rssb ___REBEC_STACK_POINTER___
	rssb zero
	rssb zero
	rssb $+20
	rssb $+20
	rssb $+19
	rssb $+18
	rssb $+17
	rssb ___REBEC_STACK_POINTER___
	rssb zero
	rssb zero
	rssb $+13
	rssb $+18
	rssb $+17
	rssb $+16
	rssb $+15
	rssb ___REBEC_STACK_POINTER___
	rssb zero
	rssb zero
	rssb $+11
	rssb acc
	rssb acc
	rssb 0
	rssb 0
	rssb 0
	rssb acc
	rssb acc
	rssb $+7
	rssb zero
	rssb zero
	rssb 0
	rssb acc
	rssb acc
	rssb neg
	rssb $+17
;Increment the stack pointer.
	rssb acc
	rssb acc
	rssb pos
	rssb zero
	rssb zero
	rssb ___REBEC_STACK_POINTER___
;Jump to the call.
	rssb acc
	rssb acc
	rssb $+7
	rssb zero
	rssb zero
	rssb pc
	rssb acc
	rssb acc
	rssb neg
	rssb print-$+3
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; }                                                   ;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; LoadImmidiate(A, B) {                               ;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	rssb read_arg
	rssb read_arg
	rssb read_arg
	rssb read_arg
	rssb $+7
	rssb zero
	rssb zero
	rssb read_arg
	rssb acc
	rssb acc
	rssb neg
	rssb str_name
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; }                                                   ;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; Call() {                                            ;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;Store our location in the stack.
	rssb $+34
	rssb $+33
	rssb $+32
	rssb $+31
	rssb ___REBEC_STACK_POINTER___
	rssb zero
	rssb zero
	rssb $+27
	rssb $+27
	rssb $+26
	rssb $+25
	rssb $+24
	rssb ___REBEC_STACK_POINTER___
	rssb zero
	rssb zero
	rssb $+20
	rssb $+20
	rssb $+19
	rssb $+18
	rssb $+17
	rssb ___REBEC_STACK_POINTER___
	rssb zero
	rssb zero
	rssb $+13
	rssb $+18
	rssb $+17
	rssb $+16
	rssb $+15
	rssb ___REBEC_STACK_POINTER___
	rssb zero
	rssb zero
	rssb $+11
	rssb acc
	rssb acc
	rssb 0
	rssb 0
	rssb 0
	rssb acc
	rssb acc
	rssb $+7
	rssb zero
	rssb zero
	rssb 0
	rssb acc
	rssb acc
	rssb neg
	rssb $+17
;Increment the stack pointer.
	rssb acc
	rssb acc
	rssb pos
	rssb zero
	rssb zero
	rssb ___REBEC_STACK_POINTER___
;Jump to the call.
	rssb acc
	rssb acc
	rssb $+7
	rssb zero
	rssb zero
	rssb pc
	rssb acc
	rssb acc
	rssb neg
	rssb read-$+3
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; }                                                   ;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; LoadImmidiate(A, B) {                               ;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	rssb print_arg
	rssb print_arg
	rssb print_arg
	rssb print_arg
	rssb $+7
	rssb zero
	rssb zero
	rssb print_arg
	rssb acc
	rssb acc
	rssb neg
	rssb str_response
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; }                                                   ;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; Call() {                                            ;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;Store our location in the stack.
	rssb $+34
	rssb $+33
	rssb $+32
	rssb $+31
	rssb ___REBEC_STACK_POINTER___
	rssb zero
	rssb zero
	rssb $+27
	rssb $+27
	rssb $+26
	rssb $+25
	rssb $+24
	rssb ___REBEC_STACK_POINTER___
	rssb zero
	rssb zero
	rssb $+20
	rssb $+20
	rssb $+19
	rssb $+18
	rssb $+17
	rssb ___REBEC_STACK_POINTER___
	rssb zero
	rssb zero
	rssb $+13
	rssb $+18
	rssb $+17
	rssb $+16
	rssb $+15
	rssb ___REBEC_STACK_POINTER___
	rssb zero
	rssb zero
	rssb $+11
	rssb acc
	rssb acc
	rssb 0
	rssb 0
	rssb 0
	rssb acc
	rssb acc
	rssb $+7
	rssb zero
	rssb zero
	rssb 0
	rssb acc
	rssb acc
	rssb neg
	rssb $+17
;Increment the stack pointer.
	rssb acc
	rssb acc
	rssb pos
	rssb zero
	rssb zero
	rssb ___REBEC_STACK_POINTER___
;Jump to the call.
	rssb acc
	rssb acc
	rssb $+7
	rssb zero
	rssb zero
	rssb pc
	rssb acc
	rssb acc
	rssb neg
	rssb print-$+3
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; }                                                   ;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; LoadImmidiate(A, B) {                               ;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	rssb print_arg
	rssb print_arg
	rssb print_arg
	rssb print_arg
	rssb $+7
	rssb zero
	rssb zero
	rssb print_arg
	rssb acc
	rssb acc
	rssb neg
	rssb str_name
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; }                                                   ;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; Call() {                                            ;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;Store our location in the stack.
	rssb $+34
	rssb $+33
	rssb $+32
	rssb $+31
	rssb ___REBEC_STACK_POINTER___
	rssb zero
	rssb zero
	rssb $+27
	rssb $+27
	rssb $+26
	rssb $+25
	rssb $+24
	rssb ___REBEC_STACK_POINTER___
	rssb zero
	rssb zero
	rssb $+20
	rssb $+20
	rssb $+19
	rssb $+18
	rssb $+17
	rssb ___REBEC_STACK_POINTER___
	rssb zero
	rssb zero
	rssb $+13
	rssb $+18
	rssb $+17
	rssb $+16
	rssb $+15
	rssb ___REBEC_STACK_POINTER___
	rssb zero
	rssb zero
	rssb $+11
	rssb acc
	rssb acc
	rssb 0
	rssb 0
	rssb 0
	rssb acc
	rssb acc
	rssb $+7
	rssb zero
	rssb zero
	rssb 0
	rssb acc
	rssb acc
	rssb neg
	rssb $+17
;Increment the stack pointer.
	rssb acc
	rssb acc
	rssb pos
	rssb zero
	rssb zero
	rssb ___REBEC_STACK_POINTER___
;Jump to the call.
	rssb acc
	rssb acc
	rssb $+7
	rssb zero
	rssb zero
	rssb pc
	rssb acc
	rssb acc
	rssb neg
	rssb print-$+3
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; }                                                   ;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; LoadImmidiate(A, B) {                               ;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	rssb print_arg
	rssb print_arg
	rssb print_arg
	rssb print_arg
	rssb $+7
	rssb zero
	rssb zero
	rssb print_arg
	rssb acc
	rssb acc
	rssb neg
	rssb str_final
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; }                                                   ;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; Call() {                                            ;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;Store our location in the stack.
	rssb $+34
	rssb $+33
	rssb $+32
	rssb $+31
	rssb ___REBEC_STACK_POINTER___
	rssb zero
	rssb zero
	rssb $+27
	rssb $+27
	rssb $+26
	rssb $+25
	rssb $+24
	rssb ___REBEC_STACK_POINTER___
	rssb zero
	rssb zero
	rssb $+20
	rssb $+20
	rssb $+19
	rssb $+18
	rssb $+17
	rssb ___REBEC_STACK_POINTER___
	rssb zero
	rssb zero
	rssb $+13
	rssb $+18
	rssb $+17
	rssb $+16
	rssb $+15
	rssb ___REBEC_STACK_POINTER___
	rssb zero
	rssb zero
	rssb $+11
	rssb acc
	rssb acc
	rssb 0
	rssb 0
	rssb 0
	rssb acc
	rssb acc
	rssb $+7
	rssb zero
	rssb zero
	rssb 0
	rssb acc
	rssb acc
	rssb neg
	rssb $+17
;Increment the stack pointer.
	rssb acc
	rssb acc
	rssb pos
	rssb zero
	rssb zero
	rssb ___REBEC_STACK_POINTER___
;Jump to the call.
	rssb acc
	rssb acc
	rssb $+7
	rssb zero
	rssb zero
	rssb pc
	rssb acc
	rssb acc
	rssb neg
	rssb print-$+3
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; }                                                   ;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; Exit() {                                            ;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	rssb acc
	rssb acc
	rssb pc
	rssb pc
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; }                                                   ;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

read:
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; Get(A) {                                            ;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	rssb char
	rssb char
	rssb char
	rssb char
	rssb in
	rssb zero
	rssb zero
	rssb char
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; }                                                   ;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; StoreByReference(A, B) {                            ;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	rssb $+34
	rssb $+33
	rssb $+32
	rssb $+31
	rssb read_arg
	rssb zero
	rssb zero
	rssb $+27
	rssb $+27
	rssb $+26
	rssb $+25
	rssb $+24
	rssb read_arg
	rssb zero
	rssb zero
	rssb $+20
	rssb $+20
	rssb $+19
	rssb $+18
	rssb $+17
	rssb read_arg
	rssb zero
	rssb zero
	rssb $+13
	rssb $+18
	rssb $+17
	rssb $+16
	rssb $+15
	rssb read_arg
	rssb zero
	rssb zero
	rssb $+11
	rssb acc
	rssb acc
	rssb 0
	rssb 0
	rssb 0
	rssb acc
	rssb acc
	rssb char
	rssb zero
	rssb zero
	rssb 0
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; }                                                   ;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; Incrementation(A) {                                 ;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	rssb acc
	rssb acc
	rssb pos
	rssb zero
	rssb zero
	rssb read_arg
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; }                                                   ;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; LoadByReference(A, B) {                             ;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;Load the location to store the data.
	rssb $+12
	rssb $+11
	rssb $+10
	rssb $+9
	rssb read_arg
	rssb zero
	rssb zero
	rssb $+5
;Store the data.
	rssb char
	rssb char
	rssb char
	rssb char
	rssb 0
	rssb zero
	rssb zero
	rssb char
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; }                                                   ;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; JumpIfNotNegative(A, B) {                           ;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;Mathematically, these next three sections do nothing
;  if the input is positive, but if it is negative then
;  its value is changed to be -1
;Add 1 to the input.
	rssb acc
	rssb acc
	rssb pos
	rssb zero
	rssb zero
	rssb char
;If the input is negative, clear it.
	rssb acc
	rssb acc
	rssb char
	rssb zero
	rssb char
;Decrement the input.
	rssb acc
	rssb acc
	rssb neg
	rssb zero
	rssb zero
	rssb char
;If the input is negative then replace `rssb pc` within
;  this segment with the negation of the input. Since
;  the negation of the input is always -1 if it is 
;  negative, then `rssb pc` will always be overwritten
;  with the value 1, which is the same as `rssb acc`.
	rssb acc
	rssb acc
	rssb char
	rssb zero
	rssb $+9
;Repeat this for the other `rssb pc`.
	rssb acc
	rssb acc
	rssb char
	rssb zero
	rssb $+9
;Jump to the given address if it is positive.
	rssb acc
	rssb acc
	rssb $+16
	rssb pc
;Jump to the given address if negative.
	rssb acc
	rssb acc
	rssb $+16
	rssb zero
	rssb pc
;Restore the two removed `rssb pc`.
	rssb acc
	rssb acc
	rssb $-3
	rssb $-4
	rssb $-10
	rssb $-11
;Storage for the address to jump to if positive.
	rssb acc
	rssb acc
	rssb neg
	rssb ($-15)-read
;Storage for the address to jump to if negative.
	rssb acc
	rssb acc
	rssb neg
	rssb ($-14)-read
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; }                                                   ;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; Return() {                                          ;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;Decrement the stack pointer
	rssb acc
	rssb acc
	rssb neg
	rssb zero
	rssb zero
	rssb ___REBEC_STACK_POINTER___
;Load the stack pointer
	rssb $+12
	rssb $+11
	rssb $+10
	rssb $+9
	rssb ___REBEC_STACK_POINTER___
	rssb zero
	rssb zero
	rssb $+5
	rssb ___REBEC_TEMP_2___
	rssb ___REBEC_TEMP_2___
	rssb ___REBEC_TEMP_2___
	rssb ___REBEC_TEMP_2___
	rssb 0
	rssb zero
	rssb zero
	rssb ___REBEC_TEMP_2___
;Subtract from here
	rssb acc
	rssb acc
	rssb $+10
	rssb ___REBEC_TEMP_2___
	rssb acc
	rssb acc
	rssb $+6
	rssb neg
	rssb ___REBEC_TEMP_2___
	rssb acc
	rssb acc
	rssb neg
	rssb $+7
;Jump to the address.
	rssb acc
	rssb acc
	rssb ___REBEC_TEMP_2___
	rssb zero
	rssb zero
	rssb pc
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; }                                                   ;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

print:
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; LoadByReference(A, B) {                             ;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;Load the location to store the data.
	rssb $+12
	rssb $+11
	rssb $+10
	rssb $+9
	rssb print_arg
	rssb zero
	rssb zero
	rssb $+5
;Store the data.
	rssb char
	rssb char
	rssb char
	rssb char
	rssb 0
	rssb zero
	rssb zero
	rssb char
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; }                                                   ;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; Set(A) {                                            ;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;Store the set character.
	rssb ___REBEC_TEMP_2___
	rssb ___REBEC_TEMP_2___
	rssb ___REBEC_TEMP_2___
	rssb ___REBEC_TEMP_2___
	rssb char
	rssb zero
	rssb zero
	rssb ___REBEC_TEMP_2___
;Negate the input.
	rssb ___REBEC_TEMP_1___
	rssb ___REBEC_TEMP_1___
	rssb ___REBEC_TEMP_1___
	rssb ___REBEC_TEMP_1___
	rssb char
	rssb zero
	rssb zero
	rssb ___REBEC_TEMP_1___
	rssb char
	rssb char
	rssb char
	rssb ___REBEC_TEMP_1___
	rssb char
	rssb char
;Add our previous output to the input.
	rssb acc
	rssb acc
	rssb ___REBEC_PREVIOUS_OUTPUT___
	rssb zero
	rssb zero
	rssb char
;Subtract the input from the previous output.
	rssb acc
	rssb acc
	rssb char
	rssb ___REBEC_PREVIOUS_OUTPUT___
	rssb acc
	rssb acc
	rssb char
	rssb neg
	rssb ___REBEC_PREVIOUS_OUTPUT___
;Subtract the input from the output
	rssb acc
	rssb acc
	rssb char
	rssb out
	rssb acc
	rssb acc
	rssb char
	rssb neg
	rssb out
;Negate the input.
	rssb ___REBEC_TEMP_1___
	rssb ___REBEC_TEMP_1___
	rssb ___REBEC_TEMP_1___
	rssb ___REBEC_TEMP_1___
	rssb char
	rssb zero
	rssb zero
	rssb ___REBEC_TEMP_1___
	rssb char
	rssb char
	rssb char
	rssb ___REBEC_TEMP_1___
	rssb char
	rssb char
;Restore the set character.
	rssb char
	rssb char
	rssb char
	rssb char
	rssb ___REBEC_TEMP_2___
	rssb zero
	rssb zero
	rssb char
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; }                                                   ;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; Incrementation(A) {                                 ;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	rssb acc
	rssb acc
	rssb pos
	rssb zero
	rssb zero
	rssb print_arg
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; }                                                   ;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; LoadByReference(A, B) {                             ;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;Load the location to store the data.
	rssb $+12
	rssb $+11
	rssb $+10
	rssb $+9
	rssb print_arg
	rssb zero
	rssb zero
	rssb $+5
;Store the data.
	rssb char
	rssb char
	rssb char
	rssb char
	rssb 0
	rssb zero
	rssb zero
	rssb char
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; }                                                   ;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; JumpIfNotNegative(A, B) {                           ;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;Mathematically, these next three sections do nothing
;  if the input is positive, but if it is negative then
;  its value is changed to be -1
;Add 1 to the input.
	rssb acc
	rssb acc
	rssb pos
	rssb zero
	rssb zero
	rssb char
;If the input is negative, clear it.
	rssb acc
	rssb acc
	rssb char
	rssb zero
	rssb char
;Decrement the input.
	rssb acc
	rssb acc
	rssb neg
	rssb zero
	rssb zero
	rssb char
;If the input is negative then replace `rssb pc` within
;  this segment with the negation of the input. Since
;  the negation of the input is always -1 if it is 
;  negative, then `rssb pc` will always be overwritten
;  with the value 1, which is the same as `rssb acc`.
	rssb acc
	rssb acc
	rssb char
	rssb zero
	rssb $+9
;Repeat this for the other `rssb pc`.
	rssb acc
	rssb acc
	rssb char
	rssb zero
	rssb $+9
;Jump to the given address if it is positive.
	rssb acc
	rssb acc
	rssb $+16
	rssb pc
;Jump to the given address if negative.
	rssb acc
	rssb acc
	rssb $+16
	rssb zero
	rssb pc
;Restore the two removed `rssb pc`.
	rssb acc
	rssb acc
	rssb $-3
	rssb $-4
	rssb $-10
	rssb $-11
;Storage for the address to jump to if positive.
	rssb acc
	rssb acc
	rssb neg
	rssb ($-15)-print
;Storage for the address to jump to if negative.
	rssb acc
	rssb acc
	rssb neg
	rssb ($-14)-print
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; }                                                   ;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; Return() {                                          ;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;Decrement the stack pointer
	rssb acc
	rssb acc
	rssb neg
	rssb zero
	rssb zero
	rssb ___REBEC_STACK_POINTER___
;Load the stack pointer
	rssb $+12
	rssb $+11
	rssb $+10
	rssb $+9
	rssb ___REBEC_STACK_POINTER___
	rssb zero
	rssb zero
	rssb $+5
	rssb ___REBEC_TEMP_2___
	rssb ___REBEC_TEMP_2___
	rssb ___REBEC_TEMP_2___
	rssb ___REBEC_TEMP_2___
	rssb 0
	rssb zero
	rssb zero
	rssb ___REBEC_TEMP_2___
;Subtract from here
	rssb acc
	rssb acc
	rssb $+10
	rssb ___REBEC_TEMP_2___
	rssb acc
	rssb acc
	rssb $+6
	rssb neg
	rssb ___REBEC_TEMP_2___
	rssb acc
	rssb acc
	rssb neg
	rssb $+7
;Jump to the address.
	rssb acc
	rssb acc
	rssb ___REBEC_TEMP_2___
	rssb zero
	rssb zero
	rssb pc
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; }                                                   ;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;                End of Code Segment                  ;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;               Start of Data Segment                 ;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
___REBEC_TEMP_1___:
	rssb 0
___REBEC_TEMP_2___:
	rssb 0
___REBEC_TEMP_3___:
	rssb 0
___REBEC_TEMP_4___:
	rssb 0
___REBEC_TEMP_5___:
	rssb 0
___REBEC_TEMP_6___:
	rssb 0
___REBEC_TEMP_7___:
	rssb 0
___REBEC_PREVIOUS_OUTPUT___:
	rssb 0
___REBEC_STACK_POINTER___:
	rssb ___REBEC_STACK___
___REBEC_STACK___:
	rssb 0
	rssb 0
	rssb 0
	rssb 0
	rssb 0
	rssb 0
	rssb 0
	rssb 0
	rssb 0
	rssb 0
char:
	rssb 0
str_intro:
	rssb 'W'
	rssb 'h'
	rssb 'a'
	rssb 't'
	rssb ' '
	rssb 'i'
	rssb 's'
	rssb ' '
	rssb 'y'
	rssb 'o'
	rssb 'u'
	rssb 'r'
	rssb ' '
	rssb 'n'
	rssb 'a'
	rssb 'm'
	rssb 'e'
	rssb '?'
	rssb ':'
	rssb ' '
	rssb -1
str_response:
	rssb 'H'
	rssb 'e'
	rssb 'l'
	rssb 'l'
	rssb 'o'
	rssb ','
	rssb ' '
	rssb -1
str_name:
	rssb 0
	rssb 0
	rssb 0
	rssb -1
str_final:
	rssb '!'
	rssb 10
	rssb -1
print_arg:
	rssb 0
read_arg:
	rssb 0
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;                End of Data Segment                  ;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
