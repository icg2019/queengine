#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 normal;



out vec3 normal_location;
out vec3 frag_loc;

uniform mat4 rotation;
uniform mat4 rotation2;


void main()
{
    frag_loc = vec3(gl_Position.x, gl_Position.y, gl_Position.z);
    normal_location = normal;

    gl_Position = rotation * rotation2 * vec4(aPos, 1.0);

}
