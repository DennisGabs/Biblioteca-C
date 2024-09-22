#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int id;
    char nome[150];
    char ISBN[12];
    int qtd;
    int qtd_emprestado;
} Livro;

void registrar(Livro *livro) {
    FILE *file = fopen("./registros.txt", "a");
    fprintf(file, "========= Livro =========\n");
    fprintf(file, "ID: %d\n", livro->id);
    fprintf(file, "Nome: %s\n", livro->nome);
    fprintf(file, "ISBN: %s\n", livro->ISBN);
    fprintf(file, "Quantidade Disponivel: %d\n", livro->qtd);
    fprintf(file, "Quantidade Emprestada: %d\n", livro->qtd_emprestado);
    fprintf(file, "===========================\n");
    fclose(file);
}

void refazerRegistros(Livro livros[], int posicoes){
	FILE *file = fopen("./registros.txt", "w");
	int i;
	for(i = 0; i < posicoes; i++){
		fprintf(file, "========= Livro =========\n");
    	fprintf(file, "ID: %d\n", livros[i].id);
    	fprintf(file, "Nome: %s\n", livros[i].nome);
    	fprintf(file, "ISBN: %s\n", livros[i].ISBN);
    	fprintf(file, "Quantidade Disponivel: %d\n", livros[i].qtd);
    	fprintf(file, "Quantidade Emprestada: %d\n", livros[i].qtd_emprestado);
    	fprintf(file, "===========================\n");
	}
	fclose(file);
}

void salvarLivros(Livro livros[], int posicao) {
    FILE *file = fopen("./livros.bin", "wb");
    fwrite(livros, sizeof(Livro), posicao, file);
    fclose(file);
    refazerRegistros(livros, posicao);
}

void carregarLivros(Livro livros[], int *posicao) {
    FILE *file = fopen("./livros.bin", "rb");
    if (file != NULL) {
        while (fread(&livros[*posicao], sizeof(Livro), 1, file)) {
            (*posicao)++;
        }
        fclose(file);
    }
}

void cadastrarLivro(Livro livros[], int *posicao) {
    Livro livro;
    fflush(stdin);
    printf("======== Cadastrar Livro ========\n");
    printf("NOME: ");
    fgets(livro.nome, sizeof(livro.nome), stdin);
    livro.nome[strcspn(livro.nome, "\n")] = 0;

    printf("ISBN: ");
    fgets(livro.ISBN, sizeof(livro.ISBN), stdin);
    livro.ISBN[strcspn(livro.ISBN, "\n")] = 0;

    printf("Quantidade: ");
    scanf("%d", &livro.qtd);

    livro.qtd_emprestado = 0;
    livro.id = (*posicao) + 1;
    livros[*posicao] = livro;
    (*posicao)++;

    registrar(&livros[*posicao - 1]);
    salvarLivros(livros, *posicao);
}

void emprestarLivro(Livro livros[], int posicao) {
    char isbn[12];
    printf("Informe o ISBN do livro que deseja emprestar: ");
    fflush(stdin);
    fgets(isbn, sizeof(isbn), stdin);
    isbn[strcspn(isbn, "\n")] = 0;
	int i;
    for (i = 0; i < posicao; i++) {
        if (strcmp(livros[i].ISBN, isbn) == 0) {
            if (livros[i].qtd > 0) {
                livros[i].qtd--;
                livros[i].qtd_emprestado++;
                printf("Livro %s emprestado com sucesso!\n", livros[i].nome);
                salvarLivros(livros, posicao);
                return;
            } else {
                printf("Não há mais exemplares disponíveis para empréstimo.\n");
                return; 
            }
        }
    }
    printf("Livro não encontrado!\n");
}

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
                livros[i].qtd++;
                livros[i].qtd_emprestado--;
                printf("Livro %s devolvido com sucesso!\n", livros[i].nome);
                salvarLivros(livros, posicao);
                return;
            } else {
                printf("Nenhum exemplar emprestado deste livro.\n");
                return;
            }
        }
    }
    printf("Livro não encontrado!\n");
}

void pesquisarLivro(Livro livros[], int posicao) {
    char isbn[12];
    printf("Informe o ISBN do livro para pesquisa: ");
    fflush(stdin);
    fgets(isbn, sizeof(isbn), stdin);
    isbn[strcspn(isbn, "\n")] = 0;
	int i;
    for (i = 0; i < posicao; i++) {
        if (strcmp(livros[i].ISBN, isbn) == 0) {
            printf("Livro encontrado!\n");
            printf("ID: %d\n", livros[i].id);
            printf("Nome: %s\n", livros[i].nome);
            printf("Quantidade disponível: %d\n", livros[i].qtd);
            printf("Quantidade emprestada: %d\n", livros[i].qtd_emprestado);
            return;
        }
    }
    printf("Livro não encontrado!\n");
}

void menu() {
    printf("======= MENU =======\n");
    printf("1 - CADASTRAR Livro\n");
    printf("2 - EMPRESTAR Livro\n");
    printf("3 - DEVOLVER Livro\n");
    printf("4 - PESQUISAR Livro\n");
    printf("5 - LER REGISTROS\n");
    printf("0 - SAIR\n");
}

void lerRegistros(){
	FILE *file = fopen("./registros.txt", "r");
	char linha[150];
	system("cls");
	printf("====== Conteudo do Arquivo ======\n");
	while(fgets(linha, sizeof(linha), file)){
		printf("%s", linha);
	}
	fclose(file);
	printf("==============================\n");
}

void limpaTerminal(){
	system("pause");
	system("cls");        
}

int opcaoMenu(Livro livros[], int *posicao) {
    menu();
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
        default:
            printf("Opcao Invalida!!\n");
            break;
    }
    return 1;
}

int main() {
    Livro livros[1000];
    int posicao = 0;
    int loop = 1;

    carregarLivros(livros, &posicao);

    while(loop) {
        loop = opcaoMenu(livros, &posicao);
    }
    return 0;
}