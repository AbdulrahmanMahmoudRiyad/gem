# Minimum version of CMake
cmake_minimum_required(VERSION 3.5)

# Project name and version
project(gem LANGUAGES C CXX)

# Set the C standard
set(CMAKE_C_STANDARD 99)

# Directories for header files
include_directories(include)
include_directories(raylib/include)

# Set up paths to Raylib and FFmpeg libraries
set(RAYLIB_DIR "${CMAKE_SOURCE_DIR}/lib")

# Use pkg-config to find FFmpeg include and library paths
find_package(PkgConfig REQUIRED)

# Include the FFmpeg include directories
include_directories(${FFMPEG_INCLUDE_DIRS})

# Include directories for FFmpeg
include_directories(/usr/include/x86_64-linux-gnu)

# Libraries for FFmpeg (manually set if pkg-config is not finding them)
find_library(FFMPEG_AVCODEC avcodec HINTS "/usr/lib/x86_64-linux-gnu")
find_library(FFMPEG_AVFORMAT avformat HINTS "/usr/lib/x86_64-linux-gnu")
find_library(FFMPEG_AVUTIL avutil HINTS "/usr/lib/x86_64-linux-gnu")
find_library(FFMPEG_SWSCALE swscale HINTS "/usr/lib/x86_64-linux-gnu")

# Add source files for the main executable
set(SOURCES
    bezier.c
    ffmpeg_linux.c
    nob.c
    gem.c
    squares.c
    tasks.c
    tm.c
    probe.cpp
)

# Create the main executable
add_executable(gem ${SOURCES})

# Link the libraries to the executable
target_link_libraries(gem PRIVATE ${RAYLIB} ${FFMPEG_AVCODEC} ${FFMPEG_AVFORMAT} ${FFMPEG_AVUTIL} ${FFMPEG_SWSCALE} m pthread dl GL X11)

# For dynamic library support (plugins)
# Use an interface-only library since no source file is needed for the plugin
add_library(plug INTERFACE)

# Link to Raylib for the interface library
target_link_libraries(plug INTERFACE ${RAYLIB})

# Set the output directory for the executable and shared libraries
set_target_properties(gem PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build)
set_target_properties(plug PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build)

# Include tests
enable_testing()

# Add test executable for unit tests
add_executable(tests tests.c)

# Link the testing executable with Raylib and FFmpeg libraries
target_link_libraries(tests PRIVATE ${RAYLIB} ${FFMPEG_AVCODEC} ${FFMPEG_AVFORMAT} ${FFMPEG_AVUTIL} ${FFMPEG_SWSCALE})

# Define a test
add_test(NAME UnitTests COMMAND tests)

# Installation rules (optional)
install(TARGETS gem RUNTIME DESTINATION bin)

