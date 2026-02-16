/**
	* Copyright (C) 2026 Indonesia Chip Design Collaborative Center (ICDEC)
	*
	* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
	* EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
	* OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
	* NONINFRINGEMENT.
	*/

#include <stdio.h>

#include "cxxstring.hpp"

int main(void)
{
	cxxstring init1 = new cxxstring;
	cxxstring init2 = new cxxstring("test dynamic init2");
	cxxstring init3 = new cxxstring(init2);

	/* print sentence */
	printf("init1: %s\r\n", init1.c_str());
	printf("init2: %s\r\n", init2.c_str());
	printf("init3: %s\r\n", init3.c_str());

	delete init1;
	delete init2;
	delete init3;

	return 0;
}

/* implement pe_start as c function */
extern "C" void pe_start(void)
{
}
