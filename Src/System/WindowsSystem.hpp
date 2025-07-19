#pragma once
#include "Core/System.hpp"
#include <string>

struct WindowsAttr{
    std::string title;
    int x;
    int y;
    int width;
    int height;
    bool fullscreen;
};

struct GLFWwindow;
class WindowsSystem : public System {
public:
    WindowsSystem(const WindowsAttr& attr);
    WindowsSystem();

    ~WindowsSystem();

    WindowsSystem& setParam(const WindowsAttr& attr) {
        _attr = attr;
        return *this;
    }

    GLFWwindow* getWindow() const {
        return _window;
    }
    
    virtual void init() override;

    virtual void tick(float dt) override;

    void destroy() override;

    void swpaBuffer();

    virtual bool isRunning() const override;
    
private:
    void initGLFW();
    void createWindow();

private:
    WindowsAttr _attr;
    // GLFW window or similar handle would go here
    GLFWwindow* _window = nullptr;
};