#pragma once

#include "Core/System.hpp"
#include "Geometry/Camera.hpp"
#include "Geometry/Sphere.hpp"

class GLProgram;
class RenderSystem : public System {
public:
    RenderSystem() = default;

    virtual ~RenderSystem() = default;

    virtual void init() override;
    virtual void tick(float dt) override;
    virtual void destroy() override;

private:
    void createVertexBuffer();

private:
    unsigned int _vao = 0; // Vertex Array Object
    unsigned int _vbo[2] = {0, 0}; // Vertex Buffer Objects
    unsigned int _ebo = 0; // Element Buffer Object

    GLProgram* _glProgram = nullptr; // Pointer to OpenGL program for rendering
    Camera _camera; // Camera for view transformation
    Sphere _shape;
};