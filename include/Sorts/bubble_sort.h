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

#ifndef SORTS_BUBBLE_SORT_H_INCLUDED
#define SORTS_BUBBLE_SORT_H_INCLUDED

#include <assert.h>
#include <stddef.h>

#include "sorter.h"





void BubbleSort(size_t elem_sz, Range range, Comparer comp);

void BubbleSortBool(_Bool *begin, _Bool *end);
void BubbleSortSignedChar(signed char *begin, signed char *end);
void BubbleSortUnsignedChar(unsigned char *begin, unsigned char *end);
void BubbleSortInt(int *begin, int *end);
void BubbleSortUnsigned(unsigned *begin, unsigned *end);
void BubbleSortLong(long *begin, long *end);
void BubbleSortUnsignedLong(unsigned long *begin, unsigned long *end);
void BubbleSortLongLong(long long *begin, long long *end);
void BubbleSortUnsignedLongLong(unsigned long long *begin, unsigned long long *end);
void BubbleSortFloat(float *begin, float *end);
void BubbleSortDouble(double *begin, double *end);
void BubbleSortLongDouble(long double *begin, long double *end);

#define BubbleSortG(begin, end) \
    _Generic((begin), \
        _Bool *: BubbleSortBool, \
        signed char *: BubbleSortSignedChar, \
        unsigned char *: BubbleSortUnsignedChar, \
        int *: BubbleSortInt, \
        unsigned *: BubbleSortUnsigned, \
        long *: BubbleSortLong, \
        unsigned long *: BubbleSortUnsignedLong, \
        long long *: BubbleSortLongLong, \
        unsigned long long *: BubbleSortUnsignedLongLong, \
        float *: BubbleSortFloat, \
        double *: BubbleSortDouble, \
        long double *: BubbleSortLongDouble \
    ) (begin, end)

#ifndef ORDERING_DONT_ENFORCE_INTERFACES
static_assert(_Generic((BubbleSort), Sorter: 1, default: 0),
    "BubbleSort() does not match Sorter interface!\n"
    "ignore by defining ORDERING_DONT_ENFORCE_INTERFACES.");
#endif // #ifndef ORDERING_DONT_ENFORCE_INTERFACES

#endif // #ifndef SORTS_BUBBLE_SORT_H_INCLUDED
