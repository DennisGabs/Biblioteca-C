#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// Estrutura de livros
typedef struct {
    int id;
    char nome[150];
    char ISBN[13];
    int qtd;
    int qtd_emprestado;
} Livro;


// registra os livros no arquivo txt 
void registrar(Livro *livro) {
	// abre o arquivo em modo de atualizacao
    FILE *file = fopen("./registros.txt", "a");
    // escreve o livro no arquivo.
    fprintf(file, "========= Livro =========\n");
    fprintf(file, "ID: %d\n", livro->id);
    fprintf(file, "Nome: %s\n", livro->nome);
    fprintf(file, "ISBN: %s\n", livro->ISBN);
    fprintf(file, "Quantidade Disponivel: %d\n", livro->qtd);
    fprintf(file, "Quantidade Emprestada: %d\n", livro->qtd_emprestado);
    fprintf(file, "===========================\n");
    fclose(file); // fecha arquivo
}

// Em caso de emprestimo ou de devolucao o arquivo é refeito
void refazerRegistros(Livro livros[], int posicoes){
	// abre o arquivo em modo de escrita
	FILE *file = fopen("./registros.txt", "w");
	int i;
	// Os livros são reescritos no arquivo.
	for(i = 0; i < posicoes; i++){
		fprintf(file, "========= Livro =========\n");
    	fprintf(file, "ID: %d\n", livros[i].id);
    	fprintf(file, "Nome: %s\n", livros[i].nome);
    	fprintf(file, "ISBN: %s\n", livros[i].ISBN);
    	fprintf(file, "Quantidade Disponivel: %d\n", livros[i].qtd);
    	fprintf(file, "Quantidade Emprestada: %d\n", livros[i].qtd_emprestado);
    	fprintf(file, "===========================\n");
	}
	fclose(file); // fecha arquivo
}
 // Salva os livros no arquivo binario para futura leitura da aplicacao
void salvarLivros(Livro livros[], int posicao) {
	// o arquivo binario é aberto em modo de escrita
    FILE *file = fopen("./livros.bin", "wb"); 
    // é feito a escrita dos dados no arquivo binario
    fwrite(livros, sizeof(Livro), posicao, file);
    fclose(file); // fecha o arquivo
    refazerRegistros(livros, posicao); // refaz os registros no txt
}

// Carrega os dados guardados no arquivo e coloca no buffer
void carregarLivros(Livro livros[], int *posicao) {
    FILE *file = fopen("./livros.bin", "rb"); // Abre o arquivo
    if (file != NULL) { // verifica se o arquivo foi aberto
    	// enquanto houver livros, ele coloca no buffer, de 1 a 1
        while (fread(&livros[*posicao], sizeof(Livro), 1, file)) {
            (*posicao)++; // incrementa o valor da posicao atual
        }
        fclose(file); // fecha o arquivo.
    }
}

// cadstro de livros
void cadastrarLivro(Livro livros[], int *posicao) {
    Livro livro;
    fflush(stdin); // limpa a entrada de dados
    printf("======== Cadastrar Livro ========\n");
    printf("NOME: ");
    fgets(livro.nome, sizeof(livro.nome), stdin);
    livro.nome[strcspn(livro.nome, "\n")] = 0; // retira a entrada do enter

    printf("ISBN: ");
    fgets(livro.ISBN, sizeof(livro.ISBN), stdin);
    livro.ISBN[strcspn(livro.ISBN, "\n")] = 0; // retira a entrada do enter

    printf("Quantidade: ");
    scanf("%d", &livro.qtd);

    livro.qtd_emprestado = 0; // por padrao um livro nao possui emprestimos
    livro.id = (*posicao) + 1; // o id do livro recebe a posicao atual mais um
    livros[*posicao] = livro; // o livro criado é colocado dentro do array de livros
    (*posicao)++; // posicao é incrementada

    registrar(&livros[*posicao - 1]); // é feito o registro do livro no arquivo txt
    salvarLivros(livros, *posicao); // Salva os livros no arquivo binario
    printf("Livro %s cadastrado com sucesso!!!\n", livro.nome);
}

void emprestarLivro(Livro livros[], int posicao) {
    char isbn[12];
    printf("Informe o ISBN do livro que deseja emprestar: ");
    fflush(stdin);
    fgets(isbn, sizeof(isbn), stdin);
    isbn[strcspn(isbn, "\n")] = 0;
	int i;
	// procura pelo livro com o ISBN digitado e faz o emprestimo 
	// caso teha acima 0 quantidades disponiveis
    for (i = 0; i < posicao; i++) {
        if (strcmp(livros[i].ISBN, isbn) == 0) {
            if (livros[i].qtd > 0) {
                livros[i].qtd--; // diminui a quantidade de disponiveis
                livros[i].qtd_emprestado++; // incrementa a quantidade de emprestado
                printf("Livro %s emprestado com sucesso!\n", livros[i].nome);
                salvarLivros(livros, posicao);
                return;
            } else {
                printf("Nao ha mais exemplares disponiveis para emprestimo.\n");
                return; 
            }
        }
    }
    printf("Livro nao encontrado!\n");
}

// semelhante a funcao de emprestar, so que faz o reverso
void devolverLivro(Livro livros[], int posicao) {
    char isbn[12];
    printf("Informe o ISBN do livro que deseja devolver: ");
    fflush(stdin);
    fgets(isbn, sizeof(isbn), stdin);
    isbn[strcspn(isbn, "\n")] = 0;
	int i;
    for (i = 0; i < posicao; i++) {
        if (strcmp(livros[i].ISBN, isbn) == 0) {
            if (livros[i].qtd_emprestado > 0) {
                livros[i].qtd++; // adiciona a quantia de disponiveis
                livros[i].qtd_emprestado--; // remove uma quantidade de emprestados
                printf("Livro %s devolvido com sucesso!\n", livros[i].nome);
                salvarLivros(livros, posicao);
                return;
            } else {
                printf("Nenhum exemplar emprestado deste livro.\n");
                return;
            }
        }
    }
    printf("Livro nao encontrado!\n");
}

// procura por um livro dado seu ISBN
void pesquisarLivro(Livro livros[], int posicao) {
    char isbn[12];
    printf("Informe o ISBN do livro para pesquisa: ");
    fflush(stdin);
    fgets(isbn, sizeof(isbn), stdin);
    isbn[strcspn(isbn, "\n")] = 0;
	int i;
    for (i = 0; i < posicao; i++) {
    	// Se encontrar o livro, eh exibido na tela
        if (strcmp(livros[i].ISBN, isbn) == 0) {
            printf("Livro encontrado!\n");
            printf("ID: %d\n", livros[i].id);
            printf("Nome: %s\n", livros[i].nome);
            printf("Quantidade dispon?vel: %d\n", livros[i].qtd);
            printf("Quantidade emprestada: %d\n", livros[i].qtd_emprestado);
            return;
        }
    }
    printf("Livro nao encontrado!\n");
}

// exie o menu
void menu() {
    printf("======= MENU =======\n");
    printf("1 - CADASTRAR Livro\n");
    printf("2 - EMPRESTAR Livro\n");
    printf("3 - DEVOLVER Livro\n");
    printf("4 - PESQUISAR Livro\n");
    printf("5 - LER REGISTROS\n");
    printf("0 - SAIR\n");
}

// faz uma leitura do arquivo txt
void lerRegistros(){
	// abre o arquivo em modo de leitura
	FILE *file = fopen("./registros.txt", "r");
	char linha[150];  
	system("cls");
	printf("====== Conteudo do Arquivo ======\n");
	while(fgets(linha, sizeof(linha), file)){
		printf("%s", linha); // mostra a leitura do arquivo, linha a linha
	}
	fclose(file); // fecha o arquivo
	printf("==============================\n");
}

void limpaTerminal(){
	system("pause");
	system("cls");
}

// funcao das opcoes de menu
int opcaoMenu(Livro livros[], int *posicao) {
    menu(); // Chama sempre o menu
    int op;
    printf("Informe uma opcao --> ");
    scanf("%d", &op);
    switch(op) {
        case 1:
            cadastrarLivro(livros, posicao);
            limpaTerminal();
			break;
        case 2:
            emprestarLivro(livros, *posicao);
            limpaTerminal();
			break;
        case 3:
            devolverLivro(livros, *posicao);
            limpaTerminal();
            break;
        case 4:
            pesquisarLivro(livros, *posicao);
            limpaTerminal();
            break;
        case 5:
        	lerRegistros();
        	limpaTerminal();
        	break;
        case 0:
        	printf("Programa encerrado!\n");
        	limpaTerminal();
            return 0;
        default: // Caso seja um valor nao esperado mostra Opcao Invalida
            printf("Opcao Invalida!!\n");
            break;
    }
    return 1;
}

int main() {
    Livro livros[1000];
    int posicao = 0;
    int loop = 1;

    carregarLivros(livros, &posicao); // carrega os livros no buffer inicialmente

    while(loop) {
        loop = opcaoMenu(livros, &posicao);
    }
    return 0;
}