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

#ifndef INSERTION_SORT_H_INCLUDED
#define INSERTION_SORT_H_INCLUDED

#include <assert.h>
#include <stddef.h>

#include "sorter.h"





void InsertionSort(size_t elem_sz, Range range, Comparer comp);

void InsertionSortBool(_Bool *begin, _Bool *end);
void InsertionSortSignedChar(signed char *begin, signed char *end);
void InsertionSortUnsignedChar(unsigned char *begin, unsigned char *end);
void InsertionSortInt(int *begin, int *end);
void InsertionSortUnsigned(unsigned *begin, unsigned *end);
void InsertionSortLong(long *begin, long *end);
void InsertionSortUnsignedLong(unsigned long *begin, unsigned long *end);
void InsertionSortLongLong(long long *begin, long long *end);
void InsertionSortUnsignedLongLong(unsigned long long *begin, unsigned long long *end);
void InsertionSortFloat(float *begin, float *end);
void InsertionSortDouble(double *begin, double *end);
void InsertionSortLongDouble(long double *begin, long double *end);

#define InsertionSortG(begin, end) \
    _Generic((begin), \
        _Bool *: InsertionSortBool, \
        signed char *: InsertionSortSignedChar, \
        unsigned char *: InsertionSortUnsignedChar, \
        int *: InsertionSortInt, \
        unsigned *: InsertionSortUnsigned, \
        long *: InsertionSortLong, \
        unsigned long *: InsertionSortUnsignedLong, \
        long long *: InsertionSortLongLong, \
        unsigned long long *: InsertionSortUnsignedLongLong, \
        float *: InsertionSortFloat, \
        double *: InsertionSortDouble, \
        long double *: InsertionSortLongDouble \
    ) (begin, end)

void InsertionSortVerbose(size_t elem_sz, Range range, Comparer comp, size_t interval);
#ifndef ORDERING_DONT_ENFORCE_INTERFACES
static_assert(_Generic((InsertionSort), Sorter: 1, default: 0),
    "InsertionSort() does not match Sorter interface!\n"
    "ignore by defining ORDERING_DONT_ENFORCE_INTERFACES");
#endif // #ifndef ORDERING_DONT_ENFORCE_INTERFACES

#endif // #ifndef INSERTION_SORT_H_INCLUDED