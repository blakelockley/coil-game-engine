#include "internal.h"

Camera *create_camera(float x, float y, float z) {
    Camera *camera = malloc(sizeof(Camera));

    // clang-format off
    *camera = (Camera) {
        { x, y, z},
        { 0.0f, 0.0f, -1.0f},
        {
            { 1.0f, 0.0f, 0.0f, 0.0f},
            { 0.0f, 1.0f, 0.0f, 0.0f},
            { 0.0f, 0.0f, 1.0f, 0.0f},
            { 0.0f, 0.0f, 0.0f, 1.0f}
        }
    };
    // clang-format on

    return camera;
}

void set_camera_position(Camera *camera, float x, float y, float z) {
    camera->position[0] = x;
    camera->position[1] = y;
    camera->position[2] = z;
}

void set_camera_direction(Camera *camera, float x, float y, float z) {
    camera->direction[0] = x;
    camera->direction[1] = y;
    camera->direction[2] = z;
}

void destroy_camera(Camera *camera) {
    free(camera);
}
