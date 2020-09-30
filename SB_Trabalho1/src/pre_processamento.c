// Aluno: Guilherme Braga Pinto
// Matrícula: 17/0162290
// Semestre 2020/01, UnB
// https://github.com/gui1080/SB_Trabalho_1

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pre_processamento.h>
#include <auxiliar.h>

void Pre_p(char *nome_do_arquivo) {

    // vamos satisfazer os ifs e apagar comentarios, exportando tudo num arquivo 
    // apago o que esta de baixo de um if falso ate um if positivo aparecer, e apago comentários

    int i, conta_equs, j, y, pula_linha, pula_prox_linha;
    y=0; 
    char *resultado_de_leitura; 
    char linha_reserva[200];
    char *linha; // 200 espaços por linha como margem de segurança pois cada rótulo é variável tem até 50 caracteres cada 
                    // se a linha ocupa muito mais do que isso logo tem um comentário que é imediatamente descartado

    char divisor[] = "\n "; 
    char *tokens; 

    char equ[3] = "EQU"; 

    int tamanho_do_nome_do_arquivo; 

    tamanho_do_nome_do_arquivo = strlen(nome_do_arquivo);

    char *novo_nome_do_arquivo; 

    novo_nome_do_arquivo = (char *) malloc(tamanho_do_nome_do_arquivo * sizeof(char));

    strcpy(novo_nome_do_arquivo, nome_do_arquivo);

    novo_nome_do_arquivo[tamanho_do_nome_do_arquivo-1] = 'e';
    novo_nome_do_arquivo[tamanho_do_nome_do_arquivo-2] = 'r';
    novo_nome_do_arquivo[tamanho_do_nome_do_arquivo-3] = 'p';

    if(nome_do_arquivo[tamanho_do_nome_do_arquivo-1] != 'm' ||
        nome_do_arquivo[tamanho_do_nome_do_arquivo-2] != 's' ||
        nome_do_arquivo[tamanho_do_nome_do_arquivo-3] != 'a'){

        printf("Erro no formato do arquivo passado!\n"); 
        exit(0);         

    }

    char tabela_EQU[50][4][50]; 

    // 50 possiveis simbolos de equ/4 dimensoes/cada dimensão tem 50 de espaço

    int limite_tam_termo = 50; 
    char *termo1;
    char *termo2; 
    char *termo3;
    char *termo4; 

    char ch = ':';

    pula_prox_linha = 0;
    int conta_linhas = 0; 

    termo1 = (char *) malloc(limite_tam_termo * sizeof(char)); 
    termo2 = (char *) malloc(limite_tam_termo * sizeof(char));
    termo3 = (char *) malloc(limite_tam_termo * sizeof(char));
    termo4 = (char *) malloc(limite_tam_termo * sizeof(char));

    linha = (char *) malloc((4*limite_tam_termo) * sizeof(char));
 
    int tem_label;
    int passou_do_sectiontext = 0; 

    int if_valido = 0;
    int conta_simbolos; 

    printf("Este é o nome do arquivo passado: %s\n", nome_do_arquivo); 
    printf("\n"); 

    FILE *file; 
    FILE *file_teste;
    FILE *file_final;

    file = fopen(nome_do_arquivo, "r");
    file_teste = fopen("teste.txt", "a");
    file_final = fopen(novo_nome_do_arquivo, "a"); 

    if((file == NULL)||(file_teste == NULL)||(file_final == NULL)){
        printf("Deu algo errado na abertura do arquivo"); 
    }

    for(i=0; i<50; i++){
        for(y=0; y<3; y++){
            for(j=0; j<50; j++){
                tabela_EQU[i][conta_equs][j] = '\0';  
            }
        }
    }

    i = 0; 
    conta_equs = 0; 
    j = 0; 
    pula_linha = 0;

    while(!feof(file)){

        conta_linhas++; 

        if(pula_prox_linha == 1){
            pula_linha = 1;
            pula_prox_linha = 0;
        }

        // a que a gnt vai dividir em tokens
        resultado_de_leitura = fgets(linha, 100, file); 

        // a que vai pro documento do pre-processamento
        strcpy(linha_reserva, linha);

        //printf("!!!%s!!!", linha);

        tokens = strtok(linha, divisor);
        i = 1; 

        while(tokens != NULL){
            printf("%s \n\n\n", tokens);
            
            if(tokens != NULL){
                switch(i){

                    case 1 : strcpy(termo1, tokens);
                    case 2 : strcpy(termo2, tokens);
                    case 3 : strcpy(termo3, tokens);
                    case 4 : strcpy(termo4, tokens); 
                
                }
                i++;  
            }


            //printf("%s %s %s", termo1, termo2, termo3); 
            tokens = strtok(NULL, divisor); 
        }
        i--; 
        if(i==1){
            printf("Termos na linha: %s\nQuantidade: %d\n\n", termo1, i);

            if(termo1[0] == ';'){
                pula_linha = 1; 
                termo1[0] = '\0';
                termo2[0] = '\0';
                termo3[0] = '\0'; 
                termo4[0] = '\0';
            }

        }
        if(i==2){
            printf("Termos na linha: %s %s\nQuantidade: %d\n\n", termo1, termo2, i);

            if(termo2[0] == ';'){
                termo2[0] = '\0';
                termo3[0] = '\0';
                termo4[0] = '\0'; 
            }

            if(termo1[0] == ';'){
                pula_linha = 1;
                termo1[0] = '\0';
                termo2[0] = '\0';
                termo3[0] = '\0'; 
                termo4[0] = '\0';
            }

        }
        if(i==3){
            printf("Termos na linha: %s %s %s\nQuantidade: %d\n\n", termo1, termo2, termo3, i);

            if(termo3[0] == ';'){
                termo3[0] = '\0';
                termo4[0] = '\0'; 
            }

            if(termo2[0] == ';'){
                termo2[0] = '\0';
                termo3[0] = '\0';
                termo4[0] = '\0'; 
            }

            if(termo1[0] == ';'){
                pula_linha = 1;
                termo1[0] = '\0';
                termo2[0] = '\0';
                termo3[0] = '\0'; 
                termo4[0] = '\0';
            }
        }
        if(i==4){
            printf("Termos na linha: %s %s %s %s\nQuantidade: %d\n\n", termo1, termo2, termo3, termo4, i);
            
            if(termo4[0] == ';'){
                termo4[0] = '\0'; 
            }

            if(termo3[0] == ';'){
                termo3[0] = '\0';
                termo4[0] = '\0'; 
            }

            if(termo2[0] == ';'){
                termo2[0] = '\0';
                termo3[0] = '\0';
                termo4[0] = '\0'; 
            }

            if(termo1[0] == ';'){
                pula_linha = 1;
                termo1[0] = '\0';
                termo2[0] = '\0';
                termo3[0] = '\0'; 
                termo4[0] = '\0';
            }
        }    
         
        // acho q n tá funcionando isso daqui :/
        //memset(termo1, 0, 50); 
        //memset(termo2, 0, 50); 
        //memset(termo3, 0, 50); 


        // "i" é a quantidade de tokens que achamos
        // cada string "termoX" é a string com uma das tokens encontradas
        // para o pre processamento, vamos ler o arquivo e ir tirando as linhas que os IFs mandam tirar
        // IF só vai existir se teve um EQU antes

        printf("\n\ntermo 1 : %s\n\n", termo1); 

        tem_label = acha_label(termo1); 

        if (tem_label == 1){
            conta_simbolos++; 
            printf("é label"); 
        }

        if ( (passou_do_sectiontext == 1) && (strcmp(termo2, "EQU") == 0) ){
            
            printf("\nErro na linha %d: não era para ter um EQU depois do SECTION TEXT!\nErro semântico.\n", conta_linhas); 
            exit(0); 
        }

        if(tem_label == 1 && passou_do_sectiontext == 0){
            // bota os primeiros simbolos q vamos descartar no arquivo pre-processado final numa tabela
            // não escrevemos essa linha no arquivo

            // tabela de EQU tem a estrutura termo1/termo2/"vai ser descartado ou não"?

            y=0;
            while(y < conta_equs){

                printf("\ncomparei %s e %s\n", termo1, tabela_EQU[y][0]);

                if(strcmp(tabela_EQU[y][0], termo1) == 0){

                    printf("\nErro na linha %d: diretiva EQU redefinindo uma label!\nErro semântico.\n", conta_linhas); 
                    exit(0); 

                    //printf("\n\n!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!%s %s\n\n", tabela_EQU[y][0], termo2);
                }
                y++;
            }

            strcpy(tabela_EQU[conta_equs][0], termo1);

            y=0;
            j=0;

            //j=0;

            //while(termo1[j] != '\0'){
               // tabela_EQU[y][0][j] = termo1[j]; 
              //  j++; 
            //}

            strcpy(tabela_EQU[conta_equs][1], termo2);
            
            j=0; 

            //while(termo2[j] != '\0'){
              //  tabela_EQU[y][1][j] = termo1[j]; 
               // j++; 
            //}
            strcpy(tabela_EQU[conta_equs][2], termo3);

            tabela_EQU[conta_equs][3][0] = '0';

            conta_equs++; 
            pula_linha = 1; 

        }


        if(tem_label == 1 && passou_do_sectiontext == 1){
            // é uma label dentro do section text
            // escrevemos essa linha no arquivo

        }

        if(tem_label == 0){
            // escreve a linha no arquivo pre-processado

        }


        if(tem_label == 2){
            // achou o if
            // procura o simbolo na tabela temporaria pra ver se o proximo simbolo vai ser escrito no arquivo
            // a atual linha não será escrita
            // se if == 1, linha seguinte é ignoradas

            pula_linha = 1;

            strncat(termo2, &ch, 1);
            
            y=0;
            while(y < conta_equs){

                printf("\ncomparei %s e %s\n", termo2, tabela_EQU[y][0]);

                if(strcmp(tabela_EQU[y][0], termo2) == 0){

                    tabela_EQU[y][3][0] = '1';
                    printf("\nachei\n"); 
                    printf("\ncomparei %s e 0\n", tabela_EQU[y][2]);

                    if_valido = 1;

                    if(strcmp(tabela_EQU[y][2], "0") == 0){
                        printf("ignora a proxima linha!");
                        pula_prox_linha = 1; 
                    }
                    
                    //printf("\n\n!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!%s %s\n\n", tabela_EQU[y][0], termo2);
                }
                y++;
            }
            if(if_valido == 1){
                if_valido = 0;
            }
            else{
                printf("\nErro na linha %d: o IF fez comparação com um termo indefinido!\nErro semântico.\n", conta_linhas); 
                exit(0); 
            }

        }

        // escreve tudo num temp sem os EQU, ai escreve os EQUs importantes em um novo arquivo e ai então insere as linhas do arquivo antigo?

        printf("\n---------TEM LABEL?: %d\n", tem_label);

        tem_label = 0; 


        if(strcmp(termo2, "TEXT") == 0){
            // detro do section text, todos os rotulos q vieram antes podem ser apagados do contador
            // pode ser q estes sirvam apenas para os ifs
            conta_simbolos = 0; 
            passou_do_sectiontext = 1; 
            pula_linha = 0;
        }

        if(strcmp(termo1, "COPY") == 0){
            // vamos tirar a virgula do final do termo 2 só para ajudar 
            j=0;
            y=0;
            while(j==0){

                if(termo2[y] == ','){
                    termo2[y] = '\0';
                    j=1;
                }
                y++;
            }
            
        }

        // numa linha tenho no máximo um rotulo com uma inst de 2 operandos, totalizando 4 termos
        // assim checo se um termo é comentário e passo a ignora-lo 
        if(termo4[0] == ';'){
            printf("\n\nAchei o comentário\n\n");
            //apaga ele e continua

        }


        if(resultado_de_leitura){
            //printf("!!!%s!!!", linha);
        }
        //printf("\n");
    
    
        if(pula_linha == 0){
            switch(i){
                case 1 : fprintf(file_teste, "%s\n", termo1); break;
                case 2 : fprintf(file_teste, "%s %s\n", termo1, termo2); break;
                case 3 : fprintf(file_teste, "%s %s %s\n", termo1, termo2, termo3); break;
                case 4 : fprintf(file_teste, "%s %s %s %s\n", termo1, termo2, termo3, termo4); break;
                    
            }
        }
        if(pula_linha == 1){
            pula_linha = 0; 
        }
    
    
    
    }


    free(termo1);
    free(termo2);
    free(termo3);
    free(termo4); 

    free(linha); 
    free(novo_nome_do_arquivo); 

    fclose(file);

    /*

    for(i=0; i<3; i++){
        
            
        printf("%c ", tabela_EQU[i][3][0]); 
           
        
        printf("\n"); 
    }
    */

    // temos a tabela equ do q foi usado ou nao nos ifs, um arquivo de texto com as linhas limpas
    // junta tudo em 1 arquivo só

    printf("%s %d", novo_nome_do_arquivo, conta_equs); 

    for(i=0 ; i<conta_equs ; i++){

        if(tabela_EQU[i][3][0] == '0'){

            fprintf(file_final, "%s %s %s\n", tabela_EQU[i][0], tabela_EQU[i][1], tabela_EQU[i][2]);
            conta_simbolos++; 

        }

    }

    char c; 

    fclose(file_teste);

    file_teste = fopen("teste.txt", "r");

    

    while((c = fgetc(file_teste)) != EOF){
        printf("%c", c);
        fprintf(file_final, "%c", c);
    }

    //resultado_de_leitura = fgets(linha, 200, file_teste);
    //printf("%s", resultado_de_leitura); 

    //while(!feof(file_teste)){

    //    resultado_de_leitura = fgets(linha, 100, file_teste);
    //    resultado = fputs(linha, file_final); 

    //}
    


    printf("\nQuantidade de símbolos para a atabela de símbolos: %d\n", conta_simbolos); 
    
    fclose(file_teste);

    remove("teste.txt");
    
    fclose(file_final);

}

