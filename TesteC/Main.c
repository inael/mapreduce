#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const int maxWords = 33;

int qtyWord = 0;
struct Token {
	char *word;
	char *qtd;
};

void map(char *name, char *text, struct Token tokens[]);
void emit(char *word, char *qtd, struct Token tokens[]);
void reduce(char * key, char * valuesByKey);
int digit_to_int(char d);
int sortChar(int size, char * arrays[]);
int sortToken(int sizes, struct Token *tokens);
static int compare(const void * a, const void * b);
static int compareToken(const void * a, const void * b);
void printVetor(struct Token *tokens);
void shuffleSort(struct Token tokensEncontrados[], struct Token tokensUnidos[]);

int main() {
	printf("Inicio \n");
	char *name = "frutas";
	char text[] = "P M B U M L P Z U Y M K Q L K A M N X O P Z K Q W E F G V C X Z C O K J H T R E W Q A S F B N M K L P O I U Y T R E W Q A S D F G H J K L M N B V C X Z N J F U M L A C U P M B U M L P U M L P M B U M L P U M L A C U A C U ";

	struct Token tokensFound[maxWords];
	//struct Token tokens2[maxWords];

	map(name, text, tokensFound);
	//map(name, text2, tokens2);

	sortToken(maxWords, tokensFound);
	//sortToken(maxWords, tokens2);
	printVetor(tokensFound);
	struct Token tokensUnited[maxWords];
	shuffleSort(tokensFound, tokensUnited);
	printVetor(tokensUnited);
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
	int countTokensUnited=1;;
	for (i = 1; i < maxWords; i++) {
		currentToken = tokensFound[i];
		previousToken = tokensFound[i - 1];
		printf("Tokens - %s %s\n", currentToken.word, previousToken.word);

		if (strcmp(currentToken.word, previousToken.word) == 0) {
			printf("Igual- %s %s\n", currentToken.word, previousToken.word);

			int indexToken = countTokensUnited-1;
			const char* ocurrences = tokensUnited[indexToken].qtd;
			printf("ocurrences %s\n ", ocurrences);
			const char* newOcurrences = " 1";
			printf("countEquals %d\n",countEquals);
			char* ocurrencesUpdated = malloc(strlen(ocurrences)+strlen(newOcurrences)+1);
			strcpy(ocurrencesUpdated, ocurrences);
			strcat(ocurrencesUpdated, newOcurrences);

			tokensUnited[indexToken].qtd = ocurrencesUpdated;
			countEquals++;
			printf("Novo Ocurrence (%s,%s) na posicao %d\n \n", currentToken.word, ocurrencesUpdated, indexToken);

		}else{
			countEquals = 0;
			countTokensUnited++;
			tokensUnited[countTokensUnited-1] = currentToken;
			printf("Diferente (%s,%s) adicionando na posicao %d\n", tokensUnited[countTokensUnited-1].word,tokensUnited[countTokensUnited-1].qtd,countTokensUnited-1);
			printf("countEquals %d\n",countEquals);
			printf("countTokensUnited %d\n \n",countTokensUnited);



		}

	}
}
void printVetor(struct Token *tokens) {
	int i;

	printf("size %d, %d\n",sizeof(tokens), sizeof(tokens[0].word));
	printf("Print Vetor");
	for (i = 0; i < 18; i++) {
		printf("(%s,%s), ", tokens[i].word, tokens[i].qtd);
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
	return 0;
}
int sortChar(int sizes, char * array[]) {
	int i = 0;
	qsort(array, sizes, sizeof(const char *), compare);
	return 0;
}
void emit(char *word, char *qtd, struct Token *tokens) {
	if (qtyWord <= maxWords) {
		tokens[qtyWord].word = word;
		tokens[qtyWord].qtd = "1";
		qtyWord++;
	}
}

int digit_to_int(char d) {
	char str[2];
	str[0] = d;
	str[1] = '\0';
	return (int) strtol(str, NULL, 10);
}
void reduce(char * key, char * valuesByKey) {
	printf("Iniciando Reduce\n");
	int sum = 0;
	int i = 0;
	for (i = 0; i < sizeof(valuesByKey) / sizeof(int); i++) {
		sum = +digit_to_int(valuesByKey[i]);
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

/*
 * function map(String name, String document):
 // name: document name
 // document: document contents
 for each word w in document:
 emit (w, 1)

 function reduce(String word, Iterator xpartialCounts):
 // word: a word
 // partialCounts: a list of aggregated partial counts
 sum = 0
 for each pc in partialCounts:
 sum += ParseInt(pc)
 emit (word, sum)
 *
 */

