#ifndef _CLIBGAME_RENDERER_HPP_
#define _CLIBGAME_RENDERER_HPP_

namespace clibgame {
    // A central class to handle rendering.
    struct Renderer {
        // Rendering the scene according to some information inside the
        // renderer. 
        virtual void render() const = 0;

        // Clearing the last render from the renderer.
        virtual void clear();
    };
}

#endif
