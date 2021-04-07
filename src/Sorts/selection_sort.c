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

#include <MemSwap/memswap.h>
#include <Sorts/selection_sort.h>





void SelectionSort(size_t elem_sz, Range range, Comparer comp)
{
    for (void *top = range.begin; top < range.end; top += elem_sz)
    {
        void *lesser = top;
        for (void *cur = top + elem_sz; cur < range.end; cur += elem_sz)
            if (comp(cur, lesser) == ordering_less)
                lesser = cur;

        if (lesser != top)
            MemSwap(elem_sz, top, lesser);
    }
}
