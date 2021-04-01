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

/**
 * @file
 * @author Luiz Fernando F. G. Valle (github.com/luizffgv)
 * @brief Defines Ordering type
 * @version 1.0
 * @date 2021-03-09
 *
 * @copyright Copyright (c) 2021
 */

#ifndef ORDERING_ORDERING_H_INCLUDED
#define ORDERING_ORDERING_H_INCLUDED





/// Represents the way that two values compare
typedef enum Ordering
{
    ordering_less    = -1, ///< The first value is lesser than the second
    ordering_equal   =  0, ///< The values are equivalent
    ordering_greater =  1  ///< The first value is greater than the second
} Ordering;

#endif // #ifndef ORDERING_ORDERING_H_INCLUDED
