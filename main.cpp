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
#include "drawable.hpp"

int main(int ac, char **av)
{
    (void)ac;
    (void)av;

    registry reg;

    reg.add_system<component::controllable, component::velocity>(control_system);
    reg.add_system<component::position, component::velocity>(position_system);
    reg.add_system<component::position, component::drawable>(draw_system);
    reg.add_system<component::position, component::velocity>(logging_system); //* DEBUG

    reg.register_component<component::position>();
    reg.register_component<component::velocity>();
    reg.register_component<component::controllable>();
    reg.register_component<component::drawable>();

    entity_t player = reg.spawn_entity();

    reg.add_component<component::position>(player, component::position(50, 50));
    reg.add_component<component::velocity>(player, component::velocity(0, 0));
    component::controllable controllable;
    reg.add_component<component::controllable>(player, std::move(controllable));
    reg.add_component<component::drawable>(player, component::drawable(std::make_shared<sf::RectangleShape>(sf::Vector2f(50, 50))));

    entity_t enemy = reg.spawn_entity();

    reg.add_component<component::position>(enemy, component::position(200, 200));
    reg.add_component<component::velocity>(enemy, component::velocity(0, 0));
    reg.add_component<component::drawable>(enemy, component::drawable(std::make_shared<sf::CircleShape>(30)));


    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) window.close();
        }

        window.clear(sf::Color::Black);

        reg.run_systems();

        window.display();
    }

    return (0);
}
