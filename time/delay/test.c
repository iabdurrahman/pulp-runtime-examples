/**
	* Copyright (C) 2025 ICDEC
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
