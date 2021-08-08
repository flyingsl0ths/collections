#pragma once

#include <stdbool.h>
#include <stdlib.h>

#include "../../interfaces/comparator/comparator.h"
#include "../../interfaces/destructor/destructor.h"
#include "../../interfaces/iterator/iterator.h"
#include "../transformations/map.h"

#define ARRAY_LIST_HEADER(FPX, TYPE)                                                     \
	typedef size_t array_list_size_t;                                                    \
                                                                                         \
	typedef struct TYPE##_array_list_t TYPE##_array_list_t;                              \
                                                                                         \
	DESTRUCTOR_OF(TYPE)                                                                  \
                                                                                         \
	COMPARATOR_OF(TYPE)                                                                  \
                                                                                         \
	TYPE##_array_list_t* FPX##_new(const array_list_size_t capacity);                    \
                                                                                         \
	TYPE* FPX##_at(TYPE##_array_list_t* const instance, const array_list_size_t index);  \
                                                                                         \
	TYPE* FPX##_get(TYPE##_array_list_t* const instance, TYPE* const item,               \
					TYPE##_comparator cmp);                                              \
                                                                                         \
	void* FPX##_add(TYPE##_array_list_t* const instance, TYPE* const item);              \
                                                                                         \
	TYPE* FPX##_remove(TYPE##_array_list_t* const instance,                              \
					   const array_list_size_t index);                                   \
                                                                                         \
	array_list_size_t FPX##_capacity(const TYPE##_array_list_t* const instance);         \
                                                                                         \
	array_list_size_t FPX##_size(const TYPE##_array_list_t* const instance);             \
                                                                                         \
	void FPX##_free(TYPE##_array_list_t* instance, TYPE##_destructor destructor);        \
                                                                                         \
	ITERATOR(FPX, TYPE##_array_list, TYPE)                                               \
                                                                                         \
	MAP_HEADER(FPX, TYPE##_array_list, TYPE)

#define MEMORY_UTILS_FOR_LIST_OF(FPX, TYPE)                                              \
	void FPX##_clear(TYPE** buffer, size_t capacity, TYPE##_destructor destructor) {     \
		if (buffer) {                                                                    \
			for (size_t i = 0UL; i < capacity; ++i) {                                    \
				TYPE* current = buffer[i];                                               \
                                                                                         \
				if (current) {                                                           \
					destructor(current);                                                 \
				}                                                                        \
                                                                                         \
				current = NULL;                                                          \
			}                                                                            \
                                                                                         \
			free(buffer);                                                                \
                                                                                         \
			buffer = NULL;                                                               \
		}                                                                                \
	}                                                                                    \
                                                                                         \
	TYPE** FPX##_resize(TYPE** old_buffer, const size_t old_size,                        \
						const size_t new_size) {                                         \
		TYPE** resized = NULL;                                                           \
                                                                                         \
		if (old_buffer) {                                                                \
			if (old_size < new_size) {                                                   \
				TYPE** new_buffer = malloc(sizeof(TYPE*) * new_size);                    \
                                                                                         \
				for (size_t i = 0UL; i < old_size; ++i) {                                \
					new_buffer[i] = old_buffer[i];                                       \
                                                                                         \
					old_buffer[i] = NULL;                                                \
				}                                                                        \
                                                                                         \
				free(old_buffer);                                                        \
                                                                                         \
				resized = new_buffer;                                                    \
			}                                                                            \
		}                                                                                \
                                                                                         \
		return resized;                                                                  \
	}

#define ARRAY_LIST_STRUCT_DEFS(TYPE)                                                     \
	struct TYPE##_array_list_t {                                                         \
		TYPE** data;                                                                     \
		array_list_size_t capacity;                                                      \
		array_list_size_t size;                                                          \
	};                                                                                   \
                                                                                         \
	struct TYPE##_array_list_iter_t {                                                    \
		TYPE##_array_list_t* target;                                                     \
		TYPE* cursor;                                                                    \
		array_list_size_t current_index;                                                 \
	};

#define ARRAY_LIST_SOURCE(FPX, TYPE)                                                     \
	static const array_list_size_t g_FIRST_ITEM = 0UL;                                   \
                                                                                         \
	static const array_list_size_t g_EMPTY_LIST = 0UL;                                   \
                                                                                         \
	static const array_list_size_t g_DEFAULT_SIZE = 10UL;                                \
                                                                                         \
	static const array_list_size_t g_BUFFER_SCALAR = 2UL;                                \
                                                                                         \
	ARRAY_LIST_STRUCT_DEFS(TYPE)                                                         \
                                                                                         \
	MEMORY_UTILS_FOR_LIST_OF(FPX, TYPE)                                                  \
                                                                                         \
	TYPE##_array_list_t* FPX##_new(const array_list_size_t size) {                       \
		TYPE##_array_list_t* instance = malloc(sizeof(TYPE##_array_list_t));             \
                                                                                         \
		instance->capacity = 0UL;                                                        \
                                                                                         \
		if (size == 0UL) {                                                               \
			instance->data = malloc(sizeof(TYPE*) * g_DEFAULT_SIZE);                     \
                                                                                         \
			instance->size = g_DEFAULT_SIZE;                                             \
		} else {                                                                         \
			instance->data = malloc(sizeof(TYPE*) * size);                               \
                                                                                         \
			instance->size = size;                                                       \
		}                                                                                \
                                                                                         \
		return instance;                                                                 \
	}                                                                                    \
                                                                                         \
	TYPE* FPX##_at(TYPE##_array_list_t* const instance, const array_list_size_t index) { \
		return ((instance && (index < instance->capacity)) ? (instance->data[index])     \
														   : NULL);                      \
	}                                                                                    \
                                                                                         \
	TYPE* FPX##_get(TYPE##_array_list_t* const instance, TYPE* const item,               \
					TYPE##_comparator cmp) {                                             \
		const bool contains_data = (instance && instance->capacity > g_EMPTY_LIST);      \
                                                                                         \
		const bool can_search_for_item = (contains_data && item && cmp);                 \
                                                                                         \
		if (can_search_for_item) {                                                       \
			array_list_size_t capacity = instance->capacity;                             \
                                                                                         \
			for (array_list_size_t i = 0UL; i < capacity; ++i) {                         \
				const bool are_equal = (cmp(item, instance->data[i]) == EQUAL);          \
                                                                                         \
				if (are_equal) {                                                         \
					return item;                                                         \
				}                                                                        \
			}                                                                            \
                                                                                         \
			return (instance->data[g_FIRST_ITEM]);                                       \
		}                                                                                \
                                                                                         \
		return NULL;                                                                     \
	}                                                                                    \
                                                                                         \
	void* FPX##_add(TYPE##_array_list_t* const instance, TYPE* const item) {             \
		if (instance && item) {                                                          \
			array_list_size_t new_capacity = instance->capacity + 1UL;                   \
                                                                                         \
			if (new_capacity > instance->size) {                                         \
				array_list_size_t new_size = (instance->size * g_BUFFER_SCALAR);         \
                                                                                         \
				TYPE** resized =                                                         \
					FPX##_resize(instance->data, instance->capacity, new_size);          \
                                                                                         \
				if (resized) {                                                           \
					instance->data = resized;                                            \
                                                                                         \
					instance->size = new_size;                                           \
				}                                                                        \
			}                                                                            \
                                                                                         \
			instance->data[instance->capacity] = item;                                   \
                                                                                         \
			instance->capacity = new_capacity;                                           \
		}                                                                                \
                                                                                         \
		return NULL;                                                                     \
	}                                                                                    \
                                                                                         \
	TYPE* FPX##_remove(TYPE##_array_list_t* const instance,                              \
					   const array_list_size_t index) {                                  \
                                                                                         \
		TYPE* item = FPX##_at(instance, index);                                          \
                                                                                         \
		if (item) {                                                                      \
			instance->data[index] = NULL;                                                \
		}                                                                                \
                                                                                         \
		return item;                                                                     \
	}                                                                                    \
                                                                                         \
	array_list_size_t FPX##_capacity(const TYPE##_array_list_t* const instance) {        \
		return (instance ? instance->capacity : g_EMPTY_LIST);                           \
	}                                                                                    \
                                                                                         \
	array_list_size_t FPX##_size(const TYPE##_array_list_t* const instance) {            \
		return (instance ? instance->size : g_EMPTY_LIST);                               \
	}                                                                                    \
                                                                                         \
	void FPX##_free(TYPE##_array_list_t* instance, TYPE##_destructor destructor) {       \
		if (instance && (instance->capacity > g_EMPTY_LIST) && destructor) {             \
			FPX##_clear(instance->data, instance->capacity, destructor);                 \
                                                                                         \
			free(instance);                                                              \
                                                                                         \
			instance = NULL;                                                             \
                                                                                         \
		} else if (instance && (instance->capacity == g_EMPTY_LIST) && !destructor) {    \
			free(instance->data);                                                        \
                                                                                         \
			free(instance);                                                              \
                                                                                         \
			instance = NULL;                                                             \
		}                                                                                \
	}                                                                                    \
                                                                                         \
	TYPE##_array_list_iter_t* FPX##_iter_new(TYPE##_array_list_t* const instance) {      \
		if (instance && (instance->capacity > g_EMPTY_LIST)) {                           \
			TYPE##_array_list_iter_t* itr = malloc(sizeof(TYPE##_array_list_iter_t));    \
                                                                                         \
			itr->current_index = g_FIRST_ITEM;                                           \
                                                                                         \
			itr->target = instance;                                                      \
                                                                                         \
			itr->cursor = instance->data[g_FIRST_ITEM];                                  \
                                                                                         \
			return itr;                                                                  \
		}                                                                                \
                                                                                         \
		return NULL;                                                                     \
	}                                                                                    \
                                                                                         \
	bool FPX##_iter_has_next(const TYPE##_array_list_iter_t* const itr) {                \
		const bool has_valid_pointers = itr && itr->target;                              \
                                                                                         \
		return (has_valid_pointers && (itr->current_index < (itr->target)->capacity));   \
	}                                                                                    \
                                                                                         \
	TYPE* FPX##_iter_next(TYPE##_array_list_iter_t* const itr) {                         \
		if (FPX##_iter_has_next(itr)) {                                                  \
			TYPE* current = NULL;                                                        \
                                                                                         \
			if (itr->current_index != g_FIRST_ITEM) {                                    \
				itr->cursor = itr->target->data[itr->current_index];                     \
                                                                                         \
				++itr->current_index;                                                    \
                                                                                         \
				current = itr->cursor;                                                   \
                                                                                         \
			} else {                                                                     \
				TYPE* first_item = itr->cursor;                                          \
                                                                                         \
				current = first_item;                                                    \
                                                                                         \
				++itr->current_index;                                                    \
			}                                                                            \
                                                                                         \
			return current;                                                              \
		}                                                                                \
                                                                                         \
		return NULL;                                                                     \
	}                                                                                    \
                                                                                         \
	void FPX##_iter_free(TYPE##_array_list_iter_t* itr) {                                \
		if (itr) {                                                                       \
			itr->cursor = NULL;                                                          \
			itr->target = NULL;                                                          \
                                                                                         \
			free(itr);                                                                   \
                                                                                         \
			itr = NULL;                                                                  \
		}                                                                                \
	}                                                                                    \
                                                                                         \
	MAP_SOURCE(FPX, TYPE##_array_list, TYPE)
