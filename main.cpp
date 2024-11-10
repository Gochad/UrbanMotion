#include "src/App.h"
#include <iostream>

int main() {
    int grid_size = 10;
    int square_size = 50;

    App app(grid_size, square_size);

    if (!app.init()) {
        std::cerr << "Failed to initialize the application.\n";
        return -1;
    }

    app.run();

    app.shutdown();

    return 0;
}
