// text.vert
// Pass-through shader for 2D text rendering

attribute vec4 a_vertex; // {x, y, u, v}
varying vec2 v_tex_coords;

void main() {
    // The vertex position is passed directly in screen coordinates
    gl_Position = gl_ProjectionMatrix * gl_ModelViewMatrix * vec4(a_vertex.xy, 0.0, 1.0);
    v_tex_coords = a_vertex.zw;
}
