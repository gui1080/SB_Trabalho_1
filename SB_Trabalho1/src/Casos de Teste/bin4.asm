A0: EQU 0 ;testando
A1: equ 1
A2: equ A
IF: A0
INPUT SPACE
IF: A1
SECTION TEXT
INPUT OLD_DATA
LOAD OLD_DATA
L1: 
DIV DOIS
STORE NEW_DATA
MULT DOIS
STORE TMP_DATA
LOAD OLD_DATA 
SUB TMP_DATA
STORE TMP_DATA

;2+2=4

output TMP_DATA
COPY NEW_DATA, OLD_DATA
LOAD OLD_DATA
JMPP L1
STOP ;comentário útil aqui
SECTION DATA
DOIS: CONST 2
OLD_DATA: SPACE
NEW_DATA: SPACE
TMP_DATA: SPACE
