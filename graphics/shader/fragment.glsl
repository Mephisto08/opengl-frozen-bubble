#version 100
precision mediump float;
uniform vec4 Color;

void main(void) {
    gl_FragColor = Color;
}