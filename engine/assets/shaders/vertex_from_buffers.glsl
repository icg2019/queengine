#version 300 es
layout (location = 0) in vec3 uPosition;
layout (location = 1) in vec2 tex_coords;

out vec2 fragCoord;
out vec2 texCoord;
out vec3 frag_loc;

uniform mat4 rotation;
uniform mat4 rotation2;

void main()
{
    gl_Position = rotation * rotation2 * vec4(uPosition, 1.0);
    frag_loc = gl_Position.xyz;
    texCoord = tex_coords;
    fragCoord = (gl_Position.xy - vec2(-1, -1)) / vec2(2, 2);
}
