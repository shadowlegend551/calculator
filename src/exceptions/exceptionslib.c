#include "exceptions.h"
#include "exceptionslib.h"


exception memory_allocation_error =
{
    .criticality = FATAL_ERROR,
    .message = "Memory allocation failed"
};

exception memory_reallocation_error =
{
    .criticality = FATAL_ERROR,
    .message = "Memory reallocation failed"
};

exception input_read_error =
{
    .criticality = WARNING,
    .message = "Reading input failed"
};

exception integer_overflow_error =
{
    .criticality = FATAL_ERROR,
    .message = "Integer overflow"
};
