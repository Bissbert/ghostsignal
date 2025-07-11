#include "binary_rain.h"
#include "util.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void binary_rain_init(binary_rain_state *state, const char* quote_file) {
    // TODO: Load quote_file into state->quotes
    printf("Binary Rain Init: Would load %s\n", quote_file);
    state->num_quotes = 0;
    state->quotes = NULL;

    for (int i = 0; i < MAX_RAIN_COLUMNS; i++) {
        state->columns[i].x = random_float(-1.0f, 1.0f) * 4.0f; // Spread them out
        state->columns[i].y = random_float(0.0f, 3.0f); // Start at different heights
        state->columns[i].speed = random_float(0.5f, 1.5f);
        state->columns[i].length = random_int(10, MAX_COLUMN_LENGTH);
        for (int j = 0; j < state->columns[i].length; j++) {
            state->columns[i].chars[j] = (rand() % 2 == 0) ? '0' : '1';
        }
    }
}

void binary_rain_update(binary_rain_state *state) {
    for (int i = 0; i < MAX_RAIN_COLUMNS; i++) {
        state->columns[i].y -= state->columns[i].speed * (1.0f / 60.0f);
        if (state->columns[i].y < -3.0f) { // Reset when off-screen
            state->columns[i].y = 3.0f;
        }
    }
}

void binary_rain_draw(binary_rain_state *state) {
    // This would require a text rendering system.
    // For now, we'll just draw some placeholder lines.
    glPushMatrix();
    glTranslatef(0.0f, 0.0f, -6.0f); // Behind everything

    glColor4f(0.0f, 1.0f, 0.2f, 0.7f);
    glLineWidth(2.0f);

    for (int i = 0; i < MAX_RAIN_COLUMNS; i++) {
        glPushMatrix();
        glTranslatef(state->columns[i].x, state->columns[i].y, 0.0f);
        
        // Draw a simple line to represent the rain column
        glBegin(GL_LINES);
        glVertex2f(0.0f, 0.0f);
        glVertex2f(0.0f, -0.05f * state->columns[i].length);
        glEnd();

        glPopMatrix();
    }

    glPopMatrix();
}

void binary_rain_reshape(int w, int h) {
    // Nothing to do here for now
}
