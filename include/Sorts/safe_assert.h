#ifndef SORTS_SAFE_ASSERT_H_INCLUDED
#define SORTS_SAFE_ASSERT_H_INCLUDED

#include <assert.h>
#ifndef static_assert
#ifndef SORTS_DEFINE_STATIC_ASSERT
#error This compiler does not define static_assert in <assert.h>. Define SORTS_DEFINE_STATIC_ASSERT as a workaround.
#else
#define static_assert _Static_assert
#endif // #ifndef SORTS_DEFINE_STATIC_ASSERT
#endif // #ifndef static_assert

#endif // #ifndef SORTS_SAFE_ASSERT_H_INCLUDED