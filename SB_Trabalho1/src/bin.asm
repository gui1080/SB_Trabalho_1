;                            oi
A0: EQU 0 ;testando
A1: equ 1
A2: equ 0

SECTION TEXT

INPUT OLD_DATA

LOAD OLD_DATA

L1: 

DIV DOIS

STORE NEW_DATA



MULT DOIS

; comentario definitivamente importante

STORE TMP_DATA

LOAD OLD_DATA  

SUB TMP_DATA
STORE TMP_DATA

;2+2=4
; comentario
output TMP_DATA
;oi
COPY NEW_DATA, OLD_DATA
LOAD OLD_DATA ; comentario
JMPP L1 ; comentario
STOP ;comentário útil aqui

SECTION DATA
DOIS: CONST 2
OLD_DATA: SPACE
NEW_DATA: SPACE
TMP_DATA: SPACE
