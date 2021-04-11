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

#include <math.h> // Por pow

#include <MemSwap/memswap.h>
#include <Sorts/insertion_sort.h>
#include <Sorts/shell_sort.h>





static unsigned long long A036562_(unsigned long long n);





void ShellSort(size_t elem_sz, Range range, Comparer comp)
{
    long long gap_algo_n = -1;
    while (A036562_(gap_algo_n + 1) < ((char *)range.end - (char *)range.begin)
                                      / elem_sz / 2)
        ++gap_algo_n;

    while (gap_algo_n >= 0)
    {
        long long leap = A036562_(gap_algo_n) * elem_sz;

        for (char *top = range.begin, *top_end = (char *)range.end - leap;
                   top < top_end;
                   top += elem_sz)
        {
            char *cur = top + leap;

            while ((char *)range.begin + leap <= cur
                   && comp(cur, cur - leap) == ordering_less)
            {
                MemSwap(elem_sz, cur, cur - leap);
                cur -= leap;
            }
        }

        --gap_algo_n;
    }

    InsertionSort(elem_sz, (Range){range.begin, range.end}, comp);
}





unsigned long long A036562_(unsigned long long n)
{
    return pow(4, n + 1) + 3 * pow(2, n) + 1;
}
