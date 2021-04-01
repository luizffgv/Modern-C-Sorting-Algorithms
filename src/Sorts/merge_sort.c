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

#include <stdlib.h>
#include <string.h>

#include <Sorts/merge_sort.h>





#define MAX(x, y) ((x) > (y) ? (x) : (y))





static void MergeUnrestricted_(size_t elem_sz, void *dest, Range first, Range second, Comparer comp);





void MergeSort(size_t elem_sz, Range range, Comparer comp)
{
    const size_t range_sz = range.end - range.begin;

    if (range_sz / elem_sz > 1)
    {
        // Find middle and align with elem_sz
        Range first = {range.begin, range.begin + range_sz / elem_sz / 2 * elem_sz};
        Range second = {first.end , range.end};
        MergeSort(elem_sz, first, comp);
        MergeSort(elem_sz, second, comp);
        MergeUnrestricted_(elem_sz, first.begin, first, second, comp);
    }
}





void MergeUnrestricted_(size_t elem_sz, void *dest, Range first, Range second, Comparer comp)
{
    size_t first_range_sz  = first.end  - first.begin;
    size_t second_range_sz = second.end - second.begin;

#define RESERVED_DATA_SZ 128
    // Auxiliary memory
    _Thread_local static char reserved_first_data[RESERVED_DATA_SZ];
    _Thread_local static char reserved_second_data[RESERVED_DATA_SZ];
    // Possibly use auxiliary memory instead of heap
    void *first_old_begin = first.begin;
    void *second_old_begin = second.begin;
    if (RESERVED_DATA_SZ >= MAX(first_range_sz, second_range_sz))
    {
        first.begin  = reserved_first_data;
        second.begin = reserved_second_data;
    }
    else
    {
        first.begin  = malloc(first_range_sz);
        second.begin = malloc(second_range_sz);
    }
    first.end  = first.begin  + first_range_sz;
    second.end = second.begin + second_range_sz;
    memcpy(first.begin, first_old_begin, first_range_sz);
    memcpy(second.begin, second_old_begin, second_range_sz);

    while (first.begin != first.end && second.begin != second.end)
    {
        if (comp(first.begin, second.begin) != ordering_greater)
        {
            memcpy(dest, first.begin, elem_sz);
            first.begin += elem_sz;
        }
        else
        {
            memcpy(dest, second.begin, elem_sz);
            second.begin += elem_sz;
        }
        dest += elem_sz;
    }

    while (first.begin != first.end)
    {
        memcpy(dest, first.begin, elem_sz);
        dest += elem_sz;
        first.begin += elem_sz;
    }

    while (second.begin != second.end)
    {
        memcpy(dest, second.begin, elem_sz);
        dest += elem_sz;
        second.begin += elem_sz;
    }

    // Possibly free auxiliary vectors
    if (first.end - first_range_sz != reserved_first_data)
    {
        free(first.end - first_range_sz);
        free(second.end - second_range_sz);
    }
}