// Name: clibgame/ecp.hpp
//
// Description:
//   This module provides an API for dealing with Entity Component Systems.

#ifndef _CLIBGAME_ECP_HPP_
#define _CLIBGAME_ECP_HPP_

//////////////
// Includes //
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <unordered_map>
#include <memory>
#include <string>
#include <set>

#include "renderer.hpp"
#include "res.hpp"

//////////
// Code //

namespace clibgame {
    class Component;
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

        // Initializing this component.
        virtual void init(GLFWwindow*, const ECP&, const Res&) { };

        // Updating a component.
        virtual void update(GLFWwindow*, const ECP&, float) { };

        // Rendering a component.
        virtual void render(Renderer&) const { };
    };

    // A type to represent the container of a set of components.
    class Entity {
    private:
        std::unordered_map<std::string, std::unique_ptr<Component>> components;
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

        // Checking if this entity has a component.
        bool hasComponent(std::string) const;

        // Getting a const ref to a component from this entity.
        const Component& getComponent(std::string) const throw(std::runtime_error);

        // Getting a ref to a component from the entity.
        Component& getComponent(std::string) throw(std::runtime_error);

        // Initializing the set of components in this Entity.
        void initComponents(GLFWwindow*, const ECP&, const Res&);

        // Updating the set of components.
        void updateComponents(GLFWwindow*, const ECP&, float);

        // Rendering the set of components.
        void renderComponents(Renderer&) const;
    };

    class ECP {
    private:
        std::unordered_map<std::string, Entity> entities;

    public:
        // Creating an empty ECP.
        ECP();

        // Adding a new entity with a set of components.
        void addEntity(std::string, std::set<Component*>);

        // Adding a new entity.
        void addEntity(std::string);

        // Checking if this ECP contains an entity by a given name.
        bool hasEntity(std::string) const;

        // Returning some iterators into the entity list.
        std::unordered_map<std::string, Entity>::const_iterator begin() const;
        std::unordered_map<std::string, Entity>::iterator begin();
        std::unordered_map<std::string, Entity>::const_iterator end() const;
        std::unordered_map<std::string, Entity>::iterator end();

        // Getting a list of names of the entities in this ECP.
        std::vector<std::string> getEntityNames() const;

        // Getting a const reference to an entity.
        const Entity& getEntity(std::string) const throw(std::runtime_error);

        // Getting a reference to an entity.
        Entity& getEntity(std::string) throw(std::runtime_error);

        // Initializing the set of entities.
        void initEntities(GLFWwindow*, const Res&);

        // Updating the set of entities.
        void updateEntities(GLFWwindow*, float);

        // Rendering the set of entities.
        void renderEntities(Renderer&) const;
    };
}

#endif
