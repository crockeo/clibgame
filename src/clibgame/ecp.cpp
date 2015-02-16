#include "ecp.hpp"

//////////
// Code //

// Creating a component with a set owner already.
clibgame::Component::Component(Entity* owner) {
    this->owner = owner;
}

// Creating a Component without an owner.
clibgame::Component::Component() {
    this->owner = nullptr;
}

// Checking if this component has an owner.
bool clibgame::Component::hasOwner() const {
    return this->owner != nullptr;
}

// Setting the owner of this Component.
void clibgame::Component::setOwner(Entity* owner) {
    this->owner = owner;
}

// Getting a reference to the owner.
clibgame::Entity& clibgame::Component::getOwner() {
    return *this->owner;
}

// Getting a const reference to the owner.
const clibgame::Entity& clibgame::Component::getOwner() const {
    return *this->owner;
}

// Constructing a new Entity with all of its data set.
clibgame::Entity::Entity(std::string uid, std::set<Component*> components) {
    this->uid = uid;
    for (auto& component: components)
        if (component != nullptr)
            this->components[component->getName()] = std::unique_ptr<Component>(component);
}

// Constructing a new Entity with no components.
clibgame::Entity::Entity(std::string uid) {
    this->uid = uid;
}

// Getting the UID of the 
std::string clibgame::Entity::getUID() const { return this->uid; }

// Adding a component to this entity.
void clibgame::Entity::addComponent(Component* component) {
    component->setOwner(this);
    if (component != nullptr && this->components.find(component->getName()) == this->components.end())
       this->components[component->getName()] = std::unique_ptr<Component>(component);
}

// Removing a component from this entity.
void clibgame::Entity::removeComponent(Component* component) {
    auto pos = this->components.find(component->getName());
    if (pos != this->components.end())
        this->components.erase(pos);
}

// Getting a const ref to a component from this entity.
const clibgame::Component& clibgame::Entity::getComponent(std::string name) const throw(std::runtime_error) {
    if (this->components.find(name) == this->components.end())
        throw std::runtime_error("No such component exists in this Entity.");
    return *this->components.at(name);
}

// Getting a ref to a component from the entity.
clibgame::Component& clibgame::Entity::getComponent(std::string name) throw(std::runtime_error) {
    if (this->components.find(name) == this->components.end())
        throw std::runtime_error("No such component exists in this Entity.");
    return *this->components[name];
}

// Initializing the set of components in this Entity.
void clibgame::Entity::initComponents(GLFWwindow* window, const ECP& ecp, const Res& res) {
    for (auto& pair: this->components)
        std::get<1>(pair)->init(window, ecp, res);
}

// Updating the set of components.
void clibgame::Entity::updateComponents(GLFWwindow* window, const clibgame::ECP& ecp, float dt) {
    for (auto& pair: this->components)
        std::get<1>(pair)->update(window, ecp, dt);
}

// Rendering the set of components.
void clibgame::Entity::renderComponents() const {
    for (auto& pair: this->components)
        std::get<1>(pair)->render();
}

// Creating an empty ECP.
clibgame::ECP::ECP() { }

// Adding a new entity with a set of components.
void clibgame::ECP::addEntity(std::string uid, std::set<Component*> components) {
    this->entities.emplace(std::piecewise_construct,
                           std::forward_as_tuple(uid),
                           std::forward_as_tuple(uid, components));
}

// Adding a new entity.
void clibgame::ECP::addEntity(std::string uid) {
    this->entities.emplace(std::piecewise_construct,
                           std::forward_as_tuple(uid),
                           std::forward_as_tuple(uid));
}

// Getting a const reference to an entity.
const clibgame::Entity& clibgame::ECP::getEntity(std::string uid) const {
    return this->entities.at(uid);
}

// Getting a reference to an entity.
clibgame::Entity& clibgame::ECP::getEntity(std::string uid) {
    return this->entities.at(uid);
}

// Initializing the set of entities.
void clibgame::ECP::initEntities(GLFWwindow* window, const Res& res) {
    for (auto& pair: this->entities)
        std::get<1>(pair).initComponents(window, *this, res);
}

// Updating the set of entities.
void clibgame::ECP::updateEntities(GLFWwindow* window, float dt) {
    for (auto& pair: this->entities)
        std::get<1>(pair).updateComponents(window, *this, dt);
}

// Rendering the set of entities.
void clibgame::ECP::renderEntities() const {
    for (auto& pair: this->entities)
        std::get<1>(pair).renderComponents();
}
