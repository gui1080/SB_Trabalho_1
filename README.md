# Trabalho 1 de Software Básico: Montador de Assembly de Duas Passagens

Aluno: Guilherme Braga Pinto

Matrícula: 17/0162290

Professor: Bruno Macchiavello

UnB, 2020/01

Prazo de entrega: 09/10/2020

Escolha de implementação: detectar erros. 

# Instruções de Uso

O arquivo a ser utilizado deve se localizado na pasta src. Os outputs também serão criados nesta pasta.

Para compilar o programa, rode "make" dentro da pasta source.

Para rodar o programa, rode "./main" seguido de  um espaço com "-o" (para ter como um retorno o arquivo ".obj", tendo como entrada um arquivo ".asm") ou "-p" (para ter como um retorno o arquivo ".pre", tendo como entrada um arquivo ".pre"), e então seguido de um espaço e o nome do seu arquivo. 

Exemplos: "./main -p bin.asm" e "./main -o bin.pre"

Para então limpar os arquivos compilados, pode ser utilizado o comando "make clean"

# Observações

Programa feito no Ubuntu 18.04

Makefile baseado em: https://www.cs.colby.edu/maxwell/courses/tutorials/maketutor/ 

Link para o Github do trabalho: https://github.com/gui1080/SB_Trabalho_1

# Estrutura dos arquivos

SB_Trabalho1

├── _include

├── _src

    ├── _Casos de Teste

    └── _obj

Na pasta include estão os arquivos .h

Na pasta src, se encontram os arquivos .c, .asm, .pre e .obj

Também na pasta src, se encontram as pastas obj (para onde vão os arquivos objeto) e a pasta Casos de Teste (com alguns programas que testam a detecção de erros)

# Demonstração

A seguinte demo vem pronta junto deste trabalho:

Recomenda-se rodar um "make clean" seguido de um "make" no início, na pasta src (atenção para detectar se a pasta obj está presente).

Então executa-se:

> ./main -p bin.asm

> ./main -o bin.pre

E assim se chega no código objeto/pré-processado desejado. 