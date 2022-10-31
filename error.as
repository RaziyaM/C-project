;example to detect label error
3MAIN:	mov	S1.1 , W
3M AIN:	mov	S1.1 , W
MAIN :	mov	S1.1 , W
MAIN:	mov	S1.1 , W
MAIN:	mov	S1.1 , W
MAINasdfgasdfasdfasdfsdfasdasdasdasdasdasdasdasdasdasdasdasdasdasdasdasd:	mov	S1.1 , W
mov:	mov	S1.1 , W
	add	r2,STR
LOOP: jmp W	
	prn	#-5
	sub	r1,r4
	inc K

	mov	S1.2 , r3
	bne	L3 
END:	hlt
STR:	.string "abcdef"
LENGHT:	.data 6,-9,15
K:	.data 22
S1:	.struct 8,"ab"
