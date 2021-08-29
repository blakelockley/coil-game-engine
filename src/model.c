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

Model *load_model(const char *path) {
    FILE *file = fopen(path, "r");

    if (file == NULL) {
        fprintf(stderr, "Failed to load model: %s\n", path);
        return NULL;
    }

    char *line = NULL;
    size_t len = 0;

    float *positions = NULL, *normals = NULL, *textures = NULL;
    size_t positions_n = 0, normals_n = 0, textures_n = 0;

    Vertex *vertices = NULL;
    size_t vertices_n = 0;

    unsigned int *indicies = NULL;
    size_t indicies_n = 0;

    while (getline(&line, &len, file) != EOF) {
        if (strncmp(line, "v ", 2) == 0) {
            float x, y, z;
            sscanf(line, "v  %f %f %f", &x, &y, &z);

            positions = realloc(positions, sizeof(float) * 3 * (positions_n + 3));

            positions[positions_n + 0] = x;
            positions[positions_n + 1] = y;
            positions[positions_n + 2] = z;
            positions_n += 3;

        } else if (strncmp(line, "vn ", 3) == 0) {
            float x, y, z;
            sscanf(line, "vn  %f %f %f", &x, &y, &z);

            normals = realloc(normals, sizeof(float) * 3 * (normals_n + 3));

            normals[normals_n + 0] = x;
            normals[normals_n + 1] = y;
            normals[normals_n + 2] = z;
            normals_n += 3;

        } else if (strncmp(line, "vt ", 3) == 0) {
            float u, v;
            sscanf(line, "vt  %f %f", &u, &v);

            textures = realloc(textures, sizeof(float) * 2 * (textures_n + 2));

            textures[textures_n + 0] = u;
            textures[textures_n + 1] = v;
            textures_n += 2;

        } else if (strncmp(line, "f ", 2) == 0) {
            unsigned int ap, at, an;  // a = vertex, p = position, t = texture, n = normal
            unsigned int bp, bt, bn;
            unsigned int cp, ct, cn;

            sscanf(line, "f %u/%u/%u %u/%u/%u %u/%u/%u", &ap, &at, &an, &bp, &bt, &bn, &cp, &ct, &cn);

            Vertex a, b, c;

            // Vertex a
            a.position[0] = positions[3 * (ap - 1) + 0];
            a.position[1] = positions[3 * (ap - 1) + 1];
            a.position[2] = positions[3 * (ap - 1) + 2];

            a.normal[0] = normals[3 * (an - 1) + 0];
            a.normal[1] = normals[3 * (an - 1) + 1];
            a.normal[2] = normals[3 * (an - 1) + 2];

            a.texcoord[0] = textures[2 * (at - 1) + 0];
            a.texcoord[1] = textures[2 * (at - 1) + 1];

            // Vertex b
            b.position[0] = positions[3 * (bp - 1) + 0];
            b.position[1] = positions[3 * (bp - 1) + 1];
            b.position[2] = positions[3 * (bp - 1) + 2];

            b.normal[0] = normals[3 * (bn - 1) + 0];
            b.normal[1] = normals[3 * (bn - 1) + 1];
            b.normal[2] = normals[3 * (bn - 1) + 2];

            b.texcoord[0] = textures[2 * (bt - 1) + 0];
            b.texcoord[1] = textures[2 * (bt - 1) + 1];

            // Vertex c
            c.position[0] = positions[3 * (cp - 1) + 0];
            c.position[1] = positions[3 * (cp - 1) + 1];
            c.position[2] = positions[3 * (cp - 1) + 2];

            c.normal[0] = normals[3 * (cn - 1) + 0];
            c.normal[1] = normals[3 * (cn - 1) + 1];
            c.normal[2] = normals[3 * (cn - 1) + 2];

            c.texcoord[0] = textures[2 * (ct - 1) + 0];
            c.texcoord[1] = textures[2 * (ct - 1) + 1];

            vertices = realloc(vertices, sizeof(Vertex) * (vertices_n + 3));
            vertices[vertices_n + 0] = a;
            vertices[vertices_n + 1] = b;
            vertices[vertices_n + 2] = c;
            vertices_n += 3;

            indicies = realloc(indicies, sizeof(unsigned int) * (indicies_n + 3));
            indicies[indicies_n + 0] = vertices_n - 3;
            indicies[indicies_n + 1] = vertices_n - 2;
            indicies[indicies_n + 2] = vertices_n - 1;
            indicies_n += 3;
        }
    }

    Model *model = create_model(vertices, vertices_n, indicies, indicies_n);

    free(positions);
    free(normals);
    free(textures);

    free(vertices);
    free(indicies);

    free(line);

    return model;
}