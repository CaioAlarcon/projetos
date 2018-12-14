;Nomes:
;	Caio Cesar Aguiar Alarcon	n° 7241109
;	Denis Alexandre da Silva	n° 7238999
;	Bruno de Souza Menzzano		n° 9790795
jmp main
Tabuleiro : string "_________"
Mensagem : string "Use os numeros para movimentar o cursor e o Enter para executar as jogadas."
Cursor : var #1
Slot : var #1
Vez : var #1;1 é vez do pc, 0 é do usuario
rnd : var #1

;Se r0 == r1 == r2 => r3=1
;caso contrário r3 = 0
Iguais:
	push r0
	push r1
	push r2
	loadn r3, #Tabuleiro
	add r0, r0, r3
	add r1, r1, r3
	add r2, r2, r3
	loadi r0, r0
	loadi r1, r1
	loadi r2, r2
	
	cmp r0, r1
	jne NaoIguais
	cmp r0, r2
	jne NaoIguais	
	
	loadn r3, #'_'
	cmp r3, r0
	jeq NaoIguais;São iguais, mas não conta....
	loadn r3, #1
	
	jmp IguaisFim
	
	NaoIguais :
	loadn r3, #0
	
	IguaisFim :
	pop r2
	pop r1
	pop r0
rts

AlguemGanhou:
	push r0
	push r1
	push r2
	push r3
	push r4
	loadn r4, #1
	
	loadn r0,#0
	loadn r1,#1
	loadn r2,#2
	call Iguais
	cmp r4, r3
	jeq SimAlguemGanhou
	
	loadn r0,#3
	loadn r1,#4
	loadn r2,#5
	call Iguais
	cmp r4, r3
	jeq SimAlguemGanhou
	
	loadn r0,#6
	loadn r1,#7
	loadn r2,#8
	call Iguais
	cmp r4, r3
	jeq SimAlguemGanhou
	
	loadn r0,#0
	loadn r1,#3
	loadn r2,#6
	call Iguais
	cmp r4, r3
	jeq SimAlguemGanhou
	
	loadn r0,#1
	loadn r1,#4
	loadn r2,#7
	call Iguais
	cmp r4, r3
	jeq SimAlguemGanhou
	
	loadn r0,#2
	loadn r1,#5
	loadn r2,#8
	call Iguais
	cmp r4, r3
	jeq SimAlguemGanhou
	
	loadn r0,#0
	loadn r1,#4
	loadn r2,#8
	call Iguais
	cmp r4, r3
	jeq SimAlguemGanhou

	loadn r0,#2
	loadn r1,#4
	loadn r2,#6
	call Iguais
	cmp r4, r3
	jeq SimAlguemGanhou
	
	
	jmp NinguemGanhou
	SimAlguemGanhou :

	call ColoreLinha

	call ProximoSlot
	;reiniciar o jogo
	call reinicia
	
	NinguemGanhou :
	call DeuVelha
	pop r4
	pop r3
	pop r2
	pop r3
	pop r0
rts

DeuVelha:
	push r0
	loadn r0, #9
	cmp r0, r6
	jne NaoDeuVelha
	call PrintSemCursor
	call ProximoSlot
	call reinicia
	NaoDeuVelha :
	
	pop r0
rts

ProximoSlot:
	push r0
	push r1
	push r2
	;baixar o valor do slot
	;somar 1
	;atualizar r5 com base nele
	load r0, Slot;Slot++;
	inc r0
	loadn r2, #70
	mod r0, r0, r2

	store Slot, r0
	
	;r5 = (Slot mod 10)*4 + (slot/10)*160
	loadn r2, #10
	
	mod r1, r0, r2
	loadn r2, #4
	mul r1, r1, r2
	mov r5, r1
	
	
	loadn r2, #10
	div r1, r0, r2
	
	loadn r2, #160
	mul r1, r1, r2

	add r5, r5, r1
	
	pop r2
	pop r1
	pop r0
rts

ColoreLinha:;Colore a linha que ganhou 
	
	push r4
	push r3
	push r2
	push r1
	push r0
	push r7
	
	load r4, Vez
	loadn r3, #0
	cmp r4, r3
	jne CorAdversario
	loadn r7, #2304
	jmp SaiCor
	CorAdversario :
	loadn r7, #512
	SaiCor :
	
	loadn r3, #Tabuleiro
	add r3, r3, r0
	loadi r4, r3
	
	add r4, r4, r7
	storei r3, r4
	
	loadn r3, #Tabuleiro
	add r3, r3, r1
	loadi r4, r3

	add r4, r4, r7
	storei r3, r4
	
	loadn r3, #Tabuleiro
	add r3, r3, r2
	loadi r4, r3

	add r4, r4, r7
	storei r3, r4
	
	call PrintSemCursor
	
	pop r7
	pop r0
	pop r1
	pop r2
	pop r3
	pop r4
	
rts
PrintSemCursor:
	push r0
	push r1
	push r2
	
	load r0, Cursor
	loadn r1, #10
	store Cursor, r1
	
	mov r2, r5
	call print
	
	store Cursor, r0
	pop r2
	pop r1
	pop r0
rts

MudaVez:
	push r0
	push r1
	load r0, Vez
	loadn r1, #0
	cmp r0, r1
	jne MudaVezFim
	loadn r1, #1
	MudaVezFim :
	store Vez, r1
	pop r1
	pop r0
rts
PCJoga:
	;você só tem que escolher um lugar vazio pra jogar
	push r0
	push r1
	push r2
	push r3
	loadn r2, #'_'
	loadn r0, #Tabuleiro
	PCJogaLoop :
	call RND
	add r1, r0, r7; r1 = Tabuleiro[rnd];
	loadi r3, r1
	cmp r2, r3; while(Tabuleiro[rnd] != '_');
	jne PCJogaLoop;
	;Finalmente encontrou um lugar vazio
	loadn r3, #'O'
	storei r1, r3
	inc r6
	call MudaVez
	pop r3
	pop r2
	pop r1
	pop r0
rts

Joga:;Ver de quem é a vez antes de jogar
	push r0
	push r1
	push r2
	;Se for vez do pc, pc joga
	load r0, Vez;r0 tem o valor de Vez
	loadn r1, #0
	cmp r0, r1;se for igual pc não joga pois é a vez do user
	jeq PCNaoJoga
	call PCJoga
	call AlguemGanhou
	jmp JogaFim
	PCNaoJoga :
	loadn r1, #Tabuleiro
	load r0, Cursor
	add r1, r1, r0
	
	loadi r0 , r1;Ver se a casa está vazia:
	loadn r2, #'_'
	cmp r2, r0
	jne JogaFim;Se não for vazia, termina
	loadn r0, #'X'
	storei r1, r0
	inc r6
	call MudaVez
	call AlguemGanhou
	
	JogaFim :
	pop r2
	pop r1
	pop r0
rts

LeTeclado:
	push r0
	push r1
	inchar r0
	
	loadn r1, #13;Testa se enter
	cmp r0, r1
	jne LeTecladoNaoEnter
	;Se for enter:
	call Joga
	jmp LeTecladoFim
	
	LeTecladoNaoEnter :
	loadn r1, #49
	sub r0, r0, r1
	loadn r1, #9
	cmp r0, r1
	jgr LeTecladoFim
	store Cursor, r0
	
	LeTecladoFim :
	pop r1
	pop r0
rts


print:
	push r0;contador
	push r1;Ponteiro do tabuleiro
	push r2;Ponteiro da tela
	push r3;Aux
	push r4;Aux2
	loadn r0, #0
	loadn r1, #Tabuleiro
	
	printloop :
	loadi r3, r1
	load r4, Cursor
	cmp r4, r0;ver se o cusor esta aqui
	jne printsemcursor; se não estiver pula
	;se estiver, muda a cor
	loadn r4, #2816
	add r3, r3, r4
	printsemcursor :
	
	outchar r3, r2
	inc r2
	inc r1
	inc r0
	
	loadn r3, #3
	mod r3, r0, r3
	loadn r4, #0
	cmp r4, r3
	jne printnaoenter
	
	;enter:
	loadn r3, #37
	add r2, r2, r3
	printnaoenter :
	loadn r3, #9
	cmp r0, r3
	jle printloop
	
	pop r4
	pop r3
	pop r2
	pop r1
	pop r0
rts
RND:
	push r0
	inc r7
	loadn r0, #9
	mod r7, r7, r0
	pop r0
rts
reinicia:
	push r0;tabuleiro
	push r1;contador
	push r2
	push r3;aux
	loadn r6, #0
	loadn r0, #Tabuleiro
	loadn r1, #0
	
	reinicialoop :
	add r2, r0, r1
	loadn r3, #'_'
	storei r2, r3
	inc r1
	loadn r3, #9
	cmp r1, r3
	jne reinicialoop
	
	pop r3
	pop r2
	pop r1
	pop r0
rts

ImprimeMensagem:
	push r0
	push r1
	push r2
	push r3
	loadn r0, #Mensagem
	loadn r1, #1120
	loadi r2, r0
	LoopImprimeMsg :
	outchar r2, r1
	inc r1
	inc r0
	loadi r2, r0
	loadn r3, #'\0'
	cmp r2, r3
	jne LoopImprimeMsg
	
	pop r3
	pop r2
	pop r1
	pop r0
	
rts

main:
	loadn r0, #0
	loadn r5, #0;Posição do tabuleiro na tela
	loadn r6, #0;r6 é o contador de jogadas
	store Cursor, r0;inicializa o cursor em 0
	store Slot, r0;inicializa o slot em 0
	store Vez, r0; inicializa vez em 0
	
	call ImprimeMensagem
	
	mainloop :
	call RND;Gerencia o número aleatorio
	call LeTeclado
	
	mov r2, r5
	call print
	
	jmp mainloop

halt
