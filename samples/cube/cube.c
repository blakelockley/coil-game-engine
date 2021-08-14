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

static unsigned int indicies[36] = {
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

Light *light;
Entity *lamp;

float rot_y = 0.0f;
void update(Entity *cube, float delta) {
    rot_y += delta;
    set_rotation(cube, 0, 1, 0, -rot_y * 0.1f);

    set_position(lamp, sin(rot_y), 0.0f, -3 + cos(rot_y));
    set_light_position(light, sin(rot_y), 0.0f, -3 + cos(rot_y));
}

int main(int argc, char **argv) {
    Window *window = create_window(640, 480, "Cube");

    Scene *scene = create_scene();
    set_clear_color(scene, 0.0, 0.0, 0.0, 1.0);
    add_scene(window, scene);

    Entity *cube = create_entity();
    set_color(cube, 0.1f, 0.6f, 0.8f);
    set_position(cube, 0.0f, 0.0f, -3.0f);

    set_update_function(cube, update);
    add_entity(scene, cube);

    Model *model = create_model(vertices, 24, indicies, 36);
    set_model(cube, model);

    light = create_light();
    set_ambient_color(light, 0.1f, 0.1f, 0.1f);
    set_diffuse_color(light, 0.2f, 0.2f, 0.2f);
    set_specular_color(light, 0.8f, 0.8f, 0.8f);
    add_light(scene, light);

    lamp = create_entity();
    set_emissive(lamp, 1.0f, 1.0f, 1.0f);
    set_scale(lamp, 0.1f);
    set_model(lamp, model);
    add_entity(scene, lamp);

    loop_window(window);

    destroy_entity(lamp);
    destroy_light(light);

    destroy_model(model);
    destroy_entity(cube);

    destroy_scene(scene);
    destroy_window(window);
}