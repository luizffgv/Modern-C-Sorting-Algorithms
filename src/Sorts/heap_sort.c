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

#include <MemSwap/memswap.h>
#include <Sorts/heap_sort.h>





#define HEAPSORT_DEF(name, type) \
static void name##Heapify_(type *begin, type *end, size_t root) \
{ \
    type aux; \
    type *root_ptr = begin + root; \
\
    type *left = begin + root * 2 + 1; \
    type *right = begin + root * 2 + 2; \
\
    if (left >= end) \
        return; \
\
    type *largest = root_ptr; \
    if (*left > *largest) \
        largest = left; \
    if (right < end \
        && *right > *largest) \
        largest = right; \
\
    if (largest != root_ptr) \
    { \
        aux = *root_ptr; \
        *root_ptr = *largest; \
        *largest = aux; \
        --end; \
        name##Heapify_(begin, end, largest - begin); \
    } \
} \
\
void name(type *begin, type *end) \
{ \
    type aux; \
\
    for (size_t cur_i = (end - begin - 2) / 2; cur_i > 0; --cur_i) \
        name##Heapify_(begin, end, cur_i); \
\
    if (begin < end) \
        name##Heapify_(begin, end, 0); \
\
    while (end > begin + 1) \
    { \
        aux = begin[0]; \
        begin[0] = *(end - 1); \
        *(end - 1) = aux; \
        name##Heapify_(begin, end--, 0); \
    } \
}





static void Heapify_(size_t elem_sz, Range range, size_t root, Comparer comp);





void HeapSort(size_t elem_sz, Range range, Comparer comp)
{
    for (void *cur = range.begin + ((range.end - range.begin - 2 * elem_sz) / 2);
               cur >= range.begin;
               cur -= elem_sz)
            Heapify_(elem_sz, range, (cur - range.begin) / elem_sz, comp);

    for (void *cur = range.end - elem_sz; cur > range.begin; cur -= elem_sz)
    {
        MemSwap(elem_sz, range.begin, cur);
        range.end -= elem_sz;
        Heapify_(elem_sz, range, 0, comp);
    }
}





static void Heapify_(size_t elem_sz, Range range, size_t root, Comparer comp)
{
    void *root_ptr = range.begin + root * elem_sz;

    void *left = range.begin + (root * 2 + 1) * elem_sz;
    void *right = range.begin + (root * 2 + 2) * elem_sz;

    // Returning early makes the algorithm run almost twice as fast
    if (left >= range.end)
        return;

    void *largest = root_ptr;
    if (comp(left, largest) == ordering_greater)
        largest = left;
    if (right < range.end
        && comp(right, largest) == ordering_greater)
        largest = right;

    if (largest != root_ptr)
    {
        MemSwap(elem_sz, root_ptr, largest);
        Heapify_(elem_sz, range, (largest - range.begin) / elem_sz, comp);
    }
}





HEAPSORT_DEF(HeapSortBool, _Bool);
HEAPSORT_DEF(HeapSortChar, char);
HEAPSORT_DEF(HeapSortSignedChar, signed char);
HEAPSORT_DEF(HeapSortUnsignedChar, unsigned char);
HEAPSORT_DEF(HeapSortInt, int);
HEAPSORT_DEF(HeapSortUnsigned, unsigned);
HEAPSORT_DEF(HeapSortLong, long);
HEAPSORT_DEF(HeapSortUnsignedLong, unsigned long);
HEAPSORT_DEF(HeapSortLongLong, long long);
HEAPSORT_DEF(HeapSortUnsignedLongLong, unsigned long long);
HEAPSORT_DEF(HeapSortFloat, float);
HEAPSORT_DEF(HeapSortDouble, double);
HEAPSORT_DEF(HeapSortLongDouble, long double);
