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
	printf("======== Cadastrar Livro ========\n");
	printf("NOME: ");
	gets(&livro.nome);
	printf("ISBN: ");
	gets(&livro.ISBN);
	livros[*posicao] = livro;
	*posicao = *posicao + 1;
	fprintf(file, "========= Livro %d =========\n", *posicao);
	fprintf(file, "Nome do Livro: %s\n", livro.nome);
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