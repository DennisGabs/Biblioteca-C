# include <stdio.h>
# include <stdlib.h>
# include <string.h>

typedef struct{
	int id;
	char nome[150];
	char ISBN[12];
	int qtd;
	int qtd_emprestado;
}Livro;

void cadastrarLivro(Livro livros[], int *posicao){
	FILE *file;
	file = fopen("./registros.txt", "a");
	Livro livro;
	fflush(stdin);
	printf("======== Cadastrar Livro ========\n");
	printf("NOME: ");
	gets(&livro.nome);
	printf("ISBN: ");
	gets(&livro.ISBN);
	printf("Quantidade: ");
	scanf("%d", &livro.qtd);
	*posicao = *posicao + 1;
	livros[*posicao] = livro;
	fprintf(file, "========= Livro %d =========\n", *posicao);
	fprintf(file, "Nome: %s\n", livro.nome);
	fprintf(file, "ISBN: %s\n", livro.ISBN);
	fprintf(file, "Quantidade: %d\n", livro.qtd);
	fprintf(file, "===========================\n");
	fclose(file);
	return livros;
}

int main(){
	Livro livros[1000];
	int posicao = 0;
	cadastrarLivro(livros, &posicao);
	printf("%s\n", livros[posicao].nome);
	cadastrarLivro(livros, &posicao);
	printf("%s\n", livros[posicao].nome);
	return 0;
}