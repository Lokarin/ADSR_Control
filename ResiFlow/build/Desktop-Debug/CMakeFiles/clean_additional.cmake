# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles/ResiFlow_autogen.dir/AutogenUsed.txt"
  "CMakeFiles/ResiFlow_autogen.dir/ParseCache.txt"
  "ResiFlow_autogen"
  )
endif()
