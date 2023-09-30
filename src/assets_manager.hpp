/*
** EPITECH PROJECT, 2023
** rtypebs [WSL : Ubuntu]
** File description:
** assets_manager
*/

#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <unordered_map>
#include "raylib.h"
#include <cmrc/cmrc.hpp>
#include <cstring>

CMRC_DECLARE(app1);

class assets_manager
{
    public:
        using texture_t = Texture2D;
        using sound_t = Sound;
        using font_t = Font;
    public:
        assets_manager() = default;
        virtual ~assets_manager() = default;

        bool load_texture(const std::string &name, const std::string &path)
        {
            auto fs = cmrc::app1::get_filesystem();
            auto rose = fs.open(path);

            std::string extension = strrchr(const_cast<char *>(path.c_str()), '.');
            const unsigned char *data = reinterpret_cast<const unsigned char *>(rose.begin());

            Image image = LoadImageFromMemory(extension.c_str(), data, rose.size());
            _textures[name] = LoadTextureFromImage(image);
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
