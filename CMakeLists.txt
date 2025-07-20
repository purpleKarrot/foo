# Copyright 2025 Daniel Pfeifer <daniel@pfeifer-mail.de>
# This work is free. You can redistribute it and/or modify it under the
# terms of the Do What The Fuck You Want To Public License, Version 2,
# as published by Sam Hocevar. See http://www.wtfpl.net/ for more details.

cmake_minimum_required(VERSION 3.31)
project(Foo
  VERSION 1.0.0
  LANGUAGES C
  )

find_package(Bar REQUIRED)
find_package(Baz REQUIRED)

add_executable(foo)
add_executable(Foo::foo ALIAS foo)

target_sources(foo
  PUBLIC FILE_SET HEADERS FILES
    foo.h
  PRIVATE
    foo.c
  )

set_target_properties(foo PROPERTIES
  C_VISIBILITY_PRESET hidden
  ENABLE_EXPORTS ON
  )

function(foo_plugin target)
  add_library(${target} MODULE ${ARGN})
  target_link_libraries(${target} PRIVATE Foo::foo)
  set_target_properties(${target} PROPERTIES
    PREFIX ""
    SUFFIX ".foo"
    )
endfunction()

foo_plugin(foobar foobar.c)
target_link_libraries(foobar PRIVATE Bar::bar)

foo_plugin(foobaz foobaz.c)
target_link_libraries(foobaz PRIVATE Baz::baz)

enable_testing()

add_test(NAME foobar COMMAND Foo::foo $<TARGET_FILE:foobar>)
set_tests_properties(foobar PROPERTIES
  PASS_REGULAR_EXPRESSION "hello, world!"
  ENVIRONMENT "PATH=$<TARGET_RUNTIME_DLL_DIRS:foobar>"
  )

add_test(NAME foobaz COMMAND Foo::foo $<TARGET_FILE:foobaz>)
set_tests_properties(foobaz PROPERTIES
  PASS_REGULAR_EXPRESSION "goodbye, world!"
  ENVIRONMENT "PATH=$<TARGET_RUNTIME_DLL_DIRS:foobaz>"
  )
