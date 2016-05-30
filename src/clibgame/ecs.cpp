#include "ecs.hpp"

//////////////
// Includes //
#include <iostream>

#include "core/debug.hpp"

//////////
// Code //

namespace clibgame {
    namespace ecs {
        ////
        // Entity

        // Constructing a new, empty Entity.
        Entity::Entity() :
                _uuid(clibgame::core::UUID::generateUUID()) { }

        // Deleting this Entity and all of its components.
        Entity::~Entity() {
            for (auto pair: this->components)
                delete std::get<1>(pair);
        }

        // Adding a Component to this Entity.
        void Entity::addComponent(Component* component) {
            auto it = components.find(component->name());
            if (it != components.end()) {
                delete std::get<1>(*it);
                components.erase(it);
            }

            components.insert(std::pair<std::string, Component*>(component->name(), component));
        }

        // Initializing the Entity.
        void Entity::init() { 
            for (auto& pair: this->components)
                std::get<1>(pair)->init(*this);
        }

        // Updating the Entity.
        void Entity::update(float dt) {
            for (auto& pair: components)
                std::get<1>(pair)->update(*this, dt);
        }

        // Rendering the Entity.
        void Entity::render() const {
            for (const auto& pair: components)
                std::get<1>(pair)->render(*this);
        }

        // Getting the UUID.
        const clibgame::core::UUID& Entity::uuid() const {
            return _uuid;
        }

        ////
        // World

        // Creating a new, empty world.
        World::World() { }

        // Destroying the world and all of its contents - including entities
        // and systems.
        World::~World() {
            for (auto& pair: entities)
                delete std::get<1>(pair);

            for (auto& pair: systems)
                delete std::get<1>(pair);
        }

        // Adding an Entity.
        void World::addEntity(Entity* entity) {
            auto it = entities.find(entity->uuid());
            if (it != entities.end()) {
                if (clibgame::core::Debug::level() > 0)
                    std::cout << "UUID clash -- overwriting entity." << std::endl;
                delete std::get<1>(*it);
                entities.erase(it);
            }

            entities.insert(std::pair<clibgame::core::UUID, Entity*>(entity->uuid(), entity));
        }

        // Adding an Entity at runtime -- the same as addEntity, only that
        // it also calls init() on the Entity.
        void World::addEntityRuntime(Entity* entity) {
            addEntity(entity);
            entity->init();
        }

        // Removing an Entity from the World by UUID. Also calls the
        // destructor on the Entity.
        void World::removeEntity(clibgame::core::UUID uuid) {
            auto it = entities.find(uuid);
            if (it == entities.end())
                throw std::out_of_range("");
            entities.erase(it);
        }

        // Adding a System.
        void World::addSystem(System* system) {
            auto it = systems.find(system->name());
            if (it != systems.end()) {
                if (clibgame::core::Debug::level() > 0)
                    std::cout << "System name clash -- overwriting System." << std::endl;
                delete std::get<1>(*it);
                systems.erase(it);
            }

            systems.insert(std::make_pair(system->name(), system));
        }

        // Initializing the the world.
        void World::init() {
            for (auto& pair: entities)
                std::get<1>(pair)->init();
            for (auto& pair: systems)
                std::get<1>(pair)->init(*this);
        }

        // Updating the world.
        void World::update(float dt) {
            for (auto& pair: entities)
                std::get<1>(pair)->update(dt);
            for (auto& pair: systems)
                std::get<1>(pair)->update(*this, dt);
        }

        // Rendering the world.
        void World::render() const {
            for (const auto& pair: entities)
                std::get<1>(pair)->render();
        }
    }
}
