/**
	* Copyright (C) 2026 ICDEC
	*
	* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
	* EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
	* OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
	* NONINFRINGEMENT.
	*/

#include <stddef.h>

#include <stdio.h>

#include <pulp.h>

/**
	* gpio index to use for pwm output
	*
	* set pad mux to 0b_10 so that pad is connected to timer3_i[0]
	* see pulpissimo/rtl/pulpissimo/pad_control.sv around line 263
	*/
#ifndef GPIO_PWM
#define GPIO_PWM        17
#endif

#ifndef GPIO_PWM_MUX
#define GPIO_PWM_MUX    2
#endif

#ifndef GPIO_PWM_PADMUX_ID
#define GPIO_PWM_PADMUX_ID   1    /* for pin 17, use register 1 */
#endif

#ifndef GPIO_PWM_PADMUX_BIT
#define GPIO_PWM_PADMUX_BIT   2u    /* for pin 17, use offset 2 */
#endif

int main(void)
{
	int retval;

	/* initialize to invalid value */
	size_t   timer   = 0xffffffff;
	size_t   channel = 0xffffffff;

	uint32_t event_cfg = 0;

	uint32_t padmux;

	/* get timer and channel for current gpio */
	retval = adv_timer_get_timer_and_channel_from_io(GPIO_PWM, GPIO_PWM_MUX,
		&timer, &channel);
	if (retval != 0)
	{
		/* if we cannot get timer and channel then just return */
		return retval;
	}

	/* make sure we get correct result */
	if ((timer < 0) || (timer >= 4) || (channel < 0) || (channel >= 4))
	{
		return (-1);
	}


	/* set correct mux for pwm */
	padmux = hal_apb_soc_padfun_get(GPIO_PWM_PADMUX_ID);
	hal_apb_soc_padfun_set(GPIO_PWM_PADMUX_ID, (padmux & (~(0x3u << GPIO_PWM_PADMUX_BIT))) | (GPIO_PWM_MUX << GPIO_PWM_PADMUX_BIT));
	/*rt_pad_set_function(GPIO_PWM, GPIO_PWM_MUX);*/



	/* we can now use timer api based on timer and channel */


	/* disable timer before we configure */
	adv_timer_disable(timer);


	/* enable clock */
	adv_timer_enable_clock(timer);


	/* set prescaler and threshold */
	adv_timer_config_frequency(timer, 100, 160);

	/* we don't have event setting for now, use api from archi */
	event_cfg = adv_timer_event_cfg_get(timer);
	event_cfg = ADV_TIMER_EVENT_CFG_ENA_SET(event_cfg, 0x00);
	adv_timer_event_cfg_set(timer, event_cfg);

	/* start timer */
	adv_timer_start(timer);


	printf("Entering test\n");

	/* let hardware run the pwm without processor involvement */
	while (true)
	{
		/* put cpu to sleep */
		__asm__ __volatile__ (
			"wfi\n"
			:
			:
			:
		);
	}

	return 0;
}

void pe_start(void)
{
}
