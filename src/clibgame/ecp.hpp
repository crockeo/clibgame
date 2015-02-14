// Name: clibgame/ecp.hpp
//
// Description:
//   This module provides an API for dealing with Entity Component Systems.

#ifndef _CLIBGAME_ECP_HPP_
#define _CLIBGAME_ECP_HPP_

//////////////
// Includes //
#include <memory>
#include <string>
#include <map>
#include <set>

//////////
// Code //

namespace clibgame {
    struct Component;
    class Entity;
    class ECP;

    // The type to represent a single component in an entity.
    class Component {
    private:
        Entity* owner;

    public:
        // Creating a component with a set owner already.
        Component(Entity*);

        // Creating a Component without an owner.
        Component();

        // Virtual destructor.
        virtual ~Component() { };

        // Checking if this component has an owner.
        bool hasOwner() const;

        // Setting the owner of this Component.
        void setOwner(Entity*);

        // Getting a reference to the owner.
        Entity& getOwner();

        // Getting a const reference to the owner.
        const Entity& getOwner() const;

        // Getting the name of the component.
        virtual std::string getName() const = 0;

        // Updating a component.
        virtual void update(const ECP& ecp, float dt) { };

        // Rendering a component.a
        virtual void render() const { };
    };

    // A type to represent the container of a set of components.
    class Entity {
    private:
        std::map<std::string, std::unique_ptr<Component>> components;
        std::string uid;

    public:
        // Constructing a new Entity with all of its data set.
        Entity(std::string, std::set<Component*>);

        // Constructing a new Entity with no components.
        Entity(std::string);

        // Deleting the copy constructor.
        Entity(const Entity&) = delete;

        // Virtual destructor so things don't break.
        virtual ~Entity() { }

        // Deleting the assignment operator.
        Entity& operator=(const Entity&) = delete;

        // Getting the UID of the 
        std::string getUID() const;

        // Adding a component to this entity.
        void addComponent(Component*);

        // Removing a component from this entity.
        void removeComponent(Component*);

        // Updating the set of components.
        void updateComponents(const ECP&, float);

        // Rendering the set of components.
        void renderComponents() const;
    };

    class ECP {
    private:
        std::map<std::string, Entity> entities;

    public:
        // Creating an empty ECP.
        ECP();

        // Adding a new entity with a set of components.
        void addEntity(std::string, std::set<Component*>);

        // Adding a new entity.
        void addEntity(std::string);

        // Getting a const reference to an entity.
        const Entity& getEntity(std::string) const;

        // Getting a reference to an entity.
        Entity& getEntity(std::string);

        // Updating the set of entities.
        void updateEntities(float);

        // Rendering the set of entities.
        void renderEntities() const;
    };
}

#endif
