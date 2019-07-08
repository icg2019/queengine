#version 300 es

precision highp float;
precision highp int;

layout(location = 0) in vec3 uPosition;

out vec2 fragCoord;

void main() {
    gl_Position = vec4(uPosition, 1.0);
    fragCoord = (gl_Position.xy - vec2(-1, -1)) / vec2(2, 2);
}
