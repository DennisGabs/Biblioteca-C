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

Livro* cadastrarLivro(Livro livros[], int *posicao){
	Livro livro;
	printf("======== Cadastrar Livro ========\n");
	printf("NOME: ");
	gets(&livro.nome);
	printf("ISBN: ");
	gets(&livro.ISBN);
	livros[*posicao] = livro;
	posicao = posicao + 1;
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