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

#include <stdlib.h> // For malloc()
#include <string.h> // For memcpy()

#include <MemSwap/memswap.h>
#include <Sorts/radix_sort.h>





#define MAX(x, y) ((x) > (y) ? (x) : (y))
#define ABS(x) ((x) < 0 ? -(x) : (x))

#define MinMaxG_(begin, end) \
    _Generic((begin), \
        _Bool *: MinMaxBool_, \
        char *: MinMaxChar_, \
        signed char *: MinMaxSignedChar_, \
        unsigned char *: MinMaxUnsignedChar_, \
        int *: MinMaxInt_, \
        unsigned *: MinMaxUnsigned_, \
        long *: MinMaxLong_, \
        unsigned long *: MinMaxUnsignedLong_, \
        long long *: MinMaxLongLong_, \
        unsigned long long *: MinMaxUnsignedLongLong_ \
        /* float *: MinMaxFloat_, */ \
        /* double *: MinMaxDouble_, */ \
        /* long double *: MinMaxLongDouble_ */ \
    )(begin, end);





typedef struct
{
    void *first;
    void *second;
} Pair_;





#define MINMAX_DEF(name, type) \
static Pair_ name(type *begin, type *end) \
{ \
    Pair_ pair = {begin, begin}; \
    while (++begin != end) \
    { \
        if (*begin > *(type *)pair.second) \
            pair.second = begin; \
        else if (*begin < *(type *)pair.first) \
            pair.first = begin; \
    } \
\
    return pair; \
} \





#define RADIXSORT_DEF(name, type) \
static void name##_(type *begin, type *end, type unit) \
{ \
    size_t count[10] = {}; \
\
    for (type *cur = begin; cur < end; ++cur) \
        ++count[ABS(*cur) / unit % 10]; \
\
    type *vecs[10]; \
    type *tops[10]; \
\
    for (size_t i = 0; i < sizeof(count) / sizeof(*count); ++i) \
        tops[i] = vecs[i] = malloc(count[i] * sizeof(*vecs[i])); \
\
    for (type *cur = begin; cur < end; ++cur) \
        *(tops[ABS(*cur) / unit % 10]++) = *cur; \
\
    for (size_t i = 0; i < sizeof(count) / sizeof(*count); ++i) \
    { \
        memcpy(begin, vecs[i], count[i] * sizeof(*vecs[i])); \
        begin += count[i]; \
        free(vecs[i]); \
    } \
} \
\
static void name##Sign_(type *begin, type *end) \
{ \
    type *arr = malloc((end - begin) * sizeof(type)); \
\
    size_t positives = 0; \
\
    for (type *cur = begin; cur < end; ++cur) \
        if (*cur >= 0) \
            ++positives; \
\
    type *pos_start = arr + (end - begin) - positives; \
    type *neg_end = pos_start - 1; \
\
    for (type *cur = begin; cur < end; ++cur) \
        if (*cur >= 0) \
            *(pos_start++) = *cur; \
        else \
            *(neg_end--) = *cur; \
\
    memcpy(begin, arr, (end - begin) * sizeof(type)); \
\
    free(arr); \
} \
\
void name(type *begin, type *end) \
{ \
    type unit = 1; \
\
    Pair_ minmax = MinMaxG_(begin, end); \
    type min = *(type *)minmax.first; \
    type max = *(type *)minmax.second; \
\
    while (1) \
    { \
        name##_(begin, end, unit); \
\
        if (max >= 0 && max / unit >= 10 || min < 0 && min / unit <= -10) \
            unit *= 10; \
        else \
            break; \
    } \
\
    name##Sign_(begin, end); \
}





MINMAX_DEF(MinMaxBool_, _Bool);
MINMAX_DEF(MinMaxChar_, char);
MINMAX_DEF(MinMaxSignedChar_, signed char);
MINMAX_DEF(MinMaxUnsignedChar_, unsigned char);
MINMAX_DEF(MinMaxInt_, int);
MINMAX_DEF(MinMaxUnsigned_, unsigned);
MINMAX_DEF(MinMaxLong_, long);
MINMAX_DEF(MinMaxUnsignedLong_, unsigned long);
MINMAX_DEF(MinMaxLongLong_, long long);
MINMAX_DEF(MinMaxUnsignedLongLong_, unsigned long long);
// MINMAX_DEF(MinMaxFloat_, float);
// MINMAX_DEF(MinMaxDouble_, double);
// MINMAX_DEF(MinMaxLongDouble_, long double);





RADIXSORT_DEF(RadixSortBool, _Bool);
RADIXSORT_DEF(RadixSortChar, char);
RADIXSORT_DEF(RadixSortSignedChar, signed char);
RADIXSORT_DEF(RadixSortUnsignedChar, unsigned char);
RADIXSORT_DEF(RadixSortInt, int);
RADIXSORT_DEF(RadixSortUnsigned, unsigned);
RADIXSORT_DEF(RadixSortLong, long);
RADIXSORT_DEF(RadixSortUnsignedLong, unsigned long);
RADIXSORT_DEF(RadixSortLongLong, long long);
RADIXSORT_DEF(RadixSortUnsignedLongLong, unsigned long long);
// RADIXSORT_DEF(RadixSortFloat, float);
// RADIXSORT_DEF(RadixSortDouble, double);
// RADIXSORT_DEF(RadixSortLongDouble, long double);
