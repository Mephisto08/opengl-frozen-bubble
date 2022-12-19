#version 100
precision mediump float;
attribute vec4 Position;
attribute vec2 aTexCoord;
uniform mat4 Projection;
uniform mat4 View;
uniform mat4 Model;
varying vec2 TexCoord;

void main(void) {
    //gl_Position = Position;
    gl_Position = Projection * View * Model * Position;
    TexCoord = aTexCoord;
}