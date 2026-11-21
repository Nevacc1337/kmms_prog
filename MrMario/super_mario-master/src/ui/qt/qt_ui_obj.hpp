#pragma once

class QPainter;

namespace biv {
	enum QtLayer {
		GROUND_LAYER,
		BLOCK_LAYER,
		ITEM_LAYER,
		ENEMY_LAYER,
		PLAYER_LAYER,
		LAYERS_COUNT
	};

	class QtUIObject {
		public:
			virtual int get_bottom() const noexcept = 0;
			virtual int get_layer() const noexcept = 0;
			virtual int get_left() const noexcept = 0;
			virtual int get_right() const noexcept = 0;
			virtual int get_top() const noexcept = 0;
			virtual void paint(QPainter&) const = 0;
	};
}
