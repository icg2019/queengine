void mainImage( out vec4 fragColor, in vec2 fragCoord )
{
    // Time varying pixel color
    vec3 col = vec3(1.0, 1.0, 1.0);

    // Output to screen
    fragColor = vec4(col, 0.1);
}
