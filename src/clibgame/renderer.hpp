#ifndef _CLIBGAME_RENDERER_HPP_
#define _CLIBGAME_RENDERER_HPP_

namespace clibgame {
    // A central class to handle rendering.
    struct Renderer {
        // A virtual destructor such that derivative classes with constructors
        // don't cause accidental segfaults.
        virtual ~Renderer() { }

        // Rendering the scene according to some information inside the
        // renderer. 
        virtual void render() const = 0;

        // Clearing the last render from the renderer.
        virtual void clear() { };
    };

    // A derivative of Renderer that does nothing. Used to facilitate backwards
    // compatability.
    struct NullRenderer : public Renderer {
        // An empty constructor.
        NullRenderer() { }

        // A render function that does nothing.
        virtual void render() const override { };
    };
}

#endif
