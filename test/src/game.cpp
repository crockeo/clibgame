#include "game.hpp"

//////////
// Code //

struct PositionEvent : public clibgame::Event {
    std::string name;
    float x, y;
    float w, h;

    PositionEvent(std::string name,
                   float x, float y,
                   float w, float h) {
        this->name = name;

        this->x = x;
        this->y = y;
        this->w = w;
        this->h = h;
    }

    std::string getEventType() const { return this->name; }
};

struct Position : public clibgame::Component {
    float x, y, w, h;
    bool alert;

    Position(float x, float y,
             float w, float h,
             bool alert) {
        this->x = x;
        this->y = y;

        this->w = w;
        this->h = h;

        this->alert = alert;
    }

    std::string getName() const { return "position"; }

    void translate(float dx, float dy) {
        this->x += dx;
        this->y += dy;

        if (this->alert)
            clibgame::ListenerManager::instance().alert(PositionEvent(this->getName(),
                                                                      this->x, this->y,
                                                                      this->w, this->h));
    }
};

struct PlayerController : public clibgame::Component {
    float speed;

    PlayerController(float speed) {
        this->speed = speed;
    }

    std::string getName() const { return "playerController"; }

    void update(GLFWwindow* window, const clibgame::ECP& ecp, float dt) {
        float dx = 0,
              dy = 0;

        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
            dy += speed;
        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
            dy -= speed;
        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
            dx -= speed;
        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
            dx += speed;

        if (dx != 0 || dy != 0) {
            Position& p = dynamic_cast<Position&>(this->getOwner().getComponent("position"));
            p.translate(dx, dy);
        }
    }
};

struct PlayerRender : public clibgame::Component,
                      public clibgame::Listener {
    clibgame::Texture* texture;
    clibgame::Shader* shader;
    GLuint vao, ebo;

    GLuint vbo1, vbo2;
    bool mode;

    std::vector<GLfloat> generateCoords(float x, float y,
                                        float w, float h) {
        std::vector<GLfloat> vertices = {
            x    , y    , 0, 0,
            x + w, y    , 1, 0,
            x + w, y + h, 1, 1,
            x    , y + h, 0, 1
        };

        return vertices;
    }

    void updateVertices(float x, float y, float w, float h) {
        auto vVertices = generateCoords(x, y, w, h);

        GLfloat aVertices[vVertices.size()];
        for (int i = 0; i < vVertices.size(); i++)
            aVertices[i] = vVertices.at(i);

        glBindBuffer(GL_ARRAY_BUFFER, this->mode ? vbo1 : vbo2);
        glBufferData(GL_ARRAY_BUFFER, sizeof(aVertices), aVertices, GL_DYNAMIC_DRAW);
        mode = !mode;
    }

    PlayerRender() {
        clibgame::ListenerManager::instance().registerListener(this, "position");

        texture = nullptr;
        shader  = nullptr;
        vao     = 0;
        vbo1    = 0;
        vbo2    = 0;
        ebo     = 0;
    }

    ~PlayerRender() {
        if (texture != nullptr)
            delete texture;
        if (shader != nullptr)
            delete shader;

        glDeleteVertexArrays(1, &this->vao);
        glDeleteBuffers(1, &this->vbo1);
        glDeleteBuffers(1, &this->vbo2);
        glDeleteBuffers(1, &this->ebo);
    }

    std::string getName() const { return "playerRender"; }

    void init(GLFWwindow* window, const clibgame::ECP& ecp, const clibgame::Res& res) {
        texture = new clibgame::Texture(res.getTexture("res/test.png"));
        shader = new clibgame::Shader(res.getShader("res/test"));

        glGenVertexArrays(1, &this->vao);
        glBindVertexArray(this->vao);

        glGenBuffers(1, &this->vbo1);
        glGenBuffers(1, &this->vbo2);
        this->updateVertices(0, 0, 0.1, 0.1);
        this->updateVertices(0, 0, 0.1, 0.1);

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
        glBindBuffer(GL_ARRAY_BUFFER, this->mode ? vbo2 : vbo1);
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

    void alert(const clibgame::Event&& e) {
        if (e.getEventType() == "position") {
            const PositionEvent&& pe = dynamic_cast<const PositionEvent&&>(e);
            //this->updateVertices(pe.x, pe.y,
                                 //pe.w, pe.h);
        }
    }
};

// Creating a new game.
Game::Game() {
    this->addEntity("player");
    this->getEntity("player").addComponent(new Position(0, 0, 0.1, 0.1, true));
    this->getEntity("player").addComponent(new PlayerController(0.5));
    this->getEntity("player").addComponent(new PlayerRender());
}
