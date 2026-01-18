/**
	* Copyright (C) 2025 ICDEC
	*
	* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
	* EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
	* OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
	* NONINFRINGEMENT.
	*/

#include <stdio.h>
#include <pulp.h>

/**
	* undef    USE_BUSY_WAIT if you want to test interval print based on tick
	* define   USE_BUSY_WAIT if you want to test interval printing tick value based on loop
	*/
#undef USE_BUSY_WAIT

#ifndef USE_BUSY_WAIT
	#ifndef TIMEOUT_INTERVAL_MS
		#define TIMEOUT_INTERVAL_MS 1000L
	#endif

	#ifndef TOLERANCE
		#define TOLERANCE 15
	#endif
#endif

int main(void)
{
#ifndef USE_BUSY_WAIT
	long previous_time_ms = 0;
	long timeout          = previous_time_ms + TIMEOUT_INTERVAL_MS;
#endif


	printf("Entering test\n");


	while (true)
	{

		long     time_ms;
		long     time_us;


#ifdef USE_BUSY_WAIT     /* implement busy wait in (volatile) assembly so it not optimized */

		unsigned int counter;

		/* busy wait by looping */
		__asm__ __volatile__ (
				"li     %0, 4000000     \n"  /* set counter initial value */              \
				"__loop_wait:           \n"  /* start loop decrement counter */           \
				"addi   %0, %0, -1      \n"  /* decrement counter */                      \
				"bnez   %0, __loop_wait \n"  /* loop if counter is still not 0 */
				: "=r" (counter)
				:  "r" (counter)
				:
			);

		/* collect the time first */
		time_us = pos_tick_get_counter_us();
		time_ms = pos_tick_get_counter_ms();

/* end of busy wait implementation */
/* defined(USE_BUSY_WAIT) */

#else /* ! defined(USE_BUSY_WAIT) */    /* implement delayed wait by checking tick counter */

		long current_time_ms;

		/* collect tick counter first */
		time_us = pos_tick_get_counter_us();
		time_ms = pos_tick_get_counter_ms();

		/* get current tick */
		current_time_ms = time_ms;

		/* if timeout is bigger than current_time_ms, then loop again */
		if ((timeout - current_time_ms) > 0)
		{
			/* continue loop if current_time_ms not big enough */
			continue;
		}

		/* update previous_time and timeout */
		previous_time_ms = current_time_ms;
		timeout          = previous_time_ms + TIMEOUT_INTERVAL_MS;

		/* make sure counter do correct calculation */
		if (((time_ms * 1000) > (time_us + TOLERANCE)) || ((time_ms * 1000) < (time_us - TOLERANCE)))
		{
			/* trap error */
			while (1)
			{
			}
		}


		/*if ((timeout - tick_get_counter_ms()) > 2000)
		{
			break;
		}*/

/* end of tick checking wait implementation */
#endif    /* ! defined(USE_BUSY_WAIT) */

		/**
			* print tick
			* send to console
			*/
		printf("tick us: %ld\r\n", time_us);
		printf("tick ms: %ld\r\n", time_ms);
	}

	return 0;
}

void pe_start(void)
{
}
