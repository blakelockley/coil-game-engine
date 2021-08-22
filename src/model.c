#include "internal.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

Model *create_model(Vertex vertices[], size_t vertices_n, unsigned int indicies[], size_t indicies_n) {
    Model *model = (Model *)malloc(sizeof(Model));
    model->has_texture = GL_FALSE;
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

    // vTexture
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)(sizeof(vec3) * 2));

    return model;
}

void set_texture(Model *model, const char *filename) {
    int width, height, n_channels;
    unsigned char *image = stbi_load(filename, &width, &height, &n_channels, STBI_rgb);

    if (image != NULL) {
        model->has_texture = GL_TRUE;

        glGenTextures(1, &model->texture);
        glBindTexture(GL_TEXTURE_2D, model->texture);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
        glGenerateMipmap(GL_TEXTURE_2D);
    } else {
        fprintf(stderr, "Failed to load texture: %s\n", filename);
    }

    stbi_image_free(image);
}

void destroy_model(Model *model) {
    glDeleteVertexArrays(1, &model->vao);
    glDeleteBuffers(1, &model->ebo);
    glDeleteBuffers(1, &model->vbo);

    free(model);
}

void render_model(Model *model, GLuint shader) {
    glBindVertexArray(model->vao);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, model->texture);

    glDrawElements(GL_TRIANGLES, model->count, GL_UNSIGNED_INT, 0);
}