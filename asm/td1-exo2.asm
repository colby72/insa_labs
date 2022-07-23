.386  ; architecture 32 bits

.model flat ; modèle de la mémoire

.data  ; déclaration de segment de données
var1 DWORD 10000000h
var2 DWORD 20000000h

.code ; segment de code (instruction)
main proc ; la procédure main comme la fonction main C/C++
mov eax,var1 ; transfert de mémoire
add eax,var2 ; addition
add eax,0FFFFFFFFh
add eax,1 
sub eax,1 ; soustraction
main endp ; la fin de la procédure main 
end ; find de fichier;