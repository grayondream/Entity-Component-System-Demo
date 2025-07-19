#include "System/RenderSystem.hpp"
#include "Core/Log.hpp"
#include "Manager/WorldManager.hpp"
#include "Component/Transform.hpp"
#include "OpenGL/GLProgram.hpp"
#include "Geometry/Sphere.hpp"
#include "Utils/FileUtils.hpp"
#include "Component/RenderColor.hpp"
#include "Component/Player.hpp"

using FileUtils::join;

extern std::unique_ptr<WorldManager> g_worldManager;

void RenderSystem::init() {
    _shape = Sphere(1.0f, 8, 8);
    LOGI("RenderSystem initialized");
    _glProgram = new GLProgram();
    const auto vfile = join(ECS_SOURCE_DIR, "Shader", "obj.vs");
	const auto ffile = join(ECS_SOURCE_DIR, "Shader", "obj.fs");
	auto ret = _glProgram->init(vfile, ffile);
    if (!ret) {
        LOGE("Failed to initialize GLProgram with vertex shader {} and fragment shader {}", vfile, ffile);
        throw std::runtime_error("GLProgram initialization failed");
    }

    LOGI("GLProgram initialized with vertex shader {} and fragment shader {}", vfile, ffile);
    createVertexBuffer();
    LOGI("RenderSystem vertex buffer created with VAO: {}, VBOs: [{}, {}], EBO: {}", _vao, _vbo[0], _vbo[1], _ebo);
    _camera = Camera(glm::vec3(0.0f, 0.0f, 6.0f));
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}

void RenderSystem::createVertexBuffer() {
	unsigned int vbo[2]{}, vao{}, ebo{};
	glGenVertexArrays(1, &vao);
	glGenBuffers(2, vbo);
	glGenBuffers(1, &ebo);

	glBindVertexArray(vao);
	{
		glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
		glBufferData(GL_ARRAY_BUFFER, _shape.byteSize(), _shape.toGL().data(), GL_STATIC_DRAW);
		glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), nullptr);
		glEnableVertexAttribArray(0);

		glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(float) * 4));
		glEnableVertexAttribArray(1);

		// �󶨵ڶ��� VBO�����ö��㷨��
		glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
		glBufferData(GL_ARRAY_BUFFER, _shape.normalSize(), _shape.normal(), GL_STATIC_DRAW);
		glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, sizeof(Vector4DBase<float>), nullptr);
		glEnableVertexAttribArray(2); // ����

		// ������������
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, _shape.idxByteSize(), _shape.idx(), GL_STATIC_DRAW);
	}
	glBindVertexArray(0);

	// ��¼ VBO �� EBO
	_vao = vao;
	_vbo[0] = vbo[0], _vbo[1] = vbo[1];
	_ebo = ebo;
}

void RenderSystem::tick(float dt) {
    // This is where rendering logic would go
    glClearColor(0.1, 0.1, 0.1, 1.0);
    GLint viewport[4];

    // 获取当前视口
    glGetIntegerv(GL_VIEWPORT, viewport);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    for(const auto& entity : _entities) {
        try {
            // Example: Get a component and log its data
            auto& transform = g_worldManager->getComponent<Transform>(entity);
            auto& color = g_worldManager->getComponent<RenderColor>(entity);
            if(g_worldManager->hasComponent<Player>(entity)) {
                //LOGI("Rendering player entity {} at position [{}, {}, {}]", (int)entity, transform.position.x, transform.position.y, transform.position.z);
            }else{
                //LOGI("Rendering entity {} at position [{}, {}, {}]", (int)entity, transform.position.x, transform.position.y, transform.position.z);
            }

            //LOGI("Rendering entity {} at position [{}, {}, {}]", (int)entity, transform.position.x, transform.position.y, transform.position.z);
            {
                glBindVertexArray(_vao);
                auto projection = glm::perspective<float>(glm::radians(_camera.zoom()), viewport[3] * 1.0f/viewport[2], 0.1f, 100.0f);
	
                const auto view = _camera.getViewMatrix();
                
                glm::vec3 pos = glm::vec3(
                    transform.position.x,
                    transform.position.y,
                    1
                );
                //draw light source
                {
                    
                    glm::mat4 model = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
                    model = glm::translate(model, pos);
                    model = glm::rotate(model, 0.f, glm::vec3(1.0f, 0.f, 0.f));
                    model = glm::scale(model, glm::vec3(0.1, 0.1, 0.1));

                    _glProgram->use();
                    _glProgram->update("projection", projection);
                    _glProgram->update("view", view);
                    _glProgram->update("color", glm::vec4(color.r, color.b, color.b, color.a));
                    _glProgram->update("model", model);
                    glDrawElements(GL_TRIANGLES, _shape.idxSize(), GL_UNSIGNED_INT, 0);
                    glBindVertexArray(0);
                }
            }
        } catch (const std::exception& e) {
            LOGE("Error processing entity {}: {}", (int)entity, e.what());
        }

        
    }

}

void RenderSystem::destroy() {
    LOGI("RenderSystem destroyed");
    if(_vao) {
        glDeleteVertexArrays(1, &_vao);
        _vao = 0;
    }

    if (_vbo[0]) {
        glDeleteBuffers(2, _vbo);
        _vbo[0] = _vbo[1] = 0;
    }

    if (_ebo) {
        glDeleteBuffers(1, &_ebo);
        _ebo = 0;
    }

    if (_glProgram) {
        delete _glProgram;
        _glProgram = nullptr;
    }
}