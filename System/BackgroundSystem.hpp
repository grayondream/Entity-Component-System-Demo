#include "Core/System.hpp"

class BackgroundSystem : public System {
public:
    BackgroundSystem() = default;

    virtual ~BackgroundSystem() = default;

    virtual void init() override;
    virtual void tick(float dt) override;
    virtual void destroy() override;
};