#include "internal.h"

Light *create_light() {
    Light *light = malloc(sizeof(Light));

    // clang-format off
    *light = (Light) {
        { 0.0f, 0.0f, 0.0f, 0.0f},
        { 1.0f, 1.0f, 1.0f },
        { 1.0f, 1.0f, 1.0f },
        { 1.0f, 1.0f, 1.0f },
        1.0f, 0.09f, 0.032f,
    };
    // clang-format on

    return light;
}

void destroy_light(Light *light) {
    free(light);
}

void set_light_position(Light *light, float x, float y, float z) {
    light->position[0] = x;
    light->position[1] = y;
    light->position[2] = z;
}

void set_ambient_color(Light *light, float r, float g, float b) {
    light->ambient_color[0] = r;
    light->ambient_color[1] = g;
    light->ambient_color[2] = b;
}

void set_diffuse_color(Light *light, float r, float g, float b) {
    light->diffuse_color[0] = r;
    light->diffuse_color[1] = g;
    light->diffuse_color[2] = b;
}

void set_specular_color(Light *light, float r, float g, float b) {
    light->specular_color[0] = r;
    light->specular_color[1] = g;
    light->specular_color[2] = b;
}

void set_attenuation(Light *light, float constant, float linear, float quadratic) {
    light->constant = constant;
    light->linear = linear;
    light->quadratic = quadratic;
}

void set_light_mode(Light *light, float w) {
    light->position[3] = w;
}
