#pragma once

#include <stdbool.h>
#include <stdlib.h>

#include "../../../interfaces/comparator/comparator.h"
#include "../../../interfaces/destructor/destructor.h"
#include "../../../interfaces/iterator/iterator.h"
#include "../../transformations/map.h"

#define FORWARD_LIST_HEADER(FPX, TYPE)                                                   \
	typedef size_t forward_list_size_t;                                                  \
                                                                                         \
	typedef struct TYPE##_forward_list_t TYPE##_forward_list_t;                          \
                                                                                         \
	SUPPLIER(TYPE)                                                                       \
                                                                                         \
	DESTRUCTOR_OF(TYPE)                                                                  \
                                                                                         \
	COMPARATOR_OF(TYPE)                                                                  \
                                                                                         \
	TYPE##_forward_list_t* FPX##_new();                                                  \
                                                                                         \
	TYPE* FPX##_data(TYPE##_forward_list_t* const instance);                             \
                                                                                         \
	void FPX##_place(TYPE##_forward_list_t* const instance, TYPE* const data);           \
                                                                                         \
	TYPE##_forward_list_t* FPX##_at(TYPE##_forward_list_t* const instance,               \
									const forward_list_size_t index);                    \
                                                                                         \
	TYPE* FPX##_get(TYPE##_forward_list_t* const instance, TYPE* const item,             \
					TYPE##_comparator cmp);                                              \
                                                                                         \
	TYPE##_forward_list_t* FPX##_next(TYPE##_forward_list_t* const instance);            \
                                                                                         \
	void FPX##_set_next(TYPE##_forward_list_t* const instance,                           \
						TYPE##_forward_list_t* const to);                                \
                                                                                         \
	void FPX##_pop_front(TYPE##_forward_list_t* const instance,                          \
						 TYPE##_destructor destructor);                                  \
                                                                                         \
	void FPX##_push_front(TYPE##_forward_list_t* const instance,                         \
						  TYPE##_forward_list_t* const other);                           \
                                                                                         \
	void FPX##_add(TYPE##_forward_list_t* const instance, TYPE* const item);             \
                                                                                         \
	void FPX##_insert_before(TYPE##_forward_list_t* const instance,                      \
							 const forward_list_size_t index, TYPE* const item);         \
                                                                                         \
	void FPX##_insert_after(TYPE##_forward_list_t* const instance,                       \
							const forward_list_size_t index, TYPE* const item);          \
                                                                                         \
	void FPX##_assign(TYPE##_forward_list_t* const instance,                             \
					  const forward_list_size_t n, TYPE##_supplier supplier);            \
                                                                                         \
	void FPX##_free(TYPE##_forward_list_t* const instance,                               \
					TYPE##_destructor destructor);                                       \
                                                                                         \
	ITERATOR(FPX, TYPE##_forward_list, TYPE)                                             \
                                                                                         \
	MAP_HEADER(FPX, TYPE##_forward_list, TYPE)

#define FORWARD_LIST_STRUCT_DEFS(FPX, TYPE)                                              \
	struct TYPE##_forward_list_t {                                                       \
		TYPE* data;                                                                      \
		TYPE##_forward_list_t* next;                                                     \
	};                                                                                   \
                                                                                         \
	struct TYPE##_forward_list_iter_t {                                                  \
		TYPE##_forward_list_t* cursor;                                                   \
		bool end;                                                                        \
	};

#define FORWARD_LIST_SOURCE(FPX, TYPE)                                                   \
	FORWARD_LIST_STRUCT_DEFS(FPX, TYPE)                                                  \
                                                                                         \
	TYPE##_forward_list_t* FPX##_new() {                                                 \
		TYPE##_forward_list_t* instance = malloc(sizeof(TYPE##_forward_list_t));         \
                                                                                         \
		instance->data = NULL;                                                           \
                                                                                         \
		instance->next = NULL;                                                           \
                                                                                         \
		return instance;                                                                 \
	}                                                                                    \
                                                                                         \
	TYPE* FPX##_data(TYPE##_forward_list_t* const instance) {                            \
		return (instance ? instance->data : NULL);                                       \
	}                                                                                    \
                                                                                         \
	void FPX##_place(TYPE##_forward_list_t* const instance, TYPE* const data) {          \
		if (instance && data) {                                                          \
			instance->data = data;                                                       \
		}                                                                                \
	}                                                                                    \
                                                                                         \
	TYPE##_forward_list_t* FPX##_at(TYPE##_forward_list_t* const instance,               \
									const forward_list_size_t index) {                   \
                                                                                         \
		TYPE##_forward_list_t* tmp = NULL;                                               \
                                                                                         \
		if (instance) {                                                                  \
			tmp = instance;                                                              \
                                                                                         \
			const forward_list_size_t actual_index = index - 1;                          \
                                                                                         \
			if (actual_index > 0UL) {                                                    \
                                                                                         \
				forward_list_size_t current_index = 0UL;                                 \
                                                                                         \
				while (tmp->next) {                                                      \
					if (current_index == actual_index) {                                 \
						return tmp;                                                      \
					}                                                                    \
                                                                                         \
					tmp = tmp->next;                                                     \
                                                                                         \
					++current_index;                                                     \
				}                                                                        \
			}                                                                            \
		}                                                                                \
                                                                                         \
		return tmp;                                                                      \
	}                                                                                    \
                                                                                         \
	TYPE* FPX##_get(TYPE##_forward_list_t* const instance, TYPE* const item,             \
					TYPE##_comparator cmp) {                                             \
                                                                                         \
		if (instance && cmp && item) {                                                   \
			TYPE##_forward_list_t* tmp = instance;                                       \
                                                                                         \
			while (tmp->next) {                                                          \
				if (cmp(FPX##_data(tmp), item) == EQUAL) {                               \
					return item;                                                         \
				}                                                                        \
                                                                                         \
				tmp = tmp->next;                                                         \
			}                                                                            \
		}                                                                                \
                                                                                         \
		return NULL;                                                                     \
	}                                                                                    \
                                                                                         \
	TYPE##_forward_list_t* FPX##_next(TYPE##_forward_list_t* const instance) {           \
		return (instance ? instance->next : NULL);                                       \
	}                                                                                    \
                                                                                         \
	void FPX##_set_next(TYPE##_forward_list_t* const instance,                           \
						TYPE##_forward_list_t* const to) {                               \
                                                                                         \
		if (instance && to) {                                                            \
			instance->next = to;                                                         \
		}                                                                                \
	}                                                                                    \
                                                                                         \
	void FPX##_free_node(TYPE##_forward_list_t* const instance,                          \
						 foo_destructor destructor) {                                    \
		if (instance) {                                                                  \
			if (destructor) {                                                            \
				destructor(instance->data);                                              \
			}                                                                            \
                                                                                         \
			instance->data = NULL;                                                       \
                                                                                         \
			instance->next = NULL;                                                       \
                                                                                         \
			free(instance);                                                              \
		}                                                                                \
	}                                                                                    \
                                                                                         \
	void FPX##_pop_front(TYPE##_forward_list_t* const instance,                          \
						 TYPE##_destructor destructor) {                                 \
		if (instance) {                                                                  \
			TYPE##_forward_list_t* const tmp = instance->next;                           \
                                                                                         \
			instance->next = tmp->next;                                                  \
                                                                                         \
			FPX##_free_node(tmp, destructor);                                            \
		}                                                                                \
	}                                                                                    \
                                                                                         \
	void FPX##_push_front(TYPE##_forward_list_t* const instance,                         \
						  TYPE##_forward_list_t* const other) {                          \
		if (instance && other) {                                                         \
                                                                                         \
			TYPE##_forward_list_t* const tmp = instance->next;                           \
                                                                                         \
			other->next = tmp;                                                           \
                                                                                         \
			instance->next = other;                                                      \
		}                                                                                \
	}                                                                                    \
                                                                                         \
	void FPX##_add(TYPE##_forward_list_t* const instance, TYPE* const item) {            \
		if (instance && item) {                                                          \
			TYPE##_forward_list_t* const new_instance = FPX##_new();                     \
                                                                                         \
			FPX##_place(new_instance, item);                                             \
                                                                                         \
			FPX##_push_front(instance, new_instance);                                    \
		}                                                                                \
	}                                                                                    \
                                                                                         \
	void FPX##_insert_before(TYPE##_forward_list_t* const instance,                      \
							 const forward_list_size_t index, TYPE* const item) {        \
                                                                                         \
		TYPE##_forward_list_t* before = FPX##_at(instance, (index - 1UL));               \
                                                                                         \
		if (before && item) {                                                            \
			TYPE##_forward_list_t* const next = FPX##_new();                             \
                                                                                         \
			FPX##_place(next, item);                                                     \
                                                                                         \
			FPX##_push_front(before, next);                                              \
		}                                                                                \
	}                                                                                    \
                                                                                         \
	void FPX##_insert_after(TYPE##_forward_list_t* const instance,                       \
							const forward_list_size_t index, TYPE* const item) {         \
                                                                                         \
		TYPE##_forward_list_t* after = FPX##_at(instance, (index + 1UL));                \
                                                                                         \
		if (after && item) {                                                             \
			TYPE##_forward_list_t* const next = FPX##_new();                             \
                                                                                         \
			FPX##_place(next, item);                                                     \
                                                                                         \
			FPX##_push_front(after, next);                                               \
		}                                                                                \
	}                                                                                    \
                                                                                         \
	void FPX##_assign(TYPE##_forward_list_t* const instance,                             \
					  const forward_list_size_t n, TYPE##_supplier supplier) {           \
                                                                                         \
		if (instance && (n > 0UL)) {                                                     \
			for (forward_list_size_t i = 0UL; i < n; ++i) {                              \
				TYPE##_forward_list_t* const next = FPX##_new();                         \
                                                                                         \
				TYPE* const value = supplier();                                          \
                                                                                         \
				if (value) {                                                             \
					FPX##_place(next, value);                                            \
				}                                                                        \
                                                                                         \
				FPX##_push_front(instance, next);                                        \
			}                                                                            \
		}                                                                                \
	}                                                                                    \
                                                                                         \
	void FPX##_free(TYPE##_forward_list_t* const instance,                               \
					TYPE##_destructor destructor) {                                      \
		if (instance) {                                                                  \
                                                                                         \
			foo_forward_list_t* tmp = instance;                                          \
                                                                                         \
			while (tmp->next) {                                                          \
				foo_forward_list_pop_front(tmp, destructor);                             \
			}                                                                            \
                                                                                         \
			foo_forward_list_free_node(instance, destructor);                            \
		}                                                                                \
	}                                                                                    \
                                                                                         \
	FPX##_iter_t* FPX##_iter_new(TYPE##_forward_list_t* const instance) {                \
		FPX##_iter_t* itr = NULL;                                                        \
                                                                                         \
		if (instance) {                                                                  \
			itr = malloc(sizeof(FPX##_iter_t));                                          \
                                                                                         \
			itr->cursor = instance;                                                      \
                                                                                         \
			itr->end = false;                                                            \
		}                                                                                \
                                                                                         \
		return itr;                                                                      \
	}                                                                                    \
                                                                                         \
	bool FPX##_iter_has_next(const FPX##_iter_t* const itr) {                            \
		return (itr && !itr->end);                                                       \
	}                                                                                    \
                                                                                         \
	foo* FPX##_iter_next(FPX##_iter_t* const itr) {                                      \
		if (FPX##_iter_has_next(itr)) {                                                  \
                                                                                         \
			TYPE##_forward_list_t* cursor = itr->cursor;                                 \
			foo* data = NULL;                                                            \
                                                                                         \
			if (cursor) {                                                                \
				data = FPX##_data(cursor);                                               \
                                                                                         \
				TYPE##_forward_list_t* next = cursor->next;                              \
                                                                                         \
				if (!data) {                                                             \
					next = next->next;                                                   \
                                                                                         \
					data = FPX##_data(next);                                             \
				}                                                                        \
                                                                                         \
				if (!next) {                                                             \
					itr->end = true;                                                     \
                                                                                         \
					return data;                                                         \
				}                                                                        \
                                                                                         \
				itr->cursor = next;                                                      \
                                                                                         \
			} else {                                                                     \
				itr->end = true;                                                         \
			}                                                                            \
                                                                                         \
			return data;                                                                 \
		}                                                                                \
                                                                                         \
		return NULL;                                                                     \
	}                                                                                    \
                                                                                         \
	void FPX##_iter_free(FPX##_iter_t* itr) {                                            \
		if (itr) {                                                                       \
			itr->cursor = NULL;                                                          \
                                                                                         \
			free(itr);                                                                   \
                                                                                         \
			itr = NULL;                                                                  \
		}                                                                                \
	}                                                                                    \
                                                                                         \
	MAP_SOURCE(FPX, TYPE##_forward_list, TYPE)
