#ifndef GLITCH_SHADER_H
#define GLITCH_SHADER_H

#include <GL/gl.h>

typedef struct {
    float intensity;
    // Add other glitch-specific state here
    GLuint shader_program;
    double last_glitch_time;
} glitch_state;

void glitch_shader_init(glitch_state *state);
void glitch_shader_draw(glitch_state *state);
void glitch_shader_reshape(int w, int h);

#endif // GLITCH_SHADER_H
