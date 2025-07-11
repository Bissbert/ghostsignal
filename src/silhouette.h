#ifndef SILHOUETTE_H
#define SILHOUETTE_H

#include <GL/gl.h>

typedef struct {
    float frequency;
    // Add other silhouette-specific state here
    GLuint texture_id;
    GLuint shader_program;
    double last_spawn_time;
    float alpha;
    float x, y; // Position
    int is_active;
} silhouette_state;

void silhouette_init(silhouette_state *state, const char* image_path);
void silhouette_update(silhouette_state *state);
void silhouette_draw(silhouette_state *state);
void silhouette_reshape(int w, int h);

#endif // SILHOUETTE_H
