cmake_minimum_required(VERSION 3.20)

project(MyProject)
enable_language(C)

set(CMAKE_C_STANDARD 17) # 根据你的需求设置C标准
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_BINARY_DIR "${CMAKE_CURRENT_SOURCE_DIR}/build")
file(MAKE_DIRECTORY "${CMAKE_BINARY_DIR}")

# 设置可执行文件输出目录为 build/Exec
set(EXECUTABLE_OUTPUT_PATH "${CMAKE_BINARY_DIR}/Exec")
file(MAKE_DIRECTORY "${EXECUTABLE_OUTPUT_PATH}")

# 遍历当前目录及其子目录下的所有 .c 文件
file(GLOB_RECURSE ALL_SRCS "*.c")
# list(FILTER ALL_SRCS EXCLUDE REGEX ".*")


foreach(SRC_FILE ${ALL_SRCS})
    get_filename_component(EXE_NAME ${SRC_FILE} NAME_WE) # 获取无扩展名的文件名作为可执行文件名

    # 添加针对每个.c文件的可执行文件目标，并指定输出目录
    add_executable(${EXE_NAME} ${SRC_FILE})
    set_target_properties(${EXE_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${EXECUTABLE_OUTPUT_PATH}")

    # 指定包含目录（如果需要的话）
    #target_include_directories(${EXE_NAME} PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/../../Auxiliary_Files")

    # 如果有链接库等依赖，这里添加相应的target_link_libraries命令
endforeach()
