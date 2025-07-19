#pragma once
#include <memory>
#include "Manager/WorldManager.hpp"

class Application{
public:
    Application() = default;
    virtual ~Application() = default;

    // Initialize the application
    virtual Application& init();

    // Main loop of the application
    virtual int run();

    bool isRunning() const;
};