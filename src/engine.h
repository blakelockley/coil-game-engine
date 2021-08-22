#ifndef ENGINE_H
#define ENGINE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "linmath.h"

#define GL_SILENCE_DEPRECATION
#define GLFW_INCLUDE_GLCOREARB

#include <GLFW/glfw3.h>

#define ENGINE_DIRECTIONAL_LIGHT 0.0f
#define ENGINE_POINT_LIGHT 1.0f

typedef struct _Window Window;
typedef struct _Scene Scene;
typedef struct _Camera Camera;
typedef struct _Entity Entity;
typedef struct _Light Light;
typedef struct _Model Model;

Window *create_window(int width, int height, const char *title);
void destroy_window(Window *window);
void loop_window(Window *window);
void add_scene(Window *window, Scene *scene);

Scene *create_scene();
void destroy_scene(Scene *scene);
void set_loop_function(Scene *scene, void (*fn)(Scene *, float));
void set_viewport(Scene *scene, float x, float y, float width, float height);
void set_clear_color(Scene *scene, float r, float g, float b, float a);
void add_entity(Scene *scene, Entity *entity);
void add_light(Scene *scene, Light *light);

Entity *create_entity(Model *model);
void destroy_entity(Entity *entity);

void set_emissive(Entity *entity, float r, float g, float b);
void set_color(Entity *entity, float r, float g, float b);

void set_position(Entity *entity, float x, float y, float z);
void set_rotation(Entity *entity, float x, float y, float z, float angle);
void set_scale(Entity *entity, float scale);

void set_model(Entity *scene, Model *model);

void set_texture(Model *model, const char *path);
void destroy_model(Model *model);

Light *create_light();
void destroy_light(Light *light);

void set_light_mode(Light *light, float w);
void set_light_position(Light *light, float x, float y, float z);

void set_attenuation(Light *light, float constant, float linear, float quadratic);
void set_ambient_color(Light *light, float r, float g, float b);
void set_diffuse_color(Light *light, float r, float g, float b);
void set_specular_color(Light *light, float r, float g, float b);

Model *build_cube(float size);
Model *build_sphere(float radius, int stacks, int sectors);

#endif  // ENGINE_H