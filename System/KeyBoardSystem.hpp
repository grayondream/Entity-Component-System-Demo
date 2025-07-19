#pragma once

#include "Core/System.hpp"
#include <glfw/glfw3.h>


class KeyboardSystem : public System {
public:
    KeyboardSystem(GLFWwindow* window) : _window(window) {}

    void init() override;

    void tick(float dt) override;

    void destroy() override;
private:
    GLFWwindow* _window;
};