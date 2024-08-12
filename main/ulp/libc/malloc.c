#include <stddef.h>
#include <stdlib.h>

#define __SYMBOL_PREFIX ""

/* We want the .gnu.warning.SYMBOL section to be unallocated.  */
#define link_warning(symbol, msg)                     \
	static const char __evoke_link_warning_##symbol[] \
	    __attribute__((section(".gnu.warning." __SYMBOL_PREFIX #symbol), __used__)) = msg;

/* A canned warning for sysdeps/stub functions.
   The GNU linker prepends a "warning: " string.  */
#define stub_warning(name) link_warning(name, #name ": Heap is disabled")

void *malloc(size_t sz)
{
	(void)sz;
	abort();
}
stub_warning(malloc);

void *calloc(size_t nb, size_t sz)
{
	(void)nb;
	(void)sz;
	abort();
}
stub_warning(calloc);

void *realloc(void *p, size_t sz)
{
	(void)p;
	(void)sz;
	abort();
}
stub_warning(realloc);

void free(void *p)
{
	(void)p;
	abort();
}
stub_warning(free);
