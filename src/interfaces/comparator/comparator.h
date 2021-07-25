#pragma once

#include <stdint.h>

typedef int32_t comparison_result_t;

static const comparison_result_t EMPTY_VALUES = -2;

static const comparison_result_t EQUAL = 0;

static const comparison_result_t LEFT_NOT_EQUAL = -1;

static const comparison_result_t RIGHT_NOT_EQUAL = 1;

#define COMPARATOR_OF(TYPE)                                                              \
	typedef comparison_result_t (*TYPE##_comparator)(const TYPE* const,                  \
													 const TYPE* const);
