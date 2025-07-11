# The name of the program to build
bin_PROGRAMS = ghostsignal

# The source files for the program
ghostsignal_SOURCES = \
    ghostsignal.c \
    radar_renderer.c \
    glitch_shader.c \
    binary_rain.c \
    util.c \
    gl_loader.c \
    text_renderer.c

# Link with required libraries
ghostsignal_LDADD = $(X11_LIBS) $(XSS_LIBS) $(GL_LIBS) $(GLU_LIBS) -lm

# Compiler flags
ghostsignal_CFLAGS = $(X11_CFLAGS) $(XSS_CFLAGS) $(GL_CFLAGS) $(GLU_CFLAGS)

# Where to install the program
# xscreensaver expects screensavers in a specific directory,
# often /usr/lib/xscreensaver/ or /usr/libexec/xscreensaver/
# The user can override this during the ./configure step
xscreensaverdir = $(libexecdir)/xscreensaver
xscreensaver_PROGRAMS = ghostsignal

# Let automake know that the 'shaders' directory contains data files
# that should be distributed with the source code, but not installed.
EXTRA_DIST = shaders/beam.vert shaders/beam.frag shaders/glitch.frag shaders/rain.frag shaders/text.vert shaders/text.frag
