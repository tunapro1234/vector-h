#include "../main.h"

typedef struct vector_int_t{
	int *start, *end, *capacity;
} vector_int_t;

/********************************************************************************/

vector_int_t* vector_int_init_h(size_t capacity);
vector_int_t vector_int_init(size_t capacity);

void* vector_int_destroy(vector_int_t *self);

size_t vector_int_capacity(const vector_int_t *self);
size_t vector_int_length(const vector_int_t *self);
size_t vector_int_size(const vector_int_t *self);

vector_int_t* vector_int_move_h(vector_int_t *self);
vector_int_t vector_int_move(vector_int_t *self);
vector_int_t* vector_int_copy_h(const vector_int_t *self);
vector_int_t vector_int_copy(const vector_int_t *self);

bool vector_int_extend_capacity(vector_int_t *self);
bool vector_int_push_back(vector_int_t *self, int data);
bool vector_int_p_push_back(vector_int_t *self, int *data);

int *vector_int_get(vector_int_t *self, size_t index);
int vector_int_read(const vector_int_t *self, size_t index);
const int *vector_int_p_read(const vector_int_t *self, size_t index);

/********************************************************************************/

// indexe ekleme, ters çevirme, sıralama, swap

void vector_int_swap_indexes(vector_int_t *self, size_t index1, size_t index2) {
	int tmp = *vector_int_get(self, index1);
	*vector_int_get(self, index1) = *vector_int_get(self, index2);
	*vector_int_get(self, index2) = tmp;
}

bool vector_int_insert_p(vector_int_t *self, size_t index, int *value) {
	if (self->end == self->capacity){
		if (vector_int_extend_capacity(self) == False)
			return False;
	}
	size_t length = vector_int_length(self);
	for (int i = length-1; i >= index; i--)
		*vector_int_get(self, i+1) = *vector_int_get(self, i);
	memcpy(vector_int_get(self, index), value, sizeof(int));
	self->end++;
	return True;
}

bool vector_int_insert(vector_int_t *self, size_t index, int value) {
	if (self->end == self->capacity){
		if (vector_int_extend_capacity(self) == False)
			return False;
	}
	size_t length = vector_int_length(self);
	for (int i = length-1; i >= index; i--)
		*vector_int_get(self, i+1) = *vector_int_get(self, i);
	*vector_int_get(self, index) = value;
	self->end++;
	return True;
}

void vector_int_shift_r(vector_int_t *self) {
	size_t last_index = vector_int_length(self)-1;
	int tmp = *vector_int_get(self, last_index);
	for (int i = last_index-1; i >= 0; i--)
		*vector_int_get(self, i+1) = *vector_int_get(self, i);
	*vector_int_get(self, 0) = tmp;
}

void vector_int_shift_l(vector_int_t *self) {
	size_t length = vector_int_length(self);
	int tmp = *vector_int_get(self, 0);
	for (int i = 1; i < length; i++)
		*vector_int_get(self, i-1) = *vector_int_get(self, i);
	*vector_int_get(self, length-1) = tmp;
}


/********************************************************************************/


vector_int_t* vector_int_init_h(size_t capacity) {
	vector_int_t *new_vector = (vector_int_t *)malloc(sizeof(vector_int_t)); 
	
	new_vector->start 		= (int *)malloc(sizeof(int) * capacity);
	new_vector->capacity	= new_vector->start + capacity;
	new_vector->end			= new_vector->start;
	return new_vector;
}

vector_int_t vector_int_init(size_t capacity) {
	vector_int_t new_vector;
	
	new_vector.start 		= (int *)malloc(sizeof(int) * capacity);
	new_vector.capacity		= new_vector.start + capacity;
	new_vector.end			= new_vector.start;
	return new_vector;
}

void* vector_int_destroy(vector_int_t *self) { 
	free(self->start);
	free(self);
}

size_t vector_int_capacity(const vector_int_t *self) { return self->capacity - self->start; }

size_t vector_int_length(const vector_int_t *self) { return self->end - self->start; }

size_t vector_int_size(const vector_int_t *self) { return self->end - self->start; }

vector_int_t* vector_int_move_h(vector_int_t *self) {
	vector_int_t *new_vector = (vector_int_t *)malloc(sizeof(vector_int_t));

	new_vector->capacity = self->capacity;
	new_vector->start = self->start;
	new_vector->end = self->end;

	self->capacity = NULL;
	self->start = NULL;
	self->end = NULL;

	return new_vector;
}

vector_int_t vector_int_move(vector_int_t *self) {
	vector_int_t new_vector;

	new_vector.capacity = self->capacity;
	new_vector.start = self->start;
	new_vector.end = self->end;

	self->capacity = NULL;
	self->start = NULL;
	self->end = NULL;

	return new_vector;
}

vector_int_t* vector_int_copy_h(const vector_int_t *self) {
	size_t length = vector_int_length(self);
	vector_int_t *new_vector = vector_int_init_h(vector_int_capacity(self));
	memcpy(new_vector->start, self->start, vector_int_capacity(self) * sizeof(int));
	new_vector->end = new_vector->start + length;
	return new_vector;
}

vector_int_t vector_int_copy(const vector_int_t *self) {
	size_t length = vector_int_length(self);
	vector_int_t new_vector = vector_int_init(vector_int_capacity(self));
	memcpy(new_vector.start, self->start, vector_int_capacity(self) * sizeof(int));
	new_vector.end = new_vector.start + length;
	return new_vector;
}

bool vector_int_extend_capacity(vector_int_t *self) {
	size_t new_capacity = vector_int_capacity(self) * 2;
	size_t length 		= vector_int_length(self);

	void *tmp = realloc(self->start, new_capacity * sizeof(int));
	if (tmp == NULL) return False;

	self->start 	= (int *)tmp;
	self->capacity 	= self->start + new_capacity;
	self->end 		= self->start + length;
	return True;
}

bool vector_int_push_back(vector_int_t *self, int data) {
	if (self->end == self->capacity){
		if (vector_int_extend_capacity(self) == False)
			return False;
	}
	*self->end = data;
	self->end++;
	return True;
}

bool vector_int_p_push_back(vector_int_t *self, int *data) {
	if (self->end == self->capacity){
		if (vector_int_extend_capacity(self) == False)
			return False;
	}
	memcpy(self->end, data, sizeof(int));
	self->end++;
	return True;
}

int *vector_int_get(vector_int_t *self, size_t index) { return self->start + index; }

int vector_int_read(const vector_int_t *self, size_t index) { return *(self->start + index); }

const int *vector_int_p_read(const vector_int_t *self, size_t index) { return self->start + index; }
