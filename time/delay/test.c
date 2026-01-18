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

int main(void)
{
	int counter = 0;


	printf("Entering test\n");

	while (true)
	{
		pos_delay_busy_ms(1000);
		printf("[%lu] test delay %d\r\n", pos_tick_get_counter_ms(), counter++);
	}

	return 0;
}

void pe_start(void)
{
}
