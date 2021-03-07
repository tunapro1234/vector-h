
#include "main.h"

#include "vector.h"

/*
 * vector_int_t* vector_int_init_h(size_t capacity);
 * vector_int_t vector_int_init(size_t capacity);
 * 
 * void* vector_int_destroy(vector_int_t *self);
 * 
 * size_t vector_int_capacity(const vector_int_t *self);
 * size_t vector_int_length(const vector_int_t *self);
 * 
 * vector_int_t* vector_int_move_h(vector_int_t *self);
 * vector_int_t vector_int_move(vector_int_t *self);
 * vector_int_t* vector_int_copy_h(const vector_int_t *self);
 * vector_int_t vector_int_copy(const vector_int_t *self);
 * 
 * bool vector_int_extend_capacity(vector_int_t *self);
 * bool vector_int_push_back(vector_int_t *self, int data);
 * bool vector_int_p_push_back(vector_int_t *self, int *data);
 * 
 * int *vector_int_get(vector_int_t *self, size_t index);
 * int vector_int_read(const vector_int_t *self, size_t index);
*/

vector_t(int)

int main() {
	printf("aa\n");
	vector_int_t v1 = vector_int_init(5);
	printf("%u, %u\n", vector_int_capacity(&v1), vector_int_length(&v1));
	
	vector_int_t *v2 = vector_int_copy_h(&v1);
	printf("%u, %u\n", vector_int_capacity(v2), vector_int_length(v2));
	
	for (int i = 0; i < 10; i++) {
		vector_int_push_back(v2, i);
		printf("%u ", vector_int_capacity(v2));
	}
	
	int a = 50, *b = &a;
	vector_int_p_push_back(v2, b);
	
	printf("\n");
	for (int i = 0; i < vector_int_length(v2); i++)
		printf("%d ", vector_int_read(v2, i));
	printf("\n%u\n", vector_int_capacity(v2));

	for (int i = 0; i < vector_int_size(v2); i++)
		printf("%d ", *vector_int_get(v2, i));
	printf("\n");

	return 0;
}
