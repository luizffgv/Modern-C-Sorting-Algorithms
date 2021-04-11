#include <stdio.h>
#include <stddef.h>

#include <Ordering/ordering.h>
#include <Sorts/quick_sort.h>





Ordering CompareInts(void *first, void *second)
{
    if (*(int *)first > *(int *)second)
        return ordering_greater;
    else if (*(int *)first < *(int *)second)
        return ordering_less;
    return ordering_equal;
}

COMPARER_ARITHMETIC_FUNC_DEF(CompareFloats, float)





int main(void)
{
    //
    // Sorting with QuickSortG
    //
    int arr[] = {5, 8, 3, 2, 9, 1, 3};
    QuickSortG(arr, arr + sizeof(arr) / sizeof(*arr));
    for (size_t i = 0; i < sizeof(arr) / sizeof(*arr); ++i)
        printf("%d ", arr[i]);
    putchar('\n');

    //
    // Doing the same but using QuickSort
    //
    int arr1[] = {5, 8, 3, 2, 9, 1, 3};
    QuickSort(
        // Size of the type
        sizeof(*arr1),
        // Range containing addresses of first and one-past-last element
        (Range){arr1, arr1 + sizeof(arr1) / sizeof(*arr1)},
        // Callback function
        CompareInts
    );
    for (size_t i = 0; i < sizeof(arr1) / sizeof(*arr1); ++i)
        printf("%d ", arr1[i]);
    putchar('\n');

    //
    // Now sorting a float array
    //
    float arrf[] = {5, 8, 3, 2, 9, 1, 3};
    QuickSort(
        sizeof(*arrf),
        (Range){arrf, arrf + sizeof(arrf) / sizeof(*arrf)},
        CompareFloats
    );
    for (size_t i = 0; i < sizeof(arrf) / sizeof(*arrf); ++i)
        printf("%.f ", arrf[i]);

    return 0;
}
