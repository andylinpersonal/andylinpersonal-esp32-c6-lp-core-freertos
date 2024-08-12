/* Forbid the use of static */
#include <cxxabi.h>

#include <sys/lock.h>

#include <cstdlib>

using __cxxabiv1::__guard;

#define __SYMBOL_PREFIX ""

/* We want the .gnu.warning.SYMBOL section to be unallocated.  */
#define link_warning(symbol, msg)                     \
	static const char __evoke_link_warning_##symbol[] \
	    __attribute__((section(".gnu.warning." __SYMBOL_PREFIX #symbol), __used__)) = msg;

/* A canned warning for sysdeps/stub functions.
   The GNU linker prepends a "warning: " string.  */
#define static_local_variable_warning(name) \
	link_warning(name, #name ": C++11 thread-safe guards for local static variables are not supported")

extern "C" int __cxa_guard_acquire(__guard *pg)
{
	(void)pg;
	abort();
}
static_local_variable_warning(__cxa_guard_acquire);

extern "C" void __cxa_guard_release(__guard *pg) throw()
{
	(void)pg;
	abort();
}
static_local_variable_warning(__cxa_guard_release);

extern "C" void __cxa_guard_abort(__guard *pg) throw()
{
	(void)pg;
	abort();
}
static_local_variable_warning(__cxa_guard_abort);
