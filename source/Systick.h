#ifndef SYSTICK_H
#define SYSTICK_H

#include <stdbool.h>
#include <stdint.h>
/**
 * User defined macros
 */
#define CLOCK (48000000UL)
#define FREQUENCY_OF_EACH_TICK (16)
#define TICK_SEC (1.0/FREQUENCY_OF_EACH_TICK)

/**
 * User defined functions
 */
void Init_SysTick(void);
void SysTick_Handler(void);
volatile uint32_t get_timer_now(void);
void systick_enable(void);

#endif /* SYSTICK_H */
