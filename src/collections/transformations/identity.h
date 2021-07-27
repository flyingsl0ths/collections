#pragma once

#define IDENTITY(TYPE)                                                                   \
	TYPE TYPE##_identity(TYPE type) {                                                    \
		return type;                                                                     \
	}

#define IDENTITY_PTR(TYPE)                                                               \
	TYPE* TYPE##_identity_ptr(TYPE* type) {                                              \
		return type;                                                                     \
	}
