.386   ; model du processeur

.model flat  ; modèle mémoire

.data
val1 DWORD 20    
val2 DWORD 24 
val3 DWORD 50 
x    DWORD  ?

;---------Segment du code-----------------
.code  
main PROC
mov eax, val2   ; EAX := val2
While_: cmp val1, eax   ; 
		jae   EndW      ; 
		inc val1
			If_: cmp eax, val3 ; 
				jne E       ; 
				mov x, 2    ;
				jmp Endif_ 
			E:	mov x, 3    ; 
			Endif_:
	   jmp While_
EndW:
main ENDP
end