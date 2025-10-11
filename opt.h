/**
 *    __  ___ _____
 *   /__\| _,\_   _|
 *  | \/ | v_/ | |
 *   \__/|_|   |_|
 *
 *  opt.h — v1.0.1
 *
 *
 *  This file is placed in the public domain.
 *  See end of file for license details.
 *
 *
 *  Example usage:
 *
 *      #include "opt.h"
 *      #include <stdio.h>
 *
 *      OPT_DEFINE(int);
 *
 *      int main(void) {
 *          Opt(int) value = OPT_INIT;
 *
 *          opt_set(&value, 42);
 *
 *          if (opt_has_value(&value)) {
 *              printf("Value is %d\n", opt_get(&value));
 *          }
 *
 *          printf("Value or fallback: %d\n", opt_get_or(&value, -1));
 *
 *          opt_clear(&value);
 *      }
 *
 *  Customization:
 *   - Define OPT_ASSERT(cond) before including header to set the assert method for opt.
 *     The default is libc assert.
 *   - Define OPT_AUTODEFINE_PRIMITIVES before including header to have opt.h automatically
 *     generate optional types for most primitives
 *
 **/

#ifndef OPT_H_
#define OPT_H_

#ifndef OPT_ASSERT
#include <assert.h>
#define OPT_ASSERT(cond) assert(cond)
#endif

#define Opt(underlying_type) Opt__internal__##underlying_type

#define OPT_DEFINE(underlying_type)             \
    typedef struct {                            \
        underlying_type value;                  \
        int             has_value;              \
    } Opt(underlying_type)

#ifndef __cplusplus
#define OPT_INIT {0}
#else
#define OPT_INIT {}
#endif

#define OPT_MAKE(...) {__VA_ARGS__, 1}

#define opt_has_value(opt) ((opt)->has_value)

#define opt_set(opt, val)                       \
    do {                                        \
        (opt)->value = (val);                   \
        (opt)->has_value = 1;                   \
    } while (0)

#define opt_get(opt)        (OPT_ASSERT((opt)->has_value), (opt)->value)
#define opt_get_ptr(opt)    (OPT_ASSERT((opt)->has_value), &((opt)->value))
#define opt_get_or(opt, fallback) ((opt)->has_value ? (opt)->value : (fallback))

#define opt_clear(var)                          \
    do {                                        \
        (var)->has_value = 0;                   \
    } while (0)

#if defined(OPT_AUTODEFINE_PRIMITIVES) && !defined(OPT_PRIMITIVES_DEFINED_)
#define OPT_PRIMITIVES_DEFINED_
OPT_DEFINE(int);
OPT_DEFINE(float);
OPT_DEFINE(double);
OPT_DEFINE(char);
OPT_DEFINE(short);
OPT_DEFINE(long);
#endif

#endif // OPT_H_



/*
  LICENSE

  This is free and unencumbered software released into the public domain.

  Anyone is free to copy, modify, publish, use, compile, sell, or
  distribute this software, either in source code form or as a compiled
  binary, for any purpose, commercial or non-commercial, and by any
  means.

  In jurisdictions that recognize copyright laws, the author or authors
  of this software dedicate any and all copyright interest in the
  software to the public domain. We make this dedication for the benefit
  of the public at large and to the detriment of our heirs and
  successors. We intend this dedication to be an overt act of
  relinquishment in perpetuity of all present and future rights to this
  software under copyright law.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
  EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
  MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
  IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
  OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
  ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
  OTHER DEALINGS IN THE SOFTWARE.
*/
