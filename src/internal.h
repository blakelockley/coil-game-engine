#ifndef ENGINE_INTERNAL_H
#define ENGINE_INTERNAL_H

#include "engine.h"

struct _Scene {
    Entity **entities;
    size_t n_entities;

    Light **lights;
    size_t n_lights;

    vec4 clear_color;
    mat4x4 projection;

    void (*loop_function)(Scene *, float);
};

struct _Light {
    vec4 position;

    vec3 ambient_color;
    vec3 diffuse_color;
    vec3 specular_color;

    float constant;
    float linear;
    float quadratic;
};

typedef struct _Vertex {
    vec3 position;
    vec3 normal;
    vec2 texcoord;
} Vertex;

struct _Model {
    GLuint vao, ebo, vbo;
    GLsizei count;

    GLboolean has_texture;
    GLuint texture;
};

// Scenes
void update_scene(Scene *scene, float delta);
void render_scene(Scene *scene, int width, int height);

// Entities
void render_entity(Entity *entity, Scene *scene);

// Models
Model *create_model(Vertex vertices[], size_t vertices_n, unsigned int indicies[], size_t indicies_n);
void render_model(Model *model, GLuint shader);

#endif  // ENGINE_INTERNAL_H