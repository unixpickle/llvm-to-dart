#ifndef __LLVMTODART_SAFE_ASSERT_HPP__
#define __LLVMTODART_SAFE_ASSERT_HPP__

#include <cassert>
#define SafeAssert(x, var) bool var = (x); assert(var); (void)var;

#endif
