#pragma once

#define SUPPLIER_T(TYPE) typedef TYPE##_t* (*TYPE##_supplier)();

#define SUPPLIER(TYPE) typedef TYPE* (*TYPE##_supplier)();
