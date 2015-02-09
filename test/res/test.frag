#version 330

uniform sampler2D in_texture;
in vec2 pass_texCoords;

out vec4 out_color;

void main() {
    out_color = vec4(texture(in_texture, pass_texCoords));
}
