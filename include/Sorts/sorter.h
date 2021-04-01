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

#ifndef SORTS_SORTER_H_INCLUDED
#define SORTS_SORTER_H_INCLUDED

#include <stddef.h>

#include <Ordering/comparer.h>

#include "range.h"





typedef void (*Sorter)(size_t, Range, Comparer);

#endif // #ifndef SORTS_SORTER_H_INCLUDED