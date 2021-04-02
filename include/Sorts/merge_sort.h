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

#ifndef SORTS_MERGE_SORT_H_INCLUDED
#define SORTS_MERGE_SORT_H_INCLUDED

#include <assert.h>
#include <stddef.h>

#include "sorter.h"





void MergeSort(size_t elem_sz, Range range, Comparer comp);
#ifndef ORDERING_DONT_ENFORCE_INTERFACES
static_assert(_Generic((MergeSort), Sorter: 1, default: 0),
    "MergeSort() does not match Sorter interface!\n"
    "ignore by defining ORDERING_DONT_ENFORCE_INTERFACES");
#endif // #ifndef ORDERING_DONT_ENFORCE_INTERFACES

void MergeSortBool(_Bool *begin, _Bool *end);
void MergeSortSignedChar(signed char *begin, signed char *end);
void MergeSortUnsignedChar(unsigned char *begin, unsigned char *end);
void MergeSortInt(int *begin, int *end);
void MergeSortUnsigned(unsigned *begin, unsigned *end);
void MergeSortLong(long *begin, long *end);
void MergeSortUnsignedLong(unsigned long *begin, unsigned long *end);
void MergeSortLongLong(long long *begin, long long *end);
void MergeSortUnsignedLongLong(unsigned long long *begin, unsigned long long *end);
void MergeSortFloat(float *begin, float *end);
void MergeSortDouble(double *begin, double *end);
void MergeSortLongDouble(long double *begin, long double *end);

#define MergeSortG(begin, end) \
    _Generic((begin), \
        _Bool *: MergeSortBool, \
        signed char *: MergeSortSignedChar, \
        unsigned char *: MergeSortUnsignedChar, \
        int *: MergeSortInt, \
        unsigned *: MergeSortUnsigned, \
        long *: MergeSortLong, \
        unsigned long *: MergeSortUnsignedLong, \
        long long *: MergeSortLongLong, \
        unsigned long long *: MergeSortUnsignedLongLong, \
        float *: MergeSortFloat, \
        double *: MergeSortDouble, \
        long double *: MergeSortLongDouble \
    ) (begin, end)

#endif // #ifndef SORTS_MERGE_SORT_H_INCLUDED