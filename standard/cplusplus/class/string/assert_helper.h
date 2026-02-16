#ifndef __ASSERT_HELPER_H__
#define __ASSERT_HELPER_H__

#include <assert.h>

#if ((defined(NDEBUG)) || (defined(__riscv__)))
#define      _ASSERT(a)
#else
#define      _ASSERT(a)     assert(a)
#endif

#endif /* ! defined(__ASSERT_HELPER_H__) */
