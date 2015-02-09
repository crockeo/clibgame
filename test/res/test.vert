#version 330

in vec4 in_coordinates;
out vec2 pass_texCoords;

void main() {
    pass_texCoords = in_coordinates.zw;
    gl_Position = vec4(in_coordinates.xy, 0, 1);
}
