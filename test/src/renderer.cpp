#include "renderer.hpp"

//////////
// Code //

// Generating a vector of coordinates from a position and size.
std::vector<GLfloat> generateCoords(const clibgame::Texable& texable,
                                    float x, float y, float w, float h) {
    std::vector<GLfloat> tCoords = texable.getTextureCoords();

    std::vector<GLfloat> coords {
        x    , y    , tCoords[0], tCoords[1],
        x + w, y    , tCoords[2], tCoords[3],
        x + w, y + h, tCoords[4], tCoords[5],
        x    , y + h, tCoords[6], tCoords[7]
    };

    return coords;
}

// Performing a single render.
void Renderer::singleRender(Render render) const {
    // Moving the information into primative arrays.
    GLfloat coordinates[render.coordinates.size()];
    for (int i = 0; i < render.coordinates.size(); i++)
        coordinates[i] = render.coordinates.at(i);

    GLuint order[render.order.size()];
    for (int i = 0; i < render.order.size(); i++)
        order[i] = render.order.at(i);

    // Binding & buffering the appropriate information into the VBO and EBO.
    glBindVertexArray(vao);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(coordinates), coordinates, GL_DYNAMIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(order), order, GL_DYNAMIC_DRAW);

    glUseProgram(render.shader->getShaderID());

    // Initializing the coordinates.
    GLint coordAttrib = glGetAttribLocation(render.shader->getShaderID(), "in_coordinates");

    glEnableVertexAttribArray(coordAttrib);
    glVertexAttribPointer(coordAttrib, 4, GL_FLOAT, GL_FALSE, 0, 0);

    // Initializing the texture.
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, render.texable->getTextureID());
    glUniform1i(glGetUniformLocation(render.shader->getShaderID(), "in_tex"), 0);

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

// Creating an empty renderer.
Renderer::Renderer() :
        renders() { }

// Destructing this renderer.
Renderer::~Renderer() {
    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &vbo);
    glDeleteBuffers(1, &ebo);
}

// Adding a render to the next render.
void Renderer::addRender(Render render) { renders.push_back(render); }

// Initializing this render.
void Renderer::init(GLFWwindow* window, clibgame::Res& resources) {
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    glGenBuffers(1, &ebo);
}

// Rendering bunches of stuff.
void Renderer::render() const {
    for (auto r: renders)
        singleRender(r);
}

// Clearing out the last render.
void Renderer::clear() { renders.clear(); }
