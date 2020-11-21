// Aluno: Guilherme Braga Pinto
// Matrícula: 17/0162290
// Semestre 2020/01, UnB
// https://github.com/gui1080/SB_Trabalho_1

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <montagem.h>
#include <auxiliar.h>

// 
// REGRA DE USO: Arquivo de input precisa terminar com uma linha vazia (tanto no pré-processamento como na hora de montar)

void Monta_assembly(char *nome_do_arquivo){

    // -----------------------------
    // variáveis e flags

    int tamanho_do_nome_do_arquivo; 

    int linhas_no_arquivo; 

    int simbolo_encontrado = 0;
    
    tamanho_do_nome_do_arquivo = strlen(nome_do_arquivo);

    char *nome_do_arquivo_obj;
    char *nome_do_arquivo_pre; 

    char *resultado_de_leitura; 

    char divisor[] = "\n "; // com base nesses caracteres a linha deverá ser dividida em tokens
    char *tokens; 
    char *linha;
    int i, x = 0; 
    int y;


    int passou_section_text = 0;
    int passou_section_data = 0;

    int acumulador_do_endereco = 0; 
    int somador = 0; 
    char end_em_string[12];
    char op_em_string[12];
    int simbolos_existentes = 0;
    int passou_do_stop = 0; 


    // -----------------------------
    // tokens e tratamento de arquivos

    int limite_tam_termo = 50; 

    char *termo1;
    char *termo2; 
    char *termo3;
    char *termo4; 

    termo1 = (char *) malloc(limite_tam_termo * sizeof(char)); 
    termo2 = (char *) malloc(limite_tam_termo * sizeof(char));
    termo3 = (char *) malloc(limite_tam_termo * sizeof(char));
    termo4 = (char *) malloc(limite_tam_termo * sizeof(char));

    linha = (char *) malloc((4*limite_tam_termo) * sizeof(char));
 
    int tem_label = 0; 

    nome_do_arquivo_obj = (char *) malloc(tamanho_do_nome_do_arquivo * sizeof(char));
    nome_do_arquivo_pre = (char *) malloc(tamanho_do_nome_do_arquivo * sizeof(char));

    strcpy(nome_do_arquivo_obj, nome_do_arquivo);
    strcpy(nome_do_arquivo_pre, nome_do_arquivo);


    if( (nome_do_arquivo_pre[tamanho_do_nome_do_arquivo-1] != 'e') ||
        (nome_do_arquivo_pre[tamanho_do_nome_do_arquivo-2] != 'r') ||
        (nome_do_arquivo_pre[tamanho_do_nome_do_arquivo-3] != 'p')
    ){

        // o nome passado está incorreto
        
        printf("O formato do arquivo passado está incorreto!"); 
        exit(0); 

    }

    nome_do_arquivo_obj[tamanho_do_nome_do_arquivo-1] = 'j';
    nome_do_arquivo_obj[tamanho_do_nome_do_arquivo-2] = 'b';
    nome_do_arquivo_obj[tamanho_do_nome_do_arquivo-3] = 'o';

    FILE *file_pre;
    FILE *file_obj;


    file_pre = fopen(nome_do_arquivo_pre, "r");

    if(file_pre == NULL){

        printf("\nErro na abertura do arquivo .pre\n"); 
        exit(0); 

    }

    linhas_no_arquivo = counter(file_pre); 
    fclose(file_pre);

    // Primeira passagem
    // Na primeira passagem, se detecta alguns erros e se gera a Tabela de Símbolos
    //------------------------------------------------------------------------------------------
    // Para que a leitura ocorra de forma eficiente, o arquivo pré-processado não deveria ser manipulado após a sua geração.
    // A escrita de um .pre não apresenta linhas vazias, especialmente no final do programa, assim como os arquivos .asm.


    file_pre = fopen(nome_do_arquivo_pre, "r");

    // zeramos contadores e outras variávies 
    int k = 0;
    int linha_atual = 0;
    int j = 0;
    int op = 0; 

    // o tamanho da tabela de simbolos está sendo alocado arredondando para o pior caso
    // quando a quantidade de símbolos é definida, o tamanho da matriz será realocado de forma correta

    char (* tabela_de_simbolos )[2][50] = malloc(sizeof(char) * linhas_no_arquivo * 2 * 50);

    // tabela_de_simbolos[x][0] = simbolo em si
    // tabela_de_simbolos[x][1] = endereço

    for(k=0; k<linhas_no_arquivo; k++){
        for(j=0; j<2; j++){
            strcpy(tabela_de_simbolos[k][j], "\0"); 
        }
    }

    j = 0;
    k = 0;

    int loop = 0; 
    int era_equ = 0;

    // loop enquanto o arquivo não termina
    while(loop < linhas_no_arquivo){

        sprintf(end_em_string, "%d", acumulador_do_endereco);

        // a que a gnt vai dividir em tokens
        resultado_de_leitura = fgets(linha, 200, file_pre); 

        tokens = strtok(linha, divisor);
        i = 1; 

        do{

                switch(i){

                    case 1 : strcpy(termo1, tokens);
                    case 2 : strcpy(termo2, tokens);
                    case 3 : strcpy(termo3, tokens);
                    case 4 : strcpy(termo4, tokens); 
                
                }

                i++;  

            tokens = strtok(NULL, divisor); 
            
        }while(tokens != NULL);

        
        // i é a quantidade de tokens

        i--; 

        // Este print tem como objetivo mostrar o que se pegou da linha lida
        /*
        if(i==1){
            printf("Termos na linha: %s\nQuantidade: %d\n\n", termo1, i);
        }
        if(i==2){
            printf("Termos na linha: %s %s\nQuantidade: %d\n\n", termo1, termo2, i);
        }
        if(i==3){
            printf("Termos na linha: %s %s %s\nQuantidade: %d\n\n", termo1, termo2, termo3, i);
        }
        if(i==4){
            printf("Termos na linha: %s %s %s %s\nQuantidade: %d\n\n", termo1, termo2, termo3, termo4, i);
        } 
        */

        k++; 

        somador = tamanho_op(termo1); 
         
        tem_label = acha_label(termo1); 

        if (tem_label == 1){

            // se estamos tratando de uma label
            
            if( (!(strcmp(termo2, "EQU") == 0)) || (!(strcmp(termo2, "equ") == 0)) ){ 

                if(i != 1){

                    // uma label mas não é uma diretiva de EQU e não está sozinha na linha
                    somador = tamanho_op(termo2); 
                    acumulador_do_endereco = acumulador_do_endereco + somador;
                    
                }
                else{

                    somador = 0; 

                }
            }
            
            for(x=0; x<50; x++){
                
                // elimina-se o ":" para a tabela de símbolos 

                if(termo1[x] == ':'){
                
                    termo1[x] = '\0'; 
                
                }
            }

            for(x=0; x<simbolos_existentes ; x++){
                
                // procuramos o símbolo atual na tabela de símbolos para ver se está sendo redefinido

                if( strcmp(termo1, tabela_de_simbolos[x][0]) == 0 ){

                    printf("\nErro na linha %d: símbolo sendo redefinido!\nErro semântico.\n", k);  
                    //exit(0);   

                } 
            }



            if( (strcmp(termo2, "EQU") == 0) || (strcmp(termo2, "equ") == 0) ){

                // Tratamnento do EQU

                if(passou_section_text == 1){

                    printf("\nErro na linha %d: diretiva EQU é para ocorrer antes do SECTION TEXT!\nErro semântico.\n", k); 
                    //exit(0); 
                    
                }

                strcpy(tabela_de_simbolos[simbolos_existentes][0], termo1); 
                strcpy(tabela_de_simbolos[simbolos_existentes][1], termo3);

            } 
            else{

                if(passou_section_data == 0){

                    // Só se pode declarar estas variáveis depois de um SECTION DATA

                    if( (strcmp(termo2, "CONST") == 0) || (strcmp(termo2, "SPACE") == 0) || (strcmp(termo2, "const") == 0) || (strcmp(termo2, "space") == 0) ){

                        printf("\nErro na linha %d: esta diretiva é para ocorrer depois do SECTION DATA!\nErro semântico.\n", k); 
                        //exit(0); 

                    }
                }

                strcpy(tabela_de_simbolos[simbolos_existentes][0], termo1); 
                strcpy(tabela_de_simbolos[simbolos_existentes][1], end_em_string);

            }
           

            if(simbolos_existentes < linhas_no_arquivo){

                simbolos_existentes++;

            }
            

            linha_atual++;

        }
        else{

            // aqui não estamos tratando de uma linha com label

            // Tratamos diretivas "SECTION"

            if( !(strcmp(termo1, "SECTION") == 0) && !(strcmp(termo1, "section") == 0) ){
      
                acumulador_do_endereco = acumulador_do_endereco + somador;

                linha_atual++;
            }   

            if((strcmp(termo2, "TEXT") == 0) || (strcmp(termo2, "text") == 0)){

                passou_section_text = 1; 

            }

            if((strcmp(termo2, "DATA") == 0) || (strcmp(termo2, "data") == 0)){

                passou_section_data = 1;

            }

        }

        loop++; 

    }

    fclose(file_pre); 

    // printf("\nTabela de Símbolos resultante da Primeira Passagem!\n");

    tabela_de_simbolos = realloc( tabela_de_simbolos, sizeof(char) * simbolos_existentes * 2 * 50); 

    /*

    for(x=0; x<simbolos_existentes ; x++){
        for(y=0 ; y<2 ; y++){
            printf("%s ", tabela_de_simbolos[x][y]);    
        }
        printf("\n"); 
    }

    */

    //------------------------------------------------------------------------------------------
    // Final da primeira passagem

    // Próximas tarefas a serem executadas:

    // abrir o arquivo final obj
    // ir traduzindo item por item, já botando no arquivo final 
    // fontes para a tradução: função de definir op code e Tabela de Símbolos

    // Segunda passagem
    //------------------------------------------------------------------------------------------

    file_pre = fopen(nome_do_arquivo_pre, "r");

    passou_section_text = 0;
    passou_section_data = 0;

    file_obj = fopen(nome_do_arquivo_obj, "a");
    //printf("%s\n\n", nome_do_arquivo_obj); 

    if(file_obj == NULL){
        printf("Deu algo errado na abertura do arquivo\n"); 
        exit(0); 
    }

    k = 0; 

    while(!feof(file_pre)){

        // a que a gnt vai dividir em tokens
        resultado_de_leitura = fgets(linha, 200, file_pre); 

        tokens = strtok(linha, divisor);

        i = 1; 

        do{

                switch(i){

                    case 1 : strcpy(termo1, tokens);
                    case 2 : strcpy(termo2, tokens);
                    case 3 : strcpy(termo3, tokens);
                    case 4 : strcpy(termo4, tokens); 
                
                }
                i++;       

            tokens = strtok(NULL, divisor); 
            
        }while(tokens != NULL);

        
        i--; 
        
        // Estrutura para checar as tokens recuperadas
        /*
        if(i==1){
            printf("Termos na linha: %s\nQuantidade: %d\n\n", termo1, i);
        }
        if(i==2){
            printf("Termos na linha: %s %s\nQuantidade: %d\n\n", termo1, termo2, i);
        }
        if(i==3){
            printf("Termos na linha: %s %s %s\nQuantidade: %d\n\n", termo1, termo2, termo3, i);
        }
        if(i==4){
            printf("Termos na linha: %s %s %s %s\nQuantidade: %d\n\n", termo1, termo2, termo3, termo4, i);
        } 
        */
        
        k++; 

        // Detectamos o STOP. Precisamos do STOP neste assembly para saber onde o programa acaba.
        if((strcmp(termo1, "STOP") == 0) || (strcmp(termo1, "stop") == 0) ){

            passou_do_stop = 1;

        }
         

        tem_label = acha_label(termo1); 

        if (tem_label == 1){

            // Tratamento de labels

            if( (acha_label(termo2)) && (i != 1) ){

                // duas labels na mesma linha!!!

                printf("\nErro na linha %d: duas labels definidas na mesma linha!\nErro sintático.\n", k);
                //fclose(file_obj); 
                //remove(nome_do_arquivo_obj);
                //exit(0);

            }
            if( i == 3 ){

                if( acha_label(termo3) ){
                    // duas labels na mesma linha!!!
                    printf("\nErro na linha %d: duas labels definidas na mesma linha!\nErro sintático.\n", k);
                    //fclose(file_obj); 
                    //remove(nome_do_arquivo_obj);
                    //exit(0);

                }

            }
            if( i == 4 ){

                if( acha_label(termo3) ){
                    // duas labels na mesma linha!!!
                    printf("\nErro na linha %d: duas labels definidas na mesma linha!\nErro sintático.\n", k);
                    //fclose(file_obj); 
                    //remove(nome_do_arquivo_obj);
                    //exit(0);

                }

                if( acha_label(termo4) ){
                    // duas labels na mesma linha!!!
                    printf("\nErro na linha %d: duas labels definidas na mesma linha!\nErro sintático.\n", k);
                    //fclose(file_obj); 
                    //remove(nome_do_arquivo_obj);
                    //exit(0);

                }

            }


            if((strcmp(termo2, "SPACE") == 0) || (strcmp(termo2, "space") == 0)){
            
                // se o segundo termo da linha é SPACE, devemos imprimir "OO"
                
                fprintf(file_obj, "O ");


            }
            if((strcmp(termo2, "CONST") == 0) || (strcmp(termo2, "const") == 0)){

                x=0;
                while( x<(strlen(termo3)) ){

                    if(  !((termo3[x] >= '0') && (termo3[x] <= '9'))  ){    // essa comparação checa se todos os caracteres dessa token são dígitos ou não

                        printf("\nErro na linha %d: o CONST deveria receber um número, e não uma letra!\nErro sintaxico.\n", k); 
                        //fclose(file_obj); 
                        //remove(nome_do_arquivo_obj);
                        //exit(0); 
                
                    }
                x++;
            }

                // caso seja um const, se imprime o que havia sido declarado

                fprintf(file_obj, "%s ", termo3);

            }

            else{   // não estão sendo tratados os últimos casos abordados

                if(i != 1){

                    op = define_op_code(termo2);
                    
                    if(op == 0){

                        // não achamos essa operação na tabela

                        if( !(strcmp(termo2, "EQU") == 0) && !(strcmp(termo2, "CONST") == 0) && !(strcmp(termo2, "SPACE") == 0) && 
                        !(strcmp(termo2, "equ") == 0) && !(strcmp(termo2, "const") == 0) && !(strcmp(termo2, "space") == 0)){
                            
                            printf("\nErro na linha %d: diretiva inválida após criação de label!\nErro sintático.\n", k);
                            //fclose(file_obj); 
                            //remove(nome_do_arquivo_obj);
                            //exit(0); 

                        }

                    }
                    else{

                        // achamos a operação, que deverá ser acompanhada de uma quantidade definida de valores da Tabela de Símbolos

                        // imprimiu a operação
                        
                        fprintf(file_obj, "%d ", op);

                        if(i == 3){
                            
                            // tem 1 simbolo da TS pra imprimir (label + operação + simbolo)

                            for(x=0; x<simbolos_existentes ; x++){
                                if( strcmp(termo3, tabela_de_simbolos[x][0]) == 0 ){
                                    // achamos o símbolo
                                
                                    fprintf(file_obj, "%s ", tabela_de_simbolos[x][1]);  
                                    simbolo_encontrado = 1;
                                }
                            }
                            if(simbolo_encontrado == 1){
                                simbolo_encontrado = 0;
                            }
                            else{

                                for(x=0; x< strlen(termo3) ; x++ ){
                                    if(  ((termo3[x] >= '0') && (termo3[x] <= '9'))  ){
                                        // se esse if foi satisfeito, o termo não teve letra e foi só numeros
                                        // assumo ser um equ
                                        era_equ = 1; 
                                    }
                                }

                                if(era_equ == 1){
                                    fprintf(file_obj, "%s ", termo3);
                                    era_equ = 0; 
                                    simbolo_encontrado = 0;
                                }else{
                                    printf("\nErro na linha %d: símbolo não encontrado!\nErro léxico.\n", k);
                                    //exit(0);
                                    era_equ = 0;
                                }

                            }

                        } 
                        if(i == 4){
                            
                            // tem 2 simbolo da TS pra imprimir (label + operação + simbolo + símbolo)

                            for(x=0; x<simbolos_existentes ; x++){
                                if( strcmp(termo3, tabela_de_simbolos[x][0]) == 0 ){
                                    // achamos o símbolo
                                    
                                    fprintf(file_obj, "%s ", tabela_de_simbolos[x][1]);   
                                    simbolo_encontrado = 1;
                                } 
                            }
                            if(simbolo_encontrado == 1){
                                simbolo_encontrado = 0;
                            }
                            else{

                                for(x=0; x< strlen(termo3) ; x++ ){
                                    if(  ((termo3[x] >= '0') && (termo3[x] <= '9'))  ){
                                        // se esse if foi satisfeito, o termo não teve letra e foi só numeros
                                        // assumo ser um equ
                                        era_equ = 1; 
                                    }
                                }

                                if(era_equ == 1){
                                    fprintf(file_obj, "%s ", termo3);
                                    era_equ = 0; 
                                    simbolo_encontrado = 0;
                                }else{
                                    printf("\nErro na linha %d: símbolo não encontrado!\nErro léxico.\n", k);
                                    //exit(0);
                                    era_equ = 0;
                                    simbolo_encontrado = 0;
                                }

                            }

                            for(x=0; x<simbolos_existentes ; x++){
                                if( strcmp(termo4, tabela_de_simbolos[x][0]) == 0 ){
                                    // achamos o símbolo
                                    
                                    fprintf(file_obj, "%s ", tabela_de_simbolos[x][1]);
                                    simbolo_encontrado = 1;
                                }
                            }
                            if(simbolo_encontrado == 1){
                                simbolo_encontrado = 0;
                            }
                            else{

                                for(x=0; x< strlen(termo4) ; x++ ){
                                    if(  ((termo4[x] >= '0') && (termo4[x] <= '9'))  ){
                                        // se esse if foi satisfeito, o termo não teve letra e foi só numeros
                                        // assumo ser um equ
                                        era_equ = 1; 
                                    }
                                }

                                if(era_equ == 1){
                                    fprintf(file_obj, "%s ", termo4);
                                    era_equ = 0; 
                                    simbolo_encontrado = 0;
                                }else{
                                    printf("\nErro na linha %d: símbolo não encontrado!\nErro léxico.\n", k);
                                    //exit(0);
                                    era_equ = 0;
                                }

                            } 

                        } 

                    }
                }

                //printf("\n\n%s %s %s %s : %d\n\n", termo1, termo2, termo3, termo4, i); 

                if(i == 1){

                    // se esta passando por uma label sozinha na linha sem nada a fazer
                    op = define_op_code(termo1);
                    
                    if(op == 0){

                        // não achamos essa operação na tabela
                        // deve ser um endreço de memória
                        for(x=0; x<simbolos_existentes ; x++){
                            if( strcmp(termo1, tabela_de_simbolos[x][0]) == 0 ){
                                // achamos o símbolo
                                fprintf(file_obj, "%s ", tabela_de_simbolos[x][1]);  
                                simbolo_encontrado = 1;
                            }
                        }

                        if(simbolo_encontrado == 1){
                            simbolo_encontrado = 0;
                        }
                    }
                    else{
                        // imprime a operação sozinha
                        fprintf(file_obj, "%d ", op);

                    }

                }
            
            }

        }
        else{

            // não se trata de uma label (não consideramos nesta etapa que poderia ser um espaço em branco)

            if( !(strcmp(termo1, "SECTION") == 0) && !(strcmp(termo1, "section") == 0) ){ // ignoramos os sections por agora

                // decodifica o termo 1, ve quantos termos tem e procura esses termos na Tabela de Simbolos

                somador = tamanho_op(termo1);  

                if(i == somador){ // detecta-se se a quantidade de argumentos passada está correta para a operação definida

                    // a quantidade de instruções passadas está correta
                    op = define_op_code(termo1);

                    if(op == 0){

                        printf("\nErro na linha %d: operação inválida!\nErro léxico.\n", k); 
                        //exit(0);
                        
                    }

                    fprintf(file_obj, "%d ", op);

                    if(i == 2){

                        // tem potencialmente 1 simbolo da TS pra imprimir (operaçao + simbolo)

                        for(x=0; x<simbolos_existentes ; x++){
                            if( strcmp(termo2, tabela_de_simbolos[x][0]) == 0 ){
                                // achamos o símbolo
                                
                                fprintf(file_obj, "%s ", tabela_de_simbolos[x][1]); 
                                simbolo_encontrado = 1;
                                
                            } 
                        }

                        if(simbolo_encontrado == 1){
                            simbolo_encontrado = 0;
                        }
                        else{

                            for(x=0; x< strlen(termo2) ; x++ ){
                                if(  ((termo2[x] >= '0') && (termo2[x] <= '9'))  ){
                                    // se esse if foi satisfeito, o termo não teve letra e foi só numeros
                                    // assumo ser um equ
                                    era_equ = 1; 
                                }
                            }

                            if(era_equ == 1){
                                fprintf(file_obj, "%s ", termo2);
                                era_equ = 0; 
                                simbolo_encontrado = 0;
                            }else{
                                printf("\nErro na linha %d: símbolo não encontrado!\nErro léxico.\n", k);
                                //exit(0);
                                era_equ = 0;
                            }

                        }
                        
                    } 

                    if(i == 3){
                        
                        // tem potencialmente 2 simbolos da TS pra imprimir (operaçao + simbolo + simbolo)

                        for(x=0; x<simbolos_existentes ; x++){
                            if( strcmp(termo2, tabela_de_simbolos[x][0]) == 0 ){
                                // achamos o símbolo
                                 
                                fprintf(file_obj, "%s ", tabela_de_simbolos[x][1]);
                                simbolo_encontrado = 1;
                            } 
                        }
                        
                        if(simbolo_encontrado == 1){
                            simbolo_encontrado = 0;
                        }
                        else{

                            for(x=0; x< strlen(termo2) ; x++ ){
                                if(  ((termo2[x] >= '0') && (termo2[x] <= '9'))  ){
                                    // se esse if foi satisfeito, o termo não teve letra e foi só numeros
                                    // assumo ser um equ
                                    era_equ = 1; 
                                }
                            }

                            if(era_equ == 1){
                                fprintf(file_obj, "%s ", termo2);
                                era_equ = 0; 
                                simbolo_encontrado = 0;
                            }else{
                                printf("\nErro na linha %d: símbolo não encontrado!\nErro léxico.\n", k);
                                //exit(0);
                                era_equ = 0;
                            }

                        }

                        for(x=0; x<simbolos_existentes ; x++){
                            if( strcmp(termo3, tabela_de_simbolos[x][0]) == 0 ){
                                // achamos o símbolo
                                 
                                fprintf(file_obj, "%s ", tabela_de_simbolos[x][1]);
                                simbolo_encontrado = 1;

                            } 
                        }

                        if(simbolo_encontrado == 1){
                            simbolo_encontrado = 0;
                        }
                        else{

                            for(x=0; x< strlen(termo2) ; x++ ){
                                if(  ((termo2[x] >= '0') && (termo2[x] <= '9'))  ){
                                    // se esse if foi satisfeito, o termo não teve letra e foi só numeros
                                    // assumo ser um equ
                                    era_equ = 1; 
                                }
                            }

                            if(era_equ == 1){
                                fprintf(file_obj, "%s ", termo2);
                                era_equ = 0; 
                                simbolo_encontrado = 0;
                            }else{
                                printf("\nErro na linha %d: símbolo não encontrado!\nErro léxico.\n", k);
                                //exit(0);
                                era_equ = 0;
                            }

                        }
                        
                    } 
                }
                else{

                    printf("\nErro na linha %d: a quantidade de argumentos não está correta para esta operação!\nErro sintático.\n", k); 
                    //fclose(file_obj); 
                    //remove(nome_do_arquivo_obj);
                    //exit(0); 

                }
            
            }

            else{

                // é um section
                // se não for SECTION TEXT ou SECTION DATA, está errado

                if((strcmp(termo2, "TEXT") == 0) || (strcmp(termo2, "text") == 0)){
                    // código passando por um section 
                    passou_section_text = 1; 

                }
                else{
                    if((strcmp(termo2, "DATA") == 0) || (strcmp(termo2, "data") == 0)){
                        // código passando por um section data
                        passou_section_data = 1; 

                    }
                    else{
                        // esse section não existe
                        printf("\nErro na linha %d: esse tipo de SECTION não existe!\nErro sintático.\n", k); 
                        //fclose(file_obj); 
                        //remove(nome_do_arquivo_obj);
                        //exit(0);

                    }

                }
            }

        }
        
    }

    if(passou_do_stop == 0){

        // faltou um STOP no programa
        
        printf("\nErro: esse programa não teve um STOP!\nErro semântico.\n"); 
        fclose(file_obj); 
        remove(nome_do_arquivo_obj);
        exit(0);

    }

    if(passou_section_text == 0){
        
        // faltou um SECTION TEXT no programa
        
        printf("\nErro: esse programa não teve um SECTION TEXT!\nErro semântico.\n"); 
        fclose(file_obj); 
        remove(nome_do_arquivo_obj);
        exit(0);
    }
    else{
        if(passou_section_data == 0){
        
            // faltou um SECTION DATA no programa
        
            printf("\nErro: esse programa não teve um SECTION DATA!\nErro semântico.\n"); 
            fclose(file_obj); 
            remove(nome_do_arquivo_obj);
            exit(0);
        }
    }

    //------------------------------------------------------------------------------------------
    // Final da segunda passagem

    // Se libera a alocação dinâmica e se fecha arquivos

    free(termo1);
    free(termo2);
    free(termo3);
    free(termo4); 

    free(tabela_de_simbolos);

    free(nome_do_arquivo_obj); 
    free(nome_do_arquivo_pre);

    fclose(file_pre);
    fclose(file_obj); 
    
    printf("\nArquivo .obj gerado com sucesso!\n");

}