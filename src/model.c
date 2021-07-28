#include "internal.h"

struct _Model {
    GLuint vao, ebo, vbo;
};

Model *create_model(vec3 vertices[], size_t vertices_n, unsigned int indicies[], size_t indicies_n) {
    Model *model = (Model *)malloc(sizeof(Model));

    glGenVertexArrays(1, &model->vao);
    glBindVertexArray(model->vao);

    glGenBuffers(1, &model->ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, model->ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * indicies_n, indicies, GL_STATIC_DRAW);

    glGenBuffers(1, &model->vbo);
    glBindBuffer(GL_ARRAY_BUFFER, model->vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vec3) * vertices_n, vertices, GL_STATIC_DRAW);

    // vPos
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vec3), (void *)0);

    return model;
}

void destroy_model(Model *model) {
    free(model);
}

void render_model(Model *model, GLuint shader) {
    glBindVertexArray(model->vao);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
}