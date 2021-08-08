#pragma once

#define DESTRUCTOR_OF(TYPE) typedef void (*TYPE##_destructor)(TYPE*);
