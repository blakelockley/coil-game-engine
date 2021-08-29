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

void key_callback(GLFWwindow *handle, int key, int scancode, int action, int mods) {
    Window *window = glfwGetWindowUserPointer(handle);

    for (int i = 0; i < window->n_scenes; i++) {
        Scene *scene = window->scenes[i];
        process_scene_input(scene, key, scancode, action, mods);
    }

    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(handle, GLFW_TRUE);
}

void mouse_position_callback(GLFWwindow *handle, double xpos, double ypos) {
    Window *window = glfwGetWindowUserPointer(handle);

    int width, height;
    glfwGetWindowSize(window->handle, &width, &height);

    double xnorm = xpos / (double)width * 2.0 - 1.0;
    double ynorm = (ypos / (double)height * 2.0 - 1.0) * -1.0;

    for (int i = 0; i < window->n_scenes; i++) {
        Scene *scene = window->scenes[i];
        process_scene_mouse_position(scene, xnorm, ynorm);
    }
}

void mouse_button_callback(GLFWwindow *handle, int button, int action, int mods) {
    Window *window = glfwGetWindowUserPointer(handle);

    for (int i = 0; i < window->n_scenes; i++) {
        Scene *scene = window->scenes[i];
        process_scene_mouse_button(scene, button, action, mods);
    }
}

Window *create_window(int width, int height, const char *title) {
    Window *window = (Window *)malloc(sizeof(Window));

    window->scenes = NULL;
    window->n_scenes = 0;
    window->time_elapsed = 0;

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

    glEnable(GL_BLEND);
    glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);

    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glfwSetWindowUserPointer(window->handle, (void *)window);
    glfwSetInputMode(window->handle, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    glfwSetKeyCallback(window->handle, key_callback);
    glfwSetCursorPosCallback(window->handle, mouse_position_callback);
    glfwSetMouseButtonCallback(window->handle, mouse_button_callback);

    if (glfwRawMouseMotionSupported())
        glfwSetInputMode(window->handle, GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);

    return window;
}

void destroy_window(Window *window) {
    glfwDestroyWindow(window->handle);
    glfwTerminate();

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
