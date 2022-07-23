.386   ; model du processeur

.model flat  ; modèle mémoire*

.data
op1  BYTE 10  
op2  BYTE 12 
x    BYTE  ? 

;---------Segment du code-----------------
.code  
main PROC
mov al, op1			; Al := op1
cmp al, op2			; comparaison op1 et op2
JE Etiquette		; branchement si op1 != op2
mov x, 2			; x := 2 (else)
jmp Quit			; branchement vers Quit:
Etiquette:  mov x, 1       ; x := 1 
Quit:
main ENDP
end