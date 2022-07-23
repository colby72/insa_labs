TITLE      comparaison de chaines  TD5 exo1 
.386
; modèle de memoire utilisée, un "data segment" et un "code segment"
.model flat,stdcall ; 

includelib "C:\Program Files (x86)\Microsoft Visual Studio 12.0\VC\lib\msvcrt.lib"

extern  printf         :   proc
 




; definition des constantes


;;;;;;;;segment de données;;;;;;;;
.data 
String1 BYTE "AZERTYU",0
String2 BYTE "AZERTYUA",0
message1 BYTE "chaines identiques", 0
message2 BYTE "chaines differentes", 0

;;;;;;;;segment du code;;;;;;;;;;; 
.code
main PROC                         
        lea esi, String1    ; l'adresse du début String1 dans SI	
		lea edi, String2    ; l'adresse du début String2 dans DI
        mov ecx, LENGTHOF String2  ; taille de la chaîne	
		call compareChaines   ; appel procédure, comparaison de deux chaines 
        cmp bx, 1                 ; BX paramètre de retour, si BX=1, les deux chaînes sont identiques 
		jnz e1
		lea eax, message1 		; si non en passe à e1
		jmp affichage             ; saut pour affichage du message 1
e1:     cmp BX, 2
		jnz exit_				; sinon on quite 
		lea eax, message2      ; si BX=2 les deux chaines sont différentes	                  
affichage:  
		call afficher		      ; appel de la procédure d'affichage
exit_ : nop		
main ENDP	

;//////////////////////////////////	
compareChaines PROC
; compare deux chaînes pointées par ESI et EDI vers 
; reçoit ESI, EDI et la taille d'une chaine dans cx
; renvoi BX = 1 si les deux chaines sont égaux, BX = 2 si non
	mov bx, 0     ; initialisation de BX
	cld           ; modification du flag, pour incrementation SI et DI lors de l'utilisation de cmpsb
	repe cmpsb    ; compare deux chaines pointées par SI et DI, répétition tant que c'est égale 
	jnz e1        ; si les deux chaînes ne sont pas identiques branchement vers e1 
    mov bx, 1 	  ; BX := 1 si les deux chaînes sont identiques 	
	jmp e2        ; si non saut vers e2
e1: 
	mov bx, 2     ; BX :=2 les deux chaînes ne sont pas identiques
e2:    
ret		
compareChaines ENDP
;//////////////////////////////////

;******** PROCEDURE afichage de message ********************;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; Affiche un méssage										;
; --> Paramètres d'entrée : adresse du début du message     ;
;                            dans eax						;	
; <-- retour: message affiché dans la console	            ;
;-----------------------------------------------------------;
afficher proc
push    eax
call    printf
pop eax
ret
afficher endp 

;///////////////////////////////////
;MODE REEL appel system DOS 
;afficher PROC
; affiche une chaîne de caractères 
; reçoit l'adresse de debut de la chaîne dans DX
;mov ah, 09h   ; pour affichage lors de l'appel DOS 
;int 21h       ; interruption logiciel : appel DOS
;ret
;afficher ENDP
;////////////////////////////////////

exit_: nop
END
