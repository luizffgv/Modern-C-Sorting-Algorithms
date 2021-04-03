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

#ifndef SORTS_SELECTION_SORT_H_INCLUDED
#define SORTS_SELECTION_SORT_H_INCLUDED

#include <stddef.h>

#include "safe_assert.h"
#include "sorter.h"





void SelectionSort(size_t elem_sz, Range range, Comparer comp);
#ifndef ORDERING_DONT_ENFORCE_INTERFACES
static_assert(_Generic((SelectionSort), Sorter: 1, default: 0),
    "SelectionSort() does not match Sorter interface!\n"
    "ignore by defining ORDERING_DONT_ENFORCE_INTERFACES.");
#endif // #ifndef ORDERING_DONT_ENFORCE_INTERFACES

#endif // #ifndef SORTS_SELECTION_SORT_H_INCLUDED