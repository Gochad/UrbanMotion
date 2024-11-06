#include "src/IApp.h"

int main() {
    IApp* app = IApp::Create();

    if (!app->init()) {
        return -1;
    }

    app->run();
    app->shutdown();
    delete app;

    return 0;
}
