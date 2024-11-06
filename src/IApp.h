#pragma once
#include <memory>

class IApp {
protected:
    IApp() {}
public:
    virtual ~IApp() {}
    virtual bool init() = 0;
    virtual void run() = 0;
    virtual void shutdown() = 0;

    static IApp* Create();
};
