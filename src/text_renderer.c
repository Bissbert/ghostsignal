#include "text_renderer.h"
#include "gl_loader.h"
#include "util.h"
#include <stdio.h>
#include <string.h>

// A simple, hard-coded 8x8 font for ASCII characters 32-127
static unsigned char font_8x8_basic[96][8];

static GLuint font_texture_id;
static GLuint text_shader_program;
static GLint u_text_color_loc;
static GLint u_text_sampler_loc;
static GLint a_vertex_loc;

static void generate_font_data();

void text_renderer_init() {
    generate_font_data();

    glGenTextures(1, &font_texture_id);
    glBindTexture(GL_TEXTURE_2D, font_texture_id);

    GLubyte texture_data[8][1024];
    memset(texture_data, 0, sizeof(texture_data));

    for (int i = 0; i < 96; i++) {
        for (int y = 0; y < 8; y++) {
            for (int x = 0; x < 8; x++) {
                if ((font_8x8_basic[i][y] >> (7 - x)) & 1) {
                    texture_data[y][i * 8 + x] = 255;
                }
            }
        }
    }

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_LUMINANCE, 1024, 8, 0, GL_LUMINANCE, GL_UNSIGNED_BYTE, texture_data);
    glBindTexture(GL_TEXTURE_2D, 0);

    text_shader_program = load_shader("src/shaders/text.vert", "src/shaders/text.frag");
    if (text_shader_program == 0) {
        fprintf(stderr, "Failed to load text shader.\n");
        return;
    }
    u_text_color_loc = glGetUniformLocation(text_shader_program, "u_text_color");
    u_text_sampler_loc = glGetUniformLocation(text_shader_program, "u_text_sampler");
    a_vertex_loc = glGetAttribLocation(text_shader_program, "a_vertex");
}

void text_renderer_draw_string(const char *str, float x, float y, float scale) {
    glUseProgram(text_shader_program);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, font_texture_id);
    glUniform4f(u_text_color_loc, 0.0f, 1.0f, 0.2f, 0.7f); // Neon green
    glUniform1i(u_text_sampler_loc, 0);

    glEnableVertexAttribArray(a_vertex_loc);

    float char_width = 8.0f * scale;
    float char_height = 8.0f * scale;
    float current_x = x;

    for (const char *p = str; *p; p++) {
        int char_index = *p - 32;
        if (char_index < 0 || char_index >= 96) {
            char_index = 0; // Default to space
        }

        float u = (float)(char_index * 8) / 1024.0f;
        float v = 0.0f;
        float u_width = 8.0f / 1024.0f;
        float v_height = 1.0f;

        GLfloat vertices[4][4] = {
            { current_x, y, u, v },
            { current_x + char_width, y, u + u_width, v },
            { current_x + char_width, y + char_height, u + u_width, v + v_height },
            { current_x, y + char_height, u, v + v_height }
        };

        glVertexAttribPointer(a_vertex_loc, 4, GL_FLOAT, GL_FALSE, 0, vertices);
        glDrawArrays(GL_QUADS, 0, 4);

        current_x += char_width;
    }

    glDisableVertexAttribArray(a_vertex_loc);
    glBindTexture(GL_TEXTURE_2D, 0);
    glUseProgram(0);
}

void text_renderer_cleanup() {
    glDeleteTextures(1, &font_texture_id);
    glDeleteProgram(text_shader_program);
}

static void generate_font_data() {
    memset(font_8x8_basic, 0, sizeof(font_8x8_basic));
    // '0'
    font_8x8_basic[16][0]=0x3C; font_8x8_basic[16][1]=0x66; font_8x8_basic[16][2]=0x6E; font_8x8_basic[16][3]=0x76;
    font_8x8_basic[16][4]=0x7A; font_8x8_basic[16][5]=0x66; font_8x8_basic[16][6]=0x3C; font_8x8_basic[16][7]=0x00;
    // '1'
    font_8x8_basic[17][0]=0x18; font_8x8_basic[17][1]=0x38; font_8x8_basic[17][2]=0x18; font_8x8_basic[17][3]=0x18;
    font_8x8_basic[17][4]=0x18; font_8x8_basic[17][5]=0x18; font_8x8_basic[17][6]=0x3C; font_8x8_basic[17][7]=0x00;
}