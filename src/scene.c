#include "internal.h"

struct Rect {
    float x, y, w, h;
};

struct Color {
    float r, g, b, a;
};

struct _Scene {
    struct Rect viewport;
    struct Color clear_color;

    Entity **entities;
    size_t n_entities;

    mat4x4 projection;
};

Scene *create_scene() {
    Scene *scene = (Scene *)malloc(sizeof(Scene));

    scene->entities = NULL;
    scene->n_entities = 0;

    scene->viewport = (struct Rect){0, 0, 1, 1};
    scene->clear_color = (struct Color){0, 0, 0, 1};

    return scene;
}

void destroy_scene(Scene *scene) {
    for (int i = 0; i < scene->n_entities; i++)
        destroy_entity(scene->entities[i]);

    free(scene->entities);
    free(scene);
}

void set_viewport(Scene *scene, float x, float y, float width, float height) {
    scene->viewport = (struct Rect){x, y, width, height};
}

void set_clear_color(Scene *scene, float r, float g, float b, float a) {
    scene->clear_color = (struct Color){r, g, b, a};
}

void add_entity(Scene *scene, Entity *entity) {
    // TODO: More efficent realloc
    scene->entities = (Entity **)realloc(scene->entities, sizeof(Entity *) * (scene->n_entities + 1));
    scene->entities[scene->n_entities] = entity;
    scene->n_entities++;
}

void update_scene(Scene *scene, float delta) {
    for (int i = 0; i < scene->n_entities; i++)
        update_entity(scene->entities[i], delta);
}

void render_scene(Scene *scene, int width, int height) {
    struct Rect *rect = &scene->viewport;
    glViewport(rect->x * width, rect->y * height, rect->w * width, rect->h * height);

    mat4x4 projection;
    mat4x4_identity(projection);
    mat4x4_perspective(projection, 45.0f, (float)(rect->w * width) / (rect->h * height), 0.1f, 100.0f);

    struct Color *color = &scene->clear_color;
    glClearColor(color->r, color->g, color->b, color->a);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    for (int i = 0; i < scene->n_entities; i++)
        render_entity(scene->entities[i], projection);
}
