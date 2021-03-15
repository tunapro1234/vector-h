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
	(vector_t(type))_vector_init(sizeof(type) * capacity)

base_vector_t _vector_init(size_t size);



#define vector_init_h(type, capacity) \
	(vector_t(type) *)_vector_init_h(sizeof(type) * capacity)

base_vector_t* _vector_init_h(size_t size);



#define vector_destroy(type, self) \
	_vector_destroy((base_vector_t *)self)

void _vector_destroy(base_vector_t *self);



#define vector_capacity(type, self)	\
	_vector_capacity((const base_vector_t *)self) / sizeof(type)

size_t _vector_capacity(const base_vector_t *self);



#define vector_length(type, self) \
	_vector_length((const base_vector_t *)self) / sizeof(type)

size_t _vector_length(const base_vector_t *self);



#define vector_size(type, self)	\
	vector_size((const base_vector_t *)self) / sizeof(type)

size_t _vector_size(const base_vector_t *self);



#define vector_move_h(type, self) \
	(vector_t(type) *)_vector_move_h(sizeof(type), (base_vector_t *)self)

base_vector_t* _vector_move_h(size_t type_size, base_vector_t *self);



#define vector_move(type, self) \
	(vector_t(type) *)_vector_move((base_vector_t *)self)

base_vector_t _vector_move(base_vector_t *self);



#define vector_copy_h(type, self) \
	(vector_t(type) *)_vector_copy_h((const base_vector_t *)self)

base_vector_t* _vector_copy_h(const base_vector_t *self);



#define vector_copy(type, self) \
	(vector_t(type) *)_vector_copy((const base_vector_t *)self)

base_vector_t _vector_copy(const base_vector_t *self);



#define vector_extend_capacity(type, self) \
	_vector_extend_capacity((base_vector_t *)self)

#define _vector_extend_capacity(self) \
	_vector_resize(self, _vector_capacity(self) * 2)


#define vector_resize(type, self, size) \
	_vector_resize((base_vector_t *)self, size)

bool _vector_resize(base_vector_t *self, size_t size);



/* rvalue alabilmek için makro olmalı */
#define vector_push_back(type, self, data) ({				\
	if (self->_end == self->_capacity)						\
		if (vector_extend_capacity(type, self) == False)	\
			False;											\
	\
	*(type *)self->_end = data; 							\
	self->_end = (char *)self->_end + sizeof(type);			\
	True;													\
})



#define vector_push_back_p(type, self, data) \
	_vector_push_back_p(sizeof(type), (base_vector_t *)self, (const void *)data)

bool _vector_push_back_p(size_t type_size, base_vector_t *self, const void* data);



#define vector_get(type, self, index) \
	(type *)_vector_get(sizeof(type), (base_vector_t *)self, index)

void* _vector_get(size_t type_size, base_vector_t *self, size_t index);


#define vector_read(type, self, index) \
	*(type *)((char *)self->_start + (index * sizeof(type)))



#define vector_swap(type, self, index1, index2) 						\
	type tmp = *vector_get(type, self, index1);							\
	*vector_get(type, self, index1) = *vector_get(type, self, index2);	\
	*vector_get(type, self, index2) = tmp


/* mantıklı bir hareket değil biliyorum, ama her swap kullandığım fonksiyonun makroya dönüştürmek istemiyorum */
void _vector_swap
(size_t type_size, base_vector_t *self, size_t index1, size_t index2);



#define vector_insert_p(type, self, index, value) \
	_vector_insert_p(sizeof(type), (base_vector_t *)self, index, (const void *)value)

bool _vector_insert_p
(size_t type_size, base_vector_t *self, size_t index, const void *value);



/* rvalue alabilmek için makro olmalı */
#define vector_insert(type, self, index, value)	({			\
	size_t i, length;										\
	if (self->_end == self->_capacity)						\
		if (vector_extend_capacity(type, self) == False)	\
			False;											\
	\
	length = vector_length(type, self);						\
	for (i = length; i > index; i--)						\
		*(self->_start + i) = *(self->_start + i - 1);		\
	*vector_get(type, self, index) = value;					\
	self->_end = (char *)self->_end + sizeof(type);			\
	True;													\
})



/* faster */
#define vector_shift_r(type, self)									\
	size_t i, last_index = vector_length(type, self) - 1;			\
	type tmp = *vector_get(type, self, last_index);					\
	for (i = last_index; i > 0; i--)								\
		*vector_get(type, self, i) = *vector_get(type, self, i-1);	\
	*vector_get(type, self, 0) = tmp

/* slower */
#define vector_shift_r_(type, self)	\
	_vector_shift_r(sizeof(type), (base_vector_t *)self)

void _vector_shift_r(size_t type_size, base_vector_t *self);



/* faster */
#define vector_shift_l(type, self)										\
	size_t i, length = vector_length(type, self);						\
	type tmp = *vector_get(type, self, 0);								\
	for (i = 1; i < length; i++)										\
		*vector_get(type, self, i - 1) = *vector_get(type, self, i);	\
	*vector_get(type, self, length - 1) = tmp


/* slower */
#define vector_shift_l_(type, self)	\
	_vector_shift_l(sizeof(type), (base_vector_t *)self)

void _vector_shift_l(size_t type_size, base_vector_t *self);



/* makrolar daha hızlı */
#define vector_reverse(type, self)					\
	size_t i, length = vector_length(type, self);	\
	for (i = 0; i < length / 2; i++)				\
		vector_swap(self, i, length - 1 - i)


#define vector_reverse_(type, self) \
	_vector_reverse(sizeof(type), (base_vector_t *)self)

/* yavaş ama bulunsun (malloc yüzünden) */
void _vector_reverse(size_t type_size, base_vector_t *self);



#define vector_sort_merge(type, self, max_func) \
	_vector_sort_merge(sizeof(type), (base_vector_t *)self, max_func)

void _vector_sort_merge
(size_t type_size, base_vector_t *self, max_output_t (*max_func)(void*, void*));

void __vector_sort_merge
(size_t type_size, base_vector_t *self, size_t arr_start, 
	size_t arr_length, max_output_t (*max_func)(void*, void*));



/* faster */
#define vector_sort_bubble(type, self, max_func) 														\
	size_t i, j, last_index = vector_length(type, self) - 1;											\
	for (i = 0; i < last_index; i++)																	\
		for (j = 0; j < last_index-i; j++)																\
           	if ( MO_FIRST_ARG == max_func(vector_get(type, self, j), vector_get(type, self, j+1)) )		\
              	vector_swap(type, self, j, j+1);														\


/* slower */
#define vector_sort_bubble_(type, self, max_func) \
	__vector_sort_bubble(sizeof(type), (base_vector_t *)self, max_func)

void __vector_sort_bubble
(size_t type_size, base_vector_t *self, max_output_t (*max_func)(void*, void*));



#define vector_search_binary_p(type, self, target, max_func) \
	_vector_search_binary_p(sizeof(type), (base_vector_t *)self, (void *)target, max_func)

size_t _vector_search_binary_p
(size_t type_size, base_vector_t *self, void *target, max_output_t (*max_func)(void*, void*));

size_t __vector_search_binary_p
(size_t type_size, base_vector_t *self, void *target, size_t array_start, 
	size_t array_length, max_output_t (*max_func)(void*, void*));


/* size_t array_start = 1, array_length = vector_length(type, self); */
#define _vector_search_binary(type, self, target, max_func) \
	_vector_search_binary(type, self, target, 0, vector_length(type, self), max_func)

#define _vector_search_binary(type, self, target, array_start, array_length, max_func) ({	\
	size_t _array_start = (array_size) + 1, _array_length = (array_length) + 1;		\
	size_t mid_point; max_output_t rv;												\
	while (_array_start <= _array_length) {											\
		mid_point = (int)(_array_start + (_array_length - _array_start - 2) / 2);	\
		rv = max_func(vector_get(type, self, mid_point), &target);					\
		if (rv == MO_ARGS_EQUAL)													\
			mid_point;																\
		else if (rv == MO_FIRST_ARG)												\
			_array_length = mid_point;												\
		else if (rv == MO_SECOND_ARG)												\
			_array_start = mid_point + 2;											\
	} -1;																			\
})



#define vector_search_linear_p(type, self, target, max_func) \
	_vector_search_linear_p(sizeof(type), (base_vector_t *)self, (void *)target, max_func)

size_t _vector_search_linear_p
(size_t type_size, base_vector_t *self, void *target, max_output_t (*max_func)(void*, void*));
	
size_t __vector_search_linear_p
(size_t type_size, base_vector_t *self, void *target, size_t array_start, size_t array_length, max_output_t (*max_func)(void*, void*));


#define vector_search_linear(type, self, target, max_func) \
	_vector_search_linear(type, self, target, 0, vector_length(type, self), max_func)

#define _vector_search_linear(type, self, target, array_start, array_length, max_funx) ({	\
	size_t _array_start = (array_start), _array_length = (array_length);					\
	size_t i; for (i = _array_start; i < _array_length; i++)								\
		if (MO_ARGS_EQUAL == max_func(vector_get(type, self, i), &target))					\
			i;							 													\
	-1;																						\
})

#ifdef NVECTOR_IMPL
#include "new_vector_impl.h"
#endif

#endif