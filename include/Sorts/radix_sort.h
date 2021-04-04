
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

#ifndef SORTS_RADIX_SORT_H_INCLUDED
#define SORTS_RADIX_SORT_H_INCLUDED

#include <stddef.h>

#include "safe_assert.h"
#include "sorter.h"





void RadixSort(size_t elem_sz, Range range, Comparer comp);
#ifndef ORDERING_DONT_ENFORCE_INTERFACES
static_assert(_Generic((RadixSort), Sorter: 1, default: 0),
    "RadixSort() does not match Sorter interface.\n"
    "ignore by defining ORDERING_DONT_ENFORCE_INTERFACES.");
#endif // #ifndef ORDERING_DONT_ENFORCE_INTERFACES

void RadixSortBool(_Bool *begin, _Bool *end);
void RadixSortChar(char *begin, char *end);
void RadixSortSignedChar(signed char *begin, signed char *end);
void RadixSortUnsignedChar(unsigned char *begin, unsigned char *end);
void RadixSortInt(int *begin, int *end);
void RadixSortUnsigned(unsigned *begin, unsigned *end);
void RadixSortLong(long *begin, long *end);
void RadixSortUnsignedLong(unsigned long *begin, unsigned long *end);
void RadixSortLongLong(long long *begin, long long *end);
void RadixSortUnsignedLongLong(unsigned long long *begin, unsigned long long *end);
// void RadixSortFloat(float *begin, float *end);
// void RadixSortDouble(double *begin, double *end);
// void RadixSortLongDouble(long double *begin, long double *end);

#define RadixSortG(begin, end) \
    _Generic((begin), \
        _Bool *: RadixSortBool, \
        char *: RadixSortChar, \
        signed char *: RadixSortSignedChar, \
        unsigned char *: RadixSortUnsignedChar, \
        int *: RadixSortInt, \
        unsigned *: RadixSortUnsigned, \
        long *: RadixSortLong, \
        unsigned long *: RadixSortUnsignedLong, \
        long long *: RadixSortLongLong, \
        unsigned long long *: RadixSortUnsignedLongLong \
        /* float *: RadixSortFloat, */ \
        /* double *: RadixSortDouble, */ \
        /* long double *: RadixSortLongDouble */ \
    )(begin, end)

#endif // #ifndef SORTS_C_RADIX_SORT_H_INCLUDED