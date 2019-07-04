#version 300 es

precision highp float;
precision highp int;

layout(location = 0) in vec3 uPosition;

out vec2 fragCoord;

void main() {
    gl_Position.xyz = uPosition;
    gl_Position.w = 1.0;

    fragCoord = gl_Position.xy;
}
