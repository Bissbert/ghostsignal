#include "silhouette.h"
#include "util.h"
#include <stdio.h>
#include <math.h>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

// We need a PNG loading library for this.
// The configure.ac checks for libpng.
// #include <png.h>

void silhouette_init(silhouette_state *state, const char* image_path) {
    state->frequency = 0.02f; // spawn per second
    state->last_spawn_time = 0.0;
    state->is_active = 0;
    state->alpha = 0.0f;

    // TODO: Load soldier_silhouette.png into state->texture_id
    // For now, we'll just print a message.
    printf("Silhouette Init: Would load %s\n", image_path);
}

void silhouette_update(silhouette_state *state) {
    double current_time = get_time_seconds();
    if (!state->is_active) {
        if (current_time - state->last_spawn_time > 1.0 / state->frequency) {
            state->is_active = 1;
            state->alpha = 0.0f;
            state->last_spawn_time = current_time;
            // Pick a random position
            float angle = random_float(0, 360) * M_PI / 180.0;
            float radius = random_float(0.5, 1.5);
            state->x = cos(angle) * radius;
            state->y = sin(angle) * radius;
        }
    } else {
        // Fade in and out
        state->alpha += 1.0f / 60.0f; // Fade over 1 second
        if (state->alpha >= 1.0f) {
            state->alpha = 1.0f;
            // Start fading out after a delay (e.g. 2 seconds)
            // For simplicity, we fade out immediately now
            state->is_active = 0;
        }
    }
}


void silhouette_draw(silhouette_state *state) {
    if (state->is_active) {
        glPushMatrix();
        glTranslatef(state->x, state->y, -4.0f); // Behind the radar
        
        // Draw a placeholder quad
        glColor4f(0.8f, 0.8f, 0.8f, state->alpha);
        glBegin(GL_QUADS);
        glVertex2f(-0.2f, -0.5f);
        glVertex2f( 0.2f, -0.5f);
        glVertex2f( 0.2f,  0.5f);
        glVertex2f(-0.2f,  0.5f);
        glEnd();

        glPopMatrix();
    }
}

void silhouette_reshape(int w, int h) {
    // Nothing to do here for now
}
