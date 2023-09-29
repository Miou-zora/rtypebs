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
#include "projectile_system.hpp"
#include "shoot_system.hpp"
#include "prefab.hpp"
#include <iostream>
#include "raylib.h"
#include "EventManager.hpp"

#include "NetworkEvent.hpp"
#include "network_client.hpp"
#include "network_system.hpp"

int main(int ac, char **av)
{
    (void)ac;
    (void)av;

    int screenWidth = 1300;
    int screenHeight = 800;

    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");

    registry reg;

    reg.get_assets_manager().load_texture("player", "assets/player.png");

    reg.register_component<component::network_client>();
    reg.register_component<component::controllable>();
    reg.register_component<component::position>();
    reg.register_component<component::drawable>();

    reg.add_system<component::network_client>(network_read_system);
    reg.add_system<component::network_client>(network_write_system);
    reg.add_system<component::controllable, component::network_client>(network_control_system);
    reg.add_system<component::position, component::drawable>(draw_system);

    entity_t player = reg.spawn_entity();

    reg.emplace_component<component::network_client>(player, "localhost", 12345);
    component::controllable player_control;
    player_control.is_key_up_pressed = std::function<bool()>([]() { return (IsKeyDown(KEY_W)); });
    player_control.is_key_down_pressed = std::function<bool()>([]() { return (IsKeyDown(KEY_S)); });
    player_control.is_key_left_pressed = std::function<bool()>([]() { return (IsKeyDown(KEY_A)); });
    player_control.is_key_right_pressed = std::function<bool()>([]() { return (IsKeyDown(KEY_D)); });
    reg.add_component<component::controllable>(player, std::move(player_control));
    reg.emplace_component<component::position>(player, 50, 50);
    component::drawable player_sprite = component::drawable(reg.get_assets_manager().get_texture("player"), 0.1);
    reg.add_component<component::drawable>(player, std::move(player_sprite));

    ecs::EventManager::getInstance().subscribe<network::event::in::MoveMessage>([&reg, player](const network::event::in::MoveMessage &event) {
        std::cout << "Received move message" << std::endl;
        auto &position = reg.get_components<component::position>()[player].value();
        std::cout << "Position: " << position.Position.x << ", " << position.Position.y << std::endl;
        std::cout << "received x: " << event.x << "y: " << event.y << std::endl;
        position.Position.x += event.x;
        position.Position.y += event.y;
    });

    while (!WindowShouldClose())
    {
        BeginDrawing();

        ClearBackground(BLACK);
        reg.update_delta_time();
        reg.run_systems();

        EndDrawing();
    }

    CloseWindow();
    return (0);
}
