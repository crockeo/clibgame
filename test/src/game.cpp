#include "game.hpp"

#include <iostream>

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
    float speed, dx, dy;

    PlayerController(float speed) {
        this->speed = speed;
        this->dx = 0;
        this->dy = 0;
    }

    std::string getName() const { return "playerController"; }

    void update(GLFWwindow* window, const clibgame::ECP& ecp, float dt) {
        bool my = false,
             mx = false;

        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
            this->dy += speed * dt;
            my = true;
        }

        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
            this->dy -= speed * dt;
            my = true;
        }

        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
            this->dx -= speed * dt;
            mx = true;
        }

        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
            this->dx += speed * dt;
            mx = true;
        }

        if (!my)
            this->dy -= this->dy * dt;
        if (!mx)
            this->dx -= this->dx * dt;

        if (dx != 0 || dy != 0) {
            Position& p = dynamic_cast<Position&>(this->getOwner().getComponent("position"));
            p.translate(dx * dt, dy * dt);
        }
    }
};

struct PlayerRender : public clibgame::Component,
                      public clibgame::Listener {
    clibgame::Texture* texture;
    clibgame::Shader* shader;
    GLuint vao, vbo, ebo;

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

        glBindBuffer(GL_ARRAY_BUFFER, this->vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(aVertices), aVertices, GL_DYNAMIC_DRAW);
    }

    PlayerRender() {
        clibgame::ListenerManager::instance().registerListener(this, "position");

        texture = nullptr;
        shader  = nullptr;
        vao     = 0;
        vbo     = 0;
        ebo     = 0;
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

    void init(GLFWwindow* window, const clibgame::ECP& ecp, const clibgame::Res& res) {
        texture = new clibgame::Texture(res.getTexture("res/test.png"));
        shader = new clibgame::Shader(res.getShader("res/test"));

        glGenVertexArrays(1, &this->vao);
        glBindVertexArray(this->vao);

        glGenBuffers(1, &this->vbo);
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

    void alert(const clibgame::Event&& e) {
        if (e.getEventType() == "position") {
            const PositionEvent&& pe = dynamic_cast<const PositionEvent&&>(e);
            this->updateVertices(pe.x, pe.y,
                                 pe.w, pe.h);
        }
    }
};

// A component to perform text rendering.
struct TextRender : public clibgame::Component {
    std::unique_ptr<clibgame::Shader> shader;
    std::unique_ptr<clibgame::Font> font;

    std::string fontName;
    GLFWwindow* window;
    std::string str;
    float x, y;
    GLuint ebo;
    GLuint vbo;

    // Constructing a new text render.
    TextRender(std::string fontName, std::string str, float x, float y) {
        this->font = nullptr;
        this->fontName = fontName;
        this->str = str;
        this->x = x;
        this->y = y;
        this->vbo = 0;
        this->ebo = 0;
    }

    // Deleting a text render.
    ~TextRender() {
        if (vbo != 0)
            glDeleteBuffers(1, &this->vbo);
        if (ebo != 0)
            glDeleteBuffers(1, &this->ebo);
    }

    std::string getName() const { return "textRender"; }

    void init(GLFWwindow* window, const clibgame::ECP& ecp, const clibgame::Res& res) {
        shader = std::unique_ptr<clibgame::Shader>(new clibgame::Shader(res.getShader("res/fontshader")));
        font   = std::unique_ptr<clibgame::Font>(new clibgame::Font(res.getFont(this->fontName)));

        this->window = window;

        glGenBuffers(1, &this->vbo);
        glGenBuffers(1, &this->ebo);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->ebo);
        GLuint order[] = { 0, 1, 2, 2, 3, 0 };
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(order), order, GL_STATIC_DRAW);
    }

    void render() const {
        FT_Face fontFace = this->font->getFontFace();

        glUseProgram(this->shader->getShaderID());

        // Getting the window size.
        int width, height;
        glfwGetWindowSize(window, &width, &height);
        glUniform2f(glGetUniformLocation(this->shader->getShaderID(), "in_size"), width, height);

        // Setting the text color.
        glUniform4f(glGetUniformLocation(this->shader->getShaderID(), "in_color"), 1, 1, 1, 1);

        // Loading up the texture.
        GLuint tex;
        glGenTextures(1, &tex);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, tex);
        glUniform1i(glGetUniformLocation(this->shader->getShaderID(), "in_tex"), 0);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

        // Loading up the VBO.
        glBindBuffer(GL_ARRAY_BUFFER, this->vbo);

        // Loading up the EBO.
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->ebo);

        // Setting the vertex coordinate.
        GLint posAttrib = glGetAttribLocation(this->shader->getShaderID(), "in_coordinates");
        glEnableVertexAttribArray(posAttrib);
        glVertexAttribPointer(posAttrib, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), 0);

        float tx = this->x,
              ty = this->y;

        FT_GlyphSlot g = fontFace->glyph;
        for (const char* ptr = str.c_str(); *ptr; ptr++) {
            if (FT_Load_Char(fontFace, *ptr, FT_LOAD_RENDER))
                continue;

            glTexImage2D(
                GL_TEXTURE_2D,
                0,
                GL_RED,
                g->bitmap.width,
                g->bitmap.rows,
                0,
                GL_RED,
                GL_UNSIGNED_BYTE,
                g->bitmap.buffer
            );

            float w = g->bitmap.width,
                  h = g->bitmap.rows;

            GLfloat box[] = {
                tx    , ty    , 0, 1,
                tx + w, ty    , 1, 1,
                tx + w, ty + h, 1, 0,
                tx    , ty + h, 0, 0
            };

            glBufferData(GL_ARRAY_BUFFER, sizeof(box), box, GL_DYNAMIC_DRAW);
            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

            tx += g->advance.x >> 6;
            ty += g->advance.y >> 6;
        }

        glDeleteTextures(1, &tex);

        GLenum err = glGetError();
        if (err != GL_NO_ERROR)
            std::cout << static_cast<int>(err) << std::endl;
    }
};

// Creating a new game.
Game::Game() {
    this->addEntity("player");
    this->getEntity("player").addComponent(new Position(0, 0, 0.1, 0.1, true));
    this->getEntity("player").addComponent(new PlayerController(1));
    this->getEntity("player").addComponent(new PlayerRender());

    this->addEntity("sometext");
    this->getEntity("sometext").addComponent(new TextRender("res/testfont.ttf", "Testing!", 10, 10));
}
