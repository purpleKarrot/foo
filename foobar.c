// Copyright 2025 Daniel Pfeifer <daniel@pfeifer-mail.de>
// This work is free. You can redistribute it and/or modify it under the
// terms of the Do What The Fuck You Want To Public License, Version 2,
// as published by Sam Hocevar. See http://www.wtfpl.net/ for more details.

#include "foo.h"
#include <bar.h>

FOO_API void plugin(char const* x)
{
  char* str = bar(x);
  foo(str);
  bar_free(str);
}
