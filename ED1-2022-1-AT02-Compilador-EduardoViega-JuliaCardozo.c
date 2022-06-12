#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct NoPilha *PtrNoPilha;

//-----------------------------------
// Ponteiros (encadeamento)
//-----------------------------------

// Struct NoPilha* -> PtrNoPilha
typedef struct NoPilha {
    char x;
	PtrNoPilha proximo;
} NoPilha;

// PilhaDinamica
typedef struct {
    PtrNoPilha topo;
    int tamanho;
} PilhaDinamica;

//---------------------------------------------------------------------------------
//---------------------------------------------------------------------------------

// Inicializa a pilha 
void iniciaPilhaDinamica(PilhaDinamica *pilha) {
	pilha->topo = NULL;
	pilha->tamanho = 0;
}

//---------------------------------------------------------------------------------
//---------------------------------------------------------------------------------

// Retorna tamanho da pilha
int tamanhoPilhaDinamica(PilhaDinamica *pilha) {
	return(pilha->tamanho);
}

//---------------------------------------------------------------------------------
//---------------------------------------------------------------------------------

// Retorna se a pilha est� vazia ou n�o
bool estaVaziaPilhaDinamica(PilhaDinamica *pilha) {
	return(pilha->tamanho == 0);
}

//---------------------------------------------------------------------------------
//---------------------------------------------------------------------------------

// Adiciona elementos na pilha
void empilhaPilhaDinamica(PilhaDinamica *pilha, int x) {
	PtrNoPilha aux;
	aux = (PtrNoPilha)malloc(sizeof(NoPilha));
	aux->x = x;
	aux->proximo = pilha->topo;
	pilha->topo = aux;
	pilha->tamanho++;
}

//---------------------------------------------------------------------------------
//---------------------------------------------------------------------------------

// Remove elementos da pilha
void desempilhaPilhaDinamica(PilhaDinamica *pilha) {
	if(!estaVaziaPilhaDinamica(pilha)) {
		PtrNoPilha aux = pilha->topo;
		pilha->topo = pilha->topo->proximo;
		free(aux);
		pilha->tamanho--;
	}
}

//---------------------------------------------------------------------------------
//---------------------------------------------------------------------------------

// Libera a mem�ria
void destroiPilhaDinamica(PilhaDinamica *pilha) {
	while(!estaVaziaPilhaDinamica(pilha)) {
		desempilhaPilhaDinamica(pilha);
	}
	if(estaVaziaPilhaDinamica(pilha)){
		free(pilha);
	}
}

//---------------------------------------------------------------------------------
//---------------------------------------------------------------------------------

// Fun��o para resolver a nota��o p�s-fixa do arquivo de entrada e imprimir no arquivo de sa�da
void resolve(PilhaDinamica*p, char operador, int posicaoAtual, int ultimo, FILE* saida, int* contadorF) {
	// Contador para a vari�vel TEMP
	int contador = *contadorF;
	//printf("contador %d", contador);
	//static int contador=0;
	char op1, op2, temp1, x;
	
	// Atribuindo o topo da pilha � vari�vel op1 e imprimindo no arquivo qual vari�vel foi desempilhada
	op1 = p->topo->x;
	if(op1 >= 49 && op1 <=57) {
		printf("LDR TEMP%c\n",op1);
		fprintf(saida,"LDR TEMP%c\n",op1);
	}else {
		printf("LDR %c\n",op1);
		fprintf(saida,"LDR %c\n",op1);
	}
	desempilhaPilhaDinamica(p);
	
	// Atribuindo o topo da pilha � vari�vel op2 e imprimindo no arquivo qual vari�vel foi desempilhada
	op2 = p->topo->x;
	if(op2 >= 49 && op2 <=57) {
    	printf("LDR TEMP%c\n",op2);
    	fprintf(saida,"LDR TEMP%c\n",op2);
	}else {
		printf("LDR %c\n",op2);
		fprintf(saida,"LDR %c\n",op2);
	}
	desempilhaPilhaDinamica(p);

	// Verificando qual � o operador que foi encontrado no arquivo de entrada
	switch (operador) {
		case '+':
			// Incrementando o contador da vari�vel TEMP
			contador++;
			*contadorF = *contadorF + 1;
			// Casos para impress�o no arquivo de sa�da dependendo do tipo(caractere ou TEMP) e da ordem das vari�veis
			if((op2 >= 49 && op2 <= 57)&&(op1 >= 49 && op1 <= 57)) {
		    	printf("ADD TEMP%c TEMP%c\n",op1,op2);
		    	fprintf(saida,"ADD TEMP%c TEMP%c\n",op1,op2);
			}else if(op1 >= 49 && op1<=57) {
				printf("ADD TEMP%c %c\n",op1,op2);
				fprintf(saida,"ADD TEMP%c %c\n",op1,op2);
			}else if(op2 >= 49 && op2<=57) {
				printf("ADD %c TEMP%c\n",op1,op2);
				fprintf(saida,"ADD %c TEMP%c\n",op1,op2);
			}else {
			    printf("ADD %c %c\n",op1, op2 );
			    fprintf(saida,"ADD %c %c\n",op1, op2 );
		  	}
		  	// Caso n�o seja a �ltima opera��o, empilhar o resultado da opera��o e imprimir no arquivo de sa�da 
		  	if(posicaoAtual!=ultimo) {
			    x = '0'+contador;
			    printf("STR TEMP%d\n",contador );
			    fprintf(saida,"STR TEMP%d\n",contador );
			    empilhaPilhaDinamica(p,x);
		  	}
			break;
		case '-':
		    // Incrementando o contador da vari�vel TEMP
			contador++;
			*contadorF = *contadorF +1;
			// Casos para impress�o no arquivo de sa�da dependendo do tipo(caractere ou TEMP) e da ordem das vari�veis
		    if((op2 >= 49 && op2<=57)&&(op1 >= 49 && op1<=57)) {
			    printf("SUB TEMP%c TEMP%c\n",op1,op2);
			    fprintf(saida,"SUB TEMP%c TEMP%c\n",op1,op2);
		    }else if(op1 >= 49 && op1<=57) {
			    printf("SUB TEMP%c %c\n",op1,op2);
			    fprintf(saida,"SUB TEMP%c %c\n",op1,op2);
		    }else if(op2 >= 49 && op2<=57) {
		    	printf("SUB %c TEMP%c\n",op1,op2);
				fprintf(saida,"SUB %c TEMP%c\n",op1,op2);
		    }else {
		    	printf("SUB %c %c\n",op1, op2 );
		    	fprintf(saida,"SUB %c %c\n",op1, op2 );
		    }
		  	// Caso n�o seja a �ltima opera��o, empilhar o resultado da opera��o e imprimir no arquivo de sa�da 
		    if(posicaoAtual!=ultimo) {
			    x = '0'+contador;
			    printf("STR TEMP%d\n",contador );
			    fprintf(saida,"STR TEMP%d\n",contador );
			    empilhaPilhaDinamica(p,x);
		    }
		    break;
		case '*':
			// Incrementando o contador da vari�vel TEMP
		    contador++;
			*contadorF = *contadorF +1;
			// Casos para impress�o no arquivo de sa�da dependendo do tipo(caractere ou TEMP) e da ordem das vari�veis
		    if((op2 >= 49 && op2<=57)&&(op1 >= 49 && op1<=57)) {
		    	printf("MUL TEMP%c TEMP%c\n",op1,op2);
		        fprintf(saida,"MUL TEMP%c TEMP%c\n",op1,op2);
		    }else if(op1 >= 49 && op1<=57) {
		        printf("MUL TEMP%c %c\n",op1,op2);
		        fprintf(saida,"MUL TEMP%c %c\n",op1,op2);
		    }else if(op2 >= 49 && op2<=57) {
		        printf("MUL %c TEMP%c\n",op1,op2);
		        fprintf(saida,"MUL %c TEMP%c\n",op1,op2);
		    }else {
		        printf("MUL %c %c\n",op1, op2 );
		        fprintf(saida,"MUL %c %c\n",op1, op2 );
		    }
		  	// Caso n�o seja a �ltima opera��o, empilhar o resultado da opera��o e imprimir no arquivo de sa�da 
		    if(posicaoAtual!=ultimo) {
		        x = '0'+contador;
		        fprintf(saida,"STR TEMP%d\n",contador );
		        empilhaPilhaDinamica(p,x);
		    }
		    break;
		case '/':
			// Incrementando o contador da vari�vel TEMP
		    contador++;
			*contadorF = *contadorF +1;
			// Casos para impress�o no arquivo de sa�da dependendo do tipo(caractere ou TEMP) e da ordem das vari�veis
		    if((op2 >= 49 && op2<=57)&&(op1 >= 49 && op1<=57)) {
		    	printf("DIV TEMP%c TEMP%c\n",op1,op2);
		        fprintf(saida,"DIV TEMP%c TEMP%c\n",op1,op2);
		    }else if(op1 >= 49 && op1<=57) {
		    	printf("DIV TEMP%c %c\n",op1,op2);
		    	fprintf(saida,"DIV TEMP%c %c\n",op1,op2);
		    }else if(op2 >= 49 && op2<=57) {
		    	printf("DIV %c TEMP%c\n",op1,op2);
		    	fprintf(saida,"DIV %c TEMP%c\n",op1,op2);
		    }else {
		    	printf("DIV %c %c\n",op1, op2 );
		    	fprintf(saida,"DIV %c %c\n",op1, op2 );
		    }
		  	// Caso n�o seja a �ltima opera��o, empilhar o resultado da opera��o e imprimir no arquivo de sa�da 
		    if(posicaoAtual!=ultimo) {
		        x = '0'+contador;
		    	fprintf(saida,"STR TEMP%d\n",contador );
		    	empilhaPilhaDinamica(p,x);
		    }
		    break;
	}
}

//---------------------------------------------------------------------------------
//---------------------------------------------------------------------------------

int main(int argc, char* argv[]){
	// Declarando o contador que ser� usado na fun��o resolve
	int contador = 0;
	
	// Verificando se os par�metros argc e argv est�o corretos
	if(argc!= 3){
		printf("Quantidade de parametros invalida\n");
		return 1;
	}
  
	// Abrindo os arquivos txt de entrada e sa�da
	FILE* entrada = fopen(argv[1],"r");
	FILE* saida = fopen(argv[2],"w");
  	
  	// Declarando e inicializando a pilha
	PilhaDinamica pilhacompilador;
	iniciaPilhaDinamica(&pilhacompilador);
	
	// Declarando o char c que guarda os caracteres a serem lidos da entrada
	char c;
	// Declarando a vari�vel tamanho, que guarda quantos caracteres tem no arquivo de entrada, ele � iniciado com -1 para n�o fazer o incremento de EOF
	int tamanho = -1;
	
	// Lendo o arquivo de entrada at� chegar ao final
	while((c=fgetc(entrada))!=EOF){
		// Contador de caracteres m�ximos do arquivo de entrada
		tamanho++;
		// Verificando se a entrada � v�lida ou n�o e retornando no arquivo de sa�da se n�o for v�lida e terminando o programa
		if(tamanho == 1) {
			if(!(c>=65 && c<=90)){
				printf("Expressao invalida!\n");
				fprintf(saida, "Express�o inv�lida!");	
				return 1;
			}
		}
		// Verificando se h� alguma quebra de linha no arquivo de entrada
		if(c == '\n'){
			tamanho--;
		}
	}

	// Volta o indicador de posi��o para o come�o do arquivo
	rewind(entrada);
	
	// Declarando a vari�vel atual, que guarda quantos caracteres j� foram lidos e � incrementada at� ser igual ao contador tamanho, � iniciada em -1 para n�o fazer o incremento de EOF
	int atual = -1;
	
	// Lendo o arquivo de entrada at� chegar ao final
	while((c=fgetc(entrada))!=EOF){
		// Contador de caracteres que j� foram lidos do arquivo de entrada
		atual++;
		// Verificando se o caractere lido da entrada � um operador e mandando para a fun��o para resolver a nota��o p�s fixa
		if(c == '+' || c == '-' || c == '*' || c == '/') {
			resolve(&pilhacompilador, c, atual, tamanho, saida, &contador);
		}else{
			// Caso n�o seja um operador, empilhando o caractere que foi lido na pilha
			empilhaPilhaDinamica(&pilhacompilador, c);
		}
		// Verificando se h� alguma quebra de linha no arquivo de entrada
		if(c == '\n'){
			tamanho--;
		}
	}
	
	// Fechando os arquivos que foram abertos no programa
	fclose(entrada);
	fclose(saida);
	
	// Destruindo a pilha
	destroiPilhaDinamica(&pilhacompilador);
  
	return 0;
}
