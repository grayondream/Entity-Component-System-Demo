#include "Core/Log.hpp"
#include "App/Application.hpp"
int main(int argc, char** argv) {
    LOGI("Hello ECS");
    Application app;
    app.init();
    return app.run();
}
    
    