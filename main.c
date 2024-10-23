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
    // Definindo o caminho do diretorio a ser criado
    LPCSTR dirPath = "C:\\Users\\camargo\\Downloads\\PastaTeste";
    LPCSTR transcrisaoDirPath = "C:\\Users\\camargo\\Downloads\\PastaTeste\\conteudotranscrito";

    // Tenta criar o diretorio principal
    if (CreateDirectoryA(dirPath, NULL) || GetLastError() == ERROR_ALREADY_EXISTS) {
        printf("Diretorio criado com sucesso ou ja existe: %s\n", dirPath);

        // Tenta criar a nova subpasta
        if (CreateDirectoryA(transcrisaoDirPath, NULL) || GetLastError() == ERROR_ALREADY_EXISTS) {
            printf("Pasta para conteudo transcrito criada com sucesso ou ja existe: %s\n", transcrisaoDirPath);

            char entradaUsuarioConteudoArquivo[256];
            char entradaUsuarioNomeArquivo[100];
            int numeroArquivos;

            // Solicita ao usuario a quantidade de arquivos a serem criados
            printf("Escolha a quantidade de arquivos que deseja criar: ");
            if (scanf_s("%d", &numeroArquivos) != 1 || numeroArquivos <= 0) {
                printf("Entrada invalida para o numero de arquivos.\n");
                return 1;
            }
            (void)getchar(); // Ignora o retorno do getchar

            // Cria um arquivo para armazenar todo o conteudo combinado
            char arquivoFinal[256];
            sprintf_s(arquivoFinal, sizeof(arquivoFinal), "%s\\conteudo_combinado.txt", transcrisaoDirPath);

            HANDLE hFileFinal = CreateFileA(
                arquivoFinal,
                GENERIC_WRITE,
                0,
                NULL,
                CREATE_ALWAYS,
                FILE_ATTRIBUTE_NORMAL,
                NULL
            );

            if (hFileFinal == INVALID_HANDLE_VALUE) {
                printf("Erro ao criar o arquivo combinado. Codigo do erro: %lu\n", GetLastError());
                return 1;
            }

            for (int i = 0; i < numeroArquivos; i++) {
                printf("Digite o nome do arquivo %d (sem extensao): ", i + 1);
                if (fgets(entradaUsuarioNomeArquivo, sizeof(entradaUsuarioNomeArquivo), stdin) == NULL) {
                    printf("Erro ao ler o nome do arquivo.\n");
                    CloseHandle(hFileFinal);
                    return 1;
                }
                entradaUsuarioNomeArquivo[strcspn(entradaUsuarioNomeArquivo, "\n")] = '\0';

                char fileName[256];
                sprintf_s(fileName, sizeof(fileName), "%s\\%s.txt", dirPath, entradaUsuarioNomeArquivo);
                printf("Criando %s...\n", fileName);

                HANDLE hFile = CreateFileA(
                    fileName,
                    GENERIC_READ | GENERIC_WRITE,
                    0,
                    NULL,
                    CREATE_ALWAYS,
                    FILE_ATTRIBUTE_NORMAL,
                    NULL
                );

                if (hFile == INVALID_HANDLE_VALUE) {
                    printf("Erro ao criar o arquivo. Codigo do erro: %lu\n", GetLastError());
                    CloseHandle(hFileFinal);
                    return 1;
                }

                printf("Digite algo para escrever no arquivo %d: ", i + 1);
                if (fgets(entradaUsuarioConteudoArquivo, sizeof(entradaUsuarioConteudoArquivo), stdin) == NULL) {
                    printf("Erro ao ler o conteudo do arquivo.\n");
                    CloseHandle(hFile);
                    CloseHandle(hFileFinal);
                    return 1;
                }

                DWORD bytesWritten;
                BOOL result = WriteFile(
                    hFile,
                    entradaUsuarioConteudoArquivo,
                    strlen(entradaUsuarioConteudoArquivo),
                    &bytesWritten,
                    NULL
                );

                if (!result) {
                    printf("Erro ao escrever no arquivo.\n");
                    CloseHandle(hFile);
                    CloseHandle(hFileFinal);
                    return 1;
                }

                SetFilePointer(hFile, 0, NULL, FILE_BEGIN);

                char buffer[256];
                DWORD bytesRead;
                result = ReadFile(
                    hFile,
                    buffer,
                    sizeof(buffer) - 1,
                    &bytesRead,
                    NULL
                );

                if (!result) {
                    printf("Erro ao ler o arquivo. Codigo do erro: %lu\n", GetLastError());
                    CloseHandle(hFile);
                    CloseHandle(hFileFinal);
                    return 1;
                }

                buffer[bytesRead] = '\0';

                DWORD bytesWrittenFinal;
                result = WriteFile(
                    hFileFinal,
                    buffer,
                    bytesRead,
                    &bytesWrittenFinal,
                    NULL
                );

                if (!result) {
                    printf("Erro ao escrever no arquivo combinado. Codigo do erro: %lu\n", GetLastError());
                    CloseHandle(hFile);
                    CloseHandle(hFileFinal);
                    return 1;
                }

                printf("Dados lidos e escritos no arquivo combinado:\n%s\n", buffer);
                CloseHandle(hFile);
            }

            CloseHandle(hFileFinal);
        }
        else {
            printf("Falha ao criar a pasta 'conteudotranscrito'. Codigo do erro: %lu\n", GetLastError());
        }
    }
    else {
        printf("Falha ao criar o diretorio. Codigo do erro: %lu\n", GetLastError());
    }

    return 0;
}

void ShowMenu() {
    printf("Menu:\n");
    printf("1. Criar e manipular arquivos\n");
    printf("2. Listar arquivos na pasta\n");
    printf("3. Sair\n");
}

void ListFiles(const char* dirPath) {
    WIN32_FIND_DATAA findFileData;
    HANDLE hFind = FindFirstFileA(dirPath, &findFileData);
    if (hFind == INVALID_HANDLE_VALUE) {
        printf("Erro ao listar arquivos. Codigo do erro: %lu\n", GetLastError());
        return;
    }

    do {
        printf("%s\n", findFileData.cFileName);
    } while (FindNextFileA(hFind, &findFileData) != 0);
    FindClose(hFind);
}

int main() {
    int choice;

    while (1) {
        ShowMenu();
        printf("Escolha uma opcao: ");
        if (scanf_s("%d", &choice) != 1) {
            printf("Entrada invalida. Tente novamente.\n");
            (void)getchar(); // Ignora o retorno do getchar
            continue;
        }
        (void)getchar(); // Ignora o retorno do getchar

        switch (choice) {
        case 1: {
            HANDLE hThread;
            DWORD threadId;

            hThread = CreateThread(NULL, 0, FileOperations, NULL, 0, &threadId);

            if (hThread == NULL) {
                printf("Erro ao criar thread. Codigo do erro: %lu\n", GetLastError());
                return 1;
            }

            WaitForSingleObject(hThread, INFINITE);
            CloseHandle(hThread);
            break;
        }
        case 2: {
            const char* dirPath = "C:\\Users\\camargo\\Downloads\\PastaTeste\\*"; // O asterisco lista todos os arquivos
            ListFiles(dirPath);
            break;
        }
        case 3:
            printf("Saindo...\n");
            return 0;
        default:
            printf("Opcao invalida. Tente novamente.\n");
        }
    }
}
