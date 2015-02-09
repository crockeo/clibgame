#include "rendering.hpp"

//////////////
// Includes //
#include <clibgame.hpp>
#include <GL/glew.h>

//////////
// Code //

struct TextureRender {
    GLuint vbo;
    GLuint ebo;
    clibgame::Texture* texture;
    clibgame::Shader* shader;

    // Construcitng a new TextureRender.
    TextureRender(float x, float y, float w, float h) {
        this->texture = new clibgame::Texture("res/test.png");
        this->shader = new clibgame::Shader("res/test");

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
        // TODO: Actually perform a render.
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
