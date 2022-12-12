#version 100
precision mediump float;
attribute vec4 vertex;

void main(void) {
    vec4 pos = vertex;
    gl_Position = pos;
}