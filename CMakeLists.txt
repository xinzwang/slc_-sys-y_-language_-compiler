cmake_minimum_required(VERSION 3.10.2)

if(CMAKE_HOST_WIN32)
    set(WINDOWS 1)
elseif(CMAKE_HOST_APPLE)
    set(MACOS 1)
elseif(CMAKE_HOST_UNIX)
    set(LINUX 1)
endif()

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/build)

set(CMAKE_BUILD_TYPE "Debug")
set(CMAKE_CXX_FLAGS "$ENV{CXXFLAGS} -O0 -Wall -g2 -ggdb")
set(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O3 -Wall")

if(WINDOWS)
    include_directories(src/win_dep)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${PROJECT_SOURCE_DIR}/build)  
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${PROJECT_SOURCE_DIR}/build)  
endif()

include_directories(src/ast)
include_directories(src/front)
# include_directories(src/semantic)
include_directories(src/ir)
include_directories(src/codegen)

add_subdirectory(src/ast)
add_subdirectory(src/front)
# add_subdirectory(src/semantic)
add_subdirectory(src/ir)
add_subdirectory(src/codegen)


add_executable(compiler src/main.cpp)

target_link_libraries(
    compiler
    Front
    Ast
    Ir
	CodeGen
)