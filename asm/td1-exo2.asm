.386  ; architecture 32 bits

.model flat ; mod�le de la m�moire

.data  ; d�claration de segment de donn�es
var1 DWORD 10000000h
var2 DWORD 20000000h

.code ; segment de code (instruction)
main proc ; la proc�dure main comme la fonction main C/C++
mov eax,var1 ; transfert de m�moire
add eax,var2 ; addition
add eax,0FFFFFFFFh
add eax,1 
sub eax,1 ; soustraction
main endp ; la fin de la proc�dure main 
end ; find de fichier;