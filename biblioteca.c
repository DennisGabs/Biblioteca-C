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

void registrar(Livro *livro, int posicao) {
	// fonte de inspiracao: https://www.w3schools.com/c/c_files_write.php
    FILE *file = fopen("./registros.txt", "a"); // abre arquivo em modo de atualizacao
   	// escrevendo no arquivo 	  
	fprintf(file, "========= Livro =========\n");
    fprintf(file, "Nome: %s\n", livro->nome);
    fprintf(file, "ISBN: %s\n", livro->ISBN);
    fprintf(file, "Quantidade: %d\n", livro->qtd);
    fprintf(file, "===========================\n");
    fclose(file); // fecha o processo de atualizacao
}

void cadastrarLivro(Livro livros[], int *posicao) {
    Livro livro;
    fflush(stdin);
    printf("======== Cadastrar Livro ========\n");
    printf("NOME: ");
    fgets(livro.nome, sizeof(livro.nome), stdin);
    // garante q a proxima entrada n seja ignorado devido ao \n(enter)
    livro.nome[strcspn(livro.nome, "\n")] = 0; 

    printf("ISBN: ");
    fgets(livro.ISBN, sizeof(livro.ISBN), stdin);
    livro.ISBN[strcspn(livro.ISBN, "\n")] = 0;

    printf("Quantidade: ");
    scanf("%d", &livro.qtd);
    
    livro.id = (*posicao) + 1; // o novo livro cadastrado recebe o Id da posicao atual + 1
    livros[*posicao] = livro; // o array de livros recebe um novo livro na posicao atual
    (*posicao)++; // O valor da posicao eh incrementado, para q os futuros livros n se sobreponham
    
    registrar(&livros[*posicao - 1], *posicao);
}

void lerArquivo() {
    FILE *file = fopen("./registros.txt", "rt"); //abre o arquivo modo leitura
    char linha[500];
    char *result; // vai ser usado para intercalar entre as linhas do arquivo
    printf("========= Conteudo do Arquivo =========\n");
	// fonte de inspiracao https://www.inf.pucrs.br/~pinho/LaproI/Arquivos/Arquivos.htm
	while (!feof(file)){
		// faz a leitura ate 499 caracteres ou até o \n
		result = fgets(linha, sizeof(linha), file); 
		if(result){ // se foi possivel fazer a leitura
			printf("%s", linha);
		}
	}
    fclose(file);
    printf("========================================\n");
}

void menu() {
    printf("======= MENU =======\n");
    printf("1 - CADASTRAR Livro\n");
    printf("2 - LER Arquivo\n");
    printf("0 - SAIR\n");
}

int opcaoMenu(Livro livros[], int *posicao) {
    menu();
    int op;
    printf("Informe uma opcao: ");
    scanf("%d", &op);
    switch(op) {
        case 1:
            cadastrarLivro(livros, posicao);
            system("pause");
            system("cls");
            break;
        case 2:
            lerArquivo();
            system("pause");
            system("cls");
            break;
        case 0:
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

    while(loop) {
        loop = opcaoMenu(livros, &posicao);
    }
    return 0;
}
