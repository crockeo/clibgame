#include "position.hpp"

//////////
// Code //

// Constructing a new CPositionEvent with a given owner name and a set
// of values representing position and size.
clibgame::CPositionEvent::CPositionEvent(std::string ownerName,
                                         float x, float y,
                                         float w, float h) :
        name("clibgame_position_" + ownerName),
        x(x), y(y),
        w(w), h(h) { }

// Getting the type of this event.
std::string clibgame::CPositionEvent::getEventType() const { return name; }

// Pushing the CPositionEvent for updated vertices.
void clibgame::CPosition::pushEvent() {
    clibgame::ListenerManager::instance().alert(CPositionEvent(getOwner().getUID(),
                                                               x, y,
                                                               w, h));
}

// Creating a new CPosition with a specified x & y coordinate.
clibgame::CPosition::CPosition(float x, float y) {
    this->x = x;
    this->y = y;
}

// Creating a new CPosition where the x & y coordinates are set to 0.
clibgame::CPosition::CPosition() {
    x = 0;
    y = 0;
}

// Returning the name of this component - which is "clibgame_position".
std::string clibgame::CPosition::getName() const {
    return "clibgame_position";
}

// Some accessor functions or something.
std::tuple<float, float> clibgame::CPosition::getCoords() const {
    return std::make_tuple(x, y);
}

std::tuple<float, float> clibgame::CPosition::getSize() const {
    return std::make_tuple(w, h);
}

float clibgame::CPosition::getX()      const { return x; }
float clibgame::CPosition::getY()      const { return y; }
float clibgame::CPosition::getWidth()  const { return w; }
float clibgame::CPosition::getHeight() const { return h; }

// Some mutator functions or something.
void clibgame::CPosition::translate(float dx, float dy) {
    x += dx;
    y += dy;

    if (dx != 0 || dy != 0)
        pushEvent();
}

void clibgame::CPosition::resize(float dw, float dh) {
    w += dw;
    h += dh;

    if (dw != 0 || dh != 0)
        pushEvent();
}

void clibgame::CPosition::setX     (float x) { translate(x - this->x, 0); }
void clibgame::CPosition::setY     (float y) { translate(0, y - this->y); }
void clibgame::CPosition::setWidth (float w) { resize(w - this->w, 0); }
void clibgame::CPosition::setHeight(float h) { resize(0, h - this->h); }
