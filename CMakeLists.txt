# To build
# For Linux version: cmake -B build -DCMAKE_BUILD_TYPE=MINSIZEREL
# For Windows version: cmake -B build -DCMAKE_TOOLCHAIN_FILE=./mingw64.cmake -DCMAKE_BUILD_TYPE=MINSIZEREL
# cmake --build build
#
# To install
# cmake --install ./build --prefix .
#
# Set the minimum version of CMake that can be used
# To find the cmake version run
# $ cmake --version
cmake_minimum_required(VERSION 3.16)

# Set the project name
project (EasyBreakout VERSION 0.1.1)

# Generate compile_commands.json
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Dependencies
set(RAYLIB_VERSION 4.5.0)
find_package(raylib ${RAYLIB_VERSION} QUIET)
if (NOT raylib_FOUND) # If there's none, fetch and build raylib
  include(FetchContent)
  FetchContent_Declare(
    raylib
    DOWNLOAD_EXTRACT_TIMESTAMP OFF
    URL https://github.com/raysan5/raylib/archive/refs/tags/${RAYLIB_VERSION}.tar.gz
  )
  FetchContent_GetProperties(raylib)
  if (NOT raylib_POPULATED) # Have we downloaded raylib yet?
    set(FETCHCONTENT_QUIET NO)
    FetchContent_Populate(raylib)
    set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE) # don't build the supplied examples
    add_subdirectory(${raylib_SOURCE_DIR} ${raylib_BINARY_DIR})
  endif()
endif()

# EasyBreakout project
file(GLOB "${PROJECT_NAME}_SOURCES" "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")

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

# Define executable output file name with application version 
set(OUTPUT_FILE_NAME "${PROJECT_NAME}-${CMAKE_PROJECT_VERSION}-${CMAKE_SYSTEM}")
set_target_properties(${PROJECT_NAME} PROPERTIES  OUTPUT_NAME ${OUTPUT_FILE_NAME})

if(CMAKE_SYSTEM MATCHES Windows)
    message(STATUS "Target system is Windows")
    
    # Add resource file
    target_sources(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src/${PROJECT_NAME}.rc.data)

    # Update executable output file name for Windows
    set(OUTPUT_FILE_NAME "${OUTPUT_FILE_NAME}.exe") 
endif()

# Add raylib library
target_link_libraries(${PROJECT_NAME} raylib)     

install(TARGETS ${PROJECT_NAME} CONFIGURATIONS  DEBUG DESTINATION bin/Debug)
install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/src/resources CONFIGURATIONS  DEBUG DESTINATION bin/Debug)
install(TARGETS ${PROJECT_NAME} CONFIGURATIONS  { MINSIZEREL | RELEASE | RELWITHDEBINFO } DESTINATION bin/Release)
install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/src/resources CONFIGURATIONS  { MINSIZEREL | RELEASE | RELWITHDEBINFO } DESTINATION bin/Release)