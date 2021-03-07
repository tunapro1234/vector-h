#ifndef VECTOR_H_INCLUDED
#define VECTOR_H_INCLUDED

#include "main.h"

#define VEC_SLAVES 1
#define VEC_DEBUG 1

#define TYPE int

/* 
 * vector_t *vector_init_h(size_t size);
 *	vector constructerı (vektörü heapte oluşturuyor)
 *  
 * vector_t vector_init(size_t size);
 *	vector constructerı
 *		3 pointer kopyalamak nedir ki
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
	
	/********************************************************************************/

	vector_##TYPE##_t* vector_##TYPE##_init_h(size_t capacity);
	vector_##TYPE##_t vector_##TYPE##_init(size_t capacity);
	
	void* vector_##TYPE##_destroy(vector_##TYPE##_t *self);

	size_t vector_##TYPE##_capacity(const vector_##TYPE##_t *self);
	size_t vector_##TYPE##_length(const vector_##TYPE##_t *self);
	size_t vector_##TYPE##_size(const vector_##TYPE##_t *self);
	
	vector_##TYPE##_t* vector_##TYPE##_move_h(vector_##TYPE##_t *self);
	vector_##TYPE##_t vector_##TYPE##_move(vector_##TYPE##_t *self);
	vector_##TYPE##_t* vector_##TYPE##_copy_h(const vector_##TYPE##_t *self);
	vector_##TYPE##_t vector_##TYPE##_copy(const vector_##TYPE##_t *self);

	bool vector_##TYPE##_extend_capacity(vector_##TYPE##_t *self);
	bool vector_##TYPE##_push_back(vector_##TYPE##_t *self, TYPE data);
	bool vector_##TYPE##_p_push_back(vector_##TYPE##_t *self, TYPE *data);
	
	TYPE *vector_##TYPE##_get(vector_##TYPE##_t *self, size_t index);
	TYPE vector_##TYPE##_read(const vector_##TYPE##_t *self, size_t index);
	const TYPE *vector_##TYPE##_p_read(const vector_##TYPE##_t *self, size_t index);

	/********************************************************************************/
	/********************************************************************************/


	vector_##TYPE##_t* vector_##TYPE##_init_h(size_t capacity) {
		vector_##TYPE##_t *new_vector = (vector_##TYPE##_t *)malloc(sizeof(vector_##TYPE##_t)); 
		
		new_vector->start 		= (TYPE *)malloc(sizeof(TYPE) * capacity);
		new_vector->capacity	= new_vector->start + capacity;
		new_vector->end			= new_vector->start;
		return new_vector;
	}
	
	vector_##TYPE##_t vector_##TYPE##_init(size_t capacity) {
		vector_##TYPE##_t new_vector;
		
		new_vector.start 		= (TYPE *)malloc(sizeof(TYPE) * capacity);
		new_vector.capacity		= new_vector.start + capacity;
		new_vector.end			= new_vector.start;
		return new_vector;
	}

	void* vector_##TYPE##_destroy(vector_##TYPE##_t *self) { 
		free(self->start);
		free(self);
	}

	size_t vector_##TYPE##_capacity(const vector_##TYPE##_t *self) { return self->capacity - self->start; }

	size_t vector_##TYPE##_length(const vector_##TYPE##_t *self) { return self->end - self->start; }
	
	size_t vector_##TYPE##_size(const vector_##TYPE##_t *self) { return self->end - self->start; }
	
	vector_##TYPE##_t* vector_##TYPE##_move_h(vector_##TYPE##_t *self) {
		vector_##TYPE##_t *new_vector = (vector_##TYPE##_t *)malloc(sizeof(vector_##TYPE##_t));

		new_vector->capacity = self->capacity;
		new_vector->start = self->start;
		new_vector->end = self->end;

		self->capacity = NULL;
		self->start = NULL;
		self->end = NULL;

		return new_vector;
	}

	vector_##TYPE##_t vector_##TYPE##_move(vector_##TYPE##_t *self) {
		vector_##TYPE##_t new_vector;

		new_vector.capacity = self->capacity;
		new_vector.start = self->start;
		new_vector.end = self->end;

		self->capacity = NULL;
		self->start = NULL;
		self->end = NULL;

		return new_vector;
	}

	vector_##TYPE##_t* vector_##TYPE##_copy_h(const vector_##TYPE##_t *self) {
		size_t length = vector_##TYPE##_length(self);
		vector_##TYPE##_t *new_vector = vector_##TYPE##_init_h(vector_##TYPE##_capacity(self));
		memcpy(new_vector->start, self->start, vector_##TYPE##_capacity(self) * sizeof(TYPE));
		new_vector->end = new_vector->start + length;
		return new_vector;
	}
	
	vector_##TYPE##_t vector_##TYPE##_copy(const vector_##TYPE##_t *self) {
		size_t length = vector_##TYPE##_length(self);
		vector_##TYPE##_t new_vector = vector_##TYPE##_init(vector_##TYPE##_capacity(self));
		memcpy(new_vector.start, self->start, vector_##TYPE##_capacity(self) * sizeof(TYPE));
		new_vector.end = new_vector.start + length;
		return new_vector;
	}

	bool vector_##TYPE##_extend_capacity(vector_##TYPE##_t *self) {
		size_t new_capacity = vector_##TYPE##_capacity(self) * 2;
		size_t length 		= vector_##TYPE##_length(self);

		void *tmp = realloc(self->start, new_capacity * sizeof(TYPE));
		if (tmp == NULL) return False;

		self->start 	= (TYPE *)tmp;
		self->capacity 	= self->start + new_capacity;
		self->end 		= self->start + length;
		return True;
	}

	bool vector_##TYPE##_push_back(vector_##TYPE##_t *self, TYPE data) {
		if (self->end == self->capacity){
			if (vector_##TYPE##_extend_capacity(self) == False)
				return False;
		}
		*self->end = data;
		self->end++;
		return True;
	}

	bool vector_##TYPE##_p_push_back(vector_##TYPE##_t *self, TYPE *data) {
		if (self->end == self->capacity){
			if (vector_##TYPE##_extend_capacity(self) == False)
				return False;
		}
		memcpy(self->end, data, sizeof(TYPE));
		self->end++;
		return True;
	}

	TYPE *vector_##TYPE##_get(vector_##TYPE##_t *self, size_t index) { return self->start + index; }

	TYPE vector_##TYPE##_read(const vector_##TYPE##_t *self, size_t index) { return *(self->start + index); }

	const TYPE *vector_##TYPE##_p_read(const vector_##TYPE##_t *self, size_t index) { return self->start + index; }

#endif