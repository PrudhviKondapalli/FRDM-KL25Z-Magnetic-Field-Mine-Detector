/**
 * Default libraries allowed
 */
#include "systick.h"
#include "MKL25Z4.h"

/**
 * User defined variables
 */
volatile int ticks_since_startup = 0;

/**
 * @brief      {Systick Initialization for startup before my while(1) even starts}
 * @type       {void)
 * @return     {None}
 */
void Init_SysTick(void)
{
 SysTick->LOAD = (CLOCK * TICK_SEC);         //set reload to get 1s interrupts
 NVIC_SetPriority (SysTick_IRQn, 3);     //Set interrupt priority
 SysTick->VAL = 0;                       //Force Load of reload value
}

/**
 * @brief      {Systick handler which gets executed every tick, each tick is 1sec}
 * @type       {void)
 * @return     {None}
 * @Credits: Collaboration - Sonal Tamrakar
 */
void SysTick_Handler(void)
{
	ticks_since_startup++;        //Make tick true every time systick runs out. Each Tick is 62.5ms
}

/**
 * @brief      {Systick get timer, to get the present time for time stamp purpose}
 * @type       {void)
 * @return     {Present time in milliseconds}
 */
volatile uint32_t get_timer_now(void)
{
	return(ticks_since_startup);
}

void systick_enable(void)
{
	SysTick->CTRL = SysTick_CTRL_TICKINT_Msk | SysTick_CTRL_ENABLE_Msk;  //Enable Interrupt and enable systick timer
}

