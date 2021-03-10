#ifndef VECTOR_H_INCLUDED
#define VECTOR_H_INCLUDED

#include "main.h"

/*
 * vector_##TYPE* vector_##TYPE##_init_h(size_t capacity);
 *	heapte vector oluşturur 
 *
 * vector_##TYPE vector_##TYPE##_init(size_t capacity);
 * 	3 pointer kopyalasak nolur sanki
 * 
 * void vector_##TYPE##_destroy(vector_##TYPE *self);
 * 	free(self->start); obje heapte oluştuturldaysa ayrıca temizlenmesi gerekiyor
 * 
 * size_t vector_##TYPE##_capacity(const vector_##TYPE *self);
 * 	vektörün kapasitesinin kaç elemanlık olduğu
 * 
 * size_t vector_##TYPE##_length(const vector_##TYPE *self);
 * 	vektörün içinde kaç eleman olduğu
 * 
 * size_t vector_##TYPE##_size(const vector_##TYPE *self);
 * 	vektörün içinde kaç eleman olduğu ama daha seksi
 * 
 * vector_##TYPE* vector_##TYPE##_move_h(vector_##TYPE *self);
 * 	vektörü heape taşır (eski vektör yok ediliyor)
 * 
 * vector_##TYPE vector_##TYPE##_move(vector_##TYPE *self);
 * 	vektörü stacka taşır gibi bir şey
 * 
 * vector_##TYPE* vector_##TYPE##_copy_h(const vector_##TYPE *self);
 * 	vektörü kopyalar, yeni kopya heapte
 * 
 * vector_##TYPE vector_##TYPE##_copy(const vector_##TYPE *self);
 * 	vektörü kopyalar
 * 
 * bool vector_##TYPE##_extend_capacity(vector_##TYPE *self);
 * 	vektörün kapasitesini realloc yarıdımıyla 2 katına çıkarır
 * 
 * bool vector_##TYPE##_push_back(vector_##TYPE *self, TYPE data);
 * 	vektörün sonuna eleman ekler
 * 
 * bool vector_##TYPE##_p_push_back(vector_##TYPE *self, TYPE *data);
 * 	vektörün sonuna eleman ekler, pointer alıyor
 * 
 * TYPE *vector_##TYPE##_get(vector_##TYPE *self, size_t index);
 * 	vektörün indexinci elemanının pointerını döndürür
 * 
 * TYPE vector_##TYPE##_read(const vector_##TYPE *self, size_t index);
 * 	vektörün indexinci elemanının değerini döndürür
 * 
 * 
 * void vector_##TYPE##_bubble_sort(vector_##TYPE *self, TYPE* (*key_func)(TYPE*, TYPE*));
 * 	elemanları bubble sort algoritması ile sırala (büyük olan elemanı belirlemek için fonksiyon pointerı alıyor)
 * 
 * void vector_##TYPE##_swap(vector_##TYPE *self, size_t index1, size_t index2);
 * 	iki indeksteki elemanları değiştirir
 * 
 * bool vector_##TYPE##_insert_p(vector_##TYPE *self, size_t index, TYPE *value);
 * 	verilen adresteki datayı verilen indekse kopyalar
 * 
 * bool vector_##TYPE##_insert(vector_##TYPE *self, size_t index, TYPE value);
 * 	verilen datayı indekse kopyalar
 * 
 * void vector_##TYPE##_shift_r(vector_##TYPE *self);
 * 	vektörün elemanlarını sağa kaydırır (sonuncu eleman başa geliyor)
 * 
 * void vector_##TYPE##_shift_l(vector_##TYPE *self);
 * 	vektörün elemanlarını sola kaydırır (baştaki eleman sola geliyor)
 * 
 * void vector_##TYPE##_reverse(vector_##TYPE *self);
 * 	vektörü ters döndürür
 * 
*/

int* vector_int_sort_example(int *a, int *b);

int* vector_int_sort_example(int *a, int *b) {
	return (*a > *b) ? a : b;
}

#define create_vector_t(TYPE)			\
	typedef struct vector_##TYPE{	\
		TYPE *start, *end, *capacity;	\
	} vector_##TYPE;				\
\
	vector_##TYPE* vector_##TYPE##_init_h(size_t capacity); \
	vector_##TYPE vector_##TYPE##_init(size_t capacity); 	\
	void vector_##TYPE##_destroy(vector_##TYPE *self); 	\
\
	size_t vector_##TYPE##_capacity(const vector_##TYPE *self); \
	size_t vector_##TYPE##_length(const vector_##TYPE *self); 	\
	size_t vector_##TYPE##_size(const vector_##TYPE *self); 	\
\
	vector_##TYPE* vector_##TYPE##_move_h(vector_##TYPE *self); 		\
	vector_##TYPE vector_##TYPE##_move(vector_##TYPE *self); 			\
	vector_##TYPE* vector_##TYPE##_copy_h(const vector_##TYPE *self);	\
	vector_##TYPE vector_##TYPE##_copy(const vector_##TYPE *self); 		\
\
	bool vector_##TYPE##_extend_capacity(vector_##TYPE *self); 			\
	bool vector_##TYPE##_push_back(vector_##TYPE *self, TYPE data); 	\
	bool vector_##TYPE##_p_push_back(vector_##TYPE *self, TYPE *data); 	\
\
	TYPE *vector_##TYPE##_get(vector_##TYPE *self, size_t index); 		\
	TYPE vector_##TYPE##_read(const vector_##TYPE *self, size_t index); \
\
\
	void vector_##TYPE##_bubble_sort(vector_##TYPE *self, TYPE* (*key_func)(TYPE*, TYPE*));	\
	void vector_##TYPE##_swap(vector_##TYPE *self, size_t index1, size_t index2);			\
	bool vector_##TYPE##_insert_p(vector_##TYPE *self, size_t index, TYPE *value);			\
	bool vector_##TYPE##_insert(vector_##TYPE *self, size_t index, TYPE value);				\
\
	void vector_##TYPE##_shift_r(vector_##TYPE *self);	\
	void vector_##TYPE##_shift_l(vector_##TYPE *self);	\
	void vector_##TYPE##_reverse(vector_##TYPE *self);	\
\
/********************************************************************************/	\
\
	vector_##TYPE* vector_##TYPE##_init_h(size_t capacity) { 									\
		vector_##TYPE *new_vector = (vector_##TYPE *)malloc(sizeof(vector_##TYPE));  	\
		\
		new_vector->start 		= (TYPE *)malloc(sizeof(TYPE) * capacity); 							\
		new_vector->capacity	= new_vector->start + capacity; 									\
		new_vector->end			= new_vector->start; 												\
		return new_vector; 																			\
	}	\
\
	vector_##TYPE vector_##TYPE##_init(size_t capacity) { \
		vector_##TYPE new_vector; 										\
		\
		new_vector.start 		= (TYPE *)malloc(sizeof(TYPE) * capacity); 	\
		new_vector.capacity		= new_vector.start + capacity; 				\
		new_vector.end			= new_vector.start; 						\
		return new_vector; 													\
	} 	\
\
	void vector_##TYPE##_destroy(vector_##TYPE *self) {  	\
		free(self->start); 										\
	} 	\
\
	size_t vector_##TYPE##_capacity(const vector_##TYPE *self) { return self->capacity - self->start; } \
	size_t vector_##TYPE##_length(const vector_##TYPE *self) { return self->end - self->start; } 		\
	size_t vector_##TYPE##_size(const vector_##TYPE *self) { return self->end - self->start; } 			\
\
	vector_##TYPE* vector_##TYPE##_move_h(vector_##TYPE *self) { 						\
		vector_##TYPE *new_vector = (vector_##TYPE *)malloc(sizeof(vector_##TYPE)); \
		new_vector->capacity = self->capacity; 													\
		new_vector->start = self->start; 														\
		new_vector->end = self->end; 															\
		self->capacity = NULL; 																	\
		self->start = NULL; 																	\
		self->end = NULL; 																		\
		return new_vector; 																		\
	} 	\
\
	vector_##TYPE vector_##TYPE##_move(vector_##TYPE *self) { \
		vector_##TYPE new_vector; 			\
		new_vector.capacity = self->capacity; 	\
		new_vector.start = self->start; 		\
		new_vector.end = self->end; 			\
		self->capacity = NULL; 					\
		self->start = NULL; 					\
		self->end = NULL; 						\
		return new_vector; 						\
	} 	\
\
	vector_##TYPE* vector_##TYPE##_copy_h(const vector_##TYPE *self) { 					\
		size_t length = vector_##TYPE##_length(self); 											\
		vector_##TYPE *new_vector = vector_##TYPE##_init_h(vector_##TYPE##_capacity(self)); \
		memcpy(new_vector->start, self->start, vector_##TYPE##_capacity(self) * sizeof(TYPE)); 	\
		new_vector->end = new_vector->start + length; 											\
		return new_vector; 																		\
	} 	\
\
	vector_##TYPE vector_##TYPE##_copy(const vector_##TYPE *self) { 					\
		size_t length = vector_##TYPE##_length(self); 											\
		vector_##TYPE new_vector = vector_##TYPE##_init(vector_##TYPE##_capacity(self)); 	\
		memcpy(new_vector.start, self->start, vector_##TYPE##_capacity(self) * sizeof(TYPE)); 	\
		new_vector.end = new_vector.start + length; 											\
		return new_vector; 																		\
	} 	\
\
	bool vector_##TYPE##_extend_capacity(vector_##TYPE *self) { 	\
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
	bool vector_##TYPE##_push_back(vector_##TYPE *self, TYPE data) { 	\
		if (self->end == self->capacity){ 									\
			if (vector_##TYPE##_extend_capacity(self) == False) 			\
				return False; 												\
		} 																	\
		*self->end = data; 													\
		self->end++; 														\
		return True; 														\
	} 	\
\
	bool vector_##TYPE##_p_push_back(vector_##TYPE *self, TYPE *data) { \
		if (self->end == self->capacity){ 									\
			if (vector_##TYPE##_extend_capacity(self) == False) 			\
				return False; 												\
		} 																	\
		memcpy(self->end, data, sizeof(TYPE)); 								\
		self->end++; 														\
		return True; 														\
	} 	\
\
	TYPE *vector_##TYPE##_get(vector_##TYPE *self, size_t index) { return self->start + index; } 			\
	TYPE vector_##TYPE##_read(const vector_##TYPE *self, size_t index) { return *(self->start + index); } 	\
\
\
	void vector_##TYPE##_swap(vector_##TYPE *self, size_t index1, size_t index2) {	\
		TYPE tmp = *vector_##TYPE##_get(self, index1);									\
		*vector_##TYPE##_get(self, index1) = *vector_##TYPE##_get(self, index2);		\
		*vector_##TYPE##_get(self, index2) = tmp;										\
	}	\
\
	bool vector_##TYPE##_insert_p(vector_##TYPE *self, size_t index, TYPE *value) {	\
		size_t i, length;																\
		if (self->end == self->capacity)												\
			if (vector_##TYPE##_extend_capacity(self) == False)							\
				return False;															\
		\
		length = vector_##TYPE##_length(self);											\
		for (i = length-1; i >= index; i--)												\
			*vector_##TYPE##_get(self, i+1) = *vector_##TYPE##_get(self, i);			\
		memcpy(vector_##TYPE##_get(self, index), value, sizeof(TYPE));					\
		self->end++;																	\
		return True;																	\
	}	\
\
	bool vector_##TYPE##_insert(vector_##TYPE *self, size_t index, TYPE value) {	\
		size_t i, length;																\
		if (self->end == self->capacity)												\
			if (vector_##TYPE##_extend_capacity(self) == False)							\
				return False;															\
		\
		length = vector_##TYPE##_length(self);											\
		for (i = length; i > index; i--)												\
			*vector_##TYPE##_get(self, i) = *vector_##TYPE##_get(self, i-1);			\
		*vector_##TYPE##_get(self, index) = value;										\
		self->end++;																	\
		return True;																	\
	}	\
\
	void vector_##TYPE##_shift_r(vector_##TYPE *self) {						\
		size_t i, last_index = vector_##TYPE##_length(self)-1;					\
		TYPE tmp = *vector_##TYPE##_get(self, last_index);						\
		for (i = last_index; i > 0; i--)										\
			*vector_##TYPE##_get(self, i) = *vector_##TYPE##_get(self, i-1);	\
		*vector_##TYPE##_get(self, 0) = tmp;									\
	}	\
\
	void vector_##TYPE##_shift_l(vector_##TYPE *self) {						\
		size_t i, length = vector_##TYPE##_length(self);						\
		TYPE tmp = *vector_##TYPE##_get(self, 0);								\
		for (i = 1; i < length; i++)											\
			*vector_##TYPE##_get(self, i-1) = *vector_##TYPE##_get(self, i);	\
		*vector_##TYPE##_get(self, length-1) = tmp;								\
	}	\
\
	void vector_##TYPE##_reverse(vector_##TYPE *self) {	\
		size_t i, length = vector_##TYPE##_length(self);	\
		for (i = 0; i < length/2; i++)						\
			vector_##TYPE##_swap(self, i, length-1-i);		\
	}	\
\
	void vector_##TYPE##_bubble_sort(vector_##TYPE *self, TYPE* (*key_func)(TYPE*, TYPE*)){								\
	size_t i, j, last_index = vector_##TYPE##_length(self)-1;																\
	for (i = 0; i < last_index; i++)																						\
		for (j = 0; j < last_index-i; j++)																					\
           	if ( vector_##TYPE##_get(self, j) == key_func(vector_##TYPE##_get(self, j), vector_##TYPE##_get(self, j+1)) )	\
              	vector_##TYPE##_swap(self, j, j+1);																			\
}	\


#endif