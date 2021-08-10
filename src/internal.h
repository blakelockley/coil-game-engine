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
};

struct _Light {
    vec3 position;

    vec3 ambient_color;
    vec3 diffuse_color;
    vec3 specular_color;
};

// Scenes
void update_scene(Scene *scene, float delta);
void render_scene(Scene *scene, int width, int height);

// Entities
void update_entity(Entity *entity, float delta);
void render_entity(Entity *entity, Scene *scene);

// Models
void render_model(Model *model, GLuint shader);

#endif  // ENGINE_INTERNAL_H