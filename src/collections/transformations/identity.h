#pragma once

#define IDENTITY(TYPE)                                                                   \
	TYPE identity(TYPE type) {                                                           \
		return type;                                                                     \
	}

#define IDENTITY_PTR(TYPE)                                                               \
	TYPE* identity_p(TYPE* type) {                                                       \
		return type;                                                                     \
	}
