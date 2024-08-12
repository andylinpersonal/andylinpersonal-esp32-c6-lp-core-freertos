/**
 * Aim for running static initializers, constructors between startup code and main,
 * and running static finalizers and destructors between main and halt code.
 * @ref https://gcc.gnu.org/onlinedocs/gccint/Initialization.html
 */

#include <stddef.h>
#include <ulp_lp_core_print.h>

int        premain(void) __attribute__((section(".text.startup"))); // pre-main and post-main handler
extern int main(void);                                              // int main(void);

typedef void (*init_fn)(void);
typedef void (*fini_fn)(void);

extern init_fn __init_priority_array_start[];
extern init_fn __init_priority_array_end[];
extern init_fn __init_array_start[];
extern init_fn __init_array_end[];
extern fini_fn __fini_array_start[];
extern fini_fn __fini_array_end[];
extern fini_fn __fini_priority_array_start[];
extern fini_fn __fini_priority_array_end[];

int premain(void)
{
	for (init_fn *init = __init_priority_array_start; init < __init_array_end; init++) {
		if (*init != NULL) {
			(*init)();
		}
	}

	int ret = main();

	for (fini_fn *dtor = __fini_array_start; dtor < __fini_priority_array_end; dtor++) {
		if (*dtor != NULL) {
			(*dtor)();
		}
	}

	return ret;
}
