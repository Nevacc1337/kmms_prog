#include "flying_enemy.hpp"

#include <cmath>

using biv::FlyingEnemy;

FlyingEnemy::FlyingEnemy(
	const Coord& top_left, const int width, const int height,
	const int patrol_range
) : RectMapMovableAdapter(top_left, width, height) {
	vspeed = 0;
	hspeed = H_SPEED;
	left_bound = top_left.x - patrol_range;
	right_bound = top_left.x + patrol_range;
}

biv::Rect FlyingEnemy::get_rect() const noexcept {
	return {top_left, width, height};
}

biv::Speed FlyingEnemy::get_speed() const noexcept {
	return {vspeed, hspeed};
}

int FlyingEnemy::get_reward() const noexcept {
	return REWARD;
}

void FlyingEnemy::move_horizontally() noexcept {
	if (!is_active_) {
		return;
	}
	top_left.x += hspeed;
	if (top_left.x < left_bound) {
		top_left.x = left_bound;
		hspeed = std::fabs(hspeed);
	} else if (top_left.x > right_bound) {
		top_left.x = right_bound;
		hspeed = -std::fabs(hspeed);
	}
}

void FlyingEnemy::move_vertically() noexcept {
	if (!is_active_) {
		Movable::move_vertically();
	}
}

void FlyingEnemy::move_map_horizontally(const float offset) noexcept {
	RectMapMovableAdapter::move_map_horizontally(offset);
	left_bound += offset;
	right_bound += offset;
}

void FlyingEnemy::process_horizontal_static_collision(Rect* obj) noexcept {
	hspeed = -hspeed;
	move_horizontally();
}

void FlyingEnemy::process_mario_collision(Collisionable* mario) noexcept {
	if (mario->get_speed().v > 0 && mario->get_speed().v != V_ACCELERATION) {
		kill();
	} else {
		mario->kill();
	}
}

void FlyingEnemy::process_vertical_static_collision(Rect* obj) noexcept {
}
