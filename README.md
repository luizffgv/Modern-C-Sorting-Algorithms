[![CodeFactor](https://www.codefactor.io/repository/github/luizffgv/modern-c-sorting-algorithms/badge)](https://www.codefactor.io/repository/github/luizffgv/modern-c-sorting-algorithms)
# Modern C Sorting Algorithms

## Compiling
--------------------------------------------------------------------------------
* Use `include` as an include directory
* Compile all .c files in `src` the way you want. They can be matched using
`src/*/*.c` on Linux.
* Voilà! you can now use all headers, mainly from `include/Sorts`





## Usage
--------------------------------------------------------------------------------
### Built-in types
Some of the algorithms have a "G" variant: a macro that calls the correct
function according to the type passed. It works using the C11 _Generic keyword.

Use it by passing a pointer to the first and one-past-last elements of an array:

```c
#include <stdio.h>
#include <stddef.h>

#include <Sorts/quick_sort.h>

int main(void)
{
    int arr[] = {5, 8, 3, 2, 9, 1, 3};

    QuickSortG(arr, arr + sizeof(arr) / sizeof(*arr));

    for (size_t i = 0; i < sizeof(arr) / sizeof(*arr); ++i)
        printf("%d ", arr[i]);

    return 0;
}
```

The code above outputs `1 2 3 3 5 8 9`.





### User-defined types
User-defined types require the usage of our "non-G" algorithms, which require a
callback function just like the standard library's `qsort` does. `qsort`'s
callback functions return an `int`, but our callbacks should return a value of
type `Ordering` indicating the relationship between two values. A callback that
compares two `int`s can be defined the following way:

```c
#include <Ordering/ordering.h>

Ordering CompareInts(void *first, void *second)
{
    if (*(int *)first > *(int *)second)
        return ordering_greater;
    else if (*(int *)first < *(int *)second)
        return ordering_less;
    return ordering_equal;
}
```

That was just an example, `int` is not user-defined! Use `QuickSortG` if you
want to sort `int`s!

If an user-defined type supports the `>`, `<` and `==` operators, you can
automatically declare and define a callback using the macros
`COMPARER_ARITHMETIC_FUNC_DECL` and `COMPARER_ARITHMETIC_FUNC_DEF`

```c
// Automatically defines a function named CompareFloats,
// which can be used as a callback to sort a float array.
COMPARER_ARITHMETIC_FUNC_DEF(CompareFloats, float)
```

Again, that was just an example. `float` is not user-defined!


So, to use any of the "non-G" algorithms you must pass additional arguments,
including a value of type `Range` — declared in `Sorts/range.h`:

```c
    QuickSort(
        // Size of the type
        sizeof(*arr),
        // Range containing addresses of first and one-past-last element
        (Range){arr, arr + sizeof(arr) / sizeof(*arr)},
        // Callback function
        CompareInts
    );
```

Both `QuickSortG` and `QuickSort` will sort your `arr`, but `QuickSort` needs to
call your function each time two values need to be compared, so it runs
noticeably slower, albeit not extremely.





## List of functions
--------------------------------------------------------------------------------
### **Using the Sorter interface**:
BubbleSort, HeapSort, InsertionSort, MergeSort, QuickSort, SelectionSort and
ShellSort.

### **"G" variants (actually macros)**:
BubbleSortG, HeapSortG, InsertionSortG, MergeSortG, QuickSortG and RadixSortG.

### **Type-specific**:
Any of the "G" variants with the "G" replaced by "Bool", "Char", "SignedChar",
"UnsignedChar", "Int", "Unsigned", "Long", "UnsignedLong", "LongLong",
"UnsignedLongLong", "Float", "Double" or "LongDouble" represent type-specific
functions that may or may not be implemented, so do not declare anything with
these names.





## Performance
--------------------------------------------------------------------------------
I implemented these algorithms for my CS course. They are far from the worst,
but aren't the fastest either.

The current Quicksort implementation is very slow when sorting an array
with many duplicates. This is not hard to fix, so an update should be coming
somewhat soon.

On my machine, glibc's `qsort` implementation is usually slower than
`QuickSortG` until the array contains millions of elements, where it starts
getting noticeably faster. That's due to many factors about the current `qsort`
implementation, such as:
* Better pivot selection
* Iteration rather than recursion
* It's hybrid: uses insertion sort for small arrays
* It's GNU's implementation. Of course it's going to beat mine.