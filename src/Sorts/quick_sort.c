/*
    Copyright © 2021 Luiz Fernando F. G. Valle
    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

#include <stdlib.h>
#include <string.h>

#include <Sorts/quick_sort.h>





#define QUICKSORT_DEF(name, type) \
static void *name##Part_(type *begin, type *end) \
{ \
    type pivot_data = *begin; \
\
    while (1) \
    { \
        while (begin < end && pivot_data <= *end) \
            --end; \
        if (begin >= end) \
            break; \
        *begin++ = *end; \
\
        while (begin < end && *begin <= pivot_data) \
            ++begin; \
        if (begin >= end) \
            break; \
        *end-- = *begin; \
    } \
 \
    *end = pivot_data; \
 \
    return end; \
} \
\
static void name##_(type *begin, type *end) \
{ \
    if (begin < end) \
    { \
        type *middle = name##Part_(begin, end); \
        name##_(begin, middle); \
        name##_(middle + 1, end); \
    } \
} \
 \
void name(type *begin, type *end) \
{ \
    name##_( begin, end - 1); \
}





void *Part_(size_t elem_sz, Range range, void *pivot_data, Comparer comp);
static void QuickSort_(size_t elem_sz, Range range, void *pivot_data, Comparer comp);





void QuickSort(size_t elem_sz, Range range, Comparer comp)
{
#define RESERVED_PIVOT_DATA_SZ 64
    static _Thread_local char reserved_pivot_data[RESERVED_PIVOT_DATA_SZ];
    void *pivot_data = elem_sz > RESERVED_PIVOT_DATA_SZ ? malloc(elem_sz)
                                                        : reserved_pivot_data;

    QuickSort_(elem_sz, (Range){range.begin, range.end - elem_sz}, pivot_data, comp);

    if (pivot_data != reserved_pivot_data)
        free(pivot_data);
}





QUICKSORT_DEF(QuickSortBool, _Bool);
QUICKSORT_DEF(QuickSortChar, char);
QUICKSORT_DEF(QuickSortSignedChar, signed char);
QUICKSORT_DEF(QuickSortUnsignedChar, unsigned char);
QUICKSORT_DEF(QuickSortInt, int);
QUICKSORT_DEF(QuickSortUnsigned, unsigned);
QUICKSORT_DEF(QuickSortLong, long);
QUICKSORT_DEF(QuickSortUnsignedLong, unsigned long);
QUICKSORT_DEF(QuickSortLongLong, long long);
QUICKSORT_DEF(QuickSortUnsignedLongLong, unsigned long long);
QUICKSORT_DEF(QuickSortFloat, float);
QUICKSORT_DEF(QuickSortDouble, double);
QUICKSORT_DEF(QuickSortLongDouble, long double);





static void QuickSort_(size_t elem_sz, Range range, void *pivot_data, Comparer comp)
{
    if (range.begin < range.end)
    {
        void *middle = Part_(elem_sz, range, pivot_data, comp);
        QuickSort_(elem_sz, (Range){range.begin, middle}, pivot_data, comp);

        QuickSort_(elem_sz, (Range){middle + elem_sz, range.end}, pivot_data, comp);
    }
}





inline void *Part_(size_t elem_sz, Range range, void *pivot_data, Comparer comp)
{
    // TODO: Pick median as pivot
    memcpy(pivot_data, range.begin, elem_sz);

    while (1)
    {
        while (range.begin < range.end && comp(pivot_data, range.end) != ordering_greater)
            range.end -= elem_sz;
        if (range.begin >= range.end)
            break;
        memcpy(range.begin, range.end, elem_sz);
        range.begin += elem_sz;

        while (range.begin < range.end && comp(range.begin, pivot_data) != ordering_greater)
            range.begin += elem_sz;
        if (range.begin >= range.end)
            break;
        memcpy(range.end, range.begin, elem_sz);
        range.end -= elem_sz;
    }

    memcpy(range.end, pivot_data, elem_sz);

    return range.end;
}