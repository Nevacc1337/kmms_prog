#include "qt_enemy.hpp"

#include <QPainter>

#include "qt_sprites.hpp"

using biv::QtEnemy;

QtEnemy::QtEnemy(const Coord& top_left, const int width, const int height)
	: Enemy(top_left, width, height) {}

int QtEnemy::get_layer() const noexcept {
	return ENEMY_LAYER;
}

void QtEnemy::paint(QPainter& painter) const {
	paint_sprite(
		painter,
		is_active() ? QtSprites::get("goomba") : QtSprites::get_flipped("goomba")
	);
}
