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

#include "cxxstring.hpp"

int main(void)
{
	std::vector<cxxstring>     source       = {"this", "is", "a", "test", "sentence"};

	/* Use std::move to transfer resources to 'destination' */
	std::vector<cxxstring>     destination  = std::move(source);

	cxxstring                  sentence;

	/* add word into sentence */
	for (const cxxstring& value : destination)
	{
		sentence += " " + value;
	}

	/* print sentence */
	printf("%s\r\n", sentence.c_str());

	return 0;
}

/* implement pe_start as c function */
extern "C" void pe_start(void)
{
}
