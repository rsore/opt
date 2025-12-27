/**
 *    __  ___ _____
 *   /__\| _,\_   _|
 *  | \/ | v_/ | |
 *   \__/|_|   |_|
 *
 *  opt.h — v2.1.0
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
 *  LICENSE:
 *   `opt.h` is licensed under the 3-Clause BSD license. Full license text is
 *   at the end of this file.
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


/**
 * BSD-3-CLAUSE LICENSE
 *
 * Copyright 2025 rsore
 *
 * Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its contributors may be used to endorse or promote products derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS “AS IS” AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
