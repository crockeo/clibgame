#version 330

uniform sampler2D in_tex;
uniform vec4 in_color;

in vec2 pass_texCoords;
out vec4 out_color;

void main() {
    out_color = vec4(1, 1, 1, texture(in_tex, pass_texCoords).r) * in_color;
}
