#include "System/KeyBoardSystem.hpp"
#include "Core/Log.hpp"
#include "Manager/WorldManager.hpp"
#include "Component/KeyBoard.hpp"
#include "WindowsSystem.hpp"
extern std::unique_ptr<WorldManager> g_worldManager;

void KeyboardSystem::init() {
    LOGI("KeyboardSystem initialized");
}

KeyType GetPressedKeyCode(GLFWwindow* _window) {
    if(glfwGetKey(_window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        return GLFW_KEY_ESCAPE;
    }else if(glfwGetKey(_window, GLFW_KEY_W) == GLFW_PRESS) {
        return GLFW_KEY_W;
    } else if(glfwGetKey(_window, GLFW_KEY_A) == GLFW_PRESS) {
        return GLFW_KEY_A;
    } else if(glfwGetKey(_window, GLFW_KEY_S) == GLFW_PRESS) {
        return GLFW_KEY_S;
    } else if(glfwGetKey(_window, GLFW_KEY_D) == GLFW_PRESS) {
        return GLFW_KEY_D;
    }

    return 0; // No key pressed
}

void KeyboardSystem::tick(float dt) {
    for(const auto& entity : _entities) {
        try {
            auto& keyboard = g_worldManager->getComponent<KeyBoard>(entity);
            // Here you can add logic to handle keyboard input
            // For example, you might check if a key is pressed and update the keyCode accordingly
            keyboard.keyCode = GetPressedKeyCode(_window);
            if(keyboard.keyCode != 0) {
                LOGI("Entity {} pressed key: {}", (int)entity, keyboard.keyCode);
            }
            
        } catch (const std::exception& e) {
            LOGE("Error processing entity {}: {}", (int)entity, e.what());
        }
    }
}

void KeyboardSystem::destroy() {
    LOGI("KeyboardSystem destroyed");
}

