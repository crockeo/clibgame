// Name: clibgame/components/position.hpp
//
// Description:
//   This is one of a number of default components in this library meant to keep
//   track of position in a 2D space.

#ifndef _CLIBGAME_COMPONENTS_POSITION_HPP_
#define _CLIBGAME_COMPONENTS_POSITION_HPP_

//////////////
// Includes //
#include <string>
#include <tuple>

#include "../eventing.hpp"
#include "../ecp.hpp"

//////////
// Code //

namespace clibgame {
    // The event for a position changing.
    class CPositionEvent : public Event {
    private:
        const std::string name;

    public:
        const float x, y, w, h;

        // Constructing a new CPositionEvent with a given owner name and a set
        // of values representing position and size.
        CPositionEvent(std::string,
                       float, float,
                       float, float);

        // Getting the type of this event.
        virtual std::string getEventType() const override;
    };

    // The component for tracking position.
    class CPosition : public Component {
    private:
        float x, y, w, h;
        bool doCollide;

        // Pushing the CPositionEvent for updated vertices.
        void pushEvent();

    public:
        // Creating a new CPosition with a specified x & y coordinate. It also
        // allows the option of whether or not this CPosition should be
        // considere for collision.
        CPosition(float, float, float, float,
                  bool);
        
        // Creating a new CPosition with a specified x & y coordinate.
        // Defaulting doCollision to false.
        CPosition(float, float, float, float);

        // Creating a new CPosition where the x & y coordinates are set to 0.
        CPosition();

        // Returning the name of this component - which is "clibgame_position".
        virtual std::string getName() const override;

        // Some accessor functions or something.
        std::tuple<float, float> getCoords() const;
        std::tuple<float, float> getSize() const;

        float getX() const;
        float getY() const;
        float getWidth() const;
        float getHeight() const;

        bool shouldDoCollide() const;

        // Some mutator functions or something.
        void translate(float, float);
        void resize(float, float);

        void setX(float);
        void setY(float);
        void setWidth(float);
        void setHeight(float);

        void setDoCollide(bool);
    };
}

#endif
