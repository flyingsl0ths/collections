#pragma once

#include "../../interfaces/functional/consumer.h"
#include "../../interfaces/functional/supplier.h"

#define MAP_HEADER(FPX, CONTAINER_NAME, CONTAINER_VALUE_TYPE)                            \
	SUPPLIER_T(CONTAINER_NAME)                                                           \
                                                                                         \
	CONSUMER(CONTAINER_VALUE_TYPE)                                                       \
                                                                                         \
	CONTAINER_NAME##_t* CONTAINER_NAME##_map(CONTAINER_NAME##_supplier supplier,         \
											 CONTAINER_NAME##_iter_t* const itr,         \
											 CONTAINER_VALUE_TYPE##_consumer f);

#define MAP_SOURCE(FPX, CONTAINER_NAME, CONTAINER_VALUE_TYPE)                            \
	CONTAINER_NAME##_t* CONTAINER_NAME##_map(CONTAINER_NAME##_supplier supplier,         \
											 CONTAINER_NAME##_iter_t* const itr,         \
											 CONTAINER_VALUE_TYPE##_consumer f) {        \
                                                                                         \
		CONTAINER_NAME##_t* acc = supplier();                                            \
                                                                                         \
		const bool can_perform_mapping = (itr && f && supplier);                         \
                                                                                         \
		if (can_perform_mapping) {                                                       \
                                                                                         \
			bool has_more_items = FPX##_iter_has_next(itr);                              \
                                                                                         \
			while (has_more_items) {                                                     \
				CONTAINER_VALUE_TYPE* value = FPX##_iter_next(itr);                      \
                                                                                         \
				if (value) {                                                             \
					FPX##_add(acc, f(value));                                            \
				}                                                                        \
                                                                                         \
				has_more_items = FPX##_iter_has_next(itr);                               \
			}                                                                            \
		}                                                                                \
                                                                                         \
		return acc;                                                                      \
	}
