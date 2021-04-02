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

#ifndef SORTS_QUICK_SORT_H_INCLUDED
#define SORTS_QUICK_SORT_H_INCLUDED

#include <assert.h>
#include <stddef.h>

#include "sorter.h"





void QuickSort(size_t elem_sz, Range range, Comparer comp);
#ifndef ORDERING_DONT_ENFORCE_INTERFACES
static_assert(_Generic((QuickSort), Sorter: 1, default: 0),
    "QuickSort() does not match Sorter interface.\n"
    "ignore by defining ORDERING_DONT_ENFORCE_INTERFACES.");
#endif // #ifndef ORDERING_DONT_ENFORCE_INTERFACES

void QuickSortBool(_Bool *begin, _Bool *end);
void QuickSortSignedChar(signed char *begin, signed char *end);
void QuickSortUnsignedChar(unsigned char *begin, unsigned char *end);
void QuickSortInt(int *begin, int *end);
void QuickSortUnsigned(unsigned *begin, unsigned *end);
void QuickSortLong(long *begin, long *end);
void QuickSortUnsignedLong(unsigned long *begin, unsigned long *end);
void QuickSortLongLong(long long *begin, long long *end);
void QuickSortUnsignedLongLong(unsigned long long *begin, unsigned long long *end);
void QuickSortFloat(float *begin, float *end);
void QuickSortDouble(double *begin, double *end);
void QuickSortLongDouble(long double *begin, long double *end);

#define QuickSortG(begin, end) \
    _Generic((begin), \
        _Bool *: QuickSortBool, \
        signed char *: QuickSortSignedChar, \
        unsigned char *: QuickSortUnsignedChar, \
        int *: QuickSortInt, \
        unsigned *: QuickSortUnsigned, \
        long *: QuickSortLong, \
        unsigned long *: QuickSortUnsignedLong, \
        long long *: QuickSortLongLong, \
        unsigned long long *: QuickSortUnsignedLongLong, \
        float *: QuickSortFloat, \
        double *: QuickSortDouble, \
        long double *: QuickSortLongDouble \
    ) (begin, end)

#endif // #ifndef SORTS_C_QUICK_SORT_H_INCLUDED