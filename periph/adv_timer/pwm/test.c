/**
	* Copyright (C) 2026 ICDEC
	*
	* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
	* EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
	* OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
	* NONINFRINGEMENT.
	*/

#include <stdint.h>
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

/*#ifndef GPIO_PWM_PADMUX_ID*/
/*#define GPIO_PWM_PADMUX_ID   1*/    /* for pin 17, use register 1 */
/*#endif*/

/*#ifndef GPIO_PWM_PADMUX_BIT*/
/*#define GPIO_PWM_PADMUX_BIT   2u*/    /* for pin 17, use offset 2 */
/*#endif*/

int main(void)
{
	int retval;

	/* initialize to invalid value */
	size_t   timer   = 0xffffffff;
	size_t   channel = 0xffffffff;

	/* register value */
	uint32_t config;
	uint32_t event_cfg = 0;
	uint32_t th_channel = 0;

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
	/*rt_pad_set_function(GPIO_PWM, GPIO_PWM_MUX);*/
	/*padmux = hal_apb_soc_padfun_get(GPIO_PWM_PADMUX_ID);
	hal_apb_soc_padfun_set(GPIO_PWM_PADMUX_ID,
		(padmux & (~(0x3u << GPIO_PWM_PADMUX_BIT))) |
			(GPIO_PWM_MUX << GPIO_PWM_PADMUX_BIT));*/

	hal_apb_soc_pad_set_function(GPIO_PWM, GPIO_PWM_MUX);


	/* we can now use timer api based on timer and channel */


	/* stop and reset timer before we configure */
	adv_timer_stop_and_reset(timer);


	/* we don't have event setting for now, use api from archi */
	event_cfg = adv_timer_event_cfg_get(timer);
	event_cfg = ADV_TIMER_EVENT_CFG_ENA_SET(event_cfg, 0x00);
	adv_timer_event_cfg_set(timer, event_cfg);

	/* enable clock */
	adv_timer_enable_clock(timer);


	/* set prescaler and threshold */
	adv_timer_config_frequency(timer, 4, 1000);


	/* set channel threshold and mode */
	th_channel = ADV_TIMER_TN_TH_CHANNELM_TH_SET(th_channel, 950); /* 950/1000 */
	/**
		* SET        0x0
		* TOGRST     0x1
		* SETRST     0x2
		* TOG        0x3
		* RST        0x4
		* TOGSET     0x5
		* RSTSET     0x6
		*/
	th_channel = ADV_TIMER_TN_TH_CHANNELM_MODE_SET(th_channel, 0x6);
	adv_timer_tn_th_channelm_set(ARCHI_ADV_TIMER_ADDR, timer,
		channel, th_channel);

	/* set counter to form sawtooth (counting in only one direction) */
	/*config = adv_timer_tn_config_get(ARCHI_ADV_TIMER_ADDR, timer);
	config = ADV_TIMER_TN_CONFIG_UPDOWNSEL_SET(config, 1);
	adv_timer_tn_config_set(ARCHI_ADV_TIMER_ADDR, timer, config);*/


	/**
		* NOTE: this should unnecessary since timer is not yet starter
		*       but just to make sure
		*/
	adv_timer_update(timer);


	/* start timer */
	adv_timer_start(timer);


	printf("Entering test\n");

	/* let hardware run the pwm without processor involvement */
	while (true)
	{
		/* let cpu go sleep */
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
