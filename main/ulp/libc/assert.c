#include <stdlib.h>

void __attribute__((noreturn)) __assert_func(const char *file, int line, const char *func, const char *expr)
{
	(void)file;
	(void)line;
	(void)func;
	(void)expr;
	abort();
}

void __attribute__((noreturn)) __assert(const char *file, int line, const char *failedexpr)
{
	(void)file;
	(void)line;
	(void)failedexpr;
	abort();
}
