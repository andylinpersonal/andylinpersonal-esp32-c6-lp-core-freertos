/**
 * Aim for running static initializers, constructors between startup code and main,
 * and running static finalizers and destructors between main and halt code.
 * @ref https://gcc.gnu.org/onlinedocs/gccint/Initialization.html
 */

#include <sdkconfig.h>

#include <esp_rom_caps.h>
#include <rom/ets_sys.h>
#include <soc/soc_caps.h>
#include <stddef.h>
#include <ulp_lp_core_utils.h>

extern int main(void);

typedef void (*init_fn)(void);
extern init_fn __init_priority_array_start[];
extern init_fn __init_priority_array_end[];
extern init_fn __init_array_start[];
extern init_fn __init_array_end[];

/* Initialize lp core related system functions before calling user's main*/
void lp_core_startup()
{
#if CONFIG_ULP_HP_UART_CONSOLE_PRINT && ESP_ROM_HAS_LP_ROM
	ets_install_putc1(lp_core_print_char);
#endif

	ulp_lp_core_update_wakeup_cause();

	for (init_fn *ctor = __init_priority_array_start; ctor < __init_array_end; ctor++) {
		if (*ctor != NULL) {
			(*ctor)();
		}
	}

	exit(main());
}
