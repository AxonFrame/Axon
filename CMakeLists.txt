cmake_minimum_required(VERSION 3.16)
project(Axon VERSION 0.3.3 LANGUAGES C CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

# INFO (kitsudaiki): This is a workaround to be able to run valgrind for memory analytics.
#                    See github-issue: https://github.com/llvm/llvm-project/issues/56550
set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -gdwarf-4  -fsanitize=address -fno-omit-frame-pointer")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -gdwarf-4  -fsanitize=address -fno-omit-frame-pointer")

add_subdirectory(src/libraries)
add_subdirectory(src/Axon)
