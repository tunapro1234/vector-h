#include "../../main.h"

/*
 * unit test için kütüphane bul ya da kendin yaz (vs code desteklerse daha iyi)
 * -ansi -pedantic -Wall iken çıkan warningleri düzelt
 * kütüphane için kuruluma başla
 * folder düzenle
 * merge sort
 * (binary ve linear) find
 * 
 * debug ve release olarak ikiye ayır
 * POINTERLER İÇİN VECTOR OLUŞTURAMIYORUZ
 * 		create_vector_t(NAME, TYPE) yapıcam
 * 
 * sona noktalı virgül gelmesini sağlamam lazım
 */

typedef struct vector_int{	
	int *start, *end, *capacity;	
} vector_int;				

vector_int* vector_int_init_h(size_t capacity); 
vector_int vector_int_init(size_t capacity); 	
void vector_int_destroy(vector_int *self); 	

size_t vector_int_capacity(const vector_int *self); 
size_t vector_int_length(const vector_int *self); 	
size_t vector_int_size(const vector_int *self); 	

vector_int* vector_int_move_h(vector_int *self); 		
vector_int vector_int_move(vector_int *self); 			
vector_int* vector_int_copy_h(const vector_int *self);	
vector_int vector_int_copy(const vector_int *self); 		

bool vector_int_extend_capacity(vector_int *self); 			
bool vector_int_push_back(vector_int *self, int data); 	
bool vector_int_p_push_back(vector_int *self, int *data); 	

int *vector_int_get(vector_int *self, size_t index); 		
int vector_int_read(const vector_int *self, size_t index); 


void vector_int_bubble_sort(vector_int *self, int* (*key_func)(int*, int*));	
void vector_int_swap(vector_int *self, size_t index1, size_t index2);			
bool vector_int_insert_p(vector_int *self, size_t index, int *value);			
bool vector_int_insert(vector_int *self, size_t index, int value);				

void vector_int_shift_r(vector_int *self);	
void vector_int_shift_l(vector_int *self);	
void vector_int_reverse(vector_int *self);	

/********************************************************************************/	

vector_int* vector_int_init_h(size_t capacity) { 									
	vector_int *new_vector = (vector_int *)malloc(sizeof(vector_int));  	
	
	new_vector->start 		= (int *)malloc(sizeof(int) * capacity); 							
	new_vector->capacity	= new_vector->start + capacity; 									
	new_vector->end			= new_vector->start; 												
	return new_vector; 																			
}	

vector_int vector_int_init(size_t capacity) { 
	vector_int new_vector; 										
	
	new_vector.start 		= (int *)malloc(sizeof(int) * capacity); 	
	new_vector.capacity		= new_vector.start + capacity; 				
	new_vector.end			= new_vector.start; 						
	return new_vector; 													
} 	

void vector_int_destroy(vector_int *self) {  	
	free(self->start); 										
} 	

size_t vector_int_capacity(const vector_int *self) { return self->capacity - self->start; } 
size_t vector_int_length(const vector_int *self) { return self->end - self->start; } 		
size_t vector_int_size(const vector_int *self) { return self->end - self->start; } 			

vector_int* vector_int_move_h(vector_int *self) { 						
	vector_int *new_vector = (vector_int *)malloc(sizeof(vector_int)); 
	new_vector->capacity = self->capacity; 													
	new_vector->start = self->start; 														
	new_vector->end = self->end; 															
	self->capacity = NULL; 																	
	self->start = NULL; 																	
	self->end = NULL; 																		
	return new_vector; 																		
} 	

vector_int vector_int_move(vector_int *self) { 
	vector_int new_vector; 			
	new_vector.capacity = self->capacity; 	
	new_vector.start = self->start; 		
	new_vector.end = self->end; 			
	self->capacity = NULL; 					
	self->start = NULL; 					
	self->end = NULL; 						
	return new_vector; 						
} 	

vector_int* vector_int_copy_h(const vector_int *self) { 					
	size_t length = vector_int_length(self); 											
	vector_int *new_vector = vector_int_init_h(vector_int_capacity(self)); 
	memcpy(new_vector->start, self->start, vector_int_capacity(self) * sizeof(int)); 	
	new_vector->end = new_vector->start + length; 											
	return new_vector; 																		
} 	

vector_int vector_int_copy(const vector_int *self) { 					
	size_t length = vector_int_length(self); 											
	vector_int new_vector = vector_int_init(vector_int_capacity(self)); 	
	memcpy(new_vector.start, self->start, vector_int_capacity(self) * sizeof(int)); 	
	new_vector.end = new_vector.start + length; 											
	return new_vector; 																		
} 	

bool vector_int_extend_capacity(vector_int *self) { 	
	size_t new_capacity = vector_int_capacity(self) * 2; 		
	size_t length 		= vector_int_length(self); 			
	
	void *tmp = realloc(self->start, new_capacity * sizeof(int)); 	
	if (tmp == NULL) return False; 									
	
	self->start 	= (int *)tmp; 					
	self->capacity 	= self->start + new_capacity; 	
	self->end 		= self->start + length; 		
	return True; 									
} 	

bool vector_int_push_back(vector_int *self, int data) { 	
	if (self->end == self->capacity){ 									
		if (vector_int_extend_capacity(self) == False) 			
			return False; 												
	} 																	
	*self->end = data; 													
	self->end++; 														
	return True; 														
} 	

bool vector_int_p_push_back(vector_int *self, int *data) { 
	if (self->end == self->capacity){ 									
		if (vector_int_extend_capacity(self) == False) 			
			return False; 												
	} 																	
	memcpy(self->end, data, sizeof(int)); 								
	self->end++; 														
	return True; 														
} 	

int *vector_int_get(vector_int *self, size_t index) { return self->start + index; } 			
int vector_int_read(const vector_int *self, size_t index) { return *(self->start + index); } 	


void vector_int_swap(vector_int *self, size_t index1, size_t index2) {	
	int tmp = *vector_int_get(self, index1);									
	*vector_int_get(self, index1) = *vector_int_get(self, index2);		
	*vector_int_get(self, index2) = tmp;										
}	

bool vector_int_insert_p(vector_int *self, size_t index, int *value) {	
	size_t i, length;																
	if (self->end == self->capacity)												
		if (vector_int_extend_capacity(self) == False)							
			return False;															
	
	length = vector_int_length(self);											
	for (i = length-1; i >= index; i--)												
		*vector_int_get(self, i+1) = *vector_int_get(self, i);			
	memcpy(vector_int_get(self, index), value, sizeof(int));					
	self->end++;																	
	return True;																	
}	

bool vector_int_insert(vector_int *self, size_t index, int value) {	
	size_t i, length;																
	if (self->end == self->capacity)												
		if (vector_int_extend_capacity(self) == False)							
			return False;															
	
	length = vector_int_length(self);											
	for (i = length-1; i >= index; i--)												
		*vector_int_get(self, i+1) = *vector_int_get(self, i);			
	*vector_int_get(self, index) = value;										
	self->end++;																	
	return True;																	
}	

void vector_int_shift_r(vector_int *self) {						
	size_t i, last_index = vector_int_length(self)-1;					
	int tmp = *vector_int_get(self, last_index);						
	for (i = last_index-1; i >= 0; i--)										
		*vector_int_get(self, i+1) = *vector_int_get(self, i);	
	*vector_int_get(self, 0) = tmp;									
}	

void vector_int_shift_l(vector_int *self) {						
	size_t i, length = vector_int_length(self);						
	int tmp = *vector_int_get(self, 0);								
	for (i = 1; i < length; i++)											
		*vector_int_get(self, i-1) = *vector_int_get(self, i);	
	*vector_int_get(self, length-1) = tmp;								
}	

void vector_int_reverse(vector_int *self) {	
	size_t i, length = vector_int_length(self);	
	for (i = 0; i < length/2; i++)						
		vector_int_swap(self, i, length-1-i);		
}	

void vector_int_bubble_sort(vector_int *self, int* (*key_func)(int*, int*)){								
	size_t i, j, last_index = vector_int_length(self)-1;																
	for (i = 0; i < last_index; i++)																						
		for (j = 0; j < last_index-i; j++)																					
			if ( vector_int_get(self, j) == key_func(vector_int_get(self, j), vector_int_get(self, j+1)) )	
				vector_int_swap(self, j, j+1);																			
}	