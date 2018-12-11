jmp main
Tabuleiro : var #100

Aux: var #100


EscreverM:;r1: tabuleiro, r2:x, r3: y, r4:val
	push r5
	loadn r5, #10
	mul r5, r3, r5
	add r5, r2, r5
	add r5, r5, r1
	storei r5, r4
	pop r5
	rts
LerM:
	rts
InitTabuleiro:;r1 é o endereço do tabuleiro
	push r1;Endereço do tabuleiro
	push r2;primeiro contador
	push r3;segundo contador
	push r4
	;load r1, Tabuleiro
	loadn r2, #0
	loop1:
	loadn r3, #0
	loop2:
	
	loadn r4, #0
	cmp r3, r4
	jeq seforborda
	cmp r2, r4
	jeq seforborda
	loadn r4, #9
	cmp r3, r4
	jeq seforborda
	cmp r2, r4
	jne senaoforborda
	
	seforborda:
	loadn r4, #'#'
	call EscreverM
	jmp SaiDoIF
	
	senaoforborda:
	loadn r4, #' '
	call EscreverM
	SaiDoIF:
	
	loadn r4, #10
	inc r3 
	cmp r3, r4
	jle loop2
	inc r2 
	cmp r2, r4
	jle loop1
	
	loadn r2, #5
	loadn r3, #5
	loadn r4, #'*'
	call EscreverM
	
	loadn r2, #4
	loadn r3, #4
	loadn r4, #'*'
	call EscreverM
	
	loadn r2, #4
	loadn r3, #5
	loadn r4, #'O'
	call EscreverM
	
	loadn r2, #5
	loadn r3, #4
	loadn r4, #'O'
	call EscreverM
	pop r4
	pop r3
	pop r2
	pop r1
	rts

;Parametros da função
Matriz: var #1
Onde: var #1
ImprimeMatriz:
	push r1;matriz
	push r2;contador
	push r3;aux
	push r4;ponteiro da tela
	push r5;contador para quebra de linha
	loadn r5, #0
	loadn r2, #0
	loadn r1, #Matriz
	loadi r1, r1
	
	loadn r4, #Onde
	loadi r4, r4
	
	
	loopImprime:;100 vezes
	loadi r3, r1
	outchar r3, r4
	inc r2
	inc r1
	inc r4
	inc r5
	loadn r3, #10
	cmp r5, r3
	jne NaoPulaLinha
	;Imprime a quebra de linha
	loadn r3, #30
	add r4, r4, r3
	loadn r5, #0
	NaoPulaLinha:;Prossegue a impressão sem imprimir a linha
	loadn r3, #100
	cmp r2, r3
	jle loopImprime
	pop r5
	pop r4
	pop r3
	pop r2
	pop r1
	rts
	
	

main:
	loadn r1, #Tabuleiro
	call InitTabuleiro
	
	loadn r3, #294
	loadn r2, #Onde
	storei r2, r3
	
	loadn r3, #Matriz
	storei r3, r1
	
	
	
	call ImprimeMatriz
	
	BREAKP
	
	loadn r1, #Aux
	
	call ImprimeMatriz
	halt







