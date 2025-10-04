# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles/qt-led_autogen.dir/AutogenUsed.txt"
  "CMakeFiles/qt-led_autogen.dir/ParseCache.txt"
  "qt-led_autogen"
  )
endif()
