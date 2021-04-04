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

#include <stdbool.h>

#include <MemSwap/memswap.h>
#include <Sorts/bubble_sort.h>





#define BUBBLESORT_DEF(name, type) \
void name(type *begin, type *end) \
{ \
    type aux;\
\
    for (type *sorted_bottom = end - 1; \
              sorted_bottom != begin; \
              --sorted_bottom) \
    { \
        bool sorted = true; \
\
        for (type *cur = begin + 1; \
                   cur <= sorted_bottom; \
                   ++cur) \
            if (*cur < *(cur - 1)) \
            { \
                aux = *cur; \
                *cur = *(cur - 1); \
                *(cur - 1) = aux; \
                sorted = false; \
            } \
\
        if (sorted) \
            break; \
    } \
}





void BubbleSort(size_t elem_sz, Range range, Comparer comp)
{
    for (void *sorted_bottom = range.end - elem_sz;
              sorted_bottom != range.begin;
              sorted_bottom -= elem_sz)
    {
        bool sorted = true;

        for (void *cur = range.begin + elem_sz;
                   cur <= sorted_bottom;
                   cur += elem_sz)
            if (comp(cur, cur - elem_sz) == ordering_less)
            {
                MemSwap(elem_sz, cur, cur - elem_sz);
                sorted = false;
            }

        if (sorted)
            break;
    }
}





BUBBLESORT_DEF(BubbleSortBool, _Bool);
BUBBLESORT_DEF(BubbleSortChar, char);
BUBBLESORT_DEF(BubbleSortSignedChar, signed char);
BUBBLESORT_DEF(BubbleSortUnsignedChar, unsigned char);
BUBBLESORT_DEF(BubbleSortInt, int);
BUBBLESORT_DEF(BubbleSortUnsigned, unsigned);
BUBBLESORT_DEF(BubbleSortLong, long);
BUBBLESORT_DEF(BubbleSortUnsignedLong, unsigned long);
BUBBLESORT_DEF(BubbleSortLongLong, long long);
BUBBLESORT_DEF(BubbleSortUnsignedLongLong, unsigned long long);
BUBBLESORT_DEF(BubbleSortFloat, float);
BUBBLESORT_DEF(BubbleSortDouble, double);
BUBBLESORT_DEF(BubbleSortLongDouble, long double);