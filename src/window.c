#include "internal.h"

struct _Window {
    GLFWwindow *handle;

    Scene **scenes;
    size_t n_scenes;

    double time_elapsed;
};

void error_callback(int error, const char *description) {
    fprintf(stderr, "Error: %s\n", description);
}

Window *create_window(int width, int height, const char *title) {
    Window *window = (Window *)malloc(sizeof(Window));

    glfwSetErrorCallback(error_callback);
    if (!glfwInit())
        exit(EXIT_FAILURE);

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_CENTER_CURSOR, GL_TRUE);

    window->handle = glfwCreateWindow(width, height, title, NULL, NULL);
    if (!window) {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glfwMakeContextCurrent(window->handle);
    glfwSwapInterval(1);

    glEnable(GL_DEPTH_TEST);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    window->scenes = NULL;
    window->n_scenes = 0;
    window->time_elapsed = 0;

    glfwSetWindowUserPointer(window->handle, (void *)window);

    return window;
}

void destroy_window(Window *window) {
    glfwDestroyWindow(window->handle);
    glfwTerminate();

    for (int i = 0; i < window->n_scenes; i++)
        destroy_scene(window->scenes[i]);

    free(window->scenes);
    free(window);
}

void loop_window(Window *window) {
    while (!glfwWindowShouldClose(window->handle)) {
        double current_time = glfwGetTime();
        double delta = current_time - window->time_elapsed;
        window->time_elapsed = current_time;

        int width, height;
        glfwGetFramebufferSize(window->handle, &width, &height);

        for (int i = 0; i < window->n_scenes; i++) {
            Scene *scene = window->scenes[i];

            update_scene(scene, delta);
            render_scene(scene, width, height);
        }

        glfwSwapBuffers(window->handle);
        glfwPollEvents();
    }
}

void add_scene(Window *window, Scene *scene) {
    window->scenes = (Scene **)realloc(window->scenes, sizeof(Scene *) * (window->n_scenes + 1));
    window->scenes[window->n_scenes] = scene;
    window->n_scenes++;
}
