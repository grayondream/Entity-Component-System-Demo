#pragma once


#include <cstdint>
#include <bitset>
#include <queue>
#include "Core/Types.hpp"
#include <array>

class EntityManager {
public:
    EntityManager();

    Entity createEntity();
    void destroyEntity(Entity entity);
    void setSignature(Entity entity, Signature signature);
    Signature getSignature(Entity entity) const;

private:
    Entity currentEntity;
    std::array<Signature, kMaxEntities> signatures; // 每个实体的组件签名
    std::queue<Entity> availableEntities; // 可用实体池
};