# Set the minimum version of CMake that can be used
# To find the cmake version run
# $ cmake --version
cmake_minimum_required(VERSION 3.16)

# Set the project name
project (EasyBreakout)

file(GLOB "${PROJECT_NAME}_SOURCES" ${CMAKE_SOURCE_DIR}/src/*.cpp)

# Initialize CXXFLAGS
set(CMAKE_CXX_FLAGS                "-Wall -std=c++17")
set(CMAKE_CXX_FLAGS_DEBUG          "-O0 -g")
set(CMAKE_CXX_FLAGS_MINSIZEREL     "-Os -DNDEBUG")
set(CMAKE_CXX_FLAGS_RELEASE        "-O4 -DNDEBUG")
set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "-O2 -g")

# Check C++17 activation.
if ("${CMAKE_CXX_COMPILER_ID}" MATCHES "GNU")
    execute_process(COMMAND ${CMAKE_CXX_COMPILER} -dumpversion OUTPUT_VARIABLE GCC_VERSION)   
    if (NOT (GCC_VERSION VERSION_GREATER 7 OR GCC_VERSION VERSION_EQUAL 7))
        message(FATAL_ERROR "${PROJECT_NAME} requires g++ 7.0.0 or greater.")
    endif ()
elseif ("${CMAKE_CXX_COMPILER_ID}" MATCHES "Clang")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++")
else ()
    message(FATAL_ERROR "Your C++ compiler does not support C++17.")
endif ()

add_executable(${PROJECT_NAME} ${${PROJECT_NAME}_SOURCES})

# Add raylib library
target_link_libraries(${PROJECT_NAME}
    /usr/local/lib/libraylib.so
)

install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION ${CMAKE_SOURCE_DIR}/bin)