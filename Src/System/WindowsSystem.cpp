#include "System/WindowsSystem.hpp"
#include "Core/Log.hpp"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Manager/WorldManager.hpp"
#include "Component/KeyBoard.hpp"

extern std::unique_ptr<WorldManager> g_worldManager;
WindowsSystem::~WindowsSystem() {
    destroy();
    LOGI("WindowsSystem destroyed");
}

void WindowsSystem::initGLFW() {
    if (!glfwInit()) {
        LOGE("Failed to initialize GLFW");
        return;
    }
    
    // Set GLFW error callback
    glfwSetErrorCallback([](int error, const char* description) {
        LOGE("GLFW Error {}: {}", error, description);
    });
}

WindowsSystem::WindowsSystem(const WindowsAttr& attr) : _attr(attr) {
    initGLFW();
    createWindow();
}

WindowsSystem::WindowsSystem() {
    initGLFW();
    createWindow();
}

void WindowsSystem::createWindow() {
    _window = glfwCreateWindow(_attr.width, _attr.height, _attr.title.c_str(), nullptr, nullptr);
    if (!_window) {
        LOGE("Failed to create GLFW window");
        glfwTerminate();
        return;
    }

    glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
	glfwWindowHint(GLFW_FOCUSED, GLFW_TRUE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Create OpenGL Context
	glfwMakeContextCurrent(_window);
	gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
	glfwSwapInterval(2);

	// Configure OpenGL
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glEnable(GL_DEPTH_TEST);
    
    // Set input mode
    glfwSetInputMode(_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    
    // Set the window's user pointer to this instance
    glfwSetWindowUserPointer(_window, this);
}

void WindowsSystem::init() {
    LOGI("WindowsSystem initialized with title: {}", _attr.title);
    if (!_window) {
        LOGE("Window not created, cannot initialize WindowsSystem");
        return;
    }	
}

void WindowsSystem::tick(float dt) {
    for(const auto& entity : _entities) {
        try {
            auto & keyboard = g_worldManager->getComponent<KeyBoard>(entity);
            if(keyboard.keyCode == GLFW_KEY_ESCAPE) {
                LOGI("Escape key pressed, closing window");
                glfwSetWindowShouldClose(_window, true);
            }

        } catch (const std::exception& e) {
            LOGE("Error processing entity {}: {}", (int)entity, e.what());
        }
    }

    swpaBuffer();
    glfwPollEvents();
}

void WindowsSystem::destroy() {
    glfwDestroyWindow(_window);
    glfwTerminate();
}

void WindowsSystem::swpaBuffer() {
    if (_window) {
        glfwSwapBuffers(_window);
    } else {
        LOGE("Cannot swap buffers, window is not initialized");
    }
}

bool WindowsSystem::isRunning() const {
    return _window && !glfwWindowShouldClose(_window);
}
