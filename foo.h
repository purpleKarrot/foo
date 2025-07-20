// Copyright 2025 Daniel Pfeifer <daniel@pfeifer-mail.de>
// This work is free. You can redistribute it and/or modify it under the
// terms of the Do What The Fuck You Want To Public License, Version 2,
// as published by Sam Hocevar. See http://www.wtfpl.net/ for more details.

#pragma once

#if defined(__ELF__) || defined(__MACH__) || defined(__WASM__)
#  define FOO_API __attribute__((visibility("default")))
#else  // assume PE/COFF
#  define FOO_API __declspec(dllexport)
#endif

FOO_API void foo(char const* str);
