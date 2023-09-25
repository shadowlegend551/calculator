#ifndef EXCEPTIONSLIB_H
#define EXCEPTIONSLIB_H

#include "exceptions.h"

// Should be thrown if malloc fails.
extern exception memory_allocation_error;

// Should be thrown if realloc fails.
extern exception memory_reallocation_error;

// Should be thrown if scanf fails.
extern exception input_read_error;

// Should be thrown if if a signed integer overflows when it shouldn't.
extern exception integer_overflow_error;

#endif
