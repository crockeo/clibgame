// Name     : clibgame/ecs.hpp
// Author(s): Cerek Hillen
// Init Date: 2016-05-29
// Edit Date: 2016-05-30
//
// Description:
//   An implementation of a platform-agnostic Entity/Component/System. This is
//   advantageous as you need not depend on platform-specific modules, but means
//   passing in external data (window information / user input) must be done
//   outside of this abstraction.

#ifndef _CLIBGAME_ECS_HPP_
#define _CLIBGAME_ECS_HPP_

//////////////
// Includes //
#include <unordered_map>
#include <string>

#include "core/uuid.hpp"

//////////
// Code //

namespace clibgame {
    namespace ecs {
        // Forward declarations of the types we're going to use in the ECS so
        // that we can intermix them in the definition of our code.
        class Component;
        class Entity;
        class System;
        class World;

        // A singular Component -- when updated it can either update itself or
        // other Components within its parent Entity, but does NOT have scope
        // on the entirety of the World.
        class Component {
        public:
            virtual ~Component() { }

            // Initializing this Component.
            virtual void init(Entity& owner) { }
            
            // Updating this Component.
            virtual void update(Entity& owner, float dt) { }

            // Rendering this Component.
            virtual void render(const Entity& owner) const { }

            // Getting the name of this Component. Used for sorting purposes
            // within an Entity.
            virtual std::string name() const = 0;
        };

        // An Entity functions much like a Component, only that it has a
        // predefined purpose; the management of its Components.
        class Entity {
        private:
            std::unordered_map<std::string, Component*> components;
            clibgame::core::UUID _uuid;

        public:
            Entity(const Entity&) = delete;
            Entity& operator=(const Entity&) = delete;

            // Constructing a new, empty Entity.
            Entity();

            // Deleting this Entity and all of its components.
            ~Entity();

            // Adding a Component to this Entity.
            void addComponent(Component* component);

            // Initializing the Entity.
            void init();

            // Updating the Entity.
            void update(float dt);

            // Rendering the Entity.
            void render() const;

            // Getting the UUID.
            const clibgame::core::UUID& uuid() const;
        };

        // A manager type of task. Very similar to a Component only that it has
        // reference to the entire World while updating.
        class System {
        public:
            virtual ~System() { }

            // Initializing the System. Though it has reference to the entire
            // World, it shouldn't attempt to access other Systems, as they may
            // not be initialized yet.
            virtual void init(World&) { }

            // Updating this System with reference to the World.
            virtual void update(World&, float dt) = 0;

            // Getting the name of this System. Used to organize Systems within
            // the master World object.
            virtual std::string name() const = 0;
        };

        // The top-level class in an ECS. Contains all of the Entities as well
        // as all of the Systems. Updates both in order.
        class World {
        private:
            std::unordered_map<clibgame::core::UUID, Entity*> entities;
            std::unordered_map<std::string, System*> systems;

        public:
            World(const World&) = delete;
            World& operator=(const World&) = delete;

            // Creating a new, empty world.
            World();

            // Destroying the world and all of its contents - including entities
            // and systems.
            ~World();

            // Adding an Entity.
            void addEntity(Entity*);

            // Adding an Entity at runtime -- the same as addEntity, only that
            // it also calls init() on the Entity.
            void addEntityRuntime(Entity*);

            // Removing an Entity from the World by UUID. Also calls the
            // destructor on the Entity.
            void removeEntity(clibgame::core::UUID);

            // Adding a System.
            void addSystem(System*);

            // Initializing the the world.
            void init();

            // Updating the world.
            void update(float dt);

            // Rendering the world.
            void render() const;
        };
    }
}

#endif
