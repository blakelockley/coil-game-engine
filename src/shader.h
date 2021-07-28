#ifndef SHADER_H
#define SHADER_H

#include "internal.h"

struct _Shader {
    GLuint program;
};

typedef struct _Shader Shader;

GLuint load_shader(char *vert_filename, char *frag_filename);

#endif  // SHADER_H