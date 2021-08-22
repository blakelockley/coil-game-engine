#include "engine.h"

Model *cube_model;
Entity *cube, *lamp;
Light *light;

void game_loop(Scene *scene, float delta) {
    static float rot_y = 0.0f;
    rot_y += delta;

    // set_rotation(cube, 0, 1, 0, -rot_y);

    set_position(lamp, sin(rot_y) * 3, 0, -2);
    set_light_position(light, sin(rot_y) * 3, 0, -2);
}

int main(int argc, char **argv) {
    Window *window = create_window(640, 480, "Cube");

    Scene *scene = create_scene();
    set_loop_function(scene, game_loop);
    set_clear_color(scene, 0.0, 0.0, 0.0, 1.0);
    add_scene(window, scene);

    cube_model = build_cube(1.0f);

    cube = create_entity(cube_model);
    set_color(cube, 1.0f, 0.84f, 0.0f);
    set_position(cube, 0.0f, 0.0f, -3.0f);
    add_entity(scene, cube);

    light = create_light();
    set_light_mode(light, ENGINE_POINT_LIGHT);
    set_light_position(light, 2, 0, -3.0f);
    set_ambient_color(light, 0.4f, 0.4f, 0.4f);
    set_diffuse_color(light, 0.8f, 0.8f, 0.8f);
    set_specular_color(light, 1.0f, 1.0f, 1.0f);
    set_attenuation(light, 1.0f, 0.35f, 1.8f);
    add_light(scene, light);

    lamp = create_entity(cube_model);
    set_position(lamp, 2, 0, -3.0f);
    set_scale(lamp, 0.1f);
    set_emissive(lamp, 1.0f, 1.0f, 1.0f);
    add_entity(scene, lamp);

    loop_window(window);

    destroy_light(light);

    destroy_entity(lamp);
    destroy_entity(cube);

    destroy_model(cube_model);

    destroy_scene(scene);
    destroy_window(window);
}