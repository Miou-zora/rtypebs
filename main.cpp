/*
** EPITECH PROJECT, 2023
** B-CPP-500-NAN-5-1-bsrtype-alexandre.franquet
** File description:
** main
*/

#include "registry.hpp"
#include "draw_system.hpp"
#include "position_system.hpp"
#include "control_system.hpp"
#include "logging_system.hpp"
#include "hurtbox_display_system.hpp"
#include "collide_system.hpp"
#include "drawable.hpp"
#include "damage_system.hpp"
#include "path_system.hpp"

int main(int ac, char **av)
{
    (void)ac;
    (void)av;

    registry reg;

    reg.add_system<component::collider, component::position>(collide_system);
    reg.add_system<component::controllable, component::velocity>(control_system);
    reg.add_system<component::position, component::drawable>(draw_system);
    reg.add_system<component::collider, component::health>(damage_system);
    reg.add_system<component::collider, component::displayable_hurtbox, component::position>(hurtbox_display_system);
    reg.add_system<component::velocity, component::path>(path_system);
    reg.add_system<component::position, component::velocity>(position_system);
    // reg.add_system<component::position, component::velocity>(logging_system); //* DEBUG

    reg.register_component<component::position>();
    reg.register_component<component::velocity>();
    reg.register_component<component::controllable>();
    reg.register_component<component::drawable>();
    reg.register_component<component::collider>();
    reg.register_component<component::displayable_hurtbox>();
    reg.register_component<component::health>();
    reg.register_component<component::damage>();
    reg.register_component<component::enemy>();
    reg.register_component<component::player>();
    reg.register_component<component::path>();

    entity_t player = reg.spawn_entity();
    reg.emplace_component<component::position>(player, 50, 50);
    reg.emplace_component<component::velocity>(player, 0, 0);
    reg.emplace_component<component::drawable>(player, std::make_shared<sf::RectangleShape>(sf::Vector2f(50, 50)));
    reg.emplace_component<component::collider>(player, 50, 50);
    reg.emplace_component<component::displayable_hurtbox>(player, true);
    component::controllable controllable;
    controllable.is_key_up_pressed = []() -> bool { return (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)); };
    controllable.is_key_down_pressed = []() -> bool { return (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)); };
    controllable.is_key_left_pressed = []() -> bool { return (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)); };
    controllable.is_key_right_pressed = []() -> bool { return (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)); };
    reg.add_component<component::controllable>(player, std::move(controllable));
    reg.add_component<component::health>(player, 100);
    reg.add_component<component::player>(player, component::player());

    entity_t enemy = reg.spawn_entity();
    reg.emplace_component<component::position>(enemy, 200, 200);
    reg.emplace_component<component::velocity>(enemy, 0, 0);
    reg.emplace_component<component::drawable>(enemy, std::make_shared<sf::CircleShape>(30));
    reg.emplace_component<component::collider>(enemy, 60, 60);
    reg.emplace_component<component::displayable_hurtbox>(enemy, true);
    reg.add_component<component::damage>(enemy, component::damage(10));
    reg.add_component<component::enemy>(enemy, component::enemy());

    component::path p;
    std::shared_ptr<pattern_movement> lm1 = std::make_shared<linear_movement>(100, vector<float>(300, 0));
    p.add_pattern(lm1);
    std::shared_ptr<pattern_movement> lm2 = std::make_shared<linear_movement>(vector<float>(0, 100), 1);
    p.add_pattern(lm2);
    std::shared_ptr<pattern_movement> lm3 = std::make_shared<linear_movement>(vector<float>(100, 100), 1);
    p.add_pattern(lm3);
    std::shared_ptr<pattern_movement> rlm = std::make_shared<reverse_linear_movement>(vector<float>(0, -100), 1);
    p.add_pattern(rlm);
    reg.add_component<component::path>(enemy, std::move(p));


    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) window.close();
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) window.close();
        }

        window.clear(sf::Color::Black);

        reg.run_systems();

        window.display();
    }

    return (0);
}
