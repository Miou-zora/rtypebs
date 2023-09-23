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

class assets_manager
{
    public:
        using texture_t = sf::Texture;
        using sound_t = sf::SoundBuffer;
        using font_t = sf::Font;
    public:
        assets_manager() = default;
        virtual ~assets_manager() = default;

        bool load_texture(const std::string &name, const std::string &path)
        {
            bool result = _textures[name].loadFromFile(path);
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
            bool result = _sounds[name].loadFromFile(path);
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
            bool result = _fonts[name].loadFromFile(path);
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
