# opt.h

![CI](https://github.com/rsore/opt/actions/workflows/test.yml/badge.svg)

A minimal single‑header optional value library for C (and C++).

## Features

- Single file, drop‑in (no dependencies).
- Provides `Opt(T)` for any type, including custom structs.
- `opt_get_or()` for fallback values.
- Works in both C and C++ (tested across multiple standards).
- Customizable assertions (`OPT_ASSERT`), defaults to libc `assert()`.

## Example

```c
#include "opt.h"
#include <stdio.h>

OPT_DEFINE(int); // Define optional int type

int main(void) {
    // Initialize empty optional
    Opt(int) value = OPT_INIT;

    // Set a value
    opt_set(&value, 42);

    // Alternatively: Opt(int) value = OPT_MAKE(42);

    // Check if it has a value
    if (opt_has_value(&value)) {
        printf("Value is %d\n", opt_get(&value));
    }

    // Clear value
    opt_clear(&value);

    // Get value or fallback
    printf("Value or fallback: %d\n", opt_get_or(&value, -1));

    return 0;
}
```

**Note:** OPT_DEFINE cannot be used with types containing spaces (e.g., unsigned int, int *). Use typedef to create an alias first:
```c
OPT_DEFINE(unsigned int); // Not allowed
OPT_DEFINE(int *);        // Not allowed

typedef unsigned int uint;
OPT_DEFINE(uint)           // Allowed

typedef int* int_ptr;
OPT_DEFINE(int_ptr)   // Allowed
```

## Tested platforms and compilers

### Linux
- **Compilers:** GCC 14, Clang 20
- **C standards:** C99, C11, C17, C23
- **C++ standards:** C++11, C++14, C++17, C++20, C++23, C++26
- **Flags:** `-Wall -Wextra -Werror -pedantic-errors`

### Windows
- **Compiler:** MSVC 2022
- **C standards:** C11, C17
- **C++ standards:** C++14, C++17, C++20, C++latest
- **Flags:** `/W4 /WX`

### macOS
- **Compiler:** Apple Clang (latest)
- **C standards:** C99, C11, C17, C2x
- **C++ standards:** C++11, C++14, C++17, C++20, C++2b
- **Flags:** `-Wall -Wextra -Werror -pedantic-errors`

## License

`sp.h` is licensed under the 3-Clause BSD license.
See the `LICENSE` file for details.
