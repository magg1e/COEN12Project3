/*
 *Maggie Dong
 * Project #2
 * October 5th, 2017 
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "set.h"
#include <assert.h>

unsigned strhash(char*s) {
         unsigned hash = 0;
 
         while (*s != '\0')
                 hash = 31*hash +*s ++;
 
         return hash;
}


struct set{
   	int count;  //num of elements in set
   	int length;  //max capacity of set
   	char **elts;  //dynamic array to hold strings
	char *flags;  //array to hold flags
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
	int i = 0;
	for(i = 0; i < maxElts; i++){  //initialize flags to empty 'E'
		sp->flags[i] = 'E';
	}
   	return sp;
}

//O(n)
void destroySet(SET *sp){
	assert(sp != NULL);
	int i = 0;
	for(i = 0; i < sp->count; i++){
		free(sp->elts[i]);  //deallocates the words in the array
	}
	free(sp->elts);  //deallocates array
	free(sp);  //deallocates set
	free(sp->flags);  //deallocates flags
}

//O(1)
int numElements(SET *sp){
	return (sp->count);  //returns num of elements
}

//O(n), O(1) expected
static int search(SET *sp, char *elt){
	assert(sp != NULL && elt != NULL);
	int i = 0;	
	for(int i = 0; i < sp->length; i++){
		int index = (strhash(elt) + i) % sp->length;  //get key from strhash/linear probe
		if(sp->flags[index] == 'E'){
			return (-1);  //if empty, not there
		}else if(sp->flags[index] == 'F'){
			if(strcmp(sp->elts[index], elt) == 0){
				return index;  //if elt is there, return key
			} 
		}else if(sp->flags[index] == 'D'){  //if deleted, keep going
		}
	}
	return (-1);
}

//O(n), O(1) expected
void addElement(SET *sp, char *elt){
   	assert(sp != NULL && elt != NULL);
   	if(sp->count == sp->length){ 
	     //cant add word if at max capacity
   	}   
   	if(search(sp, elt) != -1){
	     //if word exists in array, cant be added
   	}
	else{
		int i = 0;
		for(int i = 0; i < sp->length; i++){
			int index = (strhash(elt) + i) % sp->length;  //get key/linear probe            
			if(sp->flags[index] == 'E'){	
				sp->elts[index] = strdup(elt);
				//allocates memory, copies string and returns pointer
				sp->flags[index] = 'F';
			}else if(sp->flags[index] == 'D'){
				sp->elts[index] = strdup(elt);  
				//allocates memory, copies string and returns pointer
				sp->flags[index] = 'F';
			}
		}
		(sp->count)++;
	}
}

//O(n), O(1) expected
void removeElement(SET *sp, char *elt){
	assert(sp != NULL && elt != NULL);
	if(search(sp, elt) == -1){
	    //if word not in array, can't be removed
	}
	else{
		int i = 0;
		for(int i = 0; i < sp->count; i++){
			int index = (strhash(elt) + i) % sp->length;  //get key/linear probe
			if(sp->flags[index] == 'F'){
                        	if(strcmp(sp->elts[index], elt) == 0){
                                	free(sp->elts[index]);  //deallocate memory for word
					sp->flags[index] = 'D';
					(sp->count)--;
				}
			}
		}
	}
}

//O(n)
char *findElement(SET *sp, char *elt){
   	assert(sp != NULL && elt != NULL);
	if(search(sp, elt) == -1){  //if word not in array, return NULL
		return NULL;
	}
	else{
		int x = search(sp, elt);  //else return matching element
		return (sp->elts[x]);
	}
}

//O(n)
char **getElements(SET *sp){
	assert(sp != NULL);
	char **copy;  //create copy
	int i,j;
	copy = malloc(sizeof(char *)*sp->count);  //allocate memory for copy
	assert(copy != NULL);
	for(i = 0, j = 0; i < sp->length; i ++){
		if (sp->flags[i] == 'F'){
			copy[j++] = sp->elts[i];  //if filled, add the word to copy 
		}
	}
	return copy;
}



