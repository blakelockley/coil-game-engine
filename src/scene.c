#include "internal.h"

Scene *create_scene() {
    Scene *scene = (Scene *)malloc(sizeof(Scene));

    scene->entities = NULL;
    scene->n_entities = 0;

    scene->lights = NULL;
    scene->n_lights = 0;

    scene->clear_color[0] = 0.0f;
    scene->clear_color[1] = 0.0f;
    scene->clear_color[2] = 0.0f;
    scene->clear_color[3] = 1.0f;

    scene->loop_function = NULL;
    scene->input_function = NULL;
    scene->mouse_position_function = NULL;
    scene->mouse_button_function = NULL;

    return scene;
}

void destroy_scene(Scene *scene) {
    free(scene->entities);
    free(scene->lights);
    free(scene);
}

void set_loop_function(Scene *scene, void (*fn)(Scene *, float)) {
    scene->loop_function = fn;
}

void set_input_function(Scene *scene, void (*fn)(Scene *, int, int, int, int)) {
    scene->input_function = fn;
}

void set_mouse_position_function(Scene *scene, void (*fn)(Scene *, double, double)) {
    scene->mouse_position_function = fn;
}

void set_mouse_button_function(Scene *scene, void (*fn)(Scene *, int, int, int)) {
    scene->mouse_button_function = fn;
}

void set_clear_color(Scene *scene, float r, float g, float b, float a) {
    scene->clear_color[0] = r;
    scene->clear_color[1] = g;
    scene->clear_color[2] = b;
    scene->clear_color[3] = a;
}

void add_entity(Scene *scene, Entity *entity) {
    // TODO: More efficent realloc
    scene->entities = (Entity **)realloc(scene->entities, sizeof(Entity *) * (scene->n_entities + 1));
    scene->entities[scene->n_entities] = entity;
    scene->n_entities++;
}

void add_light(Scene *scene, Light *light) {
    // TODO: More efficent realloc
    scene->lights = (Light **)realloc(scene->lights, sizeof(Light *) * (scene->n_lights + 1));
    scene->lights[scene->n_lights] = light;
    scene->n_lights++;
}

void update_scene(Scene *scene, float delta) {
    if (scene->loop_function != NULL)
        scene->loop_function(scene, delta);
}

void process_scene_input(Scene *scene, int key, int scancode, int action, int mods) {
    if (scene->input_function)
        scene->input_function(scene, key, scancode, action, mods);
}

void process_scene_mouse_position(Scene *scene, double xpos, double ypos) {
    if (scene->mouse_position_function)
        scene->mouse_position_function(scene, xpos, ypos);
}

void process_scene_mouse_button(Scene *scene, int button, int action, int mods) {
    if (scene->mouse_button_function)
        scene->mouse_button_function(scene, button, action, mods);
}

void render_scene(Scene *scene, int width, int height) {
    glViewport(0, 0, width, height);

    glClearColor(scene->clear_color[0], scene->clear_color[1], scene->clear_color[2], scene->clear_color[3]);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    mat4x4_identity(scene->projection);
    mat4x4_perspective(scene->projection, 45.0f, (float)(width) / (height), 0.1f, 100.0f);

    for (int i = 0; i < scene->n_entities; i++)
        render_entity(scene->entities[i], scene);
}

void set_camera(Scene *scene, Camera *camera) {
    scene->camera = camera;
}
