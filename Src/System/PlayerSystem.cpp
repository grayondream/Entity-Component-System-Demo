#include "System/PlayerSystem.hpp"
#include "Core/Log.hpp"
#include "Manager/WorldManager.hpp"
#include "Component/Player.hpp"
#include "Component/Transform.hpp"
#include "Component/KeyBoard.hpp"
#include <glfw/glfw3.h>

extern std::unique_ptr<WorldManager> g_worldManager;

void PlayerSystem::init() {
    
}

void PlayerSystem::tick(float dt) {
    for(const auto& entity : _entities) {
        try {
            auto& player = g_worldManager->getComponent<Player>(entity);
            auto& transform = g_worldManager->getComponent<Transform>(entity);
            auto& keyboard = g_worldManager->getComponent<KeyBoard>(entity);
            if(keyboard.keyCode != 0){
                if (keyboard.keyCode == GLFW_KEY_W) {
                    transform.position.y += 0.1f; // Move forward
                } else if (keyboard.keyCode == GLFW_KEY_S) {
                    transform.position.y -= 0.1f; // Move backward
                } else if (keyboard.keyCode == GLFW_KEY_A) {
                    transform.position.x -= 0.1f; // Move left
                } else if (keyboard.keyCode == GLFW_KEY_D) {
                    transform.position.x += 0.1f; // Move right
                }

                LOGI("Player {} moved to position[{}, {}, {}]", (int)entity, transform.position.x, transform.position.y, transform.position.z);
                keyboard.keyCode = 0; // Reset key code after processing
            }
            
            
            //LOGI("Player {} moved to position[{}, {}, {}]", entity, transform.position.x, transform.position.y, transform.position.z);
        } catch (const std::exception& e) {
            LOGE("Error processing entity {}: {}", (int)entity, e.what());
        }
    }
}

void PlayerSystem::destroy() {
    
}