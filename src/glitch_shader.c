#include "glitch_shader.h"
#include "gl_loader.h"
#include "util.h"
#include <stdio.h>

// Uniform locations
static GLint u_time_loc;
static GLint u_intensity_loc;
static GLint u_resolution_loc;

// Screen dimensions
static int screen_width = 800;
static int screen_height = 600;

void glitch_shader_init(glitch_state *state) {
    state->intensity = 0.4f;
    state->last_glitch_time = 0.0;
    state->shader_program = load_shader("src/shaders/glitch.vert", "src/shaders/glitch.frag");

    if (state->shader_program == 0) {
        fprintf(stderr, "Failed to load glitch shader.\n");
        return;
    }

    // Get uniform locations
    u_time_loc = glGetUniformLocation(state->shader_program, "u_time");
    u_intensity_loc = glGetUniformLocation(state->shader_program, "u_intensity");
    u_resolution_loc = glGetUniformLocation(state->shader_program, "u_resolution");
}

void glitch_shader_draw(glitch_state *state) {
    // The glitch effect is drawn as a transparent overlay on a full-screen quad.
    // This requires setting up an orthographic projection.

    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    glOrtho(0, screen_width, 0, screen_height, -1, 1);

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    // Disable depth testing for the overlay
    glDisable(GL_DEPTH_TEST);

    // Activate shader
    glUseProgram(state->shader_program);

    // Update uniforms
    glUniform1f(u_time_loc, get_time_seconds());
    glUniform1f(u_intensity_loc, state->intensity);
    glUniform2f(u_resolution_loc, (float)screen_width, (float)screen_height);

    // Draw a quad that covers the entire screen
    glBegin(GL_QUADS);
    glVertex2f(0, 0);
    glVertex2f(screen_width, 0);
    glVertex2f(screen_width, screen_height);
    glVertex2f(0, screen_height);
    glEnd();

    // Deactivate shader
    glUseProgram(0);

    // Restore previous state
    glEnable(GL_DEPTH_TEST);
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();
}

void glitch_shader_reshape(int w, int h) {
    screen_width = w;
    screen_height = h;
}