#include "engine.h"

// clang-format off
vec3 vertices[8] = {
    {-0.5, -0.5, +0.5}, // 0 left  bottom front
    {-0.5, +0.5, +0.5}, // 1 left  top    front
    {+0.5, -0.5, +0.5}, // 2 right bottom front
    {+0.5, +0.5, +0.5}, // 3 right top    front
    {-0.5, -0.5, -0.5}, // 4 left  bottom back
    {-0.5, +0.5, -0.5}, // 5 left  top    back
    {+0.5, -0.5, -0.5}, // 6 right bottom back
    {+0.5, +0.5, -0.5}, // 7 right top    back
};

static unsigned int indicies[36] = {
    //front
    0, 1, 2,
    3, 2, 1,
    
    // left
    0, 1, 4,
    5, 4, 1,
    
    // right
    2, 3, 6,
    7, 6, 3,
    
    // back
    4, 5, 6,
    7, 6, 5,
    
    // top
    1, 5, 3,
    7, 3, 5,
    
    // bottom
    0, 4, 2,
    6, 2, 4,
};
// clang-format on

float rot_y = 0.0f;
void update(float delta) {
    rot_y += -delta * 2;
}

void transform(mat4x4 mat) {
    mat4x4_identity(mat);
    mat4x4_translate(mat, 0.0f, 0.0f, -2.0f);
    mat4x4_rotate_Y(mat, mat, rot_y);
}

int main(int argc, char **argv) {
    Window *window = create_window(640, 480, "Cube");

    Scene *scene = create_scene();
    set_clear_color(scene, 0.0, 0.0, 0.0, 1.0);
    add_scene(window, scene);

    Entity *cube = create_entity();
    set_update_function(cube, update);
    set_transform_function(cube, transform);
    add_entity(scene, cube);

    Model *model = create_model(vertices, 8, indicies, 36);
    set_model(cube, model);

    loop_window(window);

    destroy_window(window);
}