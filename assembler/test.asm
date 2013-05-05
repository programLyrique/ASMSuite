.DATA
zero:	3
4
5

.CODE

start:	add r0, R2, r30
	aDDi r5, r7, 3-start+4
lbl_1:	and r5, r12, r25
	andi r1, R10, lbl_1-32+lbl_2
	cAll start
	In r5, 2^4
	jmp lbl_1+5
	jmR r23
	JRE r12, r3, 4
	jrs r31, r7, 46+zero+un-deux
	loAd r13, r15
	

.CODE
	or r0 r0 r0
	ori r0 r0 89*(1+3)
	out 2*(3+4/2) r5
	RET
	sl r6 r7 r8
	sli r1 r2 2
	sr r9 r11 r12
	SRI r13 r14 22
	store r15 r16
	sub r17 r18 r19
lbl_2:	subi r20 r21 123
	Xor r22 r23 r24
	Xori r25 r26 79+trois-quatre

.DATA
un : 1
2
3+4
deux: trois: quatre: 4
