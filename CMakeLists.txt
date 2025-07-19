cmake_minimum_required(VERSION 3.10)
project(MYECS2DGame)

# 设置C++标准
set(CMAKE_CXX_STANDARD 17)

message(STATUS "CMAKE_TOOLCHAIN_FILE: ${CMAKE_TOOLCHAIN_FILE}")
# 查找依赖
find_package(OpenGL REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)
find_package(spdlog CONFIG REQUIRED)

# 输出包含的目录
message(STATUS "Include dirs: ${CMAKE_SOURCE_DIR}/Src")
include_directories(${CMAKE_SOURCE_DIR}/Src)
include_directories(${CMAKE_SOURCE_DIR}/Src/glad/include)
include_directories(${OPENGL_INCLUDE_DIRS} ${GLM_INCLUDE_DIRS} ${GLFW_INCLUDE_DIRS})

# 查找所有源文件
file(GLOB_RECURSE MYECS_SOURCES "${CMAKE_SOURCE_DIR}/Src/**/*.cpp")
file(GLOB_RECURSE MYECS_C_SOURCES "${CMAKE_SOURCE_DIR}/Src/**/*.c")
file(GLOB_RECURSE MYECS_CPP_FILES "${CMAKE_SOURCE_DIR}/Src/*.cpp")

# 输出找到的源文件
message(STATUS "MYECS sources: ${MYECS_SOURCES}")
message(STATUS "MYECS C sources: ${MYECS_C_SOURCES}")

# 添加可执行文件
add_executable(MYECS2DGame ${MYECS_SOURCES} ${MYECS_C_SOURCES} ${MYECS_CPP_FILES})

# 链接库
target_link_libraries(MYECS2DGame ${OPENGL_LIBRARIES} glfw glm::glm spdlog::spdlog)

# 定义预处理宏
target_compile_definitions(MYECS2DGame PRIVATE ECS_SOURCE_DIR="${CMAKE_SOURCE_DIR}/Src")