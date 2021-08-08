#ifndef ENGINE_H
#define ENGINE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "linmath.h"

#define GL_SILENCE_DEPRECATION
#define GLFW_INCLUDE_GLCOREARB

#include <GLFW/glfw3.h>

typedef struct _Vertex {
    vec3 position;
    vec3 normal;
} Vertex;

typedef struct _Window Window;
typedef struct _Scene Scene;
typedef struct _Camera Camera;
typedef struct _Entity Entity;
typedef struct _Model Model;

Window *create_window(int width, int height, const char *title);
void destroy_window(Window *window);
void loop_window(Window *window);
void add_scene(Window *window, Scene *scene);

Scene *create_scene();
void destroy_scene(Scene *scene);
void set_viewport(Scene *scene, float x, float y, float width, float height);
void set_clear_color(Scene *scene, float r, float g, float b, float a);
void add_entity(Scene *scene, Entity *entity);

Entity *create_entity();
void destroy_entity(Entity *entity);
void set_update_function(Entity *entity, void (*update)(float));
void set_transform_function(Entity *entity, void (*tranform)(mat4x4));
void set_model(Entity *scene, Model *model);

Model *create_model(Vertex vertices[], size_t vertices_n, unsigned int indicies[], size_t indicies_n);
void destroy_model(Model *model);

#endif  // ENGINE_H