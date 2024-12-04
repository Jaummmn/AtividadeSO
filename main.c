/*
    Autores: Pedro Guaita, Pedro Henrique, Matheus Cavalheiro e João Victor.
    Disciplina: Linguagem de programação
    Descrição: O programa é um sistema de cadastro e controle de alunos.
    Data de criação: 07/10/2024
    Última atualização: 20/10/2024

    O programa permite que o usuário cadastre novos alunos no sistema,
    permite a listagem de todos os alunos cadastrados e a busca por alunos
    específicos. Neste programa também é possível salvar os dados armazenados.

*/

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <locale.h>
#include <stdbool.h>
#include <dirent.h>

#define controle 100  // Define a constante para o controle de alunos
#define controleLogin 4  // Define a constante para o controle de login
// Struct para armazenar os dados dos alunos
typedef struct
{
    char nomeAluno[50];
    int idadeAluno;
    char sexo;
    char universidade[50];
    char curso[50];
    int semestre;
    char documento[20];
    char email[30];
    char telefone[20];
    int matricula;
} str_alunos;

typedef struct
{
    char nomeUsuario[50];
    char senhaUsuario[50];
} str_login;

str_alunos Alunos[controle]; // Array para armazenar os alunos
int qtdAlunos = 0; // Contador de alunos cadastrados
str_login Usuario[controleLogin];
int qtdLogin = 0;
// Função para limpar o buffer de entrada
void limparBufferEntrada()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Função para cadastrar novos alunos
void cadastrarAluno()
{
    int novosAlunos = 0;

    printf("\n");
    printf("Quantos alunos novos serão cadastrados: ");
    scanf("%d", &novosAlunos);
    limparBufferEntrada();

    // Verifica se o número de alunos excede o limite
    if (qtdAlunos + novosAlunos > controle)
    {
        printf("\nErro: Número de alunos excede o limite do array.\n");
        return;
    }

    // Loop para cadastrar os alunos
    for (int i = 0; i < novosAlunos; i++)
    {
        do
        {
            printf("\nDigite o nome do Aluno: ");
            fgets(Alunos[qtdAlunos].nomeAluno, 50, stdin);
            Alunos[qtdAlunos].nomeAluno[strcspn(Alunos[qtdAlunos].nomeAluno, "\n")] = '\0';

            // Verifica se o nome do aluno não está vazio
            if (strlen(Alunos[qtdAlunos].nomeAluno) == 0)
            {
                printf("Aluno não pode estar vazio. Digite novamente.\n");
            }

        } while (strlen(Alunos[qtdAlunos].nomeAluno) == 0);

        do
        {
            printf("Digite a idade do Aluno: ");
            scanf("%d", &Alunos[qtdAlunos].idadeAluno);
            limparBufferEntrada();

            // Verifica se a idade está dentro do intervalo permitido
            if (Alunos[qtdAlunos].idadeAluno < 16 || Alunos[qtdAlunos].idadeAluno > 120)
            {
                printf("Idade inválida. Digite uma idade entre 16 e 120.\n");
            }

        } while (Alunos[qtdAlunos].idadeAluno < 16 || Alunos[qtdAlunos].idadeAluno > 120);

        do
        {
            printf("Digite o sexo do Aluno com f ou m: ");
            scanf(" %c", &Alunos[qtdAlunos].sexo);
            limparBufferEntrada();

            // Verifica se o sexo informado é válido
            if (Alunos[qtdAlunos].sexo != 'f' && Alunos[qtdAlunos].sexo != 'm')
            {
                printf("Sexo inválido. Digite 'f' para feminino ou 'm' para masculino.\n");
            }

        } while (Alunos[qtdAlunos].sexo != 'f' && Alunos[qtdAlunos].sexo != 'm');

        do
        {
            printf("Digite a universidade do Aluno: ");
            fgets(Alunos[qtdAlunos].universidade, 50, stdin);
            Alunos[qtdAlunos].universidade[strcspn(Alunos[qtdAlunos].universidade, "\n")] = '\0';

            // Verifica se a universidade não está vazia
            if (strlen(Alunos[qtdAlunos].universidade) == 0)
            {
                printf("Universidade não pode estar vazia. Digite novamente.\n");
            }

        } while (strlen(Alunos[qtdAlunos].universidade) == 0);

        do
        {
            printf("Digite o curso do Aluno: ");
            fgets(Alunos[qtdAlunos].curso, 50, stdin);
            Alunos[qtdAlunos].curso[strcspn(Alunos[qtdAlunos].curso, "\n")] = '\0';

            // Verifica se o curso não está vazio
            if (strlen(Alunos[qtdAlunos].curso) == 0)
            {
                printf("Curso não pode estar vazio. Digite novamente.\n");
            }

        } while (strlen(Alunos[qtdAlunos].curso) == 0);

        do
        {
            printf("Digite apenas o número do semestre do Aluno: ");
            scanf("%d", &Alunos[qtdAlunos].semestre);
            limparBufferEntrada();

            // Verifica se o semestre está dentro do intervalo permitido
            if (Alunos[qtdAlunos].semestre < 1 || Alunos[qtdAlunos].semestre > 10)
            {
                printf("Semestre inválido. Digite um semestre entre 1 e 10.\n");
            }

        } while (Alunos[qtdAlunos].semestre < 1 || Alunos[qtdAlunos].semestre > 10);

        do
        {
            printf("Digite o documento do Aluno: ");
            fgets(Alunos[qtdAlunos].documento, 20, stdin);
            Alunos[qtdAlunos].documento[strcspn(Alunos[qtdAlunos].documento, "\n")] = '\0';

            // Verifica se o documento não está vazio
            if (strlen(Alunos[qtdAlunos].documento) == 0)
            {
                printf("Documento não pode estar vazio. Digite novamente.\n");
            }

        } while (strlen(Alunos[qtdAlunos].documento) == 0);

        do
        {
            printf("Digite o email do Aluno: ");
            fgets(Alunos[qtdAlunos].email, 30, stdin);
            Alunos[qtdAlunos].email[strcspn(Alunos[qtdAlunos].email, "\n")] = '\0';

            // Verifica se o email não está vazio
            if (strlen(Alunos[qtdAlunos].email) == 0)
            {
                printf("Email não pode estar vazio. Digite novamente.\n");
            }

        } while (strlen(Alunos[qtdAlunos].email) == 0);

        do
        {
            printf("Digite o telefone do Aluno: ");
            fgets(Alunos[qtdAlunos].telefone, 20, stdin);
            Alunos[qtdAlunos].telefone[strcspn(Alunos[qtdAlunos].telefone, "\n")] = '\0';

            // Verifica se o telefone não está vazio
            if (strlen(Alunos[qtdAlunos].telefone) == 0)
            {
                printf("Telefone não pode estar vazio. Digite novamente.\n");
            }

        } while (strlen(Alunos[qtdAlunos].telefone) == 0);

        do
        {
            printf("Digite os números da matrícula do Aluno: ");
            scanf("%d", &Alunos[qtdAlunos].matricula);
            limparBufferEntrada();

            int matriculaExiste = 0;
            // Verifica se a matrícula já existe
            for (int j = 0; j < qtdAlunos; j++)
            {
                if (Alunos[j].matricula == Alunos[qtdAlunos].matricula)
                {
                    matriculaExiste = 1;
                    printf("Matrícula já existente. Digite outra matrícula.\n");
                    break;
                }
            }

            if (!matriculaExiste)
            {
                break; // Saia do loop se a matrícula não existir
            }

        } while (1);

        qtdAlunos++;
        printf("\nAluno cadastrado com sucesso! \n");
    }
}

// Função para listar todos os alunos cadastrados
void listarAlunos()
{
    if (qtdAlunos == 0)
    {
        printf("Nenhum aluno cadastrado.\n");
        return;
    }

    printf("\nLista de Alunos:\n");

    // Loop para imprimir os dados de cada aluno
    for (int i = 0; i < qtdAlunos; i++)
    {
        printf("Nome: %s\n", Alunos[i].nomeAluno);
        printf("Idade: %d\n", Alunos[i].idadeAluno);
        printf("Sexo: %c\n", Alunos[i].sexo);
        printf("Universidade: %s\n", Alunos[i].universidade);
        printf("Curso: %s\n", Alunos[i].curso);
        printf("Semestre: %d\n", Alunos[i].semestre);
        printf("Documento: %s\n", Alunos[i].documento);
        printf("Email: %s\n", Alunos[i].email);
        printf("Telefone: %s\n", Alunos[i].telefone);
        printf("Matrícula: %d\n\n", Alunos[i].matricula);
    }
}

// Função para buscar um aluno pela matrícula
void buscarAluno()
{
    int matriculaBusca; // Variável para armazenar a matrícula a ser buscada
    int encontrado = 0; // Flag para verificar se o aluno foi encontrado

    printf("\nDigite a matrícula do aluno que deseja buscar:\n");
    scanf("%d", &matriculaBusca);
    limparBufferEntrada();

    // Loop para procurar o aluno pela matrícula
    for (int i = 0; i < qtdAlunos; i++)
    {
        if (Alunos[i].matricula == matriculaBusca)
        {
            // Aluno encontrado, exibe os dados
            printf("Aluno encontrado:\n");
            printf("Nome: %s\n", Alunos[i].nomeAluno);
            printf("Idade: %d\n", Alunos[i].idadeAluno);
            printf("Sexo: %c\n", Alunos[i].sexo);
            printf("Universidade: %s\n", Alunos[i].universidade);
            printf("Curso: %s\n", Alunos[i].curso);
            printf("Semestre: %d\n", Alunos[i].semestre);
            printf("Documento: %s\n", Alunos[i].documento);
            printf("Email: %s\n", Alunos[i].email);
            printf("Telefone: %s\n", Alunos[i].telefone);
            printf("Matrícula: %d\n\n", Alunos[i].matricula);
            encontrado = 1; // Define a flag como encontrada
            break; // Sai do loop se o aluno foi encontrado
        }
    }

    // Se não encontrou nenhum aluno
    if (!encontrado)
    {
        printf("Nenhum aluno encontrado com a matrícula %d.\n", matriculaBusca);
    }
}

// Função para carregar os dados dos alunos a partir de um arquivo
void carregarAlunos()
{
    FILE *arquivo; // Ponteiro para o arquivo
    arquivo = fopen("Alunos.txt", "r"); // Abre o arquivo para leitura

    if (arquivo == NULL)
    {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    // Loop para ler os dados do arquivo
    while (fscanf(arquivo, "%[^;];%d;%c;%[^;];%[^;];%d;%[^;];%[^;];%[^;];%d\n",
            Alunos[qtdAlunos].nomeAluno,
            &Alunos[qtdAlunos].idadeAluno,
            &Alunos[qtdAlunos].sexo,
            Alunos[qtdAlunos].universidade,
            Alunos[qtdAlunos].curso,
            &Alunos[qtdAlunos].semestre,
            Alunos[qtdAlunos].documento,
            Alunos[qtdAlunos].email,
            Alunos[qtdAlunos].telefone,
            &Alunos[qtdAlunos].matricula) != EOF) {
        qtdAlunos++; // Incrementa a quantidade de alunos lidos
    }

    fclose(arquivo); // Fecha o arquivo
    printf("Alunos carregados com sucesso!\n");
}

// Função para salvar os dados dos alunos
void salvarAlunos()
{
    FILE *arquivo;
    arquivo = fopen("Alunos.txt", "w"); // w, para abrir para escrita.

    if (arquivo == NULL)
    {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    // Loop para escrever os dados dos alunos no arquivo
    for (int i = 0; i < qtdAlunos; i++)
    {
        fprintf(arquivo, "%s;%d;%c;%s;%s;%d;%s;%s;%s;%d\n",
            Alunos[i].nomeAluno,
            Alunos[i].idadeAluno,
            Alunos[i].sexo,
            Alunos[i].universidade,
            Alunos[i].curso,
            Alunos[i].semestre,
            Alunos[i].documento,
            Alunos[i].email,
            Alunos[i].telefone,
            Alunos[i].matricula);
    }

    fclose(arquivo); // Fecha o arquivo
    printf("Dados dos alunos salvos!\n");
}
int contarArquivosUsuarios() {
    int contador = 0;
    DIR *dir;
    struct dirent *ent;

    // Abre o diretório atual
    if ((dir = opendir(".")) != NULL) {
        // Lê todos os arquivos no diretório
        while ((ent = readdir(dir)) != NULL) {
            // Verifica se o nome do arquivo termina com .txt
            if (strstr(ent->d_name, ".txt") != NULL) {
                contador++;
            }
        }
        closedir(dir);
    } else {
        printf("Erro ao abrir o diretório.\n");
    }

    return contador;
}


int CadastroUsuario() {
    int novosUsuarios = 0;

    printf("\nQuantos usuários serão cadastrados: ");
    scanf("%d", &novosUsuarios);
    limparBufferEntrada();

    int arquivosExistentes = contarArquivosUsuarios();

    if (arquivosExistentes >=  controleLogin) {
        printf("\nErro: Número de usuários excede o limite permitido de %d arquivos.\n",  controleLogin);
        return 0;
    }


    // Loop para cadastrar os Usuarios
    for (int i = 0; i < novosUsuarios; i++) {
        do {
            printf("\nDigite o nome do Usuário: ");
            fgets(Usuario[qtdLogin].nomeUsuario, sizeof(Usuario[qtdLogin].nomeUsuario), stdin);
            Usuario[qtdLogin].nomeUsuario[strcspn(Usuario[qtdLogin].nomeUsuario, "\n")] = '\0';

            // Verifica se o nome do Usuario não está vazio
            if (strlen(Usuario[qtdLogin].nomeUsuario) == 0) {
                printf("Usuário não pode estar vazio. Digite novamente.\n");
            }

        } while (strlen(Usuario[qtdLogin].nomeUsuario) == 0);

        do {
            printf("Digite a senha do usuario (min 8 caracteres): ");
            fgets(Usuario[qtdLogin].senhaUsuario, sizeof(Usuario[qtdLogin].senhaUsuario), stdin);
            Usuario[qtdLogin].senhaUsuario[strcspn(Usuario[qtdLogin].senhaUsuario, "\n")] = '\0';

            // Verifica se a senha está dentro do intervalo permitido
            if (strlen(Usuario[qtdLogin].senhaUsuario) < 8) {
                printf("Senha muito curta. Deve ter pelo menos 8 caracteres.\n");
            }

        } while (strlen(Usuario[qtdLogin].senhaUsuario) < 8);

        char nomeArquivo[60];
        snprintf(nomeArquivo, sizeof(nomeArquivo), "%s.txt", Usuario[qtdLogin].nomeUsuario); // Nome do arquivo baseado no nome do usuário

        FILE *arquivo = fopen(nomeArquivo, "w"); // Abre o arquivo em modo de escrita
        if (arquivo != NULL) {
            fprintf(arquivo, "Nome: %s\nSenha: %s\n", Usuario[qtdLogin].nomeUsuario, Usuario[qtdLogin].senhaUsuario);
            fclose(arquivo); // Fecha o arquivo após escrever
            printf("Arquivo '%s' criado com sucesso!\n", nomeArquivo);
        } else {
            printf("Erro ao criar o arquivo '%s'.\n", nomeArquivo);
        }

        qtdLogin++; // Incrementa o número de usuários cadastrados
    }

    return 0;
}
bool LoginUsuario() {
    char nome[50];
    char senha[50];

    printf("\nDigite seu nome de usuário: ");
    fgets(nome, sizeof(nome), stdin);
    nome[strcspn(nome, "\n")] = '\0'; // Remove a nova linha

    printf("Digite sua senha: ");
    fgets(senha, sizeof(senha), stdin);
    senha[strcspn(senha, "\n")] = '\0'; // Remove a nova linha

    // Monta o nome do arquivo baseado no nome do usuário
    char nomeArquivo[60];
    snprintf(nomeArquivo, sizeof(nomeArquivo), "%s.txt", nome);

    FILE *arquivo = fopen(nomeArquivo, "r"); // Abre o arquivo em modo de leitura
    if (arquivo == NULL) {
        printf("Usuário não encontrado!\n");
        return false; // Retorna false se o usuário não for encontrado
    }

    char linha[100];
    char usuarioArmazenado[50];
    char senhaArmazenada[50];

    // Lê as informações do arquivo
    fgets(linha, sizeof(linha), arquivo); // Lê a linha com o nome
    sscanf(linha, "Nome: %49[^\n]", usuarioArmazenado); // Extrai o nome armazenado

    fgets(linha, sizeof(linha), arquivo); // Lê a linha com a senha
    sscanf(linha, "Senha: %49[^\n]", senhaArmazenada); // Extrai a senha armazenada

    fclose(arquivo); // Fecha o arquivo após leitura

    // Valida as credenciais
    if (strcmp(usuarioArmazenado, nome) == 0 && strcmp(senhaArmazenada, senha) == 0) {
        printf("Login bem-sucedido! Bem-vindo(a), %s!\n", usuarioArmazenado);
        return true; // Retorna true se o login for bem-sucedido
    } else {
        printf("Credenciais inválidas. Tente novamente.\n");
        return false; // Retorna false se as credenciais forem inválidas
    }
}

bool Login() {
    printf("Área de Login\n");

    int tentativas = 3; // Número máximo de tentativas
    while (tentativas > 0) {
        if (LoginUsuario()) {
            return true; // Retorna true se o login for bem-sucedido
        }
        tentativas--;
        printf("Você ainda tem %d tentativas.\n", tentativas);
    }

    printf("Número máximo de tentativas atingido. Acesso negado.\n");
    return false; // Retorna false se todas as tentativas falharem
}


// Função principal do programa
int main()
{
    setlocale(LC_ALL, "Portuguese"); // Configura a localidade para português

    int opcaoMenu; // Variável para armazenar a opção do menu
    do
    {
        printf("\n*** Login ***\n");

        printf("\n Escolha uma das opções:\n\n");
        printf("0- Fechar programa\n");
        printf("1- Cadastro de Usuario\n");
        printf("2- Realizar Login\n");


        scanf("%d", &opcaoMenu);
        limparBufferEntrada();

        // Executa a opção escolhida
        switch (opcaoMenu)
        {
             case 0:
                printf("Sistema encerrado.\n");
                return 0;

            case 1:
                CadastroUsuario();
                break;

            case 2:
               if(Login()){
            int opcao;
            do
            {
                printf("\n*** Sistema de Gerenciamento de Alunos ***\n");

                printf("\n Escolha uma das opções:\n\n");
                printf("0- Sair\n");
                printf("1- Cadastrar Alunos\n");
                printf("2- Listar Alunos\n");
                printf("3- Buscar Aluno por Matrícula\n");
                printf("4- Carregar Dados dos Alunos\n");
                printf("5- Salvar Dados dos Alunos\n");

                scanf("%d", &opcao);
                limparBufferEntrada();

                // Executa a opção escolhida
                switch (opcao)
                {
                     case 0:
                        printf("Sistema encerrado.\n");
                        return 0;

                    case 1:
                        cadastrarAluno();
                        break;

                    case 2:
                        listarAlunos();
                        break;

                    case 3:
                        buscarAluno();
                        break;

                    case 4:
                        carregarAlunos();
                        break;

                    case 5:
                        salvarAlunos();
                        return 0;

                    default:

                        printf("Opção inválida. Tente novamente.\n");
                        break;
                }
    } while (opcao != 0);

                break;
            default:

                printf("Opção inválida. Tente novamente.\n");
                break;
               }
        }
    } while (opcaoMenu != 0);
    return 0; // Encerra o programa
}







/*             *** Identificação das variáveis de entrada e saída do algoritmo ***

    Variáveis de entrada:
        novosAlunos: Quantidade de alunos a serem cadastrados.
        Alunos[qtdAlunos].nomeAluno: Nome do aluno.
        Alunos[qtdAlunos].idadeAluno: Idade do aluno.
        Alunos[qtdAlunos].sexo: Sexo do aluno.
        Alunos[qtdAlunos].universidade: Nome da universidade.
        Alunos[qtdAlunos].curso: Nome do curso.
        Alunos[qtdAlunos].semestre: Semestre em que o aluno está matriculado.
        Alunos[qtdAlunos].documento: Documento do aluno.
        Alunos[qtdAlunos].email: E-mail do aluno.
        Alunos[qtdAlunos].telefone: Telefone do aluno.
        Alunos[qtdAlunos].matricula: Matrícula do aluno.
        matriculaBusca: Matrícula do aluno a ser buscado.

    Variáveis de saída:
        Alunos[qtdAlunos]: Armazena todos os dados dos alunos cadastrados.
        Mensagens que indicam o sucesso ou falha de operações, como cadastro de aluno, busca por matrícula, etc.
        qtdAlunos: Contador que armazena o número de alunos cadastrados.

Explicação do uso de cada variável:

    controle: Define o limite máximo de alunos que o sistema pode armazenar. (100 alunos)
    str_alunos: Estrutura que armazena os dados de cada aluno, como nome, idade, sexo, universidade, curso, etc.
    Alunos[controle]: Array que armazena todos os alunos cadastrados no sistema. O tamanho do array é determinado pela constante controle.
    qtdAlunos: Variável de controle que armazena a quantidade de alunos cadastrados no sistema.
    novosAlunos: Armazena o número de alunos a serem cadastrados de uma vez.
    matriculaBusca: Variável utilizada para armazenar a matrícula do aluno que o usuário deseja buscar.
    encontrado: Variável booleana (1 ou 0) que indica se o aluno foi encontrado ou não ao buscar pelo número da matrícula.
*/