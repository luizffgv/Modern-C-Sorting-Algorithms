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

#include <math.h>
#include <stdio.h>

#include <MemSwap/memswap.h>
#include <Sorts/insertion_sort.h>





#define INSERTIONSORT_DEF(name, type) \
void name(type *begin, type *end) \
{ \
\
    type aux; \
\
    for (type *top = begin, *top_end = end - 1; \
               top < top_end; \
               ++top) \
    { \
        type *cur = top + 1; \
        while (cur != begin && *cur < *(cur - 1)) \
        { \
            aux = *cur; \
            *cur = *(cur - 1); \
            *(cur - 1) = aux; \
            --cur; \
        } \
    } \
}





void InsertionSort(size_t elem_sz, Range range, Comparer comp)
{
    for (char *top = range.begin, *top_end = (char *)range.end - elem_sz;
               top < top_end;
               top += elem_sz)
    {
        char *cur = top + elem_sz;
        while (cur != range.begin && comp(cur, cur - elem_sz) == ordering_less)
        {
            MemSwap(elem_sz, cur, cur - elem_sz);
            cur -= elem_sz;
        }
    }
}





void InsertionSortVerbose(size_t elem_sz, Range range, Comparer comp, size_t interval)
{
    putchar('\n');

    size_t n_elems = ((char *)range.end - (char *)range.begin) / elem_sz;
    size_t ordered_sz = 0;

    for (char *top = range.begin, *top_end = (char *)range.end - elem_sz;
               top < top_end;
               top += elem_sz)
    {
        char *cur = top + elem_sz;
        while (cur != range.begin && comp(cur, cur - elem_sz) == ordering_less)
        {
            MemSwap(elem_sz, cur, cur - elem_sz);
            cur -= elem_sz;
        }

        if (!(++ordered_sz % interval))
        {
            printf("\r%.2f%%", pow(ordered_sz, 2) / pow(n_elems, 2) * 100);
            fflush(stdout);
        }
    }

    puts("\r100.00%");
}





INSERTIONSORT_DEF(InsertionSortBool, _Bool)
INSERTIONSORT_DEF(InsertionSortChar, char)
INSERTIONSORT_DEF(InsertionSortSignedChar, signed char)
INSERTIONSORT_DEF(InsertionSortUnsignedChar, unsigned char)
INSERTIONSORT_DEF(InsertionSortInt, int)
INSERTIONSORT_DEF(InsertionSortUnsigned, unsigned)
INSERTIONSORT_DEF(InsertionSortLong, long)
INSERTIONSORT_DEF(InsertionSortUnsignedLong, unsigned long)
INSERTIONSORT_DEF(InsertionSortLongLong, long long)
INSERTIONSORT_DEF(InsertionSortUnsignedLongLong, unsigned long long)
INSERTIONSORT_DEF(InsertionSortFloat, float)
INSERTIONSORT_DEF(InsertionSortDouble, double)
INSERTIONSORT_DEF(InsertionSortLongDouble, long double)
