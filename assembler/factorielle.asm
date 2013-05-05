// calcule les factorielles de 0 à 10.

.DATA
debut_data :	11

.CODE
	subi r0 r0 r0 // r0 vaut 0 (constante)
	addi r1 r0 debut_data+10 // r1 vaut 10 (constante)
	addi r2 r0 debut_data // r2 vaut 0 (pointeur sur données)
	addi r3 r0 1 // r3 vaut la factorielle courante (ici fact(0)=1)
	store r2 r3
	addi r2 r2 1
		// boucle principale
lbl1:		jre fin_bcl_princ r1 r2
		subi r4 r2 debut_data // compteur de boucle secondaire
		add r5 r0 r0	// résultat de la multiplication
			// boucle secondaire : multiplication
lbl2:			jre fin_bcl2 r4 r0
				add r5 r3 r5
				jmp lbl2
fin_bcl2:	addi r3 r5 r0
		store r2 r3
		addi r2 r2 1
		jmp lbl1
fin_bcl_princ:
