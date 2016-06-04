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

        //AdvancedManager(Manager& manager);

        //// Loading a given resource.
        //virtual void loadResource(std::string path, ResourceType type)
                //throw(std::runtime_error, std::logic_error);

        //// Unloading a resource.
        //virtual void unloadResource(std::string path, ResourceType type)
                //throw(std::runtime_error, std::logic_error);

        //// Getting a raw pointer to a loaded resource.
        //virtual const void* getResource(std::string path)
                //throw(std::logic_error);

        //// Typed calls to getResource.
        //ShaderProgram getShader(std::string path) throw(std::logic_error);
        //Texture getTexture(std::string path) throw(std::logic_error);
        //// Sound getSound(std::string path) throw(std::logic_error); TODO
        //Font getFont(std::string path) throw(std::logic_error);
    }
}
