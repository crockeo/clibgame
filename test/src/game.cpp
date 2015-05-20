#include "game.hpp"

//////////////
// Includes //
#include "renderer.hpp"

//////////
// Code //

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
            clibgame::CPosition& p = dynamic_cast<clibgame::CPosition&>(this->getOwner().getComponent("clibgame_position"));
            p.translate(dx * dt, dy * dt);
        }
    }
};

struct PlayerRender : public clibgame::Component,
                      public clibgame::Listener {
    clibgame::Texture* texture;
    clibgame::Shader* shader;
    float x, y, w, h;

    void updateVertices(float x, float y, float w, float h) {
        this->x = x;
        this->y = y;
        this->w = w;
        this->h = h;
    }

    PlayerRender() {
        clibgame::ListenerManager::instance().registerListener(this, "clibgame_position_player");

        texture = nullptr;
        shader  = nullptr;
    }

    ~PlayerRender() {
        if (texture != nullptr)
            delete texture;
        if (shader != nullptr)
            delete shader;
    }

    std::string getName() const { return "playerRender"; }

    void init(GLFWwindow* window, const clibgame::ECP& ecp, const clibgame::Res& res) {
        texture = new clibgame::Texture(res.getTexture("res/test.png"));
        shader = new clibgame::Shader(res.getShader("res/test"));
    }
    virtual void render(clibgame::Renderer& cRenderer) const override {
        Renderer& renderer = dynamic_cast<Renderer&>(cRenderer);
        Render render;

        render.coordinates = generateCoords(*texture, x, y, w, h);
        render.order = STANDARD_ORDER;
        render.texable = texture;
        render.shader = shader;

        renderer.addRender(render);
    }

    void alert(const clibgame::Event&& e) {
        if (e.getEventType() == "clibgame_position_player") {
            const clibgame::CPositionEvent&& pe = dynamic_cast<const clibgame::CPositionEvent&&>(e);
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
    }
};

struct AnimRender : public clibgame::Component {
    clibgame::Animation* texture;
    clibgame::Shader* shader;
    std::string animName;

    const float x, y, w, h;

    AnimRender(std::string animName, float x) :
            x(x  ), y(0  ),
            w(0.1), h(0.1) {
        this->animName = animName;

        texture = nullptr;
        shader  = nullptr;
    }

    ~AnimRender() {
        if (texture != nullptr)
            delete texture;
        if (shader != nullptr)
            delete shader;
    }

    std::string getName() const { return "animRender"; }

    void init(GLFWwindow* window, const clibgame::ECP& ecp, const clibgame::Res& res) {
        texture = new clibgame::Animation(res.getAnimation(this->animName));
        shader = new clibgame::Shader(res.getShader("res/test"));
    }

    virtual void render(clibgame::Renderer& cRenderer) const override {
        Renderer& renderer = dynamic_cast<Renderer&>(cRenderer);
        Render render;

        render.coordinates = generateCoords(*texture, x, y, w, h);
        render.order = STANDARD_ORDER;
        render.texable = texture;
        render.shader = shader;

        renderer.addRender(render);
    }
};

// Creating a new game.
Game::Game() {
    this->addEntity("player");
    this->getEntity("player").addComponent(new clibgame::CPosition(0, 0, 0.1, 0.1));
    this->getEntity("player").addComponent(new PlayerController(4));
    this->getEntity("player").addComponent(new PlayerRender());

    this->addEntity("sometext");
    this->getEntity("sometext").addComponent(new TextRender("res/testfont.ttf", "Testing!", 10, 10));

    this->addEntity("testanim");
    this->getEntity("testanim").addComponent(new AnimRender("testanim", 0));

    this->addEntity("boundanim");
    this->getEntity("boundanim").addComponent(new AnimRender("boundanim", 0.1f));
}
