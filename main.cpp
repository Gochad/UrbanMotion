#include "src/App.h"
#include <iostream>

int main() {
    App app;

    if (!app.init()) {
        std::cerr << "Failed to initialize the application.";
        return -1;
    }

    app.run();

    app.shutdown();

    return 0;
}
