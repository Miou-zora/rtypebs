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
#include "mouse_system.hpp"
#include "assets_manager.hpp"
#include "animation_system.hpp"
#include "PrefabManager.hpp"

int main(int ac, char **av)
{
    (void)ac;
    (void)av;

    int screenWidth = 1300;
    int screenHeight = 800;

    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");

    registry reg;

    reg.add_system<component::collider, component::position>(collide_system());
    reg.add_system<component::controllable, component::velocity>(control_system);
    reg.add_system<component::position, component::drawable>(draw_system);
    reg.add_system<component::animation, component::position>(animation_system());
    reg.add_system<component::collider, component::health>(damage_system);
    reg.add_system<component::collider, component::displayable_hurtbox, component::position>(hurtbox_display_system);
    reg.add_system<component::collider, component::projectile>(projectile_system);
    reg.add_system<component::velocity, component::path>(path_system);
    reg.add_system<component::shooter>(shoot_system);
    reg.add_system<component::position, component::velocity>(position_system);
    reg.add_system<component::clickable, component::position, component::collider>(mouse_system());
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
    reg.register_component<component::clickable>();
    reg.register_component<component::animation>();

    AssetsManager::get_instance().load_texture("player", "assets/player.png");
    AssetsManager::get_instance().load_texture("enemy", "assets/enemy.png");
    AssetsManager::get_instance().load_texture("sphere", "assets/sphere.gif");

    entity_t player = reg.spawn_entity();

    reg.emplace_component<component::position>(player, 50, 50);
    reg.emplace_component<component::velocity>(player, 0, 0);
    reg.emplace_component<component::displayable_hurtbox>(player, component::displayable_hurtbox(true));
    reg.add_component<component::health>(player, 100);
    reg.add_component<component::player>(player, component::player());
    component::drawable player_sprite = component::drawable(AssetsManager::get_instance().get_texture("player"), 0.1);
    reg.add_component<component::collider>(player, component::collider(player_sprite.Drawable.width * player_sprite.scale, player_sprite.Drawable.height * player_sprite.scale));
    component::controllable player_control;
    player_control.is_key_up_pressed = std::function<bool()>([]() { return (IsKeyDown(KEY_W)); });
    player_control.is_key_down_pressed = std::function<bool()>([]() { return (IsKeyDown(KEY_S)); });
    player_control.is_key_left_pressed = std::function<bool()>([]() { return (IsKeyDown(KEY_A)); });
    player_control.is_key_right_pressed = std::function<bool()>([]() { return (IsKeyDown(KEY_D)); });
    reg.add_component<component::controllable>(player, std::move(player_control));
    reg.add_component<component::drawable>(player, std::move(player_sprite));
    reg.emplace_component<component::clickable>(player, component::clickable());

    PrefabManager::get_instance().CreatePrefab("proj_enemy_prefab")
        .add_component<component::velocity>(0, 0)
        .add_component<component::position>(0, 0)
        .add_component<component::collider>(10, 5)
        .add_component<component::displayable_hurtbox>(true)
        .add_component<component::damage>(10)
        .add_component<component::enemy>(component::enemy())
        .add_component<component::projectile>(component::projectile())
        .add_component<component::path>(component::path().add_pattern<infinite_linear_movement>(vector<float>(-1, 0), 300));

    entity_t enemy = reg.spawn_entity();
    reg.emplace_component<component::position>(enemy, 200, 200);
    reg.emplace_component<component::velocity>(enemy, 0, 0);
    reg.emplace_component<component::displayable_hurtbox>(enemy, component::displayable_hurtbox(true));
    reg.add_component<component::enemy>(enemy, component::enemy());
    component::path p;
    p.add_pattern<linear_movement>(1, vector<float>(300, 0))
        .add_pattern<linear_movement>(vector<float>(0, 100), 100)
        .add_pattern<linear_movement>(vector<float>(100, 100), 100)
        .add_pattern<reverse_linear_movement>(vector<float>(0, -100), 100);
    reg.add_component<component::path>(enemy, std::move(p));
    reg.add_component<component::shooter>(enemy, component::shooter("proj_enemy_prefab", 1));
    component::drawable enemy_sprite = component::drawable(AssetsManager::get_instance().get_texture("enemy"), 0.5);
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
    reg.add_component<component::path>(projectile, std::move(component::path().add_pattern<infinite_linear_movement>(vector<float>(-1, 0), 100)));


    component::drawable square_prefab_drawable = component::drawable(AssetsManager::get_instance().get_texture("enemy"), 0.4);
    PrefabManager::get_instance().CreatePrefab("square_prefab")
        .add_component<component::position>(100, 100)
        .add_component<component::velocity>(0, 0)
        .add_component<component::displayable_hurtbox>(true)
        .add_component<component::collider>(component::collider(square_prefab_drawable.Drawable.width * square_prefab_drawable.scale, square_prefab_drawable.Drawable.height * square_prefab_drawable.scale))
        .add_component<component::drawable>(square_prefab_drawable);

    entity_t square = PrefabManager::get_instance().Instantiate("square_prefab", reg);
    reg.get_components<component::position>()[square].value().Position.x = 500;
    reg.get_components<component::position>()[square].value().Position.y = 500;

    PrefabManager::get_instance().Instantiate("square_prefab", reg);

    entity_t sphere = reg.spawn_entity();
    reg.emplace_component<component::position>(sphere, 700, 700);
    reg.emplace_component<component::velocity>(sphere, 0, 0);
    reg.emplace_component<component::displayable_hurtbox>(sphere, component::displayable_hurtbox(true));
    component::animation sphere_animation;
    sphere_animation.texture = AssetsManager::get_instance().get_texture("sphere");
    sphere_animation.scale = 2;
    sphere_animation.source_rect = Rectangle{0, 0, 16, 16};
    // 12
    sphere_animation.frames.push_back(vector<int>(1, 1));
    sphere_animation.frames.push_back(vector<int>(18, 1));
    sphere_animation.frames.push_back(vector<int>(35, 1));
    sphere_animation.frames.push_back(vector<int>(52, 1));
    sphere_animation.frames.push_back(vector<int>(69, 1));
    sphere_animation.frames.push_back(vector<int>(86, 1));
    sphere_animation.frames.push_back(vector<int>(103, 1));
    sphere_animation.frames.push_back(vector<int>(120, 1));
    sphere_animation.frames.push_back(vector<int>(137, 1));
    sphere_animation.frames.push_back(vector<int>(154, 1));
    sphere_animation.frames.push_back(vector<int>(171, 1));
    sphere_animation.frames.push_back(vector<int>(188, 1));
    sphere_animation.current_frame = 0;
    sphere_animation.time = 0;
    sphere_animation.loop = true;
    sphere_animation.finished = false;
    for (std::size_t i = 0; i < sphere_animation.frames.size(); i++)
        sphere_animation.frame_times.push_back(0.1);
    reg.add_component<component::collider>(sphere, component::collider(sphere_animation.source_rect.width * sphere_animation.scale, sphere_animation.source_rect.height * sphere_animation.scale));
    reg.add_component<component::animation>(sphere, std::move(sphere_animation));


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
