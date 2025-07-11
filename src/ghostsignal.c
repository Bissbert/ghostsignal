/*
 * ghostsignal.c - A moody, techno-military screensaver.
 *
 * Author: Your Name <your-email@example.com>
 */

#include <X11/Xlib.h>
#include <X11/extensions/scrnsaver.h>
#include <GL/gl.h>
#include <GL/glx.h>
#include <GL/glu.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#include "util.h"
#include "radar_renderer.h"
#include "glitch_shader.h"
// #include "silhouette.h"
#include "binary_rain.h"
#include "gl_loader.h"
#include "text_renderer.h"

// Forward declarations for xscreensaver hooks
void ghostsignal_init(Display *dpy, Window win);
void ghostsignal_draw(Display *dpy, Window win);
void ghostsignal_reshape(Display *dpy, Window win, int w, int h);
void ghostsignal_free(Display *dpy, Window win);

typedef struct {
    Display *dpy;
    Window win;
    int width, height;

    // Component states
    radar_state radar;
    glitch_state glitch;
    // silhouette_state silhouette;
    binary_rain_state rain;

    // Add other global state here
    double start_time;

} ghostsignal_state;

// Global state variable
static ghostsignal_state *gs_state = NULL;

// Main xscreensaver entry point
int main(int argc, char *argv[]) {
    // This is a simplified main function. A real xscreensaver module
    // has more complex argument parsing.
    Display *dpy;
    Window win;

    dpy = XOpenDisplay(NULL);
    if (dpy == NULL) {
        fprintf(stderr, "Cannot open display\n");
        exit(1);
    }

    win = XDefaultRootWindow(dpy);

    // Look for a -root argument
    for (int i = 1; i < argc; i++) {
        if (!strcmp(argv[i], "-root")) {
            // In a real scenario, you'd parse more options
        }
    }

    XWindowAttributes wa;
    XGetWindowAttributes(dpy, win, &wa);

    ghostsignal_init(dpy, win);
    ghostsignal_reshape(dpy, win, wa.width, wa.height);

    while (1) {
        ghostsignal_draw(dpy, win);
        glXSwapBuffers(dpy, win);
        // A real screensaver would have a delay here and handle X events
        usleep(16666); // ~60 FPS
    }

    ghostsignal_free(dpy, win);
    XCloseDisplay(dpy);
    return 0;
}


void ghostsignal_init(Display *dpy, Window win) {
    gs_state = (ghostsignal_state *)calloc(1, sizeof(ghostsignal_state));
    if (!gs_state) {
        fprintf(stderr, "Failed to allocate memory for state\n");
        exit(1);
    }

    gs_state->dpy = dpy;
    gs_state->win = win;
    gs_state->start_time = get_time_seconds();

    // Seed the random number generator
    srand(time(NULL));

    // Load OpenGL functions
    if (!load_gl_functions()) {
        fprintf(stderr, "Failed to load OpenGL functions\n");
        exit(1);
    }

    // Initialize components
    radar_renderer_init(&gs_state->radar);
    glitch_shader_init(&gs_state->glitch);
    // silhouette_init(&gs_state->silhouette, "data/soldier_silhouette.png");
    binary_rain_init(&gs_state->rain, "data/quote.txt");

    // Basic OpenGL setup
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glShadeModel(GL_SMOOTH);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

void ghostsignal_draw(Display *dpy, Window win) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Update components
    // silhouette_update(&gs_state->silhouette);
    binary_rain_update(&gs_state->rain);

    // Draw components
    radar_renderer_draw(&gs_state->radar);
    // silhouette_draw(&gs_state->silhouette);
    binary_rain_draw(&gs_state->rain);
    glitch_shader_draw(&gs_state->glitch); // Glitch is an overlay
}

void ghostsignal_reshape(Display *dpy, Window win, int w, int h) {
    gs_state->width = w;
    gs_state->height = h;

    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (GLfloat)w / (GLfloat)h, 0.1, 100.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // Inform components of the new size
    radar_renderer_reshape(w, h);
    glitch_shader_reshape(w, h);
    // silhouette_reshape(w, h);
    binary_rain_reshape(w, h);
}

void ghostsignal_free(Display *dpy, Window win) {
    free(gs_state);
    gs_state = NULL;
}
