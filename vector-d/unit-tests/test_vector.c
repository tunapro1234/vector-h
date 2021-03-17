#include <string.h>
#include <ctype.h>

#include "cu_test.h"

#define NVECTOR_IMPL
#include "../new_vector.h"

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
 * swap 
 * insert
 * insert ptr
 * shift r
 * shift l
 * reverse
 * bubble sort
 * merge sort
 */

const size_t default_test_len = 50;

typedef struct person_t {
	char* name;
	size_t age;
} person_t;


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
void test_vector_swap(cu_test_t *tc);
void test_vector_insert(cu_test_t *tc);
void test_vector_insert_ptr(cu_test_t *tc);
void test_vector_shift_r(cu_test_t *tc);
void test_vector_shift_l(cu_test_t *tc);
void test_vector_reverse(cu_test_t *tc);
void test_vector_sort_bubble(cu_test_t *tc);
void test_vector_sort_merge(cu_test_t *tc);
void test_vector_search_linear(cu_test_t *tc);
void test_vector_search_binary(cu_test_t *tc);
void test_base_vector_typed_funcs(cu_test_t *tc);

cu_suite_t* test_vector_get_suite() {
	cu_suite_t* suite = cu_suite_new();
	
	SUITE_ADD_TEST(suite, test_vector_get_read			);
	SUITE_ADD_TEST(suite, test_vector_move				);
	SUITE_ADD_TEST(suite, test_vector_copy				);
	SUITE_ADD_TEST(suite, test_vector_expand			);
	SUITE_ADD_TEST(suite, test_vector_push_back_ptr		);
	SUITE_ADD_TEST(suite, test_vector_swap				);
	SUITE_ADD_TEST(suite, test_vector_insert			);
	SUITE_ADD_TEST(suite, test_vector_insert_ptr		); 
	SUITE_ADD_TEST(suite, test_vector_shift_r			);
	SUITE_ADD_TEST(suite, test_vector_shift_l			);
	SUITE_ADD_TEST(suite, test_vector_reverse			);
	SUITE_ADD_TEST(suite, test_vector_sort_bubble		);
	SUITE_ADD_TEST(suite, test_vector_sort_merge		);
	SUITE_ADD_TEST(suite, test_vector_search_linear		);
	SUITE_ADD_TEST(suite, test_vector_search_binary		);
	SUITE_ADD_TEST(suite, test_base_vector_typed_funcs	);
	
	return suite;
}


void test_vector_get_read(cu_test_t *tc) {
#define LEN default_test_len
	size_t i;
	base_vector_t *v1 = _vector_init(sizeof(int) * LEN);
	for (i = 0; i < LEN; i++) {
		vector_push_back(int, v1, i);
		cu_assert_int_equals(tc, i, vector_read(int, v1, i));
	}
#undef LEN
}


void test_vector_move(cu_test_t *tc) {
	base_vector_t *v1 = _vector_init(sizeof(person_t) * 2), *v2;
	person_t *p1 = person_init("p1", 1), *p2 = person_init("p2", 2);
	vector_push_back_p(person_t, v1, p1);
	vector_push_back_p(person_t, v1, p2);
	
	v2 = _vector_move(sizeof(person_t), v1);
	
	cu_assert_ptr_not_null(tc, v2->_capacity);
	cu_assert_ptr_not_null(tc, v2->_start);
	cu_assert_ptr_not_null(tc, v2->_end);
	
	cu_assert_ptr_null(tc, v1->_capacity);
	cu_assert_ptr_null(tc, v1->_start);
	cu_assert_ptr_null(tc, v1->_end);
}


void test_vector_copy(cu_test_t *tc) {
	base_vector_t *v1 = _vector_init(sizeof(person_t) * 2), *v2;
	person_t *p1 = person_init("p1", 1), *p2 = person_init("p2", 2);
	vector_push_back_p(person_t, v1, p1);
	vector_push_back_p(person_t, v1, p2);
	
	v2 = _vector_copy(v1);
	
	cu_assert_true(tc, v1->_capacity != v2->_capacity);
	cu_assert_true(tc, v1->_start 	 != v2->_start	 );
	cu_assert_true(tc, v1->_end 	 != v2->_end	 );
}


void test_vector_expand(cu_test_t *tc) {
#define LEN default_test_len
	size_t i;
	base_vector_t *v1 = _vector_init(sizeof(int) * LEN);
	for (i = 0; i < LEN * 2; i++) vector_push_back(int, v1, i);
	for (i = 0; i < LEN * 2; i++) cu_assert_int_equals(tc, i, vector_read(int, v1, i));
#undef LEN
}


void test_vector_push_back_ptr(cu_test_t *tc) {
	base_vector_t *v1 = _vector_init(sizeof(person_t) * 2);
	person_t *p1 = person_init("p1", 1), *p2 = person_init("p2", 2);
	vector_push_back_p(person_t, v1, p1);
	vector_push_back_p(person_t, v1, p2);
}


void test_vector_swap(cu_test_t *tc) {
	size_t i;
	base_vector_t *v1 = _vector_init(sizeof(int) * 3);
	for (i = 0; i < 3; i++) vector_push_back(int, v1, i);
	vector_swap(int, v1, 0, 2);
	
	cu_assert_int_equals(tc, vector_read(int, v1, 0), 2);
	cu_assert_int_equals(tc, vector_read(int, v1, 1), 1);
	cu_assert_int_equals(tc, vector_read(int, v1, 2), 0); 
}


void test_vector_insert(cu_test_t *tc) {
#define LEN default_test_len
	size_t i;
	base_vector_t *v1 = _vector_init(sizeof(int) * LEN);
	for (i = 0; i < LEN; i++) vector_push_back(int, v1, i);
	vector_insert(int, v1, 0, 0);

	cu_assert_int_equals(tc, 0, vector_read(int, v1, 0));
	for (i = 1; i < (LEN+1); i++) cu_assert_int_equals(tc, i - 1, vector_read(int, v1, i));
#undef LEN
}


void test_vector_insert_ptr(cu_test_t *tc) {
#define LEN default_test_len
	size_t i;
	base_vector_t *v1 = _vector_init(sizeof(person_t) * LEN);
	for (i = 0; i < LEN; i++) vector_push_back_p(person_t, v1, person_init("a", i));
	vector_insert_p(person_t, v1, 0, person_init("a", 0));

	cu_assert_int_equals(tc, 0, vector_read(person_t, v1, 0).age);
	for (i = 1; i < (LEN+1); i++) cu_assert_int_equals(tc, i - 1, vector_read(person_t, v1, i).age);
#undef LEN
}


void test_vector_shift_r(cu_test_t *tc) {
#define LEN default_test_len
	size_t i;
	base_vector_t *v1 = _vector_init(sizeof(int) * LEN);
	for (i = 0; i < LEN; i++) vector_push_back(int, v1, i);
	vector_shift_r(int, v1);
	
	cu_assert_int_equals(tc, (LEN-1), vector_read(int, v1, 0));
	for (i = 1; i < LEN; i++) cu_assert_int_equals(tc, i - 1, vector_read(int, v1, i));
#undef LEN
}


void test_vector_shift_l(cu_test_t *tc) {
#define LEN default_test_len
	size_t i;
	base_vector_t *v1 = _vector_init(sizeof(int) * LEN);
	for (i = 0; i < LEN; i++) vector_push_back(int, v1, i);
	vector_shift_l(int, v1);

	cu_assert_int_equals(tc, 0, vector_read(int, v1, (LEN-1)));
	for (i = 0; i < (LEN-1); i++) cu_assert_int_equals(tc, i + 1, vector_read(int, v1, i));
#undef LEN
}


void test_vector_reverse(cu_test_t *tc) {
#define LEN default_test_len
	size_t i;
	base_vector_t *v1 = _vector_init(sizeof(int) * LEN);
	for (i = 0; i < LEN; i++) vector_push_back(int, v1, i);
	vector_reverse(int, v1);
	
	for (i = 0; i < LEN; i++) 
		cu_assert_int_equals(tc, (LEN-1)-i, vector_read(int, v1, i));
#undef LEN
}


void test_vector_sort_bubble(cu_test_t *tc) {
#define LEN default_test_len
	size_t i;
	base_vector_t *v_ex = _vector_init(sizeof(int) * LEN);
	base_vector_t *v_ac = _vector_init(sizeof(int) * LEN);
	
	for (i = 0; i < LEN; i++) vector_push_back(int, v_ex, i);
	for (i = LEN; i > 0; i--) vector_push_back(int, v_ac, i - 1); 	/* (i = 6; i-- > 0; ) */
	
	vector_sort_bubble(int, v_ac, s32_max_func);
	for (i = 0; i < LEN; i++) 
		cu_assert_int_equals(tc, vector_read(int, v_ex, i), vector_read(int, v_ac, i));
#undef LEN
}


void test_vector_sort_merge(cu_test_t *tc) {
#define LEN default_test_len
	size_t i;
	base_vector_t *v_ex = _vector_init(sizeof(int) * LEN);
	base_vector_t *v_ac = _vector_init(sizeof(int) * LEN);
	
	for (i = 0; i < LEN; i++) vector_push_back(int, v_ex, i);
	for (i = LEN; i > 0; i--) vector_push_back(int, v_ac, i - 1); 	/* (i = 6; i-- > 0; ) */
	
	vector_sort_merge(int, v_ac, s32_max_func);
	for (i = 0; i < LEN; i++) 
		cu_assert_int_equals(tc, vector_read(int, v_ex, i), vector_read(int, v_ac, i));
#undef LEN
}


void test_vector_search_linear(cu_test_t *tc) {
#define LEN default_test_len
	base_vector_t *v1 = _vector_init(sizeof(int) * LEN); size_t i;
	for (i = 0; i < LEN; i++) vector_push_back(int, v1, i);

	for (i = 0; i < LEN; i++) {
		cu_assert_int_equals(tc, i, vector_search_linear(int, v1, i, s32_max_func));
	}
#undef LEN
}


void test_vector_search_binary(cu_test_t *tc) {
#define LEN default_test_len
	base_vector_t *v1 = _vector_init(sizeof(int) * LEN); size_t i;
	for (i = 0; i < LEN; i++) vector_push_back(int, v1, i);

	for (i = 0; i < LEN; i++)
		cu_assert_int_equals(tc, i, 
			vector_search_binary(int, v1, i, s32_max_func));
#undef LEN
}


void test_base_vector_typed_funcs(cu_test_t *tc) {
	base_vector_t v1 = _vector_init_s(sizeof(int) * 10);

	vector_push_back(int, &v1, 10);
	cu_assert_int_equals(tc, 10, vector_read(int, &v1, 0));
}

