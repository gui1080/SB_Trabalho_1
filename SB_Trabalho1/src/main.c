// Aluno: Guilherme Braga Pinto
// Matrícula: 17/0162290
// Semestre 2020/01, UnB
// https://github.com/gui1080/SB_Trabalho_1


//------------------------
// libs

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

//------------------------
// pasta include

#include <pre_processamento.h>
#include <montagem.h>

//------------------------


int main(int argc, char *argv[]) {

  // argv -p: apenas pre-precessamento
  // argv -o: faz o arquivo objeto
  
  // sempre passa "./main -p/-o programinha.asm" (dois argumentos)

  int i; 
  char faz_obj[] = "-o";
  char faz_prep[] = "-p"; 
  char nome_do_arquivo[30]; 
  char instrucao[2]; 

  printf("Foi passado na linha de comando:\n"); 

  for(i=0; i<argc; i++){
    printf("%d: %s\n", i, argv[i]); 
  }
  
  strcpy(nome_do_arquivo, argv[2]);
  strcpy(instrucao, argv[1]); 

  if(strcmp(instrucao, "-p") == 0){

    // ./main -p seuprograma.asm

    //faz o pre-processamento

    Pre_p(nome_do_arquivo); 

  }


  if(strcmp(instrucao, "-o") == 0){

    // ./main -o seuprograma.pre

    // faz o arquivo objeto
    
    // o usuário deve antes executar o pre-processamento

    Monta_assembly(nome_do_arquivo); 

  }


  return(0);
}

