#ifndef NVECTOR_H_INCLUDED
#define NVECTOR_H_INCLUDED

#include "../main.h"

/* 
 * #define NVECTOR_IMPL 
 * 
 */

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



/*========================*/
base_vector_t __new_vector;
/*========================*/

/* 
 * statement expressionların kendine özel scopeu oluyormuş
 * muhtemelen __new_vectorü vermeye çalışmam undefined behaviour 
 * ile sonuçlanacak
 * 
 * #define vector_init_s(type, capacity) ({				\
 * 	__new_vector = _vector_init_s(sizeof(int) * 10);	\
 * 	(vector_t(type) *)&__new_vector; 					\
 * })
*/

base_vector_t _vector_init_s(size_t size);



/* type, capacity */
#define vector_init(type, capacity) \
	(vector_t(type) *)_vector_init(sizeof(type) * capacity)

base_vector_t* _vector_init(size_t size);



/* type, self */
#define vector_destroy(type, self) \
	_vector_destroy((base_vector_t *)(self))

void _vector_destroy(base_vector_t *self);



/* type, self */
#define vector_capacity(type, self)	\
	_vector_capacity((const base_vector_t *)(self)) / sizeof(type)

size_t _vector_capacity(const base_vector_t *self);



/* type, self */
#define vector_length(type, self) \
	_vector_length((const base_vector_t *)(self)) / sizeof(type)

size_t _vector_length(const base_vector_t *self);



/* type, self */
#define vector_size(type, self)	\
	vector_size((const base_vector_t *)(self)) / sizeof(type)

size_t _vector_size(const base_vector_t *self);



/* type, self */
#define vector_move(type, self) \
	(vector_t(type) *)_vector_move(sizeof(type), (base_vector_t *)(self))

base_vector_t* _vector_move(size_t type_size, base_vector_t *self);



/* type, self */
#define vector_move_s(type, self) \
	(vector_t(type) *)_vector_move_s((base_vector_t *)(self))

base_vector_t _vector_move_s(base_vector_t *self);



/* type, self */
#define vector_copy(type, self) \
	(vector_t(type) *)_vector_copy((const base_vector_t *)(self))

base_vector_t* _vector_copy(const base_vector_t *self);



/* type, self */
#define vector_copy_s(type, self) \
	(vector_t(type) *)_vector_copy_s((const base_vector_t *)(self))

base_vector_t _vector_copy_s(const base_vector_t *self);



/* type, self */
#define vector_extend_capacity(type, self) \
	_vector_extend_capacity((base_vector_t *)(self))

/* self */
#define _vector_extend_capacity(self) \
	_vector_resize(self, _vector_capacity(self) * 2)


/* type, self, size */
#define vector_resize(type, self, size) \
	_vector_resize((base_vector_t *)(self), size)

bool _vector_resize(base_vector_t *self, size_t size);



/* type, self, data */
#define vector_push_back(type, self, data) ({						\
	base_vector_t *__base_self0 = (base_vector_t *)(self);			\
	bool rv = True;													\
	if (__base_self0->_end == __base_self0->_capacity)				\
		if (vector_extend_capacity(type, __base_self0) == False)	\
			rv = False;												\
	\
	if (rv) {														\
		*(type *)__base_self0->_end = data; 						\
		__base_self0->_end = (type *)__base_self0->_end + 1;		\
	} rv;															\
})


/* type, self, data */
#define vector_push_back_p(type, self, data) \
	_vector_push_back_p(sizeof(type), (base_vector_t *)(self), (const void *)data)

bool _vector_push_back_p(size_t type_size, base_vector_t *self, const void* data);

/* type, self, index */
#define vector_get(type, self, index) \
	((type *)_vector_get(sizeof(type), (base_vector_t *)(self), index))

void* _vector_get(size_t type_size, base_vector_t *self, size_t index);


/* type, self, index */
#define vector_read(type, self, index) \
	(*(type *)((char *)(self)->_start + (index * sizeof(type))))



/* type, self, index1, index2 */
#define vector_swap(type, self, index1, index2) ({ 									\
	base_vector_t *__base_self1 = (base_vector_t *)(self); 							\
	size_t i1 = (index1), i2 = (index2);											\
	type __tmp = *vector_get(type, __base_self1, i1);								\
	*vector_get(type, __base_self1, i1) = *vector_get(type, __base_self1, i2);		\
	*vector_get(type, __base_self1, i2) = __tmp;									\
})


/* mantıklı bir hareket değil biliyorum, ama her swap kullandığım fonksiyonun makroya dönüştürmek istemiyorum */
void _vector_swap
(size_t type_size, base_vector_t *self, size_t index1, size_t index2);



/* type, self, index, value */
#define vector_insert_p(type, self, index, value) \
	_vector_insert_p(sizeof(type), (base_vector_t *)(self), index, (const void *)value)

bool _vector_insert_p
(size_t type_size, base_vector_t *self, size_t index, const void *value);



/* type, self, index, value / rvalue alabilmek için makro olmalı */
#define vector_insert(type, self, index, value)	({							\
	base_vector_t *__base_self2 = (base_vector_t *)(self);					\
	size_t _i, __length; bool rv = True; 									\
	if (__base_self2->_end == __base_self2->_capacity)						\
		if (vector_extend_capacity(type, __base_self2) == False)			\
			rv = False;														\
	\
	if (rv) {																					\
		__length = vector_length(type, __base_self2);											\
		for (_i = __length; _i > index; _i--)													\
			/* __base_self2[i] = __base_self2[i-1] soldan sağa doğru giderek sağa kaydırma */ 	\
			*((type *)__base_self2->_start + _i) = *((type *)__base_self2->_start + _i - 1);	\
		/* istenilen indexe istenilen data */													\
		*vector_get(type, __base_self2, index) = value;											\
		__base_self2->_end = (type *)__base_self2->_end + 1;									\
	} rv;																						\
})



/* type, self / faster */
#define vector_shift_r(type, self) ({													\
	base_vector_t *__base_self3 = (base_vector_t *)(self);								\
	size_t _i, last_index = vector_length(type, __base_self3) - 1;						\
	type __tmp = *vector_get(type, __base_self3, last_index);							\
	for (_i = last_index; _i > 0; _i--)													\
		*vector_get(type, __base_self3, _i) = *vector_get(type, __base_self3, _i-1);	\
	*vector_get(type, __base_self3, 0) = __tmp;											\
})

/* type, self / slower */
#define vector_shift_r_(type, self)	\
	_vector_shift_r(sizeof(type), (base_vector_t *)(self))

void _vector_shift_r(size_t type_size, base_vector_t *self);



/* type, self / faster */
#define vector_shift_l(type, self) ({													\
	base_vector_t *__base_self4 = (base_vector_t *)(self);								\
	size_t _i, __length = vector_length(type, __base_self4);							\
	type __tmp = *vector_get(type, __base_self4, 0);									\
	for (_i = 1; _i < __length; _i++)													\
		*vector_get(type, __base_self4, _i - 1) = *vector_get(type, __base_self4, _i);	\
	*vector_get(type, __base_self4, __length - 1) = __tmp;								\
})


/* type, self / slower */
#define vector_shift_l_(type, self)	\
	_vector_shift_l(sizeof(type), (base_vector_t *)(self))

void _vector_shift_l(size_t type_size, base_vector_t *self);



/* type, self / makrolar daha hızlı */
#define vector_reverse(type, self) ({							\
	base_vector_t *__base_self5 = (base_vector_t *)(self);		\
	size_t _i, __length = vector_length(type, __base_self5);	\
	for (_i = 0; _i < __length / 2; _i++)						\
		vector_swap(type, __base_self5, _i, __length - 1 - _i);	\
})


/* type, self */
#define vector_reverse_(type, self) \
	_vector_reverse(sizeof(type), (base_vector_t *)(self))

/* yavaş ama bulunsun (malloc yüzünden) */
void _vector_reverse(size_t type_size, base_vector_t *self);



/* type, self, max_func */
#define vector_sort_merge(type, self, max_func) \
	_vector_sort_merge(sizeof(type), (base_vector_t *)(self), (max_output_t (*)(void*, void*))(max_func))

void _vector_sort_merge
(size_t type_size, base_vector_t *self, max_output_t (*max_func)(void*, void*));

void __vector_sort_merge
(size_t type_size, base_vector_t *self, size_t arr_start, 
	size_t arr_length, max_output_t (*max_func)(void*, void*));



/* aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa */
/* type, self, max_func / faster */
#define vector_sort_bubble(type, self, max_func) ({														\
	base_vector_t *__base_self6 = (base_vector_t *)(self);												\
	size_t _i, j, last_index = vector_length(type, __base_self6) - 1;									\
	for (_i = 0; _i < last_index; _i++)																	\
		for (j = 0; j < last_index-_i; j++)																\
           	if ( MO_FIRST_ARG == max_func(vector_get(type, __base_self6, j), 							\
			   								vector_get(type, __base_self6, j+1)) )						\
              	vector_swap(type, __base_self6, j, j+1);												\
})


/* type, self, max_func / slower */
#define vector_sort_bubble_(type, self, max_func) \
	__vector_sort_bubble(sizeof(type), (base_vector_t *)(self), (*)(void*, void*)(max_func))

void __vector_sort_bubble
(size_t type_size, base_vector_t *self, max_output_t (*max_func)(void*, void*));


/* type, self, target, max_func */
#define vector_search_binary_p(type, self, target, max_func) \
	_vector_search_binary_p(sizeof(type), (base_vector_t *)(self), (void *)(target), (*)(void*, void*)(max_func))

size_t _vector_search_binary_p
(size_t type_size, base_vector_t *self, void *target, max_output_t (*max_func)(void*, void*));

size_t __vector_search_binary_p
(size_t type_size, base_vector_t *self, void *target, size_t array_start, 
	size_t array_length, max_output_t (*max_func)(void*, void*));


/* type, self, target, max_func */
#define vector_search_binary(type, self, target, max_func) ({		\
	base_vector_t *__base_self7 = (base_vector_t *)(self);			\
	_vector_search_binary(type, __base_self7, target, 0, 			\
				vector_length(type, __base_self7), max_func);		\
})

/* type, self, target, array_start, array_length, max_func */
#define _vector_search_binary(type, self, target, array_start, array_length, max_func) ({	\
	base_vector_t *__base_self8 = (base_vector_t *)(self);							\
	type _target = (target);														\
	size_t _array_start = (array_start) + 1, _array_length = (array_length) + 1;	\
	size_t mid_point, found = -1; max_output_t rv;									\
	while (_array_start <= _array_length) {											\
		mid_point = (int)(_array_start + (_array_length - _array_start - 2) / 2);	\
		rv = max_func(vector_get(type, __base_self8, mid_point), &_target);			\
		if (rv == MO_ARGS_EQUAL) {													\
			found = mid_point; break;												\
		} else if (rv == MO_FIRST_ARG)												\
			_array_length = mid_point;												\
		else if (rv == MO_SECOND_ARG)												\
			_array_start = mid_point + 2;											\
	} found;																		\
})



/* type, self, target, max_func */
#define vector_search_linear_p(type, self, target, max_func) \
	_vector_search_linear_p(sizeof(type), (base_vector_t *)(self), (void *)(target), (*)(void*, void*)(max_func))

size_t _vector_search_linear_p
(size_t type_size, base_vector_t *self, void *target, max_output_t (*max_func)(void*, void*));
	
size_t __vector_search_linear_p
(size_t type_size, base_vector_t *self, void *target, size_t array_start, size_t array_length, max_output_t (*max_func)(void*, void*));


/* type, self, target, max_func */
#define vector_search_linear(type, self, target, max_func) \
	_vector_search_linear(type, self, target, 0, vector_length(type, self), max_func)

/* aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa */
/* type, self, target, array_start, array_length, max_func */
#define _vector_search_linear(type, self, target, array_start, array_length, max_func) ({	\
	type _target = (target);																\
	size_t _array_start = (array_start), _array_length = (array_length), found = -1;		\
	size_t _i; for (_i = _array_start; _i < _array_length; _i++)							\
		if (MO_ARGS_EQUAL == max_func(vector_get(type, self, _i), &_target)) {				\
			found = _i; break;					 											\
		}																					\
	found;																					\
})

#ifdef NVECTOR_IMPL
#include "impl/new_vector_impl.h"
#endif

#endif