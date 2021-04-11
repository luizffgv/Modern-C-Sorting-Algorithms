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

#include <Sorts/merge_sort.h>





#define MAX(x, y) ((x) > (y) ? (x) : (y))
#define RESERVED_DATA_SZ 128

#define MERGESORT_DEF(name, type) \
static void name##Merge_(type *dest, Range first, Range second) \
{ \
    size_t first_range_sz  = (char *)first.end  - (char *)first.begin; \
    size_t second_range_sz = (char *)second.end - (char *)second.begin; \
    size_t first_range_len  = first_range_sz / sizeof(type); \
    size_t second_range_len = second_range_sz / sizeof(type); \
    struct {type *begin, *end;} first_, second_; \
\
    first_.begin = first.begin; \
    first_.end = first.end; \
    second_.begin = second.begin; \
    second_.end = second.end; \
\
    _Thread_local static char reserved_first_data[RESERVED_DATA_SZ]; \
    _Thread_local static char reserved_second_data[RESERVED_DATA_SZ]; \
    type *first_old_begin  = first_.begin; \
    type *second_old_begin = second_.begin; \
    if (RESERVED_DATA_SZ >= MAX(first_range_sz, second_range_sz)) \
    { \
        first_.begin  = (type *)reserved_first_data; \
        second_.begin = (type *)reserved_second_data; \
    } \
    else \
    { \
        first_.begin  = malloc(first_range_sz); \
        second_.begin = malloc(second_range_sz); \
    } \
    first_.end  = first_.begin  + first_range_len; \
    second_.end = second_.begin + second_range_len; \
    memcpy(first_.begin, first_old_begin, first_range_sz); \
    memcpy(second_.begin, second_old_begin, second_range_sz); \
\
    while (first_.begin != first_.end && second_.begin != second_.end) \
    { \
        if (*first_.begin <= *second_.begin) \
            *dest++ = *first_.begin++; \
        else \
            *dest++ = *second_.begin++; \
    } \
\
    while (first_.begin != first_.end) \
        *dest++ = *first_.begin++; \
\
    while (second_.begin != second_.end) \
    { \
        *dest++ = *second_.begin++; \
    } \
\
    if (first_.end - first_range_len != (type *)reserved_first_data) \
    { \
        free(first_.end - first_range_len); \
        free(second_.end - second_range_len); \
    } \
} \
\
void name(type *begin, type *end) \
{ \
    const size_t range_len = end - begin; \
\
    if (range_len > 1) \
    { \
        Range first  = {begin, begin + range_len / 2}; \
        Range second = {first.end, end}; \
        name(first.begin, first.end); \
        name(second.begin, second.end); \
        name##Merge_(begin, first, second); \
    } \
} \





static void MergeUnrestricted_(size_t elem_sz, void *dest, Range first, Range second, Comparer comp);





void MergeSort(size_t elem_sz, Range range, Comparer comp)
{
    const size_t range_sz = (char *)range.end - (char *)range.begin;

    if (range_sz / elem_sz > 1)
    {
        // Find middle and align with elem_sz
        Range first = {
            range.begin,
            (char *)range.begin + range_sz / elem_sz / 2 * elem_sz
        };
        Range second = {first.end , range.end};
        MergeSort(elem_sz, first, comp);
        MergeSort(elem_sz, second, comp);
        MergeUnrestricted_(elem_sz, first.begin, first, second, comp);
    }
}





MERGESORT_DEF(MergeSortBool, _Bool)
MERGESORT_DEF(MergeSortChar, char)
MERGESORT_DEF(MergeSortSignedChar, signed char)
MERGESORT_DEF(MergeSortUnsignedChar, unsigned char)
MERGESORT_DEF(MergeSortInt, int)
MERGESORT_DEF(MergeSortUnsigned, unsigned)
MERGESORT_DEF(MergeSortLong, long)
MERGESORT_DEF(MergeSortUnsignedLong, unsigned long)
MERGESORT_DEF(MergeSortLongLong, long long)
MERGESORT_DEF(MergeSortUnsignedLongLong, unsigned long long)
MERGESORT_DEF(MergeSortFloat, float)
MERGESORT_DEF(MergeSortDouble, double)
MERGESORT_DEF(MergeSortLongDouble, long double)





void MergeUnrestricted_(size_t elem_sz, void *dest, Range first, Range second, Comparer comp)
{
    size_t first_range_sz  = (char *)first.end  - (char *)first.begin;
    size_t second_range_sz = (char *)second.end - (char *)second.begin;

    // Auxiliary memory
    _Thread_local static char reserved_first_data[RESERVED_DATA_SZ];
    _Thread_local static char reserved_second_data[RESERVED_DATA_SZ];
    // Possibly use auxiliary memory instead of heap
    void *first_old_begin = first.begin;
    void *second_old_begin = second.begin;
    if (RESERVED_DATA_SZ >= MAX(first_range_sz, second_range_sz))
    {
        first.begin  = reserved_first_data;
        second.begin = reserved_second_data;
    }
    else
    {
        first.begin  = malloc(first_range_sz);
        second.begin = malloc(second_range_sz);
    }
    first.end  = (char *)first.begin  + first_range_sz;
    second.end = (char *)second.begin + second_range_sz;
    memcpy(first.begin, first_old_begin, first_range_sz);
    memcpy(second.begin, second_old_begin, second_range_sz);

    while (first.begin != first.end && second.begin != second.end)
    {
        if (comp(first.begin, second.begin) != ordering_greater)
        {
            memcpy(dest, first.begin, elem_sz);
            first.begin = (char *)first.begin + elem_sz;
        }
        else
        {
            memcpy(dest, second.begin, elem_sz);
            second.begin = (char *)second.begin + elem_sz;
        }
        dest = (char *)dest + elem_sz;
    }

    while (first.begin != first.end)
    {
        memcpy(dest, first.begin, elem_sz);
        dest = (char *)dest + elem_sz;
        first.begin = (char *)first.begin + elem_sz;
    }

    while (second.begin != second.end)
    {
        memcpy(dest, second.begin, elem_sz);
        dest = (char *)dest + elem_sz;
        second.begin = (char *)second.begin + elem_sz;
    }

    // Possibly free auxiliary vectors
    if ((char *)first.end - first_range_sz != reserved_first_data)
    {
        free((char *)first.end - first_range_sz);
        free((char *)second.end - second_range_sz);
    }
}
