TITLE      comparaison de chaines  TD5 exo1 
.386
; mod�le de memoire utilis�e, un "data segment" et un "code segment"
.model flat,stdcall ; 

includelib "C:\Program Files (x86)\Microsoft Visual Studio 12.0\VC\lib\msvcrt.lib"

extern  printf         :   proc
 




; definition des constantes


;;;;;;;;segment de donn�es;;;;;;;;
.data 
String1 BYTE "AZERTYU",0
String2 BYTE "AZERTYUA",0
message1 BYTE "chaines identiques", 0
message2 BYTE "chaines differentes", 0

;;;;;;;;segment du code;;;;;;;;;;; 
.code
main PROC                         
        lea esi, String1    ; l'adresse du d�but String1 dans SI	
		lea edi, String2    ; l'adresse du d�but String2 dans DI
        mov ecx, LENGTHOF String2  ; taille de la cha�ne	
		call compareChaines   ; appel proc�dure, comparaison de deux chaines 
        cmp bx, 1                 ; BX param�tre de retour, si BX=1, les deux cha�nes sont identiques 
		jnz e1
		lea eax, message1 		; si non en passe � e1
		jmp affichage             ; saut pour affichage du message 1
e1:     cmp BX, 2
		jnz exit_				; sinon on quite 
		lea eax, message2      ; si BX=2 les deux chaines sont diff�rentes	                  
affichage:  
		call afficher		      ; appel de la proc�dure d'affichage
exit_ : nop		
main ENDP	

;//////////////////////////////////	
compareChaines PROC
; compare deux cha�nes point�es par ESI et EDI vers 
; re�oit ESI, EDI et la taille d'une chaine dans cx
; renvoi BX = 1 si les deux chaines sont �gaux, BX = 2 si non
	mov bx, 0     ; initialisation de BX
	cld           ; modification du flag, pour incrementation SI et DI lors de l'utilisation de cmpsb
	repe cmpsb    ; compare deux chaines point�es par SI et DI, r�p�tition tant que c'est �gale 
	jnz e1        ; si les deux cha�nes ne sont pas identiques branchement vers e1 
    mov bx, 1 	  ; BX := 1 si les deux cha�nes sont identiques 	
	jmp e2        ; si non saut vers e2
e1: 
	mov bx, 2     ; BX :=2 les deux cha�nes ne sont pas identiques
e2:    
ret		
compareChaines ENDP
;//////////////////////////////////

;******** PROCEDURE afichage de message ********************;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; Affiche un m�ssage										;
; --> Param�tres d'entr�e : adresse du d�but du message     ;
;                            dans eax						;	
; <-- retour: message affich� dans la console	            ;
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
; affiche une cha�ne de caract�res 
; re�oit l'adresse de debut de la cha�ne dans DX
;mov ah, 09h   ; pour affichage lors de l'appel DOS 
;int 21h       ; interruption logiciel : appel DOS
;ret
;afficher ENDP
;////////////////////////////////////

exit_: nop
END
