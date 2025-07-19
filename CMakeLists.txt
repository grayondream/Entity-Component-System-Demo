cmake_minimum_required(VERSION 3.10)
project(MYECS2DGame)

# 设置C++标准
set(CMAKE_CXX_STANDARD 17)

set(VCPKG_ROOT ENV${VCPKG_ROOT} CACHE PATH "Path to vcpkg root directory")
# 添加vcpkg路径
set(CMAKE_TOOLCHAIN_FILE "${VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake" CACHE STRING "Vcpkg toolchain file")

# 查找依赖
find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)
find_package(glm CONFIG REQUIRED)
find_package(spdlog CONFIG REQUIRED)
    
message(STATUS " include dirs: ${CMAKE_SOURCE_DIR}/MYECS")
include_directories(${CMAKE_SOURCE_DIR}/MYECS)
include_directories(${CMAKE_SOURCE_DIR}/MYECS/glad/include)
include_directories(${OPENGL_INCLUDE_DIRS} ${GLM_INCLUDE_DIRS} ${GLFW_INCLUDE_DIRS})
file(GLOB_RECURSE MYECS_SOURCES "${CMAKE_SOURCE_DIR}/MYECS/**/*.cpp")
file(GLOB_RECURSE MYECS_C_SOURCES "${CMAKE_SOURCE_DIR}/MYECS/**/*.c")
file(GLOB_RECURSE MYECS_CPP_FILES "${CMAKE_SOURCE_DIR}/MYECS/*.cpp")
message(STATUS "MYECS sources: ${MYECS_SOURCES}")
message(STATUS "MYECS sources: ${MYECS_C_SOURCES}")

# 添加C源文件
# 添加源码
add_executable(MYECS2DGame ${MYECS_SOURCES} ${MYECS_C_SOURCES} ${MYECS_CPP_FILES})
target_link_libraries(MYECS2DGame ${OPENGL_LIBRARIES} glfw)
target_link_libraries(MYECS2DGame glm::glm)
target_link_libraries(MYECS2DGame spdlog::spdlog)
target_compile_definitions(MYECS2DGame PRIVATE ECS_SOURCE_DIR="${CMAKE_SOURCE_DIR}/MYECS")