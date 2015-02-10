#include "rendering.hpp"

//////////////
// Includes //
#include <clibgame.hpp>
#include <GL/glew.h>

//////////
// Code //

#include <iostream>

struct TextureRender {
    GLuint vao;
    GLuint vbo;
    GLuint ebo;
    clibgame::Texture* texture;
    clibgame::Shader* shader;

    // Construcitng a new TextureRender.
    TextureRender(float x, float y, float w, float h) {
        this->texture = new clibgame::Texture("res/test.png");
        this->shader = new clibgame::Shader("res/test");

        // Making the VAO.
        glGenVertexArrays(1, &this->vao);

        // Making the VBO.
        glGenBuffers(1, &this->vbo);
        glBindBuffer(GL_ARRAY_BUFFER, this->vbo);

        GLfloat coords[] {
            x    , y    , 0, 0,
            x + w, y    , 1, 0,
            x + w, y + h, 1, 1,
            x    , y + h, 0, 1
        };

        glBufferData(GL_ARRAY_BUFFER, sizeof(coords), coords, GL_STATIC_DRAW);

        // Making the EBO.
        glGenBuffers(1, &this->ebo);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->ebo);

        GLuint order[] {
            0, 1, 2,
            2, 3, 0
        };

        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(order), order, GL_STATIC_DRAW);
    }

    // Cleaning this bad boy up.
    ~TextureRender() {
        glDeleteBuffers(1, &this->vbo);
        glDeleteBuffers(1, &this->ebo);
        delete this->texture;
        delete this->shader;
    }

    // Rendering the TextureRender.
    void render() {
        glBindVertexArray(this->vao);
        glBindBuffer(GL_ARRAY_BUFFER, this->vbo);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->ebo);

        glUseProgram(this->shader->getShaderID());

        // Initializing the coordinates.
        GLint coordAttrib = glGetAttribLocation(this->shader->getShaderID(), "in_coordinates");

        glEnableVertexAttribArray(coordAttrib);
        glVertexAttribPointer(coordAttrib, 4, GL_FLOAT, GL_FALSE, 0, 0);

        // Initializing the texture.
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, this->texture->getTextureID());
        glUniform1i(glGetUniformLocation(this->shader->getShaderID(), "in_tex"), 0);

        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    }
};

// The global textureRender.
static TextureRender* textureRender;

// Preparing a render.
void prepareRendering() {
    textureRender = new TextureRender(-0.5, -0.5, 1, 1);
}

// Performing a single render.
void doRendering() {
    textureRender->render();
}

// Cleaning up the rendering.
void cleanRendering() {
    delete textureRender;
}
