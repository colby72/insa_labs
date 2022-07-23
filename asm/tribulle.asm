.386

.model flat


.DATA 
; déclaration d'un tableau statique
tab SWORD 1h,5h,3h,0h,-5d,0Ah,4h,-1d,6h,7h

.CODE
main proc
L0: ;------- WHILE (desorde)-----------------------------------
mov ebx, 0               ; bx : la variable en_desordre
mov ecx, LENGTHOF tab    ; directive pour récupérer la taille du tableau
dec ecx				    ; pour balayer le tableau jusqu'à n-1
mov esi,0				; indice sur le tableau (j)
	
    L1: ;----- FOR ---------- --------------------------------
		mov ax, tab[esi]        ; transfert de la valeur tab[j]
			cmp ax, tab[esi+2]  ; compare tab[j] et tab[j+1]
			;----- IF -------------------------------------
			jle L2             ; un saut si tab[j]<=tab[j+1]
			xchg ax, tab[esi+2] ; echange des valeurs de tab[j] et tab[j+1]
			mov tab[esi], ax    ; //
			mov ebx,1           ; en_desorde = true
			;----FIN DE IF---------------------------------
		L2:add esi,2            ; incrémentation du j, j=j+1
   loop L1					   ; boucle tant que cx >0 
	  ;------FIN de FOR------------------------------------
cmp ebx,1
je L0
;----- FIN WHILE ----------------------------------------
nop
main endp
END