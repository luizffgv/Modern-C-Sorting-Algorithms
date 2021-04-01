#ifdef MEMSWAP_USE_MEMCPY
#include <string.h> // For memcpy
#include <stdlib.h> // For malloc and free
#endif // #ifdef MEMSWAP_USE_MEMCPY

#include <MemSwap/memswap.h>





// Function definitions ----------------------------------------------------- >>

void MemSwap(size_t sz, void *first, void *second)
{
#ifdef MEMSWAP_USE_MEMCPY
    void *aux = malloc(sz);

    memcpy(aux, first, sz);
    memcpy(first, second, sz);
    memcpy(second, aux, sz);

    free(aux);
#else // #ifdef MEMSWAP_USE_MEMCPY
    char aux;

    while (sz--)
    {
        aux                  = ((char *)first)[sz];
        ((char *)first)[sz]  = ((char *)second)[sz];
        ((char *)second)[sz] = aux;
    }
#endif // #else
}
