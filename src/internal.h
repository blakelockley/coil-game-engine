#ifndef ENGINE_INTERNAL_H
#define ENGINE_INTERNAL_H

#include "engine.h"

// Window
void add_scene(Window *window, Scene *scene);

// Scenes
void update_scene(Scene *scene, float delta);
void render_scene(Scene *scene, int width, int height);

// Entities
void update_entity(Entity *entity, float delta);
void render_entity(Entity *entity, mat4x4 projection);

// Models
void render_model(Model *model, GLuint shader);

#endif  // ENGINE_INTERNAL_H