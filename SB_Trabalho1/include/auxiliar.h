// Aluno: Guilherme Braga Pinto
// Matrícula: 17/0162290
// Semestre 2020/01, UnB
// https://github.com/gui1080/SB_Trabalho_1


// Esta função tem como input uma operação do assembly inventado (como LOAD e MULT)
// E tem como saída o inteiro que representa a operação em código de máquina
int define_op_code(char *opcode); 

// Esta função recebe um arquivo e retorna o número de linhas que existem
int counter (FILE *fp);

// Esta função recebe uma operação do assembly e retorna seu tamanho junto de termos que o acompanha
// Por exemplo, ao receber um COPY, a função retorna 3 (estrutura: COPY + A + B)
int tamanho_op(char *opcode);

// Esta função recebe uma token e retorna se a token é uma label ou não. E detecta se é um IF também. 
// Caso não seja token: retorna 0
// Caso seja token: retorna 1
// Caso seja IF: retorna 2
int acha_label(char *termo); 