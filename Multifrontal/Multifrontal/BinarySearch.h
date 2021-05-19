#include "main.h"
#include <cstdint>

#ifndef _BINARYSEARCH_H_
#define _BINARYSEARCH_H_

class BinarySearch
{
public:
	int64_t ExactlySearch(int64_t start, int64_t stop, double key, void *array, double(*getvalue)(void*, int64_t));
	int64_t SmallNearestSearch(int64_t start, int64_t stop, double key, void *array, double(*getvalue)(void*, int64_t));
};

#endif