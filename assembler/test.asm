.DATA
zero:	3
4
5

.CODE

start:	add r0, R2, r30			// 0
	aDDi r5, r7, 3-start+4		// 1
lbl_1:	and r5, r12, r25 		// 2
	andi r1, R10, lbl_1-32+lbl_2	// 3
	cAll start			// 4
	In r5, 2^4			// 5
	jmp lbl_1+5			// 6
	jmR r23				// 7
	JRE r12, r3, 4			// 8
	jrs r31, r7, 46+zero+un-deux	// 9
	loAd r13, r15			// 10
	

.CODE
	or r0 r0 r0			// 11
	ori r0 r0 89*(1+3)		// 12
	out 2*(3+4/2) r5		// 13
	RET				// 14
	sl r6 r7 r8			// 15
	sli r1 r2 2			// 16
	sr r9 r11 r12			// 17
	SRI r13 r14 22			// 18
	store r15 r16			// 19
	sub r17 r18 r19			// 20
lbl_2:	subi r20 r21 123		// 21
	Xor r22 r23 r24			// 22
	Xori r25 r26 79+trois-quatre	// 23

.DATA
un : 1
2
3+4
deux: trois: quatre: 4
