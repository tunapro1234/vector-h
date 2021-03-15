#ifndef NVECTOR_H_IMPL_INCLUDED
#define NVECTOR_H_IMPL_INCLUDED

/* hata var diye çok ağlıyor */
#ifdef NVECTOR_IMPL

base_vector_t _vector_init_s(size_t size) {
    base_vector_t new_vector;
	
	new_vector._start 		= malloc(size);
	new_vector._capacity 	= (char *)new_vector._start + (size);
	new_vector._end 		= new_vector._start;

	return new_vector;
}


base_vector_t* _vector_init(size_t size) {
    base_vector_t *new_vector = (base_vector_t *)malloc(sizeof(base_vector_t));
	
	new_vector->_start 		= malloc(size);
	new_vector->_capacity 	= (char *)new_vector->_start + size;
	new_vector->_end 		= new_vector->_start;

	return new_vector;
}


void _vector_destroy(base_vector_t *self) {
	free(self->_start);
	self->_capacity = NULL;
	self->_start 	= NULL;
	self->_end 		= NULL;
}


size_t _vector_capacity(const base_vector_t *self)
	{ return ((char *)self->_capacity - (char *)self->_start); }


size_t _vector_length(const base_vector_t *self)
	{ return ((char *)self->_end - (char *)self->_start); }


size_t _vector_size(const base_vector_t *self)
	{ return ((char *)self->_end - (char *)self->_start); }


base_vector_t* _vector_move(size_t type_size, base_vector_t *self) {
	base_vector_t *new_vector = (base_vector_t *)malloc(sizeof(base_vector_t));
	
	new_vector->_capacity 	= self->_capacity;
	new_vector->_start 		= self->_start;
	new_vector->_end 		= self->_end;
	
	self->_capacity 		= NULL;
	self->_start 			= NULL;
	self->_end 				= NULL;
	return new_vector;
}


base_vector_t _vector_move_s(base_vector_t *self) {
	base_vector_t new_vector;
	
	new_vector._capacity 	= self->_capacity;
	new_vector._start 		= self->_start;
	new_vector._end 		= self->_end;
	
	self->_capacity 		= NULL;
	self->_start 			= NULL;
	self->_end 				= NULL;
	return new_vector;
}


base_vector_t* _vector_copy(const base_vector_t *self) {
	size_t length = _vector_length(self);
	base_vector_t *new_vector = _vector_init(_vector_capacity(self));
	memcpy(new_vector->_start, self->_start, _vector_capacity(self));
	new_vector->_end = (char *)new_vector->_start + length;
	return new_vector;
}


base_vector_t _vector_copy_s(const base_vector_t *self) {
	size_t length = ((char *)self->_end - (char *)self->_start);
	base_vector_t new_vector = _vector_init_s(_vector_capacity(self));
	memcpy(new_vector._start, self->_start, _vector_capacity(self));
	new_vector._end = (char *)new_vector._start + length;
	return new_vector;
}


bool _vector_resize(base_vector_t *self, size_t size) {
	size_t length 		= _vector_length(self);
	size_t new_capacity = size;
	
	void *tmp = realloc(self->_start, new_capacity);
	if (tmp == NULL) return False;

	self->_start 	= tmp;
	self->_capacity = (char *)self->_start + new_capacity;
	self->_end 		= (char *)self->_start + length;
	return True;
}


bool _vector_push_back_p(size_t type_size, base_vector_t *self, const void* data) {
	if (self->_end == self->_capacity)
		if (_vector_extend_capacity(self) == False)
			return False;

	memcpy(self->_end, data, type_size);
	self->_end = (char *)self->_end + type_size;
	return True;
}


void* _vector_get(size_t type_size, base_vector_t *self, size_t index)
	{ return (char *)self->_start + (index * type_size); }


/* mantıklı bir hareket değil biliyorum, ama her swap kullandığım fonksiyonun makroya dönüştürmek istemiyorum */
void _vector_swap
(size_t type_size, base_vector_t *self, size_t index1, size_t index2) {	
	void* tmp = malloc(type_size);
	memcpy(tmp, _vector_get(type_size, self, index1), type_size);
	memcpy(_vector_get(type_size, self, index1), _vector_get(type_size, self, index2), type_size);
	memcpy(_vector_get(type_size, self, index2), tmp, type_size);
}


bool _vector_insert_p
(size_t type_size, base_vector_t *self, size_t index, const void *value) {	
	size_t i, length;
	if (self->_end == self->_capacity)
		if (_vector_extend_capacity(self) == False)
			return False;

	length = _vector_length(self) / type_size;
	for (i = length; i > index; i--)
		memcpy(_vector_get(type_size, self, i), _vector_get(type_size, self, (i - 1)), type_size);
		/* *_vector_get(type_size, self, i) = *_vector_get(type_size, self, (i - 1)); */
		/* *((char *)self->_start + (i * type_size)) = *((char *)self->_start + ((i - 1) * type_size)); */
	memcpy(_vector_get(type_size, self, index), value, type_size);
	self->_end = (char *)self->_end + type_size;
	return True;
}


void _vector_shift_r(size_t type_size, base_vector_t *self) {
	void *tmp = malloc(type_size);
	size_t i, last_index = _vector_length(self) - 1;
	memcpy(tmp, _vector_get(type_size, self, last_index), type_size);
	for (i = last_index; i > 0; i--)
		memcpy(_vector_get(type_size, self, i), 
			_vector_get(type_size, self, i-1), type_size);
	memcpy(_vector_get(type_size, self, 0), tmp, type_size);
}


void _vector_shift_l(size_t type_size, base_vector_t *self) {
	size_t i, length = _vector_length(self);
	void *tmp = malloc(type_size);
	
	memcpy(tmp, _vector_get(type_size, self, 0), type_size);
	for (i = 1; i < length; i++)
		memcpy(_vector_get(type_size, self, i - 1), 
			_vector_get(type_size, self, i), type_size);
	memcpy(_vector_get(type_size, self, length - 1), tmp, type_size);
}


/* yavaş ama bulunsun (malloc yüzünden) */
void _vector_reverse(size_t type_size, base_vector_t *self) {
	size_t i, length = _vector_length(self) / type_size;
	for (i = 0; i < length / 2; i++)
		_vector_swap(type_size, self, i, length - 1 - i);
}


void _vector_sort_merge
(size_t type_size, base_vector_t *self, max_output_t (*max_func)(void*, void*)) {
	__vector_sort_merge(type_size, self, 0, _vector_length(self) / type_size, max_func);
}

void __vector_sort_merge
(size_t type_size, base_vector_t *self, size_t arr_start, size_t arr_length, max_output_t (*max_func)(void*, void*))	{
	size_t i = 0, li = 0, ri = 0, mid_point = 0;
	char *left_temp, *right_temp;
	max_output_t rv;
	
	if (arr_start == arr_length-1) return;	 /* 1 eleman kalinca bitir */
	mid_point = arr_start + (arr_length - arr_start) / 2; /* l+(r-l)/2 */
	
	__vector_sort_merge(type_size, self, arr_start, mid_point , max_func);
	__vector_sort_merge(type_size, self, mid_point, arr_length, max_func);
	
	left_temp  = (char *)malloc(type_size * (mid_point - arr_start ));
	right_temp = (char *)malloc(type_size * (arr_length - mid_point));

	memcpy(left_temp,  (char*)self->_start + (arr_start * type_size), type_size * (mid_point  - arr_start));
	memcpy(right_temp, (char*)self->_start + (mid_point * type_size), type_size * (arr_length - mid_point));
	
	for (i = arr_start; li < (mid_point - arr_start) && ri < (arr_length - mid_point);) {
		rv = max_func(left_temp + (li * type_size), right_temp + (ri * type_size));
		if (rv == MO_FIRST_ARG) {
			memcpy(_vector_get(type_size, self, i), right_temp + (ri * type_size), type_size);
			ri++; i++;
		} else if (rv == MO_ARGS_EQUAL) {
			memcpy(_vector_get(type_size, self, i), left_temp + (li * type_size), type_size);
			li++; i++;
			memcpy(_vector_get(type_size, self, i), right_temp + (ri * type_size), type_size);
			ri++; i++;
		} else {
			memcpy(_vector_get(type_size, self, i), left_temp + (li * type_size), type_size);
			li++; i++;
		}
	}
	
	while (li < (mid_point  - arr_start)) { memcpy(_vector_get(type_size, self, i), left_temp  + (li * type_size), type_size); li++; i++; }
	while (ri < (arr_length - mid_point)) { memcpy(_vector_get(type_size, self, i), right_temp + (ri * type_size), type_size); ri++; i++; }
	free(left_temp); free(right_temp);
}


void __vector_sort_bubble(size_t type_size, base_vector_t *self, max_output_t (*max_func)(void*, void*)) {
	size_t i, j, last_index = (_vector_length(self) / type_size) - 1;
	for (i = 0; i < last_index; i++)
		for (j = 0; j < last_index-i; j++)
			if ( MO_FIRST_ARG == max_func(_vector_get(type_size, self, j), _vector_get(type_size, self, j + 1)) )
				_vector_swap(type_size, self, j, j + 1);
}


size_t _vector_search_binary_p
(size_t type_size, base_vector_t *self, void *target, max_output_t (*max_func)(void*, void*)) {
	/* array_start = 1, array_length = (_vector_length(self) / type_size); */
	return __vector_search_binary_p(type_size, self, target, 0, (_vector_length(self) / type_size) - 1, max_func);
}

size_t __vector_search_binary_p
(size_t type_size, base_vector_t *self, void *target, size_t array_start, 
	size_t array_length, max_output_t (*max_func)(void*, void*)) 
{
	array_start++; array_length++;
	size_t mid_point; max_output_t rv;
	while (array_start <= array_length) {
		mid_point = (int)(array_start + (array_length - array_start - 2) / 2);
		rv = max_func(_vector_get(type_size, self, mid_point), target);
		if (rv == MO_ARGS_EQUAL)
			return mid_point;
		else if (rv == MO_FIRST_ARG)
			array_length = mid_point;
		else if (rv == MO_SECOND_ARG)
			array_start = mid_point + 2;
	} return -1;
}

#endif
#endif