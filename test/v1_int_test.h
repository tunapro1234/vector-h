#include "../main.h"

/*
 * max_output_type_t sil?
 * malloc için exception handling (whgbkvugkz)
 * debug ve release olarak ikiye ayır (augbvnukb)
 * 
 */

typedef enum max_output_t {
	MO_FIRST_ARG=1,
	MO_ARGS_EQUAL=0,
	MO_SECOND_ARG=-1,
	MO_COUNT
} max_output_t;


max_output_t s32_max_func(s32* a, s32* b) {
	if (*a > *b) 		return MO_FIRST_ARG ;
	else if (*a == *b) 	return MO_ARGS_EQUAL;
	else 				return MO_SECOND_ARG;
}

typedef struct vector_int_t{								
	int *_start, *_end, *_capacity;				
} vector_int_t; 											

vector_int_t* vector_int_t_init_h(size_t capacity); 				
vector_int_t vector_int_t_init(size_t capacity); 					
void vector_int_t_destroy(vector_int_t *self); 					

size_t vector_int_t_capacity(const vector_int_t *self); 			
size_t vector_int_t_length(const vector_int_t *self); 			
size_t vector_int_t_size(const vector_int_t *self); 				

vector_int_t* vector_int_t_move_h(vector_int_t *self); 					
vector_int_t vector_int_t_move(vector_int_t *self); 						
vector_int_t* vector_int_t_copy_h(const vector_int_t *self);				
vector_int_t vector_int_t_copy(const vector_int_t *self); 				

bool vector_int_t_extend_capacity(vector_int_t *self); 			
bool vector_int_t_push_back(vector_int_t *self, int data); 		
bool vector_int_t_push_back_p(vector_int_t *self, int *data); 	

int *vector_int_t_get(vector_int_t *self, size_t index); 		
int vector_int_t_read(const vector_int_t *self, size_t index); 	


void vector_int_t_swap(vector_int_t *self, size_t index1, size_t index2);		
bool vector_int_t_insert_p(vector_int_t *self, size_t index, int *value);	
bool vector_int_t_insert(vector_int_t *self, size_t index, int value);		

void vector_int_t_shift_r(vector_int_t *self);	
void vector_int_t_shift_l(vector_int_t *self);	
void vector_int_t_reverse(vector_int_t *self);	


void __inter_vector_int_t_sort_merge	
(vector_int_t *self, size_t arr_start, size_t arr_length, max_output_t (*max_func)(int*, int*));			

void vector_int_t_sort_merge(vector_int_t *self, max_output_t (*max_func)(int*, int*));							
void vector_int_t_sort_bubble(vector_int_t *self, max_output_t (*max_func)(int*, int*));						


size_t vector_int_t_search_binary														
(vector_int_t *self, int target, max_output_t (*max_func)(int*, int*));		

size_t vector_int_t_search_binary_p													
(vector_int_t *self, int *target, max_output_t (*max_func)(int*, int*));		

size_t vector_int_t_search_linear														
(vector_int_t *self, int target, max_output_t (*max_func)(int*, int*));				

size_t vector_int_t_search_linear_p													
(vector_int_t *self, int *target, max_output_t (*max_func)(int*, int*));				

/****************************************************************************************************/	

vector_int_t* vector_int_t_init_h(size_t capacity) { 										
	vector_int_t *new_vector = (vector_int_t *)malloc(sizeof(vector_int_t)); 						
	
	new_vector->_start 		= (int *)malloc(sizeof(int) * capacity); 		
	new_vector->_capacity	= new_vector->_start + capacity; 				
	new_vector->_end		= new_vector->_start; 							
	return new_vector; 														
}	

vector_int_t vector_int_t_init(size_t capacity) { 										
	vector_int_t new_vector; 														
	
	new_vector._start 		= (int *)malloc(sizeof(int) * capacity); 		
	new_vector._capacity		= new_vector._start + capacity; 			
	new_vector._end			= new_vector._start; 							
	return new_vector; 														
} 	

void vector_int_t_destroy(vector_int_t *self) { 			
	free(self->_start); 					
} 	

size_t vector_int_t_capacity(const vector_int_t *self) { return self->_capacity - self->_start; }	
size_t vector_int_t_length(const vector_int_t *self) 	 { return self->_end - self->_start; 	  }	
size_t vector_int_t_size(const vector_int_t *self) 	 { return self->_end - self->_start; 	  }	

vector_int_t* vector_int_t_move_h(vector_int_t *self) { 						
	vector_int_t *new_vector = (vector_int_t *)malloc(sizeof(vector_int_t)); 	
	new_vector->_capacity = self->_capacity; 			
	new_vector->_start = self->_start; 					
	new_vector->_end = self->_end; 						
	self->_capacity = NULL; 							
	self->_start = NULL; 								
	self->_end = NULL; 									
	return new_vector; 									
} 	

vector_int_t vector_int_t_move(vector_int_t *self) {							
	vector_int_t new_vector; 							 		
	new_vector._capacity = self->_capacity; 			
	new_vector._start = self->_start; 					
	new_vector._end = self->_end; 						
	self->_capacity = NULL; 							
	self->_start = NULL; 								
	self->_end = NULL; 									
	return new_vector; 									
} 	

vector_int_t* vector_int_t_copy_h(const vector_int_t *self) { 												
	size_t length = vector_int_t_length(self); 												
	vector_int_t *new_vector = vector_int_t_init_h(vector_int_t_capacity(self)); 							
	memcpy(new_vector->_start, self->_start, vector_int_t_capacity(self) * sizeof(int)); 	
	new_vector->_end = new_vector->_start + length; 									
	return new_vector; 																	
} 	

vector_int_t vector_int_t_copy(const vector_int_t *self) { 												
	size_t length = vector_int_t_length(self); 											
	vector_int_t new_vector = vector_int_t_init(vector_int_t_capacity(self)); 							
	memcpy(new_vector._start, self->_start, vector_int_t_capacity(self) * sizeof(int));	
	new_vector._end = new_vector._start + length; 									
	return new_vector; 																
} 	

bool vector_int_t_extend_capacity(vector_int_t *self) { 							
	size_t new_capacity = vector_int_t_capacity(self) * 2; 				
	size_t length 		= vector_int_t_length(self); 						
	
	void *tmp = realloc(self->_start, new_capacity * sizeof(int)); 
	if (tmp == NULL) return False; 									
	
	self->_start 	= (int *)tmp; 									
	self->_capacity 	= self->_start + new_capacity; 				
	self->_end 		= self->_start + length; 						
	return True; 													
} 	

bool vector_int_t_push_back(vector_int_t *self, int data) { 			
	if (self->_end == self->_capacity) 					
		if (vector_int_t_extend_capacity(self) == False) 		
			return False; 								
	
	*self->_end = data; 								
	self->_end++; 										
	return True; 										
} 	

bool vector_int_t_push_back_p(vector_int_t *self, int *data) { 		
	if (self->_end == self->_capacity)					
		if (vector_int_t_extend_capacity(self) == False) 		
			return False; 								
	
	memcpy(self->_end, data, sizeof(int)); 			
	self->_end++; 										
	return True; 										
} 	

int *vector_int_t_get(vector_int_t *self, size_t index) 		 { return 	self->_start + index ; } 	
int vector_int_t_read(const vector_int_t *self, size_t index) { return *(self->_start + index); }	


void vector_int_t_swap(vector_int_t *self, size_t index1, size_t index2) {	
	int tmp = *vector_int_t_get(self, index1);						
	*vector_int_t_get(self, index1) = *vector_int_t_get(self, index2);		
	*vector_int_t_get(self, index2) = tmp;							
}	

bool vector_int_t_insert_p(vector_int_t *self, size_t index, int *value) {	
	size_t i, length;											
	if (self->_end == self->_capacity)							
		if (vector_int_t_extend_capacity(self) == False)				
			return False;										
	
	length = vector_int_t_length(self);								
	for (i = length; i > index; i--)							
		*(self->_start + i) = *(self->_start + i - 1);			
	memcpy(vector_int_t_get(self, index), value, sizeof(int));		
	self->_end++;												
	return True;												
}	

bool vector_int_t_insert(vector_int_t *self, size_t index, int value) {		
	size_t i, length;											
	if (self->_end == self->_capacity)							
		if (vector_int_t_extend_capacity(self) == False)				
			return False;										
	
	length = vector_int_t_length(self);								
	for (i = length; i > index; i--)							
		*(self->_start + i) = *(self->_start + i - 1);			
	*vector_int_t_get(self, index) = value;							
	self->_end++;												
	return True;												
}	

void vector_int_t_shift_r(vector_int_t *self) {								
	size_t i, last_index = vector_int_t_length(self)-1;				
	int tmp = *vector_int_t_get(self, last_index);					
	for (i = last_index; i > 0; i--)							
		*vector_int_t_get(self, i) = *vector_int_t_get(self, i-1);			
	*vector_int_t_get(self, 0) = tmp;									
}	

void vector_int_t_shift_l(vector_int_t *self) {								
	size_t i, length = vector_int_t_length(self);						
	int tmp = *vector_int_t_get(self, 0);							
	for (i = 1; i < length; i++)								
		*vector_int_t_get(self, i-1) = *vector_int_t_get(self, i);			
	*vector_int_t_get(self, length-1) = tmp;							
}	

void vector_int_t_reverse(vector_int_t *self) {								
	size_t i, length = vector_int_t_length(self);						
	for (i = 0; i < length/2; i++)								
		vector_int_t_swap(self, i, length-1-i);						
}	

void __inter_vector_int_t_sort_merge																
(vector_int_t *self, size_t arr_start, size_t arr_length, max_output_t (*max_func)(int*, int*)) {		
	size_t i = 0, li = 0, ri = 0, mid_point = 0;	
	int *left_temp, *right_temp; 					
	max_output_t rv; 								
	
	if (arr_start == arr_length-1) return;	 /* 1 eleman kalinca bitir */ 	
	mid_point = arr_start + (arr_length - arr_start) / 2; /* l+(r-l)/2 */ 	
	
	__inter_vector_int_t_sort_merge(self, arr_start, mid_point , max_func);		
	__inter_vector_int_t_sort_merge(self, mid_point, arr_length, max_func);		
	
	left_temp  = (int *)malloc(sizeof(int) * (mid_point - arr_start ));	
	right_temp = (int *)malloc(sizeof(int) * (arr_length - mid_point));	
	
	memcpy(left_temp,  self->_start + arr_start, sizeof(int) * (mid_point  - arr_start));	
	memcpy(right_temp, self->_start + mid_point, sizeof(int) * (arr_length - mid_point));	
	
	for (i = arr_start; li < (mid_point - arr_start) && ri < (arr_length - mid_point);) {	
		rv = max_func(&left_temp[li], &right_temp[ri]); 	
		if (rv == MO_FIRST_ARG) { 							
			*vector_int_t_get(self, i) = right_temp[ri]; 			
			ri++; i++; 										
		} else if (rv == MO_ARGS_EQUAL) { 					
			*vector_int_t_get(self, i) = left_temp[li]; 			
			li++; i++; 										
			*vector_int_t_get(self, i) = right_temp[ri]; 			
			ri++; i++; 										
		} else { 											
			*vector_int_t_get(self, i) = left_temp[li]; 			
			li++; i++; 										
		} 	
	}	
	
	while (li < (mid_point  - arr_start)) { *vector_int_t_get(self, i) = left_temp[li]; li++; i++;  } 	
	while (ri < (arr_length - mid_point)) { *vector_int_t_get(self, i) = right_temp[ri]; ri++; i++; } 	
	free(left_temp); free(right_temp); 																
} 	

void vector_int_t_sort_merge(vector_int_t *self, max_output_t (*max_func)(int*, int*)) {	
	__inter_vector_int_t_sort_merge(self, 0, vector_int_t_length(self), max_func);		
}	

void vector_int_t_sort_bubble(vector_int_t *self, max_output_t (*max_func)(int*, int*)) {			
size_t i, j, last_index = vector_int_t_length(self)-1;										
for (i = 0; i < last_index; i++)														
	for (j = 0; j < last_index-i; j++)													
		if ( MO_FIRST_ARG == max_func(vector_int_t_get(self, j), vector_int_t_get(self, j+1)) )		
			vector_int_t_swap(self, j, j+1);													
}	

size_t vector_int_t_search_binary														
(vector_int_t *self, int target, max_output_t (*max_func)(int*, int*)) {				
	size_t array_start = 1, array_length = vector_int_t_length(self);					
	size_t mid_point; max_output_t rv;											
	while (array_start <= array_length) {										
		mid_point = (int)(array_start + (array_length - array_start - 2) / 2);	
		rv = max_func(vector_int_t_get(self, mid_point), &target);					
		if (rv == MO_ARGS_EQUAL)												
			return mid_point;													
		else if (rv == MO_FIRST_ARG)											
			array_length = mid_point;											
		else if (rv == MO_SECOND_ARG)											
			array_start = mid_point + 2;										
	} return -1;																
}	

size_t vector_int_t_search_binary_p													
(vector_int_t *self, int *target, max_output_t (*max_func)(int*, int*)) {			
	size_t array_start = 1, array_length = vector_int_t_length(self);					
	size_t mid_point; max_output_t rv;											
	while (array_start <= array_length) {										
		mid_point = (int)(array_start + (array_length - array_start - 2) / 2);	
		rv = max_func(vector_int_t_get(self, mid_point), target);						
		if (rv == MO_ARGS_EQUAL)												
			return mid_point;													
		else if (rv == MO_FIRST_ARG)											
			array_length = mid_point;											
		else if (rv == MO_SECOND_ARG)											
			array_start = mid_point + 2;										
	} return -1;																
}	

size_t vector_int_t_search_linear												
(vector_int_t *self, int target, max_output_t (*max_func)(int*, int*)) {		
	size_t array_start = 0, array_length = vector_int_t_length(self);			
	size_t i; for (i = array_start; i < array_length; i++)				
		if (MO_ARGS_EQUAL == max_func(vector_int_t_get(self, i), &target))	
			return i;							 						
	return -1;															
}	

size_t vector_int_t_search_linear_p											
(vector_int_t *self, int *target, max_output_t (*max_func)(int*, int*)) {	
	size_t array_start = 0, array_length = vector_int_t_length(self);			
	size_t i; for (i = array_start; i < array_length; i++)				
		if (MO_ARGS_EQUAL == max_func(vector_int_t_get(self, i), target))		
			return i;							 						
	return -1;															
}	

struct __internal_you_need_semicolon;