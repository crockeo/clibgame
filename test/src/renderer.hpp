#ifndef _RENDERER_HPP_
#define _RENDERER_HPP_

//////////////
// Includes //
#include <clibgame.hpp>

//////////
// Code //

// The standard order for which a rectangle ought to be rendered in OpenGL.
const static std::vector<GLuint> STANDARD_ORDER {
    0, 1, 2,
    2, 3, 0
};

// Generating a vector of coordinates from a position and size.
std::vector<GLfloat> generateCoords(const clibgame::Texable&, float, float, float, float);

// A struct that represents a render.
struct Render {
    std::vector<GLfloat> coordinates;
    std::vector<GLuint> order;

    clibgame::Texable* texable;
    clibgame::Shader* shader;
};

// A central renderer for the test game.
class Renderer : public clibgame::Renderer {
private:
    std::vector<Render> renders;
    GLuint vao, vbo, ebo;

    // Performing a single render.
    void singleRender(Render) const;

public:
    // Creating an empty renderer.
    Renderer();

    // Destructing this renderer.
    ~Renderer();

    // Adding a render to the next render.
    void addRender(Render);

    // Initializing this render.
    virtual void init(GLFWwindow*, clibgame::Res&) override;

    // Rendering bunches of stuff.
    virtual void render() const override;

    // Clearing out the last render.
    virtual void clear() override;
};

#endif
