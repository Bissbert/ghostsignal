#ifndef BINARY_RAIN_H
#define BINARY_RAIN_H

#include <GL/gl.h>

#define MAX_RAIN_COLUMNS 100
#define MAX_COLUMN_LENGTH 40

typedef struct {
    float x, y;
    float speed;
    int length;
    char chars[MAX_COLUMN_LENGTH];
} rain_column;

typedef struct {
    // Add other binary_rain-specific state here
    GLuint shader_program;
    rain_column columns[MAX_RAIN_COLUMNS];
    char** quotes;
    int num_quotes;
} binary_rain_state;

void binary_rain_init(binary_rain_state *state, const char* quote_file);
void binary_rain_update(binary_rain_state *state);
void binary_rain_draw(binary_rain_state *state);
void binary_rain_reshape(int w, int h);

#endif // BINARY_RAIN_H
