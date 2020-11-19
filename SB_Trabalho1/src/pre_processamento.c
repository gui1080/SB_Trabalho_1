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

    // vamos satisfazer os ifs e apagar comentarios, exportando tudo num arquivo .pre
    // deve-se apagar o que esta imediatamente baixo de um if falso

    int i, conta_equs, j, y;
    y=0; 
    int m, n; 
    char *resultado_de_leitura; 
    char *linha; // 200 espaços por linha como margem de segurança pois cada rótulo é variável tem até 50 caracteres cada 
                    // se a linha ocupa muito mais do que isso logo tem um comentário que é imediatamente descartado

    char char_atual;
     
    char *tokens; // cada linha do arquivo é dividida em tokens a serem analisadas
    char divisor[] = "\n "; // com base no espaço e na mudança de linhas as linhas no arquivo serão divididas

    // -----------------------------
    // tratamento dos arquivos

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

        // descobrimos que não foi passado umm arquivo .asm

        printf("Erro no formato do arquivo passado!\n"); 
        exit(0);         

    }

    // -----------------------------
    // tratamento de EQU e tokens

    char tabela_EQU[50][4][50]; 
    // 50 possiveis simbolos de equ/4 dimensoes/cada dimensão tem 50 espaços

    int limite_tam_termo = 50; 
    char *termo1;
    char *termo2; 
    char *termo3;
    char *termo4; 

    char *antigo1; 

    char ch = ':';

    int conta_linhas = 0; 

    termo1 = (char *) malloc(limite_tam_termo * sizeof(char)); 
    termo2 = (char *) malloc(limite_tam_termo * sizeof(char));
    termo3 = (char *) malloc(limite_tam_termo * sizeof(char));
    termo4 = (char *) malloc(limite_tam_termo * sizeof(char));
    antigo1 = (char *) malloc(limite_tam_termo * sizeof(char));

    linha = (char *) malloc((4*limite_tam_termo) * sizeof(char));
 
    // -----------------------------
    // flags

    int tem_label;
    int passou_do_sectiontext = 0; 

    int if_valido = 0;
    int conta_simbolos; 
    int pula_linha, pula_prox_linha; 

    // -----------------------------
    // tratamento de arquivos

    printf("Este é o nome do arquivo passado: %s\n", nome_do_arquivo);  

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
    pula_prox_linha = 0;

    int passou_do_sectiondata = 0; 

    int prox_linha = 1; 

    // -----------------------------
    // Loop da leitura de tokens

    while(!feof(file)){

        strcpy(antigo1, termo1);

        conta_linhas++; 

        if(prox_linha == 0){
            fprintf(file_teste, "\n"); // isso previne que no arquivo .pre existam linhas vazias a toa no final
            prox_linha = 1; 
        }

        if(pula_prox_linha == 1){
            pula_linha = 1;            // atualizando flags relacionadas à pular linhas
            pula_prox_linha = 0;
        }

        // linha que vai ser dividida em tokens
        resultado_de_leitura = fgets(linha, 100, file); 

        tokens = strtok(linha, divisor);
        i = 1; 

        while(tokens != NULL){
            //printf("%s \n\n\n", tokens);
            
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

        // i é a quantidade de tokens na linha

        i--; 

        //strcpy(antigo1, termo1);

        if(strcmp(termo1, antigo1) == 0){
            pula_linha = 1; 
        }

        if( (strcmp(linha, "\n") == 0) || (strcmp(linha, "\0") == 0) ){

            // ignora linha vazia

            pula_linha = 1; 
            i = 0;

            *termo1 = '\0';
            *termo2 = '\0';
            *termo3 = '\0';
            *termo4 = '\0'; 

        }

        // numa linha temos no máximo um rotulo com uma inst de 2 operandos, totalizando 4 termos ("tokens")
        // assim checo se um termo é comentário e passo a ignora-lo 
        // se havia um comentário após as 4 tokens, já foi descartado

        if(termo1[0] == ';'){
            pula_linha = 1; 
        }

        
        if(i==1){

            //printf("Termos na linha: %s\nQuantidade: %d\n\n", termo1, i);

            if(termo1[0] == ';'){
                pula_linha = 1; 
                termo1[0] = '\0';
                termo2[0] = '\0';
                termo3[0] = '\0'; 
                termo4[0] = '\0';
            }

        }
        if(i==2){
            
            //printf("Termos na linha: %s %s\nQuantidade: %d\n\n", termo1, termo2, i);

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

            //printf("Termos na linha: %s %s %s\nQuantidade: %d\n\n", termo1, termo2, termo3, i);

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

            //printf("Termos na linha: %s %s %s %s\nQuantidade: %d\n\n", termo1, termo2, termo3, termo4, i);
            
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
         

        // "i" é a quantidade de tokens que existem na linha
        // cada string "termoX" é a string com uma das tokens encontradas
        // para o pre processamento, deve-se ler o arquivo e ir tirando as linhas que os IFs mandam tirar
        // IF só vai existir se teve um EQU antes

        tem_label = acha_label(termo1); 

        if (tem_label == 1){
            conta_simbolos++;  
        }

        if ( ((passou_do_sectiontext == 1) && (strcmp(termo2, "EQU") == 0)) || ((passou_do_sectiontext == 1) && (strcmp(termo2, "equ") == 0)) ){
            
            printf("\nErro na linha %d: não era para ter um EQU depois do SECTION TEXT!\nErro semântico.\n", conta_linhas); 
            exit(0); 
        }

        if(tem_label == 1 && passou_do_sectiontext == 0){

            // bota os primeiros simbolos q vamos descartar no arquivo pre-processado final numa tabela
            // não se escreve essa linha no arquivo

            // tabela de EQU tem a estrutura termo1/termo2/"vai ser descartado ou não"?

            y=0;
            while(y < conta_equs){


                if(strcmp(tabela_EQU[y][0], termo1) == 0){

                    printf("\nErro na linha %d: diretiva EQU redefinindo uma label!\nErro semântico.\n", conta_linhas); 
                    exit(0); 
                }

                y++;

            }

            y = strlen(termo3);

            j=0;

            while(j<y){

                if(  !((termo3[j] >= '0') && (termo3[j] <= '9'))  ){    // essa comparação checa se todos os caracteres dessa token são dígitos ou não

                    printf("\nErro na linha %d: o EQU deveria receber um número, e não uma letra!\nErro sintaxico.\n", conta_linhas); 
                    exit(0); 
                
                }
                j++;
            }

            strcpy(tabela_EQU[conta_equs][0], termo1);

            strcpy(tabela_EQU[conta_equs][1], termo2);
    
            strcpy(tabela_EQU[conta_equs][2], termo3);

            tabela_EQU[conta_equs][3][0] = '0';

            conta_equs++; 
            pula_linha = 1; 

        }

        if(tem_label == 2){

            // achou o if
            // procura o simbolo na tabela temporaria pra ver se o proximo simbolo vai ser escrito no arquivo
            // a atual linha não será escrita
            // se if == 0, linha seguinte é ignorada

            pula_linha = 1;

            strncat(termo2, &ch, 1);
            
            y=0;
            while(y < conta_equs){

                if(strcmp(tabela_EQU[y][0], termo2) == 0){

                    tabela_EQU[y][3][0] = '1';

                    if_valido = 1;

                    if(strcmp(tabela_EQU[y][2], "0") == 0){
                        // proxima linha será ignorada
                        pula_prox_linha = 1; 
                    }
                    
                }

                y++;
            }

            if(if_valido == 1){

                if_valido = 0;

            }

            else{

                printf("\nErro na linha %d: o IF fez comparação com um termo indefinido!\nErro léxico.\n", conta_linhas); 
                exit(0);

            }

        }

        tem_label = 0; 


        if((strcmp(termo2, "TEXT") == 0) || (strcmp(termo2, "text") == 0)){
            
            // detro do section text, todos os rotulos q vieram antes podem ser apagados do contador
            // pode ser q estes sirvam apenas para os ifs
            
            conta_simbolos = 0; 
            passou_do_sectiontext = 1; 
            pula_linha = 0;

        }

        if((strcmp(termo2, "DATA") == 0) || (strcmp(termo2, "data") == 0)){
            
            // detro do section text, todos os rotulos q vieram antes podem ser apagados do contador
            // pode ser q estes sirvam apenas para os ifs
            
            passou_do_sectiondata = 1; 

        }

        if((strcmp(termo1, "COPY") == 0) || (strcmp(termo1, "copy") == 0)){
            
            // tiro a virgula do final do termo 2 para ajudar mais adiante e para checar erro
            // a estrutura do copy é: COPY X, Y
            // o segundo termo deve terminar em "," ou está equivocado 

            j=0;
            y=0;

             

            while(termo2[y] != '\0'){

                if(termo2[y] == ','){
                    termo2[y] = '\0';
                    j=1;
                }
                y++;
            }
            
            y=0;
            while(termo3[y] != '\0'){

                if(termo3[y] == ','){
                    j=0;
                }
                y++;
            }

            if(j==0){
                
                printf("\nErro na linha %d: Não é assim que se declara um COPY!\nErro sintático.\n", conta_linhas); 
                exit(0); 
            
            }
            
        }
    
        if(pula_linha == 0){


            switch(i){
                case 1 : fprintf(file_teste, "%s", termo1); break;
                case 2 : fprintf(file_teste, "%s %s", termo1, termo2); break;
                case 3 : fprintf(file_teste, "%s %s %s", termo1, termo2, termo3); break;
                case 4 : fprintf(file_teste, "%s %s %s %s", termo1, termo2, termo3, termo4); break;
                    
            }
            prox_linha = 0;

        }
        if(pula_linha == 1){
            pula_linha = 0; 
        } 

        //*termo1 = '\0';
        *termo2 = '\0';
        *termo3 = '\0';
        *termo4 = '\0'; 
    
    }


    //------------------------------------------------------------------------------------------
    // Final do loop de pré-processamento

    // Se libera a alocação dinâmica e se fecha arquivos

    free(termo1);
    free(termo2);
    free(termo3);
    free(termo4); 

    free(linha); 
    free(novo_nome_do_arquivo); 

    fclose(file);


    // obtém-se a tabela equ do q foi usado ou nao nos ifs, um arquivo de texto com as linhas limpas
    // junta tudo no arquivo .pre final

    for(i=0 ; i<conta_equs ; i++){

        if(tabela_EQU[i][3][0] == '0'){

            fprintf(file_final, "%s %s %s\n", tabela_EQU[i][0], tabela_EQU[i][1], tabela_EQU[i][2]);
            conta_simbolos++; 

        }

    }

    fclose(file_teste);

    file_teste = fopen("teste.txt", "r");

    while((char_atual = fgetc(file_teste)) != EOF){

        fprintf(file_final, "%c", char_atual);
        
    }


    //printf("\nQuantidade de símbolos para a atabela de símbolos: %d\n", conta_simbolos); 
    
    fclose(file_teste);

    remove("teste.txt");
    
    fclose(file_final);

    printf("\nArquivo .pre gerado com sucesso!\n"); 

}

