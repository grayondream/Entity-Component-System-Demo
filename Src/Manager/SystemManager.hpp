#pragma once

#include "Core/Types.hpp"
#include "Core/System.hpp"
#include <unordered_map>
#include <memory>
#include <string>
#include <cassert>

class SystemManager{
public:
    template<typename T, typename... Args>
    std::shared_ptr<T> registerSystem(Args&&... args) {
        const char* typeName = typeid(T).name();
        assert(_systems.find(typeName) == _systems.end() && "Registering system more than once.");
        
        auto system = std::make_shared<T>(std::forward<Args>(args)...);
        _systems.insert({typeName, system});
        return system;
    }

    template<typename T>
    void setSignature(Signature signature) {
        const char* typeName = typeid(T).name();
        assert(_systems.find(typeName) != _systems.end() && "System used before registered.");
        
        _signatures.insert({typeName, signature});
    }

    void entityDestroyed(Entity entity) {
        for (auto& [_, system] : _systems) {
            system->erase(entity);
        }
    }

    template<typename T>
    std::shared_ptr<T> getSystem() {
        const char* typeName = typeid(T).name();
        auto it = _systems.find(typeName);
        assert(it != _systems.end() && "System not found.");
        return std::static_pointer_cast<T>(it->second);
    }
    template<typename T>
    void signatureChanged(Entity entity, Signature signature) {
       for(auto& [type, system] : _systems) {
            auto& systemSignature = _signatures[type];
            if ((signature & systemSignature) == systemSignature) {
                system->insert(entity);
            } else {
                system->erase(entity);
            }
        }
    }
    
    void initializeAll() {
        for (auto& [_, system] : _systems) {
            system->init();
        }
    }

    void tickAll(float dt) {
        for (auto& [_, system] : _systems) {
            system->tick(dt);
        }
    }

    bool isRunning() const {
        for (const auto& [_, system] : _systems) {
            if (!system->isRunning()) {
                return false;
            }
        }
        return true;
    }
private:
    std::unordered_map<const char*, std::shared_ptr<ISystem>> _systems;
    std::unordered_map<const char*, Signature> _signatures; // 系统签名
};

