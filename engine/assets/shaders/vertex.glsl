#version 300 es

precision highp float;
precision highp int;

layout(location = 0) in vec3 uPosition;

uniform mat4 view;

out vec2 fragCoord;

void main() {
    gl_Position = view * vec4(uPosition, 1.0);

    fragCoord = gl_Position.xy;
}
