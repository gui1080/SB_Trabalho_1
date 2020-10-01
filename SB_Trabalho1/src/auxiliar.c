// Aluno: Guilherme Braga Pinto
// Matrícula: 17/0162290
// Semestre 2020/01, UnB
// https://github.com/gui1080/SB_Trabalho_1


#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int acha_label(char *termo){

    int i; 
    i = 0; 

    if((strcmp(termo, "IF:") == 0) || (strcmp(termo, "if:") == 0)){
        return 2; 
    }

    while(i < 50){
        if(termo[i] == ':'){ 
            return 1; 
        }
        if(termo[i] == '\0'){
            return 0;
        }
        i++; 
    }
}

int tamanho_op(char *opcode){

    // função serve para se calcular o número a se somar ao endereço atual 
    // aqui se considera que a operação/diretiva existe

    if((strcmp(opcode, "COPY") == 0) || (strcmp(opcode, "copy") == 0)){
        return 3; 
    }

    if((strcmp(opcode, "SECTION") == 0) || (strcmp(opcode, "section") == 0) || (strcmp(opcode, "EQU") == 0) || (strcmp(opcode, "equ") == 0)){
        return 0; 
    }

    if((strcmp(opcode, "STOP") == 0) || (strcmp(opcode, "stop") == 0) || 
    (strcmp(opcode, "SPACE") == 0) || (strcmp(opcode, "space") == 0) || 
    (strcmp(opcode, "CONST") == 0) || (strcmp(opcode, "const") == 0) )
    {
        return 1; 
    }

    return (2); // o resto das operações só retorna 2. 

}

int counter (FILE *fp) {
  int c = 0, numCod = 0, cont = 0;

  char texto[(sizeof(fp) * 1024)];
//--------------------------------------------------
  if(fp !=NULL){        // se conseguimos abrir o arquivo
      do{
        c = fgetc(fp);    //pegamos sempre o seguinte simbolo
        if(c=='\n'){   //se chegamos no final da linha
          numCod++;     //atualizamos o numero de linhas
        }
        texto[cont] = c;  //armazenamos o texto
        cont++;      // contamos o processo
      }while(c!= EOF);
  }else {
    printf("Impossivel abrir o arquivo\n");  // erro!
    exit(0); 
  }
  return numCod;
}

int define_op_code(char *opcode){

    if((strcmp(opcode, "ADD") == 0) || (strcmp(opcode, "add") == 0)){
        return 1; 
    }

    if( (strcmp(opcode, "SUB") == 0) || (strcmp(opcode, "sub") == 0)){
        return 2; 
    }

    if((strcmp(opcode, "MULT") == 0) || (strcmp(opcode, "mult") == 0)){
        return 3; 
    }

    if((strcmp(opcode, "DIV") == 0) || (strcmp(opcode, "div") == 0)){
        return 4; 
    }
    
    if((strcmp(opcode, "JMP") == 0) || (strcmp(opcode, "jmp") == 0)){
        return 5; 
    }
    
    if((strcmp(opcode, "JMPN") == 0) || (strcmp(opcode, "jmpn") == 0)){
        return 6; 
    }

    if((strcmp(opcode, "JMPP") == 0) || (strcmp(opcode, "jmpp") == 0)){
        return 7; 
    }

    if((strcmp(opcode, "JMPZ") == 0) || (strcmp(opcode, "jmpz") == 0)){
        return 8; 
    }

    if((strcmp(opcode, "COPY") == 0) || (strcmp(opcode, "copy") == 0)){
        return 9; 
    }

    if((strcmp(opcode, "LOAD") == 0) || (strcmp(opcode, "load") == 0)){
        return 10; 
    }

    if((strcmp(opcode, "STORE") == 0) || (strcmp(opcode, "store") == 0)){
        return 11; 
    }

    if((strcmp(opcode, "INPUT") == 0) || (strcmp(opcode, "input") == 0)){
        return 12; 
    }

    if((strcmp(opcode, "OUTPUT") == 0) || (strcmp(opcode, "output") == 0)){
        return 13; 
    }

    if((strcmp(opcode, "STOP") == 0) || (strcmp(opcode, "stop") == 0)){
        return 14; 
    }

    //if((strcmp(opcode, "SECTION") == 0) || (strcmp(opcode, "section") == 0)){
    //    return 15;
        // vai começar o section text ou o section data
        // nesse caso só pula a linha  
    //}

    // se chegou até aqui a instrução deve ser inválida, temos um erro

    //printf("Erro: %s não é um termo!\nO programa será pausado agora.\n", opcode); 
    //exit(0); 
    return 0;
}
