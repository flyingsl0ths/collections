#pragma once

#define ITERATOR(FPX, CONTAINER, VALUE)                                                  \
	typedef struct CONTAINER##_iter_t CONTAINER##_iter_t;                                \
                                                                                         \
	CONTAINER##_iter_t* FPX##_iter_new(CONTAINER##_t* const instance);                   \
                                                                                         \
	bool FPX##_iter_has_next(const CONTAINER##_iter_t* const itr);                       \
                                                                                         \
	VALUE* FPX##_iter_next(CONTAINER##_iter_t* const itr);                               \
                                                                                         \
	void FPX##_iter_free(CONTAINER##_iter_t* itr);
