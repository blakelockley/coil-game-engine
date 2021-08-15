#include "engine.h"

// clang-format off
Vertex vertices[24] = {
    
    // front 
    {{-0.5, -0.5, +0.5}, {0.0, 0.0, +1.0}},  //  0 left  bottom front
    {{-0.5, +0.5, +0.5}, {0.0, 0.0, +1.0}},  //  1 left  top    front
    {{+0.5, -0.5, +0.5}, {0.0, 0.0, +1.0}},  //  2 right bottom front
    {{+0.5, +0.5, +0.5}, {0.0, 0.0, +1.0}},  //  3 right top    front
 
    // left  
    {{-0.5, -0.5, +0.5}, {-1.0, 0.0, 0.0}},  //  4 left  bottom front
    {{-0.5, +0.5, +0.5}, {-1.0, 0.0, 0.0}},  //  5 left  top    front
    {{-0.5, -0.5, -0.5}, {-1.0, 0.0, 0.0}},  //  6 left  bottom back
    {{-0.5, +0.5, -0.5}, {-1.0, 0.0, 0.0}},  //  7 left  top    back
 
    // right 
    {{+0.5, -0.5, +0.5}, {+1.0, 0.0, 0.0}},  //  8 right bottom front
    {{+0.5, +0.5, +0.5}, {+1.0, 0.0, 0.0}},  //  9 right top    front
    {{+0.5, -0.5, -0.5}, {+1.0, 0.0, 0.0}},  // 10 right bottom back
    {{+0.5, +0.5, -0.5}, {+1.0, 0.0, 0.0}},  // 11 right top    back

    // back
    {{-0.5, -0.5, -0.5}, {0.0, 0.0, -1.0}},  // 12 left  bottom back
    {{-0.5, +0.5, -0.5}, {0.0, 0.0, -1.0}},  // 13 left  top    back
    {{+0.5, -0.5, -0.5}, {0.0, 0.0, -1.0}},  // 14 right bottom back
    {{+0.5, +0.5, -0.5}, {0.0, 0.0, -1.0}},  // 15 right top    back

    // top
    {{-0.5, +0.5, +0.5}, {0.0, 1.0, 0.0}},  // 16 left  top    front
    {{-0.5, +0.5, -0.5}, {0.0, 1.0, 0.0}},  // 17 left  top    back
    {{+0.5, +0.5, +0.5}, {0.0, 1.0, 0.0}},  // 18 right top    front
    {{+0.5, +0.5, -0.5}, {0.0, 1.0, 0.0}},  // 19 right top    back

    // bottom
    {{-0.5, -0.5, +0.5}, {0.0, -1.0, 0.0}},  // 20 left  bottom front
    {{-0.5, -0.5, -0.5}, {0.0, -1.0, 0.0}},  // 21 left  bottom back
    {{+0.5, -0.5, +0.5}, {0.0, -1.0, 0.0}},  // 22 right bottom front
    {{+0.5, -0.5, -0.5}, {0.0, -1.0, 0.0}},  // 23 right bottom back
};

unsigned int indicies[36] = {
    //front
    0, 1, 2,
    3, 2, 1,
    
    // left
    4, 5, 6,
    7, 6, 5,
    
    // right
    8, 9, 10,
    11, 10, 9,
    
    // back
    12, 13, 14,
    15, 14, 13,
    
    // top
    16, 17, 18,
    19, 18, 17,
    
    // bottom
    20, 21, 22,
    23, 22, 21,
};
// clang-format on

#define SEED 42
#define N_CUBES 1

vec3 cube_positions[N_CUBES] = {
    {0.0f, 0.0f, -3.0f},
};

Entity *cubes[N_CUBES], *lamp;
Model *cube_model;
Light *light;

void game_loop(Scene *scene, float delta) {
    static float rot_y = 0.0f;
    rot_y += delta;

    for (int i = 0; i < N_CUBES; i++)
        set_rotation(cubes[i], 0, 1, 0, -rot_y * 0.1f * i);

    set_position(lamp, sin(rot_y), 0.0f, -3 + cos(rot_y));
    set_light_position(light, sin(rot_y), 0.0f, -3 + cos(rot_y));
}

int main(int argc, char **argv) {
    Window *window = create_window(640, 480, "Cube");

    Scene *scene = create_scene();
    set_loop_function(scene, game_loop);
    set_clear_color(scene, 0.0, 0.0, 0.0, 1.0);
    add_scene(window, scene);

    srand(SEED);

    cube_model = create_model(vertices, 24, indicies, 36);

    for (int i = 0; i < N_CUBES; i++) {
        Entity *cube = create_entity();

        set_model(cube, cube_model);
        set_color(cube, rand() / (float)RAND_MAX, rand() / (float)RAND_MAX, rand() / (float)RAND_MAX);

        set_position(cube, cube_positions[i][0], cube_positions[i][1], cube_positions[i][2]);
        add_entity(scene, cube);

        cubes[i] = cube;
    }

    light = create_light();
    set_ambient_color(light, 0.4f, 0.4f, 0.4f);
    set_diffuse_color(light, 0.8f, 0.8f, 0.8f);
    set_specular_color(light, 1.0f, 1.0f, 1.0f);
    add_light(scene, light);

    lamp = create_entity();
    set_model(lamp, cube_model);
    set_emissive(lamp, 1.0f, 1.0f, 1.0f);
    set_scale(lamp, 0.1f);
    add_entity(scene, lamp);

    loop_window(window);

    destroy_light(light);

    destroy_model(cube_model);

    destroy_entity(lamp);

    for (int i = 0; i < N_CUBES; i++)
        destroy_entity(cubes[i]);

    destroy_scene(scene);
    destroy_window(window);
}