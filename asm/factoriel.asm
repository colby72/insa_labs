Title calcul du factoriel par recursivité

.386 ; processeur 32 bits

.model flat ; modèle de la mémoire

.data
tab DWORD ?

.code
;************ PROCEDURE MAIN ************;
main proc
; initialisation des paramètres de la procédure facto
;-----------
mov eax, 5   
mov ebx, eax
mov ecx, 0
lea esi, tab
;------------
call facto
nop  ; facultatif pour ne pas sortir du programme
ret
main endp
;************ FIN PROCEDURE MAIN ********;

;******************* PROCEDURE FACTO ***********************;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; procédure pour calcul du factoriel						;
; d'un nombre entier N, stockage des factoriels				;
; dans un tableau											;	
; utilisation de la recursivité	
; le résultat est limité sur 32 bits							;
; --> Paramètres d'entrée :- le nombre N dans eax et ebx	;	
;                           - l'adresse du tableau dans esi	;
;							- initialiser ecx = 0			;
; <-- retour: - factoriel de N dans eax						;
;			   - les valeurs dans un tableau pointé à la fin;
;				 par esi									;	
;			   - la taille du tableau ecx					;	
;-----------------------------------------------------------;
facto proc 
dec ebx            ; N=N-1
mov [esi],eax      ; Stockage des resultats : N, N*(N-1), (N-1)*(N-2),...
add esi, 4         ; incrémenter l'indice du tableau
inc ecx            ; incrimenter ecx  pour la taille du tableau
cmp ebx,1          ; si le dernier nombre !=0
je fin             ; si le dernier nombre == 0 aller à fin
mul ebx            ; N*(N-i), (N-1)*(N-2),..., résultat dan eax
call facto         ; appel recursive de la procédure facto
fin:ret            ; retour de la fonction facto
facto endp
;************ FIN DE LA PROCEDURE FACTO *********************;

end
