#pragma once
#include <memory>
#include "Manager/ComponentManager.hpp"
#include "Manager/SystemManager.hpp"
#include "Manager/EntityManager.hpp"


class WorldManager {
public:
    WorldManager()
        : _sysManager(std::make_unique<SystemManager>()),
          _entityManager(std::make_unique<EntityManager>()),
          _componentManager(std::make_unique<ComponentManager>()) {}

    ~WorldManager() = default;

    template<typename T, typename... Args>
    std::shared_ptr<T> registerSystem(Args&&... args) {
        return _sysManager->registerSystem<T>(std::forward<Args>(args)...);
    }

    void initializeAll() {
        _sysManager->initializeAll();
    }

    void tickAll(float dt) {
        _sysManager->tickAll(dt);
    }

    bool isRunning() const {
        return _sysManager->isRunning();
    }

    Entity createEntity() {
        return _entityManager->createEntity();
    }

    template<typename T>
    void registerComponent() {
        _componentManager->registerComponent<T>();
    }

    template<typename T>
    void addComponent(Entity entity, T component) {
        _componentManager->add<T>(entity, component);
        auto signature = _entityManager->getSignature(entity);
        signature.set(_componentManager->getType<T>(), true);
        _entityManager->setSignature(entity, signature);
        _sysManager->signatureChanged<T>(entity, signature);
    }

    template<typename T>
    void removeComponent(Entity entity) {
        _componentManager->removeComponent<T>(entity);
        auto signature = _entityManager->getSignature(entity);
        signature.set(_componentManager->getComponentType<T>(), false);
        _entityManager->setSignature(entity, signature);
        _sysManager->signatureChanged<T>(entity, signature);
    }

    template<typename T>
    T& getComponent(Entity entity) {
        return _componentManager->get<T>(entity);
    }

    template<typename T>
    ComponentType getComponentType() {
        return _componentManager->getType<T>();
    }

    template<typename T>
    bool hasComponent(Entity entity) {
        return _componentManager->hasComponent<T>(entity);
    }

    template<typename T>
    void setSystemSignature(Signature signature) {
        _sysManager->setSignature<T>(signature);
    }

    void destroyEntity(Entity entity) {
        _entityManager->destroyEntity(entity);
        _sysManager->entityDestroyed(entity);
        _componentManager->destroyEntity(entity);
    }
private:
    std::unique_ptr<SystemManager> _sysManager;
    std::unique_ptr<EntityManager> _entityManager;
    std::unique_ptr<ComponentManager> _componentManager;
};