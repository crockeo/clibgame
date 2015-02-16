#include "game.hpp"

//////////
// Code //

struct PlayerRender : public clibgame::Component {
    clibgame::Texture* texture;
    clibgame::Shader* shader;
    GLuint vao, vbo, ebo;

    PlayerRender() {
        texture = nullptr;
        shader = nullptr;
        vao = 0;
        vbo = 0;
        ebo = 0;
    }

    ~PlayerRender() {
        if (texture != nullptr)
            delete texture;
        if (shader != nullptr)
            delete shader;

        glDeleteVertexArrays(1, &this->vao);
        glDeleteBuffers(1, &this->vbo);
        glDeleteBuffers(1, &this->ebo);
    }

    std::string getName() const { return "playerRender"; }

    void init(const clibgame::ECP& ecp, const clibgame::Res& res) {
        texture = new clibgame::Texture(res.getTexture("res/test.png"));
        shader = new clibgame::Shader(res.getShader("res/test"));

        glGenVertexArrays(1, &this->vao);
        glBindVertexArray(this->vao);

        glGenBuffers(1, &this->vbo);
        glBindBuffer(GL_ARRAY_BUFFER, this->vbo);

        GLfloat vertices[] = {
            -0.5, -0.5, 0, 0,
             0.5, -0.5, 1, 0,
             0.5,  0.5, 1, 1,
            -0.5,  0.5, 0, 1
        };

        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);


        glGenBuffers(1, &this->ebo);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->ebo);

        GLuint order[] = {
            0, 1, 2,
            2, 3, 0
        };

        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(order), order, GL_STATIC_DRAW);
    }

    void render() const {
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

// Creating a new game.
Game::Game() {
    this->addEntity("player");
    this->getEntity("player").addComponent(new PlayerRender());
}
