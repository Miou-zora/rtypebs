/*
** EPITECH PROJECT, 2023
** rtypebs [WSL : Ubuntu]
** File description:
** assets_manager
*/

#pragma once

#include <unordered_map>
#include <iostream>
#include "raylib.h"

class AssetsManager // TODO: add .cpp
{
    // Singleton part
    private:
        AssetsManager() = default;
    public:
        static AssetsManager &get_instance()
        {
            if (!m_instance)
                m_instance = new AssetsManager();
            return (*m_instance);
        }
    private:
        static AssetsManager *m_instance;

    public:
        using texture_t = Texture2D;
        using sound_t = Sound;
        using font_t = Font;

        virtual ~AssetsManager() = default;

        bool load_texture(const std::string &name, const std::string &path)
        {
            _textures[name] = LoadTexture(path.c_str());
            bool result = _textures[name].id != 0;
            if (result) {
                std::cout << "Loaded texture " << name << " from " << path << std::endl;
            } else {
                std::cerr << "Failed to load texture " << name << " from " << path << std::endl;
            }
            return (result);
        }

        texture_t &get_texture(const std::string &name)
        {
            return (_textures[name]);
        }

        bool load_sound(const std::string &name, const std::string &path)
        {
            _sounds[name] = LoadSound(path.c_str());
            bool result = _sounds[name].frameCount != 0;
            if (result) {
                std::cout << "Loaded sound " << name << " from " << path << std::endl;
            } else {
                std::cerr << "Failed to load sound " << name << " from " << path << std::endl;
            }
            return (result);
        }

        sound_t &get_sound(const std::string &name)
        {
            return (_sounds[name]);
        }

        bool load_font(const std::string &name, const std::string &path)
        {
            _fonts[name] = LoadFont(path.c_str());
            bool result = _fonts[name].baseSize != 0;
            if (result) {
                std::cout << "Loaded font " << name << " from " << path << std::endl;
            } else {
                std::cerr << "Failed to load font " << name << " from " << path << std::endl;
            }
            return (result);
        }

        font_t &get_font(const std::string &name)
        {
            return (_fonts[name]);
        }

    private:
        std::unordered_map<std::string, texture_t> _textures;
        std::unordered_map<std::string, sound_t> _sounds;
        std::unordered_map<std::string, font_t> _fonts;
};

inline AssetsManager *AssetsManager::m_instance = nullptr;
