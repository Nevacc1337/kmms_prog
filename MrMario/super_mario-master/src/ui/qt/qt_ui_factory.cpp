#include "qt_ui_factory.hpp"

using biv::QtUIFactory;

QtUIFactory::QtUIFactory(Game* game) : UIFactory(game) {}

void QtUIFactory::clear_data() {
	game->remove_objs();
	game_map->remove_objs();
	delete mario;
	mario = nullptr;
	boxes.clear();
	full_boxes.clear();
	ships.clear();
	enemies.clear();
	moneys.clear();
	flying_enemies.clear();
	jumping_enemies.clear();
	moving_platforms.clear();
}

void QtUIFactory::create_box(
	const Coord& top_left, const int width, const int height
) {
	QtBox* box = new QtBox(top_left, width, height);
	boxes.push_back(box);
	game->add_map_movable(box);
	game->add_static_obj(box);
	game_map->add_obj(box);
}

void QtUIFactory::create_enemy(
	const Coord& top_left, const int width, const int height
) {
	QtEnemy* enemy = new QtEnemy(top_left, width, height);
	enemies.push_back(enemy);
	game->add_map_movable(enemy);
	game->add_movable(enemy);
	game->add_collisionable(enemy);
	game_map->add_obj(enemy);
}

void QtUIFactory::create_flying_enemy(
	const Coord& top_left, const int width, const int height,
	const int patrol_range
) {
	QtFlyingEnemy* enemy = new QtFlyingEnemy(
		top_left, width, height, patrol_range
	);
	flying_enemies.push_back(enemy);
	game->add_map_movable(enemy);
	game->add_movable(enemy);
	game->add_collisionable(enemy);
	game_map->add_obj(enemy);
}

void QtUIFactory::create_jumping_enemy(
	const Coord& top_left, const int width, const int height
) {
	QtJumpingEnemy* enemy = new QtJumpingEnemy(top_left, width, height);
	jumping_enemies.push_back(enemy);
	game->add_map_movable(enemy);
	game->add_movable(enemy);
	game->add_collisionable(enemy);
	game_map->add_obj(enemy);
}

void QtUIFactory::create_moving_platform(
	const Coord& top_left, const int width, const int height,
	const int patrol_range
) {
	QtMovingPlatform* platform = new QtMovingPlatform(
		top_left, width, height, patrol_range
	);
	moving_platforms.push_back(platform);
	game->add_carrier(platform);
	game->add_map_movable(platform);
	game->add_movable(platform);
	game->add_static_obj(platform);
	game_map->add_obj(platform);
}

void QtUIFactory::create_full_box(
	const Coord& top_left, const int width, const int height
) {
	QtFullBox* full_box = new QtFullBox(top_left, width, height, this);
	full_boxes.push_back(full_box);
	game->add_collisionable(full_box);
	game->add_map_movable(full_box);
	game->add_static_obj(full_box);
	game_map->add_obj(full_box);
}

void QtUIFactory::create_mario(
	const Coord& top_left, const int width, const int height
) {
	game->remove_collisionable(mario);
	game->remove_movable(mario);
	game->remove_mario();
	game_map->remove_obj(mario);
	delete mario;
	mario = nullptr;
	
	mario = new QtMario(top_left, width, height);
	game->add_collisionable(mario);
	game->add_movable(mario);
	game->add_mario(mario);
	game_map->add_obj(mario);
}

void QtUIFactory::create_money(
	const Coord& top_left, const int width, const int height
) {
	QtMoney* money = new QtMoney(top_left, width, height);
	moneys.push_back(money);
	game->add_map_movable(money);
	game->add_movable(money);
	game->add_collisionable(money);
	game_map->add_obj(money);
}

void QtUIFactory::create_ship(
	const Coord& top_left, const int width, const int height
) {
	QtShip* ship = new QtShip(top_left, width, height);
	ships.push_back(ship);
	game->add_map_movable(ship);
	game->add_static_obj(ship);
	game_map->add_obj(ship);
}

biv::GameMap* QtUIFactory::get_game_map(const int height, const int width) {
	if (game_map == nullptr) {
		game_map = new QtGameMap(height, width);
	}
	return game_map;
}

biv::Mario* QtUIFactory::get_mario() {
	return mario;
}
