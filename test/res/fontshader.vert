#version 330

uniform vec2 in_size;

in vec4 in_coordinates;
out vec2 pass_texCoords;

void main() {
    vec2 temp_coordinates = in_coordinates.xy;

    temp_coordinates.x /= in_size.x / 2;
    temp_coordinates.x -= 1;

    temp_coordinates.y /= in_size.y / 2;
    temp_coordinates.y -= 1;

    pass_texCoords = in_coordinates.zw;

    gl_Position = vec4(temp_coordinates, 0, 1);
}
