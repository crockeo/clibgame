#include "rendering.hpp"

//////////////
// Includes //
#include <clibgame.hpp>
#include <GL/glew.h>
#include <iostream>

//////////
// Code //

struct NothingEvent : public clibgame::Event {
    std::string getEventType() const { return "nothingEvent"; }
};

struct NothingListener : public clibgame::Listener {
    void alert(const clibgame::Event&& e) override {
        if (e.getEventType().compare("nothingEvent") == 0) {
            std::cout << "Got a nothing event!" << std::endl;
        }
    }
};

struct Render {
    GLuint vao;
    GLuint vbo;
    GLuint ebo;
    clibgame::Texable* texable;
    clibgame::Shader* shader;

    // Construcitng a new TextureRender.
    Render(clibgame::Texable* texable, clibgame::Shader* shader,
           float x, float y, float w, float h) {
        this->texable = texable;
        this->shader = shader;
        glGenVertexArrays(1, &this->vao);
        glGenBuffers(1, &this->vbo);
        glGenBuffers(1, &this->ebo);

        this->updateVertices(x, y, w, h);
    }

    // Cleaning this bad boy up.
    ~Render() {
        glDeleteBuffers(1, &this->vbo);
        glDeleteBuffers(1, &this->ebo);
        delete this->texable;
        delete this->shader;
    }

    // Updating the set of vertices and texture coordinates.
    void updateVertices(float x, float y, float w, float h) {
        glBindBuffer(GL_ARRAY_BUFFER, this->vbo);

        std::vector<GLfloat> tCoords = texable->getTextureCoords();
        std::vector<GLfloat> cCoords = {
            x    , y    ,
            x + w, y    ,
            x + w, y + h,
            x    , y + h
        };

        GLfloat coords[cCoords.size() * 2];
        int lvc = 0, evc = 0, tvc = 0;
        while (lvc < cCoords.size() * 2 && evc < cCoords.size()) {
            coords[lvc    ] = cCoords[evc    ];
            coords[lvc + 1] = cCoords[evc + 1];
            coords[lvc + 2] = tCoords[tvc    ];
            coords[lvc + 3] = tCoords[tvc + 1];

            lvc += 4;
            evc += 2;
            tvc += 2;
            if (tvc >= tCoords.size())
                tvc = 0;
        }

        glBufferData(GL_ARRAY_BUFFER, sizeof(coords), coords, GL_DYNAMIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->ebo);

        GLuint order[] {
            0, 1, 2,
            2, 3, 0
        };

        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(order), order, GL_DYNAMIC_DRAW);
    }

    // Rendering the TextureRender.
    void render() {
        clibgame::ListenerManager::instance().alert(NothingEvent());
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
        glBindTexture(GL_TEXTURE_2D, this->texable->getTextureID());
        glUniform1i(glGetUniformLocation(this->shader->getShaderID(), "in_tex"), 0);

        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    }
};

// The global textureRender.
static Render* textureRender;
static Render* texSheetRender;
static Render* animationRender;
static NothingListener* nl;

// Preparing a render.
void prepareRendering() {
    nl = new NothingListener();
    clibgame::ListenerManager::instance().registerListener(nl, "nothingEvent");

    textureRender = new Render(new clibgame::Texture("res/test.png"),
                               new clibgame::Shader("res/test"),
                               -1, -1, 0.2, 0.2);

    texSheetRender = new Render(new clibgame::TexSheet("res/test.png", 2, 2),
                                new clibgame::Shader("res/test"),
                                -0.75, -1, 0.2, 0.2);

    animationRender = new Render(new clibgame::Animation("res/test.png", 2, 2, 0.5f),
                                 new clibgame::Shader("res/test"),
                                 -1, -0.75, 0.2, 0.2);
}

// Performing a single render.
void doRendering() {
    textureRender->render();
    texSheetRender->render();

    animationRender->updateVertices(-1, -0.75, 0.2, 0.2);
    animationRender->render();
}

// Cleaning up the rendering.
void cleanRendering() {
    delete textureRender;
    delete texSheetRender;
    delete animationRender;
}
