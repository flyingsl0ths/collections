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
		CONTAINER_NAME##_t* const acc = supplier();                                      \
                                                                                         \
		const bool can_perform_mapping = (itr && f && supplier);                         \
                                                                                         \
		if (can_perform_mapping) {                                                       \
                                                                                         \
			while (FPX##_iter_has_next(itr)) {                                           \
				CONTAINER_VALUE_TYPE* value = FPX##_iter_next(itr);                      \
                                                                                         \
				CONTAINER_VALUE_TYPE* mapped_value = f(value);                           \
                                                                                         \
				if (mapped_value != value) {                                             \
					FPX##_add(acc, mapped_value);                                        \
				}                                                                        \
			}                                                                            \
		}                                                                                \
                                                                                         \
		return acc;                                                                      \
	}
