.386   ; model du processeur

.model flat  ; mod�le m�moire

.data
var1 WORD 45000    
var2 WORD 45000 
var3 WORD 5000 

;---------Segment du code-----------------
.code  
main PROC
mov bx, var1   ; BX := op1
mov cx, var2   ; CX := op2
mov dx, var3   ; DX := op3
cmp bx, cx     ; comparaison BX et CX
ja   E1      ; branchement vers la sortie si BX > CX, la condition n'est pas v�rifi�e
cmp cx, dx     ; si BX <= CX on test la deuxi�me condition CX > DX
jbe E1       ; Si CX <= DX condition n'est pas v�rifi�e
mov ax, 5      ; AX := 5, condition v�rifi�e (BX <= CX) AND (CX > DX)
mov dx, 6      ; DX := 6
E1:
main ENDP
end