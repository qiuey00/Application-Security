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

    while(cursor != NULL) {
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
    char *pos = 0;
    char *aWord;
    int num_misspelled = 0;
    char str[80];

    if (fp == NULL){
        return false;
    }

    while ( fgets(str, 80, fp) != NULL) {
        if ((pos = strchr(str, '\n')) != NULL)
            *pos = '\0';

        aWord = strtok(str," ");

        if (aWord != NULL && strlen(aWord) > LENGTH)
            aWord = NULL;

        char *temp = aWord + strlen(aWord) - 1;
        char *temp2 = aWord;
        while (ispunct(*temp)) {
            temp++;
        }
        while (ispunct(*temp2) && temp < temp2) { 
            *temp2 = 0; temp2--; 
        }
        aWord=temp;

        while (aWord) {
            if (check_word(aWord, hashtable)) {
                aWord = strtok(NULL, " ");
                char *temp = aWord+ strlen(aWord) - 1;
                char *temp2 = aWord;
                while (ispunct(*temp)) {
                    temp++;
                }
                while (ispunct(*temp2) && temp < temp2) { 
                    *temp2 = 0; temp2--; 
                }
                aWord=temp;
            }
            else {
                if (num_misspelled < MAX_MISSPELLED){
                    misspelled[num_misspelled] = (char *) malloc((LENGTH+1)*sizeof(char));
                    strncpy(misspelled[num_misspelled],aWord,(LENGTH+1));
                    num_misspelled++;
                    aWord = strtok(NULL, " ");
                    if (aWord != NULL){
                        char *temp = aWord+ strlen(aWord) - 1;
                        char *temp2 = aWord;
                        while (ispunct(*temp)) {
                            temp++;
                        }
                        while (ispunct(*temp2) && temp < temp2) { 
                            *temp2 = 0; temp2--; 
                        }
                        aWord=temp;
                    }
                }
                else{
                    return num_misspelled;
                }
            }
        }
    }
    return num_misspelled;
}