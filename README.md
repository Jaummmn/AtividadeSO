# Trabalho Prático de Sistemas Operacionais - Windows em C

## Participantes

- João Victor
- Matheus Cavalheiro
- Pedro Henrique
- Pedro Guaita

## Descrição

Este projeto tem como objetivo a criação de um sistema que manipula arquivos e diretórios utilizando APIs do Windows em C, como `CreateProcess()`, `CreateThread()`, `CreateFile()`, `ReadFile()` e `WriteFile()`. Ele demonstra a criação e sincronização de processos e threads, além de realizar operações de leitura e escrita de arquivos, tudo implementado em um programa interativo.

O programa principal oferece um menu para que o usuário possa:
1. Criar múltiplos arquivos e adicionar conteúdo a eles.
2. Combinar o conteúdo desses arquivos em um arquivo final.
3. Listar os arquivos criados em um diretório específico.

## Funcionalidades

- **Criação de Processos**: Embora o foco do programa esteja na manipulação de arquivos e threads, o conceito de processos foi explorado, e uma implementação inicial foi realizada. Contudo, optamos por focar em threads para otimizar o desempenho e simplificar a implementação.
  
- **Gerenciamento de Threads**: O programa cria uma thread para realizar as operações de criação e manipulação de arquivos, garantindo que as ações sejam realizadas de forma paralela e eficiente. A sincronização é feita utilizando a função `WaitForSingleObject()`, garantindo que o programa principal aguarde a finalização das tarefas executadas pelas threads antes de prosseguir.

- **Manipulação de Arquivos**: Utilizando as funções `CreateFile()`, `ReadFile()` e `WriteFile()`, o programa cria arquivos, escreve o conteúdo fornecido pelo usuário e os combina em um único arquivo final, armazenado em um diretório específico.

## Como Executar

1. Compile o código no Visual Studio ou em qualquer outro ambiente de desenvolvimento C compatível com o Windows.
2. Execute o programa, e um menu será exibido.
3. Escolha uma das opções para criar e manipular arquivos ou listar os arquivos já existentes no diretório.

## Vídeo Demonstrativo

Assista ao vídeo do programa funcionando: [Programa em funcionamento](https://youtu.be/QCv8Q4O_D5A)
