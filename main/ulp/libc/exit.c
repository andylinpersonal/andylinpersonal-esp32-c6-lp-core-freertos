/**
 * Splitted from the second half of `lp_core_startup()` after `main()`.
 * @see ${IDF_PATH}/components/ulp/lp_core/lp_core/lp_core_startup.c
 */
#include <sdkconfig.h>

#include <soc/soc_caps.h>
#if SOC_LP_TIMER_SUPPORTED
#include <ulp_lp_core_lp_timer_shared.h>
#include <ulp_lp_core_memory_shared.h>
#endif
#include <ulp_lp_core_utils.h>

typedef void (*fini_fn)(void);
extern fini_fn __fini_array_start[];
extern fini_fn __fini_array_end[];
extern fini_fn __fini_priority_array_start[];
extern fini_fn __fini_priority_array_end[];

void exit(int code)
{
	(void)code; // TODO: print out non-zero return code?

	for (fini_fn *dtor = __fini_array_start; dtor < __fini_priority_array_end; dtor++) {
		if (*dtor != NULL) {
			(*dtor)();
		}
	}

#if SOC_LP_TIMER_SUPPORTED
	ulp_lp_core_memory_shared_cfg_t *shared_mem           = ulp_lp_core_memory_shared_cfg_get();
	uint64_t                         sleep_duration_ticks = shared_mem->sleep_duration_ticks;

	if (sleep_duration_ticks) {
		ulp_lp_core_lp_timer_set_wakeup_ticks(sleep_duration_ticks);
	}
#endif // SOC_LP_TIMER_SUPPORTED

	ulp_lp_core_halt();
}
