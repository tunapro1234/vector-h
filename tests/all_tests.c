#include "cu_test.h"
#include "stdio.h"

cu_suite_t* test_vector_get_suite();

int main() {
    cu_string_t *output = cu_string_new();
    cu_suite_t *main_suite = cu_suite_new();

    cu_suite_add_suite(main_suite, test_vector_get_suite());
    
    cu_suite_run(main_suite);
    cu_suite_summary(main_suite, output);
    cu_suite_details(main_suite, output);
    printf("%s\n", output->buffer);
    return 0;
}
