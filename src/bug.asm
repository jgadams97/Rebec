;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;               Start of Code Segment                 ;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
main:
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; JumpIfEqual(A, B) {                           ;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;Clear the temporary register..
;Subtract the second value from the first.
	rssb ___REBEC_TEMP_2___
	rssb ___REBEC_TEMP_2___
	rssb ___REBEC_TEMP_2___
	rssb ___REBEC_TEMP_2___
	rssb x
	rssb zero
	rssb zero
	rssb ___REBEC_TEMP_2___
	rssb acc
	rssb acc
	rssb y
	rssb ___REBEC_TEMP_2___
	rssb acc
	rssb acc
	rssb y
	rssb neg
	rssb ___REBEC_TEMP_2___
	rssb acc
	rssb acc
	rssb pos
	rssb zero
	rssb zero
	rssb ___REBEC_TEMP_2___
	rssb acc
	rssb acc
	rssb ___REBEC_TEMP_2___
	rssb zero
	rssb ___REBEC_TEMP_2___
	rssb acc
	rssb acc
	rssb neg
	rssb zero
	rssb zero
	rssb ___REBEC_TEMP_2___
;If the input is negative then replace `rssb pc` within
;  this segment with the negation of the input. Since
;  the negation of the input is always -1 if it is 
;  negative, then `rssb pc` will always be overwritten
;  with the value 1, which is the same as `rssb acc`.
	rssb acc
	rssb acc
	rssb ___REBEC_TEMP_2___
	rssb zero
	rssb $+53
;Repeat this for the other `rssb pc`.
	rssb acc
	rssb acc
	rssb ___REBEC_TEMP_2___
	rssb zero
	rssb $+53
;Subtract the first value from the second.
	rssb ___REBEC_TEMP_2___
	rssb ___REBEC_TEMP_2___
	rssb ___REBEC_TEMP_2___
	rssb ___REBEC_TEMP_2___
	rssb y
	rssb zero
	rssb zero
	rssb ___REBEC_TEMP_2___
	rssb acc
	rssb acc
	rssb x
	rssb ___REBEC_TEMP_2___
	rssb acc
	rssb acc
	rssb x
	rssb neg
	rssb ___REBEC_TEMP_2___
	rssb acc
	rssb acc
	rssb pos
	rssb zero
	rssb zero
	rssb ___REBEC_TEMP_2___
	rssb acc
	rssb acc
	rssb ___REBEC_TEMP_2___
	rssb zero
	rssb ___REBEC_TEMP_2___
	rssb acc
	rssb acc
	rssb neg
	rssb zero
	rssb zero
	rssb ___REBEC_TEMP_2___
;If the input is negative then replace `rssb pc` within
;  this segment with the negation of the input. Since
;  the negation of the input is always -1 if it is 
;  negative, then `rssb pc` will always be overwritten
;  with the value 1, which is the same as `rssb acc`.
	rssb acc
	rssb acc
	rssb ___REBEC_TEMP_2___
	rssb zero
	rssb $+9
;Repeat this for the other `rssb pc`.
	rssb acc
	rssb acc
	rssb ___REBEC_TEMP_2___
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
	rssb ($-15)-main
;Storage for the address to jump to if negative.
	rssb acc
	rssb acc
	rssb neg
	rssb ($-14)-main
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
x:
	rssb 32767
y:
	rssb 32767
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;                End of Data Segment                  ;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
