#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 tex_coords;

out vec2 v_text_coord;

out vec3 frag_loc;

uniform mat4 rotation;
uniform mat4 rotation2;


void main()
{

    gl_Position = rotation * rotation2 * vec4(aPos, 1.0);
    frag_loc = gl_Position.xyz;
    v_text_coord = tex_coords;
}
