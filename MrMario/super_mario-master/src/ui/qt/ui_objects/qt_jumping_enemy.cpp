#include "qt_jumping_enemy.hpp"

#include <QPainter>

#include "qt_sprites.hpp"

using biv::QtJumpingEnemy;

QtJumpingEnemy::QtJumpingEnemy(const Coord& top_left, const int width, const int height)
	: JumpingEnemy(top_left, width, height) {}

int QtJumpingEnemy::get_layer() const noexcept {
	return ENEMY_LAYER;
}

void QtJumpingEnemy::paint(QPainter& painter) const {
	paint_sprite(
		painter,
		is_active() ? QtSprites::get("jumper") : QtSprites::get_flipped("jumper")
	);
}
