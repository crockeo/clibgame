#include "manager.hpp"

//////////
// Code //

namespace clibgame {
    namespace res {
        ////
        // PakManager

        PakManager::PakManager(core::Pak& pak) :
                resources(),
                pak(pak) { }

        // Loading a given resource.
        void PakManager::loadResource(std::string path, ResourceType type)
                throw(std::runtime_error, std::logic_error) {
            if (hasResource(path))
                throw std::logic_error("Manager already contains resource: '" + path + "'.");

            // TODO: Implement loading.
            switch (type) {
            case SHADER_PROGRAM:
                break;
            case TEXTURE:
                break;
            case SOUND:
                break;
            case FONT:
                break;
            }
        }

        // Unloading a resource.
        void PakManager::unloadResource(std::string path, ResourceType type)
                throw(std::runtime_error, std::logic_error) {
            if (!hasResource(path))
                throw std::logic_error("Manager doesn't contain resource '" + path + "'.");

            // TODO: Implement unloading.
            switch (type) {
            case SHADER_PROGRAM:
                break;
            case TEXTURE:
                break;
            case SOUND:
                break;
            case FONT:
                break;
            }
        }

        // Getting a raw pointer to a loaded resource.
        const void* PakManager::getResource(std::string path) const
                throw(std::logic_error) {
            if (!hasResource(path))
                throw std::logic_error("No such resource as '" + path + "' in this manager.");
            return resources.at(path);
        }

        // Checking if this manager has a resource.
        bool PakManager::hasResource(std::string path) const {
            return resources.find(path) != resources.end();
        }

        ////
        // AdvancedManager

        AdvancedManager::AdvancedManager(Manager& manager) :
                manager(manager) { }

        // Loading a given resource.
        void AdvancedManager::loadResource(std::string path, ResourceType type)
                throw(std::runtime_error, std::logic_error) {
            manager.loadResource(path, type);
        }

        // Unloading a resource.
        void AdvancedManager::unloadResource(std::string path, ResourceType type)
                throw(std::runtime_error, std::logic_error) {
            manager.unloadResource(path, type);
        }

        // Getting a raw pointer to a loaded resource.
        const void* AdvancedManager::getResource(std::string path) const
                throw(std::logic_error) {
            return manager.getResource(path);
        }
    }
}
