/Users/maggiedong/coen12/project3/generic/table.c/*
 * Maggie Dong
 * Project #3
 * October 12th, 2017
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "set.h"
#include <assert.h>
#define EMPTY 0
#define FILLED 1
#define DELETED 2

struct set{
	int count; //num of elements in set
	int length; //max capacity of set
	char **elts; //dynamic array to hold strings
	char *flags; //array of flags
};

//O(n)  
SET *createSet(int maxElts){
   	SET *sp;
   	sp = malloc(sizeof(SET));
   	assert(sp != NULL);  //verifies that sp is not null
   	sp->count = 0;
   	sp->length = maxElts;
   	sp->elts = malloc(sizeof(char*)*maxElts);  //allocates memory for elts
   	assert(sp->elts != NULL);
	sp->flags = malloc(sizeof(char)*maxElts);  //allocates memory for flags
   	return sp;
}

//O(n)
void destroySet(SET *sp){
	assert(sp != NULL);
	int i = 0;
	for(i = 0; i < sp->count; i++){
		free(sp->elts[i]);  //deallocates the words in the array
	}
	for(i = 0; i < sp->length; i++){
		free(sp->flags[i];  //deallocates the flags
	}
	free(sp->elts);  //deallocates array
	free(sp->flags);  //deallocates array
	free(sp);  //deallocates set
}

//O(1)
int numElements(SET *sp){
	return (sp->count);  //returns num of elements
}





