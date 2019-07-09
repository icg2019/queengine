#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 color;
layout (location = 2) in vec2 text_coord;

out vec3 v_color;
out vec2  v_text_coord;

void main()
{
    gl_Position = vec4(aPos, 1.0);
    v_color = color;
    v_text_coord = text_coord;

}
