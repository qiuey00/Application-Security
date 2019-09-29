#include "dictionary.h"
#include <stdlib.h>

int main(int argc, char * argv[]) {
	hashmap_t hashtable[HASH_SIZE];
	char *misspelled[MAX_MISSPELLED];

	FILE *fp = fopen(argv[1], "r");
	load_dictionary(argv[2], hashtable);

	int num_misspelled = check_words(fp, hashtable, misspelled);
	fclose(fp);
	printf("misspelled: %i",num_misspelled);
}