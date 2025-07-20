# Copyright 2025 Daniel Pfeifer <daniel@pfeifer-mail.de>
# This work is free. You can redistribute it and/or modify it under the
# terms of the Do What The Fuck You Want To Public License, Version 2,
# as published by Sam Hocevar. See http://www.wtfpl.net/ for more details.

cmake_minimum_required(VERSION 3.31)

include(FetchContent)

FetchContent_Declare(Bar
  GIT_REPOSITORY https://github.com/purpleKarrot/bar.git
  GIT_TAG        de8407535dd28d33f9683e9bc205d58e25a8ddbb
  EXCLUDE_FROM_ALL
  SYSTEM
  )

FetchContent_Declare(Baz
  GIT_REPOSITORY https://github.com/purpleKarrot/baz.git
  GIT_TAG        766ab38eba108b60789d3be92c6d2537ff259999
  EXCLUDE_FROM_ALL
  SYSTEM
  )

FetchContent_Declare(Qux
  GIT_REPOSITORY https://github.com/purpleKarrot/qux.git
  GIT_TAG        5bdf2088b26735b2ad5fde66fb90548b53780ac6
  EXCLUDE_FROM_ALL
  SYSTEM
  )

macro(foo_provide_dependency method dep_name)
  if("${dep_name}" MATCHES "^(Bar|Baz|Qux)$")
    FetchContent_MakeAvailable(${dep_name})
    set(${dep_name}_FOUND TRUE)
  endif()
endmacro()

cmake_language(SET_DEPENDENCY_PROVIDER foo_provide_dependency
  SUPPORTED_METHODS
    FIND_PACKAGE
    FETCHCONTENT_MAKEAVAILABLE_SERIAL
  )
