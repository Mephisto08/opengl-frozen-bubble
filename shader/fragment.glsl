#version 100
precision mediump float;
uniform vec4 Color;
uniform sampler2D tex;
varying vec2 TexCoord;
void main(void) {
    gl_FragColor = texture2D(tex,TexCoord);
}