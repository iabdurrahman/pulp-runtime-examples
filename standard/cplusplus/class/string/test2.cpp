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
	cxxstring init1;
	/*cxxstring init2();*/
	cxxstring init3("");
	cxxstring init4("test init 4");
	cxxstring init5(init4);
	cxxstring init6 = init5;
	cxxstring init7 = "test init 7";

	/* print sentence */
	printf("init1: %s\r\n", init1.c_str());
	/*printf("init2: %s\r\n", init2.c_str());*/
	printf("init3: %s\r\n", init3.c_str());
	printf("init4: %s\r\n", init4.c_str());
	printf("init5: %s\r\n", init5.c_str());
	printf("init6: %s\r\n", init6.c_str());
	printf("init7: %s\r\n", init7.c_str());

	return 0;
}

/* implement pe_start as c function */
extern "C" void pe_start(void)
{
}
