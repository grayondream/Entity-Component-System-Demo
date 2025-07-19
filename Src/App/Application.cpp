#include "App/Application.hpp"
#include "Core/Log.hpp"
#include "System/System.hpp"
#include "Component/Component.hpp"
#include <random>

std::unique_ptr<WorldManager> g_worldManager;

void RegisterComponents() {
    g_worldManager->registerComponent<Player>();
    g_worldManager->registerComponent<Transform>();
    g_worldManager->registerComponent<KeyBoard>();
    g_worldManager->registerComponent<RenderColor>();
    g_worldManager->registerComponent<Velocity>();
}

void RegisterSystems() {
    // ע�� WindowsSystem
    WindowsAttr attr = { "My ECS Window", 100, 100, 800, 600, false };
    auto windowSystem = g_worldManager->registerSystem<WindowsSystem>(attr);
    {
        Signature signature;
        signature.set(g_worldManager->getComponentType<KeyBoard>());
        g_worldManager->setSystemSignature<WindowsSystem>(signature);
    }

    // ע�� KeyboardSystem
    auto keyboardSystem = g_worldManager->registerSystem<KeyboardSystem>(windowSystem->getWindow());
    {
        Signature signature;
        signature.set(g_worldManager->getComponentType<KeyBoard>());
        g_worldManager->setSystemSignature<KeyboardSystem>(signature);
    }

    // ע�� RenderSystem
    auto renderSystem = g_worldManager->registerSystem<RenderSystem>();
    {
        Signature signature;
        signature.set(g_worldManager->getComponentType<Transform>());
        signature.set(g_worldManager->getComponentType<RenderColor>());
        g_worldManager->setSystemSignature<RenderSystem>(signature);
    }

    auto backgroundSystem = g_worldManager->registerSystem<BackgroundSystem>();
    {
        Signature signature;
        signature.set(g_worldManager->getComponentType<Transform>());
        signature.set(g_worldManager->getComponentType<Velocity>());
        g_worldManager->setSystemSignature<BackgroundSystem>(signature);
    }
    // // 创建 Camera 对象
    // Camera* camera = new Camera(glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3(0.0f, 1.0f, 0.0f), -90.0f, 0.0f);
    // // 注册 CameraControlSystem
    // auto cameraControlSystem = g_worldManager->registerSystem<CameraControlSystem>(camera);
    // {
    //     Signature signature;
    //     signature.set(g_worldManager->getComponentType<KeyBoard>());
    //     g_worldManager->setSystemSignature<CameraControlSystem>(signature);
    // }
}

void CreatePlayerEntity() {
    auto playerSystem = g_worldManager->registerSystem<PlayerSystem>();
    {
        Signature signature;
        signature.set(g_worldManager->getComponentType<Player>());
        signature.set(g_worldManager->getComponentType<Transform>());
        signature.set(g_worldManager->getComponentType<KeyBoard>());
        signature.set(g_worldManager->getComponentType<RenderColor>());
        g_worldManager->setSystemSignature<PlayerSystem>(signature);
    }

    Entity playerEntity = g_worldManager->createEntity();
    g_worldManager->addComponent(playerEntity, Player{});
    g_worldManager->addComponent(playerEntity, Transform{ glm::vec3(0.0f), glm::vec3(0.0f), glm::vec3(1.0f) });
    g_worldManager->addComponent(playerEntity, KeyBoard{ 0 }); // Initialize with a default key code
    g_worldManager->addComponent(playerEntity, RenderColor{ 1.0f, 0.0f, 0.0f, 1.0f }); // Red color
}

void CreateRandomEntity(){
    constexpr int entityCount = 200;
    for (int i = 0; i < entityCount; ++i) {
        Entity entity = g_worldManager->createEntity();
        {
            // Random position
            std::random_device rd;
            std::mt19937 gen(rd());
            std::uniform_real_distribution<float> dis(-4.0f, 4.f);
            glm::vec3 position(dis(gen), dis(gen), dis(gen));
            g_worldManager->addComponent(entity, Transform{ position, glm::vec3(0.0f), glm::vec3(1.0f) });
            // Random color
            std::uniform_real_distribution<float> colorDis(0.0f, 1.0f);
            glm::vec3 color(colorDis(gen), colorDis(gen), colorDis(gen));
            g_worldManager->addComponent(entity, RenderColor{ color.r, color.g, color.b, 1.0f }); // Alpha set to 1.0
        }
        // Random velocity
        {
            std::random_device rd;
            std::mt19937 gen(rd());
            std::uniform_real_distribution<float> dis(0.5f, 1.f);
            glm::vec3 speed(0, -1 * dis(gen), 0);
            g_worldManager->addComponent(entity, Velocity{ speed });
        }
    }
}

void CreateWindowsEntity() {
    Entity windowEntity = g_worldManager->createEntity();
    g_worldManager->addComponent(windowEntity, KeyBoard{ 0 }); // Initialize with a default key code
}

void CreateEntities() {
    // Create a player entity
    CreatePlayerEntity();
    // Create a window entity
    CreateWindowsEntity();
    CreateRandomEntity();
}

Application& Application::init() {
    LOGI("Application initialized");
    g_worldManager = std::make_unique<WorldManager>();
    RegisterComponents();
    RegisterSystems();
    CreateEntities();
    return *this;
}

bool Application::isRunning() const {
    // Placeholder for actual running condition
    return g_worldManager->isRunning();
}

int Application::run() {
    LOGI("Application run");
    g_worldManager->initializeAll();

    while (isRunning()) {
        g_worldManager->tickAll(0.016f); // Simulate a frame time of 16ms (60 FPS)
        std::this_thread::sleep_for(std::chrono::milliseconds(16)); // Simulate frame delay
    }

    return 0;
}