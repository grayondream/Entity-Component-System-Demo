#pragma once
#include <array>
#include <unordered_map>
#include <memory>
#include <stdexcept>
#include "Core/ComponentArray.hpp"

class ComponentManager {
public:
    template<typename T>
    void registerComponent(){
        static_assert(std::is_standard_layout_v<T>, "Component must be standard layout.");
        static_assert(sizeof(T) > 0, "Component must have size.");

        const char* typeName = typeid(T).name();
        if (_componentTypes.find(typeName) != _componentTypes.end()) {
            throw std::runtime_error("Component type already registered.");
        }

        _componentTypes[typeName] = _componentTypes.size();
        _componentStorages[typeName] = std::make_shared<ComponentArray<T>>();
    }

    template<typename T>
    void add(Entity entity, T component){
        getComponentArray<T>()->insert(entity, component);
    }

    template<typename T>
    void remove(Entity entity){
        getComponentArray<T>()->remove(entity);

    }

    template<typename T>
    ComponentType getType(){
        const char * typeName = typeid(T).name();
        assert(_componentTypes.find(typeName) != _componentTypes.end() && "Component type not registered.");
        return _componentTypes[typeName];
    }

    template<typename T>
    T& get(Entity entity){
        return getComponentArray<T>()->get(entity);
    }
    
    void destroyEntity(Entity entity){
        for (auto& [type, storage] : _componentStorages) {
            storage->destroyEntity(entity);
        }
    }

    template<typename T>
    bool hasComponent(Entity entity) {
        const char* typeName = typeid(T).name();
        auto it = _componentTypes.find(typeName);
        if (it == _componentTypes.end()) {
            return false; // Component type not registered
        }

        auto storage = getComponentArray<T>();
        if (!storage) {
            return false; // Storage not found
        }

        return storage->hasComponent(entity);
    }

private:
    template<typename T>
	std::shared_ptr<ComponentArray<T>> getComponentArray(){
		const char* typeName = typeid(T).name();

		assert(_componentTypes.find(typeName) != _componentTypes.end() && "Component not registered before use.");
		return std::static_pointer_cast<ComponentArray<T>>(_componentStorages[typeName]);
	}

private:
    std::unordered_map<const char*, ComponentType> _componentTypes;
    std::unordered_map<const char*, std::shared_ptr<IComponentArray>> _componentStorages;
};