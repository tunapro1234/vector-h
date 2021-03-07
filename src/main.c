
#include "main.h"

#include "vector.h"
/* #include "test/v1_int_test.h" */

/*
 * vector_int* vector_int_init_h(size_t capacity);
 * vector_int vector_int_init(size_t capacity);
 * 
 * void* vector_int_destroy(vector_int *self);
 * 
 * size_t vector_int_capacity(const vector_int *self);
 * size_t vector_int_length(const vector_int *self);
 * 
 * vector_int* vector_int_move_h(vector_int *self);
 * vector_int vector_int_move(vector_int *self);
 * vector_int* vector_int_copy_h(const vector_int *self);
 * vector_int vector_int_copy(const vector_int *self);
 * 
 * bool vector_int_extend_capacity(vector_int *self);
 * bool vector_int_push_back(vector_int *self, int data);
 * bool vector_int_p_push_back(vector_int *self, int *data);
 * 
 * int *vector_int_get(vector_int *self, size_t index);
 * int vector_int_read(const vector_int *self, size_t index);
*/

typedef struct person_t {
	u8* name;
	u32 age;
} person_t;

person_t* person_init(u8 *name, u32 age) {
	person_t *new_person = (person_t *)malloc(sizeof(person_t));
	new_person->name = (u8 *)malloc(strlen(name) + 1);
	memcpy(new_person->name, name, strlen(name) + 1);
	new_person->age = age;
	return new_person;
}

create_vector_t(person_t)
create_vector_t(int)

void test_vector_int();
void test_vector_person_t();
int* vector_int_sort_example(int *a, int *b);

int* vector_int_sort_example(int *a, int *b) {
	/* büyük olanı döndürüyor */
	return (*a > *b) ? a : b;
}

int main() {
	test_vector_person_t();
	return 0;
}

void test_vector_person_t() {
	size_t i;
	vector_person_t v1;
	person_t p1 = *person_init("Tuna", 16);
	
	v1 = vector_person_t_init(10);
	for (i = 0; i < 20; i++) {
		p1.age = i;
		vector_person_t_push_back(&v1, p1);
	}

	for (i = 0; i < vector_person_t_length(&v1); i++) {
		person_t person = vector_person_t_read(&v1, i);
		printf("%s, %u\n", person.name, person.age);
	}
}

void test_vector_int() {
	size_t i;
	vector_int v1, *v2, *v3;
	int a = 50, *b = &a;
	
	v1 = vector_int_init(5);
	printf("%u, %u\n", vector_int_capacity(&v1), vector_int_length(&v1));
	
	v2 = vector_int_copy_h(&v1);
	printf("%u, %u\n", vector_int_capacity(v2), vector_int_length(v2));
	
	for (i = 0; i < 10; i++) {
		vector_int_push_back(v2, i);
		printf("%u ", vector_int_capacity(v2));
	}
	vector_int_p_push_back(v2, b);
	
	printf("\n");
	for (i = 0; i < vector_int_length(v2); i++)
		printf("%d ", vector_int_read(v2, i));
	printf("\n%u\n", vector_int_capacity(v2));

	for (i = 0; i < vector_int_size(v2); i++)
		printf("%d ", *vector_int_get(v2, i));
	printf("\n\n\n");

	/********************************************************************************/

	v3 = vector_int_init_h(5);
	for (i = 0; i < 6; i++)
		vector_int_push_back(v3, i);

	for (i = 0; i < 6; i++)
		printf("%d ", *vector_int_get(v3, i));

	vector_int_reverse(v3);
	
	printf("\n");
	for (i = 0; i < 6; i++)
		printf("%d ", *vector_int_get(v3, i));
	
	vector_int_bubble_sort(v3, vector_int_sort_example);

	printf("\n");
	for (i = 0; i < 6; i++)
		printf("%d ", *vector_int_get(v3, i));
}
