/*
    Nome do arquivo: main.c
    Autores: João Victor, Pedro Guaita, Pedro Henrique e Matheus Cavalheiro.
    Disciplina: Sistemas Operacional.
    Descrição: O programa cria diretórios, manipula arquivos com conteúdo fornecido pelo usuário, e combina esses conteúdos em um arquivo final.
    Data de criação: 09/10/2024
    Última atualização: 11/10/2024

    O programa permite criar múltiplos arquivos, adicionar conteúdo a eles, 
    e combinar esse conteúdo em um único arquivo, utilizando threads e 
    operações de criação e leitura de arquivos no Windows.
*/
#include <windows.h>
#include <stdio.h>
#include <string.h>

// Funcao que sera executada pela thread criada
DWORD WINAPI FileOperations(LPVOID lpParam) {
    // Definindo o caminho do diretorio a ser criado (trocar USUARIO pelo nome correto)
    LPCSTR dirPath = "C:\\Users\\USUARIO\\Downloads\\PastaTeste";
    // Definindo o caminho da subpasta dentro do diretorio principal
    LPCSTR transcrisaoDirPath = "C:\\Users\\USUARIO\\Downloads\\PastaTeste\\conteudotranscrito";

    // Tenta criar o diretorio principal
    if (CreateDirectory(dirPath, NULL) || GetLastError() == ERROR_ALREADY_EXISTS) {
        printf("Diretorio criado com sucesso ou ja existe: %s\n", dirPath);

        // Tenta criar a nova subpasta
        if (CreateDirectory(transcrisaoDirPath, NULL) || GetLastError() == ERROR_ALREADY_EXISTS) {
            printf("Pasta para conteudo transcrito criada com sucesso ou ja existe: %s\n", transcrisaoDirPath);

            // Buffer para entrada do usuario
            char entradaUsuarioConteudoArquivo[256]; // Armazena o conteudo a ser inserido pelo usuario
            char entradaUsuarioNomeArquivo[100]; // Armazena o nome do arquivo fornecido pelo usuario
            int numeroArquivos; // Quantidade de arquivos que o usuario deseja criar

            // Solicita ao usuario a quantidade de arquivos a serem criados
            printf("Escolha a quantidade de arquivos que deseja criar: ");
            if (scanf("%d", &numeroArquivos) != 1 || numeroArquivos <= 0) {
                printf("Entrada invalida para o numero de arquivos.\n");
                return 1;
            }
            getchar(); // Consome o caractere de nova linha deixado pelo scanf

            // Cria um arquivo para armazenar todo o conteudo combinado na nova subpasta
            char arquivoFinal[256];
            sprintf(arquivoFinal, "%s\\conteudo_combinado.txt", transcrisaoDirPath);

            // Abre ou cria o arquivo combinado para escrita
            HANDLE hFileFinal = CreateFile(
                arquivoFinal,
                GENERIC_WRITE,
                0,
                NULL,
                CREATE_ALWAYS, // Cria um novo arquivo ou sobrescreve o existente
                FILE_ATTRIBUTE_NORMAL,
                NULL
            );

            // Verifica se o arquivo combinado foi criado com sucesso
            if (hFileFinal == INVALID_HANDLE_VALUE) {
                printf("Erro ao criar o arquivo combinado. Codigo do erro: %lu\n", GetLastError());
                return 1; // Encerra se houver erro
            }

            // Loop para criar multiplos arquivos conforme solicitado pelo usuario
            for (int i = 0; i < numeroArquivos; i++) {
                // Solicita o nome do arquivo ao usuario
                printf("Digite o nome do arquivo %d (sem extensao): ", i + 1);
                if (fgets(entradaUsuarioNomeArquivo, sizeof(entradaUsuarioNomeArquivo), stdin) == NULL) {
                    printf("Erro ao ler o nome do arquivo.\n");
                    CloseHandle(hFileFinal);
                    return 1;
                }
                // Remove o newline do final da string
                entradaUsuarioNomeArquivo[strcspn(entradaUsuarioNomeArquivo, "\n")] = '\0';

                // Monta o caminho completo do arquivo a ser criado
                char fileName[256];
                sprintf(fileName, "%s\\%s.txt", dirPath, entradaUsuarioNomeArquivo);

                printf("Criando %s...\n", fileName);

                // Cria ou abre o arquivo para leitura e escrita
                HANDLE hFile = CreateFile(
                    fileName,
                    GENERIC_READ | GENERIC_WRITE, // Permissao para ler e escrever
                    0,
                    NULL,
                    CREATE_ALWAYS, // Cria ou sobrescreve o arquivo
                    FILE_ATTRIBUTE_NORMAL,
                    NULL
                );

                // Verifica se o arquivo foi criado com sucesso
                if (hFile == INVALID_HANDLE_VALUE) {
                    printf("Erro ao criar o arquivo. Codigo do erro: %lu\n", GetLastError());
                    CloseHandle(hFileFinal); // Fecha o handle do arquivo combinado antes de sair
                    return 1; // Encerra se houver erro
                }

                // Solicita ao usuario que insira o conteudo a ser escrito no arquivo
                printf("Digite algo para escrever no arquivo %d: ", i + 1);
                if (fgets(entradaUsuarioConteudoArquivo, sizeof(entradaUsuarioConteudoArquivo), stdin) == NULL) {
                    printf("Erro ao ler o conteudo do arquivo.\n");
                    CloseHandle(hFile);
                    CloseHandle(hFileFinal);
                    return 1;
                }

                // Escreve o conteudo fornecido no arquivo
                DWORD bytesWritten;
                BOOL result = WriteFile(
                    hFile,                      // Handle do arquivo
                    entradaUsuarioConteudoArquivo, // Conteudo a ser escrito
                    strlen(entradaUsuarioConteudoArquivo), // Tamanho do conteudo
                    &bytesWritten,              // Numero de bytes escritos
                    NULL                        // Operacao sincrona
                );

                // Verifica se a escrita foi bem-sucedida
                if (!result) {
                    printf("Erro ao escrever no arquivo.\n");
                    CloseHandle(hFile);
                    CloseHandle(hFileFinal);
                    return 1; // Encerra se houver erro
                } else {
                    printf("Dados escritos com sucesso: %lu bytes\n", bytesWritten);

                    // Reposiciona o ponteiro para o inicio do arquivo para leitura
                    SetFilePointer(hFile, 0, NULL, FILE_BEGIN);

                    // Buffer para armazenar o conteudo lido
                    char buffer[256];
                    DWORD bytesRead;

                    // Le o conteudo do arquivo
                    result = ReadFile(
                        hFile,
                        buffer,
                        sizeof(buffer) - 1, // Deixa espaco para o terminador nulo
                        &bytesRead,
                        NULL // Operacao sincrona
                    );

                    // Verifica se a leitura foi bem-sucedida
                    if (!result) {
                        printf("Erro ao ler o arquivo. Codigo do erro: %lu\n", GetLastError());
                        CloseHandle(hFile);
                        CloseHandle(hFileFinal);
                        return 1; // Encerra se houver erro
                    }

                    // Adiciona o terminador nulo ao conteudo lido
                    buffer[bytesRead] = '\0';

                    // Escreve o conteudo lido no arquivo combinado
                    DWORD bytesWrittenFinal;
                    result = WriteFile(
                        hFileFinal, // Handle do arquivo combinado
                        buffer,     // Dados lidos
                        bytesRead,  // Numero de bytes lidos
                        &bytesWrittenFinal,
                        NULL        // Operacao sincrona
                    );

                    // Verifica se a escrita no arquivo combinado foi bem-sucedida
                    if (!result) {
                        printf("Erro ao escrever no arquivo combinado. Codigo do erro: %lu\n", GetLastError());
                        CloseHandle(hFile);
                        CloseHandle(hFileFinal);
                        return 1; // Encerra se houver erro
                    }

                    printf("Dados lidos e escritos no arquivo combinado:\n%s\n", buffer);
                }

                // Fecha o handle do arquivo individual apos cada iteracao
                CloseHandle(hFile);
            }

            // Fecha o arquivo combinado apos todas as iteracoes
            CloseHandle(hFileFinal);

        } else {
            // Exibe erro se nao for possivel criar a subpasta
            printf("Falha ao criar a pasta 'conteudotranscrito'. Codigo do erro: %lu\n", GetLastError());
        }
    } else {
        // Exibe erro se nao for possivel criar o diretorio principal
        printf("Falha ao criar o diretorio. Codigo do erro: %lu\n", GetLastError());
    }

    return 0;
}

int main() {
    HANDLE hThread; // Handle para a thread
    DWORD threadId; // ID da thread

    // Cria a thread que executa a funcao FileOperations
    hThread = CreateThread(NULL, 0, FileOperations, NULL, 0, &threadId);

    // Verifica se a thread foi criada com sucesso
    if (hThread == NULL) {
        printf("Erro ao criar thread. Codigo do erro: %lu\n", GetLastError());
        return 1; // Encerra o programa se houver erro
    }

    // Aguarda a conclusao da thread
    WaitForSingleObject(hThread, INFINITE);

    // Fecha o handle da thread
    CloseHandle(hThread);

    // Inicializa estruturas para criar um processo filho
    STARTUPINFO si;
    PROCESS_INFORMATION pi;
    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    ZeroMemory(&pi, sizeof(pi));

    // Define o comando que sera executado pelo processo filho
    // A string deve ser modificavel, por isso usamos uma string de caracteres
    char command[] = "cmd.exe /c tree C:\\Users\\USUARIO\\Downloads\\PastaTeste /f";

    // Cria o processo filho para executar o comando
    if (!CreateProcess(
            NULL,           // Nenhum modulo especificado
            command,        // Linha de comando a ser executada
            NULL,           // Atributos de processo
            NULL,           // Atributos de thread
            FALSE,          // Nao herda handles
            0,              // Sem flags de criacao
            NULL,           // Usa o bloco de ambiente do pai
            NULL,           // Usa o diretorio atual do pai
            &si,            // Ponteiro para STARTUPINFO
            &pi             // Ponteiro para PROCESS_INFORMATION
        )) {
        printf("Erro ao criar o processo. Codigo do erro: %lu\n", GetLastError());
        return 1; // Encerra o programa se houver erro
    }

    // Aguarda a conclusao do processo filho
    WaitForSingleObject(pi.hProcess, INFINITE);

    // Fecha os handles do processo e da thread
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);

    return 0; // Encerra a funcao main
}
