#include "qt_flying_enemy.hpp"

#include <QPainter>

#include "qt_sprites.hpp"

using biv::QtFlyingEnemy;

QtFlyingEnemy::QtFlyingEnemy(
	const Coord& top_left, const int width, const int height,
	const int patrol_range
) : FlyingEnemy(top_left, width, height, patrol_range) {}

int QtFlyingEnemy::get_layer() const noexcept {
	return ENEMY_LAYER;
}

void QtFlyingEnemy::paint(QPainter& painter) const {
	paint_sprite(
		painter,
		is_active()
			? QtSprites::get("goomba_wings")
			: QtSprites::get_flipped("goomba_wings")
	);
}
