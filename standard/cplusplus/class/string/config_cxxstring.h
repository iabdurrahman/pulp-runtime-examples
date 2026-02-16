#ifndef __CONFIG_CXXSTRING_H__
#define __CONFIG_CXXSTRING_H__

/**
	* when set to 1, overloading operator will call abort when
	* dynamic memory allocation function (malloc, realloc, etc.) is fail
	*/
#ifndef CXXSTRING_CONF_OPERATOR_OVERLOADING_ABORT_ON_ALLOC_FAIL
#define CXXSTRING_CONF_OPERATOR_OVERLOADING_ABORT_ON_ALLOC_FAIL      1
#endif


/**
	* remove last byte from operand buffer if we detect
	* buffer has same length as string (+ '\0' termination)
	* can save memory, but add more operation
	*/
#ifndef CXXSTRING_CONF_OPERATOR_PLUS_REMOVE_ZERO_TERMINATION
#define CXXSTRING_CONF_OPERATOR_PLUS_REMOVE_ZERO_TERMINATION      1
#endif


#endif /* ! defined(__CONFIG_CXXSTRING_H__) */
