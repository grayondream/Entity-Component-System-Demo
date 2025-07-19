#pragma once
#include <set>
#include "Core/Types.hpp"

class SystemStoratge{
protected:
    std::set<Entity> _entities;
};

class ISystem{
public:
    virtual void init() = 0;
    virtual void tick(float dt) = 0;
    virtual ~ISystem() = default;
    virtual bool isRunning() const = 0;
    virtual void destroy() = 0;
    virtual void erase(Entity entity) = 0;
    virtual void insert(Entity entity) = 0;
};

class System : public SystemStoratge, public ISystem{
public:
    virtual bool isRunning() const {
        return true;
    }

    virtual void init() override {}
    virtual void tick(float dt) override {}
    virtual void destroy() override {}
    virtual void erase(Entity entity) override {
        _entities.erase(entity);
    }

    virtual void insert(Entity entity) override {
        _entities.insert(entity);
    }
    
};