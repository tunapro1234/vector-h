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
