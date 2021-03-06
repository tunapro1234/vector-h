#ifndef VECTOR_H_INCLUDED
#define VECTOR_H_INCLUDED

#include "main.h"

#define VEC_SLAVES 1
#define VEC_DEBUG 1

#define TYPE int

/* 
 * vector_t *vector_init(size_t size, ...);
 *	vector constructerı
 *  
 * void *vector_destroy(vector_t *self);
 * 	vector destructerı
 * 
 * u32 vector_capacity(const vector_t *self);
 * 	Verilen tipten max kaç tane eleman alabileceği
 * 
 * u32 vector_length(const vector_t *self);
 * 	Verilen tipten kaç tane eleman olduğu
 * 
 * vector_t *vector_move(vector_t *self);
 * 	Ne işe yarıyor ben de bilmiyorum
 * 
 * vector_t *vector_copy(const vector_t *self);
 * 	Vektörü kopyalar (deep copy)
 * 
 * const vector_t *vector_copy_ro(vector_t *self);
 * 	Vektörü kopyalar (pointerlar, önermiyorum)
 * 
 * void vector_free_slaves(vector_t *self);
 * 	slaves açıksa (yazar mıyım ona da emin değilim) slaveleri temizler
 * 
 * bool vector_extend_capacity(vector_t *self);
 * 	internal, kapasiteyi arttırır
 * 
 * bool vector_push_back(vector_t *self, TYPE data);
 * 	vektörün sonuna eleman ekler
 * 
 * bool vector_push_back_p(vector_t *self, TYPE *data);
 * 	vektörün sonuna eleman ekler
 * 
 * TYPE* vector_get(vector_t *self, s32 index);
 * 	get işte
 * 
 * TYPE vector_read(vector_t *self, s32 index);
 * 	kopyalıyor ve yolluyor
 */



#define vector_t(TYPE)					\
	typedef struct vector_##TYPE##_t{	\
		TYPE *start, *end, *capacity;	\
	} vector_##TYPE##_t;				\


vector_##TYPE##_t *vector_##TYPE##_init(size_t size, ...);
bool *vector_##TYPE##_push_back(vector_##TYPE##_t self, TYPE new_element);
bool *vector_##TYPE##_push_back_p(vector_##TYPE##_t self, TYPE* new_element);

void *vector_##TYPE##_destroy(vector_##TYPE##_t *self);

u32 vector_##TYPE##_capacity(const vector_##TYPE##_t *self);
u32 vector_##TYPE##_length(const vector_##TYPE##_t *self);

vector_##TYPE##_t *vector_##TYPE##_move(vector_##TYPE##_t *self);
vector_##TYPE##_t *vector_##TYPE##_copy(const vector_##TYPE##_t *self);

const vector_##TYPE##_t *vector_##TYPE##_copy_ro(vector_##TYPE##_t *self);
void vector_##TYPE##_free_slaves(vector_##TYPE##_t *self);

bool vector_##TYPE##_extend_capacity(vector_##TYPE##_t *self);
bool vector_##TYPE##_push_back(vector_##TYPE##_t *self, TYPE data);
bool vector_##TYPE##_push_back_p(vector_##TYPE##_t *self, TYPE *data);

TYPE* vector_##TYPE##_get(vector_##TYPE##_t *self, size_t index);
TYPE vector_##TYPE##_read(vector_##TYPE##_t *self, size_t index);


vector_##TYPE##_t *vector_##TYPE##_init(size_t size, ...) {
	int i; /* vektör için yer oluştur */
	vector_##TYPE##_t *new_vector = (vector_##TYPE##_t *)malloc(sizeof(vector_##TYPE##_t));
	
	/* içindekiler için yer oluştur */
	new_vector->start 		= (TYPE *)malloc(sizeof(TYPE) * size);
	new_vector->capacity	= new_vector->start + size;
	new_vector->end			= new_vector->capacity;
	
	va_list args; va_start(args, size);
	for (i = 0; i < size; i++) { vector_##TYPE##_push_back(new_vector, va_arg(args, TYPE)); }
	

	
	return new_vector;
}




#endif