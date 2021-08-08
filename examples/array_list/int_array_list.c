#include "int_array_list.h"

ARRAY_LIST_SOURCE(int_list, int)

comparison_result_t int_comparison(const int* const left, const int* const right) {
	if (left && right) {
		const int left_value = (*left);
		const int right_value = (*right);

		if (left_value < right_value) {
			return LEFT_NOT_EQUAL;
		} else if (right_value > left_value) {
			return RIGHT_NOT_EQUAL;
		} else {
			return EQUAL;
		}
	}

	return EMPTY_VALUES;
}

void int_deleter(int* const n) {
	if (n) {
		free(n);
	}
}