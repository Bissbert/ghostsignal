#ifndef TEXT_RENDERER_H
#define TEXT_RENDERER_H

#include <GL/gl.h>

// Initializes the text renderer, creates the font texture atlas.
void text_renderer_init();

// Renders a string of text at a given position.
// The (x, y) coordinates are in the modelview space.
void text_renderer_draw_string(const char *str, float x, float y, float scale);

// Cleans up resources used by the text renderer.
void text_renderer_cleanup();

#endif // TEXT_RENDERER_H
