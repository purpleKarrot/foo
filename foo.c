// Copyright 2025 Daniel Pfeifer <daniel@pfeifer-mail.de>
// This work is free. You can redistribute it and/or modify it under the
// terms of the Do What The Fuck You Want To Public License, Version 2,
// as published by Sam Hocevar. See http://www.wtfpl.net/ for more details.

#include "foo.h"

#include <stdio.h>

#ifdef _WIN32
#  include <windows.h>
#  define dlopen(lib, flags) LoadLibraryA(lib)
#  define dlsym(handle, name) GetProcAddress((HMODULE)(handle), (name))
#  define dlclose(handle) FreeLibrary((HMODULE)(handle))
#else
#  include <dlfcn.h>
#endif

void foo(char const* str) {
  printf("%s\n", str);
}

typedef void (*plugin_type)(char const*);

int main(int ac, char* av[]) {
  if (ac != 2) {
    printf("wrong number of arguments\n");
    return -1;
  }

  void* handle = dlopen(av[1], RTLD_LAZY);
  if (handle == NULL) {
    printf("dlopen %s failed\n", av[1]);
    return -1;
  }

  plugin_type const plugin = (plugin_type)dlsym(handle, "plugin");
  if (plugin == NULL) {
    dlclose(handle);
    printf("dlsym failed\n");
    return -1;
  }

  plugin("world");
  dlclose(handle);
}
