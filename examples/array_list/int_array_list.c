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

int_array_list_iter_t* int_list_iter_new(int_array_list_t* const instance) {
	if (!int_list_is_empty(instance)) {
		int_array_list_iter_t* itr = malloc(sizeof(int_array_list_iter_t));

		itr->current_index = g_FIRST_ITEM;

		itr->target = instance;

		itr->cursor = instance->data[g_FIRST_ITEM];

		return itr;
	}

	return NULL;
}

bool int_list_iter_has_next(const int_array_list_iter_t* const itr) {
	const bool has_valid_pointers = itr && itr->target;

	return (has_valid_pointers && (itr->current_index < (itr->target)->capacity));
}

int* int_list_iter_next(int_array_list_iter_t* const itr) {
	if (int_list_iter_has_next(itr)) {
		int* current = NULL;

		if (itr->current_index != g_FIRST_ITEM) {
			itr->cursor = itr->target->data[itr->current_index];

			++itr->current_index;

			current = itr->cursor;

		} else {
			int* first_item = itr->cursor;

			current = first_item;

			++itr->current_index;
		}

		return current;
	}

	return NULL;
}

void int_list_iter_free(int_array_list_iter_t* itr) {
	if (itr) {
		itr->cursor = NULL;
		itr->target = NULL;

		free(itr);

		itr = NULL;
	}
}
