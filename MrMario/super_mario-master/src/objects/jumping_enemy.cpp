#include "jumping_enemy.hpp"

using biv::JumpingEnemy;

JumpingEnemy::JumpingEnemy(const Coord& top_left, const int width, const int height)
	: RectMapMovableAdapter(top_left, width, height) {
	vspeed = 0;
	hspeed = 0;
}

biv::Rect JumpingEnemy::get_rect() const noexcept {
	return {top_left, width, height};
}

biv::Speed JumpingEnemy::get_speed() const noexcept {
	return {vspeed, hspeed};
}

int JumpingEnemy::get_reward() const noexcept {
	return 50;
}

void JumpingEnemy::move_vertically() noexcept {
	if (is_active_ && on_ground) {
		pause_counter++;
		if (pause_counter >= PAUSE_FRAMES) {
			pause_counter = 0;
			on_ground = false;
			vspeed = ENEMY_JUMP_SPEED;
		}
	}
	Movable::move_vertically();
}

void JumpingEnemy::process_horizontal_static_collision(Rect* obj) noexcept {}

void JumpingEnemy::process_mario_collision(Collisionable* mario) noexcept {
	if (mario->get_speed().v > 0 && mario->get_speed().v != V_ACCELERATION) {
		kill();
	} else {
		mario->kill();
	}
}

void JumpingEnemy::process_vertical_static_collision(Rect* obj) noexcept {
	if (vspeed > 0) {
		top_left.y -= vspeed;
		vspeed = 0;
		on_ground = true;
	} else if (vspeed < 0) {
		top_left.y -= vspeed;
		vspeed = 0;
	}
}
