#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "foo_forward_list.h"

FORWARD_LIST_SOURCE(foo_forward_list, foo)

comparison_result_t foo_comparison(const foo* const left, const foo* const right) {
	if (left && right) {
		const char* l_str = left->name;
		const char* r_str = right->name;

		if (l_str && r_str) {
			const size_t left_size = strlen(l_str);
			const size_t right_size = strlen(r_str);

			if (left_size < right_size) {
				return strncmp(l_str, r_str, left_size);
			} else {
				return strncmp(r_str, l_str, right_size);
			}
		}
	}

	return EMPTY_VALUES;
}

void foo_deleter(foo* instance) {
	if (instance) {
		if (instance->is_owning) {
			free(instance->name);
		}

		free(instance);

		instance = NULL;
	}
}

void printFoo(const foo* const instance) {
	if (instance) {
		const char* const name = instance->name;

		printf("%d, %s\n", instance->is_owning, (name ? name : "???"));

	} else {
		puts("...");
	}
}

foo* make_foo() {
	static int count = -1;
	foo* instance = malloc(sizeof(foo));

	instance->is_owning = false;
	instance->id = ++count;
	instance->name = NULL;

	return instance;
}

foo* withSuffix(foo* const instance) {
	if (instance) {
		foo* out = make_foo();

		if (instance->name) {
			const char* suffix = " <-\0";

			const size_t instance_name_length = strlen(instance->name);

			const size_t suffix_length = 5UL;

			const size_t new_name_length = instance_name_length + suffix_length;

			out->name = malloc(new_name_length);

			for (size_t i = 0UL; i < instance_name_length; ++i) {
				out->name[i] = instance->name[i];
			}

			for (size_t i = instance_name_length, j = 0UL; i < new_name_length;
				 ++i, ++j) {
				out->name[i] = suffix[j];
			}

			out->is_owning = true;
		}

		return out;
	}

	return NULL;
}
