#version 300 es
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 tex_coords;

out vec2 fragCoord;

uniform mat4 rotation;
uniform mat4 rotation2;


void main()
{

    gl_Position = rotation * rotation2 * vec4(aPos, 1.0);
    // frag_loc = gl_Position.xyz;
    fragCoord = tex_coords;
}
