#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<time.h>
//-------------------------------CONSTANTES--------------------------------------
struct Token {
	char *word;
	char qtd[50];
};
#define BUZZ_SIZE 1024
const int maxWords = 47;
const int maxPrint = 47;
int qtyWord = 0;
//-------------------------------FUNCOES MAPREDUCE-------------------------------------
/**
 * A funcao Map leva como entrada uma linha, textLine, que ser‡ quebrada em v‡rios
 * tokens e no final ser‡ gerado pares de (chave, valor) armazenada em tokens.
 * PARAMETROS:
 * name-> identificacao da linha processada
 * textLine->linha de texto
 * tokens-> vetor(struct) de pares de chave e valor. Nesse caso de wordCount, a chave e
 * a palavra, e o valor e a quantidade de ocorrencias.
 */
void map(char *name, char *textLine, struct Token tokens[]);
/**
 * Funcao chamada pelo map, a qual monta um token com o par chave(word) valor(qtd)
 * PARAMETROS:
 * word-> palavra
 * qtd-> quantidade de ocorrencias da palavra, que e "1"
 * tokens->vetor(struct) de pares de chave e valor. Ex: (A,1),(C,1),(A,1)...
 */
void emit(char *word, char *qtd, struct Token tokens[]);
/**
 * Funcao que ordena os tokens para que os pares de mesma palavra fiquem proximos.
 * Isso facilita as proximas etapas de Shuffle e Reduce
 * PARAMETROS:
 * qtdTokens-> Quantidade de tokens no vetor.
 * tokens->  Vetor de retorno com tokens ordenados. Ex: (A,1),(A,1),(B,1)(C,1)...
 */
int sortToken(int qtdTokens, struct Token *tokens);
/**
 * Funcao que uni os tokens com a mesma palavra e incrementa a quantidade de ocorrencias.
 * Ex. para um vetor (A,1),(A,1),(B,1)(C,1) a saida seria (A,1 1),(B,1)(C,1).
 * PARAMETROS:
 * tokenFound-> Tokens ordenados
 * tokensUnited->Tokens unidos e ordenados
 */
void shuffleSort(struct Token tokensFound[], struct Token tokensUnited[]);
/**
 * Funcao que soma a quantidade de ocorrencias de palavra para cada token.
 * Ex. para o vetor  (A,1 1),(B,1)(C,1) a sa’da sera  (A,2),(B,1)(C,1).
 * PARAMETROS:
 * tokens-> Vetor de tokens unidos e ordenados.
 */
void reduce(struct Token *tokens);

//--------------------------------FUNCOES AUXILIARES--------------------------------
static int compareToken(const void * a, const void * b);
int digit_to_int(char d);
void printVetor(struct Token tokens[], int indexMax);
float diffTime(clock_t t2,clock_t t1);
//--------------------------------MAIN-----------------------------------------

int main() {
	clock_t t1, t2; //usado para calcular o tempo de exec
	int sizeLine = 94;//tamanho de uma linha do documento entrada.txt
	char *text = malloc(sizeLine); //aloco o tamanho de uma linha na memoria
	int countLine; //contador de linha do documento, usado para impressao apenas;
	FILE *f = fopen("entrada.txt", "r");
	t1 = clock();
	//divide a entrada em pedacos, sendo que cada pedaco e uma linha
	while (fgets(text, sizeLine, f) != NULL ) {
		countLine++;
		printf("Linha %d: %s\n",countLine, text);
		fclose(f);

		//aloco um array de Tokens{word, qtd}
		struct Token tokensFound[maxWords];

		//inicio a etapa de map, na qual para cada palavra sera emitido um par de(key,'1')
		char *name;
		sprintf(name,"Line%d",countLine);
		map(name, text, tokensFound);
		printVetor(tokensFound, maxWords);

		//ordeno os tokens para facilitar a proxima etapa
		sortToken(maxWords, tokensFound);
		printVetor(tokensFound, maxWords);

		//pega os tokens com a mesma chave e uni o qtd.
		//Ex se temos ('A',1) e ('A',1) no final teremos('A',1 1)
		struct Token tokensUnited[maxWords];
		shuffleSort(tokensFound, tokensUnited);
		printVetor(tokensUnited, 25);

		//reduz os qtd de toquem somando-os. Ex para ('A',1 1), ficar‡ ('A',2)
		reduce(tokensUnited);
		printVetor(tokensUnited, 25);
		printf("--------------------------- Final da linha %d ---------------------------\n",countLine);
	}
	t2 = clock();
	printf("Tempo %f mms",diffTime(t2,t1));
	return 0;
}
//--------------------------------IMPLEMENTACOES-----------------------------------------

void map(char* name, char text[], struct Token tokens[]) {
	printf("Iniciando Map\n");
	char s[2] = " ";//separator
	char *token;
	/* get the first token */
	token = strtok(text, s);
	char * one = "1";
	emit(token, one, tokens);
	/* walk through other tokens */
	while (token) {
		token = strtok(NULL, s);
		emit(token, one, tokens);
	}
}

void emit(char *word, char *qtd, struct Token *tokens) {
	if (qtyWord < maxWords) {
		tokens[qtyWord].word = word;
		strcpy(tokens[qtyWord].qtd, "1");
		qtyWord++;
	}
}

int sortToken(int qtdTokens, struct Token *tokens) {
	printf("Iniciando Ordenacao\n");
	int i = 0;
	qsort(tokens, qtdTokens, sizeof(tokens[0]), compareToken);
	printf("Fim da Ordenacao");
	return 0;
}

void shuffleSort(struct Token tokensFound[], struct Token tokensUnited[]) {
	printf("\n Iniciando SuffleSort \n");
	int i;
	struct Token currentToken;
	struct Token previousToken;
	//Copia-se o primeiro token de tokensFound para tokensUnited.
	tokensUnited[0] = tokensFound[0];
	int countEquals = 0;
	int countTokensUnited = 1;
	/**
	 * Para cada tokens em tokensFound
	 * Compara o proximo token de tokensFound com o token anterior de tokensFound
	 * 	- se for igual incrementa-se  a quantidade de ocorrencias do token em tokenFound
	 *  - se nao for igual, adiciona o novo token na proxima posicao de tokenFound
	 */
	for (i = 1; i < maxWords; i++) {
		currentToken = tokensFound[i];
		previousToken = tokensFound[i - 1];
		printf("Tokens - %s %s\n", currentToken.word, previousToken.word);

		if (strcmp(currentToken.word, previousToken.word) == 0) {
			printf("Igual- %s %s\n", currentToken.word, previousToken.word);

			int indexToken = countTokensUnited - 1;
			const char* ocurrences = tokensUnited[indexToken].qtd;
			printf("ocurrences %s\n ", ocurrences);
			const char* newOcurrences = " 1";
			printf("countEquals %d\n", countEquals);
			char* ocurrencesUpdated = malloc(
					strlen(ocurrences) + strlen(newOcurrences) + 1);
			strcpy(ocurrencesUpdated, ocurrences);
			strcat(ocurrencesUpdated, newOcurrences);

			strcpy(tokensUnited[indexToken].qtd, ocurrencesUpdated);
			countEquals++;
			printf("Novo Ocurrence (%s,%s) na posicao %d\n \n",
					currentToken.word, ocurrencesUpdated, indexToken);

		} else {
			countEquals = 0;
			countTokensUnited++;
			tokensUnited[countTokensUnited - 1] = currentToken;
			printf("Diferente (%s,%s) adicionando na posicao %d\n",
					tokensUnited[countTokensUnited - 1].word,
					tokensUnited[countTokensUnited - 1].qtd,
					countTokensUnited - 1);
			printf("countEquals %d\n", countEquals);
			printf("countTokensUnited %d\n \n", countTokensUnited);

		}

	}
}

void reduce(struct Token *tokens) {
	printf("Iniciando Reduce\n");

	int i = 0;
	/**
	 * Para cada token em tokens faca:
	 * separa as ocorrencias em tokens[i].qtd
	 * para cada ocorrencia incrementa um contador
	 * depois atualiza a quantidade de ocorrencia do tokens[i].qtd
	 * com o contador.
	 */
	for (i = 0; i < maxPrint; i++) {
		char * ocurrences = tokens[i].qtd;
		char *value;
		const char separator[2] = " ";
		int acumulator = 0;
		value = strtok(ocurrences, separator);
		while (value) {
			value = strtok(NULL, separator);
			acumulator++;
		}
		snprintf(tokens[i].qtd, 200, "%d", acumulator);
		printf("tokens[%d].qtd %s\n", i, tokens[i].qtd);
		acumulator = 0;
	}

}

static int compareToken(const void * a, const void * b) {
	const struct Token *elem1 = a;
	const struct Token *elem2 = b;
	return strcmp(elem1->word, elem2->word);

}
void printVetor(struct Token *tokens, int indexMax) {
	int i;
	printf("Imprimindo o Vetor\n");
	for (i = 0; i < indexMax; i++) {
		printf("%d: (%s|%s) \n ", i, tokens[i].word, tokens[i].qtd);
	}
}

int digit_to_int(char d) {
	char str[2];
	str[0] = d;
	str[1] = '\0';
	return (int) strtol(str, NULL, 10);
}

float diffTime(clock_t t2,clock_t t1){
	 float diff = (((float)t2 - (float)t1) / 1000000.0F ) * 1000;
	 return diff;
}
