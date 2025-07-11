#ifndef RADAR_RENDERER_H
#define RADAR_RENDERER_H

#include <GL/gl.h>

typedef struct {
    float rotation_speed;
    float beam_width;
    float pulse_interval;
    // Add other radar-specific state here
    float current_angle;
    GLuint shader_program;
} radar_state;

void radar_renderer_init(radar_state *state);
void radar_renderer_draw(radar_state *state);
void radar_renderer_reshape(int w, int h);

#endif // RADAR_RENDERER_H
