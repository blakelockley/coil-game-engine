#include "internal.h"
#include "shader.h"

struct _Entity {
    Model *model;
    GLuint shader;

    void (*update_function)(float delta);

    mat4x4 transform;
    void (*transform_function)(mat4x4 mat);
};

Entity *create_entity() {
    Entity *entity = malloc(sizeof(Entity));

    entity->model = NULL;
    entity->shader = load_shader("../../assets/static.vs", "../../assets/static.fs");

    entity->update_function = NULL;

    mat4x4_identity(entity->transform);
    entity->transform_function = NULL;

    return entity;
}

void destroy_entity(Entity *entity) {
    destroy_model(entity->model);
    free(entity);
}

void update_entity(Entity *entity, float delta) {
    if (entity->update_function)
        entity->update_function(delta);

    if (entity->transform_function)
        entity->transform_function(entity->transform);
}

void render_entity(Entity *entity, mat4x4 projection) {
    glUseProgram(entity->shader);

    GLint transformation_matrix_loc = glGetUniformLocation(entity->shader, "transformationMatrix");
    GLint projection_matrix_loc = glGetUniformLocation(entity->shader, "projectionMatrix");

    glUniformMatrix4fv(transformation_matrix_loc, 1, GL_FALSE, (float *)entity->transform);
    glUniformMatrix4fv(projection_matrix_loc, 1, GL_FALSE, (float *)projection);

    render_model(entity->model, entity->shader);
}

void set_model(Entity *entity, Model *model) {
    entity->model = model;
}

void set_update_function(Entity *entity, void (*update)(float)) {
    entity->update_function = update;
}

void set_transform_function(Entity *entity, void (*transform)(mat4x4)) {
    entity->transform_function = transform;
}
