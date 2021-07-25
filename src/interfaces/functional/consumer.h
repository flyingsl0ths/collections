#pragma once

#define CONSUMER_T(TYPE) typedef TYPE##_t* (*TYPE##_consumer)(TYPE*);

#define CONSUMER(TYPE) typedef TYPE* (*TYPE##_consumer)(TYPE*);
