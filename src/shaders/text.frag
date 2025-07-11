// text.frag
// Renders text from a single-channel font atlas

varying vec2 v_tex_coords;
uniform sampler2D u_text_sampler;
uniform vec4 u_text_color;

void main() {
    // Sample the texture (it's single-channel, so we use .r)
    float alpha = texture2D(u_text_sampler, v_tex_coords).r;

    // Set the fragment color
    gl_FragColor = vec4(u_text_color.rgb, u_text_color.a * alpha);
}
