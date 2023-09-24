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

int main(int ac, char **av)
{
    (void)ac;
    (void)av;

    int screenWidth = 1300;
    int screenHeight = 800;

    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");

    registry reg;

    reg.add_system<component::collider, component::position>(collide_system);
    reg.add_system<component::controllable, component::velocity>(control_system);
    reg.add_system<component::position, component::drawable>(draw_system);
    reg.add_system<component::collider, component::health>(damage_system);
    reg.add_system<component::collider, component::displayable_hurtbox, component::position>(hurtbox_display_system);
    reg.add_system<component::collider, component::projectile>(projectile_system);
    reg.add_system<component::velocity, component::path>(path_system);
    reg.add_system<component::shooter>(shoot_system);
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
    reg.register_component<component::projectile>();
    reg.register_component<component::path>();
    reg.register_component<component::shooter>();

    reg.get_assets_manager().load_texture("player", "assets/player.png");
    reg.get_assets_manager().load_texture("enemy", "assets/enemy.png");

    entity_t player = reg.spawn_entity();

    reg.emplace_component<component::position>(player, 50, 50);
    reg.emplace_component<component::velocity>(player, 0, 0);
    reg.emplace_component<component::displayable_hurtbox>(player, component::displayable_hurtbox(true));
    reg.add_component<component::health>(player, 100);
    reg.add_component<component::player>(player, component::player());
    component::drawable player_sprite = component::drawable(reg.get_assets_manager().get_texture("player"), 0.1);
    reg.add_component<component::collider>(player, component::collider(player_sprite.Drawable.width * player_sprite.scale, player_sprite.Drawable.height * player_sprite.scale));
    component::controllable player_control;
    player_control.is_key_up_pressed = std::function<bool()>([]() { return (IsKeyDown(KEY_W)); });
    player_control.is_key_down_pressed = std::function<bool()>([]() { return (IsKeyDown(KEY_S)); });
    player_control.is_key_left_pressed = std::function<bool()>([]() { return (IsKeyDown(KEY_A)); });
    player_control.is_key_right_pressed = std::function<bool()>([]() { return (IsKeyDown(KEY_D)); });
    reg.add_component<component::controllable>(player, std::move(player_control));
    reg.add_component<component::drawable>(player, std::move(player_sprite));

    prefab proj_enemy_prefab;
    proj_enemy_prefab.add_component<component::position>(0, 0);
    proj_enemy_prefab.add_component<component::velocity>(0, 0);
    proj_enemy_prefab.add_component<component::collider>(10, 5);
    proj_enemy_prefab.add_component<component::displayable_hurtbox>(true);
    proj_enemy_prefab.add_component<component::damage>(10);
    proj_enemy_prefab.add_component<component::enemy>(component::enemy());
    proj_enemy_prefab.add_component<component::projectile>(component::projectile());
    component::path p3;
    std::shared_ptr<pattern_movement> ilm2 = std::make_shared<infinite_linear_movement>(vector<float>(-1, 0), 1);
    p3.add_pattern(ilm2);
    proj_enemy_prefab.add_component<component::path>(std::move(p3));

    entity_t enemy = reg.spawn_entity();
    reg.emplace_component<component::position>(enemy, 200, 200);
    reg.emplace_component<component::velocity>(enemy, 0, 0);
    reg.emplace_component<component::displayable_hurtbox>(enemy, component::displayable_hurtbox(true));
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
    reg.add_component<component::shooter>(enemy, component::shooter(std::move(proj_enemy_prefab), 200));
    component::drawable enemy_sprite = component::drawable(reg.get_assets_manager().get_texture("enemy"), 0.5);
    reg.add_component<component::collider>(enemy, component::collider(enemy_sprite.Drawable.width * enemy_sprite.scale, enemy_sprite.Drawable.height * enemy_sprite.scale));
    reg.add_component<component::drawable>(enemy, std::move(enemy_sprite));

    entity_t projectile = reg.spawn_entity();
    reg.emplace_component<component::position>(projectile, 1000, 200);
    reg.emplace_component<component::velocity>(projectile, 0, 0);
    reg.add_component<component::collider>(projectile, component::collider(10, 5));
    reg.emplace_component<component::displayable_hurtbox>(projectile, component::displayable_hurtbox(true));
    reg.add_component<component::damage>(projectile, component::damage(10));
    reg.add_component<component::enemy>(projectile, component::enemy());
    reg.add_component<component::projectile>(projectile, component::projectile());
    component::path p2;
    std::shared_ptr<pattern_movement> ilm = std::make_shared<infinite_linear_movement>(vector<float>(-1, 0), 1);
    p2.add_pattern(ilm);
    reg.add_component<component::path>(projectile, std::move(p2));

    prefab square_prefab;
    square_prefab.add_component<component::position>(100, 100);
    square_prefab.add_component<component::velocity>(0, 0);
    square_prefab.add_component<component::displayable_hurtbox>(true);
    component::drawable enemy_sprite2 = component::drawable(reg.get_assets_manager().get_texture("enemy"), 0.4);
    square_prefab.add_component<component::collider>(component::collider(enemy_sprite2.Drawable.width * enemy_sprite2.scale, enemy_sprite2.Drawable.height * enemy_sprite2.scale));
    square_prefab.add_component<component::drawable>(std::move(enemy_sprite2));

    entity_t square = square_prefab.instantiate(reg);
    reg.get_components<component::position>()[square].value().Position.x = 500;
    reg.get_components<component::position>()[square].value().Position.y = 500;

    square_prefab.instantiate(reg);

    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        BeginDrawing();

        ClearBackground(BLACK);

        reg.run_systems();

        EndDrawing();
    }

    CloseWindow();
    return (0);
}
