#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int maxWords = 13;
char *words[13][2];
int qtyWord = 0;

int map(char *name, char *text);
int digit_to_int(char d);
void emit(char *word, char *count);
void reduce(char * key, char * valuesByKey);
struct token {
	char word;
	char qtd;
};

int main() {
	printf("Inicio \n");
	char *name = "frutas";
	char text[] = "PERA-MA‚A BANANA UVA-MELANCIA LARANJA PERA-UVA MORANDO LARANJA ACEROLA CAQUI UVA";
	map(name, text);

	return 0;
}

int map(char* name, char text[]) {
	printf("Map \n");
	printf("%s\n",text);
	char s[2] = "-";
	char *token;
	printf("antes do strtok");
	/* get the first token */

	token = strtok(text, s);
	printf("Primeiro %s\n",token);
	/* walk through other tokens */
	while (token) {
		printf(" %s\n", token);
		token = strtok(NULL, s);
	}

	return 0;
}

int digit_to_int(char d) {
	char str[2];
	str[0] = d;
	str[1] = '\0';
	return (int) strtol(str, NULL, 10);
}
void emit(char *word, char *count) {
	if (qtyWord <= 10) {
		words[qtyWord][0] = word;
		words[qtyWord][1] = count;
		qtyWord++;
	}
	printf("%s %u\n", word, count);
}

void reduce(char * key, char * valuesByKey) {
	int sum = 0;
	int i =0;
	for (i = 0; i < sizeof(valuesByKey) / sizeof(int); i++) {
		sum = +digit_to_int(valuesByKey[i]);
	}
	printf("%s %u\n", key, sum);

}

/*
 * function map(String name, String document):
 // name: document name
 // document: document contents
 for each word w in document:
 emit (w, 1)

 function reduce(String word, Iterator partialCounts):
 // word: a word
 // partialCounts: a list of aggregated partial counts
 sum = 0
 for each pc in partialCounts:
 sum += ParseInt(pc)
 emit (word, sum)
 *
 */

