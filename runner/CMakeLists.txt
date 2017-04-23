macro(add_exe executable)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

add_executable(${executable} main.cpp)

set_property(TARGET ${executable} PROPERTY FOLDER ${cat})

set(exe ${executable})

endmacro(add_exe)


macro(add_test filename)

add_executable(${exe}_${filename} ${PROJECT_SOURCE_DIR}/runner/run.cpp)

set_property(TARGET ${exe}_${filename} PROPERTY FOLDER ${cat})

set_target_properties(${exe}_${filename} PROPERTIES COMPILE_DEFINITIONS FILENAME=\"${CMAKE_CURRENT_SOURCE_DIR}/${filename}\")

endmacro(add_test)
