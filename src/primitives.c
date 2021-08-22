#include "internal.h"
#include "math.h"

Model *build_cube(float size) {
    float s = size / 2;

    // clang-format off
    Vertex vertices[24] = {
        {{-s, -s, +s}, {+0.0, +0.0, +1.0}, { 0.0f, 1.0f }},  //  0 left  bottom front (front)
        {{+s, -s, +s}, {+0.0, +0.0, +1.0}, { 1.0f, 1.0f }},  //  1 right bottom front
        {{-s, +s, +s}, {+0.0, +0.0, +1.0}, { 0.0f, 0.0f }},  //  2 left  top    front
        {{+s, +s, +s}, {+0.0, +0.0, +1.0}, { 1.0f, 0.0f }},  //  3 right top    front
        {{-s, -s, +s}, {-1.0, +0.0, +0.0}, { 0.0f, 1.0f }},  //  4 left  bottom front (left)
        {{-s, +s, +s}, {-1.0, +0.0, +0.0}, { 1.0f, 1.0f }},  //  5 left  top    front
        {{-s, -s, -s}, {-1.0, +0.0, +0.0}, { 0.0f, 0.0f }},  //  6 left  bottom back
        {{-s, +s, -s}, {-1.0, +0.0, +0.0}, { 1.0f, 0.0f }},  //  7 left  top    back
        {{+s, -s, +s}, {+1.0, +0.0, +0.0}, { 0.0f, 1.0f }},  //  8 right bottom front (right)
        {{+s, -s, -s}, {+1.0, +0.0, +0.0}, { 1.0f, 1.0f }},  //  9 right bottom back
        {{+s, +s, +s}, {+1.0, +0.0, +0.0}, { 0.0f, 0.0f }},  // 10 right top    front
        {{+s, +s, -s}, {+1.0, +0.0, +0.0}, { 1.0f, 0.0f }},  // 11 right top    back
        {{-s, -s, -s}, {+0.0, +0.0, -1.0}, { 0.0f, 1.0f }},  // 12 left  bottom back  (back)
        {{-s, +s, -s}, {+0.0, +0.0, -1.0}, { 1.0f, 1.0f }},  // 13 left  top    back
        {{+s, -s, -s}, {+0.0, +0.0, -1.0}, { 0.0f, 0.0f }},  // 14 right bottom back
        {{+s, +s, -s}, {+0.0, +0.0, -1.0}, { 1.0f, 0.0f }},  // 15 right top    back
        {{-s, +s, +s}, {+0.0, +1.0, +0.0}, { 0.0f, 1.0f }},  // 16 left  top    front (top)
        {{+s, +s, +s}, {+0.0, +1.0, +0.0}, { 0.0f, 0.0f }},  // 18 right top    front
        {{-s, +s, -s}, {+0.0, +1.0, +0.0}, { 1.0f, 1.0f }},  // 17 left  top    back
        {{+s, +s, -s}, {+0.0, +1.0, +0.0}, { 1.0f, 0.0f }},  // 19 right top    back
        {{-s, -s, +s}, {+0.0, -1.0, +0.0}, { 0.0f, 1.0f }},  // 20 left  bottom front (bottom)
        {{-s, -s, -s}, {+0.0, -1.0, +0.0}, { 1.0f, 1.0f }},  // 21 left  bottom back
        {{+s, -s, +s}, {+0.0, -1.0, +0.0}, { 0.0f, 0.0f }},  // 22 right bottom front
        {{+s, -s, -s}, {+0.0, -1.0, +0.0}, { 1.0f, 0.0f }},  // 23 right bottom back
    };

    unsigned int indicies[36] = {
         0,  1,  2,  3,  2,  1,
         4,  5,  6,  7,  6,  5,
         8,  9, 10, 11, 10,  9,
        12, 13, 14, 15, 14, 13,
        16, 17, 18, 19, 18, 17,
        20, 21, 22, 23, 22, 21,
    };
    // clang-format on

    Model *model = create_model(vertices, 24, indicies, 36);
    return model;
}

Model *build_sphere(float radius, int stacks, int sectors) {
    unsigned int n_vertices = (stacks + 1) * (sectors + 1);
    unsigned int n_indices = (stacks * sectors * 6);

    Vertex *vertices = malloc(sizeof(Vertex) * n_vertices);
    unsigned int *indicies = malloc(sizeof(unsigned int) * n_indices);

    float stack_d = M_PI / stacks;
    float sector_d = 2 * M_PI / sectors;

    float stack_a, sector_a;
    float y, xz, x, z;

    for (int i = 0; i <= stacks; i++) {
        stack_a = stack_d * i;
        y = cosf(stack_a) / 2;
        xz = sinf(stack_a) / 2;

        for (int j = 0; j <= sectors; j++) {
            sector_a = sector_d * j;
            x = xz * sinf(sector_a);
            z = xz * cosf(sector_a);

            vertices[i * (sectors + 1) + j].position[0] = radius * x;
            vertices[i * (sectors + 1) + j].position[1] = radius * y;
            vertices[i * (sectors + 1) + j].position[2] = radius * z;

            vertices[i * (sectors + 1) + j].normal[0] = x;
            vertices[i * (sectors + 1) + j].normal[1] = y;
            vertices[i * (sectors + 1) + j].normal[2] = z;

            vertices[i * (sectors + 1) + j].texcoord[0] = sector_a / (2 * M_PI);
            vertices[i * (sectors + 1) + j].texcoord[1] = stack_a / M_PI;
        }
    }

    for (int stack = 0; stack < stacks; stack++) {
        for (int sector = 0; sector < sectors; sector++) {
            // clang-format off
            indicies[(stack * sectors + sector) * 6 + 0] = (stack + 1) * (sectors + 1) + (sector + 0); // left bottom
            indicies[(stack * sectors + sector) * 6 + 1] = (stack + 0) * (sectors + 1) + (sector + 0); // left top
            indicies[(stack * sectors + sector) * 6 + 2] = (stack + 1) * (sectors + 1) + (sector + 1); // right bottom
            
            indicies[(stack * sectors + sector) * 6 + 3] = (stack + 0) * (sectors + 1) + (sector + 1); // right top
            indicies[(stack * sectors + sector) * 6 + 4] = (stack + 1) * (sectors + 1) + (sector + 1); // right bottom
            indicies[(stack * sectors + sector) * 6 + 5] = (stack + 0) * (sectors + 1) + (sector + 0); // left top
            // clang-format on
        }
    }

    Model *model = create_model(vertices, n_vertices, indicies, n_indices);

    free(vertices);
    free(indicies);

    return model;
}
