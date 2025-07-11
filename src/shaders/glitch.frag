// glitch.frag
uniform float u_time;       // Time for animation
uniform float u_intensity;  // How strong the glitch is
uniform vec2  u_resolution; // Screen resolution

// 2D Random function
float random(vec2 st) {
    return fract(sin(dot(st.xy, vec2(12.9898, 78.233))) * 43758.5453123);
}

void main() {
    vec2 uv = gl_FragCoord.xy / u_resolution.xy;

    // --- Scan Line Effect ---
    float scanline_intensity = 0.05;
    float scanline = sin(uv.y * 800.0) * scanline_intensity;

    // --- Jitter Effect ---
    float jitter_amount = 0.005 * u_intensity;
    float jitter_speed = 10.0;
    float jitter = (random(vec2(u_time * jitter_speed, 0.0)) - 0.5) * jitter_amount;
    uv.x += jitter;

    // --- Noise Effect ---
    float noise_amount = 0.2 * u_intensity;
    float noise = (random(uv + u_time) - 0.5) * noise_amount;

    // The glitch is a transparent green overlay
    vec4 glitch_color = vec4(0.0, 1.0, 0.5, 0.0);

    // Combine effects
    // Only show glitches intermittently
    if (random(vec2(floor(u_time * 5.0), 0.0)) > 0.6) {
         glitch_color.a = (scanline + noise) * u_intensity;
    }

    gl_FragColor = glitch_color;
}