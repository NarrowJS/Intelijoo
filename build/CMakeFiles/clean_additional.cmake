# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\IntelliJoo_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\IntelliJoo_autogen.dir\\ParseCache.txt"
  "IntelliJoo_autogen"
  )
endif()
