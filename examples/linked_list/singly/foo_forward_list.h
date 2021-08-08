#pragma once

#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

#include "../../../src/collections/linked_list/singly/forward_list.h"

typedef struct foo {
	bool is_owning;
	int id;
	char* name;
} foo;

FORWARD_LIST_HEADER(foo_forward_list, foo)

comparison_result_t foo_comparison(const foo* const left, const foo* const right);

void foo_deleter(foo* instance);

void printFoo(const foo* const instance);

foo* make_foo();

foo* withSuffix(foo* const instance);
