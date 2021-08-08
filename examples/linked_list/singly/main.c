#include <stdio.h>
#include <stdlib.h>
#include "foo_forward_list.h"

foo_forward_list_t* empty_foo_list() {
	return foo_forward_list_new();
}

int main() {
	// Allocate a new singly linked list
	foo_forward_list_t* const head = foo_forward_list_new();

	// Fill head with data
	foo* foo1 = make_foo();

	foo1->name = "Foo";

	foo_forward_list_place(head, foo1);
	//

	// Allocates 5 entries after head of list
	foo_forward_list_assign(head, 5, make_foo);

	foo_forward_list_t* foo2 = foo_forward_list_at(head, 2);
	foo_forward_list_t* foo3 = foo_forward_list_at(head, 3);
	foo_forward_list_t* foo4 = foo_forward_list_at(head, 4);
	foo_forward_list_t* foo5 = foo_forward_list_at(head, 5);
	foo_forward_list_t* foo6 = foo_forward_list_at(head, 6);
	//

	// Retrieve those 5 instances
	foo* f2 = foo_forward_list_data(foo2);
	foo* f3 = foo_forward_list_data(foo3);
	foo* f4 = foo_forward_list_data(foo4);
	foo* f5 = foo_forward_list_data(foo5);
	foo* f6 = foo_forward_list_data(foo6);

	f2->name = "Foo5";
	f3->name = "Foo4";
	f4->name = "Foo3";
	f5->name = "Foo2";
	f6->name = "Foo1";
	//

	// Finds node pointed to by 'f2'
	foo* found = foo_forward_list_get(head, f2, foo_comparison);

	printFoo(found);
	//

	// Deletes node after head
	foo_forward_list_pop_front(head, foo_deleter);
	//

	foo* foo7 = make_foo();
	foo7->name = "Foo6";

	foo_forward_list_add(head, foo7);

	foo* foo8 = make_foo();
	foo8->name = "Foo7";

	foo* foo9 = make_foo();
	foo9->name = "Foo9";

	// Inserts after node with postion 1 (uses zero-based indexing)
	foo_forward_list_insert_after(head, 1, foo8);
	//

	// add to front of head
	foo_forward_list_add(head, foo9);
	//

	foo* foo10 = make_foo();
	foo10->name = "Foo10";

	// Inserts before node with postion 8 (uses zero-based indexing)
	foo_forward_list_insert_before(head, 8, foo10);
	//

	// Allocates a new iterator for linked-list
	foo_forward_list_iter_t* const itr = foo_forward_list_iter_new(head);
	//

	// Uses iterator to map pointed to elements to new elements in a separate list
	foo_forward_list_t* mapped = foo_forward_list_map(empty_foo_list, itr, withSuffix);
	//

	// Frees the memory used by the iterator not the list
	foo_forward_list_iter_free(itr);

	// Iterates over elements in newly constructed list
	foo_forward_list_iter_t* const itr2 = foo_forward_list_iter_new(mapped);

	puts("\nIterating over mapped head");
	while (foo_forward_list_iter_has_next(itr2)) {
		const foo* current = foo_forward_list_iter_next(itr2);

		printFoo(current);
	}
	puts("");

	foo_forward_list_iter_free(itr2);
	//

	// Frees the memory used by both lists and it's elements
	// if second argument of free function is NULL only frees the memory used by nodes
	foo_forward_list_free(head, foo_deleter);

	foo_forward_list_free(mapped, foo_deleter);
	//

	return 0;
}
