#ifndef VECTOR_H_INCLUDED
#define VECTOR_H_INCLUDED

#include "main.h"

/*
 * vector_##NAME* vector_##NAME##_init_h(size_t capacity);
 *	heapte vector oluşturur 
 *
 * vector_##NAME vector_##NAME##_init(size_t capacity);
 * 	3 pointer kopyalasak nolur sanki
 * 
 * void vector_##NAME##_destroy(vector_##NAME *self);
 * 	free(self->_start); obje heapte oluştuturldaysa ayrıca temizlenmesi gerekiyor
 * 
 * size_t vector_##NAME##_capacity(const vector_##NAME *self);
 * 	vektörün kapasitesinin kaç elemanlık olduğu
 * 
 * size_t vector_##NAME##_length(const vector_##NAME *self);
 * 	vektörün içinde kaç eleman olduğu
 * 
 * size_t vector_##NAME##_size(const vector_##NAME *self);
 * 	vektörün içinde kaç eleman olduğu ama daha seksi
 * 
 * vector_##NAME* vector_##NAME##_move_h(vector_##NAME *self);
 * 	vektörü heape taşır (eski vektör yok ediliyor)
 * 
 * vector_##NAME vector_##NAME##_move(vector_##NAME *self);
 * 	vektörü stacka taşır gibi bir şey
 * 
 * vector_##NAME* vector_##NAME##_copy_h(const vector_##NAME *self);
 * 	vektörü kopyalar, yeni kopya heapte
 * 
 * vector_##NAME vector_##NAME##_copy(const vector_##NAME *self);
 * 	vektörü kopyalar
 * 
 * bool vector_##NAME##_extend_capacity(vector_##NAME *self);
 * 	vektörün kapasitesini realloc yarıdımıyla 2 katına çıkarır
 * 
 * bool vector_##NAME##_push_back(vector_##NAME *self, TYPE data);
 * 	vektörün sonuna eleman ekler
 * 
 * bool vector_##NAME##_push_back_p(vector_##NAME *self, TYPE *data);
 * 	vektörün sonuna eleman ekler, pointer alıyor
 * 
 * TYPE *vector_##NAME##_get(vector_##NAME *self, size_t index);
 * 	vektörün indexinci elemanının pointerını döndürür
 * 
 * TYPE vector_##NAME##_read(const vector_##NAME *self, size_t index);
 * 	vektörün indexinci elemanının değerini döndürür
 * 
 * 
 * void vector_##NAME##_bubble_sort(vector_##NAME *self, TYPE* (*key_func)(TYPE*, TYPE*));
 * 	elemanları bubble sort algoritması ile sırala (büyük olan elemanı belirlemek için fonksiyon pointerı alıyor)
 * 
 * void vector_##NAME##_swap(vector_##NAME *self, size_t index1, size_t index2);
 * 	iki indeksteki elemanları değiştirir
 * 
 * bool vector_##NAME##_insert_p(vector_##NAME *self, size_t index, TYPE *value);
 * 	verilen adresteki datayı verilen indekse kopyalar
 * 
 * bool vector_##NAME##_insert(vector_##NAME *self, size_t index, TYPE value);
 * 	verilen datayı indekse kopyalar
 * 
 * void vector_##NAME##_shift_r(vector_##NAME *self);
 * 	vektörün elemanlarını sağa kaydırır (sonuncu eleman başa geliyor)
 * 
 * void vector_##NAME##_shift_l(vector_##NAME *self);
 * 	vektörün elemanlarını sola kaydırır (baştaki eleman sola geliyor)
 * 
 * void vector_##NAME##_reverse(vector_##NAME *self);
 * 	vektörü ters döndürür
 * 
*/





int* vector_int_sort_example(int *a, int *b);

int* vector_int_sort_example(int *a, int *b) {
	return (*a > *b) ? a : b;
}

#define create_vector_t(NAME, TYPE)																							\
	typedef struct vector_##NAME{																							\
		TYPE *_start, *_end, *_capacity;																					\
	} vector_##NAME; 																										\
\
	vector_##NAME* vector_##NAME##_init_h(size_t capacity); 																\
	vector_##NAME vector_##NAME##_init(size_t capacity); 																	\
	void vector_##NAME##_destroy(vector_##NAME *self); 																		\
\
	size_t vector_##NAME##_capacity(const vector_##NAME *self); 															\
	size_t vector_##NAME##_length(const vector_##NAME *self); 																\
	size_t vector_##NAME##_size(const vector_##NAME *self); 																\
\
	vector_##NAME* vector_##NAME##_move_h(vector_##NAME *self); 															\
	vector_##NAME vector_##NAME##_move(vector_##NAME *self); 																\
	vector_##NAME* vector_##NAME##_copy_h(const vector_##NAME *self);														\
	vector_##NAME vector_##NAME##_copy(const vector_##NAME *self); 															\
\
	bool vector_##NAME##_extend_capacity(vector_##NAME *self); 																\
	bool vector_##NAME##_push_back(vector_##NAME *self, TYPE data); 														\
	bool vector_##NAME##_push_back_p(vector_##NAME *self, TYPE *data); 														\
\
	TYPE *vector_##NAME##_get(vector_##NAME *self, size_t index); 															\
	TYPE vector_##NAME##_read(const vector_##NAME *self, size_t index); 													\
\
\
	void vector_##NAME##_bubble_sort(vector_##NAME *self, TYPE* (*key_func)(TYPE*, TYPE*));									\
	void vector_##NAME##_swap(vector_##NAME *self, size_t index1, size_t index2);											\
	bool vector_##NAME##_insert_p(vector_##NAME *self, size_t index, TYPE *value);											\
	bool vector_##NAME##_insert(vector_##NAME *self, size_t index, TYPE value);												\
\
	void vector_##NAME##_shift_r(vector_##NAME *self);																		\
	void vector_##NAME##_shift_l(vector_##NAME *self);																		\
	void vector_##NAME##_reverse(vector_##NAME *self);																		\
\
/********************************************************************************/											\
\
	vector_##NAME* vector_##NAME##_init_h(size_t capacity) { 																\
		vector_##NAME *new_vector = (vector_##NAME *)malloc(sizeof(vector_##NAME)); 										\
		\
		new_vector->_start 		= (TYPE *)malloc(sizeof(TYPE) * capacity); 													\
		new_vector->_capacity	= new_vector->_start + capacity; 															\
		new_vector->_end			= new_vector->_start; 																	\
		return new_vector; 																									\
	}	\
\
	vector_##NAME vector_##NAME##_init(size_t capacity) { 																	\
		vector_##NAME new_vector; 																							\
		\
		new_vector._start 		= (TYPE *)malloc(sizeof(TYPE) * capacity); 													\
		new_vector._capacity		= new_vector._start + capacity; 														\
		new_vector._end			= new_vector._start; 																		\
		return new_vector; 																									\
	} 	\
\
	void vector_##NAME##_destroy(vector_##NAME *self) { 																	\
		free(self->_start); 																								\
	} 	\
\
	size_t vector_##NAME##_capacity(const vector_##NAME *self) { return self->_capacity - self->_start; } 					\
	size_t vector_##NAME##_length(const vector_##NAME *self) { return self->_end - self->_start; } 							\
	size_t vector_##NAME##_size(const vector_##NAME *self) { return self->_end - self->_start; } 							\
\
	vector_##NAME* vector_##NAME##_move_h(vector_##NAME *self) { 															\
		vector_##NAME *new_vector = (vector_##NAME *)malloc(sizeof(vector_##NAME)); 										\
		new_vector->_capacity = self->_capacity; 																			\
		new_vector->_start = self->_start; 																					\
		new_vector->_end = self->_end; 																						\
		self->_capacity = NULL; 																							\
		self->_start = NULL; 																								\
		self->_end = NULL; 																									\
		return new_vector; 																									\
	} 	\
\
	vector_##NAME vector_##NAME##_move(vector_##NAME *self) {																\
		vector_##NAME new_vector; 							 																\
		new_vector._capacity = self->_capacity; 			 																\
		new_vector._start = self->_start; 					  																\
		new_vector._end = self->_end; 						  																\
		self->_capacity = NULL; 							  																\
		self->_start = NULL; 								  																\
		self->_end = NULL; 									  																\
		return new_vector; 									  																\
	} 	\
\
	vector_##NAME* vector_##NAME##_copy_h(const vector_##NAME *self) { 														\
		size_t length = vector_##NAME##_length(self); 																		\
		vector_##NAME *new_vector = vector_##NAME##_init_h(vector_##NAME##_capacity(self)); 								\
		memcpy(new_vector->_start, self->_start, vector_##NAME##_capacity(self) * sizeof(TYPE)); 							\
		new_vector->_end = new_vector->_start + length; 																	\
		return new_vector; 																									\
	} 	\
\
	vector_##NAME vector_##NAME##_copy(const vector_##NAME *self) { 														\
		size_t length = vector_##NAME##_length(self); 																		\
		vector_##NAME new_vector = vector_##NAME##_init(vector_##NAME##_capacity(self)); 									\
		memcpy(new_vector._start, self->_start, vector_##NAME##_capacity(self) * sizeof(TYPE)); 							\
		new_vector._end = new_vector._start + length; 																		\
		return new_vector; 																									\
	} 	\
\
	bool vector_##NAME##_extend_capacity(vector_##NAME *self) { 															\
		size_t new_capacity = vector_##NAME##_capacity(self) * 2; 															\
		size_t length 		= vector_##NAME##_length(self); 																\
		\
		void *tmp = realloc(self->_start, new_capacity * sizeof(TYPE)); 													\
		if (tmp == NULL) return False; 																						\
		\
		self->_start 	= (TYPE *)tmp; 																						\
		self->_capacity 	= self->_start + new_capacity; 																	\
		self->_end 		= self->_start + length; 																			\
		return True; 																										\
	} 	\
\
	bool vector_##NAME##_push_back(vector_##NAME *self, TYPE data) { 														\
		if (self->_end == self->_capacity){ 																				\
			if (vector_##NAME##_extend_capacity(self) == False) 															\
				return False; 																								\
		} 																													\
		*self->_end = data; 																								\
		self->_end++; 																										\
		return True; 																										\
	} 	\
\
	bool vector_##NAME##_push_back_p(vector_##NAME *self, TYPE *data) { 													\
		if (self->_end == self->_capacity){ 																				\
			if (vector_##NAME##_extend_capacity(self) == False) 															\
				return False; 																								\
		} 																													\
		memcpy(self->_end, data, sizeof(TYPE)); 																			\
		self->_end++; 																										\
		return True; 																										\
	} 	\
\
	TYPE *vector_##NAME##_get(vector_##NAME *self, size_t index) { return self->_start + index; } 							\
	TYPE vector_##NAME##_read(const vector_##NAME *self, size_t index) { return *(self->_start + index); } 					\
\
\
	void vector_##NAME##_swap(vector_##NAME *self, size_t index1, size_t index2) {											\
		TYPE tmp = *vector_##NAME##_get(self, index1);																		\
		*vector_##NAME##_get(self, index1) = *vector_##NAME##_get(self, index2);											\
		*vector_##NAME##_get(self, index2) = tmp;																			\
	}	\
\
	bool vector_##NAME##_insert_p(vector_##NAME *self, size_t index, TYPE *value) {											\
		size_t i, length;																									\
		if (self->_end == self->_capacity)																					\
			if (vector_##NAME##_extend_capacity(self) == False)																\
				return False;																								\
		\
		length = vector_##NAME##_length(self);																				\
		for (i = length; i > index; i--)																					\
			*(self->_start + i) = *(self->_start + i - 1);																	\
		memcpy(vector_##NAME##_get(self, index), value, sizeof(TYPE));														\
		self->_end++;																										\
		return True;																										\
	}	\
\
	bool vector_##NAME##_insert(vector_##NAME *self, size_t index, TYPE value) {											\
		size_t i, length;																									\
		if (self->_end == self->_capacity)																					\
			if (vector_##NAME##_extend_capacity(self) == False)																\
				return False;																								\
		\
		length = vector_##NAME##_length(self);																				\
		for (i = length; i > index; i--)																					\
			*(self->_start + i) = *(self->_start + i - 1);																	\
		*vector_##NAME##_get(self, index) = value;																			\
		self->_end++;																										\
		return True;																										\
	}	\
\
	void vector_##NAME##_shift_r(vector_##NAME *self) {																		\
		size_t i, last_index = vector_##NAME##_length(self)-1;																\
		TYPE tmp = *vector_##NAME##_get(self, last_index);																	\
		for (i = last_index; i > 0; i--)																					\
			*vector_##NAME##_get(self, i) = *vector_##NAME##_get(self, i-1);												\
		*vector_##NAME##_get(self, 0) = tmp;																				\
	}	\
\
	void vector_##NAME##_shift_l(vector_##NAME *self) {																		\
		size_t i, length = vector_##NAME##_length(self);																	\
		TYPE tmp = *vector_##NAME##_get(self, 0);																			\
		for (i = 1; i < length; i++)																						\
			*vector_##NAME##_get(self, i-1) = *vector_##NAME##_get(self, i);												\
		*vector_##NAME##_get(self, length-1) = tmp;																			\
	}	\
\
	void vector_##NAME##_reverse(vector_##NAME *self) {																		\
		size_t i, length = vector_##NAME##_length(self);																	\
		for (i = 0; i < length/2; i++)																						\
			vector_##NAME##_swap(self, i, length-1-i);																		\
	}	\
\
	void vector_##NAME##_bubble_sort(vector_##NAME *self, TYPE* (*key_func)(TYPE*, TYPE*)){									\
	size_t i, j, last_index = vector_##NAME##_length(self)-1;																\
	for (i = 0; i < last_index; i++)																						\
		for (j = 0; j < last_index-i; j++)																					\
           	if ( vector_##NAME##_get(self, j) == key_func(vector_##NAME##_get(self, j), vector_##NAME##_get(self, j+1)) )	\
              	vector_##NAME##_swap(self, j, j+1);																			\
}	\
\
struct __internal_you_need_semicolon


#endif