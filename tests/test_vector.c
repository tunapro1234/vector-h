#include <string.h>
#include <ctype.h>

#include "cu_test.h"
#include "vector/vector.h"

/* 
 * void cu_assert(cu_test* tc, char* message, int condition);
 * void cu_assert_true(cu_test* tc, int condition);
 * void cu_assert_str_equals(cu_test* tc, char* expected, char* actual);
 * void cu_assert_int_equals(cu_test* tc, int expected, int actual);
 * void cu_assert_ptr_equals(cu_test* tc, void* expected, void* actual);
 * void cu_assert_ptr_not_null(cu_test* tc, void* pointer);
 * 
 * 
 * move
 * copy
 * expand
 * ptr push back
 * get - read
 * 
 * bubble sort
 * swap 
 * insert
 * insert ptr
 * shift r
 * shift l
 * reverse
 */

typedef struct person_t {
	char* name;
	size_t age;
} person_t;

create_vector_t(person_t, person_t);
create_vector_t(int, int);

person_t* person_new() { return (person_t *)malloc(sizeof(person_t)); }

person_t* person_init(char* name, size_t age) {
	person_t *new_person = person_new();
	new_person->name = (char *)malloc(strlen(name) + 1);
	memcpy(new_person->name, name, strlen(name) + 1);
	new_person->age = age;
	return new_person;
}

void test_vector_get_read(cu_test_t *tc);
void test_vector_move(cu_test_t *tc);
void test_vector_copy(cu_test_t *tc);
void test_vector_expand(cu_test_t *tc);
void test_vector_push_back_ptr(cu_test_t *tc);
void test_vector_bubble_sort(cu_test_t *tc);
void test_vector_swap(cu_test_t *tc);
void test_vector_insert(cu_test_t *tc);
void test_vector_insert_ptr(cu_test_t *tc);
void test_vector_shift_r(cu_test_t *tc);
void test_vector_shift_l(cu_test_t *tc);
void test_vector_reverse(cu_test_t *tc);

cu_suite_t* test_vector_get_suite() {
	cu_suite_t* suite = cu_suite_new();
	
	SUITE_ADD_TEST(suite, test_vector_get_read		);
	SUITE_ADD_TEST(suite, test_vector_move			);
	SUITE_ADD_TEST(suite, test_vector_copy			);
	SUITE_ADD_TEST(suite, test_vector_expand		);
	SUITE_ADD_TEST(suite, test_vector_push_back_ptr	);
	SUITE_ADD_TEST(suite, test_vector_bubble_sort	);
	SUITE_ADD_TEST(suite, test_vector_swap			);
	SUITE_ADD_TEST(suite, test_vector_insert		);
	/* SUITE_ADD_TEST(suite, test_vector_insert_ptr	); */
	SUITE_ADD_TEST(suite, test_vector_shift_r		);
	SUITE_ADD_TEST(suite, test_vector_shift_l		);
	SUITE_ADD_TEST(suite, test_vector_reverse		);
	
	return suite;
}

void test_vector_get_read(cu_test_t *tc) {
	int i;
	vector_int v1 = vector_int_init(10);
	for (i = 0; i < 10; i++) {
		vector_int_push_back(&v1, i);
		cu_assert_int_equals(tc, i, vector_int_read(&v1, i));
	}
}

void test_vector_move(cu_test_t *tc) {
	vector_person_t *v1 = vector_person_t_init_h(2), *v2;
	person_t *p1 = person_init("p1", 1), *p2 = person_init("p2", 2);
	vector_person_t_push_back_p(v1, p1);
	vector_person_t_push_back_p(v1, p2);
	
	v2 = vector_person_t_move_h(v1);
	
	cu_assert_ptr_not_null(tc, v2->capacity);
	cu_assert_ptr_not_null(tc, v2->start);
	cu_assert_ptr_not_null(tc, v2->end);
	
	cu_assert_ptr_null(tc, v1->capacity);
	cu_assert_ptr_null(tc, v1->start);
	cu_assert_ptr_null(tc, v1->end);
}

void test_vector_copy(cu_test_t *tc) {
	vector_person_t *v1 = vector_person_t_init_h(2), *v2;
	person_t *p1 = person_init("p1", 1), *p2 = person_init("p2", 2);
	vector_person_t_push_back_p(v1, p1);
	vector_person_t_push_back_p(v1, p2);
	
	v2 = vector_person_t_copy_h(v1);
	
	cu_assert_true(tc, v1->capacity != v2->capacity);
	cu_assert_true(tc, v1->start != v2->start);
	cu_assert_true(tc, v1->end != v2->end);
}

void test_vector_expand(cu_test_t *tc) {
	size_t i;
	vector_int v1 = vector_int_init(5);
	for (i = 0; i < 10; i++) vector_int_push_back(&v1, i);
	for (i = 0; i < 10; i++) cu_assert_int_equals(tc, i, vector_int_read(&v1, i));
}

void test_vector_push_back_ptr(cu_test_t *tc) {
	vector_person_t *v1 = vector_person_t_init_h(2);
	person_t *p1 = person_init("p1", 1), *p2 = person_init("p2", 2);
	vector_person_t_push_back_p(v1, p1);
	vector_person_t_push_back_p(v1, p2);
}

void test_vector_bubble_sort(cu_test_t *tc) {
	size_t i;
	vector_int *v_ex = vector_int_init_h(6);
	vector_int *v_ac = vector_int_init_h(6);
	
	for (i = 0; i < 6; i++) vector_int_push_back(v_ex, i);
	for (i = 6; i > 0; i--) vector_int_push_back(v_ac, i - 1); 	/* (i = 6; i-- > 0; ) */
	
	vector_int_bubble_sort(v_ac, vector_int_sort_example);
	for (i = 0; i < vector_int_length(v_ex); i++) 
		cu_assert_int_equals(tc, vector_int_read(v_ex, i), vector_int_read(v_ac, i));
}

void test_vector_swap(cu_test_t *tc) {
	size_t i;
	vector_int *v1 = vector_int_init_h(3);
	for (i = 0; i < 3; i++) vector_int_push_back(v1, i);
	vector_int_swap(v1, 0, 2);
	
	cu_assert_int_equals(tc, vector_int_read(v1, 0), 2);
	cu_assert_int_equals(tc, vector_int_read(v1, 1), 1);
	cu_assert_int_equals(tc, vector_int_read(v1, 3), 0);
}

void test_vector_insert(cu_test_t *tc) {
	size_t i;
	vector_int *v1 = vector_int_init_h(3);
	for (i = 0; i < 3; i++) vector_int_push_back(v1, i);
	vector_int_insert(v1, 0, 0);

	cu_assert_int_equals(tc, 0, vector_int_read(v1, 0));
	for (i = 1; i < 4; i++) cu_assert_int_equals(tc, i - 1, vector_int_read(v1, i));
}

/*
void test_vector_insert_ptr(cu_test_t *tc) {
	size_t i;
	vector_person_t *v1 = vector_person_t_init_h(3);
	for (i = 0; i < 3; i++) vector_person_t_push_back(v1, );
	vector_int_insert(v1, 0, 0);

	cu_assert_int_equals(tc, 0, vector_int_read(v1, 0));
	for (i = 1; i < 4; i++) cu_assert_int_equals(tc, i - 1, vector_int_read(v1, i));
}
*/

void test_vector_shift_r(cu_test_t *tc) {
	size_t i;
	vector_int *v1 = vector_int_init_h(10);
	for (i = 0; i < 10; i++) vector_int_push_back(v1, i);
	vector_int_shift_r(v1);
	
	cu_assert_int_equals(tc, 9, vector_int_read(v1, 0));
	for (i = 1; i < 10; i++) cu_assert_int_equals(tc, i - 1, vector_int_read(v1, i));
}

void test_vector_shift_l(cu_test_t *tc) {
	size_t i;
	vector_int *v1 = vector_int_init_h(10);
	for (i = 0; i < 10; i++) vector_int_push_back(v1, i);
	vector_int_shift_l(v1);

	cu_assert_int_equals(tc, 0, vector_int_read(v1, 9));
	for (i = 0; i < 9; i++) cu_assert_int_equals(tc, i + 1, vector_int_read(v1, i));
}

void test_vector_reverse(cu_test_t *tc) {
	size_t i;
	vector_int *v1 = vector_int_init_h(10);
	for (i = 0; i < 10; i++) vector_int_push_back(v1, i);
	vector_int_reverse(v1);
	
	for (i = 0; i < 10; i++) 
		cu_assert_int_equals(tc, 9-i, vector_int_read(v1, i));
}
