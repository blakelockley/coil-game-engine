#include "internal.h"
#include "shader.h"

struct _Entity {
    Model *model;
    GLuint shader;

    void (*update_function)(Entity *, float);

    mat4x4 transform;

    vec3 position;
    quat rotation;
    float scale;
};

Entity *create_entity() {
    Entity *entity = malloc(sizeof(Entity));

    entity->model = NULL;
    entity->shader = load_shader("../../assets/static.vs", "../../assets/static.fs");

    entity->update_function = NULL;

    mat4x4_identity(entity->transform);
    entity->position[0] = 0;
    entity->position[1] = 0;
    entity->position[2] = 0;

    quat_identity(entity->rotation);

    entity->scale = 1;

    return entity;
}

void destroy_entity(Entity *entity) {
    free(entity);
}

void update_entity(Entity *entity, float delta) {
    if (entity->update_function)
        entity->update_function(entity, delta);
}

void render_entity(Entity *entity, Scene *scene) {
    glUseProgram(entity->shader);

    GLint transformation_matrix_loc = glGetUniformLocation(entity->shader, "transformationMatrix");
    GLint normal_matrix_loc = glGetUniformLocation(entity->shader, "normalMatrix");
    GLint projection_matrix_loc = glGetUniformLocation(entity->shader, "projectionMatrix");

    GLint light_pos_loc = glGetUniformLocation(entity->shader, "lightPos");
    GLint ambient_color_loc = glGetUniformLocation(entity->shader, "ambientColor");
    GLint diffuse_color_loc = glGetUniformLocation(entity->shader, "diffuseColor");
    GLint specular_color_loc = glGetUniformLocation(entity->shader, "specularColor");

    mat4x4 translation, rotation, scale;

    mat4x4_translate(translation, entity->position[0], entity->position[1], entity->position[2]);
    mat4x4_from_quat(rotation, entity->rotation);

    mat4x4_identity(scale);
    mat4x4_scale_aniso(scale, scale, entity->scale, entity->scale, entity->scale);

    mat4x4_identity(entity->transform);
    mat4x4_mul(entity->transform, entity->transform, translation);
    mat4x4_mul(entity->transform, entity->transform, rotation);
    mat4x4_mul(entity->transform, entity->transform, scale);

    mat4x4 normal_matrix, temp_matrix;
    mat4x4_transpose(temp_matrix, entity->transform);
    mat4x4_invert(normal_matrix, temp_matrix);

    glUniformMatrix4fv(transformation_matrix_loc, 1, GL_FALSE, (float *)entity->transform);
    glUniformMatrix4fv(normal_matrix_loc, 1, GL_FALSE, (float *)normal_matrix);
    glUniformMatrix4fv(projection_matrix_loc, 1, GL_FALSE, (float *)scene->projection);

    Light *light = scene->lights[0];

    glUniform3fv(light_pos_loc, 1, (float *)light->position);
    glUniform3fv(ambient_color_loc, 1, (float *)light->ambient_color);
    glUniform3fv(diffuse_color_loc, 1, (float *)light->diffuse_color);
    glUniform3fv(specular_color_loc, 1, (float *)light->specular_color);

    render_model(entity->model, entity->shader);
}

void set_model(Entity *entity, Model *model) {
    entity->model = model;
}

void set_update_function(Entity *entity, void (*update)(Entity *, float)) {
    entity->update_function = update;
}

void set_position(Entity *entity, float x, float y, float z) {
    entity->position[0] = x;
    entity->position[1] = y;
    entity->position[2] = z;
}

void set_rotation(Entity *entity, float x, float y, float z, float angle) {
    quat_identity(entity->rotation);

    vec3 axis = {x, y, z};
    quat_rotate(entity->rotation, angle, axis);
}

void set_scale(Entity *entity, float scale) {
    entity->scale = scale;
}
