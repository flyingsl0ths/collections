#include <stdio.h>

#include "../src/interfaces/functional/identity.h"
#include "int_array_list.h"

IDENTITY_PTR(int)

int_array_list_t* make_empty_int_list() {
	return int_list_new(10);
}

int main() {
	// instantiates an 'int' array-list
	int_array_list_t* ns = int_list_new(10);

	int* a = malloc(sizeof(int));
	int* s = malloc(sizeof(int));
	int* d = malloc(sizeof(int));
	int* f = malloc(sizeof(int));
	int* g = malloc(sizeof(int));
	int* h = malloc(sizeof(int));
	int* j = malloc(sizeof(int));
	int* k = malloc(sizeof(int));
	int* i = malloc(sizeof(int));
	int* l = malloc(sizeof(int));
	int* m = malloc(sizeof(int));

	*a = 10;
	*s = 20;
	*d = 30;
	*f = 40;
	*g = 50;
	*h = 60;
	*j = 70;
	*k = 80;
	*i = 90;
	*l = 100;
	*m = 110;

	// instantiates add function for array-list's type
	int_list_add(ns, a);
	int_list_add(ns, s);
	int_list_add(ns, d);
	int_list_add(ns, f);
	int_list_add(ns, g);
	int_list_add(ns, h);
	int_list_add(ns, j);
	int_list_add(ns, k);
	int_list_add(ns, i);
	int_list_add(ns, l);
	int_list_add(ns, m);

	puts("Traversing int_list:");

	// instantiates a new iterator instance for the array-list's type
	int_array_list_iter_t* ns_itr = int_list_iter_new(ns);

	// instantiates a new map instance for the array-list's type
	// ends up copying pointers from ns to ns'
	int_array_list_t* ns_ = int_array_list_map(make_empty_int_list, ns_itr, identity_p);

	// frees the memory for the iterator only
	int_list_iter_free(ns_itr);

	// creates a new iterator for ns_
	int_array_list_iter_t* ns_itr_ = int_list_iter_new(ns_);

	bool has_more_items = int_list_iter_has_next(ns_itr_);

	// iterates 'array-list capacity' times
	while (has_more_items) {
		int* current = int_list_iter_next(ns_itr_);

		printf("Item: %d\n", *current);

		has_more_items = int_list_iter_has_next(ns_itr_);
	}

	puts("");

	// only call free on ns not ns_ otherwise "double free" error
	int_list_free(ns);
}
