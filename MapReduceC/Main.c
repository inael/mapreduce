#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Token {
	char *word;
	char qtd[50];
};
void map(char *name, char *text, struct Token tokens[]);
void emit(char *word, char *qtd, struct Token tokens[]);
void reduce(struct Token *tokens);
int sortToken(int sizes, struct Token *tokens);
void shuffleSort(struct Token tokensEncontrados[], struct Token tokensUnidos[]);

static int compare(const void * a, const void * b);
static int compareToken(const void * a, const void * b);
int sortChar(int size, char * arrays[]);
int digit_to_int(char d);
void printVetor(struct Token tokens[], int indexMax);
#define BUZZ_SIZE 1024
const int maxWords = 47;
const int maxPrint = 47;
int qtyWord = 0;
int main() {
	int sizeLine = 94;
	char *text = malloc(sizeLine);
	;
	FILE *f = fopen("entrada.txt", "r");
	while (fgets(text, sizeLine, f) != NULL ) {

		printf("Linha: %s\n", text);
		fclose(f);
		printf("Inicio \n");
		char *name = "frutas";

		struct Token tokensFound[maxWords];
		//struct Token tokens2[maxWords];

		map(name, text, tokensFound);
		//map(name, text2, tokens2);
		printVetor(tokensFound, maxWords);
		sortToken(maxWords, tokensFound);
		//sortToken(maxWords, tokens2);
		printVetor(tokensFound, maxWords);
		struct Token tokensUnited[maxWords];
		shuffleSort(tokensFound, tokensUnited);
		printVetor(tokensUnited, 25);
		reduce(tokensUnited);
		printVetor(tokensUnited, 25);
	}
	return 0;
}
void shuffleSort(struct Token tokensFound[], struct Token tokensUnited[]) {
	printf("\n Iniciando SuffleSort \n");
	int i;
	struct Token currentToken;
	struct Token previousToken;
	tokensUnited[0] = tokensFound[0];
	//printf("Primeiro %s %s\n", tokensFound[0].word, tokensFound[0].qtd);
	int countEquals = 0;
	int countTokensUnited = 1;
	;
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

void map(char* name, char text[], struct Token tokens[]) {
	printf("Iniciando Map\n");
	char s[2] = " ";
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

/* n_array is the number of elements in the array. */
int sortToken(int size, struct Token *tokens) {
	printf("Iniciando Ordenacao\n");
	int i = 0;
	qsort(tokens, size, sizeof(tokens[0]), compareToken);
	printf("Fim da Ordenacao");
	return 0;
}
int sortChar(int sizes, char * array[]) {
	int i = 0;
	qsort(array, sizes, sizeof(const char *), compare);
	return 0;
}
void emit(char *word, char *qtd, struct Token *tokens) {
	if (qtyWord < maxWords) {
		tokens[qtyWord].word = word;
		strcpy(tokens[qtyWord].qtd, "1");
		qtyWord++;
	}
}

int digit_to_int(char d) {
	char str[2];
	str[0] = d;
	str[1] = '\0';
	return (int) strtol(str, NULL, 10);
}

void reduce(struct Token *tokens) {
	printf("Iniciando Reduce\n");

	int i = 0;
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
		//char qtd[acumulator];
		//itoa(acumulator,qtd);
		snprintf(tokens[i].qtd, 200, "%d", acumulator);
		//strcpy(tokens[i].qtd, qtd);
		printf("tokens[%d].qtd %s\n", i, tokens[i].qtd);

		acumulator = 0;
	}

}

static int compare(const void * a, const void * b) {
	/* The pointers point to offsets into "array", so we need to
	 dereference them to get at the strings. */
	return strcmp(*(const char **) a, *(const char **) b);
}
static int compareToken(const void * a, const void * b) {
	const struct Token *elem1 = a;
	const struct Token *elem2 = b;
	return strcmp(elem1->word, elem2->word);

}
void printVetor(struct Token *tokens, int indexMax) {
	int i;
	printf("Print Vetor\n");
	for (i = 0; i < indexMax; i++) {
		printf("%d: (%s|%s) \n ", i, tokens[i].word, tokens[i].qtd);

	}
}
