#include "System/BackgroundSystem.hpp"
#include "Core/Log.hpp"
#include "Manager/WorldManager.hpp"
#include "Component/Transform.hpp"
#include "Component/Velocity.hpp"

extern std::unique_ptr<WorldManager> g_worldManager;

void BackgroundSystem::init() {
    LOGI("BackgroundSystem initialized");
}

void BackgroundSystem::tick(float dt) {
    for(const auto& entity : _entities) {
        try {
            // Example: Get a component and log its data
            auto& transform = g_worldManager->getComponent<Transform>(entity);
            auto& velocity = g_worldManager->getComponent<Velocity>(entity);

            // Update position based on velocity
            transform.position += velocity.speed * dt;
            if(transform.position.y < -4.0f) {
                // Reset position if it goes below a certain threshold
                transform.position.y = 4.0f;
            }
            //LOGI("Entity {} moved to position [{}, {}, {}]", (int)entity, transform.position.x, transform.position.y, transform.position.z);
        } catch (const std::exception& e) {
            LOGE("Error processing entity {}: {}", (int)entity, e.what());
        }
    }
}

void BackgroundSystem::destroy() {
    LOGI("BackgroundSystem destroyed");
}