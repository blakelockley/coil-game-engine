#include "engine.h"

Model *cube_model;
Entity *cube, *lamp;
Light *light;
Camera *camera;

#define DIRECTION_NONE 0
#define DIRECTION_FORWARD 1
#define DIRECTION_LEFT 2
#define DIRECTION_RIGHT 3
#define DIRECTION_BACKWARD 4

int direction = DIRECTION_NONE;
float speed = 5.0f;

int dir_x = 0, dir_y = 0, dir_z = 0;
float pos_z = 0, pos_y, pos_x = 0;

float yaw, pitch;

void game_loop(Scene *scene, float delta) {
    static float rot_y = 0.0f;
    rot_y += delta;

    set_rotation(cube, 0, 1, 0, rot_y);

    float y = sin(pitch);
    float xz = cos(pitch);
    float x = xz * sin(yaw);
    float z = -xz * cos(yaw);
    set_camera_direction(camera, x, y, z);

    if (direction == DIRECTION_FORWARD) {
        pos_x += x * delta * speed;
        pos_y += y * delta * speed;
        pos_z += z * delta * speed;
    } else if (direction == DIRECTION_LEFT) {
        pos_x += z * delta * speed;
        pos_z -= x * delta * speed;
    } else if (direction == DIRECTION_RIGHT) {
        pos_x -= z * delta * speed;
        pos_z += x * delta * speed;
    } else if (direction == DIRECTION_BACKWARD) {
        pos_x -= x * delta * speed;
        pos_y -= y * delta * speed;
        pos_z -= z * delta * speed;
    }
    set_camera_position(camera, pos_x, pos_y, pos_z);

    set_position(lamp, sin(rot_y) * 3, 0, -2);
    set_light_position(light, sin(rot_y) * 3, 0, -2);
}

void mouse_position_handler(Scene *scene, double xpos, double ypos) {
    static float prev_x = 0, prev_y = 0;

    float dx = (xpos - prev_x) * 0.5;
    float dy = (ypos - prev_y) * 0.5;

    yaw += dx;
    pitch += dy;

    prev_x = xpos;
    prev_y = ypos;
}

void mouse_button_handler(Scene *scene, int button, int action, int mods) {
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
        printf("Left mouse button pressed\n");
}

void input_handler(Scene *scene, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_SPACE && action == GLFW_PRESS) {
        yaw = 0;
        pitch = 0;
    }

    if (key == GLFW_KEY_W && action == GLFW_PRESS)
        direction = DIRECTION_FORWARD;

    if (key == GLFW_KEY_S && action == GLFW_PRESS)
        direction = DIRECTION_BACKWARD;

    if (key == GLFW_KEY_A && action == GLFW_PRESS)
        direction = DIRECTION_LEFT;

    if (key == GLFW_KEY_D && action == GLFW_PRESS)
        direction = DIRECTION_RIGHT;

    if (action == GLFW_RELEASE && ((key == GLFW_KEY_W && direction == DIRECTION_FORWARD) ||
                                   (key == GLFW_KEY_S && direction == DIRECTION_BACKWARD) ||
                                   (key == GLFW_KEY_A && direction == DIRECTION_LEFT) ||
                                   (key == GLFW_KEY_D && direction == DIRECTION_RIGHT)))
        direction = DIRECTION_NONE;
}

int main(int argc, char **argv) {
    Window *window = create_window(640, 480, "Cube");

    Scene *scene = create_scene();
    set_loop_function(scene, game_loop);
    set_input_function(scene, input_handler);
    set_mouse_position_function(scene, mouse_position_handler);
    set_mouse_button_function(scene, mouse_button_handler);
    set_clear_color(scene, 0.5, 0.5, 0.5, 1.0);
    load_skybox(scene, "assets/skybox");
    add_scene(window, scene);

    camera = create_camera(0, 0, 0);
    set_camera(scene, camera);

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
    destroy_camera(camera);
    destroy_scene(scene);
    destroy_window(window);
}