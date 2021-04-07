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

#ifndef SORTS_HEAP_SORT_H_INCLUDED
#define SORTS_HEAP_SORT_H_INCLUDED

#include <stddef.h>

#include "safe_assert.h"
#include "sorter.h"





void HeapSort(size_t elem_sz, Range range, Comparer comp);
#ifndef ORDERING_DONT_ENFORCE_INTERFACES
static_assert(_Generic((HeapSort), Sorter: 1, default: 0),
    "HeapSort() does not match Sorter interface!\n"
    "ignore by defining ORDERING_DONT_ENFORCE_INTERFACES.");
#endif // #ifndef ORDERING_DONT_ENFORCE_INTERFACES

void HeapSortBool(_Bool *begin, _Bool *end);
void HeapSortChar(char *begin, char *end);
void HeapSortSignedChar(signed char *begin, signed char *end);
void HeapSortUnsignedChar(unsigned char *begin, unsigned char *end);
void HeapSortInt(int *begin, int *end);
void HeapSortUnsigned(unsigned *begin, unsigned *end);
void HeapSortLong(long *begin, long *end);
void HeapSortUnsignedLong(unsigned long *begin, unsigned long *end);
void HeapSortLongLong(long long *begin, long long *end);
void HeapSortUnsignedLongLong(unsigned long long *begin, unsigned long long *end);
void HeapSortFloat(float *begin, float *end);
void HeapSortDouble(double *begin, double *end);
void HeapSortLongDouble(long double *begin, long double *end);

#define HeapSortG(begin, end) \
    _Generic((begin), \
        _Bool *: HeapSortBool, \
        char *: HeapSortChar, \
        signed char *: HeapSortSignedChar, \
        unsigned char *: HeapSortUnsignedChar, \
        int *: HeapSortInt, \
        unsigned *: HeapSortUnsigned, \
        long *: HeapSortLong, \
        unsigned long *: HeapSortUnsignedLong, \
        long long *: HeapSortLongLong, \
        unsigned long long *: HeapSortUnsignedLongLong, \
        float *: HeapSortFloat, \
        double *: HeapSortDouble, \
        long double *: HeapSortLongDouble \
    )(begin, end)

#endif // #ifndef SORTS_HEAP_SORT_H_INCLUDED
