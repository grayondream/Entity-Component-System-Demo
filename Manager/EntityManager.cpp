#include "Manager/EntityManager.hpp"
#include <cassert>
#include <exception>
#include  <stdexcept>

EntityManager::EntityManager() : currentEntity(0) {}

Entity EntityManager::createEntity() {
    if (!availableEntities.empty()) {
        Entity entity = availableEntities.front();
        availableEntities.pop();
        return entity;
    }

    if (currentEntity >= kMaxEntities) {
        throw std::runtime_error("Maximum number of entities reached.");
    }
    return currentEntity++;
}

void EntityManager::destroyEntity(Entity entity) {
    if (entity >= currentEntity) {
        throw std::runtime_error("Entity does not exist.");
    }
    signatures[entity].reset(); // 清除该实体的签名
    availableEntities.push(entity); // 将实体加入可用池
}

void EntityManager::setSignature(Entity entity, Signature signature) {
    if (entity >= currentEntity) {
        throw std::runtime_error("Entity does not exist.");
    }

    signatures[entity] = signature;
}


Signature EntityManager::getSignature(Entity entity) const {
    if (entity >= currentEntity) {
        throw std::runtime_error("Entity does not exist.");
    }
    
    return signatures[entity];
}