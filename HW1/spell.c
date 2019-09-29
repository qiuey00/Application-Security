#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include "dictionary.h"
#include <ctype.h>
#include <stdlib.h>

bool load_dictionary(const char* dictionary_file, hashmap_t hashtable[]){
	for(int i=0; i<=HASH_SIZE; i++){
        hashtable[i] = NULL;
    }

    FILE* fp = fopen(dictionary_file, "r");

	if (!fp) {
		printf("no file");
		return false;
	}

    char str[LENGTH];

	while(fgets(str, LENGTH, fp)) {
        for(int i = 0; i <= strlen(str); i++) {
            str[i] = tolower(str[i]);
        }

        if (str[strlen(str)-1] == '\n'){
            str[strlen(str)-1] = '\0';
        }

    	int index = hash_function(str);

    	if (hashtable[index] == NULL) {
            node *aNode = malloc(sizeof(node));
            strcpy(aNode->word, str);
	    	aNode->next = NULL;
    		hashtable[index] = aNode;
    	}
    	else{
            node *aNode = malloc(sizeof(node));
            strcpy(aNode->word, str);
	    	aNode->next = hashtable[index];
    		hashtable[index] = aNode;
    	}
    }

    fclose(fp);
    return true;

}

bool check_word(const char* word, hashmap_t hashtable[]) {
    char theWord[LENGTH];

    for(int i=0; i<=strlen(word); i++) {
        theWord[i] = tolower(word[i]);
    }

    int index = hash_function(theWord);
	node* cursor = hashtable[index];

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
    char str[255];
    char* token = strtok(str," ");

    while (fgets(str, 255, fp)) {
        token = strtok(NULL," ");
    	while (token != NULL){
            if (token[strlen(token)-1] =='\n'){
            	token[strlen(token)-1]='\0';
            }
            token[strlen(token)]='\0';    

            if (ispunct(token[strlen(token)-1])){
                while(ispunct(token[strlen(token)-1])){
                    token[strlen(token)-1]='\0';
                }
            }
            if (ispunct(token[0])){
                while(ispunct(token[0])){
                    token++;                    
                }
            }

			bool spellcheck = check_word(token,hashtable);
			if(spellcheck == false){
        		misspelled[num_misspelled] = malloc(strlen(token));
            	strcpy(misspelled[num_misspelled], token);
            	num_misspelled ++;
            }
            token = strtok(NULL," ");
		}
        // if (num_misspelled > MAX_MISSPELLED){
        //     break;
        // }

    }
    return num_misspelled;
}