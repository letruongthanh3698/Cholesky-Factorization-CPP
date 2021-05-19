#include "stdafx.h"

#include <cstdint>
#include "BinarySearch.h"

int64_t BinarySearch::ExactlySearch(int64_t left, int64_t right, double key, void *array, double(*getvalue)(void*,int64_t))
{
    int64_t pos=-1;
    int64_t middle=0;
    double value;
    while (pos==-1 && left<=right)
    {
        middle=(left+right)/2;
        value=getvalue(array,middle);
        if (value<key)
            left=middle+1;
        else if (value>key)
            right=middle-1;
        else
            pos=middle;
    }
    return pos;
}

int64_t BinarySearch::SmallNearestSearch(int64_t left, int64_t right, double key, void *array, double(*getvalue)(void*,int64_t))
{
    int64_t pos=-1;
    int64_t middle=0;
    double value;
    while (pos==-1 && left<=right)
    {
        middle=(left+right)/2;
        value=getvalue(array,middle);
        if (value<=key)
        {
            pos=middle;
            left=middle+1;
        }
        else
            right=middle-1;
    }
    return pos;
}
