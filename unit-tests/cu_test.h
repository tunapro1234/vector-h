#ifndef CU_TEST_H
#define CU_TEST_H

#include <setjmp.h>
#include <stdarg.h>

#define CUTEST_VERSION  "CuTest 1.5"

/* cu_string_t */

char* cu_str_alloc(int size);
char* cu_str_copy(const char* old);

#define CU_ALLOC(TYPE)		((TYPE*) malloc(sizeof(TYPE)))

#define HUGE_STRING_LEN	8192
#define STRING_MAX		256
#define STRING_INC		256

typedef struct cu_string_t {
	int length;
	int size;
	char* buffer;
} cu_string_t;

void cu_string_init(cu_string_t* str);
cu_string_t* cu_string_new(void);
void cu_string_read(cu_string_t* str, const char* path);
void cu_string_append(cu_string_t* str, const char* text);
void cu_string_append_char(cu_string_t* str, char ch);
void cu_string_append_format(cu_string_t* str, const char* format, ...);
void cu_string_insert(cu_string_t* str, const char* text, int pos);
void cu_string_resize(cu_string_t* str, int new_size);
void cu_string_delete(cu_string_t* str);

/* cu_test_t */

typedef struct cu_test_t cu_test_t;

typedef void (*test_function)(cu_test_t *);

struct cu_test_t
{
	char* name;
	test_function function;
	int failed;
	int ran;
	const char* message;
	jmp_buf *jump_buf;
};

void cu_test_init(cu_test_t* t, const char* name, test_function function);
cu_test_t* cu_test_new(const char* name, test_function function);
void cu_test_run(cu_test_t* tc);
void cu_test_delete(cu_test_t *t);

/* Internal versions of assert functions -- use the public versions */
void cu_fail_line(cu_test_t* tc, const char* file, int line, const char* message2, const char* message);
void cu_assert_line(cu_test_t* tc, const char* file, int line, const char* message, int condition);
void cu_assert_str_equals_line_msg(cu_test_t* tc, 
	const char* file, int line, const char* message, 
	const char* expected, const char* actual);
void cu_assert_int_equals_line_msg(cu_test_t* tc, 
	const char* file, int line, const char* message, 
	int expected, int actual);
void cu_assert_dbl_equals_line_msg(cu_test_t* tc, 
	const char* file, int line, const char* message, 
	double expected, double actual, double delta);
void cu_assert_ptr_equals_line_msg(cu_test_t* tc, 
	const char* file, int line, const char* message, 
	void* expected, void* actual);

/* public assert functions */

#define cu_fail(tc, ms)                        cu_fail_line(  (tc), __FILE__, __LINE__, NULL, (ms))
#define cu_assert(tc, ms, cond)                cu_assert_line((tc), __FILE__, __LINE__, (ms), (cond))
#define cu_assert_true(tc, cond)                cu_assert_line((tc), __FILE__, __LINE__, "assert failed", (cond))

#define cu_assert_str_equals(tc,ex,ac)           cu_assert_str_equals_line_msg((tc),__FILE__,__LINE__,NULL,(ex),(ac))
#define cu_assert_str_equals_msg(tc,ms,ex,ac)    cu_assert_str_equals_line_msg((tc),__FILE__,__LINE__,(ms),(ex),(ac))
#define cu_assert_int_equals(tc,ex,ac)           cu_assert_int_equals_line_msg((tc),__FILE__,__LINE__,NULL,(ex),(ac))
#define cu_assert_int_equals_msg(tc,ms,ex,ac)    cu_assert_int_equals_line_msg((tc),__FILE__,__LINE__,(ms),(ex),(ac))
#define cu_assert_dbl_equals(tc,ex,ac,dl)        cu_assert_dbl_equals_line_msg((tc),__FILE__,__LINE__,NULL,(ex),(ac),(dl))
#define cu_assert_dbl_equals_msg(tc,ms,ex,ac,dl) cu_assert_dbl_equals_line_msg((tc),__FILE__,__LINE__,(ms),(ex),(ac),(dl))
#define cu_assert_ptr_equals(tc,ex,ac)           cu_assert_ptr_equals_line_msg((tc),__FILE__,__LINE__,NULL,(ex),(ac))
#define cu_assert_ptr_equals_msg(tc,ms,ex,ac)    cu_assert_ptr_equals_line_msg((tc),__FILE__,__LINE__,(ms),(ex),(ac))

#define cu_assert_ptr_null(tc,p)        		cu_assert_line((tc),__FILE__,__LINE__,"null pointer expected", (p == NULL))
#define cu_assert_ptr_not_null(tc,p)        	cu_assert_line((tc),__FILE__,__LINE__,"null pointer unexpected", (p != NULL))
#define cu_assert_ptr_not_null_msg(tc,msg,p) 	cu_assert_line((tc),__FILE__,__LINE__,(msg),(p != NULL))

/* cu_suite_t */

#define MAX_TEST_CASES	1024

#define SUITE_ADD_TEST(SUITE,TEST)	cu_suite_add(SUITE, cu_test_new(#TEST, TEST))

typedef struct cu_suite_t {
	int count;
	cu_test_t* list[MAX_TEST_CASES];
	int fail_count;
} cu_suite_t;


void cu_suite_init(cu_suite_t* testSuite);
cu_suite_t* cu_suite_new(void);
void cu_suite_delete(cu_suite_t *testSuite);
void cu_suite_add(cu_suite_t* testSuite, cu_test_t *testCase);
void cu_suite_add_suite(cu_suite_t* testSuite, cu_suite_t* testSuite2);
void cu_suite_run(cu_suite_t* testSuite);
void cu_suite_summary(cu_suite_t* testSuite, cu_string_t* summary);
void cu_suite_details(cu_suite_t* testSuite, cu_string_t* details);

#endif /* CU_TEST_H */
