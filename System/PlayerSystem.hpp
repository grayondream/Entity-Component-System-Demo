#pragma once
#include "Core/System.hpp"

class PlayerSystem : public System {
public:
    void init() override;
    void tick(float dt) override;
    void destroy() override;
};