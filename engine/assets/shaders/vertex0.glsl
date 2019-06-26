#version 300 es

precision highp float;
precision highp int;

layout(location = 0) in vec3 uPosition;

out vec2 fragCoord;

void main() {
    gl_Position.xyz = uPosition - vec3(0.25, 0.5, 0.0);
    gl_Position.w = 1.0;

    fragCoord = gl_Position.xy*gl_Position.xy;
}
