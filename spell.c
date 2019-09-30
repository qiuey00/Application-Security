#include "dictionary.h"
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

bool load_dictionary(const char* dictionary_file, hashmap_t hashtable[]){
    for(int i=0; i<=HASH_SIZE; i++){
        hashtable[i] = NULL;
    }
    FILE* fp = fopen(dictionary_file, "r");

    if (fp) {
        char str[LENGTH];
        while(fgets(str, LENGTH, fp)) {
            if(str[strlen(str)-1] =='\n'){
                str[strlen(str)-1]='\0';
            }
            for(int i = 0; i <= strlen(str); i++) {
                str[i] = tolower(str[i]);
            }
      
            int index = hash_function(str);

            if (hashtable[index] == NULL) {
                node *aNode = malloc(sizeof(node));
                strncpy(aNode->word, str, LENGTH);
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
    return false;
}

bool check_word(const char* word, hashmap_t hashtable[]) {
    if((word == NULL || strlen(word) >LENGTH)){
        return false;
    }

    char theWord[LENGTH];

    for(int i=0; i<=strlen(word); i++) {
        theWord[i] = tolower(word[i]);
    }

    int index = hash_function(theWord);
    node* cursor = hashtable[index];

    while(cursor != NULL) {
        if (strcmp(theWord, cursor->word) == 0) { 
            return true;
        }
        else{
            cursor = cursor->next;
        }
    }
    return false;
}

int check_words(FILE* fp, hashmap_t hashtable[], char* misspelled[]) { 
    int num_misspelled = 0;
    char str[10000];

    if (fp == NULL){
        return 0;
    }

    char* token = strtok(str, " ");

    while (fgets(str, 10000, fp)) {

        token = strtok(NULL," ");

        while (token != NULL){
            if (token[strlen(token)-1] == '\n') {
                token[strlen(token)-1] = '\0';
            }

            token[strlen(token)] = '\0';

            bool punc = ispunct(token[strlen(token)-1]);
            if(punc) {
                while (punc) {
                    token[strlen(token)-1] = '\0';
                    punc = ispunct(token[strlen(token)-1]);
                }
            }

            punc = ispunct(token[0]);
            if(punc) {
                while (punc) {
                    token++;
                    punc = ispunct(token[0]);
                }
            }

            bool correctness = check_word(token, hashtable);

            if(!(correctness == 1 && strlen(str) < 10000)){
                misspelled[num_misspelled] = malloc(strlen(token));
                strcpy(misspelled[num_misspelled], token);
                num_misspelled ++;
            }
            token = strtok(NULL, " ");
        }

        return num_misspelled;
    }
    return 0;
}


