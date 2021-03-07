#ifndef VECTOR_H_INCLUDED
#define VECTOR_H_INCLUDED

#include "main.h"

/*
 * vector_##TYPE##_t* vector_##TYPE##_init_h(size_t capacity);
 *	heapte vector oluşturur 
 *
 * vector_##TYPE##_t vector_##TYPE##_init(size_t capacity);
 * 	3 pointer kopyalasak nolur sanki
 * 
 * void* vector_##TYPE##_destroy(vector_##TYPE##_t *self);
 * 	free(self->start); obje heapte oluştuturldaysa ayrıca temizlenmesi gerekiyor
 * 
 * size_t vector_##TYPE##_capacity(const vector_##TYPE##_t *self);
 * 	vektörün kapasitesinin kaç elemanlık olduğu
 * 
 * size_t vector_##TYPE##_length(const vector_##TYPE##_t *self);
 * 	vektörün içinde kaç eleman olduğu
 * 
 * size_t vector_##TYPE##_size(const vector_##TYPE##_t *self);
 * 	vektörün içinde kaç eleman olduğu ama daha seksi
 * 
 * vector_##TYPE##_t* vector_##TYPE##_move_h(vector_##TYPE##_t *self);
 * 	vektörü heape taşır (eski vektör yok ediliyor)
 * 
 * vector_##TYPE##_t vector_##TYPE##_move(vector_##TYPE##_t *self);
 * 	vektörü stacka taşır gibi bir şey
 * 
 * vector_##TYPE##_t* vector_##TYPE##_copy_h(const vector_##TYPE##_t *self);
 * 	vektörü kopyalar, yeni kopya heapte
 * 
 * vector_##TYPE##_t vector_##TYPE##_copy(const vector_##TYPE##_t *self);
 * 	vektörü kopyalar
 * 
 * bool vector_##TYPE##_extend_capacity(vector_##TYPE##_t *self);
 * 	vektörün kapasitesini realloc yarıdımıyla 2 katına çıkarır
 * 
 * bool vector_##TYPE##_push_back(vector_##TYPE##_t *self, TYPE data);
 * 	vektörün sonuna eleman ekler
 * 
 * bool vector_##TYPE##_p_push_back(vector_##TYPE##_t *self, TYPE *data);
 * 	vektörün sonuna eleman ekler, pointer alıyor
 * 
 * TYPE *vector_##TYPE##_get(vector_##TYPE##_t *self, size_t index);
 * 	vektörün indexinci elemanının pointerını döndürür
 * 
 * TYPE vector_##TYPE##_read(const vector_##TYPE##_t *self, size_t index);
 * 	vektörün indexinci elemanının değerini döndürür
 * 
*/


#define vector_t(TYPE)					\
	typedef struct vector_##TYPE##_t{	\
		TYPE *start, *end, *capacity;	\
	} vector_##TYPE##_t;				\
\
	vector_##TYPE##_t* vector_##TYPE##_init_h(size_t capacity); \
	vector_##TYPE##_t vector_##TYPE##_init(size_t capacity); 	\
	void* vector_##TYPE##_destroy(vector_##TYPE##_t *self); 	\
\
	size_t vector_##TYPE##_capacity(const vector_##TYPE##_t *self); \
	size_t vector_##TYPE##_length(const vector_##TYPE##_t *self); 	\
	size_t vector_##TYPE##_size(const vector_##TYPE##_t *self); 	\
\
	vector_##TYPE##_t* vector_##TYPE##_move_h(vector_##TYPE##_t *self); 		\
	vector_##TYPE##_t vector_##TYPE##_move(vector_##TYPE##_t *self); 			\
	vector_##TYPE##_t* vector_##TYPE##_copy_h(const vector_##TYPE##_t *self);	\
	vector_##TYPE##_t vector_##TYPE##_copy(const vector_##TYPE##_t *self); 		\
 \
	bool vector_##TYPE##_extend_capacity(vector_##TYPE##_t *self); 			\
	bool vector_##TYPE##_push_back(vector_##TYPE##_t *self, TYPE data); 	\
	bool vector_##TYPE##_p_push_back(vector_##TYPE##_t *self, TYPE *data); 	\
	 \
	TYPE *vector_##TYPE##_get(vector_##TYPE##_t *self, size_t index); 		\
	TYPE vector_##TYPE##_read(const vector_##TYPE##_t *self, size_t index); \
\
/********************************************************************************/ \
\
	vector_##TYPE##_t* vector_##TYPE##_init_h(size_t capacity) { 									\
		vector_##TYPE##_t *new_vector = (vector_##TYPE##_t *)malloc(sizeof(vector_##TYPE##_t));  	\
		\
		new_vector->start 		= (TYPE *)malloc(sizeof(TYPE) * capacity); 							\
		new_vector->capacity	= new_vector->start + capacity; 									\
		new_vector->end			= new_vector->start; 												\
		return new_vector; 																			\
	}	\
\
	vector_##TYPE##_t vector_##TYPE##_init(size_t capacity) { \
		vector_##TYPE##_t new_vector; 										\
		\
		new_vector.start 		= (TYPE *)malloc(sizeof(TYPE) * capacity); 	\
		new_vector.capacity		= new_vector.start + capacity; 				\
		new_vector.end			= new_vector.start; 						\
		return new_vector; 													\
	} 	\
\
	void* vector_##TYPE##_destroy(vector_##TYPE##_t *self) {  	\
		free(self->start); 										\
	} 	\
\
	size_t vector_##TYPE##_capacity(const vector_##TYPE##_t *self) { return self->capacity - self->start; } \
	size_t vector_##TYPE##_length(const vector_##TYPE##_t *self) { return self->end - self->start; } 		\
	size_t vector_##TYPE##_size(const vector_##TYPE##_t *self) { return self->end - self->start; } 			\
\
	vector_##TYPE##_t* vector_##TYPE##_move_h(vector_##TYPE##_t *self) { 						\
		vector_##TYPE##_t *new_vector = (vector_##TYPE##_t *)malloc(sizeof(vector_##TYPE##_t)); \
		new_vector->capacity = self->capacity; 													\
		new_vector->start = self->start; 														\
		new_vector->end = self->end; 															\
		self->capacity = NULL; 																	\
		self->start = NULL; 																	\
		self->end = NULL; 																		\
		return new_vector; 																		\
	} 	\
\
	vector_##TYPE##_t vector_##TYPE##_move(vector_##TYPE##_t *self) { \
		vector_##TYPE##_t new_vector; 			\
		new_vector.capacity = self->capacity; 	\
		new_vector.start = self->start; 		\
		new_vector.end = self->end; 			\
		self->capacity = NULL; 					\
		self->start = NULL; 					\
		self->end = NULL; 						\
		return new_vector; 						\
	} 	\
\
	vector_##TYPE##_t* vector_##TYPE##_copy_h(const vector_##TYPE##_t *self) { 					\
		size_t length = vector_##TYPE##_length(self); 											\
		vector_##TYPE##_t *new_vector = vector_##TYPE##_init_h(vector_##TYPE##_capacity(self)); \
		memcpy(new_vector->start, self->start, vector_##TYPE##_capacity(self) * sizeof(TYPE)); 	\
		new_vector->end = new_vector->start + length; 											\
		return new_vector; 																		\
	} 	\
\
	vector_##TYPE##_t vector_##TYPE##_copy(const vector_##TYPE##_t *self) { 					\
		size_t length = vector_##TYPE##_length(self); 											\
		vector_##TYPE##_t new_vector = vector_##TYPE##_init(vector_##TYPE##_capacity(self)); 	\
		memcpy(new_vector.start, self->start, vector_##TYPE##_capacity(self) * sizeof(TYPE)); 	\
		new_vector.end = new_vector.start + length; 											\
		return new_vector; 																		\
	} 	\
\
	bool vector_##TYPE##_extend_capacity(vector_##TYPE##_t *self) { 	\
		size_t new_capacity = vector_##TYPE##_capacity(self) * 2; 		\
		size_t length 		= vector_##TYPE##_length(self); 			\
		\
		void *tmp = realloc(self->start, new_capacity * sizeof(TYPE)); 	\
		if (tmp == NULL) return False; 									\
		\
		self->start 	= (TYPE *)tmp; 					\
		self->capacity 	= self->start + new_capacity; 	\
		self->end 		= self->start + length; 		\
		return True; 									\
	} 	\
\
	bool vector_##TYPE##_push_back(vector_##TYPE##_t *self, TYPE data) { 	\
		if (self->end == self->capacity){ 									\
			if (vector_##TYPE##_extend_capacity(self) == False) 			\
				return False; 												\
		} 																	\
		*self->end = data; 													\
		self->end++; 														\
		return True; 														\
	} 	\
\
	bool vector_##TYPE##_p_push_back(vector_##TYPE##_t *self, TYPE *data) { \
		if (self->end == self->capacity){ 									\
			if (vector_##TYPE##_extend_capacity(self) == False) 			\
				return False; 												\
		} 																	\
		memcpy(self->end, data, sizeof(TYPE)); 								\
		self->end++; 														\
		return True; 														\
	} 	\
\
	TYPE *vector_##TYPE##_get(vector_##TYPE##_t *self, size_t index) { return self->start + index; } 			\
	TYPE vector_##TYPE##_read(const vector_##TYPE##_t *self, size_t index) { return *(self->start + index); } 	\


#endif