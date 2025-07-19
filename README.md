# Entity Component System Demo

## 项目简介
基于ECS（实体-组件-系统）架构的Demo。

## 构建指南
### 环境要求
- Windows 10/11
- CMake 3.10 或更高版本
- 支持C++17的编译器（如Visual Studio 2019及以上）
- vcpkg（用于依赖管理，需设置`VCPKG_ROOT`环境变量）

### 依赖项
项目依赖以下库（通过vcpkg安装）：
- **OpenGL**：图形渲染接口（系统自带或通过vcpkg安装）
- **glfw3**：窗口管理库（vcpkg包名：`glfw3`）
- **glm**：数学库（vcpkg包名：`glm`）
- **spdlog**：日志库（vcpkg包名：`spdlog`）

### 构建步骤
1. 安装vcpkg并设置`VCPKG_ROOT`环境变量（参考[vcpkg文档](https://vcpkg.io/)）。
2. 使用vcpkg安装依赖：
   ```powershell
   vcpkg install glfw3:x64-windows glm:x64-windows spdlog:x64-windows
   ```
3. 生成构建文件：
   运行根目录下的`build.bat`脚本（或手动执行以下命令）：
   ```powershell
   cmake -S . -B build -DCMAKE_TOOLCHAIN_FILE="%VCPKG_ROOT%/scripts/buildsystems/vcpkg.cmake"
   ```
4. 编译项目：
   进入`build`目录，使用Visual Studio打开生成的解决方案文件（`MYECS2DGame.sln`），选择`Release`或`Debug`模式编译。

## 注意事项
- 确保CMake版本符合要求（3.10+），否则可能导致配置失败。
- 若需修改依赖版本，可通过vcpkg指定版本号（如`glfw3@3.3.8`）。
- 首次构建可能需要较长时间下载和编译依赖，请耐心等待。