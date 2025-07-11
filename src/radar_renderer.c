#include "radar_renderer.h"
#include "gl_loader.h"
#include "util.h"
#include <GL/gl.h>
#include <math.h>
#include <stdio.h>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

// Uniform locations
static GLint u_beam_angle_rad_loc;
static GLint u_beam_width_rad_loc;
static GLint u_beam_color_loc;

void radar_renderer_init(radar_state *state) {
    state->rotation_speed = 15.0f; // degrees per second
    state->beam_width = 25.0f;     // degrees
    state->pulse_interval = 2.0f;  // seconds
    state->current_angle = 0.0f;

    state->shader_program = load_shader("src/shaders/beam.vert", "src/shaders/beam.frag");
    if (state->shader_program == 0) {
        fprintf(stderr, "Failed to load radar shader.\n");
        // Handle error appropriately
        return;
    }

    // Get uniform locations
    u_beam_angle_rad_loc = glGetUniformLocation(state->shader_program, "u_beam_angle_rad");
    u_beam_width_rad_loc = glGetUniformLocation(state->shader_program, "u_beam_width_rad");
    u_beam_color_loc = glGetUniformLocation(state->shader_program, "u_beam_color");
}

void radar_renderer_draw(radar_state *state) {
    // This should be based on a proper time delta, but 1/60 is a fine approximation for now.
    double time_delta = 1.0 / 60.0;
    state->current_angle += state->rotation_speed * time_delta;
    if (state->current_angle > 360.0f) {
        state->current_angle -= 360.0f;
    }

    glPushMatrix();
    // Center the radar and move it back a bit
    glTranslatef(0.0f, 0.0f, -5.0f);

    // Activate the shader
    glUseProgram(state->shader_program);

    // Update uniforms
    // Note: The beam appears to rotate opposite to the dish, so we pass a negative angle.
    // The vertex shader calculates angles based on a static coordinate system.
    float beam_angle_rad = -state->current_angle * M_PI / 180.0f;
    float beam_width_rad = state->beam_width * M_PI / 180.0f;
    glUniform1f(u_beam_angle_rad_loc, beam_angle_rad);
    glUniform1f(u_beam_width_rad_loc, beam_width_rad);
    glUniform4f(u_beam_color_loc, 0.0f, 1.0f, 0.5f, 1.0f); // Neon green

    // Draw the radar dish geometry (a simple disc)
    // The fragment shader will handle coloring the dish and the beam.
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(0.0f, 0.0f); // Center point
    for (int i = 0; i <= 360; i++) {
        float angle = i * M_PI / 180.0f;
        glVertex2f(cos(angle) * 2.0f, sin(angle) * 2.0f);
    }
    glEnd();

    // Deactivate the shader
    glUseProgram(0);

    glPopMatrix();
}

void radar_renderer_reshape(int w, int h) {
    // Reshape logic is handled globally for now
}