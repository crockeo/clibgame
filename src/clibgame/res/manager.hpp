// Name     : manager.hpp
// Author(s): Cerek Hillen
// Init Date: 2016-06-03
// Edit Date: 2016-06-03
//
// Description:
//   An API and implementation of a resource manager.

#ifndef _CLIBGAME_RES_MANAGER_HPP_
#define _CLIBGAME_RES_MANAGER_HPP_

//////////////
// Includes //
#include <unordered_map>

#include "../core/pak.hpp"
#include "texture.hpp"
#include "shader.hpp"
#include "sound.hpp"
#include "font.hpp"

//////////
// Code //

namespace clibgame {
    namespace res {
        // An enumeration of ResourceTypes, used in Manager.
        enum ResourceType {
            SHADER_PROGRAM,
            TEXTURE,
            SOUND,
            FONT
        };

        // The defined interface for a working Manager; can load, unload, and
        // retrieve resources.
        struct Manager {
            virtual ~Manager() { }

            // Loading a given resource.
            virtual void loadResource(std::string path, ResourceType type)
                    throw(std::runtime_error, std::logic_error) = 0;

            // Unloading a resource.
            virtual void unloadResource(std::string path, ResourceType type)
                    throw(std::runtime_error, std::logic_error) = 0;

            // Getting a raw pointer to a loaded resource.
            virtual const void* getResource(std::string path) const
                    throw(std::logic_error) = 0;

            // Checking if this manager has a resource.
            virtual bool hasResource(std::string path) const = 0;
        };

        // An implementation of a Manager that works off of a native Pak.
        class PakManager : public Manager {
        private:
            std::unordered_map<std::string, void*> resources;
            core::Pak& pak;

        public:
            PakManager(const PakManager&) = delete;
            PakManager& operator=(const PakManager&) = delete;

            PakManager(core::Pak& pak);

            // Loading a given resource.
            virtual void loadResource(std::string path, ResourceType type)
                    throw(std::runtime_error, std::logic_error);

            // Unloading a resource.
            virtual void unloadResource(std::string path, ResourceType type)
                    throw(std::runtime_error, std::logic_error);

            // Getting a raw pointer to a loaded resource.
            virtual const void* getResource(std::string path) const
                    throw(std::logic_error);

            // Checking if this manager has a resource.
            virtual bool hasResource(std::string path) const;
        };

        // A wrapper around another Manager to provide a typed interface on
        // resource access.
        class AdvancedManager : public Manager {
        private:
            Manager& manager;

        public:
            AdvancedManager(Manager& manager);

            // Loading a given resource.
            virtual void loadResource(std::string path, ResourceType type)
                    throw(std::runtime_error, std::logic_error);

            // Unloading a resource.
            virtual void unloadResource(std::string path, ResourceType type)
                    throw(std::runtime_error, std::logic_error);

            // Getting a raw pointer to a loaded resource.
            virtual const void* getResource(std::string path) const
                    throw(std::logic_error);

            // Typed calls to getResource.
            ShaderProgram getShader(std::string path) throw(std::logic_error);
            Texture getTexture(std::string path) throw(std::logic_error);
            // Sound getSound(std::string path) throw(std::logic_error); TODO
            Font getFont(std::string path) throw(std::logic_error);
        };
    }
}

#endif
