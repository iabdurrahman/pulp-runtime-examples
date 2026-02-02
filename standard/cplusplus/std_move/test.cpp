/**
	* Copyright (C) 2026 Indonesia Chip Design Collaborative Center (ICDEC)
	*
	* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
	* EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
	* OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
	* NONINFRINGEMENT.
	*/

#include <vector>
#include <utility> /* Required for std::move */

#include <stdio.h>

int main(void)
{
	std::vector<int> source = {1, 2, 3, 4, 5};

	/* Use std::move to transfer resources to 'destination' */
	std::vector<int> destination = std::move(source);

	/* print vector value */
	for (const int& value : destination)
	{
		printf("%d\r\n", value);
	}

	return 0;
}

/* implement pe_start as c function */
extern "C" void pe_start(void)
{
}

