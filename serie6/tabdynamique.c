#include <stdio.h>
#include <stdlib.h>

/* Created by Valentin Garnier - PROGOS Course */

typedef int type_el;

typedef struct {
	size_t size;
	size_t allocated;
	type_el* content;
} vector;

//INITIALISATION

#define VECTOR_PADDING 128
vector* vector_construct(vector* v) {
	vector* result = v;

	if(result != NULL) {
		result.content = calloc(VECTOR_PADDING, sizeof(type_el));
		
		if(result.content != NULL) {
			result.size = 0;
			result -> allocated = VECTOR_PADDING;
		} else {
			result = NULL;
		}
	}
return result;
}