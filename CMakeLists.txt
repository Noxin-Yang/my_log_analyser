# CMakeList.txt: my_log_analyser 的 CMake 项目，在此处包括源代码并定义
# 项目特定的逻辑。
#
cmake_minimum_required (VERSION 3.10)

# 如果支持，请为 MSVC 编译器启用热重载。
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project (my_log_analyser VERSION 0.1.0 LANGUAGES C CXX)
SET(CMAKE_CXX_STANDARD 23)

if(MSVC)
add_compile_options(/utf-8)
endif()

message(STATUS "CMake 版本 = ${CMAKE_VERSION}")
message(STATUS "MSVC_VERSION = ${MSVC_VERSION}")

add_subdirectory(bin)
add_subdirectory(lib/analysis)
add_subdirectory(lib/core)
add_subdirectory(lib)
# TODO: 如有需要，请添加测试并安装目标。
