#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include "dictionary.h"

bool load_dictionary(const char* dictionary_file, hashmap_t hashtable[]){

	for(int k = 0; k < HASH_SIZE; k++){
		// free(hashtable[k]);
		hashtable[k] = NULL;
	}

	char str[LENGTH];

	FILE *fp;
	fp = fopen(dictionary_file, "r");
	if (fp == NULL){
		printf("Could not open file %s", dictionary_file);
		return false;
	}

	int count = 0
	while (fgets(str, LENGTH, fp) != NULL){
    	node *aNode = malloc(sizeof(node));
        strnpy(aNode->word, line, LENGTH)
    	aNode.next = NULL;

    	int index = hash_function(str);

    	if (hashtable[index] == NULL){
    		hashtable[index] = aNode;
    	}
    	else{
    		node *tmp = hashtable[index];
    		while (tmp != NULL)
    		{
    			if (tmp->next == NULL)
    			{
    				break;
    			}
    			tmp = tmp->next;
    		}
    		tmp->next = aNode;
    	}
    	count++;
    }
    fclose(fp);

}
