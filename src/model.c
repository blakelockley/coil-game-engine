#include "internal.h"

struct _Model {
    GLuint vao, ebo, vbo;
    GLsizei count;
};

Model *create_model(Vertex vertices[], size_t vertices_n, unsigned int indicies[], size_t indicies_n) {
    Model *model = (Model *)malloc(sizeof(Model));
    model->count = indicies_n;

    glGenVertexArrays(1, &model->vao);
    glBindVertexArray(model->vao);

    glGenBuffers(1, &model->ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, model->ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * indicies_n, indicies, GL_STATIC_DRAW);

    glGenBuffers(1, &model->vbo);
    glBindBuffer(GL_ARRAY_BUFFER, model->vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * vertices_n, vertices, GL_STATIC_DRAW);

    // vPos
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)0);

    // vNormal
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)sizeof(vec3));

    return model;
}

void destroy_model(Model *model) {
    free(model);
}

void render_model(Model *model, GLuint shader) {
    glBindVertexArray(model->vao);
    glDrawElements(GL_TRIANGLES, model->count, GL_UNSIGNED_INT, 0);
}