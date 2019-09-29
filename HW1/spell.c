#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include "dictionary.h"
#include <ctype.h>
#include <stdlib.h>

bool load_dictionary(const char* dictionary_file, hashmap_t hashtable[]){

	for(int k = 0; k < HASH_SIZE; k++){
		// free(hashtable[k]);
		hashtable[k] = NULL;
	}
	char str[LENGTH];

	FILE* fp;
	fp = fopen(dictionary_file, "r");
	if (fp == NULL){
		printf("Could not open file %s", dictionary_file);
		return false;
	}

	while (fgets(str, LENGTH, fp) != NULL) {
        for (int i=0; i<=strlen(str); i++) {
            str[i] = tolower(str[i]);
        }
    	node* aNode = malloc(sizeof(node));
        strpy(aNode->word, str);

    	int index = hash_function(str);

    	if (hashtable[index] == NULL) {
	    	aNode->next = NULL;
    		hashtable[index] = aNode;
    	}
    	else{
	    	aNode->next = hashtable[index];
    		hashtable[index] = aNode;
    	}
    }
    fclose(fp);
    return true;
}

bool check_word(const char* word, hashmap_t hashtable[]) {
	int index = hash_function(word);
	node* cursor = hashtable[index];
    char theWord[LENGTH];

    for(int i=0; i<=strlen(word); i++) {
        theWord[i] = tolower(word[i]);
    }
	while(cursor) {
		if (strcmp(cursor->word, theWord) == 0) { 
			return true;
		}
		else{
			cursor = cursor->next;
		}
	}
	return false;
}

int check_words(FILE* fp, hashmap_t hashtable[], char* misspelled[MAX_MISSPELLED]) { 
	int num_misspelled = 0;
	if (fp == NULL) {
        printf("Could not open file");
        return 1;
    }

    char str[10000];
    char* token = strtok(str," ");

    while (fgets(str, 10000, fp) != NULL) {
    	token = strtok(NULL," ");
    	while(token != NULL){
            if (token[strlen(token)-1] =='\n'){
            	token[strlen(token)-1]='\0';
            }
            token[strlen(token)]='\0';    

            if (ispunct(token[strlen(token)-1])){
                token[strlen(token)-1]='\0';
            }
            if (ispunct(token[0])){
                token[0]='\0';
            }
			bool spellcheck = check_word(token,hashtable);
			if(!(spellcheck == true)){
        		misspelled[num_misspelled] = malloc(strlen(token));
            	strcpy(misspelled[num_misspelled], token);
            	num_misspelled ++;
            }            
		}
    }
}