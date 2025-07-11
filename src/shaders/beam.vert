// beam.vert
varying vec2 v_polar_coords; // r, theta

void main() {
    // Pass through the original vertex position
    gl_Position = ftransform();

    // Calculate polar coordinates from vertex position (assuming centered at 0,0)
    // This is a bit of a hack in old OpenGL, but works for a 2D disc.
    // The 'r' is the distance from the center, 'theta' is the angle.
    float r = length(gl_Vertex.xy);
    float theta = atan(gl_Vertex.y, gl_Vertex.x);

    v_polar_coords = vec2(r, theta);

    // Pass through texture coordinates for other potential effects
    gl_TexCoord[0] = gl_MultiTexCoord0;
}