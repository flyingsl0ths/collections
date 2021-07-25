#pragma once

#include <stdlib.h>

#include "../../interfaces/comparator/comparator.h"
#include "../../interfaces/iterator/iterator.h"
#include "../transformations/map.h"

#define ARRAY_LIST_HEADER(FPX, TYPE)                                                     \
	typedef size_t array_list_size_t;                                                    \
                                                                                         \
	typedef struct TYPE##_array_list_t TYPE##_array_list_t;                              \
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
	array_list_size_t FPX##_capacity(const TYPE##_array_list_t* const instance);         \
                                                                                         \
	array_list_size_t FPX##_size(const TYPE##_array_list_t* const instance);             \
                                                                                         \
	bool FPX##_is_empty(const TYPE##_array_list_t* const instance);                      \
                                                                                         \
	void FPX##_free(TYPE##_array_list_t* instance);                                      \
                                                                                         \
	ITERATOR(FPX, TYPE##_array_list, TYPE)                                               \
                                                                                         \
	MAP_HEADER(FPX, TYPE##_array_list, TYPE)

#define MEMORY_UTILS_FOR_LIST_OF(TYPE)                                                   \
	void freeArray(TYPE** buffer, size_t capacity) {                                     \
		if (buffer) {                                                                    \
			for (size_t i = 0UL; i < capacity; ++i) {                                    \
				TYPE* current = buffer[i];                                               \
                                                                                         \
				if (current) {                                                           \
					free(current);                                                       \
                                                                                         \
					current = NULL;                                                      \
				}                                                                        \
			}                                                                            \
                                                                                         \
			free(buffer);                                                                \
                                                                                         \
			buffer = NULL;                                                               \
		}                                                                                \
	}                                                                                    \
                                                                                         \
	TYPE** resizeArray(TYPE** old_buffer, const size_t old_size,                         \
					   const size_t new_size) {                                          \
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
				return new_buffer;                                                       \
			}                                                                            \
		}                                                                                \
		return NULL;                                                                     \
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
	const array_list_size_t g_DEFAULT_SIZE = 10UL;                                       \
                                                                                         \
	const array_list_size_t g_FIRST_ITEM = 0UL;                                          \
                                                                                         \
	const array_list_size_t g_BUFFER_SCALAR = 2UL;                                       \
                                                                                         \
	const array_list_size_t g_EMPTY_LIST = 0UL;                                          \
                                                                                         \
	ARRAY_LIST_STRUCT_DEFS(TYPE)                                                         \
                                                                                         \
	MEMORY_UTILS_FOR_LIST_OF(TYPE)                                                       \
                                                                                         \
	TYPE##_array_list_t* FPX##_new(const array_list_size_t size) {                       \
		TYPE##_array_list_t* instance = malloc(sizeof(TYPE##_array_list_t));             \
                                                                                         \
		instance->capacity = 0UL;                                                        \
                                                                                         \
		if (size == 0UL) {                                                               \
			instance->data = malloc(sizeof(TYPE*) * g_DEFAULT_SIZE);                     \
			instance->size = g_DEFAULT_SIZE;                                             \
		} else {                                                                         \
			instance->data = malloc(sizeof(TYPE*) * size);                               \
			instance->size = size;                                                       \
		}                                                                                \
                                                                                         \
		return instance;                                                                 \
	}                                                                                    \
                                                                                         \
	TYPE* FPX##_at(TYPE##_array_list_t* const instance, const array_list_size_t index) { \
                                                                                         \
		if (instance && instance->data) {                                                \
			if (index < instance->capacity) {                                            \
				return (instance->data[index]);                                          \
			}                                                                            \
		}                                                                                \
                                                                                         \
		return NULL;                                                                     \
	}                                                                                    \
                                                                                         \
	TYPE* FPX##_get(TYPE##_array_list_t* const instance, TYPE* const item,               \
					TYPE##_comparator cmp) {                                             \
		const bool contains_data =                                                       \
			(instance && instance->data && instance->capacity > 1UL);                    \
                                                                                         \
		if (contains_data && item) {                                                     \
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
		if (instance) {                                                                  \
			array_list_size_t new_capacity = instance->capacity + 1UL;                   \
                                                                                         \
			if (new_capacity > instance->size) {                                         \
				array_list_size_t new_size = (instance->size * g_BUFFER_SCALAR);         \
                                                                                         \
				instance->data =                                                         \
					resizeArray(instance->data, instance->capacity, new_size);           \
                                                                                         \
				instance->size = new_size;                                               \
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
	array_list_size_t FPX##_capacity(const TYPE##_array_list_t* const instance) {        \
		return (instance ? instance->capacity : g_EMPTY_LIST);                           \
	}                                                                                    \
                                                                                         \
	array_list_size_t FPX##_size(const TYPE##_array_list_t* const instance) {            \
		return (instance ? instance->size : g_EMPTY_LIST);                               \
	}                                                                                    \
                                                                                         \
	bool FPX##_is_empty(const TYPE##_array_list_t* const instance) {                     \
		return (instance && instance->capacity == g_EMPTY_LIST);                         \
	}                                                                                    \
                                                                                         \
	void FPX##_free(TYPE##_array_list_t* instance) {                                     \
		freeArray(instance->data, instance->capacity);                                   \
                                                                                         \
		free(instance);                                                                  \
                                                                                         \
		instance = NULL;                                                                 \
	}                                                                                    \
                                                                                         \
	MAP_SOURCE(FPX, TYPE##_array_list, TYPE)
