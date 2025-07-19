#pragma once
#include "Core/Types.hpp"
#include <array>
#include <unordered_map>
#include <cassert>

class IComponentArray {
public:
    virtual ~IComponentArray() = default;
    virtual void destroyEntity(Entity entity) = 0;
};

template<typename T>
class ComponentArray : public IComponentArray {
public:
    void insert(Entity entity, T component) {
        assert(_entityToIndexMap.find(entity) == _entityToIndexMap.end() && "Component added to the same entity more than once.");

        // Put new entry at end
        size_t newIndex = _size;
        _entityToIndexMap[entity] = newIndex;
        _indexToEntityMap[newIndex] = entity;
        _componentArray[newIndex] = component;
        ++_size;
    }

    void remove(Entity entity) {
        assert(_entityToIndexMap.find(entity) != _entityToIndexMap.end() && "Removing non-existent component.");

        // Copy element at end into deleted element's place to maintain density
        size_t indexOfRemovedEntity = _entityToIndexMap[entity];
        size_t indexOfLastElement = _size - 1;
        _componentArray[indexOfRemovedEntity] = _componentArray[indexOfLastElement];

        // Update map to point to moved spot
        Entity entityOfLastElement = _indexToEntityMap[indexOfLastElement];
        _entityToIndexMap[entityOfLastElement] = indexOfRemovedEntity;
        _indexToEntityMap[indexOfRemovedEntity] = entityOfLastElement;

        _entityToIndexMap.erase(entity);
        _indexToEntityMap.erase(indexOfLastElement);

        --_size;
    }

    T& get(Entity entity) {
        assert(_entityToIndexMap.find(entity) != _entityToIndexMap.end() && "Retrieving non-existent component.");

        return _componentArray[_entityToIndexMap[entity]];
    }

    void destroyEntity(Entity entity) override {
        if (_entityToIndexMap.find(entity) != _entityToIndexMap.end()) {
            remove(entity);
        }
    }

    bool hasComponent(Entity entity) const {
        return _entityToIndexMap.find(entity) != _entityToIndexMap.end();
    }
    
private:
    std::array<T, kMaxEntities> _componentArray{};
    std::unordered_map<Entity, size_t> _entityToIndexMap{};
    std::unordered_map<size_t, Entity> _indexToEntityMap{};
    size_t _size{0}; // 当前存储的大小
};

