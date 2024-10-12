cmake_minimum_required(VERSION 3.5)
project(gem LANGUAGES C CXX)
set(CMAKE_C_STANDARD 99)

include_directories(include)
include_directories(raylib/include)

set(RAYLIB_DIR "${CMAKE_SOURCE_DIR}/lib")

find_package(PkgConfig REQUIRED)

include_directories(${FFMPEG_INCLUDE_DIRS})
include_directories(/usr/include/x86_64-linux-gnu)

find_library(FFMPEG_AVCODEC avcodec HINTS "/usr/lib/x86_64-linux-gnu")
find_library(FFMPEG_AVFORMAT avformat HINTS "/usr/lib/x86_64-linux-gnu")
find_library(FFMPEG_AVUTIL avutil HINTS "/usr/lib/x86_64-linux-gnu")
find_library(FFMPEG_SWSCALE swscale HINTS "/usr/lib/x86_64-linux-gnu")

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

add_executable(gem ${SOURCES})

target_link_libraries(gem PRIVATE ${RAYLIB} ${FFMPEG_AVCODEC} ${FFMPEG_AVFORMAT} ${FFMPEG_AVUTIL} ${FFMPEG_SWSCALE} m pthread dl GL X11)
add_library(plug INTERFACE)

target_link_libraries(plug INTERFACE ${RAYLIB})
set_target_properties(gem PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build)
set_target_properties(plug PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build)

# enable_testing()
# add_executable(tests tests.c)

target_link_libraries(tests PRIVATE ${RAYLIB} ${FFMPEG_AVCODEC} ${FFMPEG_AVFORMAT} ${FFMPEG_AVUTIL} ${FFMPEG_SWSCALE})
add_test(NAME UnitTests COMMAND tests)
install(TARGETS gem RUNTIME DESTINATION bin)

