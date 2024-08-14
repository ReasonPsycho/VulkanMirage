#include <SDL2/SDL.h>
#include <iostream>
#include <cstdlib>
#include <vector>
#include "VulkanMiragePathtracer.h"

int SDL_main(int argc, char *argv[]) {

    VulkanMiragePathtracer app;

    try {
        app.run();
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

