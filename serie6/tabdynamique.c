#include <stdio.h>
#include <stdlib.h>

/* Created by Valentin Garnier - PROGOS Course */

typedef int type_el;

typedef struct {
	size_t size;
	size_t allocated;
	type_el* content;
} vector;

int main(void) {

printf("test \n");
return 0;
}

//INITIALISATION
#define VECTOR_PADDING 128
vector* vector_construct(vector* v) {
	vector* result = v;

	if(result != NULL) {
		(*result).content = calloc(VECTOR_PADDING, sizeof(type_el));
		
		if((*result).content != NULL) {
			(*result).size = 0;
			(*result).allocated = VECTOR_PADDING;
		} else {
			result = NULL;
		}
	}
return result;
}

//DESTRUCTION
void vector_destruct(vector* v) {
	if((v != NULL) && (v->content != NULL)) {
		free((*v).content);
		(*v).content = NULL;
		(*v).size = 0;
		(*v).allocated = 0;
	}
}

//AJOUT D'UN ELEMENT
size_t add_element(vector* vect, type_el element) {
 	if(vect != NULL) {
 		if(vect->size )
 	(*vect).content[(*vect).size] = element;
 	++((*vect).size);

 	return (*vect).size;
 }
 else { return 0; }
}

type_el change_value(vector* vect, size_t index, type_el newValue) {
	if(vect != NULL) {
		(*vect).content[index] = newValue;
		return newValue;
	} else {
		return 0;
	}	
}

type_el read_value(vector* vect, size_t index) {
	if(vect != NULL) {
		type_el result = (*vect).content[index];
		return result;
	}
	else {
		return 0;
	}
}

//ENLARGE








