.386

.model flat


.code
.386   ; model du processeur

.model flat  ; modèle mémoire

;_______Allocation statique____
;         Segment 1           ;
.data        
Xval DWORD 25450546
Yval DWORD 78976552
Zval DWORD 45646544
Rval DWORD ?
var1 DWORD 46545565
var2 DWORD 789756456
var3 DWORD 465454565
var4 DWORD 2 dup (?) ; pour stocker le résultat de MUL sur 64 bits
var5 QWORD ?         ; pour stocker le résultat de MUL sur 64 bits


;_______ Segment du code ______________
.code  ; déclaration du segment du code
main PROC
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; operation Rval = -Xval + Yval - Zval
mov eax, xval
neg eax
add eax, Yval
sub eax, Zval
mov Rval, eax
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; opération var4 = (var1+var2)*var3
mov eax, var1;
add eax, var2;
mul var3;
lea esi, var5 ; stockage sur une variable 64 bits
mov [esi], eax 
mov [esi + 4], edx
; solution 2 pour le stockage 64 bits
mov var4, eax
mov [var4+4], edx
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;opération var4 = -5*var1/(var2 % var3)
mov eax, var2 
div var3        ;  var2 % var3
mov ebx, edx    ;  garder le reste de la division dans ebx car edx peut changer  
mov eax, var1   ;
mov ecx, 5
mul ecx         ; 5*var1  on considère que le résultat est sur 32 bits si non il faut gérer 64 bits EDX:EAX
div ebx        ;  5*var1/(var2 % var3)
neg eax         ; 
nop
main ENDP
END