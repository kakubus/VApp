# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles/appuntitled2_autogen.dir/AutogenUsed.txt"
  "CMakeFiles/appuntitled2_autogen.dir/ParseCache.txt"
  "appuntitled2_autogen"
  )
endif()
