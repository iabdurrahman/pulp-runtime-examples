/**
	* Copyright (C) 2025 ICDEC
	*
	* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
	* EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
	* OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
	* NONINFRINGEMENT.
	*/

#include <stdbool.h>
#include <stdint.h>

#include <stdio.h>

#include <pulp.h>

#ifndef   TEST_TIMER_ID
#define   TEST_TIMER_ID   TIMER_HI
#endif

bool           is_interrupt_raised = false;
unsigned int   counter_1s = 0;

/*static __attribute__ ((interrupt ("machine"))) void timer_irq_handler(void);*/
static __attribute__ ((interrupt))             void timer_irq_handler(void);
/*static                                         void timer_irq_handler(void);*/

int main(void)
{
	uint32_t interrupt_mask;

	printf("Entering test\n");

	/**
		* **************************************************
		* enable interrupt
		* **************************************************
		*/
	pos_irq_init();

	interrupt_mask = hal_itc_enable_value_get();
	switch (TEST_TIMER_ID)
	{
	case (TIMER_LO):
		rt_irq_set_handler(10, &timer_irq_handler);
		hal_itc_enable_set(interrupt_mask | (1 << 10));
		break;
	case (TIMER_HI):
		rt_irq_set_handler(11, &timer_irq_handler);
		hal_itc_enable_set(interrupt_mask | (1 << 11));
		break;
	default:
		/* error */
		while (1)
		{
		}
	}

	/**
		* **************************************************
		* setup timer
		* **************************************************
		*/

	/* stop and reset timer */
	timer_stop(timer_base_fc(0, 0), TEST_TIMER_ID);
	timer_reset(timer_base_fc(0, 0), TEST_TIMER_ID);

	/**
		* configure timer
		*/
	timer_set_clock_source(timer_base_fc(0, 0), TEST_TIMER_ID, false); /* set clock source to fll */

	/**
		* enable prescaler
		* since fll frequency is 12.5 MHz, timer will increment every 0.08 us
		* if prescaler set to 250, then second-stage timer will increment every
		* 0.08 us * 250 = 20 us
		*
		* to make timer raise interrupt every 1 sec, we need compare value:
		* 1 s / 20 us = 50000
		*/
	timer_set_prescaler(timer_base_fc(0, 0), TEST_TIMER_ID, true, 250);

	/**
		* mode continue
		* reset counter value after compare value reached
		*/
	timer_set_continuity(timer_base_fc(0, 0), TEST_TIMER_ID, false, true);

	/**
		* set compare value according previous calculation
		*/
	timer_cmp_set(timer_base_fc(0, 0), TEST_TIMER_ID, 50000);


	/* enable interrupt line */
	timer_enable_irq(timer_base_fc(0, 0), TEST_TIMER_ID);


	/* start timer */
	timer_start(timer_base_fc(0, 0), TEST_TIMER_ID);


	/* check is interrupt is raised */
	while (true)
	{
		if (is_interrupt_raised)
		{
			uint32_t timer_counter_value = 0;

			is_interrupt_raised = false;

			switch (TEST_TIMER_ID)
			{
			case (0):
				hal_itc_ack_set(1 << 10);
				break;
			case (1):
				hal_itc_ack_set(1 << 11);
				break;
			}


			/* get timer counter value */
			timer_counter_value = timer_count_get(timer_base_fc(0, 0), TEST_TIMER_ID);

			printf("counter interrupt: %u ; counter timer: %u\r\n",
				counter_1s, (unsigned int) timer_counter_value);
		}
	}

	return 0;
}

/**
	* interrupt handling
	*/
/*static __attribute__ ((interrupt ("machine"))) void timer_irq_handler(void)*/
static __attribute__ ((interrupt))             void timer_irq_handler(void)
{
	is_interrupt_raised = true;
	counter_1s++;
}

void pe_start(void)
{
}
