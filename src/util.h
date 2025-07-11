#ifndef UTIL_H
#define UTIL_H

#include <GL/gl.h>

// Timer function
double get_time_seconds();

// Random number functions
float random_float(float min, float max);
int random_int(int min, int max);

// Shader loading function
GLuint load_shader(const char *vertex_path, const char *fragment_path);

#endif // UTIL_H
