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
#include "player_shoot_system.hpp"
#include "spawner_system.hpp"

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
    reg.add_system<component::velocity, component::path, component::position>(path_system);
    reg.add_system<component::playerShooter, component::controllable>(player_shoot_system);
    reg.add_system<component::shooter>(shoot_system);
    reg.add_system<component::position, component::velocity>(position_system);
    reg.add_system<component::clickable, component::position, component::collider>(mouse_system());
    reg.add_system<component::Spawner>(spawner_system());
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
    reg.register_component<component::playerShooter>();
    reg.register_component<component::clickable>();
    reg.register_component<component::animation>();
    reg.register_component<component::Spawner>();

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
    player_control.is_key_shoot_pressed = std::function<bool()>([]() { return (IsKeyDown(KEY_SPACE)); });
    reg.add_component<component::controllable>(player, std::move(player_control));
    reg.add_component<component::drawable>(player, std::move(player_sprite));
    reg.add_component<component::playerShooter>(player, component::playerShooter("proj_player_prefab", 0.5));
    // reg.emplace_component<component::clickable>(player, component::clickable());

    PrefabManager::get_instance().CreatePrefab("proj_player_prefab")
        .add_component<component::velocity>(0, 0)
        .add_component<component::position>(0, 0)
        .add_component<component::collider>(10, 5)
        .add_component<component::displayable_hurtbox>(true)
        .add_component<component::damage>(1)
        .add_component<component::player>()
        .add_component<component::projectile>()
        .add_component<component::path>(component::path().AddPoint(-300, 0));


    PrefabManager::get_instance().CreatePrefab("proj_enemy_prefab")
        .add_component<component::velocity>(0, 0)
        .add_component<component::position>(0, 0)
        .add_component<component::collider>(10, 5)
        .add_component<component::displayable_hurtbox>(true)
        .add_component<component::damage>(1)
        .add_component<component::enemy>()
        .add_component<component::projectile>()
        .add_component<component::path>(component::path().AddPoint(-200, 0, component::path::Context::Local));

    entity_t enemy = reg.spawn_entity();
    reg.add_component<component::position>(enemy, component::position(200, 200));
    reg.add_component<component::velocity>(enemy, component::velocity(0, 0));
    reg.add_component<component::displayable_hurtbox>(enemy, component::displayable_hurtbox(true));
    reg.add_component<component::enemy>(enemy, component::enemy());
    component::path p;
    p.AddPoint(400, 200)
     .AddPoint(0, 100, component::path::Context::Local)
     .AddPoint(100, 100, component::path::Context::Local);
    reg.add_component<component::path>(enemy, std::move(p));
    reg.add_component<component::shooter>(enemy, component::shooter("proj_enemy_prefab", 1));
    reg.add_component<component::health>(enemy, 100);
    component::drawable enemy_sprite = component::drawable(AssetsManager::get_instance().get_texture("enemy"), 0.5);
    reg.add_component<component::collider>(enemy, component::collider(enemy_sprite.Drawable.width * enemy_sprite.scale, enemy_sprite.Drawable.height * enemy_sprite.scale));
    reg.add_component<component::drawable>(enemy, std::move(enemy_sprite));

    entity_t projectile = reg.spawn_entity();
    reg.add_component<component::position>(projectile, component::position(1000, 200));
    reg.add_component<component::velocity>(projectile, component::velocity(0, 0));
    reg.add_component<component::collider>(projectile, component::collider(10, 5));
    reg.add_component<component::displayable_hurtbox>(projectile, component::displayable_hurtbox(true));
    reg.add_component<component::damage>(projectile, component::damage(10));
    reg.add_component<component::enemy>(projectile, component::enemy());
    reg.add_component<component::projectile>(projectile, component::projectile());
    reg.add_component<component::path>(projectile, std::move(component::path().AddPoint(200, 200)));


    component::drawable square_prefab_drawable = component::drawable(AssetsManager::get_instance().get_texture("enemy"), 0.4);
    PrefabManager::get_instance().CreatePrefab("square_prefab")
        .add_component<component::position>(100, 100)
        .add_component<component::velocity>(0, 0)
        .add_component<component::displayable_hurtbox>(true)
        .add_component<component::collider>(component::collider(square_prefab_drawable.get_size()))
        .add_component<component::drawable>(square_prefab_drawable);

    entity_t square = PrefabManager::get_instance().Instantiate("square_prefab", reg);
    reg.get_components<component::position>()[square].value().Position.x = 500;
    reg.get_components<component::position>()[square].value().Position.y = 500;

    PrefabManager::get_instance().Instantiate("square_prefab", reg);

    entity_t sphere = reg.spawn_entity();
    reg.add_component<component::position>(sphere, component::position(700, 700));
    reg.add_component<component::velocity>(sphere, component::velocity(0, 0));
    reg.add_component<component::displayable_hurtbox>(sphere, component::displayable_hurtbox(true));
    component::animation sphere_animation;
    sphere_animation.texture = AssetsManager::get_instance().get_texture("sphere");
    sphere_animation.scale = 2;
    sphere_animation.source_rect = Rectangle{0, 0, 16, 16};
    for (std::size_t i = 0; i < 12; i++) {
        sphere_animation.frames.push_back(vector<int>(i * 17 + 1, 1));
        sphere_animation.frame_times.push_back(0.1);
    }
    sphere_animation.current_frame = 0;
    sphere_animation.time = 0;
    sphere_animation.loop = true;
    sphere_animation.finished = false;
    reg.add_component<component::collider>(sphere, component::collider(sphere_animation.source_rect.width * sphere_animation.scale, sphere_animation.source_rect.height * sphere_animation.scale));
    reg.add_component<component::animation>(sphere, std::move(sphere_animation));

    PrefabManager::get_instance().CreatePrefab("diagonal_enemy")
        .add_component<component::position>(500, 100)
        .add_component<component::velocity>(0, 0)
        .add_component<component::displayable_hurtbox>(true)
        .add_component<component::drawable>(AssetsManager::get_instance().get_texture("enemy"), 0.5)
        .add_component<component::collider>(component::collider(AssetsManager::get_instance().get_texture("enemy").width * 0.5, AssetsManager::get_instance().get_texture("enemy").height * 0.5))
        .add_component<component::path>(component::path()
            .AddPoint(300, 300)
            .AddPoint(500, 500)
            .AddPoint(1000, 500)
            .SetDestroyAtEnd(true))
        .add_component<component::shooter>(component::shooter("proj_enemy_prefab", 1));

    entity_t spawner = reg.spawn_entity();
    component::Spawner spawner_component;
    spawner_component._spawnList.push_back(std::make_pair(2, "diagonal_enemy"));
    spawner_component._spawnList.push_back(std::make_pair(4, "diagonal_enemy"));
    reg.add_component<component::Spawner>(spawner, std::move(spawner_component));

    std::cout << "Prefabs: " << PrefabManager::get_instance() << std::endl;

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
