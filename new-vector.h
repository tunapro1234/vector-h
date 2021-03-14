#ifndef NVECTOR_H_INCLUDED
#define NVECTOR_H_INCLUDED

#include "main.h"


typedef enum max_output_t {
	MO_FIRST_ARG  =  1,
	MO_ARGS_EQUAL =  0,
	MO_SECOND_ARG = -1,
	MO_COUNT
} max_output_t;

max_output_t s32_max_func(s32* a, s32* b) {
	if (*a > *b) 		return MO_FIRST_ARG ;
	else if (*a == *b) 	return MO_ARGS_EQUAL;
	else 				return MO_SECOND_ARG;
}


#define vector_t(type) \
	struct { type *_start, *_end, *_capacity; }

typedef struct base_vector_t {
    void *_start, *_end, *_capacity;
} base_vector_t;



#define vector_init(type, capacity) \
	(vector_t(type)) _vector_init(sizeof(type) * capacity)

base_vector_t _vector_init(const size_t size) {
    base_vector_t new_vector;
	
	new_vector._start 		= malloc(size);
	new_vector._capacity 	= (char *)new_vector._start + (size);
	new_vector._end 		= new_vector._start;

	return new_vector;
}



#define vector_init_h(type, capacity) \
	(vector_t(type) *) _vector_init_h(sizeof(type) * capacity)

base_vector_t* _vector_init_h(const size_t size) {
    base_vector_t *new_vector = (base_vector_t *)malloc(sizeof(base_vector_t));
	
	new_vector->_start 		= malloc(size);
	new_vector->_capacity 	= (char *)new_vector->_start + size;
	new_vector->_end 		= new_vector->_start;

	return new_vector;
}



#define vector_destroy(type, self) \
	_vector_destroy((base_vector_t *) self)

void _vector_destroy(base_vector_t *self) {
	free(self->_start);
	self->_capacity = NULL;
	self->_start 	= NULL;
	self->_end 		= NULL;
}



#define vector_capacity(type, self)	\
	_vector_capacity((const base_vector_t *)self) / sizeof(type)

size_t _vector_capacity(const base_vector_t *self)
	{ return ((char*)self->_capacity - self->_start); }



#define vector_length(type, self) \
	_vector_length((const base_vector_t *)self) / sizeof(type)

size_t _vector_length(const base_vector_t *self)
	{ return ((char*)self->_end - self->_start); }



#define vector_size(type, self)	\
	vector_size((const base_vector_t *)self) / sizeof(type)

size_t _vector_size(const base_vector_t *self)
	{ return ((char*)self->_end - self->_start); }



#define vector_move_h(type, self) \
	(vector_t(type) *) _vector_move_h(sizeof(type), (base_vector_t *)self)

base_vector_t* _vector_move_h(const size_t type_size, base_vector_t *self) {
	base_vector_t *new_vector = (base_vector_t *)malloc(sizeof(base_vector_t));
	
	new_vector->_capacity 	= self->_capacity;
	new_vector->_start 		= self->_start;
	new_vector->_end 		= self->_end;
	
	self->_capacity 		= NULL;
	self->_start 			= NULL;
	self->_end 				= NULL;
	return new_vector;
}



#define vector_move(type, self) \
	(vector_t(type) *) _vector_move((base_vector_t *)self)

base_vector_t _vector_move(base_vector_t *self) {
	base_vector_t new_vector;
	
	new_vector._capacity 	= self->_capacity;
	new_vector._start 		= self->_start;
	new_vector._end 		= self->_end;
	
	self->_capacity 		= NULL;
	self->_start 			= NULL;
	self->_end 				= NULL;
	return new_vector;
}



#define vector_copy_h(type, self) \
	(vector_t(type) *) _vector_copy_h((const base_vector_t *)self)

base_vector_t* _vector_copy_h(const base_vector_t *self) {
	size_t length = _vector_length(self);
	base_vector_t *new_vector = _vector_init_h(_vector_capacity(self));
	memcpy(new_vector->_start, self->_start, _vector_capacity(self));
	new_vector->_end = (char *)new_vector->_start + length;
	return new_vector;
}



#define vector_copy(type, self) \
	(vector_t(type) *) _vector_copy((const base_vector_t *)self)

base_vector_t _vector_copy(const base_vector_t *self) {
	size_t length = ((char *)self->_end - self->_start);
	base_vector_t new_vector = _vector_init(_vector_capacity(self));
	memcpy(new_vector._start, self->_start, _vector_capacity(self));
	new_vector._end = (char *)new_vector._start + length;
	return new_vector;
}







#endif