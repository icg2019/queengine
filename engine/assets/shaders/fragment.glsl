
void mainImage( out vec4 fragColor, in vec2 fragCoord )
{
    // Normalized pixel coordinates (from 0 to 1)
    vec2 uv = fragCoord/iResolution.xy;

    // Time varying pixel color
    vec3 col = 0.5 + 0.5*cos((iTime*5.0)+uv.xyx+vec3(0,2,4));

    // Output to screen
    fragColor = vec4(col, 0.2);
}
