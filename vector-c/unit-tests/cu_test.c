#include <assert.h>
#include <setjmp.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#include "cu_test.h"

/*-------------------------------------------------------------------------*
 * CuStr
 *-------------------------------------------------------------------------*/

char* cu_str_alloc(int size)
{
	char* new_str = (char*) malloc( sizeof(char) * (size) );
	return new_str;
}

char* cu_str_copy(const char* old)
{
	int len = strlen(old);
	char* new_str = cu_str_alloc(len + 1);
	strcpy(new_str, old);
	return new_str;
}

/*-------------------------------------------------------------------------*
 * cu_string_t
 *-------------------------------------------------------------------------*/

void cu_string_init(cu_string_t* str)
{
	str->length = 0;
	str->size = STRING_MAX;
	str->buffer = (char*) malloc(sizeof(char) * str->size);
	str->buffer[0] = '\0';
}

cu_string_t* cu_string_new(void)
{
	cu_string_t* str = (cu_string_t*) malloc(sizeof(cu_string_t));
	str->length = 0;
	str->size = STRING_MAX;
	str->buffer = (char*) malloc(sizeof(char) * str->size);
	str->buffer[0] = '\0';
	return str;
}

void cu_string_delete(cu_string_t *str)
{
        if (!str) return;
        free(str->buffer);
        free(str);
}

void cu_string_resize(cu_string_t* str, int new_size)
{
	str->buffer = (char*) realloc(str->buffer, sizeof(char) * new_size);
	str->size = new_size;
}

void cu_string_append(cu_string_t* str, const char* text)
{
	int length;

	if (text == NULL) {
		text = "NULL";
	}

	length = strlen(text);
	if (str->length + length + 1 >= str->size)
		cu_string_resize(str, str->length + length + 1 + STRING_INC);
	str->length += length;
	strcat(str->buffer, text);
}

void cu_string_append_char(cu_string_t* str, char ch)
{
	char text[2];
	text[0] = ch;
	text[1] = '\0';
	cu_string_append(str, text);
}

void cu_string_append_format(cu_string_t* str, const char* format, ...)
{
	va_list argp;
	char buf[HUGE_STRING_LEN];
	va_start(argp, format);
	vsprintf(buf, format, argp);
	va_end(argp);
	cu_string_append(str, buf);
}

void cu_string_insert(cu_string_t* str, const char* text, int pos)
{
	int length = strlen(text);
	if (pos > str->length)
		pos = str->length;
	if (str->length + length + 1 >= str->size)
		cu_string_resize(str, str->length + length + 1 + STRING_INC);
	memmove(str->buffer + pos + length, str->buffer + pos, (str->length - pos) + 1);
	str->length += length;
	memcpy(str->buffer + pos, text, length);
}

/*-------------------------------------------------------------------------*
 * cu_test_t
 *-------------------------------------------------------------------------*/

void cu_test_init(cu_test_t* t, const char* name, test_function function)
{
	t->name = cu_str_copy(name);
	t->failed = 0;
	t->ran = 0;
	t->message = NULL;
	t->function = function;
	t->jump_buf = NULL;
}

cu_test_t* cu_test_new(const char* name, test_function function)
{
	cu_test_t* tc = CU_ALLOC(cu_test_t);
	cu_test_init(tc, name, function);
	return tc;
}

void cu_test_delete(cu_test_t *t)
{
        if (!t) return;
        free(t->name);
        free(t);
}

void cu_test_run(cu_test_t* tc)
{
	jmp_buf buf;
	tc->jump_buf = &buf;
	if (setjmp(buf) == 0)
	{
		tc->ran = 1;
		(tc->function)(tc);
	}
	tc->jump_buf = 0;
}

static void cu_fail_internal(cu_test_t* tc, const char* file, int line, cu_string_t* string)
{
	char buf[HUGE_STRING_LEN];

	sprintf(buf, "%s:%d: ", file, line);
	cu_string_insert(string, buf, 0);

	tc->failed = 1;
	tc->message = string->buffer;
	if (tc->jump_buf != 0) longjmp(*(tc->jump_buf), 0);
}

void cu_fail_line(cu_test_t* tc, const char* file, int line, const char* message2, const char* message)
{
	cu_string_t string;

	cu_string_init(&string);
	if (message2 != NULL) 
	{
		cu_string_append(&string, message2);
		cu_string_append(&string, ": ");
	}
	cu_string_append(&string, message);
	cu_fail_internal(tc, file, line, &string);
}

void cu_assert_line(cu_test_t* tc, const char* file, int line, const char* message, int condition)
{
	if (condition) return;
	cu_fail_line(tc, file, line, NULL, message);
}

void cu_assert_str_equals_line_msg(cu_test_t* tc, const char* file, int line, const char* message, 
	const char* expected, const char* actual)
{
	cu_string_t string;
	if ((expected == NULL && actual == NULL) ||
	    (expected != NULL && actual != NULL &&
	     strcmp(expected, actual) == 0))
	{
		return;
	}

	cu_string_init(&string);
	if (message != NULL) 
	{
		cu_string_append(&string, message);
		cu_string_append(&string, ": ");
	}
	cu_string_append(&string, "expected <");
	cu_string_append(&string, expected);
	cu_string_append(&string, "> but was <");
	cu_string_append(&string, actual);
	cu_string_append(&string, ">");
	cu_fail_internal(tc, file, line, &string);
}

void cu_assert_int_equals_line_msg(cu_test_t* tc, const char* file, int line, const char* message, 
	int expected, int actual)
{
	char buf[STRING_MAX];
	if (expected == actual) return;
	sprintf(buf, "expected <%d> but was <%d>", expected, actual);
	cu_fail_line(tc, file, line, message, buf);
}

void cu_assert_dbl_equals_line_msg(cu_test_t* tc, const char* file, int line, const char* message, 
	double expected, double actual, double delta)
{
	char buf[STRING_MAX];
	if (fabs(expected - actual) <= delta) return;
	sprintf(buf, "expected <%f> but was <%f>", expected, actual); 

	cu_fail_line(tc, file, line, message, buf);
}

void cu_assert_ptr_equals_line_msg(cu_test_t* tc, const char* file, int line, const char* message, 
	void* expected, void* actual)
{
	char buf[STRING_MAX];
	if (expected == actual) return;
	sprintf(buf, "expected pointer <0x%p> but was <0x%p>", expected, actual);
	cu_fail_line(tc, file, line, message, buf);
}


/*-------------------------------------------------------------------------*
 * cu_suite_t
 *-------------------------------------------------------------------------*/

void cu_suite_init(cu_suite_t* test_suite)
{
	test_suite->count = 0;
	test_suite->fail_count = 0;
        memset(test_suite->list, 0, sizeof(test_suite->list));
}

cu_suite_t* cu_suite_new(void)
{
	cu_suite_t* test_suite = CU_ALLOC(cu_suite_t);
	cu_suite_init(test_suite);
	return test_suite;
}

void cu_suite_delete(cu_suite_t *test_suite)
{
        unsigned int n;
        for (n=0; n < MAX_TEST_CASES; n++)
        {
                if (test_suite->list[n])
                {
                        cu_test_delete(test_suite->list[n]);
                }
        }
        free(test_suite);

}

void cu_suite_add(cu_suite_t* test_suite, cu_test_t *test_case)
{
	assert(test_suite->count < MAX_TEST_CASES);
	test_suite->list[test_suite->count] = test_case;
	test_suite->count++;
}

void cu_suite_add_suite(cu_suite_t* test_suite, cu_suite_t* test_suite_2)
{
	int i;
	for (i = 0 ; i < test_suite_2->count ; ++i)
	{
		cu_test_t* test_case = test_suite_2->list[i];
		cu_suite_add(test_suite, test_case);
	}
}

void cu_suite_run(cu_suite_t* test_suite)
{
	int i;
	for (i = 0 ; i < test_suite->count ; ++i)
	{
		cu_test_t* test_case = test_suite->list[i];
		printf("Running: %s()...\n", test_case->name);
		cu_test_run(test_case);
		if (test_case->failed) { test_suite->fail_count += 1; }
	}
}

void cu_suite_summary(cu_suite_t* test_suite, cu_string_t* summary)
{
	int i;
	for (i = 0 ; i < test_suite->count ; ++i)
	{
		cu_test_t* test_case = test_suite->list[i];
		cu_string_append(summary, test_case->failed ? "F" : ".");
	}
	cu_string_append(summary, "\n\n");
}

void cu_suite_details(cu_suite_t* test_suite, cu_string_t* details)
{
	int i;
	int fail_count = 0;

	if (test_suite->fail_count == 0)
	{
		int passCount = test_suite->count - test_suite->fail_count;
		const char* testWord = passCount == 1 ? "test" : "tests";
		cu_string_append_format(details, "OK (%d %s)\n", passCount, testWord);
	}
	else
	{
		if (test_suite->fail_count == 1)
			cu_string_append(details, "There was 1 failure:\n");
		else
			cu_string_append_format(details, "There were %d failures:\n", test_suite->fail_count);

		for (i = 0 ; i < test_suite->count ; ++i)
		{
			cu_test_t* test_case = test_suite->list[i];
			if (test_case->failed)
			{
				fail_count++;
				cu_string_append_format(details, "%d) %s: %s\n",
					fail_count, test_case->name, test_case->message);
			}
		}
		cu_string_append(details, "\n!!!FAILURES!!!\n");

		cu_string_append_format(details, "Runs: %d ",   test_suite->count);
		cu_string_append_format(details, "Passes: %d ", test_suite->count - test_suite->fail_count);
		cu_string_append_format(details, "Fails: %d\n",  test_suite->fail_count);
	}
}
