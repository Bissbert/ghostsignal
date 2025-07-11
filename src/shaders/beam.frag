// beam.frag
varying vec2 v_polar_coords;

uniform float u_beam_angle_rad; // The center of the beam in radians
uniform float u_beam_width_rad; // The total width of the beam in radians
uniform vec4 u_beam_color;       // The color of the beam

void main() {
    float fragment_angle = v_polar_coords.y;

    // Calculate the shortest angular distance between the fragment and the beam center
    float delta = abs(fragment_angle - u_beam_angle_rad);
    float angular_dist = min(delta, 2.0 * 3.14159265 - delta);

    // Calculate intensity: 1.0 at the center, fading to 0.0 at the edges
    float half_width = u_beam_width_rad / 2.0;
    float intensity = 1.0 - smoothstep(0.0, half_width, angular_dist);

    // The base radar dish is a faint, transparent circle
    float dish_alpha = 0.15;

    // The final alpha is the dish plus the beam's intensity
    float final_alpha = dish_alpha + (intensity * 0.5);

    gl_FragColor = vec4(u_beam_color.rgb, final_alpha);
}